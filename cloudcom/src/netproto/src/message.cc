#include "netproto/include/message.h"

#include "netproto/include/npp_config.h"

#include <arpa/inet.h>

namespace npp
{

    Message::Message()
    {

    }


    bool Message::Unpack( const void* data, size_t data_len )
    {
        if (!data || 
            data_len <= sizeof(net_header_) + sizeof(npp_header_))
        {
            return false;
        }

        uint8_t header_len = ((const char*)data)[0];
        assert(header_len > sizeof(net_header_));
        memcpy(&net_header_, data, sizeof(net_header_)); // for the sake of NetHeader's changes

        net_header_.data_len    = ntohs(net_header_.data_len);
        net_header_.message_id  = ntohs(net_header_.message_id);
        net_header_.preserve    = ntohs(net_header_.preserve);




        return true;
    }
}



