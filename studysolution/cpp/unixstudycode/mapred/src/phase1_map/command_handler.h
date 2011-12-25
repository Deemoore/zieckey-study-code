#ifndef _COMMAND_HANDLER_H_
#define _COMMAND_HANDLER_H_

#include <stdio.h>

#include <string>
#include <vector>

#include "qoslib/include/QOSLibAllExp.h"

#include "file_writer.h"

class CommandHandler
{
  public:
    CommandHandler();
    ~CommandHandler();

    bool Init(FILE* fp);

    virtual bool Work(osl::Slice& command) = 0;

    bool Flush(bool force = false);

  protected:

    void AddOutput(const void* data, size_t len)
    {
        writer_->Write(data, len);
    }


  private:

    FileWriter* writer_;
};

#endif //_COMMAND_HANDLER_H_

