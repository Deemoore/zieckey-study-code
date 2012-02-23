#ifndef NETPROTO_NP_CONF_H_
#define NETPROTO_NP_CONF_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/idea_wrapper.h"
#include "netproto/include/openssl_rsa.h"
#include "netproto/include/slrsa_wrapper.h"

namespace npp
{
    typedef std::map<int, IDEA_KEY_SCHEDULE> IDEAMap;
#ifdef H_PROVIDE_RSA
    typedef std::map<int, OpenSSLRSA* > OpenSSLRSAMap;
#endif

    typedef std::map<int, SimpleRSA> SimpleRSAMap;

    class _EXPORT_NETPROTO NppConfig
    {
    public:
        bool AddIdeaKey(int key_no, unsigned char key[16]);

    private:
        bool support_plain;
        bool sign_pack;
        bool verify_sign;

        IDEAMap idea_encrypt_map_;
        IDEAMap idea_decrypt_map_;

#ifdef H_PROVIDE_RSA
        OpenSSLRSAMap rsa_sign_map_;
        OpenSSLRSAMap rsa_verify_map_;
#endif
        
        SimpleRSAMap  slrsa_map_;
    };
}//end of namespace npp


#endif
