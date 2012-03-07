
#include "netproto/include/test_common.h"
#include "netproto/include/openssl_rsa.h"

#include "test_rsa_self_pair_key.h"

#if H_NPP_PROVIDE_OPENSSL_RSA

namespace
{
    void test1(const char* data)
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

        npp::OpenSSLRSA rsa;
        H_TEST_ASSERT(rsa.initialize(privatekey, privatekey_len, publickey,  publickey_len));

        size_t data_len = strlen(data);

        unsigned char sigret[2048] = {0};
        size_t siglen  = sizeof(sigret);

        ret = rsa.sign( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, sigret, &siglen );
        H_TEST_ASSERT(ret);
        ret = rsa.verify( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, sigret, siglen );
        H_TEST_ASSERT(ret);

        std::string ss;
        H_TEST_ASSERT(rsa.sign( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, ss ));
        H_TEST_ASSERT(rsa.verify( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, ss.data(), ss.size() ));
    }


    void test_encrypt_decrypt(const char* data)
    {
        npp::OpenSSLRSA rsa;
        H_TEST_ASSERT(rsa.initialize(g_rsa_private_key1, g_rsa_private_key1_len, g_rsa_public_key1,  g_rsa_public_key1_len));
        size_t data_len = strlen(data);

        unsigned char sigret[2048] = {0};
        size_t siglen = 0;
        bool ret = rsa.publicEncrypt((unsigned char*)data, data_len, sigret, &siglen );
        H_TEST_ASSERT(!ret);
        siglen = sizeof(sigret);
        ret = rsa.publicEncrypt((unsigned char*)data, data_len, sigret, &siglen );
        H_TEST_ASSERT(ret);

        unsigned char plain_data[2048] = {0};
        size_t plain_data_len = 0;
        ret = rsa.privateDecrypt((unsigned char*)sigret, siglen, plain_data, &plain_data_len );
        H_TEST_ASSERT(!ret);
        plain_data_len = sizeof(plain_data);
        ret = rsa.privateDecrypt((unsigned char*)sigret, siglen, plain_data, &plain_data_len );
        H_TEST_ASSERT(ret);
        H_TEST_ASSERT(memcmp(data, plain_data, data_len) == 0);
    }
}

TEST_UNIT(openssl_rsa_test_1)
{
    std::string test_datas[] = {
        "0",
        "01",
        "012",
        "0123",
        "01234",
        "012345",
        "0123456",
        "01234567",
        "012345678",
        "0123456789",
        "0123456789a",
        "0123456789ab",
        "0123456789abc",
        "0123456789abcd",
        "0123456789abcdf0",
        "0123456789abcdf12",
        "0123456789abcdf1231",
        "0123456789abcdf1231412412",
        "0123456789arqwerbcd",
        "0123456789aqwerqwerbcdf0"
    };

    for (size_t i = 0; i < H_ARRAYSIZE(test_datas); ++i)
    {
        test1(test_datas[i].data());
        test_encrypt_decrypt(test_datas[i].data());
    }
}

#endif

