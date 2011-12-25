#include "buffer_writer.h"
#include <fstream>
#include <gflags/gflags.h>
#include "qoslib/include/QTimer.h"

DEFINE_int32(dump_buffer, 16*1024*1024, "The max buffer size of the output buffer size");

BufferWriter::BufferWriter(FILE* fp) 
    : FileWriter(fp) 
    , dump_buffer_max_(FLAGS_dump_buffer)
{
    output_buf_.reserve(FLAGS_dump_buffer);
}

bool BufferWriter::Write(const void* data, size_t len)
{
    if (output_buf_.getSize() + len >= dump_buffer_max_)
    {
        Flush();
    }
    output_buf_.write(data, len);

    return true;
}

bool BufferWriter::Flush()
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

    fwrite(output_buf_.getCache(), 1, output_buf_.getSize(), fp_);
    output_buf_.reset();
    return true;
}//}}}

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

std::string BufferWriter::GetTempOutputFilePath(int64_t file_id)
{
    char buf[512] = {};
    snprintf(buf, sizeof(buf), "Inc_%ld_%s_%u.tmp", 
                file_id, GetUTimeString().c_str(), output_buf_.getSize() );	

    return buf;
}

