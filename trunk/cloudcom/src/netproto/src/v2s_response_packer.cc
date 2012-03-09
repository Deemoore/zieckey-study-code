
#include "netproto/include/inner_pre.h"
#include "netproto/include/v2s_response_packer.h"
#include "netproto/include/v1_message_packer.h"
#include "netproto/include/v2s_request_unpacker.h"
#include "netproto/include/compressor.h"
#include "netproto/include/npp_config.h"
#include "slrsa/md5.h"

namespace npp
{
    namespace v2s
    {
        ResponseMessagePacker::ResponseMessagePacker( RequestMessageUnpacker* message_unpacker )
            : message_unpacker_(message_unpacker)
        {
            
        }

        bool ResponseMessagePacker::Pack( const void* data, size_t data_len, void* packed_data_buf, size_t& packed_data_buf_len )
        {
            if (message_unpacker_->GetProtoVersion() == Message::kProtoVersion1)
            {
                v1::MessagePacker v1packer(message_unpacker_->v1_message_unpacker());
                return v1packer.Pack(data, data_len, packed_data_buf, packed_data_buf_len);
            }
            
            assert(message_unpacker_->GetProtoVersion() == Message::kProtoVersion2);

            if (packed_data_buf_len < GetPackedTotalDataSize(data_len))
            {
                last_error(kParameterErrorDataLengthError);
                return false;
            }

            if (last_error() != kNoError)
            {
                return false;
            }
            
            //---------------------------------------------------------
            //Step 1: NetHeader
            unsigned char* write_pos = (unsigned char*)packed_data_buf;
            NetHeader* net_header = reinterpret_cast<NetHeader*>(write_pos);
            write_pos += sizeof(*net_header);
            memcpy(net_header, &message_unpacker_->net_header(), sizeof(*net_header));
            net_header->set_reserve(0);

            //---------------------------------------------------------
            //Step 2: NppResponseHeaderV2
            NppResponseHeaderV2* npp_header = reinterpret_cast<NppResponseHeaderV2*>(write_pos);
            write_pos += sizeof(*npp_header);
            npp_header->set_compress_method(message_unpacker_->npp_request_header_v2().compress_method());
            if (!message_unpacker_->asymmetric_decrypt_ok())
            {
                assert(!message_unpacker_->IsUnpackedOK());
                npp_header->set_error_code(kInvalidClientPublicKey);
                packed_data_buf_len = sizeof(*net_header) + sizeof(*npp_header);
                return true;
            }
            else if (!message_unpacker_->IsUnpackedOK())
            {
                assert(!message_unpacker_->IsUnpackedOK());
                npp_header->set_error_code(kInvalidRequest);
                packed_data_buf_len = sizeof(*net_header) + sizeof(*npp_header);
                return true;
            }

            npp_header->set_error_code(kRequestSuccess);

            //write MD5
            CalcMD5AndWrite(data, data_len, npp_header->md5_);

            //---------------------------------------------------------
            //Step 3: Encrypt data
            size_t encrypted_data_len = _SymmetricEncryptAndWrite(npp_header, data, data_len, write_pos);
            packed_data_buf_len = sizeof(*net_header) + sizeof(*npp_header) + encrypted_data_len;

            //---------------------------------------------------------
            //Step 4: End
            net_header->set_data_len(htons(packed_data_buf_len - sizeof(*net_header)));
            net_header->set_message_id(htons(net_header->message_id()));
            net_header->set_reserve(htons(net_header->reserve())); 

            return true;
        }

        size_t ResponseMessagePacker::GetPackedTotalDataSize( size_t data_len )
        {
            if (message_unpacker_->GetProtoVersion() == Message::kProtoVersion1)
            {
                v1::MessagePacker v1packer(message_unpacker_->v1_message_unpacker());
                return v1packer.GetPackedTotalDataSize(data_len);
            }

            ErrorCode ec = kNoError;
            size_t ret = sizeof(NetHeader) + sizeof(NppResponseHeaderV2) + message_unpacker_->npp_request_header_v2().GetSymmetricEncryptDataLength(data_len, ec);
            last_error(ec);
            return ret;
        }

        size_t ResponseMessagePacker::_SymmetricEncryptAndWrite( NppResponseHeaderV2* npp_header, const void* orignal_data, size_t orignal_data_len, uint8_t* write_pos )
        {
            const void*  data_to_be_encrypt = orignal_data;
            size_t data_to_be_encrypt_len = orignal_data_len;

            Compressor* compress = message_unpacker_->compressor();
            std::string compress_data;
            if (compress)
            {
                if (!compress->Compress(orignal_data, orignal_data_len, compress_data))
                {
                    last_error(kCompressError);
                    npp_header->set_error_code(kServerInternalError);
                    return 0;
                }

                data_to_be_encrypt = reinterpret_cast<const void*>(compress_data.data());
                data_to_be_encrypt_len = compress_data.size();
            }
            else
            {
                // We force to set the compress method to <code>kNoComress</code>
                npp_header->set_compress_method(kNoComress);
            }


            SymmetricEncryptor* symmetric_encryptor = message_unpacker_->symmetric_encryptor();
            if (symmetric_encryptor)
            {
                size_t write_len = symmetric_encryptor->GetEncryptDataLength(data_to_be_encrypt_len);
                if (!symmetric_encryptor->Encrypt(data_to_be_encrypt, data_to_be_encrypt_len, write_pos, write_len))
                {
                    last_error(kSymmetricEncyptFailed);
                    npp_header->set_error_code(kServerInternalError);
                    return 0;
                }
                return write_len;
            }

            if (!s_pNppConfig->support_plain())
            {
                npp_header->set_error_code(kInvalidRequest);
                return 0;
            }

            memcpy(write_pos, data_to_be_encrypt, data_to_be_encrypt_len);
            return data_to_be_encrypt_len;
        }
    }
}





