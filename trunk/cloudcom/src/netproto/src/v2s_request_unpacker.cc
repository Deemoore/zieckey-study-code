
#include "netproto/include/v2s_request_unpacker.h"

namespace npp
{
    namespace v2s
    {

        RequestMessageUnpacker::RequestMessageUnpacker()
            : v1_message_unpacker_(NULL)
        {

        }


        RequestMessageUnpacker::~RequestMessageUnpacker()
        {
            if (v1_message_unpacker_)
            {
                delete v1_message_unpacker_;
                v1_message_unpacker_ = NULL;
            }
        }

        const uint8_t* RequestMessageUnpacker::Data() const
        {
            if (v1_message_unpacker_)
            {
                return v1_message_unpacker_->Data();
            }
            
            if (Size() == 0)
            {
                return NULL;
            }
            else
            {
                return reinterpret_cast<const uint8_t*>(unpacked_data_.data());
            }
        }

        size_t RequestMessageUnpacker::Size() const
        {
            if (v1_message_unpacker_)
            {
                return v1_message_unpacker_->Size();
            }

            return unpacked_data_.size();
        }

        bool RequestMessageUnpacker::Unpack( const void* d, size_t d_len )
        {
            if (!d)
            {
                last_error(kParameterErrorNULLPointer);
                return false;
            }

            if (d_len < sizeof(net_header_) + sizeof(NppHeaderV1))
            {
                last_error(kParameterErrorDataLengthError);
                return false;
            }

            if (static_cast<const char*>(d)[1] == kProtoVersion1)
            {
                v1_message_unpacker_ = new v1::MessageUnpacker();
                return v1_message_unpacker_->Unpack(d, d_len);
            }

            if (static_cast<const char*>(d)[1] == kProtoVersion2)
            {
                return _UnpackV2(d, d_len);
            }

            last_error(kVesionError);
            return false;
        }

        bool RequestMessageUnpacker::_UnpackV2( const void* d, size_t d_len )
        {
            if (d_len < sizeof(net_header_) + sizeof(npp_request_header_v2_) + 16 + 64)
            {
                last_error(kParameterErrorDataLengthError);
                return false;
            }

            const char* read_pos = ((const char*)d);

            uint8_t header_len = read_pos[0];
            assert(header_len >= sizeof(net_header_));
            memcpy(&net_header_, read_pos, sizeof(net_header_)); // for the sake of NetHeader's changes
            net_header_.data_len_   = ntohs(net_header_.data_len_);
            net_header_.message_id_ = ntohs(net_header_.message_id_);
            net_header_.reserve_    = ntohs(net_header_.reserve_);

            if (net_header_.data_len_ != d_len - header_len)
            {
                last_error(kNppHeaderDataLengthError);
                return false;
            }

            read_pos += header_len;
            memcpy(&npp_request_header_v2_, read_pos, sizeof(npp_request_header_v2_));

            read_pos += sizeof(npp_request_header_v2_);

            assert(read_pos == ((const char*)d) + header_len + sizeof(npp_request_header_v2_));

            const uint8_t* md5 = read_pos;

            read_pos += kMD5HexLen;

            if (npp_request_header_v2_.symmetric_encrypt_method() == kNoSymmetricEncrypt)
            {
                if (!s_pNppConfig->support_plain())
                {
                    last_error(kNotSupportPlainData);
                    return false;
                }
                else
                {
                    _UnpackV2(d, d_len);
                }
            }
            else
            {
                std::string encrypt_key = _AsymmetricDecrypt(read_pos, npp_request_header_v2_.asymmetric_encrypt_data_len());
            }
            






            //TODO




            size_t data_len = d_len - header_len - sizeof(npp_request_header_v2_) - npp_request_header_v2_.asymmetric_encrypt_data_len_;
            if (s_pNppConfig->verify_data())
            {
                if (!_AsymmetricDecrypt(read_pos, data_len))
                {
                    //ErrorCode has been set by _AsymmetricDecrypt
                    return false;
                }
            }

            read_pos += npp_request_header_v2_.asymmetric_encrypt_data_len_;

            assert(read_pos - ((const char*)d) < (long)d_len);

            size_t encrypt_data_len = ((const char*)d) + d_len - read_pos;

            if (!DecryptData(read_pos, encrypt_data_len))
            {
                //ErrorCode has been set by DecryptData
                return false;
            }

            assert(last_error() == kNoError);
            return true;
        }


        bool RequestMessageUnpacker::VerifyDigest( const void* digest, size_t digest_len, const void* d, size_t d_len )
        {
            unsigned char binarymd5[16] = {};
            MD5 md5(d, d_len);
            md5.getRawDigest(binarymd5);
            if (0 == memcmp(digest, binarymd5, sizeof(binarymd5)))
            {
                assert(last_error() == kNoError);
                return true;
            }

            last_error(kDigestVerifyFailed);
            return false;
        }

