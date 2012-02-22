#ifndef _QOSLIB_RSA_H_
#define _QOSLIB_RSA_H_


#include "netproto/include/inner_pre.h"

#if H_PROVIDE_RSA

#include <openssl/rsa.h>
#include <openssl/engine.h>

namespace npp
{
    class _EXPORT_OSLIB Rsa
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
        Rsa( const unsigned char* key, const size_t key_len, KeyType keytype );
        ~Rsa();

        //! \brief signs the message digest m of size m_len using the private
        //!     key rsa. It stores the signature in sigret
        //!     and the signature size in siglen. 
        //!     sigret must point to getSignLength() bytes of memory.
        //! \param SignType type - denotes the message digest algorithm 
        //!     that was used to generate m. It usually is one of 
        //!     NID_sha1, NID_ripemd160 and NID_md5
        //! \param[in] const unsigned char* m - 
        //! \param[in] const size_t m_len - 
        //! \param[out] unsigned char* sigret - 
        //! \param[out] size_t* siglen - 
        //! \return bool - 
        bool sign( SignType type, const unsigned char* m, const size_t m_len,
                   unsigned char* sigret, size_t* siglen );


        //! \brief verifies that the signature sigbuf of size siglen matches
        //!     a given message digest m of size m_len. 
        //!     type denotes the message digest algorithm 
        //!     that was used to generate the signature. 
        //!     rsa is the signer's public key.
        //! \param[in] SignType type - 
        //! \param[in] const unsigned char * m - 
        //! \param[in] const size_t m_len - 
        //! \param[in] const unsigned char * sigbuf - 
        //! \param[in] const size_t siglen - 
        //! \return bool - 
        bool verify( SignType type, const unsigned char* m, const size_t m_len, 
            const unsigned char* sigbuf, const size_t siglen );


        npp::Rsa::KeyType getKeyType() const { return m_eKeyType; }
        int getSignLength() const { return RSA_size(m_rsa); }

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

    private:
        KeyType    m_eKeyType;
        RSA*            m_rsa;
    };

} //end of namespace npp

#endif //#if H_PROVIDE_RSA


#endif //#ifndef _QOSLIB_RSA_H_



