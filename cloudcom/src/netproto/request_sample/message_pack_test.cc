
#include "netproto/include/test_common.h"

#include "netproto/include/npp_config.h"
#include "netproto/include/message_packer.h"
#include "netproto/include/message_unpacker.h"
#include "netproto/include/idea_wrapper.h"

#include "test_rsa_self_pair_key.h"
#include "test_client_rsa_key.h"
#include "test_server_rsa_key.h"
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

#undef  H_ADD_KEY

        return npp_config;
    }

    npp::NppConfig* CreateServerNppConfig(bool support_plain, bool sign_pack, bool verify_sign)
    {
        npp::NppConfig* npp_config = new npp::NppConfig(support_plain, sign_pack, verify_sign);
#define H_ADD_KEY(no) {\
            npp_config->AddIdeaKey(no, idea_key##no);\
            npp_config->AddSimpleRSAKey(no, g_server_slrsa_private_key##no, g_server_slrsa_private_key##no##_len, g_server_slrsa_public_key##no, g_server_slrsa_public_key##no##_len);\
            npp_config->AddOpenSSLRSAKey(no, g_server_rsa_private_key##no, g_server_rsa_private_key##no##_len, g_server_rsa_public_key##no, g_server_rsa_public_key##no##_len);\
        }

        H_ADD_KEY(1);
        H_ADD_KEY(2);
        H_ADD_KEY(3);
        H_ADD_KEY(4);

#undef  H_ADD_KEY

        return npp_config;
    }

    npp::NppConfig* CreateClientNppConfig(bool support_plain, bool sign_pack, bool verify_sign)
    {
        npp::NppConfig* npp_config = new npp::NppConfig(support_plain, sign_pack, verify_sign);
#define H_ADD_KEY(no) {\
            npp_config->AddIdeaKey(no, idea_key##no);\
            npp_config->AddSimpleRSAKey(no, g_client_slrsa_private_key##no, g_client_slrsa_private_key##no##_len, g_client_slrsa_public_key##no, g_client_slrsa_public_key##no##_len);\
            npp_config->AddOpenSSLRSAKey(no, g_client_rsa_private_key##no, g_client_rsa_private_key##no##_len, g_client_rsa_public_key##no, g_client_rsa_public_key##no##_len);\
        }

        H_ADD_KEY(1);
        H_ADD_KEY(2);
        H_ADD_KEY(3);
        H_ADD_KEY(4);

#undef  H_ADD_KEY

        return npp_config;
    }
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
