#include "thread_writer.h"

#include <fstream>
#include <gflags/gflags.h>

#include "qoslib/include/QThread.h"
#include "qoslib/include/QMyOS.h"
#include "qoslib/include/QLock.h"
#include "qoslib/include/QEvent.h"

#include "constant.h"
#include "qlog.h"

DECLARE_int32(dump_buffer_size);

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
//}}}

class ThreadWriter::WThread : public osl::Thread
{//{{{
    public:
        WThread(FILE* fp)
            : fp_(fp)
        {
            running_ = false;
        }

        ~WThread()
        { 
            fp_ = NULL; 
        }

        void Push(osl::MemoryDataStreamPtr& data_buf)
        {        
            if (data_buf->getSize() == 0)
            {
                return;
            }

            {
                H_AUTOLOCK(data_buf_list_lock_);
                data_buf_list_.push_back(data_buf);
#ifdef _DEBUG
                qLogTraces(kLogName) 
                    << "Add data to write, size=" << data_buf->getSize()
                    << " data_buf_list_.size()=" << data_buf_list_.size();
#endif
            }
            data_buf_list_changed_event_.signal();
        }

        void Flush()
        {
            fflush(fp_);
        }

        virtual void stop()
        {
            running_ = false;
            data_buf_list_changed_event_.signal();
            osl::Thread::stop();
        }
    private:
        FILE* fp_;

        typedef std::list <osl::MemoryDataStreamPtr> MemoryDataStreamPtrList;
        MemoryDataStreamPtrList data_buf_list_;
        osl::Lock               data_buf_list_lock_;
        osl::Event              data_buf_list_changed_event_;

        bool    running_;

    private:

        std::string GetTempOutputFilePath(int64_t file_id)
        {
            char buf[512] = {};
            snprintf(buf, sizeof(buf), "Inc_%ld_%s_%u.tmp", 
                        file_id, GetTimeString().c_str(), 0);	

            return buf;
        }

        virtual void run()
        {
            running_ = true;

            osl::MemoryDataStreamPtr ptr_data_buf;

            while (running_)
            {
                data_buf_list_changed_event_.wait();

                while(!data_buf_list_.empty())
                {
                    {
                        H_AUTOLOCK(data_buf_list_lock_);   
                        ptr_data_buf = data_buf_list_.front();
                        data_buf_list_.pop_front();

#ifdef _DEBUG
                qLogTraces(kLogName) 
                    << "Pop data to write, size=" << ptr_data_buf->getSize()
                    << " data_buf_list_ remain count=" << data_buf_list_.size();
#endif

                    }

#ifdef _DEBUG //{{{
                    {
                        static std::string outfile_tmp = GetTempOutputFilePath(0);
                        std::fstream ofp(outfile_tmp.c_str(), std::ios::out|std::ios::binary|std::ios::app);
                        ofp.write((char*)ptr_data_buf->getCache(), ptr_data_buf->getSize());
                        ofp.flush();
                        ofp.close();
                    }
#endif//}}}

                    fwrite(ptr_data_buf->getCache(), 1, ptr_data_buf->getSize(), fp_);
                }
            }//end of while
        }

        
};//}}}

ThreadWriter::ThreadWriter(FILE* fp) 
    : FileWriter(fp) 
    , dump_buffer_max_(FLAGS_dump_buffer_size)
    , output_buf_(new osl::MemoryDataStream(FLAGS_dump_buffer_size))
{
    thread_ = new WThread(fp);
}

bool ThreadWriter::Write(const void* data, size_t len)
{
#ifdef _DEBUG
    qLogTraces(kLogName) 
        << "write data size=" << len
        << " before this write, data_buf_ current size=" << output_buf_->getSize();
#endif

    if (output_buf_->getSize() + len >= dump_buffer_max_)
    {
#ifdef _DEBUG
        qLogTraces(kLogName) 
            << "Add current buf to thread writer, current data_buf_.size()=" << output_buf_->getSize() 
            << " dump_buffer_max_=" << dump_buffer_max_;
#endif

        thread_->Push(output_buf_);
        output_buf_ = (new osl::MemoryDataStream(dump_buffer_max_));
    }

    output_buf_->write(data, len);

    return true;
}

bool ThreadWriter::Flush()
{//{{{
    thread_->Push(output_buf_);
    //thread_->Flush();

    //waiting for the thread to write all the data and stop
    while(thread_->isRunning())
    {
        thread_->stop();
        usleep(1000);
    }

    thread_->Flush();

    return true;
}//}}}

bool ThreadWriter::Init() 
{ 
    return thread_->start(); 
}
