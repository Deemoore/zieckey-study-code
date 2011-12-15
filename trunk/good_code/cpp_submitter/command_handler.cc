#include "command_handler.h"

#include <fstream>
#include <sys/stat.h>

#include "constant.h"
#include "qlog.h"

#include <gflags/gflags.h>

DEFINE_int32(dump_time, 30, "The max interval between twice dump, measured by second.");
DEFINE_int32(dump_count, 10000, "The max count of log in one message");

DEFINE_string(memcached_sock, "", "The memcached domain socket");
DEFINE_string(memcached_host, "localhost", "The memcached server hostname");
DEFINE_string(memcached_port, "10001", "The memcached servert listening port");

DEFINE_string(output_dir, "../data/output", "The output data dir");

CommandHandler::CommandHandler()
  : dump_time_interval_(0), dump_count_max_(0), last_update_(time(0))
{
}

bool CommandHandler::Init()
{
  dump_time_interval_ = FLAGS_dump_time;
  dump_count_max_ = FLAGS_dump_count;

  dump_vect_.reserve(dump_count_max_);

  return true;
}

CommandHandler::~CommandHandler()
{
}

bool CommandHandler::Work(const std::string& command)
{
  qLogDebugs(kLogName) 
    << "Processing command: " << command;

  /*
  std::string output;
  if (line_processor_->ProcessLine(command, output))
  {
      dump_vect_.push_back(output);

    return true;
  }*/

  return false;
}


bool CommandHandler::Flush(bool force)
{
  bool ret = false;
  if (CheckDumpCount()
      || CheckDumpTime()
      || force)
  {
      /*
    if (dump_vect_.size() > 0)
    {
      if (!Dump())
      {
        return false;  
      }

      dump_vect_.clear();
      dump_vect_.reserve(dump_count_max_);
    }
    else
    {
      qLogInfos(kLogName) << "No data to dump.";
    }*/



      dump_vect_.clear();
    
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
  return dump_vect_.size() >= dump_count_max_; 
}

