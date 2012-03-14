#ifndef _NETPROTO_OPENSSL_RSA_H_
#define _NETPROTO_OPENSSL_RSA_H_


#include "netproto/include/config.h"
#include "netproto/include/inner_pre.h"

#ifdef H_NPP_PROVIDE_OPENSSL_RSA

#include "netproto/include/asymmetric_encrypt.h"
#include <openssl/rsa.h>
#include <openssl/engine.h>

namespace npp
{
    class _EXPORT_NETPROTO OpenSSLRSA : public AsymmetricEncryptor
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
        virtual ~OpenSSLRSA();

        //! \brief Initialize the rsa
        //! \warning We support the private_key/public_key pair matches or not matches.
        //!     But the private_key and public_key's generator bits MUST BE the same
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
            return (size_t)RSA_size(m_private_rsa);
        }

        bool PublicEncrypt(const void* m, const size_t m_len, std::string& sigret);

        bool PrivateDecrypt(const void* sig, const size_t sig_len, std::string& plain_data);


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

        //Overridden
    public:
        //! \brief public encrypt method
        //! \param[in] - const void * m
        //! \param[in] - const size_t m_len
        //! \param[out] - unsigned char * sigret
        //! \param[in,out] - size_t * siglen
        //! \return - bool
        virtual bool PublicEncrypt(const void* m, const size_t m_len, void* sigret, size_t* siglen);

        virtual bool PrivateDecrypt(const void* sig, const size_t sig_len, void* plain_data, size_t* plain_data_len);

        virtual bool PrivateEncrypt(const void* m, const size_t m_len, void* sigret, size_t* siglen);

        virtual bool PublicDecrypt(const void* sig, const size_t sig_len, void* plain_data, size_t* plain_data_len);


        //! \brief Get the encrypt data length which will be allocated for storing the encrypted data
        //! \param[in] - Padding padding
        //! \param[in] - size_t nSourceLen
        //! \return - size_t
        virtual size_t GetEncryptDataLength() { return (size_t)RSA_size(m_public_rsa); }

        //! \brief Get the encrypt data length which will be allocated for storing the encrypted data
        //! \param[in] - Padding padding
        //! \param[in] - size_t nSourceLen
        //! \return - size_t
        virtual size_t GetDecryptDataLength(){ return (size_t)RSA_size(m_public_rsa); }


    private:
        RSA*  m_private_rsa;
        RSA*  m_public_rsa;
    };

} //end of namespace npp

#endif //#ifdef H_NPP_PROVIDE_OPENSSL_RSA


#endif //#ifndef _NETPROTO_RSA_H_



