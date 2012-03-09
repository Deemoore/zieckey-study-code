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
    void test_symmetric_encrypt_1(npp::SymmetricEncryptor* e, const std::string& data)
    {
        char   encrypt_buf[2048] = {};
        size_t encrypt_buf_len = sizeof(encrypt_buf);

        bool ret = e->Encrypt(data.data(), data.size(), encrypt_buf, encrypt_buf_len);
        H_TEST_ASSERT(ret);

        char   decrypt_buf[2048] = {};
        size_t decrypt_buf_len = sizeof(decrypt_buf);
        ret = e->Decrypt(encrypt_buf, encrypt_buf_len, decrypt_buf, decrypt_buf_len);
        H_TEST_ASSERT(ret);
        H_TEST_ASSERT(decrypt_buf_len == data.size());
        H_TEST_ASSERT(memcmp(data.data(), decrypt_buf, data.size()) == 0);
    }
}


TEST_UNIT(test_symmetric_encrypt_1)
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
        for (int key_no = 1; key_no <= 4; key_no++)
        {
            for (int method = npp::Message::kIDEASymmetricEncrypt ; method < npp::Message::kSymmetricEncryptMethodNum; method++)
            {
                npp::SymmetricEncryptor* e = npp::SymmetricEncryptorFactory::CreateSymmetricEncryptor(method);
                std::string key = e->CreateRandomKey();
                e->Initialize((unsigned char*)key.data(), key.size());
                H_TEST_ASSERT(e);
                test_symmetric_encrypt_1(e, test_datas[i]);
                delete e;
            }
        }
    }
}