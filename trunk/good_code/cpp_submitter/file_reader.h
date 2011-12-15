#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include <string>

class FileReader
{
public:
  FileReader();
  bool Init(const std::string& path, size_t pos = 0);

  size_t GetPos() const;
  bool SetPos(size_t pos);
  
  bool GetLine(std::string& str);

  void Deinit();
  
  ~FileReader();

private:
  std::string path_;
  FILE* pfile;
  size_t file_pos_;
  bool file_eof;
  bool file_error;

  size_t log_size;

  static const size_t BUFFER_SIZE = 8 * 1024 * 1024;
  static const size_t BUFFER_THRESHOLD = 7 * 1024 * 1024 + 512 * 1024;
  char* buf;
  size_t buf_pos;
  size_t buf_size;

  bool Init();

  void moveBuffer();
  void readLineFromBuffer();
  bool loadFile();
};

#endif
