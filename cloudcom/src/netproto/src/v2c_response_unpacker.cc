
#include "netproto/include/inner_pre.h"
#include "netproto/include/v2c_response_unpacker.h"
#include "netproto/include/v2c_request_packer.h"
#include "netproto/include/npp_config.h"
#include "netproto/include/symmetric_encrypt.h"
#include "netproto/include/compressor.h"

namespace npp
{
    namespace v2c
    {
        const uint8_t* ResponseUnpacker::Data() const
        {
            if (Size() == 0)
            {
                return NULL;
            }
            else
            {
                return reinterpret_cast<const uint8_t*>(unpacked_data_.data());
            }
        }

        size_t ResponseUnpacker::Size() const
        {
            return unpacked_data_.size();
        }

        ResponseUnpacker::ResponseUnpacker( RequestMessage* request_message )
            : request_message_(request_message)
        {
        }

        bool ResponseUnpacker::Unpack( const void* d, size_t d_len )
        {
            //---------------------------------------------------------
            //Step 1: NetHeader
            if (d_len < sizeof(net_header_) + sizeof(npp_response_header_v2_))
            {
                last_error(kParameterErrorDataLengthError);
                return false;
            }

            const char* read_pos = ((const char*)d);

            uint8_t header_len = read_pos[0];
            assert(header_len >= sizeof(net_header_));
            memcpy(&net_header_, read_pos, sizeof(net_header_)); // for the sake of NetHeader's changes
            net_header_.data_len_   = ntohl(net_header_.data_len_);
            net_header_.message_id_ = ntohs(net_header_.message_id_);
            net_header_.reserve_    = ntohs(net_header_.reserve_);


            assert(request_message_);
            assert(net_header_.message_id() == request_message_->GetMessageID());

            if (net_header_.data_len_ != d_len - header_len)
            {
                last_error(kNppHeaderDataLengthError);
                return false;
            }

            read_pos += header_len;

            //---------------------------------------------------------
            //Step 2: NppRequestHeaderV2 
            memcpy(&npp_response_header_v2_, read_pos, sizeof(npp_response_header_v2_));
            read_pos += sizeof(npp_response_header_v2_);
            assert(read_pos == ((const char*)d) + header_len + sizeof(npp_response_header_v2_));

            if (npp_response_header_v2_.error_code() != kRequestSuccess)
            {
                return true;
            }
            
            //---------------------------------------------------------
            //Step 3: Symmetric Decrypt
            if (!_DecryptAndUncompressData(read_pos, net_header_.data_len_ - sizeof(npp_response_header_v2_)))
            {
                return false;
            }

            //---------------------------------------------------------
            //Step 4: MD5 verify
            if (s_pNppConfig->verify_data())
            {
                return VerifyDigest(npp_response_header_v2_.md5(), kMD5HexLen, unpacked_data_.data(), unpacked_data_.length());
            }
            
            assert(last_error() == kNoError);
            return true;
        }

        bool ResponseUnpacker::_DecryptAndUncompressData( const char* encrypt_data, size_t encrypt_data_len )
        {
            SymmetricEncryptor* e = request_message_->symmetric_encryptor();
            if (!e)
            {
                if (request_message_->npp_request_header_v2().symmetric_encrypt_method() != kNoSymmetricEncrypt)
                {
                    last_error(kServerResponseParameterError);
                    return false;
                }
                return _Uncompress(encrypt_data, encrypt_data_len);
            }

            size_t decrypted_data_len = e->GetDecryptDataLength(encrypt_data, encrypt_data_len);
            if (npp_response_header_v2_.compress_method() == kNoComress)
            {
                unpacked_data_.resize(decrypted_data_len);
                if (!e->Decrypt(encrypt_data, decrypted_data_len, &unpacked_data_[0], decrypted_data_len))
                {
                    last_error(kIDEADecryptFialed);
                    return false;
                }

                assert(encrypt_data_len <= unpacked_data_.size());
                if (decrypted_data_len < unpacked_data_.size())
                {
                    unpacked_data_.resize(decrypted_data_len);
                }
                return true;
            }

            std::string decrypted_data; //the decrypted data which is compressed
            decrypted_data.resize(decrypted_data_len);
            if (!e->Decrypt(encrypt_data, decrypted_data_len, &decrypted_data[0], decrypted_data_len))
            {
                last_error(kIDEADecryptFialed);
                return false;
            }

            assert(encrypt_data_len <= decrypted_data.size());
            if (decrypted_data_len < decrypted_data.size())
            {
                decrypted_data.resize(decrypted_data_len);
            }

            return _Uncompress(decrypted_data.data(), decrypted_data_len);
        }

        bool ResponseUnpacker::_Uncompress( const void* d, size_t d_len )
        {
            if (npp_response_header_v2_.compress_method() == kNoComress)
            {
                unpacked_data_.assign((const char*)d, d_len);
                return true;
            }

            Compressor* compressor = request_message_->compressor();
            if (compressor)
            {
                if (!compressor->Uncompress(d, d_len, unpacked_data_))
                {
                    last_error(kUncompressError);
                    return false;
                }

                return true;
            }
            else
            {
                assert(false);
                last_error(kServerResponseParameterError);
                return false;
            }
        }
    }
}




