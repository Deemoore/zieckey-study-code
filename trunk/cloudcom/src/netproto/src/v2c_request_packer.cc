#ifndef NETPROTO_MESSAGE_PACKER_H_
#define NETPROTO_MESSAGE_PACKER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/v2c_request_packer.h"
#include "slrsa/md5.h"
#include "netproto/include/npp_config.h"
#include "netproto/include/zlib.h"

namespace npp
{
    namespace v2c
    {
        uint16_t RequestMessage::message_id_ = 0;
        RequestMessage::RequestMessage()
            : symmetric_encryptor_(NULL)
        {
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

            //---------------------------------------------------------
            //Step 3: write symmetric encrypt data
            write_pos += kMD5HexLen + GetSignLength();
            assert(npp_header->digest_sign_len() == kMD5HexLen + GetSignLength());
            size_t encrypt_data_len = SymmetricEncryptAndWrite(npp_header, data, data_len, write_pos);
            if (0 == encrypt_data_len)
            {
                //error code has been set by SymmetricEncryptAndWrite
                return false;
            }
            

            //---------------------------------------------------------
            //Step 4: write the SymmetricEncryptKey's encrypt data
            size_t sign_len = AsymmetricEncryptAndWrite(write_pos, encrypt_data_len, write_pos - GetSignLength());
            if (0 == sign_len)
            {
                //error code has been set by AsymmetricEncryptAndWrite
                return false;
            }
            
            //---------------------------------------------------------
            //Step 5: end
            assert(last_error() == kNoError);
            assert(memcmp(&this->npp_request_header_, npp_header, sizeof(*npp_header)) == 0);
            net_header->set_data_len(htons((short)encrypt_data_len));
            net_header->set_message_id(htons(net_header->message_id()));
            net_header->set_reserve(net_header->reserve());
            memcpy(&this->net_header_, net_header, sizeof(*net_header));

            return true;
        }

        size_t RequestMessage::GetPackedTotalDataSize( size_t data_len )
        {
            return sizeof(NetHeader) + sizeof(NppRequestHeaderV2) + kMD5HexLen + GetSignLength() + GetEncryptDataLength(data_len);
        }

        size_t RequestMessage::GetSignLength()
        {
            if (npp_request_header_.asymmetric_encrypt_method() == kSimpleRSA)
            {
                npp::SimpleRSA* rsa = s_pNppConfig->GetSimpleRSA(npp_request_header_.asymmetric_encrypt_key_no());
                if (!rsa)
                {
                    last_error(kNotSupportSimpleRSAKeyNumber);
                    return 0;
                }
                return rsa->getSignLength();
            }
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
            else if (npp_request_header_.asymmetric_encrypt_method() == kOpenSSLRSA0 || npp_request_header_.asymmetric_encrypt_method() == kOpenSSLRSA2)
            {
                OpenSSLRSA* rsa = s_pNppConfig->GetOpenSSLRSA(npp_request_header_.asymmetric_encrypt_key_no());
                if (!rsa)
                {
                    last_error(kNotSupportSimpleRSAKeyNumber);
                    return 0;
                }
                return rsa->getSignLength();
            }
#endif
            else
            {
                last_error(kNotSupportSignMethod);
                return 0;
            }
        }

        size_t RequestMessage::GetEncryptDataLength( size_t data_len )
        {
            size_t compressed_data_len = data_len;
            if (npp_request_header_.compress_method() == kZlibCompress)
            {
                compressed_data_len = ZLib::GetCompressBound(compressed_data_len);
            }
            
            if (npp_request_header_.symmetric_encrypt_method() == kIDEAEncrypt)
            {
                return H_ALIGN(compressed_data_len + 8, 8);
            }
            else if (npp_request_header_.symmetric_encrypt_method() == kNoEncrypt)
            {
                return compressed_data_len;
            }
            else
            {
                assert(false);
                last_error(kNotSupportSymmetricEncryptMethod);
                return 0;
            }
        }

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

            Compressor* compress = CompressorFactory::CreateCompressor(this->npp_request_header_.compress_method());
            npp::ext::auto_delete< npp::Compressor > compress_auto_delete(compress);
            if (compress)
            {
                if (!compress->Compress(orignal_data, orignal_data_len))
                {
                    last_error(kCompressError);
                    return 0;
                }

                data_to_be_encrypt = reinterpret_cast<const void*>(compress->Data());
                data_to_be_encrypt_len = compress->Size();
            }
            else
            {
                // We force to set the compress method to <code>kNoComress</code>
                npp_header->set_compress_method(kNoComress);
                this->npp_request_header_.set_compress_method(kNoComress);
            }
            
            symmetric_encryptor_ = SymmetricEncryptorFactory::CreateSymmetricEncryptor(this->npp_request_header_.symmetric_encrypt_method());
            std::string key = symmetric_encryptor_->CreateRandomKey();
            assert(symmetric_encryptor_->Initialize(reinterpret_cast<const unsigned char*>(key.data()), key.size()));
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
                    if (!encryptor->PublicEncrypt(orignal_data_len, orignal_data_len, write_pos, &len))
                    {
                        last_error(kAsymmetricPublicEncryptFailed);
                        return 0;
                    }
                    return len;
                }
            case kAsymmetricPrivateEncrypt:
                {
                    size_t len = encryptor->GetEncryptDataLength();
                    if (!encryptor->PrivateEncrypt(orignal_data_len, orignal_data_len, write_pos, &len))
                    {
                        last_error(kAsymmetricPrivateEncryptFailed);
                        return 0;
                    }
                    return len;
                }
            default:
                last_error(kNotSupportAsymmetricPublicPrivateMethod)
                return 0;
            }
            return 0;
        }

    }
}

#endif



