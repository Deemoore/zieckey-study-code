#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "slrsa.h"
#include "global.h"
#include "rsa.h"
#include "r_random.h"

int slrsa_sign( const unsigned char *m, const unsigned int m_len,
            const unsigned char* privatekey,
            unsigned char *sigret, unsigned int *siglen )
{
    int ret = RSAPrivateEncrypt( sigret, siglen, 
                (unsigned char*)(m), m_len, 
                (R_RSA_PRIVATE_KEY*)privatekey );    
    if (RSA_IDOK != ret)
    {
        /* sign failed */
        return 0;
    }
     
    /* Sign OK */
    return 1;
}


int slrsa_verify( const unsigned char *m, const unsigned int m_len,
            const unsigned char* publickey,
            const unsigned char *sigbuf, const unsigned int siglen )
{
    unsigned char* vm = (unsigned char*)malloc( m_len );
    unsigned int vm_len = m_len;
    int ret = RSAPublicDecrypt( vm, &vm_len, 
                (unsigned char*)(sigbuf), siglen, 
                ( R_RSA_PUBLIC_KEY * )publickey );    
    
    if ( RSA_IDOK != ret )
    {
        free( vm ); vm = 0;
        //fprintf(stderr, "vm_len=%d, m_len=%d, RSAPublicDecrypt ret=%d\n", (int)vm_len, (int)m_len, (int)ret );
        return 0;
    }

    /* verify */
    ret = memcmp( vm, m, m_len );

    free( vm ); vm = 0;

    if ( 0 == ret ) 
    {
        /* verify pass */
        return 1;
    }
    else 
    {
        return 0;
    }
}

int slrsa_public_encrypt( const unsigned char* m, const unsigned int m_len, const unsigned char* publickey, unsigned char* sigret, unsigned int* siglen )
{
    R_RANDOM_STRUCT RandomStruct;
#ifndef WIN32
    //TODO this sentence compile error in VS9.0,, but in Unix need this.
    //I really don't know whether it is OK when doing Windows do this slrsa_public_encrypt and Unix do slrsa_private_decrypt
    R_RandomCreate( &RandomStruct );
#endif
    int encrypt_ret = RSAPublicEncrypt(sigret, siglen, (unsigned char*)m, m_len, (R_RSA_PUBLIC_KEY *)publickey, &RandomStruct);
    if (encrypt_ret == RSA_IDOK)
    {
        //successfully
        return 1;
    }
    else
    {
        return 0;
    }
}

int slrsa_private_decrypt( const unsigned char* m, const unsigned int m_len, const unsigned char* privatekey, unsigned char* sigret, unsigned int* siglen )
{
    int decrypt_ret = RSAPrivateDecrypt(sigret, siglen, (unsigned char*)m, m_len, (R_RSA_PRIVATE_KEY *)privatekey);
    if (decrypt_ret == RSA_IDOK)
    {
        //successfully
        return 1;
    }
    else
    {
        return 0;
    }
}



// int RSAPrivateEncrypt(output, outputLen, input, inputLen, privateKey)
// unsigned char *output;          /* output block */
// unsigned int *outputLen;        /* length of output block */
// unsigned char *input;           /* input block */
// unsigned int inputLen;          /* length of input block */
// R_RSA_PRIVATE_KEY *privateKey;  /* RSA private key */
int slrsa_private_encrypt( const unsigned char* m, const unsigned int m_len, const unsigned char* private_key, unsigned char* sigret, unsigned int* siglen )
{
    int encrypt_ret = RSAPrivateEncrypt(sigret, siglen, (unsigned char*)m, m_len, (R_RSA_PRIVATE_KEY *)private_key);
    if (encrypt_ret == RSA_IDOK)
    {
        //successfully
        return 1;
    }
    else
    {
        return 0;
    }
}

int slrsa_public_decrypt( const unsigned char* m, const unsigned int m_len, const unsigned char* public_key, unsigned char* sigret, unsigned int* siglen )
{
    int decrypt_ret = RSAPublicDecrypt(sigret, siglen, (unsigned char*)m, m_len, (R_RSA_PUBLIC_KEY *)public_key);
    if (decrypt_ret == RSA_IDOK)
    {
        //successfully
        return 1;
    }
    else
    {
        return 0;
    }
}
