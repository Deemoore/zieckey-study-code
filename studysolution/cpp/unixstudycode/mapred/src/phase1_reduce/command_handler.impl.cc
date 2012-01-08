#include "command_handler.impl.h"


CommandHandlerImpl::CommandHandlerImpl()
{
#ifdef USING_HASH_MAP
    mid_verset_map_.rehash(2473640);
#endif
}

#ifdef USING_TOKENER
bool CommandHandlerImpl::Work(osl::Slice& command)
{//{{{
    token_.reset(command.data(), command.size());
    current_mid_ = token_.nextString();
    TRACE("mid=%s", current_mid_.c_str());
    stringset& verset = mid_verset_map_[current_mid_];
#ifdef USING_HASH_MAP
    if (verset.size() == 0)
    {
        //first time
        verset.rehash(800);
    }
#endif

    while (!token_.isEnd())
    {
#ifdef _TRACE
        std::string ver = token_.nextString();
        verset.insert(ver);
        TRACE("\tver=%s", ver.c_str());
#else
        verset.insert(token_.nextString());
#endif
    }

    return true;
}//}}}
#else
bool CommandHandlerImpl::Work(osl::Slice& command)
{//{{{
    const char* sz = command.data();
    size_t current_pos = GetMIDLen(sz);
    current_mid_ = std::string(sz, current_pos);
    TRACE("mid=%s", current_mid_.c_str());
    stringset& verset = mid_verset_map_[current_mid_];
#ifdef USING_HASH_MAP
    if (verset.size() == 0)
    {
        //first time
        verset.rehash(800);
    }
#endif

    size_t len = 0;
    while (current_pos < command.size())
    {
        if (sz[current_pos] <= ' ')
        {
            ++current_pos;
            continue;
        }

        len = GetVerLen(sz + current_pos);
#ifdef _TRACE
        std::string ver(sz + current_pos, len);
        verset.insert(ver);
        TRACE("\tver=%s", ver.c_str());
#else
        verset.insert(std::string(sz + current_pos, len));
#endif
        current_pos += len + 1;//+1 means we directly skip one char(which is '\t')
    }
    return true;
}//}}}
#endif

/*
bool CommandHandlerImpl::GetMIDVer(osl::Slice& command, osl::Slice& mid, osl::Slice& ver)
{
    token_.reset(command.data(), command.size());

    token_.skipTo('\t');
    size_t _pos = token_.getCurPos();
    mid = osl::Slice(command.data(), _pos);
    ver = osl::Slice(command.data() + _pos + 1, command.size() - mid.size() - 1);

#ifdef _DEBUG
    std::string a(mid.data(), mid.size());
    std::string b(ver.data(), ver.size());
    std::string c(command.data(), command.size() - 1);
    qLogTrace(kLogName, "command  %s", c.data());
    qLogTrace(kLogName, "mid ver '%s'%s'", a.data(), b.data());
#endif
    return true;
}
*/
