#include "command_handler.impl.h"


CommandHandlerImpl::CommandHandlerImpl()
{
}

bool CommandHandlerImpl::Work(osl::Slice& command)
{
    osl::Slice mid;
    osl::Slice ver;
    if (!GetMIDVer(command, mid, ver))
    {
        return false;
    }

    if (strncmp(current_mid_.c_str(), mid.data(), mid.size()) == 0)
    {
        ver_set_.insert(std::string(ver.data(), ver.size()));
        //qLogTraces(kLogName) << "equals mid=" << current_mid_ << " insert ver=" << std::string(ver.data(), ver.size()) << " ver_set_.size()=" << ver_set_.size();
    }
    else
    {
        if (current_mid_.length() == 0)//the first time
        {
            //qLogTraces(kLogName) << "first mid=" << current_mid_ << " insert ver=" << std::string(ver.data(), ver.size());
            current_mid_ = std::string(mid.data(), mid.size());
            ver_set_.insert(std::string(ver.data(), ver.size()));
        }
        else
        {
            Serialize();
            ver_set_.insert(std::string(ver.data(), ver.size()));
            //qLogTraces(kLogName) << "Change from " << current_mid_ << " to " << std::string(mid.data(), mid.size()) << " insert ver=" << std::string(ver.data(), ver.size());
            current_mid_ = std::string(mid.data(), mid.size());
        }
    }

    return true;
}

bool CommandHandlerImpl::GetMIDVer(osl::Slice& command, osl::Slice& mid, osl::Slice& ver)
{
    token_.reset(command.data(), command.size());

    token_.skipTo('\t');
    size_t _pos = token_.getCurPos();
    mid = osl::Slice(command.data(), _pos);
    ver = osl::Slice(command.data() + _pos + 1, command.size() - mid.size() - 2);

    /*
#ifdef _DEBUG
    std::string a(mid.data(), mid.size());
    std::string b(ver.data(), ver.size());
    std::string c(command.data(), command.size() - 1);
    qLogTrace(kLogName, "command  %s", c.data());
    qLogTrace(kLogName, "mid ver '%s'%s'", a.data(), b.data());
#endif
    */
    return true;
}

