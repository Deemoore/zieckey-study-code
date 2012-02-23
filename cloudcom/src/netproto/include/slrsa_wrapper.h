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
            const unsigned char* public_key, const size_t public_key_len)
        {
            m_private_key = std::string((const char*)private_key, private_key_len);
            m_public_key  = std::string((const char*)public_key, public_key_len);
            return true;
        }

        //! \brief signs the message digest m of size m_len using the private
        //!     key rsa. It stores the signature in sigret
        //!     and the signature size in siglen. 
        //!     sigret must point to getSignLength() bytes of memory.
        //! \param[in] const void* m - 
        //! \param[in] const size_t m_len - 
        //! \param[out] unsigned char* sigret - 
        //! \param[out] size_t* siglen - 
        //! \return bool - 
        bool sign( const void* m, const size_t m_len,
            unsigned char* sigret, size_t* siglen )
        {
            unsigned int len;
            int ok = slrsa_sign((const unsigned char*)m, m_len, (const unsigned char*)m_private_key.data(), sigret, &len);
            *siglen = len;
            return ok != 0;
        }

        bool sign( const void* m, const size_t m_len, std::string& sigret )
        {
            unsigned char buf[512] = {};
            size_t siglen;
            bool ok = sign(m, m_len, buf, &siglen);
            if (ok)
            {
                assert(siglen == getSignLength());
                sigret = std::string((char*)buf, siglen);
                return ok;
            }
            
            return false;
        }


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
            const void* sigbuf, const size_t siglen )
        {
            return 0 != slrsa_verify((const unsigned char*)m, m_len, 
                (const unsigned char*)m_public_key.data(), 
                (const unsigned char*)sigbuf, siglen);
        }

        size_t getSignLength() const 
        { 
            return 128; 
        }

    private:
        std::string m_private_key;
        std::string m_public_key;
    };

} //end of namespace npp


#endif //#ifndef _NETPROTO_RSA_H_



