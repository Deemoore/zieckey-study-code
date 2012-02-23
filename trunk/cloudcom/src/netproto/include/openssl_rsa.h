#ifndef _NETPROTO_RSA_H_
#define _NETPROTO_RSA_H_


#include "netproto/include/config.h"
#include "netproto/include/inner_pre.h"

#if H_PROVIDE_RSA

#include <openssl/rsa.h>
#include <openssl/engine.h>

namespace npp
{
    class _EXPORT_NETPROTO OpenSSLRSA
    {
    public:
        enum KeyType
        { 
            KT_PRIVATE = 0, 
            KT_PUBLIC,
        };

        enum SignType
        {
            ST_NID_sha1 = NID_sha1, 
            ST_NID_ripemd160 = NID_ripemd160,
            ST_NID_md5 = NID_md5,
        };

    public:
        OpenSSLRSA( KeyType keytype );
        ~OpenSSLRSA();

        //! \brief Initialize the rsa
        //! \param[in] - const unsigned char * key
        //! \param[in] - const size_t key_len
        //! \return - bool return true if successfully
        bool initialize( const unsigned char* key, const size_t key_len );

        //! \brief signs the message digest m of size m_len using the private
        //!     key rsa. It stores the signature in sigret
        //!     and the signature size in siglen. 
        //!     sigret must point to getSignLength() bytes of memory.
        //! \param SignType type - denotes the message digest algorithm 
        //!     that was used to generate m. It usually is one of 
        //!     NID_sha1, NID_ripemd160 and NID_md5
        //! \param[in] const void* m - 
        //! \param[in] const size_t m_len - 
        //! \param[out] unsigned char* sigret - 
        //! \param[out] size_t* siglen - 
        //! \return bool - 
        bool sign( SignType type, const void* m, const size_t m_len,
                   unsigned char* sigret, size_t* siglen );
        bool sign( SignType type, const void* m, const size_t m_len,
                   std::string& sigret );


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
        bool verify( SignType type, const void* m, const size_t m_len, 
                     const void* sigbuf, const size_t siglen );


        npp::OpenSSLRSA::KeyType getKeyType() const 
        { 
            return m_eKeyType; 
        }

        size_t getSignLength() const 
        { 
            return (size_t)RSA_size(m_rsa); 
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
        KeyType    m_eKeyType;
        RSA*            m_rsa;
    };

} //end of namespace npp

#endif //#if H_PROVIDE_RSA


#endif //#ifndef _NETPROTO_RSA_H_



