#ifndef NETPROTO_V2S_REQUEST_MESSAGE_UNPACKER_H_
#define NETPROTO_V2S_REQUEST_MESSAGE_UNPACKER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/message.h"

#include "netproto/include/v1_message_unpacker.h"

namespace npp
{
    namespace v2s
    {
        class _EXPORT_NETPROTO RequestMessageUnpacker : public Message
        {
        public:
            RequestMessageUnpacker();
            ~RequestMessageUnpacker();

            bool Unpack(const void* data, size_t data_len);

            //! Get the unpacked data and size if unpacking successfully
            const uint8_t* Data() const;
            size_t Size() const;

        private:
            //! \brief 
            //! \param const void * digest - The digest
            //! \param size_t digest_len - 
            //! \param const void * d - The source data to be verified
            //! \param size_t d_len - 
            //! \return bool - 
            bool VerifyDigest(const void* digest, size_t digest_len, const void* d, size_t d_len);

            //! \brief 
            //! \param const char * digest - A pointer to the digest data
            //! \return bool - 
            bool VerifyOpenSSLRSASign(const char* digest);

            //! \brief 
            //! \param const char * digest - A pointer to the digest data
            //! \return bool - 
            bool VerifySimpleRSASign(const char* digest);

            //! Verify sign
            bool _AsymmetricDecrypt(const char* digest, size_t data_len, std::string& decrypted_data);

            //! Decrypt data
            bool DecryptData(const char* encrypt_data, size_t encrypt_data_len);



            //Query interface
        public:
            //! The interface for MessagePacker, don't use it
            const NetHeader& net_header() const;

            const NppRequestHeaderV2& npp_request_header_v2() const { return npp_request_header_v2_; }

            bool IsUnpackedOK() const;

            v1::MessageUnpacker* v1_message_unpacker() const { return v1_message_unpacker_; }

        private:
            bool _UnpackV2(const void* d, size_t d_len);

            bool _Uncompress(const void* d, size_t d_len);

        private:
            NetHeader            net_header_;  //! The network data header
            NppRequestHeaderV2   npp_request_header_v2_;

            v1::MessageUnpacker* v1_message_unpacker_;

            std::string unpacked_data_;
        };
    }
}

#endif



