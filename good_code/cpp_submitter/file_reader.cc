#include "file_reader.h"
#include <unistd.h>
#include <stdio.h>
#include <boost/algorithm/string.hpp>

using namespace std;

FileReader::FileReader()
      : pfile(NULL), file_eof(false), file_error(false),
        log_size(0), buf_pos(0), buf_size(0)
{
  buf = new char[BUFFER_SIZE];
}

bool FileReader::Init(const string& path, size_t pos)
{
  path_ = path;
  file_pos_ = pos;
  return Init();
}

bool FileReader::Init()
{
  if (access(path_.c_str(), R_OK | F_OK) == 0)
  {
    pfile = fopen(path_.c_str(), "r");
  }

  if (pfile == NULL)
  {
    return false;
  }
  else
  {
    file_eof = false;
    file_error = false;
    if (0 != fseek(pfile, file_pos_, SEEK_SET))
    {
      return false;
    }
  }
  return true;
}

void FileReader::Deinit()
{
  if (pfile)
  {
    fclose(pfile);
    pfile = NULL;
  }
}

FileReader::~FileReader()
{
  Deinit();
  if (buf)
  {
    delete buf;
    buf = NULL;
  }
}

size_t FileReader::GetPos() const
{
  return file_pos_;
}

bool FileReader::SetPos(size_t pos)
{
  file_pos_ = pos;
  bool ret = true;
  if (pfile != NULL && fseek(pfile, file_pos_, SEEK_SET) != 0)
  {
    file_pos_ = 0;
    ret = false;
  }
  return ret;
}

bool FileReader::GetLine(std::string& str)
{
  while(1)
  {
    if (pfile == NULL)
    {
      if (Init() == false)
      {
        Deinit();
        file_eof = true;
        file_error = true;
        return false;
      }
    }

    readLineFromBuffer();
    if (log_size == 0)
    {
      loadFile();
    }
    else
    {
      str.assign(buf + buf_pos, log_size);
      boost::algorithm::trim_if(str, boost::algorithm::is_any_of(" \n\r\0"));
      return true;
    }

    readLineFromBuffer();

    if (log_size == 0)
    {
      str.assign(buf + buf_pos, buf_size);
      boost::algorithm::trim_if(str, boost::algorithm::is_any_of(" \n\r\0"));
      return false;
    }
    else
    {
      str.assign(buf + buf_pos, log_size);
      boost::algorithm::trim_if(str, boost::algorithm::is_any_of(" \n\r\0"));
      return true;
    }
  }
}

void FileReader::moveBuffer()
{
  if (buf_pos < BUFFER_SIZE / 2)
    return;
  memmove(buf, buf + buf_pos, buf_size);
  buf_pos = 0;
}

void FileReader::readLineFromBuffer()
{
  buf_pos += log_size;
  char* endpos = (char*)memchr(buf + buf_pos, '\n', buf_size);
  if (endpos == NULL)
    log_size = 0;
  else
    log_size = endpos - buf - buf_pos + 1;
  buf_size -= log_size;
  file_pos_ += log_size;
}

bool FileReader::loadFile()
{
  if (pfile == NULL)
    return false;
  if (buf_pos > BUFFER_THRESHOLD)
    moveBuffer();
  if (buf_pos + buf_size >= BUFFER_SIZE)
    return true;

  size_t rsize;
  rsize = fread(buf + buf_pos + buf_size, 1, BUFFER_SIZE - buf_pos - buf_size, pfile);
  buf_size += rsize;
  file_eof = (feof(pfile) != 0);
  file_error = (ferror(pfile) != 0);
  clearerr(pfile);
/*
  if (!file_error)
  {
    file_pos_ = ftell(pfile);
  }*/
  return true;
}
