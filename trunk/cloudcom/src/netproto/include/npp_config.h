#ifndef NETPROTO_NP_CONF_H_
#define NETPROTO_NP_CONF_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/idea_wrapper.h"
#include "netproto/include/openssl_rsa.h"
#include "netproto/include/slrsa_wrapper.h"

#include "netproto/include/singleton.h"

namespace npp
{

    #define s_pNppConfig	( ::npp::NppConfig::getSingletonPtr() )
    class _EXPORT_NETPROTO NppConfig  : public Singleton<NppConfig>
    {
        typedef std::map<int, IDEA>         IDEAMap;
        typedef std::map<int, SimpleRSA>    SimpleRSAMap;
#if H_NPP_PROVIDE_RSA
        typedef std::map<int, OpenSSLRSA > OpenSSLRSAMap;
#endif
    public:
        //! \brief Create an instance
        //! \warning Only can be called in the main function when the program is starting
        //!     Be careful the thread-safe problem
        //! \return NppConfig* - 
        static NppConfig* CreateInstance();

    public:
        NppConfig(bool support_plain, bool sign_data, bool verify_data);

        bool AddIdeaKey(int key_no, const unsigned char key[16]);

        bool AddOpenSSLRSAKey(int key_no, 
            const unsigned char* private_key, const size_t private_key_len,
            const unsigned char* public_key, const size_t public_key_len );

        bool AddSimpleRSAKey(int key_no, 
            const unsigned char* private_key, const size_t private_key_len,
            const unsigned char* public_key, const size_t public_key_len );

        //Query
    public:
        bool support_plain() const;

        bool sign_data() const;

        bool verify_data() const;

        void set_support_plain(bool support_plain_data);

        void set_sign_data(bool sign_data);

        void set_verify_data(bool verify_data);

        OpenSSLRSA* GetOpenSSLRSA(int index);

        SimpleRSA* GetSimpleRSA(int index);

        IDEA* GetIDEA(int index);

        size_t GetOpenSSLRSAKeyCount() const;

        size_t GetSimpleRSAKeyCount() const;

        size_t GetIDEAKeyCount() const;

    protected:
        NppConfig();

    private:
        bool support_plain_;
        bool sign_data_;
        bool verify_data_;

        IDEAMap       idea_map_;
        SimpleRSAMap  slrsa_map_;
#if H_NPP_PROVIDE_RSA
        OpenSSLRSAMap rsa_map_;
#endif
    };

    inline bool NppConfig::support_plain() const 
    {
        return support_plain_;
    }

    inline bool NppConfig::sign_data() const
    {
        return sign_data_;
    }

    inline bool NppConfig::verify_data() const
    {
        return verify_data_;
    }

    inline size_t NppConfig::GetOpenSSLRSAKeyCount() const
    {
        return rsa_map_.size();
    }

    inline size_t NppConfig::GetSimpleRSAKeyCount() const
    {
        return slrsa_map_.size();
    }

    inline size_t NppConfig::GetIDEAKeyCount() const
    {
        return idea_map_.size();
    }

    inline void NppConfig::set_support_plain( bool support_plain_data )
    {
        support_plain_ = support_plain_data;
    }

    inline void NppConfig::set_sign_data( bool sign )
    {
        sign_data_ = sign;
    }

    inline void NppConfig::set_verify_data( bool verify )
    {
        verify_data_ = verify;
    }
}//end of namespace npp


#endif
