#include "netproto/include/message_unpacker.h"

#include "netproto/include/npp_config.h"

#include "netproto/include/md5.h"

#ifndef H_OS_WINDOWS
#include <arpa/inet.h>
#endif

namespace npp
{
    bool MessageUnpacker::Unpack( const void* d, size_t d_len )
    {
        if (!d || d_len < sizeof(net_header_) + sizeof(npp_header_) + 16 + 128)
        {
            last_error(kParameterError);
            return false;
        }

        const char* read_pos = ((const char*)d);

        uint8_t header_len = read_pos[0];
        assert(header_len >= sizeof(net_header_));
        memcpy(&net_header_, read_pos, sizeof(net_header_)); // for the sake of NetHeader's changes
        net_header_.data_len_   = ntohs(net_header_.data_len_);
        net_header_.message_id_ = ntohs(net_header_.message_id_);
        net_header_.preserve_   = ntohs(net_header_.preserve_);

        if (net_header_.data_len_ != d_len - header_len)
        {
            last_error(kNppHeaderDataLengthError);
            return false;
        }

        read_pos += header_len;
        memcpy(&npp_header_, read_pos, sizeof(npp_header_));

        read_pos += sizeof(npp_header_);

        assert(read_pos == ((const char*)d) + header_len + sizeof(npp_header_));
        size_t data_len = d_len - header_len - sizeof(npp_header_) - npp_header_.digest_sign_len_;
        if (s_pNppConfig->verify_data())
        {
            if (!VerifySign(read_pos, data_len))
            {
                //ErrorCode has been set by VerifySign
                return false;
            }
        }

        read_pos += npp_header_.digest_sign_len_;

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

    bool MessageUnpacker::VerifyDigest( const void* digest, size_t digest_len, const void* d, size_t d_len )
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

    bool MessageUnpacker::VerifyOpenSSLRSASign( const char* digest )
    {
        assert(npp_header_.sign_method_ == kOpenSSLRSA0 || npp_header_.sign_method_ == kOpenSSLRSA2);

#ifdef H_NPP_PROVIDE_RSA
        OpenSSLRSA* rsa = s_pNppConfig->GetOpenSSLRSA(npp_header_.sign_key_no_);
        if (!rsa)
        {
            last_error(kNotSupportOpenSSLRSAKeyNumber);
            return false;
        }

        if (!rsa->verify(digest, MD5::MD5_RAW_BIN_DIGEST_LEN, digest + MD5::MD5_RAW_BIN_DIGEST_LEN, npp_header_.digest_sign_len_ - MD5::MD5_RAW_BIN_DIGEST_LEN))
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

    bool MessageUnpacker::VerifySimpleRSASign( const char* digest )
    {
        assert(npp_header_.sign_method_ == kSimpleRSA);

        SimpleRSA* rsa = s_pNppConfig->GetSimpleRSA(npp_header_.sign_key_no_);
        if (!rsa)
        {
            last_error(kNotSupportSimpleRSAKeyNumber);
            return false;
        }

        if (!rsa->verify(digest, MD5::MD5_RAW_BIN_DIGEST_LEN, digest + MD5::MD5_RAW_BIN_DIGEST_LEN, npp_header_.digest_sign_len_ - MD5::MD5_RAW_BIN_DIGEST_LEN))
        {
            last_error(kSimpleRSAVerifyFailed);
            return false;
        }

        assert(last_error() == kNoError);
        return true;
    }

    bool MessageUnpacker::VerifySign( const char* digest, size_t data_len)
    {
        if (!VerifyDigest(digest, MD5::MD5_RAW_BIN_DIGEST_LEN, digest + npp_header_.digest_sign_len_, data_len))
        {
            last_error(kDigestVerifyFailed);
            return false;
        }

        switch (npp_header_.sign_method_)
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
            assert(false || (fprintf(stderr, "Not supported sign method [%d]\n", npp_header_.sign_method_)&& false) );
            last_error(kNotSupportSignMethod);
            break;
        }

        assert(last_error() == kNoError);
        return true;
    }

    bool MessageUnpacker::DecryptData( const char* encrypt_data, size_t encrypt_data_len )
    {
        switch (npp_header_.encrypt_method_)
        {
        case kNoEncrypt:
            if (!s_pNppConfig->support_plain())
            {
                last_error(kNotSupportPlainData);
                return false;
            }

            MemoryDataStream::write(encrypt_data, encrypt_data_len);
            break;
        case kXorEncrypt:
            last_error(kNotSupportXorEncrypt);
            return false;
            break;
        case kIDEAEncrypt:
            {
                IDEA* idea = s_pNppConfig->GetIDEA(npp_header_.encrypt_key_no_);
                if (!idea)
                {
                    last_error(kNotSupportIDEAKeyNumber);
                    return false;
                }

                if (!idea->decrypt(encrypt_data, encrypt_data_len, *this))
                {
                    last_error(kIDEADecryptFialed);
                    return false;
                }
            }
            break;
        default:
            last_error(kNotSupportEncryptMethod);
            return false;
            break;
        }

        assert(last_error() == kNoError);
        return true;
    }


}



