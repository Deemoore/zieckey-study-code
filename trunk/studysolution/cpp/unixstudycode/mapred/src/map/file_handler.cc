#include "file_handler.h"

#include <dirent.h>

#include <boost/lexical_cast.hpp>
#include <gflags/gflags.h>

#include "qlog.h"

#include "constant.h"

using namespace std;

DEFINE_string(log_path, "./", "The root path of the log for handling.");
DEFINE_int32(priority_level, 0, "The max priority level of this file handler.");


FileHandler::FileHandler()
{
}

bool FileHandler::RecordPos()
{
  bool ret = false;
  for (map<string, boost::shared_ptr<PathReader> >::iterator it = reader_map_.begin(); it != reader_map_.end(); it++)
  {
    ret |= it->second->RecordPos();
  }
  if (ret == true)
  {
    cur_path_.clear();
  }
  return ret;
}

bool FileHandler::Init()
{
  path_ = FLAGS_log_path;
  if (path_.at(path_.length() - 1) != '/')
    path_.append("/");

  priority_level_ = FLAGS_priority_level;

  return true;
}

bool FileHandler::GetLine(string& line)
{
  bool ret = false;
  if (priority_level_ > 0)
  {
    if (!cur_path_.empty())
    {
      ret = GetLineByPath(cur_path_, line);
    }

    if (!ret)
    {
      for (int i = 0; i < priority_level_; i++)
      {
        if (true == (ret = GetLineByPriority(i, line)))
        {
          cur_path_ = path_ + boost::lexical_cast<string>(i) + "/";
          break;
        }
      }
    }
  }
  else
  {
    ret = GetLineByPath(path_, line);
  }
  return ret;
}

bool FileHandler::GetLineByPriority(int priority, std::string& line)
{
  string priority_path = path_ + boost::lexical_cast<string>(priority) + "/";
  return GetLineByPath(priority_path, line);
}

bool FileHandler::GetLineByPath(const std::string& folder_path, std::string& line)
{
  if (reader_map_.find(folder_path) == reader_map_.end())
  {
    reader_map_[folder_path] = boost::shared_ptr<PathReader>(new PathReader());
    if (!reader_map_[folder_path]->Init(folder_path))
    {
      reader_map_.erase(folder_path);
//      qLogInfo(LOG, "Failed to init a path reader: %s", folder_path.c_str());
      return false;
    }
  }
  return reader_map_[folder_path]->ReadLine(line);
}
    

