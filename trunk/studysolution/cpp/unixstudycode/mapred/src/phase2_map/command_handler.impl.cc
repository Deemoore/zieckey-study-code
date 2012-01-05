#include "command_handler.impl.h"

CommandHandlerImpl::CommandHandlerImpl()
        : all_version_("-1"),
          current_mid_("", 0)
{
    string_map_[all_version_] = 0;
    cache_string_.resize(128);//only for cache
    ver_vector_.reserve(20);
    
}

bool CommandHandlerImpl::Work(osl::Slice& command)
{        
    ver_vector_.clear();
#ifdef _DEBUG
    qLogTraces(kLogName) << "line:" << command.toString();
#endif
    token_.reset(command.data(), command.size());
    current_mid_ = token_.nextSlice();
    if (strncmp(current_mid_.data(), last_mid_.data(), current_mid_.size()) != 0)
    {
        //represents all mids in any versions
        string_map_[all_version_] += 1;
        TRACE("current_mid=%s last_mid=%s diff +1", std::string(current_mid_.data(), current_mid_.size()).c_str(), last_mid_.c_str());
    }
    else
    {
        TRACE("current_mid=%s last_mid=%s equals!", std::string(current_mid_.data(), current_mid_.size()).c_str(), last_mid_.c_str());
    }

    last_mid_ = std::string(current_mid_.data(), current_mid_.size());
    while (!token_.isEnd())
    {
        ver_vector_.push_back(token_.nextSlice());
#ifdef _DEBUG
        qLogTrace(kLogName, "Get a version:'%s'", ver_vector_.rbegin()->toString().c_str());
#endif
    }

#ifdef _DEBUG
    //osl::Slice& last_slice = ver_vector_[ver_vector_.size() - 1];
    //last_slice = osl::Slice(last_slice.data(), last_slice.size() - 1);
    //qLogTrace(kLogName, "The last version modify to:'%s'", last_slice.toString().c_str());
#endif

    stringmap::iterator itmap = string_map_.end();
    stringmap::iterator itemap = string_map_.end();
    slicevector::iterator it(ver_vector_.begin());
    slicevector::iterator ite(ver_vector_.end());
    for (; it != ite; ++it)
    {
        if (it->size() == 0)
        {
            continue;
        }

        cache_string_ = std::string((*it).data(), (*it).size());
        itmap = string_map_.find(cache_string_);
        if (itmap == itemap)
        {
#ifdef _DEBUG
            qLogTrace(kLogName, "Insert a new version '%s'", cache_string_.c_str());
#endif
            string_map_[cache_string_] = 1;
        }
        else
        {
            itmap->second += 1;
#ifdef _DEBUG
            qLogTrace(kLogName, "Add 1 to version '%s' now count=%u", cache_string_.c_str(), itmap->second);
#endif
        }
    }

    return true;
}


