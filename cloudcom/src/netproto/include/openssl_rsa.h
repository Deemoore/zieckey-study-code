#ifndef _NETPROTO_RSA_H_
#define _NETPROTO_RSA_H_


#include "netproto/include/config.h"
#include "netproto/include/inner_pre.h"

#if H_NPP_PROVIDE_RSA

#include <openssl/rsa.h>
#include <openssl/engine.h>

namespace npp
{
    class _EXPORT_NETPROTO OpenSSLRSA
    {
    public:

        enum SignType
        {
            ST_NID_sha1 = NID_sha1, 
            ST_NID_ripemd160 = NID_ripemd160,
            ST_NID_md5 = NID_md5,
        };

    public:
        OpenSSLRSA();
        ~OpenSSLRSA();

        //! \brief Initialize the rsa
        //! \param[in] - const unsigned char * private_key
        //! \param[in] - const size_t private_key_len
        //! \return - bool return true if successfully
        bool initialize( const unsigned char* private_key, const size_t private_key_len,
            const unsigned char* public_key, const size_t public_key_len );

        //! \brief signs the message digest m of size m_len using the private
        //!     key rsa. It stores the signature in sigret
        //!     and the signature size in siglen. 
        //!     sigret must point to getSignLength() bytes of memory.
        //! \param[in] const void* m - 
        //! \param[in] const size_t m_len - 
        //! \param[out] unsigned char* sigret - 
        //! \param[out] size_t* siglen - 
        //! \return bool - 
        bool sign( SignType type, const void* m, const size_t m_len,
                   unsigned char* sigret, size_t* siglen );
        bool sign( SignType type, const void* m, const size_t m_len,
                   std::string& sigret );

        //! using ST_NID_sha1
        bool sign( const void* m, const size_t m_len,
                   unsigned char* sigret, size_t* siglen );
        bool sign( const void* m, const size_t m_len,
                   std::string& sigret  );


        //! \brief verifies that the signature sigbuf of size siglen matches
        //!     a given message digest m of size m_len. 
        //!     type denotes the message digest algorithm 
        //!     that was used to generate the signature. 
        //!     rsa is the signer's public key.
        //! \param[in] const void * m - 
        //! \param[in] const size_t m_len - 
        //! \param[in] const unsigned char * sigbuf - 
        //! \param[in] const size_t siglen - 
        //! \return bool - 
        bool verify( SignType type, const void* m, const size_t m_len, 
                     const void* sigbuf, const size_t siglen );

        //! using ST_NID_sha1
        bool verify( const void* m, const size_t m_len, 
                     const void* sigbuf, const size_t siglen );


        size_t getSignLength() const 
        { 
            return (size_t)RSA_size(m_priavte_rsa); 
        }

        //! \brief Generate a pair of private key and public key
        //!     Key length with keylen < 1024 should be considered insecure.
        //! \param const size_t keylen - the key length of RSA, 
        //!     the buffer of publickey and privatekey length 
        //!     MUST BE larger than keylen.
        //! \param unsigned char publickey[] - stores the public key here
        //! \param size_t * publickey_len - stores the public key length here
        //! \param unsigned char privatekey[] - stores the private key here
        //! \param size_t * privatekey_len - stores the private key length here 
        //! \return bool - true if success
        static bool generateKey( const size_t keylen, 
            unsigned char publickey[], size_t* publickey_len,
            unsigned char privatekey[] , size_t* privatekey_len );
//         static bool generateKey( const size_t keylen, 
//             std::string& publickey, 
//             std::string& privatekey);



    private:
        RSA*  m_priavte_rsa;
        RSA*  m_public_rsa;
    };

} //end of namespace npp

#endif //#if H_NPP_PROVIDE_RSA


#endif //#ifndef _NETPROTO_RSA_H_



