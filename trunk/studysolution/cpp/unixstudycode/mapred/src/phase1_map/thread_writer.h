#ifndef _THREAD_WRITER_H_
#define _THREAD_WRITER_H_

#include <stdio.h>

#include "qoslib/include/QOSLibAllExp.h"
#include "qoslib/include/QDataStream.h"
#include "qoslib/include/QThread.h"
#include "qoslib/include/QMyOS.h"
#include "qoslib/include/QLock.h"
#include "qoslib/include/QEvent.h"

#include "file_writer.h"

class ThreadWriter : public FileWriter, public osl::Thread
{
public:
    ThreadWriter(FILE* fp);

    virtual ~ThreadWriter() 
    { 
        fp_ = NULL; 
    }

    virtual bool Init() { return true; }

    virtual bool Write(const void* data, size_t len);

    //called from main thread
    virtual bool Flush();

protected:

    size_t dump_buffer_max_;

    osl::MemoryDataStreamPtr output_buf_;

    typedef std::list <osl::MemoryDataStreamPtr> MemoryDataStreamPtrList;
    MemoryDataStreamPtrList data_buf_list_;
    osl::Lock               data_buf_list_lock_;
    osl::Event              data_buf_list_changed_envent_;

private:
    std::string GetTempOutputFilePath(int64_t file_id);

    virtual void run();
};

#endif 


