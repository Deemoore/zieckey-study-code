#ifndef NETPROTO_V2S_REQUEST_MESSAGE_UNPACKER_H_
#define NETPROTO_V2S_REQUEST_MESSAGE_UNPACKER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/message.h"

#include "netproto/include/v1_message_unpacker.h"
#include "netproto/include/symmetric_encrypt.h"

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

            //Query interface
        public:
            //! The interface for MessagePacker, don't use it
            const Message::NetHeader& net_header() const;

            const Message::NppRequestHeaderV2& npp_request_header_v2() const { return npp_request_header_v2_; }

            bool IsUnpackedOK() const;

            v1::MessageUnpacker* v1_message_unpacker() const { return v1_message_unpacker_; }

            SymmetricEncryptor* symmetric_encryptor() const { return symmetric_encryptor_; }

            bool _AsymmetricDecrypt(const void* digest, size_t len, std::string& decrypted_data);

            //! After calling <code>Unpack</code>
            Message::ProtoVersion GetProtoVersion() const;

        private:

            //! Verify sign
            bool _AsymmetricDecrypt(const char* digest, size_t data_len, std::string& decrypted_data);

            //! Decrypt data
            bool _DecryptAndUncompressData(const char* encrypt_data, size_t encrypt_data_len, const std::string& symmetric_encrypt_key);

            bool _DecryptAndUncompressData(SymmetricEncryptor* e, const char* encrypt_data, size_t encrypt_data_len);

            bool _UnpackV2(const void* d, size_t d_len);

            bool _Uncompress(const void* d, size_t d_len);

            bool _VerifyDigest(const void* digest, size_t digest_len, const void* plain_data, size_t plain_data_size);

        private:
            NetHeader            net_header_;  //! The network data header

            NppRequestHeaderV2   npp_request_header_v2_;

            v1::MessageUnpacker* v1_message_unpacker_;

            std::string unpacked_data_;

            SymmetricEncryptor* symmetric_encryptor_;
        };
    }
}

#endif



