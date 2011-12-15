#include "path_reader.h"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <fstream>

#include <boost/lexical_cast.hpp>
#include <gflags/gflags.h>

#include "qlog.h"

#include "constant.h"
#include "file_reader.h"

DEFINE_string(log_prefix, "Inc_", "The prefix of the log file.");

using namespace std;

const string PathReader::pos_prefix_ = "pos.";
const string PathReader::bak_prefix_ = "bak.";

PathReader::PathReader()
{
}

bool PathReader::Init(const string& folder)
{
  bool ret = false;

  folder_ = folder;
  log_prefix_ = FLAGS_log_prefix;
  changed_ = false;
  string file_stamp;
  while (FindPos(file_stamp))
  {
    if (!FileExist(file_stamp))
    {
      qAppError(LOG, "Pos file exist, but data file not exist, remove the pos: %s", GetPosFullpath(file_stamp).c_str());
      int result = remove(GetPosFullpath(file_stamp).c_str());
      if (result != 0)
      {
        int myerr = errno;
        qAppError(LOG, "Failed to remove [%s], errno:%d %s", GetPosFullpath(cur_file_stamp_).c_str(), myerr, strerror(myerr));
      }
      continue;
    }

    size_t pos;
    ifstream infile(GetPosFullpath(file_stamp).c_str());
    infile >> pos;
    infile.close();

    cur_file_stamp_ = file_stamp;
    ret = reader_.Init(GetLogFullpath(cur_file_stamp_), pos);
    qLogInfo(LOG, "Find the pos file of %s", GetPosFullpath(cur_file_stamp_).c_str());
    break;
  }

  vector<string> done_files;
  done_files.clear(); //set a empty vector into it
  if (!ret && FindSmall(file_stamp, done_files))
  {
    cur_file_stamp_ = file_stamp;
    ret = reader_.Init(GetLogFullpath(cur_file_stamp_), 0);
    qLogInfo(LOG, "Find the smallest file of %s", GetLogFullpath(cur_file_stamp_).c_str());
  }

  return ret;
}

bool PathReader::SwitchFile()
{
  bool ret = false;
  if (!last_file_stamp_.empty())
  {
    for (size_t i = 0; i < last_file_stamp_.size(); i++)
    {
      int result;
      qLogInfo(LOG, "Remove file %s", GetPosFullpath(last_file_stamp_[i]).c_str());
      result = remove((GetPosFullpath(last_file_stamp_[i])).c_str());
      //TODO do not remove the pos file, check the pos when record pos file
      if (result != 0)
      {
        int myerr = errno;
        if (myerr != ENOENT)
        {
          qAppError(LOG, "Failed to remove [%s], errno:%d %s", GetPosFullpath(last_file_stamp_[i]).c_str(), myerr, strerror(myerr));
        }
      }

      qLogInfo(LOG, "Rename oldfile [%s] to [%s]", GetLogFullpath(last_file_stamp_[i]).c_str(), GetBakFullpath(last_file_stamp_[i]).c_str());

      result = rename((GetLogFullpath(last_file_stamp_[i])).c_str(), 
          (GetBakFullpath(last_file_stamp_[i])).c_str());
      if (result != 0)
      {
        int myerr = errno;
        qAppError(LOG, "Failed to rename oldfile [%s] to [%s], error:%d %s", GetLogFullpath(last_file_stamp_[i]).c_str(), GetBakFullpath(last_file_stamp_[i]).c_str(), myerr, strerror(myerr));
      }
      ret = true;
    }
    last_file_stamp_.clear();
  }
  return ret;
}

bool PathReader::SwitchFileReader(const std::string& next_file_stamp)
{

  reader_.Deinit();

  last_file_stamp_.push_back(cur_file_stamp_);
  cur_file_stamp_ = next_file_stamp;
  changed_ = true;
  qLogInfo(LOG, "Switch to read file [%s]", GetLogFullpath(cur_file_stamp_).c_str());
  return reader_.Init(GetLogFullpath(cur_file_stamp_), 0);
}

