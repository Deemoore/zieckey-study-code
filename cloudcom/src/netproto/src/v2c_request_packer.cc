#ifndef NETPROTO_MESSAGE_PACKER_H_
#define NETPROTO_MESSAGE_PACKER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/v2c_request_packer.h"

#include "netproto/include/npp_config.h"
#include "netproto/include/zlib.h"
#include "netproto/include/compressor.h"
#include "netproto/include/symmetric_encrypt.h"

namespace npp
{
    namespace v2c
    {
        uint16_t RequestMessage::message_id_ = 1;
        RequestMessage::RequestMessage()
            : symmetric_encryptor_(NULL)
            , compressor_(NULL)
        {
            net_header_v2_.Init();
            net_header_v2_.set_message_id(RequestMessage::message_id_++);
        }

        RequestMessage::~RequestMessage()
        {
            SymmetricEncryptorFactory::DesstorySymmetricEncryptor(symmetric_encryptor_);
            symmetric_encryptor_ = NULL;

            CompressorFactory::DesstoryCompressor(compressor_);
            compressor_ = NULL;
        }

        const uint8_t* RequestMessage::Data() const
        {
            if (Size() == 0)
            {
                return NULL;
            }
            else
            {
                return reinterpret_cast<const uint8_t*>(packed_data_.data());
            }
        }

        size_t RequestMessage::Size() const
        {
            return packed_data_.size();
        }

        bool RequestMessage::Pack( const void* data, size_t data_len )
        {
            if (NULL == data)
            {
                last_error(kParameterErrorNULLPointer);
                return false;
            }

            if (0 == data_len)
            {
                last_error(kParameterErrorDataLengthError);
                return false;
            }

            //for the sake of SetAsymmetricEncryptMethod or SetAsymmetricEncryptKeyNo has been called by App layer
            ErrorCode ec = kNoError;
            this->npp_request_header_v2_.set_asymmetric_encrypt_data_len(this->npp_request_header_v2_.GetSignLength(ec));
            if (this->npp_request_header_v2_.asymmetric_encrypt_data_len() == 0)
            {
                last_error(ec);
                return false;
            }

            //---------------------------------------------------------
            //Step 1: NetHeaderV2 and NppRequestHeaderV2
            size_t total_size = GetPackedTotalDataSize(data_len);
            if (0 == total_size)
            {
                return false;
            }
            packed_data_.resize(total_size);

            uint8_t* write_pos = reinterpret_cast<uint8_t*>(&packed_data_[0]);

            NetHeaderV2* net_header = reinterpret_cast<NetHeaderV2*>(write_pos);
            memcpy(net_header, &this->net_header_v2_, sizeof(*net_header));
            write_pos += sizeof(*net_header);

            NppRequestHeaderV2* npp_header = reinterpret_cast<NppRequestHeaderV2*>(write_pos);
            memcpy(npp_header, &this->npp_request_header_v2_, sizeof(*npp_header));
            write_pos += sizeof(*npp_header);

            //---------------------------------------------------------
            //Step 2: write md5
            CalcMD5AndWrite( data, data_len, write_pos );
            write_pos += kMD5HexLen;

            //---------------------------------------------------------
            //Step 3: write symmetric encrypt data
            uint8_t* encrypt_data_begin = write_pos + npp_header->asymmetric_encrypt_data_len();
            size_t encrypt_data_len = SymmetricEncryptAndWrite(npp_header, data, data_len, encrypt_data_begin);
            if (0 == encrypt_data_len)
            {
                //error code has been set by SymmetricEncryptAndWrite
                return false;
            }
            
            net_header->set_data_len(encrypt_data_len + npp_header->asymmetric_encrypt_data_len() + kMD5HexLen + sizeof(*npp_header));

            //---------------------------------------------------------
            //Step 4: write the SymmetricEncryptKey's encrypt data
            size_t sign_len = AsymmetricEncryptAndWrite(write_pos);
            if (0 == sign_len && last_error() != kNoError)
            {
                //error code has been set by AsymmetricEncryptAndWrite
                return false;
            }

            assert((size_t)(net_header->data_len() + net_header->header_len_) <= packed_data_.size());
            packed_data_.resize(net_header->data_len() + net_header->header_len_);

            //---------------------------------------------------------
            //Step 5: end
            assert(last_error() == kNoError);
            assert(memcmp(&this->npp_request_header_v2_, npp_header, sizeof(*npp_header)) == 0);
            net_header->set_data_len(htonl(net_header->data_len()));
            net_header->set_message_id(htons(net_header->message_id()));
            net_header->set_reserve(htons(net_header->reserve()));
            npp_header->set_asymmetric_encrypt_data_len(htons(npp_header->asymmetric_encrypt_data_len()));
            //memcpy(&this->net_header_v2_, net_header, sizeof(*net_header));

            return true;
        }

