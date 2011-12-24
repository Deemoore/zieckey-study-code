#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include <stdio.h>
#include "slice.h"

class FileReader
{
public:
    FileReader(FILE* fp) 
        : fp_(fp) 
    {
    }

    virtual ~FileReader() 
    { 
        fp_ = NULL; 
    }

    virtual bool GetLine(Slice& line) = 0;

protected:
    FILE* fp_;
};

#endif 


