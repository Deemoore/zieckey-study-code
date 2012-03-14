#include "netproto/include/test_common.h"

#include "netproto/include/npp_config.h"
#include "netproto/include/v1_message_packer.h"
#include "netproto/include/v1_message_unpacker.h"
#include "netproto/include/idea.h"
#include "netproto/include/v2c_request_packer.h"
#include "netproto/include/v2s_request_unpacker.h"
#include "npp_config_creator.h"

namespace
{
    void test_public_encrypt_1(npp::AsymmetricEncryptor* e, const std::string& data)
    {
        char   encrypt_buf[2048] = {};
        size_t encrypt_buf_len = sizeof(encrypt_buf);

        bool ret = e->PublicEncrypt(data.data(), data.size(), encrypt_buf, &encrypt_buf_len);
        H_TEST_ASSERT(encrypt_buf_len == e->GetEncryptDataLength());
        H_TEST_ASSERT(ret);

        char   decrypt_buf[2048] = {};
        size_t decrypt_buf_len = sizeof(decrypt_buf);
        ret = e->PrivateDecrypt(encrypt_buf, encrypt_buf_len, decrypt_buf, &decrypt_buf_len);
        H_TEST_ASSERT(ret);

        H_TEST_ASSERT(decrypt_buf_len == data.size());
        H_TEST_ASSERT(memcmp(data.data(), decrypt_buf, data.size()) == 0);
    }

    void test_private_encrypt_2(npp::AsymmetricEncryptor* e, const std::string& data)
    {
        char   encrypt_buf[2048] = {};
        size_t encrypt_buf_len = sizeof(encrypt_buf);

        bool ret = e->PrivateEncrypt(data.data(), data.size(), encrypt_buf, &encrypt_buf_len);
        H_TEST_ASSERT(ret);

        char   decrypt_buf[2048] = {};
        size_t decrypt_buf_len = sizeof(decrypt_buf);
        ret = e->PublicDecrypt(encrypt_buf, encrypt_buf_len, decrypt_buf, &decrypt_buf_len);
        H_TEST_ASSERT(ret);
        H_TEST_ASSERT(decrypt_buf_len == data.size());
        H_TEST_ASSERT(memcmp(data.data(), decrypt_buf, data.size()) == 0);
    }
}


TEST_UNIT(test_asymmetric_encrypt_1)
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

    bool support_plain = false;
    bool sign_pack     = true;
    bool verify_sign   = true;
    npp::NppConfig* npp_config = CreateNppConfig(support_plain, sign_pack, verify_sign);
    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
    for (size_t i = 0; i < H_ARRAYSIZE(test_datas); ++i)
    {
        for (int key_no = 1; key_no <= 2; key_no++)
        {
            for (int method = npp::Message::kOpenSSLRSA0; method < npp::Message::kAsymmetricEncryptMethodNum; method++)
            {
                npp::AsymmetricEncryptor* e = npp::AsymmetricEncryptorFactory::GetAsymmetricEncryptor(method, key_no);
                H_TEST_ASSERT(e);
                test_public_encrypt_1(e, test_datas[i]);
                test_private_encrypt_2(e, test_datas[i]);
            }
        }
    }
}

namespace
{
    std::string CreateRondomString(size_t len)
    {
        std::string ret;
        ret.resize(len);
        for (size_t i = 0; i < len; ++i)
        {
            ret[0] = (char)(rand() % 256);
        }
        return ret;
    }
}

TEST_UNIT(test_asymmetric_encrypt_2)
{
    bool support_plain = false;
    bool sign_pack     = true;
    bool verify_sign   = true;
    npp::NppConfig* npp_config = CreateNppConfig(support_plain, sign_pack, verify_sign);
    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
    for (size_t i = 1; i < 40; i = i + 3)
    {
        for (int key_no = 1; key_no <= 4; key_no++)
        {
            for (int method = npp::Message::kOpenSSLRSA0; method < npp::Message::kAsymmetricEncryptMethodNum; method++)
            {
                npp::AsymmetricEncryptor* e = npp::AsymmetricEncryptorFactory::GetAsymmetricEncryptor(method, key_no);
                H_TEST_ASSERT(e);
                test_public_encrypt_1(e, CreateRondomString(i));
                test_private_encrypt_2(e, CreateRondomString(i));
            }
        }
    }
}



