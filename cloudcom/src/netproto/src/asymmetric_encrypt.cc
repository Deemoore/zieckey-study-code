#include "netproto/include/inner_pre.h"

#include "netproto/include/symmetric_encrypt.h"
#include "netproto/include/slrsa.h"
#include "netproto/include/openssl_rsa.h"
#include "netproto/include/message.h"
#include "netproto/include/npp_config.h"

namespace npp
{
    AsymmetricEncryptor* AsymmetricEncryptorFactory::GetAsymmetricEncryptor(int encrypt_method, int key_no)
    {
        switch(encrypt_method)
        {
        case Message::kOpenSSLRSA0:
        case Message::kOpenSSLRSA2:
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
            return s_pNppConfig->GetOpenSSLRSA(key_no);
#else
            return NULL;
#endif // end of #ifdef H_NPP_PROVIDE_OPENSSL_RSA
        case Message::kSimpleRSA:
            return s_pNppConfig->GetSimpleRSA(key_no);
        default:
            return NULL;
        }
    }

} // end of namespace ext





