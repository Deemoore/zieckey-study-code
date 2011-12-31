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
#include "thread_writer.h"

DEFINE_string(file_writer_type, "BufferWriter", "The actually output writer type, options : BufferWriter, ThreadWriter");

CommandHandler::CommandHandler()
    : writer_(NULL)
{
}

CommandHandler::~CommandHandler()
{
    if (writer_)
    {
        delete writer_;
        writer_ = NULL;
    }
}

bool CommandHandler::Init(FILE* fp)
{
    if (FLAGS_file_writer_type == "BufferWriter")
    {
        writer_ = new BufferWriter(fp);
        return writer_->Init();
    }
    else if (FLAGS_file_writer_type == "ThreadWriter")
    {
        writer_ = new ThreadWriter(fp);
        return writer_->Init();
    }
    else
    {
        fprintf(stderr, "Not supported writer! %s\n", FLAGS_file_writer_type.c_str());
        return false;
    }

}

bool CommandHandler::Flush(bool force)
{
    if (force)
    {
        writer_->Flush();
    }
    
    return true;
}


