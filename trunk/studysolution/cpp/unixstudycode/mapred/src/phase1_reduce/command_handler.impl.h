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
    void LastSerialize()
    {
        //LastSerialize_output();
        //LastSerialize_aggregate();
        LastSerialize_aggregate_opt();
    }

private:
    void LastSerialize_output();
    void LastSerialize_aggregate();
    void LastSerialize_aggregate_opt();

private:
    osl::Tokener token_;

    std::string current_mid_;

    string_stringset_map mid_verset_map_;//mid/version_set map
};

inline void CommandHandlerImpl::LastSerialize_aggregate()
{//{{{
    //step 1 : represents all mids in any versions
    stringu32map ver_count_map;
    ver_count_map["-1"] = mid_verset_map_.size();

    //step 2 : aggregate now in memory
    {
        string_stringset_map::iterator it(mid_verset_map_.begin());
        string_stringset_map::iterator ite(mid_verset_map_.end());
        stringu32map::iterator vc_it = ver_count_map.end();
        for (; it != ite; ++it)
        {
            stringset& verset = it->second;
            stringset::iterator itset(verset.begin());
            stringset::iterator itendset(verset.end());
            for (; itset != itendset; ++itset)
            {
                if ((*itset).size() == 0)
                {
                    continue;
                }
                vc_it = ver_count_map.find(*itset);
                if (vc_it == ver_count_map.end())
                {
                    ver_count_map[*itset] = 1;
                }
                else
                {
                    vc_it->second += 1;
                }
            }
        }

        mid_verset_map_.clear();
    }

    //step 3 : output
    {
        stringu32map::iterator it = ver_count_map.begin();
        stringu32map::iterator ite = ver_count_map.end();
        std::string cache_string;
        cache_string.reserve(12);
        for (; it != ite; ++it)
        {
            //qLogTrace(kLogName, "version=\"%s\" count=%u", it->first.c_str(), it->second);
            AddOutput(it->first.c_str(), it->first.length());
            AddOutput("\t", 1);
            cache_string = osl::StringUtil::valueOf(it->second);
            AddOutput(cache_string.c_str(), cache_string.length());
            AddOutput("\n", 1);
        }
    }
}//}}}

namespace qh { namespace str { struct less { //{{{ 
            bool operator()(const char* s1, const char* s2) const
            {
                return strcmp(s1, s2) < 0;
            }
        };
    }//end of namespace str
}//}}} end of namespace qh  

inline void CommandHandlerImpl::LastSerialize_aggregate_opt()
{//{{{
    //step 1 : represents all mids in any versions
    typedef std::map<const char*, osl::u32, qh::str::less> charptru32map;
    charptru32map ver_count_map;
    ver_count_map["-1"] = mid_verset_map_.size();

    //step 2 : aggregate now in memory
    {
        string_stringset_map::iterator it(mid_verset_map_.begin());
        string_stringset_map::iterator ite(mid_verset_map_.end());
        charptru32map::iterator vc_it = ver_count_map.end();
        for (; it != ite; ++it)
        {
            stringset& verset = it->second;
            stringset::iterator itset(verset.begin());
            stringset::iterator itendset(verset.end());
            for (; itset != itendset; ++itset)
            {
                if ((*itset).size() == 0)
                {
                    continue;
                }
                vc_it = ver_count_map.find((*itset).c_str());
                if (vc_it == ver_count_map.end())
                {
                    ver_count_map[(*itset).c_str()] = 1;
                }
                else
                {
                    vc_it->second += 1;
                }
            }
        }
    }

    //step 3 : output
    {
        charptru32map::iterator it = ver_count_map.begin();
        charptru32map::iterator ite = ver_count_map.end();
        std::string cache_string;
        cache_string.reserve(12);
        for (; it != ite; ++it)
        {
            //qLogTrace(kLogName, "version=\"%s\" count=%u", it->first.c_str(), it->second);
            AddOutput(it->first, strlen(it->first));
            AddOutput("\t", 1);
            cache_string = osl::StringUtil::valueOf(it->second);
            AddOutput(cache_string.c_str(), cache_string.length());
            AddOutput("\n", 1);
        }
    }
}//}}}

inline void CommandHandlerImpl::LastSerialize_output()
{//{{{
    //---------------------------------------------
    string_stringset_map::iterator it(mid_verset_map_.begin());
    string_stringset_map::iterator ite(mid_verset_map_.end());
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
}//}}}

#endif //_COMMAND_HANDLER_H_

