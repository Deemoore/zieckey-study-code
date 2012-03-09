#ifndef NETPROTO_V2C_RESPONSE_MESSAGE_UNPACKER_H_
#define NETPROTO_V2C_RESPONSE_MESSAGE_UNPACKER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/message.h"

namespace npp
{
    namespace v2c
    {

        class RequestMessage;

        class _EXPORT_NETPROTO ResponseUnpacker : public Message
        {
        public:
            //! \brief The constructor of ResponseUnpacker
            //! \note When you do a response message packing, 
            //!     please provide parameter <code>request_message</code>
            //! \param RequestMessage * request_message - 
            //! \return  - 
            ResponseUnpacker(RequestMessage* request_message);

            //! \brief Pack the data
            //! \param const void * data - The original data
            //! \param size_t data_len - 
            //! \param[out] void * packed_data_buf - The packed data will be stored here
            //! \param[in,out] size_t & packed_data_buf_len - The original size of 
            //!     <code>packed_data_buf</code> and after packing 
            //!     the packed data length will stored here
            //! \return bool - 
            bool Unpack(const void* data, size_t data_len);

            //! Get the unpacked data and size if unpacking successfully
            const uint8_t* Data() const;
            size_t Size() const;

            //! Get the message ID from the data
            //! The data length MUST be larger than sizeof(NetHeader)
            static uint16_t GetMessageID(const void* data) 
            {
                const NetHeader* h = reinterpret_cast<const NetHeader*>(data);
                return ntohs(h->message_id());
            }

        private:
            RequestMessage*     request_message_;

            NetHeader           net_header_;
            NppResponseHeaderV2 npp_response_header_v2_;

            std::string unpacked_data_;
        };
    }
}

#endif



