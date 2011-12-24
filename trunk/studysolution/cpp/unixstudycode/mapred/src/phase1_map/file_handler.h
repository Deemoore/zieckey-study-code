#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_

#include <stdio.h>

#include "constant.h"

#include "file_reader.h"

class FileHandler
{
public:
    FileHandler() : reader_(NULL) {} 

    ~FileHandler(){ delete reader_; } 

    bool Init(FILE* fp);

    bool GetLine(Slice& line)
    {
        return reader_->GetLine(line);
    }

private:
    FileReader* reader_;
};

#endif // _FILE_HANDLER_H_

