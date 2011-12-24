#ifndef _REDUCE_COMMAND_HANDLER_H_
#define _REDUCE_COMMAND_HANDLER_H_

#include "command_handler.h"

#include "qoslib/include/QOSLibAllExp.h"
#include "qoslib/include/QTokener.h"
#include "qoslib/include/QMD5.h"

#include "constant.h"
#include "qlog.h"

class CommandHandlerImpl : public CommandHandler
{
    typedef std::set<std::string> stringset;
    typedef std::map<std::string, stringset> string_stringset_map;

public:

    CommandHandlerImpl();
    virtual bool Work(osl::Slice& command);

    //When finish the job, we do the last flush
    void LastSerialize()
    {
        Serialize();
    }

private:

    bool GetMIDVer(osl::Slice& command, osl::Slice& mid, osl::Slice& ver);

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
};

#endif //_COMMAND_HANDLER_H_

