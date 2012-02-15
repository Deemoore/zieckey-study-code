#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "slrsa.h"
#include "global.h"
#include "rsa.h"

/*
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif
*/

int slrsa_sign( const unsigned char *m, const unsigned int m_len,
            const unsigned char* privatekey,
            unsigned char *sigret, unsigned int *siglen )
{
    int ret = !RSAPrivateEncrypt( sigret, siglen, 
                (unsigned char*)(m), m_len, 
                (R_RSA_PRIVATE_KEY*)privatekey );    
    return ret;
}


int slrsa_verify( const unsigned char *m, const unsigned int m_len,
            const unsigned char* publickey,
            const unsigned char *sigbuf, const unsigned int siglen )
{
    unsigned char* vm = (unsigned char*)malloc( m_len );
    unsigned int vm_len = m_len;
    int ret = !RSAPublicDecrypt( vm, &vm_len, 
                (unsigned char*)(sigbuf), siglen, 
                ( R_RSA_PUBLIC_KEY * )publickey );    
    
    if ( 0 == ret )
    {
        fprintf(stderr, "vm_len=%d, m_len=%d, RSAPublicDecrypt ret=%d\n", (int)vm_len, (int)m_len, (int)ret );
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

/*
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
*/



