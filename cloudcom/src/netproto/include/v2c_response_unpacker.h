#ifndef NETPROTO_MESSAGE_PACKER_H_
#define NETPROTO_MESSAGE_PACKER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/message.h"


namespace npp
{
    namespace v2c
    {

        class MessageUnpacker;

        class _EXPORT_NETPROTO MessagePacker : public Message
        {
        public:
            //! \brief The constructor of MessagePacker
            //! \note When you do a response message packing, 
            //!     please provide parameter <code>message_unpacker</code>
            //! \param MessageUnpacker * message_unpacker - 
            //! \return  - 
            MessagePacker(MessageUnpacker* message_unpacker = NULL);

            //MessagePacker(NppHeaderV1&, NetHeader&); //TODO add this constructor

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

            MessageUnpacker* GetMessageUnpacker() const { return message_unpacker_; }

            //! Get the message id from the packed data
            static uint16_t GetMessageID(void* packed_data_buf);

        private:
            //! \brief Get the packed data length
            //! \param size_t data_len - The data to be packed
            //! \return size_t - 
            size_t GetPackedTotalDataSize(const NppHeaderV1& npp_header, size_t data_len);

            //! Get the sign length
            size_t GetSignLength(const NppHeaderV1& npp_header);

            bool pack_v1(const void* data, size_t data_len, void* packed_data_buf, size_t& packed_data_buf_len);

#ifdef _NETPROTO_TEST
        public:
#endif
            //! We decide which sign to use 
            //! 1->2 2->1
            //! 3->4 4->3
            //! 5->6 6->5
            void ReverseSignKeyNum(NppHeaderV1& npp_header);

        private:
            //! Give a random IDEA key to npp_header
            //! Give a random Sign key to npp_header
            //! Give a random Sign Method to npp_header
            void RandomNppHeader(NppHeaderV1& npp_header);

        private:
            MessageUnpacker* message_unpacker_;

            static uint16_t message_id_;
        };
    }
}

#endif



