
#include "netproto/include/inner_pre.h"
#include "netproto/include/v2c_response_unpacker.h"
#include "netproto/include/v2c_request_packer.h"

namespace npp
{
    namespace v2c
    {
        const uint8_t* ResponseUnpacker::Data() const
        {
            if (Size() == 0)
            {
                return NULL;
            }
            else
            {
                return reinterpret_cast<const uint8_t*>(unpacked_data_.data());
            }
        }

        size_t ResponseUnpacker::Size() const
        {
            return unpacked_data_.size();
        }

        ResponseUnpacker::ResponseUnpacker( RequestMessage* request_message )
            : request_message_(request_message)
        {
        }

        bool ResponseUnpacker::Unpack( const void* d, size_t d_len )
        {
            //---------------------------------------------------------
            //Step 1: NetHeader
            if (d_len < sizeof(net_header_) + sizeof(npp_response_header_v2_) + kMD5HexLen)
            {
                last_error(kParameterErrorDataLengthError);
                return false;
            }

            const char* read_pos = ((const char*)d);

            uint8_t header_len = read_pos[0];
            assert(header_len >= sizeof(net_header_));
            memcpy(&net_header_, read_pos, sizeof(net_header_)); // for the sake of NetHeader's changes
            net_header_.data_len_   = ntohs(net_header_.data_len_);
            net_header_.message_id_ = ntohs(net_header_.message_id_);
            net_header_.reserve_    = ntohs(net_header_.reserve_);


            assert(request_message_);
            assert(net_header_.message_id() == request_message_->GetMessageID());

            if (net_header_.data_len_ != d_len - header_len)
            {
                last_error(kNppHeaderDataLengthError);
                return false;
            }

            read_pos += header_len;

            //---------------------------------------------------------
            //Step 2: NppRequestHeaderV2 
            memcpy(&npp_response_header_v2_, read_pos, sizeof(npp_response_header_v2_));
            read_pos += sizeof(npp_response_header_v2_);
            assert(read_pos == ((const char*)d) + header_len + sizeof(npp_response_header_v2_));

            if (npp_response_header_v2_.error_code() != kRequestSuccess)
            {
                return true;
            }
            

            return true;
        }
    }
}




