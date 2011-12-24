#include "line_reader.h"

#include "qlog.h"
#include "constant.h"

DEFINE_int32(buf_buffer_len, 4096, "The max buffer length of one line");

bool LineReader::GetLine(Slice& line)
{
    if (0 != feof(fp_))
    {
        qLogInfos(kLogName) << "file end!";
        return false;
    }

    if (NULL == fgets(buf_, FLAGS_buf_buffer_len, fp_))
    {   
        qLogInfos(kLogName) << "fgets return NULL!";
        return false;
    }

    //qLogInfos(kLogName) << buf_;
    line = buf_;
    return true;
}


