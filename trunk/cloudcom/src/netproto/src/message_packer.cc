#include "netproto/include/message_packer.h"
#include "netproto/include/message_unpacker.h"
#include "netproto/include/npp_config.h"

#include "netproto/include/md5.h"


namespace npp
{

    MessagePacker::MessagePacker( MessageUnpacker* message_unpacker )
        : message_unpacker_(message_unpacker)
    {

    }


    size_t MessagePacker::GetPackedTotalDataSize(const NppHeader& npp_header, size_t data_len)
    {
        if (message_unpacker_)
        {
            if (message_unpacker_->net_header().version() == 1)
            {
                return sizeof(NetHeader) + sizeof(NppHeader) + MD5::MD5_RAW_BIN_DIGEST_LEN + GetSignLength(npp_header) + H_ALIGN(data_len, 8);
            }
            else
            {
                //TODO version 2
                assert(false && "Not supported!");
            }
        }
        
        //version 1
        return sizeof(NetHeader) + sizeof(NppHeader) + MD5::MD5_RAW_BIN_DIGEST_LEN + GetSignLength(npp_header) + H_ALIGN(data_len, 8);

        //TODO version 2
    }

    bool MessagePacker::Pack( const void* d, size_t data_len, void* packed_data_buf, size_t& packed_data_buf_len )
    {
        if (!message_unpacker_)
        {
            return pack_v1(d, data_len, packed_data_buf, packed_data_buf_len);
        }

        if (message_unpacker_->net_header().version() == 1)
        {
            return pack_v1(d, data_len, packed_data_buf, packed_data_buf_len);
        }
        else
        {
            assert(false && "Not supported version!");
            last_error(kVesionError);
            return false;
        }
    }

    size_t MessagePacker::GetSignLength(const NppHeader& npp_header)
    {
        if (npp_header.sign_method_ == kSimpleRSA)
        {
            npp::SimpleRSA* rsa = s_pNppConfig->GetSimpleRSA(npp_header.encrypt_key_no());
            if (!rsa)
            {
                last_error(kNotSupportSimpleRSAKeyNumber);
                return 0;
            }
            return rsa->getSignLength();
        }
        else if (npp_header.sign_method() == kOpenSSLRSA0 || npp_header.sign_method() == kOpenSSLRSA2)
        {
            OpenSSLRSA* rsa = s_pNppConfig->GetOpenSSLRSA(npp_header.sign_key_no());
            if (!rsa)
            {
                last_error(kNotSupportSimpleRSAKeyNumber);
                return 0;
            }
            return rsa->getSignLength();
        }
        else
        {
            last_error(kNotSupportSignMethod);
            return 0;
        }
    }

