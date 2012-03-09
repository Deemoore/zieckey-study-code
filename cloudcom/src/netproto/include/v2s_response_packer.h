#ifndef NETPROTO_V2S_RESPONSE_MESSAGE_PACKER_H_
#define NETPROTO_V2S_RESPONSE_MESSAGE_PACKER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/message.h"


namespace npp
{
    namespace v2s
    {
        class RequestMessageUnpacker;

        class _EXPORT_NETPROTO ResponseMessagePacker : public Message
        {
        public:
            //! \brief The constructor of MessagePacker
            //! \note When you do a response message packing, 
            //!     please provide parameter <code>message_unpacker</code>
            //! \param MessageUnpacker * message_unpacker - 
            //! \return  - 
            ResponseMessagePacker(RequestMessageUnpacker* message_unpacker);

            //! \brief Pack the data
            //! \param const void * data - The original data
            //! \param size_t data_len - 
            //! \param[out] void * packed_data_buf - The packed data will be stored here
            //! \param[in,out] size_t & packed_data_buf_len - The original size of 
            //!     <code>packed_data_buf</code> and after packing 
            //!     the packed data length will stored here
            //! \return bool - 
            bool Pack(const void* data, size_t data_len, void* packed_data_buf, size_t& packed_data_buf_len);


            //! \brief Get the packed data length
            //! \param size_t data_len - The data to be packed
            //! \return size_t - 
            size_t GetPackedTotalDataSize(size_t data_len);

            RequestMessageUnpacker* GetRequestMessageUnpacker() const { return message_unpacker_; }

            //! Get the message id from the packed data
            static uint16_t GetMessageID(void* packed_data_buf);

        private:

            void _CalcMD5AndWrite( const void* data, size_t data_len, uint8_t* write_pos );

            //! Return the size of encrypted data
            size_t _SymmetricEncryptAndWrite(NppResponseHeaderV2* npp_header, const void* orignal_data, size_t orignal_data_len, uint8_t* write_pos);

        private:
            RequestMessageUnpacker* message_unpacker_;
        };
    }
}

#endif



