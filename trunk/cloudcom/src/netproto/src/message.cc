#include "netproto/include/message.h"

#include "netproto/include/npp_config.h"

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
        H_CASE_STRING(kNotSupportEncryptMethod);
        H_CASE_STRING(kNotSupportPlainData);
        H_CASE_STRING(kNotSupportXorEncrypt);
        H_CASE_STRING_END;
    }

    Message::NppRequestHeaderV2::NppRequestHeaderV2()
    {
        symmetric_encrypt_method_  = kIDEAEncrypt;
        
        compress_method_ = kZlibCompress;

        if (s_pNppConfig->GetOpenSSLRSAKeyCount() > 0)
        {
            asymmetric_encrypt_method_ = kOpenSSLRSA0;
            OpenSSLRSA* rsa = NULL;
            do 
            {
                asymmetric_encrypt_key_no_ = rand() % (s_pNppConfig->GetOpenSSLRSAKeyCount() + 1);
                rsa = s_pNppConfig->GetOpenSSLRSA(asymmetric_encrypt_key_no_);
            } while(!rsa);
            digest_sign_len_ = 16 + rsa->getSignLength();
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
            digest_sign_len_ = 16 + rsa->getSignLength();
        }
        else
        {
            //TODO
            assert(false);
        }
    }
}



