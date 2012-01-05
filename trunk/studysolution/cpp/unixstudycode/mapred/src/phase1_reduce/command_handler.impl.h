#ifndef _REDUCE_COMMAND_HANDLER_H_
#define _REDUCE_COMMAND_HANDLER_H_

#include "command_handler.h"

#include "qoslib/include/QOSLibAllExp.h"
#include "qoslib/include/QTokener.h"
#include "qoslib/include/QMD5.h"

#include "constant.h"
#include "common.h"
#include "qlog.h"

class CommandHandlerImpl : public CommandHandler
{

public:

    CommandHandlerImpl();
    virtual bool Work(osl::Slice& command);

    //When finish the job, we do the last flush
    void LastSerialize();

private:

    //bool GetMIDVer(osl::Slice& command, osl::Slice& mid, osl::Slice& ver);

    void Serialize()
    {
        AddOutput(current_mid_.c_str(), current_mid_.length());
        stringset::iterator it(ver_set_.begin());
        stringset::iterator ite(ver_set_.end());
        for (; it != ite; ++it)
        {
            AddOutput("\t", 1);
            AddOutput(it->c_str(), it->length());
        }
        AddOutput("\n", 1);

        //qLogTraces(kLogName) << "Serialize \"" << oss.str() << "\"";
        ver_set_.clear();
    }


private:
    osl::Tokener token_;
    size_t mid_total_count_;

    std::string current_mid_;
    stringset   ver_set_;

    string_stringset_map mid_verset_map;//mid/version_set map
};


inline void CommandHandlerImpl::LastSerialize()
{
    string_stringset_map::iterator it(mid_verset_map.begin());
    string_stringset_map::iterator ite(mid_verset_map.end());
    for (; it != ite; ++it)
    {
        AddOutput(it->first.data(), it->first.size());

        stringset& verset = it->second;
        stringset::iterator itset(verset.begin());
        stringset::iterator itendset(verset.end());
        for (; itset != itendset; ++itset)
        {
            if ((*itset).size() > 0)
            {
                AddOutput("\t", 1);
                AddOutput((*itset).data(), (*itset).size());
            }
        }

        AddOutput("\n", 1);
    }
}



#endif //_COMMAND_HANDLER_H_

