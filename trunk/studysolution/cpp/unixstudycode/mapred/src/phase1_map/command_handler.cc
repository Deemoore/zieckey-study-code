#include "command_handler.h"

#include <fstream>

#include "qoslib/include/QOSLibAllExp.h"
#include "qoslib/include/QFileUtil.h"
#include "qoslib/include/QTimer.h"
#include "qoslib/include/QMD5.h"

#include "constant.h"
#include "qlog.h"

#include <gflags/gflags.h>

DEFINE_int32(dump_time, 30, "The max interval between twice dump, measured by second.");
DEFINE_int32(dump_buffer, 8*1024*1024, "The max buffer size of the output buffer size");

CommandHandler::CommandHandler()
: dump_time_interval_(0), last_update_(time(0)), dump_buffer_max_(0)
{
}

CommandHandler::~CommandHandler()
{
    fp_ = NULL;
}

bool CommandHandler::Init(FILE* fp)
{
    dump_time_interval_ = FLAGS_dump_time;
    dump_buffer_max_ = FLAGS_dump_buffer;
    output_buf_.setBufferSize(FLAGS_dump_buffer);
    fp_ = fp;
    return true;
}

bool CommandHandler::Flush(bool force)
{
    bool ret = false;
    if (CheckDumpCount()
                || CheckDumpTime()
                || force)
    {
        if (!Dump())
        {
            return false;  
        }

        last_update_ = time(0);
        ret = true;
    }
    return ret;
}

bool CommandHandler::Dump()
{//{{{
#ifdef _DEBUG
    {
        static int64_t newid = 0;
        std::string outfile_tmp = GetTempOutputFilePath(newid++);
        std::fstream ofp(outfile_tmp.c_str(), std::ios::out|std::ios::binary|std::ios::app);
        ofp.write((char*)output_buf_.getCache(), output_buf_.getSize());
        ofp.flush();
        ofp.close();
    }
#endif

    fwrite(output_buf_.getCache(), output_buf_.getSize(), 1, fp_);
    output_buf_.reset();

    return true;
    //#ifdef _DEBUG
//    {
//        static int64_t newid = 0;
//        std::string outfile_tmp = GetTempOutputFilePath(newid++);
//        std::fstream ofp(outfile_tmp.c_str(), std::ios::out|std::ios::binary);
//        stringvector::iterator it(dump_vect_.begin());
//        stringvector::iterator ite(dump_vect_.end());
//        for (; it != ite; ++it)
//        {
//            ofp << *it;
//        }
//        ofp.flush();
//        ofp.close();
//    }
//#endif
//    stringvector::iterator it(dump_vect_.begin());
//    stringvector::iterator ite(dump_vect_.end());
//    for (; it != ite; ++it)
//    {
//        fwrite((*it).c_str(), (*it).length(), 1, fp_);
//    }
//    return true;
}//}}}

bool CommandHandler::CheckDumpTime()
{
    return last_update_ + dump_time_interval_ < time(0);
}

bool CommandHandler::CheckDumpCount()
{
    return false; 
}


namespace
{//{{{
    //return the time string with micro second
    std::string GetUTimeString()
    {
        std::string::value_type szTime[128] = {};
        struct tm *pTime;
        time_t ctTime;
        time( &ctTime );
        pTime = localtime( &ctTime );


        long uunit = 1000 * 1000;
        snprintf( szTime, sizeof(szTime), "%4d%.2d%.2d%.2d%.2d%.2d_%.6ld", 
                    pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday,
                    pTime->tm_hour, pTime->tm_min, pTime->tm_sec, 
                    ((long)(s_pTimer->getImmediateSeconds() * uunit))%uunit);

        return std::string(szTime);
    }

    //return the time string, the last 2 chars represent second
    std::string GetTimeString()
    {
        std::string::value_type szTime[128] = {};
        struct tm *pTime;
        time_t ctTime;
        time( &ctTime );
        pTime = localtime( &ctTime );

        snprintf( szTime, sizeof(szTime), "%4d%.2d%.2d%.2d%.2d%.2d", 
                    pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday,
                    pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
        return std::string(szTime);
    }
}//}}}

std::string CommandHandler::GetTempOutputFilePath(int64_t file_id)
{
    char buf[512] = {};
    snprintf(buf, sizeof(buf), "Inc_%ld_%s_%u.tmp", 
                file_id, GetUTimeString().c_str(), output_buf_.getSize() );	

    return buf;
}


