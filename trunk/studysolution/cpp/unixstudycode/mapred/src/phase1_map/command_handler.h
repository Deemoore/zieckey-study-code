#ifndef _COMMAND_HANDLER_H_
#define _COMMAND_HANDLER_H_

#include <stdio.h>

#include <string>
#include <vector>

#include "qoslib/include/QOSLibAllExp.h"

#include "file_writer.h"
#include "buffer_writer.h"


class CommandHandler
{
  public:
    typedef std::set<std::string> stringset;
    typedef std::map<std::string, stringset> string_stringset_map;
    typedef std::map<std::string, osl::u32> stringu32map;
  public:
    CommandHandler();
    virtual ~CommandHandler();

    bool Init(FILE* fp);

    virtual bool Work(osl::Slice& command) = 0;

    virtual void LastSerialize() = 0;

    bool WorkBuffer(osl::MemoryDataStreamPtr& buf);

    bool Flush();

  protected:

    void AddOutput(const void* data, size_t len)
    {
        writer_->Write(data, len);
    }

  private:

    BufferWriter* writer_;

    class ThreadHandler;
    ThreadHandler* thread_handler_;
};

#endif //_COMMAND_HANDLER_H_

