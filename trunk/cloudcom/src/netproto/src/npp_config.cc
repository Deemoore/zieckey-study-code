#include "netproto/include/npp_config.h"


namespace npp
{

    template<> NppConfig* Singleton<NppConfig>::ms_Singleton = NULL;

    NppConfig* NppConfig::CreateInstance()
    {
        if (NppConfig::getSingletonPtr())
        {
            return static_cast<NppConfig*>(NppConfig::getSingletonPtr());
        }
        else
        {
            return new NppConfig();
        }
    }

    NppConfig::NppConfig()
        : support_plain_(false), sign_data_(true), verify_data_(true)
    {
    }

    NppConfig::NppConfig( bool plain, bool sign, bool verify )
        : support_plain_(plain), sign_data_(sign), verify_data_(verify)
    {
    }

    bool NppConfig::AddIdeaKey( int key_no, const unsigned char key[16] )
    {
        IDEA& idea = idea_map_[key_no];
        return idea.initialize(key);
    }

    bool NppConfig::AddOpenSSLRSAKey( int key_no, const unsigned char* private_key, const size_t private_key_len, const unsigned char* public_key, const size_t public_key_len )
    {
        OpenSSLRSA& rsa = rsa_map_[key_no];
        return rsa.initialize(private_key, private_key_len, public_key, public_key_len);
    }

    bool NppConfig::AddSimpleRSAKey( int key_no, const unsigned char* private_key, const size_t private_key_len, const unsigned char* public_key, const size_t public_key_len )
    {
        SimpleRSA& rsa = slrsa_map_[key_no];
        return rsa.initialize(private_key, private_key_len, public_key, public_key_len);
    }

    OpenSSLRSA* NppConfig::GetOpenSSLRSA( int index )
    {
        OpenSSLRSAMap::iterator it = rsa_map_.find(index);
        if (it != rsa_map_.end())
        {
            return &it->second;
        }

        return NULL;
    }

    SimpleRSA* NppConfig::GetSimpleRSA( int index )
    {
        SimpleRSAMap::iterator it = slrsa_map_.find(index);
        if (it != slrsa_map_.end())
        {
            return &it->second;
        }

        return NULL;
    }

    IDEA* NppConfig::GetIDEA( int index )
    {
        IDEAMap::iterator it = idea_map_.find(index);
        if (it != idea_map_.end())
        {
            return &it->second;
        }

        return NULL;
    }
}
