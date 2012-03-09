#include "netproto/include/message.h"

#include "netproto/include/npp_config.h"
#include "netproto/include/zlib.h"
#include "netproto/include/md5.h"

#ifndef H_OS_WINDOWS
#include <arpa/inet.h>
#endif

namespace npp
{
    Message::Message()
        : last_error_(kNoError)
    {
    }

    Message::~Message()
    {

    }


#define H_CASE_STRING_BIGIN(state) switch(state){
#define H_CASE_STRING(state) case state:return #state;break;
#define H_CASE_STRING_END  default: return "unknown"; break; }

    const char* Message::strerror() const
    {
        H_CASE_STRING_BIGIN(last_error());
        H_CASE_STRING(kNoError);
        H_CASE_STRING(kParameterErrorNULLPointer);
        H_CASE_STRING(kParameterErrorDataLengthError);
        H_CASE_STRING(kVesionError);
        H_CASE_STRING(kMemoryNotEnough);
        H_CASE_STRING(kNotSupportOpenSSLRSA);   
        H_CASE_STRING(kNotSupportOpenSSLRSAKeyNumber); 
        H_CASE_STRING(kNotSupportSimpleRSAKeyNumber);
        H_CASE_STRING(kNotSupportIDEAKeyNumber); 
        H_CASE_STRING(kNppHeaderDataLengthError);
        H_CASE_STRING(kDigestVerifyFailed);
        H_CASE_STRING(kOpenSSLRSAVerifyFailed);
        H_CASE_STRING(kSimpleRSAVerifyFailed);
        H_CASE_STRING(kOpenSSLRSASignFailed);
        H_CASE_STRING(kSimpleRSASignFailed);
        H_CASE_STRING(kIDEAEncryptFialed);
        H_CASE_STRING(kIDEADecryptFialed);
        H_CASE_STRING(kNotSupportSignMethod);
        H_CASE_STRING(kNotSupportSymmetricEncryptMethod);
        H_CASE_STRING(kNotSupportAsymmetricPublicPrivateMethod);
        H_CASE_STRING(kNotSuportCompressMethod);
        H_CASE_STRING(kNotSupportPlainData);
        H_CASE_STRING(kNotSupportXorEncrypt);
        H_CASE_STRING(kCompressError);
        H_CASE_STRING(kUncompressError);
        H_CASE_STRING(kSymmetricEncyptFailed);
        H_CASE_STRING(kAsymmetricPublicEncryptFailed);
        H_CASE_STRING(kAsymmetricPrivateDecryptFailed);
        H_CASE_STRING(kAsymmetricPrivateEncryptFailed);
        H_CASE_STRING(kAsymmetricPublicDecryptFailed);
        H_CASE_STRING_END;
    }

    Message::NppRequestHeaderV2::NppRequestHeaderV2()
    {
        memset(this, 0, sizeof(*this));

        symmetric_encrypt_method_   = kIDEASymmetricEncrypt;
        asymmetric_encrypt_         = 0;
        compress_method_            = kZlibCompress;

        if (s_pNppConfig->GetOpenSSLRSAKeyCount() > 0)
        {
            asymmetric_encrypt_method_ = kOpenSSLRSA0;
            OpenSSLRSA* rsa = NULL;
            do 
            {
                asymmetric_encrypt_key_no_ = rand() % (s_pNppConfig->GetOpenSSLRSAKeyCount() + 1);
                rsa = s_pNppConfig->GetOpenSSLRSA(asymmetric_encrypt_key_no_);
            } while(!rsa);
            asymmetric_encrypt_data_len_ = rsa->getSignLength();
        }
        else if (s_pNppConfig->GetSimpleRSAKeyCount() > 0)
        {
            asymmetric_encrypt_method_ = kSimpleRSA;
            SimpleRSA* rsa = NULL;
            do 
            {
                asymmetric_encrypt_key_no_ = rand() % (s_pNppConfig->GetSimpleRSAKeyCount() + 1);
                rsa = s_pNppConfig->GetSimpleRSA(asymmetric_encrypt_key_no_);
            } while(!rsa);
            asymmetric_encrypt_data_len_ = rsa->getSignLength();
        }
        else
        {
            //TODO
            assert(false);
        }
    }

    size_t Message::NppRequestHeaderV2::GetSymmetricEncryptDataLength(size_t data_len, ErrorCode& ec) const
    {
        size_t compressed_data_len = data_len;
        if (compress_method() == kZlibCompress)
        {
            compressed_data_len = ZLib::GetCompressBound(compressed_data_len);
        }

        switch (symmetric_encrypt_method())
        {
        case kNoSymmetricEncrypt:
            return compressed_data_len;
        case kIDEASymmetricEncrypt:
            return H_ALIGN(compressed_data_len + 8, 8);
        default:
            assert(false);
            ec = (kNotSupportSymmetricEncryptMethod);
            return 0;
        }
    }

    size_t Message::NppRequestHeaderV2::GetSignLength(ErrorCode& ec)
    {
        if (asymmetric_encrypt_method() == kSimpleRSA)
        {
            npp::SimpleRSA* rsa = s_pNppConfig->GetSimpleRSA(asymmetric_encrypt_key_no());
            if (!rsa)
            {
                ec = (kNotSupportSimpleRSAKeyNumber);
                return 0;
            }
            return rsa->getSignLength();
        }
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
        else if (asymmetric_encrypt_method() == kOpenSSLRSA0 || asymmetric_encrypt_method() == kOpenSSLRSA2)
        {
            OpenSSLRSA* rsa = s_pNppConfig->GetOpenSSLRSA(asymmetric_encrypt_key_no());
            if (!rsa)
            {
                ec = (kNotSupportSimpleRSAKeyNumber);
                return 0;
            }
            return rsa->getSignLength();
        }
#endif
        else
        {
            ec = (kNotSupportSignMethod);
            return 0;
        }
    }
}



