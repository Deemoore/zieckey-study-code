#ifndef _PATH_READER_H_
#define _PATH_READER_H_

#include <string>
#include <vector>
#include "file_reader.h"

class PathReader
{
  public:
    PathReader();
    bool Init(const std::string& folder);
    bool ReadLine(std::string& line);
    bool RecordPos();
  private:
    bool SwitchFileReader(const std::string& next_file_stamp);
    bool SwitchFile();
    bool FindSmall(std::string& file_stamp, const std::vector<std::string>& except);
    bool FindPos(std::string& file_stamp);
    bool FileExist(const std::string& file_stamp);

    std::string GetPosFullpath(const std::string& file_stamp);
    std::string GetLogFullpath(const std::string& file_stamp);
    std::string GetBakFullpath(const std::string& file_stamp);

    std::string folder_;
    std::string log_prefix_;
    static const std::string pos_prefix_;
    static const std::string bak_prefix_;

    FileReader reader_;
    std::string cur_file_stamp_;
    std::vector<std::string> last_file_stamp_;
    bool changed_;
};

#endif //_PATH_READER_H_
