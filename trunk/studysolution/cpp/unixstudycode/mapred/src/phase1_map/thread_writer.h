#ifndef _THREAD_WRITER_H_
#define _THREAD_WRITER_H_

#include <stdio.h>

#include "qoslib/include/QOSLibAllExp.h"
#include "qoslib/include/QDataStream.h"

#include "file_writer.h"

class ThreadWriter : public FileWriter
{
    class WThread;

public:

    ThreadWriter(FILE* fp);

    virtual ~ThreadWriter() 
    { 
    }

    virtual bool Init(); 

    virtual bool Write(const void* data, size_t len);

    //called from main thread
    virtual bool Flush();

protected:
    size_t dump_buffer_max_;

    osl::MemoryDataStreamPtr output_buf_;

    WThread*    thread_;

};

#endif 


