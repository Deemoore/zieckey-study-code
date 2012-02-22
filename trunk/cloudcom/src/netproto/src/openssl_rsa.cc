#include "netproto/include/inner_pre.h"

#if H_PROVIDE_RSA

#include "netproto/include/openssl_rsa.h"

namespace npp
{
    OpenSSLRSA::OpenSSLRSA( KeyType keytype ) 
        : m_eKeyType( keytype )
        , m_rsa( NULL )
    {
        
    }

    OpenSSLRSA::~OpenSSLRSA()
    {
        if ( m_rsa )
        {
            RSA_free( m_rsa );
        }
    }

    bool OpenSSLRSA::initialize( const unsigned char* key, const size_t key_len )
    {
        BIO* b = BIO_new( BIO_s_mem() );
        BIO_write( b, key, key_len );

        if( m_eKeyType == KT_PRIVATE )  
        {
            m_rsa = d2i_RSAPrivateKey_bio( b, NULL );
        }
        else if( m_eKeyType == KT_PUBLIC )
        {
            m_rsa = d2i_RSAPublicKey_bio( b, NULL );
        }
        else
        {
            assert( false && "key type error.\n" );
        }

        BIO_free( b );

        if (m_rsa)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    namespace
    {
        /**
        * Generate a random RSA, remember to RSA_free the return pointer
        */
        RSA* gen_rsa( int ibits )
        {
            BIGNUM* bne = BN_new();
            int ret = BN_set_word( bne, RSA_F4 );
            RSA* rsa = RSA_new();
            ret = RSA_generate_key_ex( rsa, ibits, bne, NULL );
            BN_free( bne );

            if( ret == 1 )
            {
                return rsa;
            }
            else
            {
                RSA_free( rsa );
                return NULL;
            }
        }
    }//end of anonymous namespace

    bool OpenSSLRSA::generateKey( const size_t keylen, 
        unsigned char public_key[], size_t* public_key_len, 
        unsigned char private_key[] , size_t* private_key_len )
    {
        RSA* rsa = gen_rsa( keylen );
        if ( !rsa )
        {
            return false;
        }

        BIO* bio = BIO_new( BIO_s_mem() );
        int ret = i2d_RSAPublicKey_bio( bio, rsa );//create a public key
        if ( 1 == ret )
        {
            *public_key_len = BIO_read( bio, public_key, keylen );//read the key data into public_key buffer
            ret = i2d_RSAPrivateKey_bio( bio, rsa );//create a private key
            if ( 1 == ret )
            {
                *private_key_len = BIO_read( bio, private_key, keylen );//read the key data into private buffer
            }
        }

        BIO_free( bio ); bio = NULL;
        RSA_free( rsa ); rsa = NULL;

        return (1 == ret);
    }

//     bool OpenSSLRSA::generateKey( const size_t keylen, 
//         std::string& publickey, 
//         std::string& privatekey)
//     {
//         unsigned char* pub_key = new unsigned char[keylen];
//         unsigned char* priv_key = new unsigned char[keylen];
// 
//         memset(pub_key, 0, sizeof(unsigned char)*keylen);
//         memset(priv_key, 0, sizeof(unsigned char)*keylen);
// 
//         size_t pub_key_len = 0;
//         size_t priv_key_len = 0;
//         bool ok = generateKey(keylen, pub_key, &pub_key_len, priv_key, &priv_key_len);
//         if (ok)
//         {
//             publickey  = std::string((char*)pub_key, pub_key_len);
//             privatekey = std::string((char*)priv_key, priv_key_len);
//         }
// 
//         delete pub_key;
//         pub_key = NULL;
//         delete priv_key;
//         priv_key = NULL;
//         return ok;
//     }

    bool OpenSSLRSA::sign( SignType type, const void* m, const size_t m_len,
                    unsigned char* sigret, size_t* siglen )
    {
        assert( m_eKeyType == KT_PRIVATE );
        int ret = RSA_sign( type, (const unsigned char*)m, (unsigned int)m_len, sigret, (unsigned int*)siglen, m_rsa );
        return (1 == ret);
    }

    bool OpenSSLRSA::sign( SignType type, const void* m, const size_t m_len, std::string& sigret )
    {
        size_t siglen = getSignLength();
        sigret.resize(siglen);
        bool ok = sign(type, m, m_len, (unsigned char*)&sigret[0], &siglen);
#ifdef _DEBUG
        if (ok)
        {
            assert(siglen == sigret.length());
        }
#endif
        return ok;
    }

    bool OpenSSLRSA::verify( SignType type, 
                      const void* m, const size_t m_len,
                      const void* sigbuf, const size_t siglen )
    {
        assert( m_eKeyType == KT_PUBLIC );
        int ret = RSA_verify( type, (const unsigned char*)m, (unsigned int)m_len, (unsigned char*)(sigbuf), (unsigned int)siglen, m_rsa );
        return (1 == ret);
    }
} //end of namespace npp

#endif //#if H_PROVIDE_RSA



