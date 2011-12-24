#ifndef _REDUCE_COMMAND_HANDLER_H_
#define _REDUCE_COMMAND_HANDLER_H_

#include "command_handler.h"

#include "qoslib/include/QOSLibAllExp.h"
#include "qoslib/include/QTokener.h"
#include "qoslib/include/QMD5.h"

#include "constant.h"
#include "qlog.h"

class ReduceCommandHandler : public CommandHandler
{
    typedef std::set<std::string> stringset;
    typedef std::map<std::string, stringset> string_stringset_map;

public:

    ReduceCommandHandler();
    virtual bool Work(Slice& command);

    //When finish the job, we do the last flush
    bool LastSerialize()
    {
        Serialize();
    }

private:

    bool GetMIDVer(Slice& command, Slice& mid, Slice& ver);

    void Serialize()
    {
        std::ostringstream oss;
        oss << current_mid_;
        stringset::iterator it(ver_set_.begin());
        stringset::iterator ite(ver_set_.end());
        for (; it != ite; ++it)
        {
            oss << "\t" << *it;
        }
        oss << "\n";
        dump_vect_.push_back(oss.str());

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

