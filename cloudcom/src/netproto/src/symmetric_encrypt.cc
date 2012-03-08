#include "netproto/include/inner_pre.h"

#include "netproto/include/symmetric_encrypt.h"
#include "netproto/include/idea.h"

#include "netproto/include/message.h"

namespace npp
{
    SymmetricEncryptor* SymmetricEncryptorFactory::CreateSymmetricEncryptor( int encrypt_method )
    {
        switch(encrypt_method)
        {
        case Message::kIDEASymmetricEncrypt:
#ifdef H_NPP_PROVIDE_IDEA_ENCRYPT
            return new IDEA();
#else
            return NULL;
#endif // end of #ifdef H_NPP_PROVIDE_IDEA_ENCRYPT
        default:
            return NULL;
        }
    }

    void SymmetricEncryptorFactory::DesstorySymmetricEncryptor( SymmetricEncryptor* c )
    {
        if (c)
        {
            delete c;
            c = NULL;
        }
    }
} // end of namespace ext





