#include "netproto/include/message.h"

#include "netproto/include/npp_config.h"

#include "netproto/include/md5.h"

#ifndef H_OS_WINDOWS
#include <arpa/inet.h>
#endif

namespace npp
{
    Message::Message()
        : last_error_(kNoError)
    {
    }

    Message::~Message()
    {

    }

    const char* Message::Data()
    {
        if (Size() == 0)
        {
            return NULL;
        }
        else
        {
            return data();
        }
    }

    size_t Message::Size()
    {
        return size();
    }

    const char* Message::strerror() const
    {
        //TODO
        return "";
    }
}



