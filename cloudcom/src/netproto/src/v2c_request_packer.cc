#ifndef NETPROTO_MESSAGE_PACKER_H_
#define NETPROTO_MESSAGE_PACKER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/v2c_request_packer.h"
#include "slrsa/md5.h"
#include "netproto/include/npp_config.h"
#include "netproto/include/zlib.h"
#include "netproto/include/compressor.h"
#include "netproto/include/symmetric_encrypt.h"

namespace npp
{
    namespace v2c
    {
        uint16_t RequestMessage::message_id_ = 0;
        RequestMessage::RequestMessage()
            : symmetric_encryptor_(NULL)
            , compressor_(NULL)
        {
            net_header_.InitV2();
            net_header_.set_message_id(RequestMessage::message_id_++);
        }

        RequestMessage::~RequestMessage()
        {
            SymmetricEncryptorFactory::DesstorySymmetricEncryptor(symmetric_encryptor_);
            symmetric_encryptor_ = NULL;
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
            ErrorCode ec;
            this->npp_request_header_.set_asymmetric_encrypt_data_len(this->npp_request_header_.GetSignLength(ec));
            if (this->npp_request_header_.asymmetric_encrypt_data_len() == 0)
            {
                last_error(ec);
                return false;
            }
            

            //---------------------------------------------------------
            //Step 1: NetHeader and NppRequestHeaderV2
            packed_data_.resize(GetPackedTotalDataSize(data_len));

            uint8_t* write_pos = reinterpret_cast<uint8_t*>(&packed_data_[0]);

            NetHeader* net_header = reinterpret_cast<NetHeader*>(write_pos);
            memcpy(net_header, &this->net_header_, sizeof(*net_header));
            write_pos += sizeof(*net_header);

            NppRequestHeaderV2* npp_header = reinterpret_cast<NppRequestHeaderV2*>(write_pos);
            memcpy(npp_header, &this->npp_request_header_, sizeof(*npp_header));
            write_pos += sizeof(*npp_header);

            //---------------------------------------------------------
            //Step 2: write md5
            CalcMD5AndWrite( data, data_len, write_pos );
            write_pos += kMD5HexLen;

            //---------------------------------------------------------
            //Step 3: write symmetric encrypt data
            assert(npp_header->asymmetric_encrypt_data_len() == GetSignLength());
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
            std::string symmetric_encrypt_key = symmetric_encryptor_->GetEncryptKey();
            size_t sign_len = AsymmetricEncryptAndWrite(symmetric_encrypt_key.data(), symmetric_encrypt_key.size(), write_pos);
            if (0 == sign_len)
            {
                //error code has been set by AsymmetricEncryptAndWrite
                return false;
            }
            

            assert(net_header->data_len() + net_header->header_len_ <= packed_data_.size());
            packed_data_.resize(net_header->data_len() + net_header->header_len_);

            //---------------------------------------------------------
            //Step 5: end
            assert(last_error() == kNoError);
            assert(memcmp(&this->npp_request_header_, npp_header, sizeof(*npp_header)) == 0);
            net_header->set_data_len(htons(net_header->data_len()));
            net_header->set_message_id(htons(net_header->message_id()));
            net_header->set_reserve(htons(net_header->reserve()));
            npp_header->set_asymmetric_encrypt_data_len(htons(npp_header->asymmetric_encrypt_data_len()));
            memcpy(&this->net_header_, net_header, sizeof(*net_header));

            return true;
        }

