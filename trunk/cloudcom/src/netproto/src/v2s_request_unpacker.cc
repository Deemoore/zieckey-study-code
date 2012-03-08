
#include "netproto/include/v2s_request_unpacker.h"
#include "netproto/include/npp_config.h"
#include "netproto/include/compressor.h"

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

            const char* md5 = read_pos;

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
                    size_t compressed_data_len = d_len - sizeof(net_header_) - sizeof(npp_request_header_v2_) -kMD5HexLen - npp_request_header_v2_.asymmetric_encrypt_data_len();
                    assert(compressed_data_len + read_pos + npp_request_header_v2_.asymmetric_encrypt_data_len() == (const char*)d + d_len);
                    return _Uncompress(read_pos + npp_request_header_v2_.asymmetric_encrypt_data_len(), compressed_data_len);
                }
            }
                
            if (!_AsymmetricDecrypt(read_pos, npp_request_header_v2_.asymmetric_encrypt_data_len(), symmetric_encrypt_key_))
            {
                //error code has been set by _AsymmetricDecrypt
                return false;
            }

            read_pos += npp_request_header_v2_.asymmetric_encrypt_data_len_;

            assert(read_pos - ((const char*)d) < (long)d_len);

            size_t encrypt_data_len = ((const char*)d) + d_len - read_pos;

            if (!DecryptData(read_pos, encrypt_data_len, symmetric_encrypt_key_))
            {
                //ErrorCode has been set by DecryptData
                return false;
            }

            assert(unpacked_data_.size() > 0);

            assert(last_error() == kNoError);
            return true;
        }

        bool RequestMessageUnpacker::_AsymmetricDecrypt( const char* digest, size_t data_len, std::string& decrypted_data )
        {
            AsymmetricEncryptor* encryptor = AsymmetricEncryptorFactory::GetAsymmetricEncryptor(npp_request_header_v2_.asymmetric_encrypt_method(), npp_request_header_v2_.asymmetric_encrypt_key_no());
            size_t decrypted_data_len = encryptor->GetDecryptDataLength();
            decrypted_data.resize(decrypted_data_len);
            switch (npp_request_header_v2_.asymmetric_pub_priv_method())
            {
            case kAsymmetricPublicEncrypt:
                if (!encryptor->PrivateDecrypt(digest, data_len, &decrypted_data[0], &decrypted_data_len))
                {
                    last_error(kAsymmetricPrivateDecryptFailed);
                    decrypted_data.resize(0);
                    return false;
                }
                break;
            case kAsymmetricPrivateEncrypt:
                if (!encryptor->PublicDecrypt(digest, data_len, &decrypted_data[0], &decrypted_data_len))
                {
                    last_error(kAsymmetricPublicDecryptFailed);
                    decrypted_data.resize(0);
                    return false;
                }
                break;
            default:
                assert(false || (fprintf(stderr, "Not supported kNotSupportAsymmetricPublicPrivateMethod [%d]\n", npp_request_header_v2_.asymmetric_pub_priv_method())&& false) );
                last_error(kNotSupportAsymmetricPublicPrivateMethod);
                return false;
            }

            if (decrypted_data.length() < decrypted_data_len)
            {
                decrypted_data.resize(decrypted_data_len);
            }
            
            assert(last_error() == kNoError);
            return true;
        }

        bool RequestMessageUnpacker::DecryptData( const char* encrypt_data, size_t encrypt_data_len, const std::string& symmetric_encrypt_key )
        {
            switch (npp_request_header_v2_.symmetric_encrypt_method())
            {
            case kNoSymmetricEncrypt:
                if (!s_pNppConfig->support_plain())
                {
                    last_error(kNotSupportPlainData);
                    return false;
                }

                return _Uncompress(encrypt_data, encrypt_data_len);
                break;
            case kXorSymmetricEncrypt:
                last_error(kNotSupportXorEncrypt);
                return false;
                break;
            case kIDEASymmetricEncrypt:
                {
                    SymmetricEncryptor* e = SymmetricEncryptorFactory::CreateSymmetricEncryptor(npp_request_header_v2_.symmetric_encrypt_method());
                    if (!e)
                    {
                        last_error(kNotSupportIDEAKeyNumber);
                        return false;
                    }
                    bool init_ok = e->Initialize((const unsigned char*)symmetric_encrypt_key.data(), symmetric_encrypt_key.size());
                    assert(init_ok);
                    size_t len = encrypt_data_len;
                    unpacked_data_.resize(len);
                    if (!e->Decrypt(encrypt_data, encrypt_data_len, &unpacked_data_[0], len))
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

        bool RequestMessageUnpacker::_Uncompress( const void* d, size_t d_len )
        {
            if (npp_request_header_v2_.compress_method() == kNoComress)
            {
                unpacked_data_.assign((const char*)d, d_len);
                return true;
            }
            
            Compressor* c = CompressorFactory::CreateCompressor(npp_request_header_v2_.compress_method());
            ext::auto_delete<Compressor> c_auto_delete(c);
            if (!c->Uncompress(d, d_len, unpacked_data_))
            {
                last_error(kUncompressError);
                return false;
            }
            
            return true;
        }
    }
}