bool PathReader::ReadLine(string& line)
{
  line.clear();
  bool ret = reader_.GetLine(line);
  if (ret == false)
  {
    string tmp_file_stamp;
    vector<string> done_files = last_file_stamp_;
    done_files.push_back(cur_file_stamp_);
    if (FindSmall(tmp_file_stamp, done_files))
    {
      reader_.GetLine(line);

      SwitchFileReader(tmp_file_stamp);

      if (line.empty())
      {
        ret = reader_.GetLine(line);
      }
      else
      {
        ret = true;
      }
    }
    else
    {
      ret = false;
    }
  }
  changed_ = ret ? true : changed_;
  return ret;
}

bool PathReader::RecordPos()
{
  bool ret = false;
  if (!cur_file_stamp_.empty() && changed_)
  {
    string pos_file = GetPosFullpath(cur_file_stamp_);
    int fd = open(pos_file.c_str(), 
        O_WRONLY | O_TRUNC | O_CREAT, 
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd)
    {
      string posStr = boost::lexical_cast<string>(reader_.GetPos());
      write(fd, posStr.c_str(), posStr.length());
      close(fd);
      changed_ = false;
      ret = true;
    }
    else
    {
      qAppError(LOG, "Failed to record the pos file: %s pos: %lu", pos_file.c_str(), reader_.GetPos());
    }
  }
  SwitchFile();
  return ret;
}

bool PathReader::FileExist(const std::string& file_stamp)
{
  bool ret = false;
  DIR* dir = opendir(folder_.c_str());
  if (dir != NULL)
  {
    dirent *dirp;
    
    string tmp;
    while((dirp = readdir(dir)) != NULL) 
    {
      if (strncmp(dirp->d_name, log_prefix_.c_str(), log_prefix_.length()) == 0) 
      {
        tmp.clear();
        tmp.assign(dirp->d_name + log_prefix_.length());
        if (tmp == file_stamp)
        {
          ret = true;
          break;
        }
      }
    }
    closedir(dir);
  }
  return ret;
}

bool PathReader::FindSmall(std::string& file_stamp, const std::vector<std::string>& except)
{
  bool ret = false;
  file_stamp.clear();
  DIR* dir = opendir(folder_.c_str());
  if (dir != NULL)
  {
    dirent *dirp;
    
    string tmp;
    while((dirp = readdir(dir)) != NULL) 
    {
      if (strncmp(dirp->d_name, log_prefix_.c_str(), log_prefix_.length()) == 0) 
      {
        tmp.clear();
        tmp.assign(dirp->d_name + log_prefix_.length());

        if (file_stamp.empty() || file_stamp.compare(tmp) > 0) //means smallest value > tmp value
        {
          bool is_except = false;
          for (size_t i = 0; i < except.size(); i++)
          {
            if (except[i] == tmp)
            {
              is_except = true;
              break;
            }
          }
          if (!is_except)
          {
            file_stamp = tmp;
            ret = true;
          }
        }
      }
    }
    closedir(dir);
  }
  return ret;
}

bool PathReader::FindPos(string& file_stamp)
{
  bool ret = false;
  DIR* dir = opendir(folder_.c_str());
  string prefix = pos_prefix_ + log_prefix_;
  if (dir != NULL)
  {
    dirent *dirp;
    while((dirp = readdir(dir)) != NULL) 
    {
      if (strncmp(dirp->d_name, prefix.c_str(), prefix.length()) == 0) 
      {
        file_stamp.assign(dirp->d_name + prefix.length());
        ret = true;
        break;
      }
    }
    closedir(dir);
  }
  return ret;
}

std::string PathReader::GetPosFullpath(const std::string& file_stamp)
{
  return folder_ + pos_prefix_ + log_prefix_ + file_stamp;
}

std::string PathReader::GetLogFullpath(const std::string& file_stamp)
{
  return folder_ + log_prefix_ + file_stamp;
}

std::string PathReader::GetBakFullpath(const std::string& file_stamp)
{
  return folder_ + bak_prefix_ + log_prefix_ + file_stamp;
}

