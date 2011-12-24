#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "constant.h"
#include "path_reader.h"

class FileHandler
{
  public:
    FileHandler();
    bool Init();
    bool GetLine(std::string& line);
    bool RecordPos();
    bool GetLineByPath(const std::string& path, std::string& line);
    bool GetLineByPriority(int priority, std::string& line);

  private:
    std::string path_;
    int priority_level_;

    std::map<std::string, boost::shared_ptr<PathReader> > reader_map_;
    std::string cur_path_;
};

#endif // _FILE_HANDLER_H_
