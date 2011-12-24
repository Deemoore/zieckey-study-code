#ifndef _COMMAND_HANDLER_H_
#define _COMMAND_HANDLER_H_

#include <string>
#include <vector>


#include "file_id_generator.h"

namespace midtag
{
  class LineProcessor;    
}

class CommandHandler
{
  public:
    CommandHandler();
    ~CommandHandler();

    bool Init();
    bool Work(const std::string& command);
    bool Flush(bool force = false);

  private:

    bool CheckDumpTime();
    bool CheckDumpCount();

    bool Dump();

    std::string GetTempOutputFilePath(int64_t file_id);
    std::string GetOutputFilePath(int64_t file_id);

  private:
    time_t dump_time_interval_;
    size_t dump_count_max_;
    time_t last_update_;

    std::string output_dir_;

    std::string channel_;

    typedef std::vector< std::string > stringvector;
    stringvector dump_vect_;

    midtag::LineProcessor* line_processor_;

    FileIDGenerator file_id_generator_;
};

#endif //_COMMAND_HANDLER_H_

