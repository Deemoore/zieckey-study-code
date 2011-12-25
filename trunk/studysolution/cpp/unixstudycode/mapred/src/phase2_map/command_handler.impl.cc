#include "command_handler.impl.h"

CommandHandlerImpl::CommandHandlerImpl(): all_version_("0.0")
{
    string_map_[all_version_] = 0;
    cache_string_.resize(128);//only for cache
    slice_vector_.reserve(20);
}

bool CommandHandlerImpl::Work(osl::Slice& command)
{        
    string_map_[all_version_] += 1;//represents all mids in any versions

    slice_vector_.clear();
    //qLogTraces(kLogName) << "line:" << command.toString();
    token_.reset(command.data(), command.size());
    token_.skipTo('\t');
    token_.next();
    while (!token_.isEnd())
    {
        slice_vector_.push_back(token_.nextSlice());
        //qLogTrace(kLogName, "Get a version:'%s'", slice_vector_.rbegin()->toString().c_str());
    }

    osl::Slice& last_slice = slice_vector_[slice_vector_.size() - 1];
    last_slice = osl::Slice(last_slice.data(), last_slice.size() - 1);
    //qLogTrace(kLogName, "The last version modify to:'%s'", last_slice.toString().c_str());

    stringmap::iterator itmap = string_map_.end();
    stringmap::iterator itemap = string_map_.end();
    slicevector::iterator it(slice_vector_.begin());
    slicevector::iterator ite(slice_vector_.end());
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
            //qLogTrace(kLogName, "Insert a new version '%s'", cache_string_.c_str());
            string_map_[cache_string_] = 1;
        }
        else
        {
            itmap->second += 1;
            //qLogTrace(kLogName, "Add 1 to version '%s' now count=%u", cache_string_.c_str(), itmap->second);
        }
    }

    return true;
}


