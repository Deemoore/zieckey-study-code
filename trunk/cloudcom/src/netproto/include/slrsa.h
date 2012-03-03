#ifndef _NETPROTO_SLRSA_H_
#define _NETPROTO_SLRSA_H_


#include "netproto/include/config.h"
#include "netproto/include/inner_pre.h"
#include "slrsa/slrsa.h"

namespace npp
{
    class _EXPORT_NETPROTO SimpleRSA
    {
    public:
        SimpleRSA(){}

        ~SimpleRSA(){}

        //! \brief Initialize the rsa
        //! \param[in] - const unsigned char * private_key
        //! \param[in] - const size_t key_len
        //! \return - bool return true if successfully
        bool initialize(const unsigned char* private_key, const size_t private_key_len,
            const unsigned char* public_key, const size_t public_key_len);

        //! \brief signs the message digest m of size m_len using the private
        //!     key rsa. It stores the signature in sigret
        //!     and the signature size in siglen. 
        //!     sigret must point to getSignLength() bytes of memory.
        //! \param[in] const void* m - 
        //! \param[in] const size_t m_len - 
        //! \param[out] unsigned char* sigret - 
        //! \param[in,out] size_t* siglen - 
        //! \return bool - 
        bool sign( const void* m, const size_t m_len,
            unsigned char* sigret, size_t* siglen );

        bool sign( const void* m, const size_t m_len, std::string& sigret );


        //! \brief verifies that the signature sigbuf of size siglen matches
        //!     a given message digest m of size m_len. 
        //!     type denotes the message digest algorithm 
        //!     that was used to generate the signature. 
        //!     rsa is the signer's public key.
        //! \param[in] SignType type - 
        //! \param[in] const void * m - 
        //! \param[in] const size_t m_len - 
        //! \param[in] const unsigned char * sigbuf - 
        //! \param[in] const size_t siglen - 
        //! \return bool - 
        bool verify( const void* m, const size_t m_len, 
            const void* sigbuf, const size_t siglen );

        size_t getSignLength() const ;

        //! \brief Simple RSA public encrypt method
        //! \param[in] - const void * m
        //! \param[in] - const size_t m_len
        //! \param[out] - unsigned char * sigret
        //! \param[in,out] - size_t * siglen
        //! \return - bool
        bool publicEncrypt(const void* m, const size_t m_len, unsigned char* sigret, size_t* siglen);
        bool publicEncrypt(const void* m, const size_t m_len, std::string& sigret);

        bool privateDecrypt(const void* sig, const size_t sig_len, unsigned char* plain_data, size_t* plain_data_len);
        bool privateDecrypt(const void* sig, const size_t sig_len, std::string& plain_data);

    private:
        std::string private_key_;
        std::string public_key_;
    };


    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    inline bool SimpleRSA::initialize(const unsigned char* private_key, const size_t private_key_len,
        const unsigned char* public_key, const size_t public_key_len)
    {
        private_key_ = std::string((const char*)private_key, private_key_len);
        public_key_  = std::string((const char*)public_key, public_key_len);
        return true;
    }

    inline bool SimpleRSA::sign( const void* m, const size_t m_len,
        unsigned char* sigret, size_t* siglen )
    {
        unsigned int len = *siglen;
        int ok = slrsa_sign((const unsigned char*)m, m_len, (const unsigned char*)private_key_.data(), sigret, &len);
        *siglen = len;
        return ok != 0;
    }

    inline bool SimpleRSA::sign( const void* m, const size_t m_len, std::string& sigret )
    {
        unsigned char buf[512] = {};
        size_t buf_len = sizeof(buf);
        bool ok = sign(m, m_len, buf, &buf_len);
        if (ok)
        {
            assert(buf_len == getSignLength());
            sigret = std::string((char*)buf, buf_len);
            return ok;
        }

        return false;
    }

    inline bool SimpleRSA::verify( const void* m, const size_t m_len, 
        const void* sigbuf, const size_t siglen )
    {
        return 0 != slrsa_verify((const unsigned char*)m, m_len, 
            (const unsigned char*)public_key_.data(), 
            (const unsigned char*)sigbuf, (const unsigned int)siglen);
    }

    inline size_t SimpleRSA::getSignLength() const 
    { 
        return 128; 
    }

    inline bool SimpleRSA::publicEncrypt(const void* m, const size_t m_len, unsigned char* sigret, size_t* siglen)
    {
        unsigned int len = *siglen;
        bool ret = 0 != slrsa_public_encrypt((const unsigned char *)m, m_len, (const unsigned char *)public_key_.c_str(), sigret, &len);
        *siglen = len;
        return ret;
    }

    inline bool SimpleRSA::publicEncrypt(const void* m, const size_t m_len, std::string& sigret)
    {
        unsigned char buf[512] = {};
        size_t buf_len = sizeof(buf);
        bool ok = publicEncrypt(m, m_len, buf, &buf_len);
        if (ok)
        {
            assert(buf_len == getSignLength());
            sigret = std::string((char*)buf, buf_len);
            return ok;
        }
        return false;
    }

    inline bool SimpleRSA::privateDecrypt(const void* sig, const size_t sig_len, unsigned char* plain_data, size_t* plain_data_len)
    {
        unsigned int len = *plain_data_len;
        bool ret = 0 != slrsa_private_decrypt((const unsigned char *)sig, sig_len, (const unsigned char *)private_key_.c_str(), plain_data, &len);
        *plain_data_len = len;
        return ret;
    }

    inline bool SimpleRSA::privateDecrypt(const void* sig, const size_t sig_len, std::string& plain_data)
    {
        unsigned char buf[512] = {};
        size_t buf_len = sizeof(buf);
        bool ok = privateDecrypt(sig, sig_len, buf, &buf_len);
        if (ok)
        {
            assert(buf_len == getSignLength());
            plain_data = std::string((char*)buf, buf_len);
            return ok;
        }
        return false;
    }
} //end of namespace npp

#endif //#ifndef _NETPROTO_RSA_H_



