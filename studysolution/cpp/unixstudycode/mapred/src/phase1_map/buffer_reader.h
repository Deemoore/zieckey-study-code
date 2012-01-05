#ifndef _FILE_BUFFER_READER_H_
#define _FILE_BUFFER_READER_H_

#include <gflags/gflags.h>

#include "file_reader.h"

#include "qlog.h"
#include "constant.h"

DECLARE_int32(input_buffer_size);

class BufferReader : public FileReader
{
public:
    BufferReader(FILE* fp)
        : FileReader(fp)
        , buf_size_(FLAGS_input_buffer_size)
    {
        data_buf_.reserve(FLAGS_input_buffer_size);
    }

    ~BufferReader()
    {
    }

    virtual bool Init()
    {
        if (0 != feof(fp_))
        {
            //qLogInfos(kLogName) << "file end!";
            return false;
        }

        int readn = fread(data_buf_.getCache(), 1, buf_size_, fp_);
        if (readn <= 0)
        {
            return false;
        }

        data_buf_.seekp(readn);
        return true;
    }

    
#ifdef _DEBUG
    #define PrintDebugString() \
    {\
        std::string s((char*)data_buf_.getCurReadBuffer(), 64);\
        data_buf_.toText();\
        qLogTraces(kLogName) \
            << "\n\tbuf_size=" << buf_size_\
            << "\n\tread_pos=" << data_buf_.tellg()\
            << "\n\twrite_pos=" << data_buf_.tellp()\
            << "\n\tcontent---------------------\n" \
            << "\n-------------------------------\n"\
            << "next string being:" << s\
            << "\n-------------------------------\n";\
    }
#else
    #define PrintDebugString() {}    
#endif

    virtual bool GetLine(osl::Slice& line);

private:
    size_t buf_size_;
    osl::MemoryDataStream data_buf_;
};

#endif

