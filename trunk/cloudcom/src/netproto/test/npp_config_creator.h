#ifndef _NETPROTO_TEST_NPP_CONFIG_CREATOR_H_
#define _NETPROTO_TEST_NPP_CONFIG_CREATOR_H_

#include "test_rsa_self_pair_key.h"
#include "test_client_rsa_key.h"
#include "test_server_rsa_key.h"
#include "idea_key.h"

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
    static npp::NppConfig* CreateNppConfig(bool support_plain, bool sign_pack, bool verify_sign)
    {
        npp::NppConfig* npp_config = new npp::NppConfig(support_plain, sign_pack, verify_sign);
#if H_NPP_PROVIDE_OPENSSL_RSA
#define H_ADD_KEY(no) {\
    npp_config->AddIdeaKey(no, idea_key##no);\
    npp_config->AddSimpleRSAKey(no, g_slrsa_private_key##no, g_slrsa_private_key##no##_len, g_slrsa_public_key##no, g_slrsa_public_key##no##_len);\
    npp_config->AddOpenSSLRSAKey(no, g_rsa_private_key##no, g_rsa_private_key##no##_len, g_rsa_public_key##no, g_rsa_public_key##no##_len);\
        }
#else
#define H_ADD_KEY(no) {\
    npp_config->AddIdeaKey(no, idea_key##no);\
    npp_config->AddSimpleRSAKey(no, g_slrsa_private_key##no, g_slrsa_private_key##no##_len, g_slrsa_public_key##no, g_slrsa_public_key##no##_len);\
        }
#endif

        H_ADD_KEY(1);
        H_ADD_KEY(2);
        H_ADD_KEY(3);
        H_ADD_KEY(4);

#undef  H_ADD_KEY

        return npp_config;
    }

    static npp::NppConfig* CreateServerNppConfig(bool support_plain, bool sign_pack, bool verify_sign)
    {
        npp::NppConfig* npp_config = new npp::NppConfig(support_plain, sign_pack, verify_sign);
#if H_NPP_PROVIDE_OPENSSL_RSA
#define H_ADD_KEY(no) {\
    npp_config->AddIdeaKey(no, idea_key##no);\
    npp_config->AddSimpleRSAKey(no, g_server_slrsa_private_key##no, g_server_slrsa_private_key##no##_len, g_server_slrsa_public_key##no, g_server_slrsa_public_key##no##_len);\
    npp_config->AddOpenSSLRSAKey(no, g_server_rsa_private_key##no, g_server_rsa_private_key##no##_len, g_server_rsa_public_key##no, g_server_rsa_public_key##no##_len);\
        }
#else
#define H_ADD_KEY(no) {\
    npp_config->AddIdeaKey(no, idea_key##no);\
    npp_config->AddSimpleRSAKey(no, g_server_slrsa_private_key##no, g_server_slrsa_private_key##no##_len, g_server_slrsa_public_key##no, g_server_slrsa_public_key##no##_len);\
        }
#endif

        H_ADD_KEY(1);
        H_ADD_KEY(2);
        H_ADD_KEY(3);
        H_ADD_KEY(4);

#undef  H_ADD_KEY

        return npp_config;
    }

    static npp::NppConfig* CreateClientNppConfig(bool support_plain, bool sign_pack, bool verify_sign)
    {
        npp::NppConfig* npp_config = new npp::NppConfig(support_plain, sign_pack, verify_sign);
#if H_NPP_PROVIDE_OPENSSL_RSA
#define H_ADD_KEY(no) {\
    npp_config->AddIdeaKey(no, idea_key##no);\
    npp_config->AddSimpleRSAKey(no, g_client_slrsa_private_key##no, g_client_slrsa_private_key##no##_len, g_client_slrsa_public_key##no, g_client_slrsa_public_key##no##_len);\
    npp_config->AddOpenSSLRSAKey(no, g_client_rsa_private_key##no, g_client_rsa_private_key##no##_len, g_client_rsa_public_key##no, g_client_rsa_public_key##no##_len);\
        }
#else
#define H_ADD_KEY(no) {\
    npp_config->AddIdeaKey(no, idea_key##no);\
    npp_config->AddSimpleRSAKey(no, g_client_slrsa_private_key##no, g_client_slrsa_private_key##no##_len, g_client_slrsa_public_key##no, g_client_slrsa_public_key##no##_len);\
        }
#endif

        H_ADD_KEY(1);
        H_ADD_KEY(2);
        H_ADD_KEY(3);
        H_ADD_KEY(4);

#undef  H_ADD_KEY

        return npp_config;
    }
}

#endif


