#include <stdio.h>
#include <string.h>

#include "rsaeuro.h"
#include "r_random.h"
#include "nn.h"
#include "prime.h"

#include "slrsa/slrsa.h"

#include <openssl/rsa.h>
#include <openssl/engine.h>

#ifdef WIN32
#	pragma comment(lib,"mkslrsa.lib")
#	pragma comment(lib,"slrsa.lib")
#	pragma comment(lib,"libeay32.lib")
#endif

unsigned char prvFileKey[706] = {};

unsigned char pubFileKey[258] = {};

// 功能: 产生RSA密钥对. 返回true表示成功, 其它表示失败
static bool MakeSimpleRSAKey(unsigned char pPubkey[1024], unsigned char pPrvKey[1024] )
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


/**
* Gengerate a ramdon RSA 
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
        return NULL;
    }
}

bool MakeRSAKey(unsigned char public_key[], int& public_key_len, unsigned char private_key[], int& private_key_len)
{
    BIO* bio = BIO_new( BIO_s_mem() );
    RSA* rsa = gen_rsa( 1024 );
    int ret = i2d_RSAPublicKey_bio( bio, rsa );//create a public key
    public_key_len = BIO_read( bio, public_key, public_key_len );//read the key data into public_key buffer
    ret = i2d_RSAPrivateKey_bio( bio, rsa );//create a private key
    private_key_len = BIO_read( bio, private_key, private_key_len);//read the key data into private buffer
    BIO_free( bio );
    RSA_free( rsa );

    return ret == 1;
}
void test_slrsa_key()
{
    printf("sizeof(R_RSA_PUBLIC_KEY)=%lu\n", sizeof(R_RSA_PUBLIC_KEY)); //258
    printf("sizeof(R_RSA_PRIVATE_KEY)=%lu\n", sizeof(R_RSA_PRIVATE_KEY));//706

    bool mkok = MakeSimpleRSAKey(pubFileKey, prvFileKey);

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
}


int key_count = 4;
int begin_key_no = 1;



void GenIDEAKey()
{
    FILE* fp_idea = fopen("idea_key.h", "w+");
    fprintf(fp_idea, "#ifndef _IDEA_ENCRYPT_KEY_H_\n");
    fprintf(fp_idea, "#define _IDEA_ENCRYPT_KEY_H_\n\n");
    srand(time(NULL));
    int jj = 0;
    for (jj = begin_key_no; jj < key_count + begin_key_no; jj++)
    {
        fprintf(fp_idea, "static const unsigned char idea_key%d[16] = {", jj);
        int i = 0;
        for( i = 0; i < 16; i++ )
        {
            if (i != 0)
            {
                fprintf(fp_idea, ", ");
                if ( i % 16 == 0 )
                    fprintf(fp_idea, "\n\t");
            }
            fprintf(fp_idea, "0x%0.2x", rand() % 256 );
        }
        fprintf(fp_idea, "};\n\n");
    }

    fprintf(fp_idea, "#endif // end of #ifndef _IDEA_ENCRYPT_KEY_H_\n\n");
    fclose(fp_idea);
}

void GenTestKey()
{
    FILE* fp_test_rsa_key = fopen("rsa_test_key.h", "w+");
    fprintf(fp_test_rsa_key, "#ifndef _RSA_SIGN_KEY_H_ \n");
    fprintf(fp_test_rsa_key, "#define _RSA_SIGN_KEY_H_ \n");
    int jj = 0;
    for (jj = 1; jj <= 4; jj++)
    {
        //generate public and private key
        unsigned char public_key[1024] = { 0 };
        unsigned char private_key[1024] = { 0 };
        BIO* bio = BIO_new( BIO_s_mem() );
        RSA* rsa = gen_rsa( 1024 );
        int ret = i2d_RSAPublicKey_bio( bio, rsa );//create a public key
        int public_key_len = BIO_read( bio, public_key, sizeof(public_key) );//read the key data into public_key buffer
        ret = i2d_RSAPrivateKey_bio( bio, rsa );//create a private key
        int private_key_len = BIO_read( bio, private_key, sizeof(private_key) );//read the key data into private buffer
        BIO_free( bio );
        RSA_free( rsa );

        //print public and private key
        int i = 0;
        fprintf(fp_test_rsa_key, "\nstatic const unsigned char g_rsa_public_key%d[%lu] = {//{{{\n", jj, public_key_len );
        for( i = 0; i < public_key_len; i++ )
        {
            if (i != 0)
            {
                fprintf(fp_test_rsa_key,", ");
                if ( i % 16 == 0 )
                    fprintf(fp_test_rsa_key,"\n\t");
            }
            else
            {
                fprintf(fp_test_rsa_key,"\t");
            }
            fprintf(fp_test_rsa_key, "0x%0.2x", public_key[i] );
        }

        fprintf(fp_test_rsa_key, "};//}}}\n" );
        fprintf(fp_test_rsa_key,"static const size_t g_rsa_public_key%d_len = %lu;\n\n", jj, public_key_len);
        fprintf(fp_test_rsa_key, "\nstatic const unsigned char g_rsa_private_key%d[%lu] = {//{{{\n", jj, private_key_len );
        for( i = 0; i < private_key_len; i++ )
        {
            if (i != 0)
            {
                fprintf(fp_test_rsa_key,", ");
                if ( i % 16 == 0 )
                    fprintf(fp_test_rsa_key,"\n\t");
            }
            else
            {
                fprintf(fp_test_rsa_key,"\t");
            }
            fprintf(fp_test_rsa_key, "0x%0.2x", private_key[i] );
        }
        fprintf(fp_test_rsa_key, "};//}}}\n" );
        fprintf(fp_test_rsa_key,"static const size_t g_rsa_private_key%d_len = %lu;\n\n", jj, private_key_len);
        fprintf(fp_test_rsa_key, "\n" );

    }

    for (jj = 1; jj <= 4; jj++)
    {
        //generate public and private key
        unsigned char public_key[258] = { 0 };
        unsigned char private_key[706] = { 0 };
        size_t public_key_len = sizeof(public_key);
        size_t private_key_len = sizeof(private_key);
        MakeSimpleRSAKey(public_key, private_key);

        //print public and private key
        int i = 0;
        fprintf(fp_test_rsa_key, "\nstatic const unsigned char g_slrsa_public_key%d[%lu] = {//{{{\n", jj, public_key_len );
        for( i = 0; i < public_key_len; i++ )
        {
            if (i != 0)
            {
                fprintf(fp_test_rsa_key,", ");
                if ( i % 16 == 0 )
                    fprintf(fp_test_rsa_key,"\n\t");
            }
            else
            {
                fprintf(fp_test_rsa_key,"\t");
            }
            fprintf(fp_test_rsa_key, "0x%0.2x", public_key[i] );
        }

        fprintf(fp_test_rsa_key, "};//}}}\n" );
        fprintf(fp_test_rsa_key,"static const size_t g_slrsa_public_key%d_len = %lu;\n\n", jj, public_key_len);
        fprintf(fp_test_rsa_key, "\nstatic const unsigned char g_slrsa_private_key%d[%lu] = {//{{{\n", jj, private_key_len );
        for( i = 0; i < private_key_len; i++ )
        {
            if (i != 0)
            {
                fprintf(fp_test_rsa_key,", ");
                if ( i % 16 == 0 )
                    fprintf(fp_test_rsa_key,"\n\t");
            }
            else
            {
                fprintf(fp_test_rsa_key,"\t");
            }
            fprintf(fp_test_rsa_key, "0x%0.2x", private_key[i] );
        }
        fprintf(fp_test_rsa_key, "};//}}}\n" );
        fprintf(fp_test_rsa_key,"static const size_t g_slrsa_private_key%d_len = %lu;\n\n", jj, private_key_len);
        fprintf(fp_test_rsa_key, "\n" );

    }

    fprintf(fp_test_rsa_key,"#endif\n");
}

int main( int argc, char* argv[] )
{
    GenIDEAKey();


    GenTestKey();

    FILE* fp_server = fopen("server_rsa_key.h", "w+");
    FILE* fp_client = fopen("client_rsa_key.h", "w+");

    fprintf(fp_server, "#ifndef _SERVER_RSA_SIGN_KEY_H_ \n");
    fprintf(fp_server, "#define _SERVER_RSA_SIGN_KEY_H_ \n");
    fprintf(fp_client, "#ifndef _CLIENT_RSA_SIGN_KEY_H_ \n");
    fprintf(fp_client, "#define _CLIENT_RSA_SIGN_KEY_H_ \n");
    int jj = 0;
    for (jj = begin_key_no; jj < key_count + begin_key_no; jj++)
    {
        FILE* fp1 = NULL;
        FILE* fp2 = NULL;
        int kk = 0;
        for (kk = 0; kk < 2; kk++)
        {
            if (kk == 0)
            {
                fp1 = fp_server;
                fp2 = fp_client;
            }
            else
            {
                fp2 = fp_server;
                fp1 = fp_client;
            }

            //generate public and private key
            unsigned char public_key[1024] = { 0 };
            unsigned char private_key[1024] = { 0 };
            int public_key_len = sizeof(public_key);
            int private_key_len = sizeof(private_key);
            if (!MakeRSAKey(public_key, public_key_len, private_key, private_key_len))
            {
                fprintf(stderr, "ERROR!\n");
                return -1;
            }
            
//             int ret = i2d_RSAPublicKey_bio( bio, rsa );//create a public key
//             int public_key_len = BIO_read( bio, public_key, sizeof(public_key) );//read the key data into public_key buffer
//             ret = i2d_RSAPrivateKey_bio( bio, rsa );//create a private key
//             int private_key_len = BIO_read( bio, private_key, sizeof(private_key));//read the key data into private buffer
//             BIO_free( bio );
//             RSA_free( rsa );

            fprintf(fp1, "\nstatic const unsigned char g_rsa_public_key%d[%lu] = {//{{{\n", jj, public_key_len );
            int i = 0;
            for( i = 0; i < public_key_len; i++ )
            {
                if (i != 0)
                {
                    fprintf(fp1, ", ");
                    if ( i % 16 == 0 )
                        fprintf(fp1, "\n\t");
                }
                else
                {
                    fprintf(fp1, "\t");
                }
                fprintf(fp1, "0x%0.2x", public_key[i] );
            }
            fprintf(fp1, "};//}}}\n" );
            fprintf(fp1, "static const size_t g_rsa_public_key%d_len = %lu;\n\n", jj, public_key_len);

            fprintf(fp2, "static const unsigned char g_rsa_private_key%d[%lu] = {//{{{\n", jj, private_key_len );
            for( i = 0; i < private_key_len; i++ )
            {
                if (i != 0)
                {
                    fprintf(fp2, ", ");
                    if ( i % 16 == 0 )
                        fprintf(fp2, "\n\t");
                }
                else
                {
                    fprintf(fp2, "\t");
                }
                fprintf(fp2, "0x%0.2x", private_key[i] );
            }

            fprintf(fp2, "};//}}}\n" );
            fprintf(fp2, "static const size_t g_rsa_private_key%d_len = %lu;\n\n", jj, private_key_len);
            fprintf(fp2, "\n" );
        }
    }

    fprintf(fp_server, "//----------------------------------------------------------------\n");
    fprintf(fp_client, "//----------------------------------------------------------------\n");
    fprintf(fp_server, "//----------------------------------------------------------------\n");
    fprintf(fp_client, "//----------------------------------------------------------------\n");
    fprintf(fp_server, "//----------------------------------------------------------------\n");
    fprintf(fp_client, "//----------------------------------------------------------------\n");

    for (jj = begin_key_no; jj < key_count + begin_key_no; jj++)
    {
        FILE* fp1 = NULL;
        FILE* fp2 = NULL;
        int kk = 0;
        for (kk = 0; kk < 2; kk++)
        {
            if (kk == 0)
            {
                fp1 = fp_server;
                fp2 = fp_client;
            }
            else
            {
                fp2 = fp_server;
                fp1 = fp_client;
            }

            unsigned char public_key[258] = { 0 };
            unsigned char private_key[706] = { 0 };
            size_t public_key_len = sizeof(public_key);
            size_t private_key_len = sizeof(private_key);
            //generate public and private key
            MakeSimpleRSAKey(public_key, private_key);

            //print public and private key
            fprintf(fp1, "\nstatic const unsigned char g_slrsa_public_key%d[%lu] = {//{{{\n", jj, public_key_len );
            int i = 0;
            for( i = 0; i < public_key_len; i++ )
            {
                if (i != 0)
                {
                    fprintf(fp1, ", ");
                    if ( i % 16 == 0 )
                        fprintf(fp1, "\n\t");
                }
                else
                {
                    fprintf(fp1, "\t");
                }
                fprintf(fp1, "0x%0.2x", public_key[i] );
            }
            fprintf(fp1, "};//}}}\n" );
            fprintf(fp1, "static const size_t g_slrsa_public_key%d_len = %lu;\n\n", jj, public_key_len);

            fprintf(fp2, "static const unsigned char g_slrsa_private_key%d[%lu] = {//{{{\n", jj, private_key_len );
            for( i = 0; i < private_key_len; i++ )
            {
                if (i != 0)
                {
                    fprintf(fp2, ", ");
                    if ( i % 16 == 0 )
                        fprintf(fp2, "\n\t");
                }
                else
                {
                    fprintf(fp2, "\t");
                }
                fprintf(fp2, "0x%0.2x", private_key[i] );
            }


            fprintf(fp2, "};//}}}\n" );
            fprintf(fp2, "static const size_t g_slrsa_private_key%d_len = %lu;\n\n", jj, private_key_len);
            fprintf(fp2, "\n" );
        }
    }


    fprintf(fp_server, "\n\n#endif // end of #ifdef _SERVER_RSA_SIGN_KEY_H_\n\n\n");
    fprintf(fp_client, "\n\n#endif // endof #ifdef _CLIENT_RSA_SIGN_KEY_H_\n\n\n");

#ifdef WIN32
    system( "pause" );
#endif

    return 0;
}
