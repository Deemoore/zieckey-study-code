#include "command_handler.h"

#include <fstream>

#include "qoslib/include/QOSLibAllExp.h"
#include "qoslib/include/QFileUtil.h"
#include "qoslib/include/QTimer.h"
#include "qoslib/include/QMD5.h"

#include "constant.h"
#include "qlog.h"

#include <gflags/gflags.h>

#include "buffer_writer.h"

DEFINE_int32(dump_time, 30, "The max interval between twice dump, measured by second.");
DEFINE_string(file_writer_type, "BufferWriter", "The actually output writer type, options : BufferWriter, ThreadWriter");

CommandHandler::CommandHandler()
    : dump_time_interval_(0), last_update_(time(0)), writer_(NULL)
{
}

CommandHandler::~CommandHandler()
{
}

bool CommandHandler::Init(FILE* fp)
{
    dump_time_interval_ = FLAGS_dump_time;

    if (FLAGS_file_writer_type == "BufferWriter")
    {
        writer_ = new BufferWriter(fp);
    }
    else
    {
        return false;
    }

    return writer_->Init();
}

bool CommandHandler::Flush(bool force)
{
    bool ret = false;
    if (CheckDumpCount()
                || CheckDumpTime()
                || force)
    {
        if (!writer_->Flush())
        {
            return false;  
        }

        last_update_ = time(0);
        ret = true;
    }
    return ret;
}

bool CommandHandler::CheckDumpTime()
{
    return last_update_ + dump_time_interval_ < time(0);
}

bool CommandHandler::CheckDumpCount()
{
    return false; 
}


