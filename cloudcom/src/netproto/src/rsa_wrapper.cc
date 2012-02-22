#include "netproto/include/inner_pre.h"

#if H_PROVIDE_RSA

#include "netproto/include/rsa_wrapper.h"

namespace npp
{
    OpenSSLRSA::OpenSSLRSA( const unsigned char* key, const size_t key_len, KeyType keytype ) 
        : m_eKeyType( keytype )
        , m_rsa( NULL )
    {
        BIO* b = BIO_new( BIO_s_mem() );
        BIO_write( b, key, key_len );

        if( keytype == KT_PRIVATE )  
        {
            m_rsa = d2i_RSAPrivateKey_bio( b, NULL );
        }
        else if( keytype == KT_PUBLIC )
        {
            m_rsa = d2i_RSAPublicKey_bio( b, NULL );
        }
        else
        {
            assert( false && "key type error.\n" );
        }

        BIO_free( b );
    }

    OpenSSLRSA::~OpenSSLRSA()
    {
        if ( m_rsa )
        {
            RSA_free( m_rsa );
        }
    }

    namespace
    {
        /**
        * Gengerate a ramdon RSA, remember to RSA_free the return pointer
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

    bool OpenSSLRSA::sign( SignType type, const unsigned char* m, const size_t m_len,
                    unsigned char* sigret, size_t* siglen )
    {
        assert( m_eKeyType == KT_PRIVATE );
        int ret = RSA_sign( type, m, (unsigned int)m_len, sigret, (unsigned int*)siglen, m_rsa );
        return (1 == ret);
    }

    bool OpenSSLRSA::verify( SignType type, 
                      const unsigned char* m, const size_t m_len,
                      const unsigned char* sigbuf, const size_t siglen )
    {
        assert( m_eKeyType == KT_PUBLIC );
        int ret = RSA_verify( type, m, (unsigned int)m_len, const_cast<unsigned char*>(sigbuf), (unsigned int)siglen, m_rsa );
        return (1 == ret);
    }
} //end of namespace npp

#endif //#if H_PROVIDE_RSA



