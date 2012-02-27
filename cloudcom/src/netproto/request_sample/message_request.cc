
//#include "netproto/include/test_common.h"

#include "netproto/include/npp_config.h"
#include "netproto/include/message_packer.h"
#include "netproto/include/message_unpacker.h"
#include "netproto/include/idea_wrapper.h"

#include "test_rsa_self_pair_key.h"
#include "test_client_rsa_key.h"
#include "test_server_rsa_key.h"
#include "idea_key.h"

#include "message_request.h"

#include <iostream>
#include <sstream>

#include "curl/curl.h"

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

size_t curl_write_func( void* ptr, size_t size, size_t nmemb, void *usrptr )
{
    std::stringstream* ss = ( std::stringstream* ) usrptr;
    ss->write( (char*)ptr, size * nmemb );
    return nmemb * size;
}

bool do_curl_post(const std::string& server_url, const std::string& request_data, std::string& result)
{
    std::stringstream ss;
    CURL *m_pEasyHeandle = curl_easy_init();

    ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_URL, server_url.data() );
    ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_NOSIGNAL, (long)1L );
    ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_TIMEOUT, (long)10000L );

    ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_WRITEFUNCTION, curl_write_func );
    ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_WRITEDATA, &ss );//this will be used in writeFunc as the usrptr
    ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_CONNECTTIMEOUT, (long)10000L );

    ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_POSTFIELDS, request_data.data() );
    ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_POSTFIELDSIZE, request_data.size() );
    curl_slist* m_curl_slist = NULL;
    m_curl_slist = ::curl_slist_append( m_curl_slist, "Expect:" );
    ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_HTTPHEADER, m_curl_slist );

    CURLcode curl_code = ::curl_easy_perform(m_pEasyHeandle);
    curl_slist_free_all( m_curl_slist );
    if (CURLE_OK == curl_code)
    {
        result = ss.str();
        return true;
    }
    else
    {
        result = curl_easy_strerror(curl_code);
        fprintf(stderr, "curl_easy_perform ret=%d [%s]\n", curl_code, result.data());
        return false;
    }
}

bool do_http_request(const std::string& server_url, const std::string& request_data, std::string& result)
{
    npp::NppConfig* npp_config = CreateNppConfig(false, true, true);
    npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
    const char * raw_data = request_data.data();
    size_t raw_data_len = request_data.size();

    char packed_data[1024] = {};
    size_t packed_data_len = sizeof(packed_data);
    npp::MessagePacker packer;
    assert(packer.Pack(raw_data, raw_data_len, packed_data, packed_data_len));

    std::string server_resp_encrypt_data;
    if (do_curl_post(server_url, std::string(packed_data, packed_data_len), server_resp_encrypt_data))
    {
        npp::MessageUnpacker unpacker;
        if (unpacker.Unpack(server_resp_encrypt_data.data(), server_resp_encrypt_data.size()))
        {
            result = std::string(unpacker.Data(), unpacker.Size());
            return true;
        }
        else
        {
            result = unpacker.strerror();
            return false;
        }
    }
    else
    {
        result = std::string("Http request failed:") + result;
        return false;
    }
}
