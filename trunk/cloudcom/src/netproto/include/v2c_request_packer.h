#ifndef NETPROTO_V2C_REQUEST_MESSAGE_PACKER_H_
#define NETPROTO_V2C_REQUEST_MESSAGE_PACKER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/message.h"


namespace npp
{
    class Compressor;
    class SymmetricEncryptor;

    namespace v2c
    {
        class _EXPORT_NETPROTO RequestMessage : public Message
        {
        public:
            //! \brief The constructor
            RequestMessage();
            ~RequestMessage();

            //! \brief Pack the data
            //! \param const void * data - The original data
            //! \param size_t data_len - 
            //! \return bool - 
            bool Pack(const void* data, size_t data_len);

            //! Get the message id from the packed data
            uint16_t GetMessageID() { return net_header_.message_id(); }

            //! Get the packed data and size if packing successfully
            const uint8_t* Data() const;
            size_t Size() const;

            //Behavior setting
        public:
            void SetSymmetricEncryptMethod(SymmetricEncryptMethod method) {npp_request_header_v2_.set_symmetric_encrypt_method(method);}

            void SetAsymmetricEncryptMethod(AsymmetricEncryptMethod method) {npp_request_header_v2_.set_asymmetric_encrypt_method(method);}

            void SetAsymmetricEncryptKeyNo(uint8_t key_no) {npp_request_header_v2_.set_asymmetric_encrypt_key_no(key_no);}

            void SetAsymmetricPublicPrivateMethod(AsymmetricPublicPrivateMethod method) { npp_request_header_v2_.set_asymmetric_pub_priv_method(method);}

            void SetCompressMethod(CompressMethod method) {npp_request_header_v2_.set_compress_method(method);}

        private:
            //! \brief Get the packed data length
            //! \param size_t data_len - The data to be packed
            //! \return size_t - 
            size_t GetPackedTotalDataSize(size_t data_len);

//             //! Get the asymmetric encrypt sign length
//             size_t GetSignLength();
// 
//             size_t GetEncryptDataLength(size_t data_len);

            //! Return the written data length
            size_t SymmetricEncryptAndWrite(NppRequestHeaderV2* npp_header, const void* orignal_data, size_t orignal_data_len, uint8_t* write_pos);

            //! Return the written data length
            size_t AsymmetricEncryptAndWrite(uint8_t* write_pos);


            SymmetricEncryptor* symmetric_encryptor() const { return symmetric_encryptor_; }
            Compressor* compressor() const { return compressor_; }
            const NppRequestHeaderV2& npp_request_header_v2() const { return npp_request_header_v2_; }

        private:
            friend class ResponseUnpacker;

            NppRequestHeaderV2  npp_request_header_v2_;
            NetHeader           net_header_;

            std::string         packed_data_;

            SymmetricEncryptor* symmetric_encryptor_;

            Compressor*         compressor_;
        private:
            static uint16_t message_id_;
        };
    }
}

#endif //



