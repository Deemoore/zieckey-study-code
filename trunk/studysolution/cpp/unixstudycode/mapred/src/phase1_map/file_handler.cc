#include "file_handler.h"

#include <gflags/gflags.h>
#include <qlog.h>

#include "line_reader.h"

DEFINE_string(file_reader_type, "LineReader", "The file reader type, options : LineReader , BufferReader");

bool FileHandler::Init(FILE* fp)
{
    if (FLAGS_file_reader_type == "LineReader")
    {
        reader_ = new LineReader(fp);
        return true;
    }
    else
    {
        //qAppErrors(kLogName) << "No such Reader : " << FLAGS_file_reader_type;
    }

    return false;
}

