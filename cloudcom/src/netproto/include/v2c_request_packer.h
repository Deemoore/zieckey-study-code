#ifndef NETPROTO_MESSAGE_PACKER_H_
#define NETPROTO_MESSAGE_PACKER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/message.h"


namespace npp
{
    namespace v2c
    {
        class _EXPORT_NETPROTO RequestMessage : public Message
        {
        public:
            //! \brief The constructor of MessagePacker
            //! \note When you do a response message packing, 
            //!     please provide parameter <code>message_unpacker</code>
            //! \param MessageUnpacker * message_unpacker - 
            //! \return  - 
            RequestMessage();

            //! \brief Pack the data
            //! \param const void * data - The original data
            //! \param size_t data_len - 
            //! \param[out] void * packed_data_buf - The packed data will be stored here
            //! \param[in,out] size_t & packed_data_buf_len - The original size of 
            //!     <code>packed_data_buf</code> and after packing 
            //!     the packed data length will stored here
            //! \return bool - 
            bool Pack(const void* data, size_t data_len, void* packed_data_buf);

            //! Get the message id from the packed data
            uint16_t GetMessageID();

        private:
            //! \brief Get the packed data length
            //! \param size_t data_len - The data to be packed
            //! \return size_t - 
            size_t GetPackedTotalDataSize(const NppHeaderV1& npp_header, size_t data_len);

            //! Get the sign length
            size_t GetSignLength(const NppHeaderV1& npp_header);

            bool pack_v1(const void* data, size_t data_len, void* packed_data_buf, size_t& packed_data_buf_len);

        private:
            NppRequestHeaderV2 request_header_;
            NetHeader          net_header_;

            std::string        packed_data_;
        private:
            static uint16_t message_id_;
        };
    }
}

#endif



