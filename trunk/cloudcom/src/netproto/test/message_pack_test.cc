
#include "netproto/include/test_common.h"

#include "netproto/include/npp_config.h"
#include "netproto/include/message_packer.h"
#include "netproto/include/message_unpacker.h"
#include "netproto/include/idea_wrapper.h"

#include "rsa_test_key.h"
#include "idea_key.h"

#include <iostream>

namespace npp { namespace ext {

    //! Name: auto_delete
    template<class T>
    struct auto_delete
    {
        T*& ptr_ref_to_be_deleted_;
        auto_delete( T*& pointer )
            : ptr_ref_to_be_deleted_( pointer )
        {
        }

        ~auto_delete()
        {
            if ( ptr_ref_to_be_deleted_ )
            {
                delete ptr_ref_to_be_deleted_;
                ptr_ref_to_be_deleted_ = 0;
            }
        }

        void noop() {}
    private:
        auto_delete(const auto_delete&);
        auto_delete&operator=(const auto_delete&);
    };

    template<class T>
    struct auto_delete<T*>; //! \note Leave it be. Do not write any implementation
    }
}

namespace npp { namespace ext {
    template<> inline
        auto_delete< npp::NppConfig >::~auto_delete()
    {
        if ( ptr_ref_to_be_deleted_ )
        {
            delete ptr_ref_to_be_deleted_;
            ptr_ref_to_be_deleted_ = NULL;
        }
    }
}
}

namespace
{
    npp::NppConfig* CreateNppConfig(bool support_plain, bool sign_pack, bool verify_sign)
    {
        npp::NppConfig* npp_config = new npp::NppConfig(support_plain, sign_pack, verify_sign);
#define H_ADD_KEY(no) {\
        npp_config->AddIdeaKey(no, idea_key##no);\
        npp_config->AddSimpleRSAKey(no, g_slrsa_private_key##no, g_slrsa_private_key##no##_len, g_slrsa_public_key##no, g_slrsa_public_key##no##_len);\
        npp_config->AddOpenSSLRSAKey(no, g_rsa_private_key##no, g_rsa_private_key##no##_len, g_rsa_public_key##no, g_rsa_public_key##no##_len);\
        }

        H_ADD_KEY(1);
        H_ADD_KEY(2);
        H_ADD_KEY(3);
        H_ADD_KEY(4);

        return npp_config;
    }
}

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
    npp::MessagePacker packer;
    H_TEST_ASSERT(packer.Pack(raw_data, raw_data_len, packed_data, packed_data_len));

    npp::MessageUnpacker unpacker;
    H_TEST_ASSERT(unpacker.Unpack(packed_data, packed_data_len));
    H_TEST_ASSERT(H_ALIGN(raw_data_len, 8) == unpacker.Size());
    H_TEST_ASSERT(strncmp(raw_data, unpacker.Data(), raw_data_len) == 0);
}

void test_pack_unpack_2( bool support_plain, bool sign_pack, bool verify_sign )
{
    npp::NppConfig* npp_config = CreateNppConfig(support_plain, sign_pack, verify_sign);
    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
    const char * raw_data = "1234567890";
    size_t raw_data_len = strlen(raw_data);

    npp::MessageUnpacker unpacker;
    npp::Message::NetHeader& net_header = const_cast<npp::Message::NetHeader&>(unpacker.net_header());
    npp::Message::NppHeader& npp_header = const_cast<npp::Message::NppHeader&>(unpacker.npp_header());
    net_header.Init();
    npp_header.Init();
  
    if (support_plain)
    {
        npp_header.encrypt_method_ = npp::Message::kNoEncrypt;
    }
    else
    {
        npp_header.encrypt_method_ = npp::Message::kIDEAEncrypt;
    }

    for (int encrypt_key_no = 1; encrypt_key_no <= 4; ++encrypt_key_no)
    {
        for (int sign_key_no = 1; sign_key_no <= 4; sign_key_no++)
        {
            for (int sign_method = 0; sign_method <= npp::Message::kOpenSSLRSA2; ++sign_method)
            {
                npp_header.encrypt_key_no_ = encrypt_key_no;
                npp_header.sign_key_no_    = sign_key_no;
                npp_header.sign_method_    = sign_method;
                net_header.message_id_     = rand() % 65536;

                char packed_data[1024] = {};
                size_t packed_data_len = sizeof(packed_data);
                npp::MessagePacker packer1(&unpacker);
                H_TEST_ASSERT(packer1.Pack(raw_data, raw_data_len, packed_data, packed_data_len));

                npp::MessageUnpacker unpacker1;
                H_TEST_ASSERT(unpacker1.Unpack(packed_data, packed_data_len));
                if (npp_header.encrypt_method_ == npp::Message::kIDEAEncrypt)
                {
                    H_TEST_ASSERT(H_ALIGN(raw_data_len, 8) == unpacker1.Size());
                }
                H_TEST_ASSERT(strncmp(raw_data, unpacker1.Data(), raw_data_len) == 0);
                H_TEST_ASSERT(unpacker1.net_header().message_id_ == net_header.message_id_);
            }
        }
    }
}