    bool MessagePacker::pack_v1( const void* d, size_t data_len, void* packed_data_buf, size_t& packed_data_buf_len )
    {
        //---------------------------------------------------------
        //Step 1: NetHeader and NppHeader
        unsigned char* write_pos = (unsigned char*)packed_data_buf;
        NetHeader* net_header = reinterpret_cast<NetHeader*>(write_pos);
        write_pos += sizeof(*net_header);
        NppHeader* npp_header = reinterpret_cast<NppHeader*>(write_pos);
        write_pos += sizeof(*npp_header);
        if (message_unpacker_)
        {
            memcpy(net_header, &(message_unpacker_->net_header()), sizeof(*net_header));
            memcpy(npp_header, &(message_unpacker_->npp_header()), sizeof(*npp_header));
            CalculateSignKeyNum(*npp_header);
        }
        else
        {
            net_header->Init();
            npp_header->Init();
        }

        assert(packed_data_buf_len >= GetPackedTotalDataSize(*npp_header, data_len));
        if (packed_data_buf_len < GetPackedTotalDataSize(*npp_header, data_len))
        {
            last_error(kMemoryNotEnough);
            return false;
        }

        //---------------------------------------------------------
        //Step 2: Fill the idea encrypt data
        {
            npp_header->digest_sign_len_ = GetSignLength(*npp_header) + MD5::MD5_RAW_BIN_DIGEST_LEN;
            switch (npp_header->encrypt_method_)
            {
            case kNoEncrypt:
                memcpy(write_pos + npp_header->digest_sign_len_, d, data_len);
                packed_data_buf_len = sizeof(*net_header) + sizeof(*npp_header) + npp_header->digest_sign_len_ + data_len;
                break;
            case kIDEAEncrypt:
                {
                    //TODO need optimize
                    MemoryDataStream buf;
                    IDEA* idea = s_pNppConfig->GetIDEA(npp_header->encrypt_key_no_);
                    assert(idea);
                    if (!idea)
                    {
                        last_error(kNotSupportIDEAKeyNumber);
                        return false;
                    }
                    idea->encrypt(d, data_len, buf);
                    memcpy(write_pos + npp_header->digest_sign_len_, buf.data(), buf.size());
                    packed_data_buf_len = sizeof(*net_header) + sizeof(*npp_header) + npp_header->digest_sign_len_ + buf.size();
                    break;
                }
            default:
                assert(false && "Not Supported!");
                last_error(kNotSupportEncryptMethod);
                return false;
                break;
            }
        }

        net_header->data_len_   = packed_data_buf_len - sizeof(*net_header);
        net_header->data_len_   = htons(net_header->data_len_);
        net_header->message_id_ = htons(net_header->message_id_);
        net_header->preserve_   = htons(net_header->preserve_);

        if (!s_pNppConfig->sign_data())
        {
            assert(last_error() == kNoError);
            return true;
        }

        //---------------------------------------------------------
        //Step 3: Fill the digest MD5
        MD5 md5(write_pos + npp_header->digest_sign_len_, 
            packed_data_buf_len - sizeof(*net_header) - sizeof(*npp_header) - npp_header->digest_sign_len_);
        md5.getRawDigest(write_pos);
        write_pos += MD5::MD5_RAW_BIN_DIGEST_LEN;

        //---------------------------------------------------------
        //Step 4: Fill the digest Sign
        if (npp_header->sign_method_ == kSimpleRSA)
        {
            SimpleRSA* rsa = s_pNppConfig->GetSimpleRSA(npp_header->sign_key_no_);
            if (!rsa)
            {
                last_error(kNotSupportSimpleRSAKeyNumber);
                return false;
            }
            size_t siglen = rsa->getSignLength();
            if (!rsa->sign(write_pos - MD5::MD5_RAW_BIN_DIGEST_LEN, MD5::MD5_RAW_BIN_DIGEST_LEN, write_pos, &siglen))
            {
                last_error(kSimpleRSASignFailed);
                return false;
            }
        }
        else if (npp_header->sign_method_ == kOpenSSLRSA0 || npp_header->sign_method_ == kOpenSSLRSA2)
        {
            OpenSSLRSA* rsa = s_pNppConfig->GetOpenSSLRSA(npp_header->sign_key_no_);
            if (!rsa)
            {
                last_error(kNotSupportOpenSSLRSAKeyNumber);
                return false;
            }
            size_t siglen = rsa->getSignLength();
            if (!rsa->sign(write_pos - MD5::MD5_RAW_BIN_DIGEST_LEN, MD5::MD5_RAW_BIN_DIGEST_LEN, write_pos, &siglen))
            {
                last_error(kOpenSSLRSASignFailed);
                return false;
            }
        }
        else
        {
            last_error(kNotSupportSignMethod);
            return false;
        }

        assert(last_error() == kNoError);
        return true;
    }

    void MessagePacker::CalculateSignKeyNum( NppHeader& npp_header )
    {
        //1->2 2->1
        //3->4 4->3
        //5->6 6->5
        //...
        {
            uint8_t encrypt_key = npp_header.encrypt_key_no();
            if (encrypt_key % 2) //1,3,5
            {
                npp_header.set_encrypt_key_no(encrypt_key + 1);
            }
            else //2, 4, 6 ...
            {
                npp_header.set_encrypt_key_no(encrypt_key - 1);
            }
        }
        
        {
            uint8_t sign_key = npp_header.sign_key_no();
            if (sign_key % 2) //1,3,5
            {
                npp_header.set_sign_key_no(sign_key + 1);
            }
            else //2, 4, 6 ...
            {
                npp_header.set_sign_key_no(sign_key - 1);
            }
        }
    }
}



