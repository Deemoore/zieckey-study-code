#include "command_handler.impl.h"


CommandHandlerImpl::CommandHandlerImpl()
{
}

bool CommandHandlerImpl::Work(osl::Slice& command)
{
    token_.reset(command.data(), command.size());
    current_mid_ = token_.nextString();
    TRACE("mid=%s", current_mid_.c_str());
    stringset& ver_set = mid_verset_map[current_mid_];
    while (!token_.isEnd())
    {
#ifdef _TRACE
        std::string ver = token_.nextString();
        ver_set.insert(ver);
        TRACE("\tver=%s", ver.c_str());
#else
        ver_set.insert(token_.nextString());
#endif
    }

    return true;
}

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