        size_t RequestMessage::GetPackedTotalDataSize( size_t data_len )
        {
            ErrorCode ec = kNoError;
            size_t ret = sizeof(NetHeaderV2) + sizeof(NppRequestHeaderV2) + kMD5HexLen + npp_request_header_v2_.GetSignLength(ec) + npp_request_header_v2_.GetSymmetricEncryptDataLength(data_len, ec);
            last_error(ec);
            return ret;
        }
// 
//         size_t RequestMessage::GetSignLength()
//         {
//             if (npp_request_header_v2_.asymmetric_encrypt_method() == kSimpleRSA)
//             {
//                 npp::SimpleRSA* rsa = s_pNppConfig->GetSimpleRSA(npp_request_header_v2_.asymmetric_encrypt_key_no());
//                 if (!rsa)
//                 {
//                     last_error(kNotSupportSimpleRSAKeyNumber);
//                     return 0;
//                 }
//                 return rsa->getSignLength();
//             }
// #ifdef H_NPP_PROVIDE_OPENSSL_RSA
//             else if (npp_request_header_v2_.asymmetric_encrypt_method() == kOpenSSLRSA0 || npp_request_header_v2_.asymmetric_encrypt_method() == kOpenSSLRSA2)
//             {
//                 OpenSSLRSA* rsa = s_pNppConfig->GetOpenSSLRSA(npp_request_header_v2_.asymmetric_encrypt_key_no());
//                 if (!rsa)
//                 {
//                     last_error(kNotSupportSimpleRSAKeyNumber);
//                     return 0;
//                 }
//                 return rsa->getSignLength();
//             }
// #endif
//             else
//             {
//                 last_error(kNotSupportSignMethod);
//                 return 0;
//             }
//         }

//         size_t RequestMessage::GetEncryptDataLength( size_t data_len )
//         {
//             size_t compressed_data_len = data_len;
//             if (npp_request_header_v2_.compress_method() == kZlibCompress)
//             {
//                 compressed_data_len = ZLib::GetCompressBound(compressed_data_len);
//             }
//             
//             if (npp_request_header_v2_.symmetric_encrypt_method() == kIDEASymmetricEncrypt)
//             {
//                 return H_ALIGN(compressed_data_len + 8, 8);
//             }
//             else if (npp_request_header_v2_.symmetric_encrypt_method() == kNoSymmetricEncrypt)
//             {
//                 return compressed_data_len;
//             }
//             else
//             {
//                 assert(false);
//                 last_error(kNotSupportSymmetricEncryptMethod);
//                 return 0;
//             }
//         }

        size_t RequestMessage::SymmetricEncryptAndWrite(NppRequestHeaderV2* npp_header, const void* orignal_data, size_t orignal_data_len, uint8_t* write_pos)
        {
            const void*  data_to_be_encrypt = orignal_data;
            size_t data_to_be_encrypt_len = orignal_data_len;

            compressor_ = CompressorFactory::CreateCompressor(npp_header->compress_method());
            std::string compress_data;
            if (compressor_)
            {
                if (!compressor_->Compress(orignal_data, orignal_data_len, compress_data))
                {
                    last_error(kCompressError);
                    return 0;
                }

                data_to_be_encrypt = reinterpret_cast<const void*>(compress_data.data());
                data_to_be_encrypt_len = compress_data.size();
            }
            else
            {
                // We force to set the compressor_ method to <code>kNoComress</code>
                npp_header->set_compress_method(kNoComress);
                this->npp_request_header_v2_.set_compress_method(kNoComress);
            }
            
            symmetric_encryptor_ = SymmetricEncryptorFactory::CreateSymmetricEncryptor(npp_header->symmetric_encrypt_method());
            if (symmetric_encryptor_)
            {
                std::string key = symmetric_encryptor_->CreateRandomKey();
                bool init_ok = symmetric_encryptor_->Initialize(reinterpret_cast<const unsigned char*>(key.data()), key.size());
                assert(init_ok);
                size_t write_len = symmetric_encryptor_->GetEncryptDataLength(data_to_be_encrypt_len);
                if (!symmetric_encryptor_->Encrypt(data_to_be_encrypt, data_to_be_encrypt_len, write_pos, write_len))
                {
                    last_error(kSymmetricEncyptFailed);
                    return 0;
                }

                return write_len;
            }
            else
            {
                memcpy(write_pos, data_to_be_encrypt, data_to_be_encrypt_len);
                return data_to_be_encrypt_len;
            }
        }

        size_t RequestMessage::AsymmetricEncryptAndWrite(uint8_t* write_pos )
        {
            if (!symmetric_encryptor_)
            {
                return 0;
            }

            std::string symmetric_encrypt_key = symmetric_encryptor_->GetEncryptKey();

            AsymmetricEncryptor* encryptor = AsymmetricEncryptorFactory::GetAsymmetricEncryptor(npp_request_header_v2_.asymmetric_encrypt_method(), npp_request_header_v2_.asymmetric_encrypt_key_no());
            if (!encryptor)
            {
                last_error(kNotSupportSignMethod);//or 
                return 0;
            }

            switch (npp_request_header_v2_.asymmetric_pub_priv_method())
            {
            case kAsymmetricPublicEncrypt:
                {
                    size_t len = encryptor->GetEncryptDataLength();
                    if (!encryptor->PublicEncrypt(symmetric_encrypt_key.data(), symmetric_encrypt_key.size(), write_pos, &len))
                    {
                        last_error(kAsymmetricPublicEncryptFailed);
                        return 0;
                    }
                    assert(len == npp_request_header_v2_.asymmetric_encrypt_data_len());
                    return len;
                }
            case kAsymmetricPrivateEncrypt:
                {
                    size_t len = encryptor->GetEncryptDataLength();
                    if (!encryptor->PrivateEncrypt(symmetric_encrypt_key.data(), symmetric_encrypt_key.size(), write_pos, &len))
                    {
                        last_error(kAsymmetricPrivateEncryptFailed);
                        return 0;
                    }
                    assert(len == npp_request_header_v2_.asymmetric_encrypt_data_len());
                    return len;
                }
            default:
                last_error(kNotSupportAsymmetricPublicPrivateMethod);
                return 0;
            }
        }
    }
}

#endif


