#include "netproto/include/test_common.h"

#include "netproto/include/npp_config.h"
#include "netproto/include/v1_message_packer.h"
#include "netproto/include/v1_message_unpacker.h"
#include "netproto/include/idea.h"

#include "npp_config_creator.h"


#include <iostream>

TEST_UNIT(test_func_MessagePackUnitTest_self_test_0)
{
    bool support_plain = false;
    bool sign_pack     = true;
    bool verify_sign   = true;
    npp::NppConfig* npp_config = CreateNppConfig(support_plain, sign_pack, verify_sign);
    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
    for (int i = 1; i <= 4; i++)
    {
        //IDEA
        {
            const char * raw_data = "1234567890";
            size_t raw_data_len = strlen(raw_data);
            npp::IDEA* idea = npp_config->GetIDEA(i);
            H_TEST_ASSERT(idea);
            npp::MemoryDataStream encrypted, decrypted;
            idea->encrypt(raw_data, raw_data_len, encrypted);
            idea->decrypt(encrypted.data(), encrypted.size(), decrypted);
            H_TEST_ASSERT(strncmp(raw_data, decrypted.data(), raw_data_len) == 0);
        }
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
        //OpenSSL RSA
        {
            const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
            size_t raw_data_len = strlen(raw_data);
            npp::OpenSSLRSA* rsa = npp_config->GetOpenSSLRSA(i);
            H_TEST_ASSERT(rsa);
            std::string sigret;
            H_TEST_ASSERT(rsa->sign(npp::OpenSSLRSA::ST_NID_sha1, raw_data, raw_data_len, sigret));
            H_TEST_ASSERT(rsa->verify(npp::OpenSSLRSA::ST_NID_sha1, raw_data, raw_data_len, sigret.data(), sigret.size()));
        }
#endif
        //Simple RSA
        {
            const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
            size_t raw_data_len = strlen(raw_data);
            npp::SimpleRSA* rsa = npp_config->GetSimpleRSA(i);
            H_TEST_ASSERT(rsa);
            std::string sigret;
            H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
            H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
        }
    }
}


