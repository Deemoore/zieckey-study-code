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

    const char* Message::Data()
    {
        if (Size() == 0)
        {
            return NULL;
        }
        else
        {
            return data();
        }
    }

    size_t Message::Size()
    {
        return size();
    }

#define H_CASE_STRING_BIGIN(state) switch(state){
#define H_CASE_STRING(state) case state:return #state;break;
#define H_CASE_STRING_END  default: return "unknown"; break; }

    const char* Message::strerror() const
    {
        H_CASE_STRING_BIGIN(last_error());
        H_CASE_STRING(kNoError);
        H_CASE_STRING(kParameterError);
        H_CASE_STRING(kVesionError);
        H_CASE_STRING(kMemoryNotEnough);
        H_CASE_STRING(kNotSupportOpenSSLRSA);   
        H_CASE_STRING(kNotSupportOpenSSLRSAKeyNumber); 
        H_CASE_STRING(kNotSupportSimpleRSAKeyNumber);
        H_CASE_STRING(kNotSupportIDEAKeyNumber); 
        H_CASE_STRING(kDigestVerifyFailed);
        H_CASE_STRING(kOpenSSLRSAVerifyFailed);
        H_CASE_STRING(kSimpleRSAVerifyFailed);
        H_CASE_STRING(kOpenSSLRSASignFailed);
        H_CASE_STRING(kSimpleRSASignFailed);
        H_CASE_STRING(kIDEADecryptFialed);
        H_CASE_STRING(kNotSupportSignMethod);
        H_CASE_STRING(kNotSupportEncryptMethod);
        H_CASE_STRING(kNotSupportPlainData);
        H_CASE_STRING(kNotSupportXorEncrypt);
        H_CASE_STRING_END;
    }
}



