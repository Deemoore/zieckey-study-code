#include <stdio.h>
#include <string.h>

#include "rsaeuro.h"
#include "r_random.h"
#include "nn.h"
#include "prime.h"

#include "slrsa/slrsa.h"

#ifdef WIN32
#	pragma comment(lib,"mkslrsa.lib")
#	pragma comment(lib,"slrsa.lib")
#endif

unsigned char prvFileKey[1024] = {};

unsigned char pubFileKey[1024] = {};

// 功能: 产生RSA密钥对. 返回true表示成功, 其它表示失败
static bool MakeRSAKey(unsigned char pPubkey[1024], unsigned char pPrvKey[1024] )
{
    //      static BYTE pbFreshOut[20];
    R_RANDOM_STRUCT RandomStruct;
    R_RSA_PROTO_KEY ProtoKey;
    int iRet;

    R_RandomCreate( &RandomStruct );
    //      R_GenerateBytes( pbFreshOut, sizeof(pbFreshOut), &RandomStruct );

    ProtoKey.useFermat4 = 1;
    ProtoKey.bits = 1024;

    iRet = R_GeneratePEMKeys( (R_RSA_PUBLIC_KEY *)pPubkey, (R_RSA_PRIVATE_KEY *)pPrvKey, &ProtoKey, &RandomStruct );

    R_RandomFinal( &RandomStruct );

    return iRet == 0;
}


int main( int argc, char* argv[] )
{
    printf("sizeof(R_RSA_PUBLIC_KEY)=%lu\n", sizeof(R_RSA_PUBLIC_KEY));
    printf("sizeof(R_RSA_PRIVATE_KEY)=%lu\n", sizeof(R_RSA_PRIVATE_KEY));

    bool mkok = MakeRSAKey(pubFileKey, prvFileKey);

    unsigned char* input = (unsigned char*)"8b2a649ecb880316db6a8c340b836b0c";

    const BYTE* g_rsa_prvFileKey = prvFileKey;
    const BYTE* g_rsa_pubFileKey = pubFileKey;

    const size_t MD5LEN = 33;
    char md5[MD5LEN];
    int inlen = MD5LEN - 1;
    char signatContent[128];
    char signatContent2[128];
    unsigned int sign_len = 128;

    char outmd5[MD5LEN];
    int outmd5Len = MD5LEN;

    
    int ret = slrsa_sign( (unsigned char*)md5, inlen, (const unsigned char*)g_rsa_prvFileKey, (unsigned char*)signatContent2, (unsigned int*)&sign_len);
    if ( ret )
    {
        printf("sign_len=%d\n", sign_len);
        ret =  slrsa_verify( (unsigned char*)md5, inlen, (const BYTE *)g_rsa_pubFileKey, (unsigned char*)signatContent2, sign_len );
        if ( ret )
        {
            printf("slrsa_verify pass the same!\n");
        }
        else
        {
            printf("slrsa_verify it is not the same.!!!!!!\n");
        }
    }

#ifdef WIN32
    system( "pause" );
#endif

    return 0;
}