        bool RequestMessageUnpacker::VerifyOpenSSLRSASign( const char* digest )
        {
            assert(npp_request_header_v2_.sign_method_ == kOpenSSLRSA0 || npp_request_header_v2_.sign_method_ == kOpenSSLRSA2);

#ifdef H_NPP_PROVIDE_OPENSSL_RSA
            OpenSSLRSA* rsa = s_pNppConfig->GetOpenSSLRSA(npp_request_header_v2_.sign_key_no_);
            if (!rsa)
            {
                last_error(kNotSupportOpenSSLRSAKeyNumber);
                return false;
            }

            if (!rsa->verify(digest, kMD5HexLen, digest + kMD5HexLen, npp_request_header_v2_.asymmetric_encrypt_data_len_))
            {
                last_error(kOpenSSLRSAVerifyFailed);
                return false;
            }
            assert(last_error() == kNoError);
            return true;
#else
            last_error(kNotSupportOpenSSLRSA);
            return false;
#endif
        }

        bool RequestMessageUnpacker::VerifySimpleRSASign( const char* digest )
        {
            assert(npp_request_header_v2_.sign_method_ == kSimpleRSA);

            SimpleRSA* rsa = s_pNppConfig->GetSimpleRSA(npp_request_header_v2_.sign_key_no_);
            if (!rsa)
            {
                last_error(kNotSupportSimpleRSAKeyNumber);
                return false;
            }

            if (!rsa->verify(digest, kMD5HexLen, digest + kMD5HexLen, npp_request_header_v2_.asymmetric_encrypt_data_len_))
            {
                last_error(kSimpleRSAVerifyFailed);
                return false;
            }

            assert(last_error() == kNoError);
            return true;
        }

        bool RequestMessageUnpacker::_AsymmetricDecrypt( const char* digest, size_t data_len, std::string& decrypted_data)
        {
            AsymmetricEncryptor* encryptor = AsymmetricEncryptorFactory::GetAsymmetricEncryptor(npp_request_header_v2_.asymmetric_encrypt_method(), npp_request_header_v2_.asymmetric_encrypt_key_no());

            switch (npp_request_header_v2_.sign_method_)
            {
            case kOpenSSLRSA0:
            case kOpenSSLRSA2:
                if (!VerifyOpenSSLRSASign(digest))
                {
                    last_error(kOpenSSLRSAVerifyFailed);
                    return false;
                }
                break;
            case kSimpleRSA:
                if (!VerifySimpleRSASign(digest))
                {
                    last_error(kSimpleRSAVerifyFailed);
                    return false;
                }
                break;
            default:
                assert(false || (fprintf(stderr, "Not supported sign method [%d]\n", npp_request_header_v2_.sign_method_)&& false) );
                last_error(kNotSupportSignMethod);
                break;
            }

            assert(last_error() == kNoError);
            return true;
        }

        bool RequestMessageUnpacker::DecryptData( const char* encrypt_data, size_t encrypt_data_len )
        {
            switch (npp_request_header_v2_.symmetric_encrypt_method())
            {
            case kNoSymmetricEncrypt:
                if (!s_pNppConfig->support_plain())
                {
                    last_error(kNotSupportPlainData);
                    return false;
                }
                
                {
                    switch ()
                    {

                    }
                }
                unpacked_data_.assign(encrypt_data, encrypt_data_len);
                break;
            case kXorSymmetricEncrypt:
                last_error(kNotSupportXorEncrypt);
                return false;
                break;
            case kIDEASymmetricEncrypt:
                {
                    IDEA* idea = s_pNppConfig->GetIDEA(npp_request_header_v2_.encrypt_key_no_);
                    if (!idea)
                    {
                        last_error(kNotSupportIDEAKeyNumber);
                        return false;
                    }
                    size_t len = encrypt_data_len;
                    unpacked_data_.resize(len);
                    if (!idea->decrypt(encrypt_data, encrypt_data_len, IDEA::PaddingZero, &unpacked_data_[0], len))
                    {
                        last_error(kIDEADecryptFialed);
                        return false;
                    }
                    assert(unpacked_data_.size() <= len);
                    if (unpacked_data_.size() < len)
                    {
                        unpacked_data_.resize(len);
                    }
                }
                break;
            default:
                last_error(kNotSupportSymmetricEncryptMethod);
                return false;
                break;
            }

            assert(last_error() == kNoError);
            return true;
        }

        const Message::NetHeader& RequestMessageUnpacker::net_header() const
        {
            if (v1_message_unpacker_)
            {
                return v1_message_unpacker_->net_header();
            }
            
            return net_header_;
        }

        bool RequestMessageUnpacker::IsUnpackedOK() const
        {
            if (v1_message_unpacker_)
            {
                return v1_message_unpacker_->IsUnpackedOK();
            }
            
            return last_error() == kNoError && Data() != NULL;
        }
    }
}

#endif



