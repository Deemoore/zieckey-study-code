#ifndef NETPROTO_NP_CONF_H_
#define NETPROTO_NP_CONF_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/idea_wrapper.h"
#include "netproto/include/openssl_rsa.h"
#include "netproto/include/slrsa_wrapper.h"

#include "netproto/include/singleton.h"

namespace npp
{

    #define s_pNppConfig	( ::npp::NppConfig::getSingletonPtr() )
    class _EXPORT_NETPROTO NppConfig  : public Singleton<NppConfig>
    {
        typedef std::map<int, IDEA>         IDEAMap;
        typedef std::map<int, SimpleRSA>    SimpleRSAMap;
#ifdef H_PROVIDE_RSA
        typedef std::map<int, OpenSSLRSA > OpenSSLRSAMap;
#endif
    public:
        NppConfig(bool support_plain, bool sign_pack, bool verify_sign);

        bool AddIdeaKey(int key_no, unsigned char key[16]);

        bool AddOpenSSLRSAKey(int key_no, 
            const unsigned char* private_key, const size_t private_key_len,
            const unsigned char* public_key, const size_t public_key_len );

        bool AddSimpleRSAKey(int key_no, 
            const unsigned char* private_key, const size_t private_key_len,
            const unsigned char* public_key, const size_t public_key_len );

        bool IsSupportPlainData() const;

        bool IsSignData() const;

        bool IsVerifySign() const;

        OpenSSLRSA* GetOpenSSLRSA(int index);

        SimpleRSA* GetSimpleRSA(int index);

        IDEA* GetIDEA(int index);

        size_t GetOpenSSLRSAKeyCount() const;

        size_t GetSimpleRSAKeyCount() const;
    private:
        bool support_plain_;
        bool sign_pack_;
        bool verify_sign_;

        IDEAMap       idea_map_;
        SimpleRSAMap  slrsa_map_;
#ifdef H_PROVIDE_RSA
        OpenSSLRSAMap rsa_map_;
#endif
    };

    inline bool NppConfig::IsSupportPlainData() const 
    {
        return support_plain_;
    }

    inline bool NppConfig::IsSignData() const
    {
        return sign_pack_;
    }

    inline bool NppConfig::IsVerifySign() const
    {
        return verify_sign_;
    }
}//end of namespace npp


#endif
