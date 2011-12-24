#ifndef _MAP_COMMAND_HANDLER_H_
#define _MAP_COMMAND_HANDLER_H_

#include "command_handler.h"

#include "qoslib/include/QOSLibAllExp.h"
#include "qoslib/include/QTokener.h"
#include "qoslib/include/QMD5.h"

#include "constant.h"
#include "qlog.h"

class MapCommandHandler : public CommandHandler
{
public:
    MapCommandHandler();
    virtual bool Work(Slice& command);

private:
    /**
     * Get the mid and version from the command
     * @param[in] command
     * @param[out] mid 
     * @param[out] ver 
     * @return true if get successfully
     */
    bool GetMIDVer(Slice& command, Slice& mid, Slice& ver);

    void GetMID(Slice& command, Slice& mid)
    {

        static const unsigned char valid_md5_chs[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        size_t curr_pos = token_.getCurPos();
        while (1 == valid_md5_chs[token_.next()]) //TODO if (token_.next() > 0)
        {
            ;
        }

        token_.back();

        size_t end_pos = token_.getCurPos();
        mid = Slice(command.data() + curr_pos, end_pos - curr_pos);//TODO if (end_pos - curr_pos) > 0)

#ifdef _DEBUG
        std::string st(command.data() + curr_pos, end_pos - curr_pos);
        qLogTraces(kLogName) << "find mid='" << st << "'";
#endif
    }

    void GetVer(Slice& command, Slice& ver)
    {

        static const char valid_ver_chs[] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };

        size_t curr_pos = token_.getCurPos();
        while (1 == valid_ver_chs[token_.next()]) //TODO if (token_.next() > 0)
        {
            ;
        }
        token_.back();

        size_t end_pos = token_.getCurPos();
        ver = Slice(command.data() + curr_pos, end_pos - curr_pos);//TODO if (end_pos - curr_pos) > 0)

#ifdef _DEBUG
        std::string st(command.data() + curr_pos, end_pos - curr_pos);
        qLogTraces(kLogName) << "find ver='" << st << "'";
#endif
    }


    void Serialize(const Slice& mid, const Slice& ver)
    {
        //mid\tver\t1\n
        //54cfa66d45acfd4fdafdeb077f7d1038\t7.0.0.1000\n
        dump_vect_.push_back(std::string());
        std::string& s = *dump_vect_.rbegin();
        s.resize(mid.size() + ver.size() + 2);// \t \n
        memcpy(&s[0], mid.data(), mid.size());
        s[mid.size()] = '\t';
        memcpy(&s[0] + mid.size() + 1, ver.data(), ver.size());
        s[mid.size() + ver.size() + 1] = '\n';
    }

private:
    osl::Tokener token_;
};

#endif //_COMMAND_HANDLER_H_

