#ifndef _COMMAND_HANDLER_H_
#define _COMMAND_HANDLER_H_

#include <stdio.h>

#include <string>
#include <vector>

#include "slice.h"

class CommandHandler
{
  public:
    CommandHandler();
    ~CommandHandler();

    bool Init(FILE* fp);

    virtual bool Work(Slice& command) = 0;

    bool Flush(bool force = false);

  protected:
    typedef std::vector< std::string > stringvector;
    stringvector dump_vect_;

  private:
    bool CheckDumpTime();
    bool CheckDumpCount();
    bool Dump();

    std::string GetTempOutputFilePath(int64_t file_id);

  private:
    time_t dump_time_interval_;
    size_t dump_count_max_;
    time_t last_update_;

    FILE* fp_;
};

#endif //_COMMAND_HANDLER_H_

