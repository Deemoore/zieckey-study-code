#ifndef NETPROTO_MESSAGE_UNPACKER_V1_H_
#define NETPROTO_MESSAGE_UNPACKER_V1_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/message.h"

#ifdef H_NPP_SUPPORT_PROTO_V1


namespace npp
{
    namespace v1
    {

        class MessagePacker;
        class _EXPORT_NETPROTO MessageUnpacker : public Message
        {
        public:
            bool Unpack(const void* data, size_t data_len);

            //! Get the unpacked data and size if unpacking successfully
            const uint8_t* Data() const;
            size_t Size() const;

        private:

            //! \brief 
            //! \param const char * digest - A pointer to the digest data
            //! \return bool - 
            bool VerifyOpenSSLRSASign(const char* digest);

            //! \brief 
            //! \param const char * digest - A pointer to the digest data
            //! \return bool - 
            bool VerifySimpleRSASign(const char* digest);

            //! Verify sign
            bool VerifySign(const char* digest, size_t data_len);

            //! Decrypt data
            bool DecryptData(const char* encrypt_data, size_t encrypt_data_len);


        public:
            //! The interface for MessagePacker, don't use it
            const NetHeader& net_header() const { return net_header_; }
            const NppHeaderV1& npp_header() const { return npp_header_; }
            bool IsUnpackedOK() const { return last_error() == kNoError && Data() != NULL;}

        private:
            bool unpack_v1(const void* d, size_t d_len);
        private:
            NetHeader net_header_;  //! The network data header
            NppHeaderV1 npp_header_;  //! The protocol relative header

            std::string unpacked_data_;
        };
    }
}

#endif




#endif // end of #ifdef H_NPP_SUPPORT_PROTO_V1


