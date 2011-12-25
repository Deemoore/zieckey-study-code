#include "thread_writer.h"

#include <fstream>

#include <gflags/gflags.h>

DECLARE_int32(dump_buffer);

ThreadWriter::ThreadWriter(FILE* fp) 
    : FileWriter(fp) 
    , dump_buffer_max_(FLAGS_dump_buffer)
    , output_buf_(new osl::MemoryDataStream(FLAGS_dump_buffer))
{
}

bool ThreadWriter::Write(const void* data, size_t len)
{
    if (output_buf_->getSize() + len >= dump_buffer_max_)
    {
        {
            H_AUTOLOCK(data_buf_list_lock_);
            data_buf_list_.push_back(output_buf_);
        }
        data_buf_list_changed_envent_.signal();
        output_buf_ = (new osl::MemoryDataStream(FLAGS_dump_buffer));
    }
    output_buf_->write(data, len);

    return true;
}

bool ThreadWriter::Flush()
{//{{{
    {
        H_AUTOLOCK(data_buf_list_lock_);
        data_buf_list_.push_back(output_buf_);
    }

    stop();//stop the thread
    data_buf_list_changed_envent_.signal();

    //waiting for the thread to write all the data and stop
    while(isRunning())
    {
        stop();
        data_buf_list_changed_envent_.signal();
        usleep(1000);
    }

    return true;
}//}}}

namespace
{//{{{
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
}

std::string ThreadWriter::GetTempOutputFilePath(int64_t file_id)
{
    char buf[512] = {};
    snprintf(buf, sizeof(buf), "Inc_%ld_%s_%u.tmp", 
                file_id, GetTimeString().c_str(), 0);	

    return buf;
}//}}}

void ThreadWriter::run()
{
    osl::MemoryDataStreamPtr ptr_data_buf;
    while (isRunning())
    {
        data_buf_list_changed_envent_.wait();

        while(!data_buf_list_.empty())
        {
            {
                H_AUTOLOCK(data_buf_list_lock_);   
                ptr_data_buf = data_buf_list_.front();
                data_buf_list_.pop_front();
            }
#ifdef _DEBUG //{{{
            {
                static int64_t newid = 0;
                std::string outfile_tmp = GetTempOutputFilePath(newid++);
                std::fstream ofp(outfile_tmp.c_str(), std::ios::out|std::ios::binary|std::ios::app);
                ofp.write((char*)ptr_data_buf->getCache(), ptr_data_buf->getSize());
                ofp.flush();
                ofp.close();
            }
#endif//}}}

            fwrite(ptr_data_buf->getCache(), 1, ptr_data_buf->getSize(), fp_);
        }
    }
}