        size_t RequestMessage::GetPackedTotalDataSize( size_t data_len )
        {
            ErrorCode ec;
            size_t ret = sizeof(NetHeader) + sizeof(NppRequestHeaderV2) + kMD5HexLen + npp_request_header_.GetSignLength(ec) + npp_request_header_.GetSymmetricEncryptDataLength(data_len, ec);
            last_error(ec);
            return ret;
        }
// 
//         size_t RequestMessage::GetSignLength()
//         {
//             if (npp_request_header_.asymmetric_encrypt_method() == kSimpleRSA)
//             {
//                 npp::SimpleRSA* rsa = s_pNppConfig->GetSimpleRSA(npp_request_header_.asymmetric_encrypt_key_no());
//                 if (!rsa)
//                 {
//                     last_error(kNotSupportSimpleRSAKeyNumber);
//                     return 0;
//                 }
//                 return rsa->getSignLength();
//             }
// #ifdef H_NPP_PROVIDE_OPENSSL_RSA
//             else if (npp_request_header_.asymmetric_encrypt_method() == kOpenSSLRSA0 || npp_request_header_.asymmetric_encrypt_method() == kOpenSSLRSA2)
//             {
//                 OpenSSLRSA* rsa = s_pNppConfig->GetOpenSSLRSA(npp_request_header_.asymmetric_encrypt_key_no());
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
//             if (npp_request_header_.compress_method() == kZlibCompress)
//             {
//                 compressed_data_len = ZLib::GetCompressBound(compressed_data_len);
//             }
//             
//             if (npp_request_header_.symmetric_encrypt_method() == kIDEASymmetricEncrypt)
//             {
//                 return H_ALIGN(compressed_data_len + 8, 8);
//             }
//             else if (npp_request_header_.symmetric_encrypt_method() == kNoSymmetricEncrypt)
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

        void RequestMessage::CalcMD5AndWrite( const void* data, size_t data_len, uint8_t* write_pos )
        {
            MD5_CTX ctx;
            MD5Init(&ctx);
            MD5Update(&ctx, (unsigned char*)data, (unsigned int)data_len);
            MD5Final((unsigned char*)write_pos, &ctx);
        }

        size_t RequestMessage::SymmetricEncryptAndWrite(NppRequestHeaderV2* npp_header, const void* orignal_data, size_t orignal_data_len, uint8_t* write_pos)
        {
            const void*  data_to_be_encrypt = orignal_data;
            size_t data_to_be_encrypt_len = orignal_data_len;

            compressor_ = CompressorFactory::CreateCompressor(npp_header->compress_method());
            npp::ext::auto_delete< npp::Compressor > compress_auto_delete(compressor_);
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
                this->npp_request_header_.set_compress_method(kNoComress);
            }
            
            symmetric_encryptor_ = SymmetricEncryptorFactory::CreateSymmetricEncryptor(npp_header->symmetric_encrypt_method());
            std::string key = symmetric_encryptor_->CreateRandomKey();
            bool init_ok = symmetric_encryptor_->Initialize(reinterpret_cast<const unsigned char*>(key.data()), key.size());
            assert(init_ok);
            if (symmetric_encryptor_)
            {
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

        size_t RequestMessage::AsymmetricEncryptAndWrite( const void* orignal_data, size_t orignal_data_len, uint8_t* write_pos )
        {
            AsymmetricEncryptor* encryptor = AsymmetricEncryptorFactory::GetAsymmetricEncryptor(npp_request_header_.asymmetric_encrypt_method(), npp_request_header_.asymmetric_encrypt_key_no());
            if (!encryptor)
            {
                last_error(kNotSupportSignMethod);//or 
                return 0;
            }
            switch (npp_request_header_.asymmetric_pub_priv_method())
            {
            case kAsymmetricPublicEncrypt:
                {
                    size_t len = encryptor->GetEncryptDataLength();
                    if (!encryptor->PublicEncrypt(orignal_data, orignal_data_len, write_pos, &len))
                    {
                        last_error(kAsymmetricPublicEncryptFailed);
                        return 0;
                    }
                    assert(len == GetSignLength());
                    return len;
                }
            case kAsymmetricPrivateEncrypt:
                {
                    size_t len = encryptor->GetEncryptDataLength();
                    if (!encryptor->PrivateEncrypt(orignal_data, orignal_data_len, write_pos, &len))
                    {
                        last_error(kAsymmetricPrivateEncryptFailed);
                        return 0;
                    }
                    assert(len == GetSignLength());
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



