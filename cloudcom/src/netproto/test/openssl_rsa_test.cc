
#include "netproto/include/test_common.h"
#include "netproto/include/openssl_rsa.h"

#if H_PROVIDE_RSA

namespace
{
    void test1()
    {
        const size_t BUF_SIZE = 1024;
        const size_t KEY_LEN = 1024;
        unsigned char publickey [BUF_SIZE] = {0};
        unsigned char privatekey[BUF_SIZE] = {0};
        size_t publickey_len = 0;
        size_t privatekey_len = 0;
        bool ret = npp::OpenSSLRSA::generateKey( KEY_LEN, publickey, &publickey_len, privatekey, &privatekey_len );
        H_TEST_ASSERT(ret);
        if ( !ret )
        {
            return;
        }

        npp::OpenSSLRSA rsa_private( npp::OpenSSLRSA::KT_PRIVATE );
        H_TEST_ASSERT(rsa_private.initialize(privatekey, privatekey_len));

        npp::OpenSSLRSA rsa_public( npp::OpenSSLRSA::KT_PUBLIC );
        H_TEST_ASSERT(rsa_public.initialize(publickey,  publickey_len));

        const char* data = "asdfjlasjflasjdflajsdlkfjasdlkfajsdlkfjas;dlkf";
        size_t data_len = strlen(data);

        unsigned char sigret[2048] = {0};
        size_t siglen  = 0;

        ret = rsa_private.sign( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, sigret, &siglen );
        H_TEST_ASSERT(ret);
        ret = rsa_public.verify( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, sigret, siglen );
        H_TEST_ASSERT(ret);

        std::string ss;
        H_TEST_ASSERT(rsa_private.sign( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, ss ));
        H_TEST_ASSERT(rsa_public.verify( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, ss.data(), ss.size() ));
    }
}

TEST_UNIT(openssl_rsa_test_1)
{
    test1();

//     std::string private_key;
//     std::string public_key;
//     H_TEST_ASSERT(npp::OpenSSLRSA::generateKey(1024, private_key, public_key));
//     H_TEST_ASSERT(private_key.length() > 0 && public_key.length() > 0);
// 
//     npp::OpenSSLRSA sign_rsa( npp::OpenSSLRSA::KT_PRIVATE );
//     H_TEST_ASSERT(sign_rsa.initialize((unsigned char*)private_key.data(), private_key.length()));
//     npp::OpenSSLRSA verify_rsa(npp::OpenSSLRSA::KT_PUBLIC);
//     H_TEST_ASSERT(verify_rsa.initialize((unsigned char*)public_key.data(), public_key.length()));
//     std::string md5 = "D05C916B4D7242f9AC989AC46EC3A0AA";
//     std::string sigret;
//     H_TEST_ASSERT(sign_rsa.sign(npp::OpenSSLRSA::ST_NID_md5, md5.data(), md5.size(), sigret));
//     H_TEST_ASSERT(verify_rsa.verify(npp::OpenSSLRSA::ST_NID_md5, md5.data(), md5.size(), sigret.data(), sigret.size()));
}

#endif

