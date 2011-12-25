#ifndef _COMMAND_HANDLER_H_
#define _COMMAND_HANDLER_H_

#include <stdio.h>

#include <string>
#include <vector>
#include <gflags/gflags.h>
#include "qoslib/include/QOSLibAllExp.h"
#include "qoslib/include/QFileUtil.h"
#include "qoslib/include/QTimer.h"
#include "qoslib/include/QMD5.h"
#include "qoslib/include/QDataStream.h"

DECLARE_int32(dump_buffer);

class CommandHandler
{
  public:
    CommandHandler();
    ~CommandHandler();

    bool Init(FILE* fp);

    virtual bool Work(osl::Slice& command) = 0;

    bool Flush(bool force = false);

  protected:

    void AddOutput(const void* data, size_t len)
    {
        if (output_buf_.getSize() + len + 256 >= dump_buffer_max_)
        {
            Dump();
        }
        output_buf_.write(data, len);
    }

  private:
    bool CheckDumpTime();
    bool CheckDumpCount();
    bool Dump();

    std::string GetTempOutputFilePath(int64_t file_id);

  private:
    time_t dump_time_interval_;
    time_t last_update_;

    size_t dump_buffer_max_;

    FILE* fp_;

    osl::MemoryDataStream output_buf_;
};

#endif //_COMMAND_HANDLER_H_

