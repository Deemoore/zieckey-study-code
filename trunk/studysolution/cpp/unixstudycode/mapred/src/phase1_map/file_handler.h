#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_

#include <stdio.h>

#include "constant.h"

#include "file_reader.h"

#include "qoslib/include/QOSLibAllExp.h" 

class FileHandler
{
public:
    FileHandler() : reader_(NULL){} 

    ~FileHandler(){ delete reader_; reader_ = NULL; } 

    bool Init(FILE* fp);

    bool GetLine(osl::Slice& line)
    {
        return reader_->GetLine(line);
    }

    osl::MemoryDataStreamPtr Read();

private:
    FileReader* reader_;
};

#endif // _FILE_HANDLER_H_