TEST_UNIT(test_func_MessagePackUnitTest_server_client_key)
{
    bool support_plain = false;
    bool sign_pack     = true;
    bool verify_sign   = true;
    for (int i = 1; i <= 4; i++)
    {
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
        //OpenSSL RSA
        {
            const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
            size_t raw_data_len = strlen(raw_data);
            std::string sigret;

            {
                //server sign
                {
                    npp::NppConfig* npp_config = CreateServerNppConfig(support_plain, sign_pack, verify_sign);
                    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
                    npp::OpenSSLRSA* rsa = npp_config->GetOpenSSLRSA(i);
                    H_TEST_ASSERT(rsa);
                    H_TEST_ASSERT(rsa->sign(npp::OpenSSLRSA::ST_NID_sha1, raw_data, raw_data_len, sigret));
                    H_TEST_ASSERT(!rsa->verify(npp::OpenSSLRSA::ST_NID_sha1, raw_data, raw_data_len, sigret.data(), sigret.size()));
                }

                //client verify
                {
                    npp::NppConfig* npp_config = CreateClientNppConfig(support_plain, sign_pack, verify_sign);
                    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
                    npp::OpenSSLRSA* rsa = npp_config->GetOpenSSLRSA(i);
                    H_TEST_ASSERT(rsa->verify(npp::OpenSSLRSA::ST_NID_sha1, raw_data, raw_data_len, sigret.data(), sigret.size()));
                }
            }

            {
                //client sign
                {
                    npp::NppConfig* npp_config = CreateClientNppConfig(support_plain, sign_pack, verify_sign);
                    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
                    npp::OpenSSLRSA* rsa = npp_config->GetOpenSSLRSA(i);
                    H_TEST_ASSERT(rsa);
                    H_TEST_ASSERT(rsa->sign(npp::OpenSSLRSA::ST_NID_sha1, raw_data, raw_data_len, sigret));
                    H_TEST_ASSERT(!rsa->verify(npp::OpenSSLRSA::ST_NID_sha1, raw_data, raw_data_len, sigret.data(), sigret.size()));
                }

                //server verify
                {
                    npp::NppConfig* npp_config = CreateServerNppConfig(support_plain, sign_pack, verify_sign);
                    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
                    npp::OpenSSLRSA* rsa = npp_config->GetOpenSSLRSA(i);
                    H_TEST_ASSERT(rsa->verify(npp::OpenSSLRSA::ST_NID_sha1, raw_data, raw_data_len, sigret.data(), sigret.size()));
                }
            }
        }
#endif
        //Simple RSA
        {
            const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
            size_t raw_data_len = strlen(raw_data);
            std::string sigret;

            {
                //server sign
                {
                    npp::NppConfig* npp_config = CreateServerNppConfig(support_plain, sign_pack, verify_sign);
                    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
                    npp::SimpleRSA* rsa = npp_config->GetSimpleRSA(i);
                    H_TEST_ASSERT(rsa);
                    H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                    H_TEST_ASSERT(!rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                }

                //client verify
                {
                    npp::NppConfig* npp_config = CreateClientNppConfig(support_plain, sign_pack, verify_sign);
                    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
                    npp::SimpleRSA* rsa = npp_config->GetSimpleRSA(i);
                    H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                }
            }

            {
                //client sign
                {
                    npp::NppConfig* npp_config = CreateClientNppConfig(support_plain, sign_pack, verify_sign);
                    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
                    npp::SimpleRSA* rsa = npp_config->GetSimpleRSA(i);
                    H_TEST_ASSERT(rsa);
                    H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                    H_TEST_ASSERT(!rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                }

                //server verify
                {
                    npp::NppConfig* npp_config = CreateServerNppConfig(support_plain, sign_pack, verify_sign);
                    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
                    npp::SimpleRSA* rsa = npp_config->GetSimpleRSA(i);
                    H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                }
            }
        }
    }
}



TEST_UNIT(test_func_MessagePackUnitTest_server_client_key1)
{
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
    //OpenSSL RSA
    {
        const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
        size_t raw_data_len = strlen(raw_data);
        std::string sigret;

        {
            //server sign
            {
                npp::OpenSSLRSA* rsa = new npp::OpenSSLRSA();
                H_TEST_ASSERT(rsa->initialize(g_server_rsa_private_key1, g_server_rsa_private_key1_len, g_client_rsa_public_key1, g_client_rsa_public_key1_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }

            //client verify
            {
                npp::OpenSSLRSA* rsa = new npp::OpenSSLRSA();
                H_TEST_ASSERT(rsa->initialize(g_client_rsa_private_key1, g_client_rsa_private_key1_len, g_server_rsa_public_key1, g_server_rsa_public_key1_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }
        }
    }
#endif
    //Simple RSA
    {
        const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
        size_t raw_data_len = strlen(raw_data);
        std::string sigret;

        {
            //server sign
            {
                npp::SimpleRSA* rsa = new npp::SimpleRSA();
                H_TEST_ASSERT(rsa->initialize(g_server_slrsa_private_key1, g_server_slrsa_private_key1_len, g_client_slrsa_public_key1, g_client_slrsa_public_key1_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }

            //client verify
            {
                npp::SimpleRSA* rsa = new npp::SimpleRSA();
                H_TEST_ASSERT(rsa->initialize(g_client_slrsa_private_key1, g_client_slrsa_private_key1_len, g_server_slrsa_public_key1, g_server_slrsa_public_key1_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }
        }
    }
}


TEST_UNIT(test_func_MessagePackUnitTest_server_client_key2)
{
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
    //OpenSSL RSA
    {
        const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
        size_t raw_data_len = strlen(raw_data);
        std::string sigret;

        {
            //server sign
            {
                npp::OpenSSLRSA* rsa = new npp::OpenSSLRSA();
                H_TEST_ASSERT(rsa->initialize(g_server_rsa_private_key2, g_server_rsa_private_key2_len, g_client_rsa_public_key2, g_client_rsa_public_key2_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }

            //client verify
            {
                npp::OpenSSLRSA* rsa = new npp::OpenSSLRSA();
                H_TEST_ASSERT(rsa->initialize(g_client_rsa_private_key2, g_client_rsa_private_key2_len, g_server_rsa_public_key2, g_server_rsa_public_key2_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }
        }
    }
#endif
    //Simple RSA
    {
        const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
        size_t raw_data_len = strlen(raw_data);
        std::string sigret;

        {
            //server sign
            {
                npp::SimpleRSA* rsa = new npp::SimpleRSA();
                H_TEST_ASSERT(rsa->initialize(g_server_slrsa_private_key2, g_server_slrsa_private_key2_len, g_client_slrsa_public_key2, g_client_slrsa_public_key2_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }

            //client verify
            {
                npp::SimpleRSA* rsa = new npp::SimpleRSA();
                H_TEST_ASSERT(rsa->initialize(g_client_slrsa_private_key2, g_client_slrsa_private_key2_len, g_server_slrsa_public_key2, g_server_slrsa_public_key2_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }
        }
    }
}


TEST_UNIT(test_func_MessagePackUnitTest_server_client_key3)
{
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
    //OpenSSL RSA
    {
        const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
        size_t raw_data_len = strlen(raw_data);
        std::string sigret;

        {
            //server sign
            {
                npp::OpenSSLRSA* rsa = new npp::OpenSSLRSA();
                H_TEST_ASSERT(rsa->initialize(g_server_rsa_private_key3, g_server_rsa_private_key3_len, g_client_rsa_public_key3, g_client_rsa_public_key3_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }

            //client verify
            {
                npp::OpenSSLRSA* rsa = new npp::OpenSSLRSA();
                H_TEST_ASSERT(rsa->initialize(g_client_rsa_private_key3, g_client_rsa_private_key3_len, g_server_rsa_public_key3, g_server_rsa_public_key3_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }
        }
    }
#endif
    //Simple RSA
    {
        const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
        size_t raw_data_len = strlen(raw_data);
        std::string sigret;

        {
            //server sign
            {
                npp::SimpleRSA* rsa = new npp::SimpleRSA();
                H_TEST_ASSERT(rsa->initialize(g_server_slrsa_private_key3, g_server_slrsa_private_key3_len, g_client_slrsa_public_key3, g_client_slrsa_public_key3_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }

            //client verify
            {
                npp::SimpleRSA* rsa = new npp::SimpleRSA();
                H_TEST_ASSERT(rsa->initialize(g_client_slrsa_private_key3, g_client_slrsa_private_key3_len, g_server_slrsa_public_key3, g_server_slrsa_public_key3_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }
        }
    }
}


TEST_UNIT(test_func_MessagePackUnitTest_server_client_key4)
{
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
    //OpenSSL RSA
    {
        const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
        size_t raw_data_len = strlen(raw_data);
        std::string sigret;

        {
            //server sign
            {
                npp::OpenSSLRSA* rsa = new npp::OpenSSLRSA();
                H_TEST_ASSERT(rsa->initialize(g_server_rsa_private_key4, g_server_rsa_private_key4_len, g_client_rsa_public_key4, g_client_rsa_public_key4_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }

            //client verify
            {
                npp::OpenSSLRSA* rsa = new npp::OpenSSLRSA();
                H_TEST_ASSERT(rsa->initialize(g_client_rsa_private_key4, g_client_rsa_private_key4_len, g_server_rsa_public_key4, g_server_rsa_public_key4_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }
        }
    }
#endif
    //Simple RSA
    {
        const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
        size_t raw_data_len = strlen(raw_data);
        std::string sigret;

        {
            //server sign
            {
                npp::SimpleRSA* rsa = new npp::SimpleRSA();
                H_TEST_ASSERT(rsa->initialize(g_server_slrsa_private_key4, g_server_slrsa_private_key4_len, g_client_slrsa_public_key4, g_client_slrsa_public_key4_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }

            //client verify
            {
                npp::SimpleRSA* rsa = new npp::SimpleRSA();
                H_TEST_ASSERT(rsa->initialize(g_client_slrsa_private_key4, g_client_slrsa_private_key4_len, g_server_slrsa_public_key4, g_server_slrsa_public_key4_len));
                H_TEST_ASSERT(rsa);
                H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
                H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
                delete rsa;
            }
        }
    }
}



void test_pack_unpack_1(bool sign_pack, bool verify_sign);
void test_pack_unpack_2( bool support_plain, bool sign_pack, bool verify_sign );



TEST_UNIT(test_func_MessagePackUnitTest_encrypt)
{
    test_pack_unpack_1(true, true);
    test_pack_unpack_1(true, false);
    test_pack_unpack_1(false, false);
}

TEST_UNIT(test_func_MessagePackUnitTest_all)
{
    test_pack_unpack_2(false, true, true);
    test_pack_unpack_2(false, true, false);
    test_pack_unpack_2(false, false, false);

    test_pack_unpack_2(true, true, true);
    test_pack_unpack_2(true, true, false);
    test_pack_unpack_2(true, false, false);
}

void test_pack_unpack_1( bool sign_pack, bool verify_sign )
{
    npp::NppConfig* npp_config = CreateNppConfig(false, sign_pack, verify_sign);
    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
    const char * raw_data = "1234567890";
    size_t raw_data_len = strlen(raw_data);

    char packed_data[1024] = {};
    size_t packed_data_len = sizeof(packed_data);
    npp::v1::MessagePacker packer;
    H_TEST_ASSERT(packer.Pack(raw_data, raw_data_len, packed_data, packed_data_len));

    npp::v1::MessageUnpacker unpacker;
    H_TEST_ASSERT(unpacker.Unpack(packed_data, packed_data_len));
    H_TEST_ASSERT(H_ALIGN(raw_data_len, 8) == unpacker.Size());
    H_TEST_ASSERT(memcmp(raw_data, unpacker.Data(), raw_data_len) == 0);
}

void test_pack_unpack_2( bool support_plain, bool sign_pack, bool verify_sign )
{
    npp::NppConfig* npp_config = CreateNppConfig(support_plain, sign_pack, verify_sign);
    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
    const char * raw_data = "1234567890";
    size_t raw_data_len = strlen(raw_data);

    char packed_data[1024] = {};
    size_t packed_data_len = sizeof(packed_data);
    npp::v1::MessagePacker packer;
    H_TEST_ASSERT(packer.Pack(raw_data, raw_data_len, packed_data, packed_data_len));

    npp::v1::MessageUnpacker unpacker;
    H_TEST_ASSERT(unpacker.Unpack(packed_data, packed_data_len));
    npp::Message::NetHeader& net_header = const_cast<npp::Message::NetHeader&>(unpacker.net_header());
    npp::Message::NppHeaderV1& npp_header = const_cast<npp::Message::NppHeaderV1&>(unpacker.npp_header());
    net_header.Init();
    npp_header.Init();
  
    if (support_plain)
    {
        npp_header.encrypt_method_ = npp::Message::kNoSymmetricEncrypt;
    }
    else
    {
        npp_header.encrypt_method_ = npp::Message::kIDEASymmetricEncrypt;
    }

    for (int encrypt_key_no = 1; encrypt_key_no <= 4; ++encrypt_key_no)
    {
        for (int sign_key_no = 1; sign_key_no <= 4; sign_key_no++)
        {
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
            for (int sign_method = 0; sign_method <= npp::Message::kOpenSSLRSA2; ++sign_method)
#else
            for (int sign_method = npp::Message::kSimpleRSA; sign_method <= npp::Message::kSimpleRSA; ++sign_method)
#endif
            {
                npp_header.encrypt_key_no_ = encrypt_key_no;
                npp_header.sign_key_no_    = sign_key_no;
                npp_header.sign_method_    = sign_method;
                net_header.message_id_     = rand() % 65536;

                packed_data_len = sizeof(packed_data);
                npp::v1::MessagePacker packer1(&unpacker);
                H_TEST_ASSERT(packer1.Pack(raw_data, raw_data_len, packed_data, packed_data_len));

                H_TEST_ASSERT(npp::v1::MessagePacker::GetMessageID(packed_data) == net_header.message_id());

                npp::v1::MessageUnpacker unpacker1;
                H_TEST_ASSERT(unpacker1.Unpack(packed_data, packed_data_len));
                H_TEST_ASSERT(unpacker1.last_error() == npp::Message::kNoError);
                if (npp_header.encrypt_method_ == npp::Message::kIDEASymmetricEncrypt)
                {
                    H_TEST_ASSERT(H_ALIGN(raw_data_len, 8) == unpacker1.Size());
                }
                H_TEST_ASSERT(memcmp(raw_data, unpacker1.Data(), raw_data_len) == 0);
                H_TEST_ASSERT(unpacker1.net_header().message_id_ == net_header.message_id_);
                H_TEST_ASSERT(unpacker1.npp_header().encrypt_key_no() + 1 == npp_header.encrypt_key_no() || unpacker1.npp_header().encrypt_key_no() == npp_header.encrypt_key_no() + 1);
                H_TEST_ASSERT(unpacker1.npp_header().sign_key_no() + 1 == npp_header.sign_key_no() || unpacker1.npp_header().sign_key_no() == npp_header.sign_key_no() + 1);
            }
        }
    }
}

TEST_UNIT(test_func_MessagePackUnitTest_message_packer_CalculateSignKeyNum)
{
#ifdef _NETPROTO_TEST
    npp::v1::MessagePacker packer;
    npp::Message::NppHeaderV1 h;
    h.Init();
    for (uint8_t i = 1; i < 14; i++)
    {
        {
            h.set_encrypt_key_no(i);
            uint8_t orignal = h.encrypt_key_no();
            packer.ReverseSignKeyNum(h);
            H_TEST_ASSERT((orignal + 1)/2 == (h.encrypt_key_no() + 1)/2);
            if (orignal % 2 == 0)//2,4,6,8...
            {
                H_TEST_ASSERT(orignal == h.encrypt_key_no() + 1);
            }
            else
            {
                H_TEST_ASSERT(orignal + 1 == h.encrypt_key_no());
            }
        }

        {
            h.set_sign_key_no(i);
            uint8_t orignal = h.sign_key_no();
            packer.ReverseSignKeyNum(h);
            H_TEST_ASSERT((orignal + 1)/2 == (h.sign_key_no() + 1)/2);
            if (orignal % 2 == 0)//2,4,6,8...
            {
                H_TEST_ASSERT(orignal == h.sign_key_no() + 1);
            }
            else
            {
                H_TEST_ASSERT(orignal + 1 == h.sign_key_no());
            }
        }
    }
#endif//_NETPROTO_TEST
}

//TODO test of 512 length key for MID Engine



namespace
{
    static const size_t test_effective_count = 100000;

    void test_effective_openssl()
    {
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
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

        const char* data = "asdfjlasjflasjdflajsdlkfjasdlkfajsdlkfjas;dlkf";
        size_t data_len = strlen(data);

        unsigned char sigret[2048] = {0};
        size_t siglen  = sizeof(sigret);

        time_t start = time(NULL);
        for (size_t i = 0; i < test_effective_count; ++i)
        {
            ret = rsa.sign( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, sigret, &siglen );
            H_TEST_ASSERT(ret);
        }
        time_t end = time(NULL);
        time_t sign_cost = end - start;

        start = time(NULL);
        for (size_t i = 0; i < test_effective_count; ++i)
        {
            ret = rsa.verify( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, sigret, siglen );
            H_TEST_ASSERT(ret);
        }
        end = time(NULL);
        time_t verify_cost = end - start;

        std::cout << "openssl sign_cost=" << sign_cost << std::endl;
        std::cout << "openssl verify_cost=" << verify_cost << std::endl;
        std::cout << "openssl sign_cost/verify_cost=" << (double)sign_cost/(double)verify_cost << std::endl;

        std::string ss;
        H_TEST_ASSERT(rsa.sign( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, ss ));
        H_TEST_ASSERT(rsa.verify( npp::OpenSSLRSA::ST_NID_sha1, (unsigned char*)data, data_len, ss.data(), ss.size() ));
#endif
    }

    void test_effective_slrsa()
    {
        bool support_plain = false;
        bool sign_pack     = true;
        bool verify_sign   = true;
        npp::NppConfig* npp_config = CreateNppConfig(support_plain, sign_pack, verify_sign);
        npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);

        const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
        size_t raw_data_len = strlen(raw_data);
        npp::SimpleRSA* rsa = npp_config->GetSimpleRSA(2);
        H_TEST_ASSERT(rsa);
        std::string sigret;
        H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
        H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));

        time_t start = time(NULL);
        for (size_t i = 0; i < test_effective_count; ++i)
        {
            H_TEST_ASSERT(rsa->sign(raw_data, raw_data_len, sigret));
        }
        time_t end = time(NULL);
        time_t sign_cost = end - start;

        start = time(NULL);
        for (size_t i = 0; i < test_effective_count; ++i)
        {
            H_TEST_ASSERT(rsa->verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
        }
        end = time(NULL);
        time_t verify_cost = end - start;

        std::cout << "slrsa sign_cost=" << sign_cost << std::endl;
        std::cout << "slrsa verify_cost=" << verify_cost << std::endl;
        std::cout << "slrsa sign_cost/verify_cost=" << (double)sign_cost/(double)verify_cost << std::endl;
    }

    void test_effective_openssl_public_encrypt_private_decrypt()
    {
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
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

        const char* data = "asdfjlasjflasjdflajsdlkfjasdlkfajsdlkfjas;dlkf";
        size_t data_len = strlen(data);

        unsigned char sigret[2048] = {0};
        size_t siglen  = sizeof(sigret);

        time_t start = time(NULL);
        for (size_t i = 0; i < test_effective_count; ++i)
        {
            ret = rsa.PublicEncrypt((unsigned char*)data, data_len, sigret, &siglen );
            H_TEST_ASSERT(ret);
        }
        time_t end = time(NULL);
        time_t sign_cost = end - start;

        start = time(NULL);
        unsigned char plain_data[2048] = {};
        size_t plain_data_len = sizeof(plain_data);
        for (size_t i = 0; i < test_effective_count; ++i)
        {
            plain_data_len = sizeof(plain_data);
            ret = rsa.PrivateDecrypt((unsigned char*)sigret, siglen, plain_data, &plain_data_len );
            H_TEST_ASSERT(ret);
        }
        end = time(NULL);
        time_t verify_cost = end - start;

        std::cout << "openssl public_encrypt cost=" << sign_cost << std::endl;
        std::cout << "openssl private_decrypt cost=" << verify_cost << std::endl;
        std::cout << "openssl public_encrypt/private_decrypt=" << (double)sign_cost/(double)verify_cost << std::endl;
#endif
    }
}

TEST_UNIT(test_func_MessagePackUnitTest_test_effective)
{
//#define H_TEST_EFFECTIVE
#ifdef H_TEST_EFFECTIVE
    test_effective_openssl_public_encrypt_private_decrypt();
     test_effective_slrsa();
     test_effective_openssl();
    //test_effective_slrsa_public_encrypt_private_decrypt();
#endif
}



