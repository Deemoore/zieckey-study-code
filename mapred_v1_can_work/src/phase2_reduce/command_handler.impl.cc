#include "command_handler.impl.h"

CommandHandlerImpl::CommandHandlerImpl(): all_version_("-1")
{
    string_map_[all_version_] = 0;
    cache_string_.resize(128);//only for cache
}

bool CommandHandlerImpl::Work(osl::Slice& command)
{        
    //qLogTraces(kLogName) << "line:" << command.toString();

    token_.reset(command.data(), command.size());
    osl::Slice ver_slice = token_.nextSlice();
    osl::Slice count_slice = token_.nextSlice();

    //qLogTrace(kLogName, "ver='%s' count='%s'", ver_slice.toString().c_str(), count_slice.toString().c_str());

    stringmap::iterator itmap = string_map_.end();
    stringmap::iterator itemap = string_map_.end();

    cache_string_ = std::string(ver_slice.data(), ver_slice.size());
    itmap = string_map_.find(cache_string_);
    if (itmap == itemap)
    {
        //qLogTrace(kLogName, "Insert a new version '%s'", cache_string_.c_str());
        string_map_[cache_string_] = atoi(count_slice.data());
    }
    else
    {
        itmap->second += atoi(count_slice.data());
        //qLogTrace(kLogName, "Add %d to version '%s' now count=%u", atoi(count_slice.data()), cache_string_.c_str(), itmap->second);
    }


    return true;
}


