#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "rsaeuro.h"
#include "r_random.h"
#include "nn.h"
#include "prime.h"

#include "slrsa/slrsa.h"

#include <openssl/rsa.h>
#include <openssl/engine.h>

// #include "netproto/include/exp.h"
// #include "netproto/include/npp_config.h"
// #include "netproto/include/message_packer.h"
// #include "netproto/include/message_unpacker.h"
// #include "netproto/include/idea_wrapper.h"
// #include "netproto/include/openssl_rsa.h"
// #include "netproto/include/slrsa_wrapper.h"

#include <map>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

struct OutputKeys
{
    std::string public_key;//0x30, 0x81, 0x89, 0x02, 0x81, 0x81, 0x00, 0xc5, 0x92, 0x60, 0x47, 0xa9, 0x9d, 0x56, 0xf1, 0x3e, ....
    size_t public_key_len;
    std::string private_key;//0x30, 0x81, 0x89, 0x02, 0x81, 0x81, 0x00, 0xc5, 0x92, 0x60, 0x47, 0xa9, 0x9d, 0x56, 0xf1, 0x3e, ....
    size_t private_key_len;
};

typedef std::vector< OutputKeys > OutputKeysVector; // keys

#ifdef WIN32
#	pragma comment(lib,"mkslrsa.lib")
#	pragma comment(lib,"slrsa.lib")
#	pragma comment(lib,"libeay32.lib")
#ifdef _DEBUG
#	pragma comment(lib,"netproto_d.lib")
#else
#	pragma comment(lib,"netproto.lib")
#endif
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

bool MakeOpenSSLRSAKey(unsigned char public_key[], int& public_key_len, unsigned char private_key[], int& private_key_len)
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


int key_count = 4; //2的倍数
int begin_key_no = 1;//begin from 1



void GenIDEAKey()
{
    FILE* fp_idea = fopen("idea_key.h", "w+");

    FILE* fp_php_idea = fopen("idea_key.php", "w+");
    fprintf(fp_php_idea, "<?php\n\n");
    fprintf(fp_php_idea, "$crypto_keys = array(\n");

    fprintf(fp_idea, "#ifndef _IDEA_ENCRYPT_KEY_H_\n");
    fprintf(fp_idea, "#define _IDEA_ENCRYPT_KEY_H_\n\n");
    srand(time(NULL));
    int jj = 0;
    for (jj = begin_key_no; jj < key_count + begin_key_no; jj++)
    {
        fprintf(fp_idea, "static const unsigned char idea_key%d[16] = {", jj);
        fprintf(fp_php_idea, "\t%d => pack('C16', ", jj);
        int i = 0;
        for( i = 0; i < 16; i++ )
        {
            if (i != 0)
            {
                fprintf(fp_php_idea, ", ");
                fprintf(fp_idea, ", ");
                if ( i % 16 == 0 )
                {
                    fprintf(fp_php_idea, "),\n");
                    fprintf(fp_idea, "\n\t");
                }
            }
            unsigned char key = rand() % 256;
            fprintf(fp_php_idea, "0x%0.2x",  key);
            fprintf(fp_idea, "0x%0.2x", key);
        }
        fprintf(fp_idea, "};\n\n");
        fprintf(fp_php_idea, "),\n");
    }

    fprintf(fp_idea, "#endif // end of #ifndef _IDEA_ENCRYPT_KEY_H_\n\n");
    fprintf(fp_php_idea, ");");
    fclose(fp_idea);
    fflush(fp_idea);
    fflush(fp_php_idea);
    fclose(fp_php_idea);

}

void GenTestKey()
{//{{{
    FILE* fp_test_rsa_key = fopen("test_rsa_self_pair_key.h", "w+");
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
//                 if ( i % 16 == 0 )
//                     fprintf(fp_test_rsa_key,"\n\t");
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
//                 if ( i % 16 == 0 )
//                     fprintf(fp_test_rsa_key,"\n\t");
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
//                 if ( i % 16 == 0 )
//                     fprintf(fp_test_rsa_key,"\n\t");
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
//                 if ( i % 16 == 0 )
//                     fprintf(fp_test_rsa_key,"\n\t");
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
}//}}}

int GenAllKeys()
{
    {
        std::stringstream oss;
        oss << std::hex << std::setfill ('0') << std::setw(2) << 17;
        std::string s = oss.str();
        const char* a = s.c_str();
        (void)a;
    }
    typedef std::map<int, std::stringstream* > int_sstream_map;

    int_sstream_map openssl_rsa_private_client_key_map;
    int_sstream_map simple_rsa_private_client_key_map;
    int_sstream_map openssl_rsa_public_client_key_map;
    int_sstream_map simple_rsa_public_client_key_map;
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
            const char* fp1_prefix = "server";
            const char* fp2_prefix = "client";
            if (kk == 0)
            {
                fp1_prefix = "server";
                fp2_prefix = "client";
                fp1 = fp_server;
                fp2 = fp_client;
            }
            else
            {
                fp2_prefix = "server";
                fp1_prefix = "client";
                fp2 = fp_server;
                fp1 = fp_client;
            }

            //generate public and private key
            unsigned char public_key[1024] = { 0 };
            unsigned char private_key[1024] = { 0 };
            int public_key_len = sizeof(public_key);
            int private_key_len = sizeof(private_key);
            if (!MakeOpenSSLRSAKey(public_key, public_key_len, private_key, private_key_len))
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

            fprintf(fp1, "\nstatic const unsigned char g_%s_rsa_public_key%d[%lu] = {//{{{\n", fp1_prefix, jj, public_key_len );
            int i = 0;
            openssl_rsa_public_client_key_map[jj] = new std::stringstream;
            std::stringstream& public_client_key_ss = *openssl_rsa_public_client_key_map[jj];
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
                if (fp1 == fp_client)
                {
                    if (0 == i)
                    {
                        public_client_key_ss << "0x" << std::hex << std::setfill ('0') << std::setw(2) << (int)public_key[i];
                    }
                    else
                    {
                        public_client_key_ss << ", 0x" << std::hex << std::setfill ('0') << std::setw(2) << (int)public_key[i];
                    }
                }
            }
            fprintf(fp1, "};//}}}\n" );
            fprintf(fp1, "static const size_t g_%s_rsa_public_key%d_len = %lu;\n\n", fp1_prefix, jj, public_key_len);

            openssl_rsa_private_client_key_map[jj] = new std::stringstream;
            std::stringstream& private_client_key_ss = *openssl_rsa_private_client_key_map[jj];
            fprintf(fp2, "static const unsigned char g_%s_rsa_private_key%d[%lu] = {//{{{\n", fp2_prefix, jj, private_key_len );
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

                if (fp2 == fp_client)
                {
                    if (0 == i)
                    {
                        private_client_key_ss << "0x" << std::hex << std::setfill ('0') << std::setw(2) << (int)private_key[i];
                    }
                    else
                    {
                        private_client_key_ss << ", 0x" << std::hex << std::setfill ('0') << std::setw(2) << (int)private_key[i];
                    }
                }
            }

            fprintf(fp2, "};//}}}\n" );
            fprintf(fp2, "static const size_t g_%s_rsa_private_key%d_len = %lu;\n\n", fp2_prefix, jj, private_key_len);
            fprintf(fp2, "\n" );
        }
    }

    fprintf(fp_server, "//----------------------------------------------------------------\n");
    fprintf(fp_client, "//----------------------------------------------------------------\n");
    fprintf(fp_server, "//----------------------------------------------------------------\n");
    fprintf(fp_client, "//----------------------------------------------------------------\n");
    fprintf(fp_server, "//----------------------------------------------------------------\n");
    fprintf(fp_client, "//----------------------------------------------------------------\n");

    //rsa
    for (jj = begin_key_no; jj < key_count + begin_key_no; jj++)
    {

        FILE* fp1 = NULL;
        FILE* fp2 = NULL;
        int kk = 0;
        for (kk = 0; kk < 2; kk++)
        {
            const char* fp1_prefix = "server";
            const char* fp2_prefix = "client";
            if (kk == 0)
            {
                fp1_prefix = "server";
                fp2_prefix = "client";
                fp1 = fp_server;
                fp2 = fp_client;
            }
            else
            {
                fp2_prefix = "server";
                fp1_prefix = "client";
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
            fprintf(fp1, "\nstatic const unsigned char g_%s_slrsa_public_key%d[%lu] = {//{{{\n", fp1_prefix, jj, public_key_len );
            int i = 0;
            simple_rsa_public_client_key_map[jj] = new std::stringstream;
            std::stringstream& public_client_key_ss = *simple_rsa_public_client_key_map[jj];
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


                if (fp1 == fp_client)
                {
                    if (0 == i)
                    {
                        public_client_key_ss << "0x" << std::hex << std::setfill ('0') << std::setw(2) << (int)public_key[i];
                    }
                    else
                    {
                        public_client_key_ss << ", 0x" << std::hex << std::setfill ('0') << std::setw(2) << (int)public_key[i];
                    }
                }
            }
            fprintf(fp1, "};//}}}\n" );
            fprintf(fp1, "static const size_t g_%s_slrsa_public_key%d_len = %lu;\n\n", fp1_prefix, jj, public_key_len);

            simple_rsa_private_client_key_map[jj] = new std::stringstream;
            std::stringstream& private_client_key_ss = *simple_rsa_private_client_key_map[jj];
            fprintf(fp2, "static const unsigned char g_%s_slrsa_private_key%d[%lu] = {//{{{\n", fp2_prefix, jj, private_key_len );
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

                if (fp2 == fp_client)
                {
                    if (0 == i)
                    {
                        private_client_key_ss << "0x" << std::hex << std::setfill ('0') << std::setw(2) << (int)private_key[i];
                    }
                    else
                    {
                        private_client_key_ss << ", 0x" << std::hex << std::setfill ('0') << std::setw(2) << (int)private_key[i];
                    }
                }
            }


            fprintf(fp2, "};//}}}\n" );
            fprintf(fp2, "static const size_t g_%s_slrsa_private_key%d_len = %lu;\n\n", fp2_prefix, jj, private_key_len);
            fprintf(fp2, "\n" );
        }
    }


    fprintf(fp_server, "\n\n#endif // end of #ifdef _SERVER_RSA_SIGN_KEY_H_\n\n\n");
    fprintf(fp_client, "\n\n#endif // endof #ifdef _CLIENT_RSA_SIGN_KEY_H_\n\n\n");

    fflush(fp_server);
    fflush(fp_client);

    fclose(fp_server);
    fclose(fp_client);

    FILE* fp_php_client = fopen("client_rsa_key.php", "w+");
    fprintf(fp_php_client, "<?php\n"
        "$sign_private_keys = array(\n"
        "\t//{{{ simple rsa private keys\n"
        "\t'simple' => array(\n"
        );

    {
        int_sstream_map::iterator it(simple_rsa_private_client_key_map.begin());
        int_sstream_map::iterator ite(simple_rsa_private_client_key_map.end());
        for (int i = 1; it != ite; ++it, ++i)
        {
            std::string s = it->second->str();
            fprintf(fp_php_client, "\t\t%d => pack('C%lu', %s),\n", i, s.size(), s.c_str());
            delete it->second;
        }
        fprintf(fp_php_client, "\t),\n//}}}\n");
    }

    {
        fprintf(fp_php_client, "\t'openssl' => array(\n");
        int_sstream_map::iterator it(openssl_rsa_private_client_key_map.begin());
        int_sstream_map::iterator ite(openssl_rsa_private_client_key_map.end());
        for (int i = 1; it != ite; ++it, ++i)
        {
            std::string s = it->second->str();
            fprintf(fp_php_client, "\t\t%d => pack('C%lu', %s),\n", i, s.size(), s.c_str());
            delete it->second;
        }
        fprintf(fp_php_client, "\t),\n//}}}\n);\n\n");
    }


    fprintf(fp_php_client, "$sign_public_keys = array(\n"
        "\t//{{{ simple rsa public keys\n"
        "\t'simple' => array(\n"
        );
    {
        int_sstream_map::iterator it(simple_rsa_public_client_key_map.begin());
        int_sstream_map::iterator ite(simple_rsa_public_client_key_map.end());
        for (int i = 1; it != ite; ++it, ++i)
        {
            std::string s = it->second->str();
            fprintf(fp_php_client, "\t\t%d => pack('C%lu', %s),\n", i, s.size(), s.c_str());
            delete it->second;
        }
        fprintf(fp_php_client, "\t),\n//}}}\n");
    }

    {
        fprintf(fp_php_client, "\t'openssl' => array(\n");
        int_sstream_map::iterator it(openssl_rsa_public_client_key_map.begin());
        int_sstream_map::iterator ite(openssl_rsa_public_client_key_map.end());
        for (int i = 1; it != ite; ++it, ++i)
        {
            std::string s = it->second->str();
            fprintf(fp_php_client, "\t\t%d => pack('C%lu', %s),\n", i, s.size(), s.c_str());
            delete it->second;
        }
        fprintf(fp_php_client, "\t),\n//}}}\n);\n\n");
    }

    fflush(fp_php_client);
    fclose(fp_php_client);

    return 0;
}



void GetOutputKey(const std::string& binary_key, std::string& c_define_keys_string)
{
    size_t binary_key_len = binary_key.length();
    char* buf = new char[8 * 1024  *1024];
    size_t writen = 0;
    for(int i = 0; i < binary_key_len; i++ )
    {
        if (i != 0)
        {
            writen += sprintf(buf + writen, ", ");
//             if ( i % 16 == 0 )
//                 writen += sprintf(buf + writen, "\n\t");
        }
        else
        {
            writen += sprintf(buf + writen, "\t");
        }
        writen += sprintf(buf + writen, "0x%0.2x", (unsigned char)binary_key[i] );
    }

    c_define_keys_string = std::string(buf, writen);

    delete buf;
}

void GetOutputKeys(const std::string& public_key, const std::string& private_key, OutputKeys& outkey)
{
    GetOutputKey(public_key, outkey.public_key);
    GetOutputKey(private_key, outkey.private_key);
    outkey.public_key_len = public_key.length();
    outkey.private_key_len = private_key.length();
    assert(public_key != private_key);
}

bool GenOpenSSLRSAKeys(OutputKeysVector& key_pairs_vector)
{
    //generate public and private key
    unsigned char public_key[1024] = { 0 };
    unsigned char private_key[1024] = { 0 };
    int public_key_len = sizeof(public_key);
    int private_key_len = sizeof(private_key);
    if (!MakeOpenSSLRSAKey(public_key, public_key_len, private_key, private_key_len))
    {
        fprintf(stderr, "ERROR!\n");
        return false;
    }

    std::string r_public_key((char*)public_key, public_key_len);
    std::string r_private_key((char*)private_key, private_key_len);

    key_pairs_vector.push_back(OutputKeys());
    OutputKeys& outkey = *key_pairs_vector.rbegin();
    GetOutputKeys(r_public_key, r_private_key, outkey);

    //check
//     {
//         npp::OpenSSLRSA rsa;
//         rsa.initialize((const unsigned char*)r_private_key.data(), r_private_key.length(),
//             (const unsigned char*)r_public_key.data(), r_public_key.length());
// 
//         const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
//         size_t raw_data_len = strlen(raw_data);
//         std::string sigret;
//         assert(rsa.sign(npp::OpenSSLRSA::ST_NID_sha1, raw_data, raw_data_len, sigret));
//         assert(rsa.verify(npp::OpenSSLRSA::ST_NID_sha1, raw_data, raw_data_len, sigret.data(), sigret.size()));
//     }

    return true;
}

bool GenSimpleRSAKeys(OutputKeysVector& key_pairs_vector)
{
    //generate public and private key
    unsigned char public_key[258] = { 0 };
    unsigned char private_key[706] = { 0 };
    int public_key_len = sizeof(public_key);
    int private_key_len = sizeof(private_key);
    if (!MakeSimpleRSAKey(public_key, private_key))
    {
        fprintf(stderr, "ERROR!\n");
        return false;
    }

    std::string r_public_key((char*)public_key, public_key_len);
    std::string r_private_key((char*)private_key, private_key_len);
    
    key_pairs_vector.push_back(OutputKeys());
    OutputKeys& outkey = *key_pairs_vector.rbegin();
    GetOutputKeys(r_public_key, r_private_key, outkey);


    //check
//     {
//         npp::SimpleRSA rsa;
//         rsa.initialize((const unsigned char*)r_private_key.data(), r_private_key.length(),
//             (const unsigned char*)r_public_key.data(), r_public_key.length());
// 
//         const char * raw_data = "0047880d4a1cf095fa4b13f9cc9f06f8";
//         size_t raw_data_len = strlen(raw_data);
//         std::string sigret;
//         assert(rsa.sign(raw_data, raw_data_len, sigret));
//         assert(rsa.verify(raw_data, raw_data_len, sigret.data(), sigret.size()));
//     }

    return true;
}


int main( int argc, char* argv[] )
{
    key_count = 4;
    begin_key_no = 1;

    GenTestKey();

    GenIDEAKey();
    
    OutputKeysVector openssl_rsa_keys_vect;
    OutputKeysVector simple_rsa_keys_vect;

    for (int jj = begin_key_no; jj < 2 * key_count + begin_key_no; jj++)
    {
        GenOpenSSLRSAKeys(openssl_rsa_keys_vect);
        GenSimpleRSAKeys(simple_rsa_keys_vect);
    }

    //output C++ header file
    {
        FILE* fp_server = fopen("server_rsa_key.h", "w+");
        FILE* fp_client = fopen("client_rsa_key.h", "w+");


        fprintf(fp_server, "#ifndef _SERVER_RSA_SIGN_KEY_H_ \n");
        fprintf(fp_server, "#define _SERVER_RSA_SIGN_KEY_H_ \n");
        fprintf(fp_client, "#ifndef _CLIENT_RSA_SIGN_KEY_H_ \n");
        fprintf(fp_client, "#define _CLIENT_RSA_SIGN_KEY_H_ \n");

        //server keys
        // k1: public_key1=rsa_keys_vect[0].public_key, private_key1=rsa_keys_vect[1].private_key
        // k2: public_key2=rsa_keys_vect[2].public_key, private_key2=rsa_keys_vect[3].private_key
        // k3: public_key3=rsa_keys_vect[4].public_key, private_key3=rsa_keys_vect[5].private_key
        // k4: public_key4=rsa_keys_vect[6].public_key, private_key4=rsa_keys_vect[7].private_key

        int jj = 0;
        const char* prefix = "server";
        for (jj = begin_key_no; jj < openssl_rsa_keys_vect.size()/2 + begin_key_no; jj++)
        {
            {
                OutputKeys& outkey = openssl_rsa_keys_vect[(jj - begin_key_no) * 2]; //public_key : 0,2,4,6
                const char* public_key = outkey.public_key.data();
                int public_key_len = outkey.public_key_len;
                const char* private_key = outkey.private_key.data();
                int private_key_len = outkey.private_key_len;

                fprintf(fp_server, "\nstatic const unsigned char g_%s_rsa_public_key%d[%lu] = {//{{{\n%s", prefix, jj, public_key_len, public_key);
                fprintf(fp_server, "};//}}}\n" );
                fprintf(fp_server, "static const size_t g_%s_rsa_public_key%d_len = %lu;\n\n", prefix, jj, public_key_len);
            }

            {
                OutputKeys& outkey = openssl_rsa_keys_vect[(jj - begin_key_no) * 2 + 1]; //private_key : 1,3,5,7
                const char* public_key = outkey.public_key.data();
                int public_key_len = outkey.public_key_len;
                const char* private_key = outkey.private_key.data();
                int private_key_len = outkey.private_key_len;

                fprintf(fp_server, "static const unsigned char g_%s_rsa_private_key%d[%lu] = {//{{{\n%s", prefix, jj, private_key_len, private_key );
                fprintf(fp_server, "};//}}}\n" );
                fprintf(fp_server, "static const size_t g_%s_rsa_private_key%d_len = %lu;\n\n", prefix, jj, private_key_len);
                fprintf(fp_server, "\n" );
            }
        }



        //client keys
        // k1: public_key1=rsa_keys_vect[1].public_key, private_key1=rsa_keys_vect[0].private_key
        // k2: public_key2=rsa_keys_vect[3].public_key, private_key2=rsa_keys_vect[2].private_key
        // k1: public_key3=rsa_keys_vect[5].public_key, private_key3=rsa_keys_vect[4].private_key
        // k2: public_key4=rsa_keys_vect[7].public_key, private_key4=rsa_keys_vect[6].private_key
        prefix = "client";
        for (jj = begin_key_no; jj < openssl_rsa_keys_vect.size()/2 + begin_key_no; jj++)
        {
            {
                OutputKeys& outkey = openssl_rsa_keys_vect[(jj - begin_key_no) * 2 + 1]; //public_key : 1,3,5,7
                const char* public_key = outkey.public_key.data();
                int public_key_len = outkey.public_key_len;
                const char* private_key = outkey.private_key.data();
                int private_key_len = outkey.private_key_len;

                fprintf(fp_client, "\nstatic const unsigned char g_%s_rsa_public_key%d[%lu] = {//{{{\n%s", prefix, jj, public_key_len, public_key);
                fprintf(fp_client, "};//}}}\n" );
                fprintf(fp_client, "static const size_t g_%s_rsa_public_key%d_len = %lu;\n\n", prefix, jj, public_key_len);
            }

            {
                OutputKeys& outkey = openssl_rsa_keys_vect[(jj - begin_key_no) * 2]; //private_key : 0,2,4,6
                const char* public_key = outkey.public_key.data();
                int public_key_len = outkey.public_key_len;
                const char* private_key = outkey.private_key.data();
                int private_key_len = outkey.private_key_len;

                fprintf(fp_client, "static const unsigned char g_%s_rsa_private_key%d[%lu] = {//{{{\n%s", prefix, jj, private_key_len, private_key );
                fprintf(fp_client, "};//}}}\n" );
                fprintf(fp_client, "static const size_t g_%s_rsa_private_key%d_len = %lu;\n\n", prefix, jj, private_key_len);
                fprintf(fp_client, "\n" );
            }
        }

        fprintf(fp_server, "//----------------------------------------------------------------\n");
        fprintf(fp_client, "//----------------------------------------------------------------\n");
        fprintf(fp_server, "//----------------------------------------------------------------\n");
        fprintf(fp_client, "//----------------------------------------------------------------\n");
        fprintf(fp_server, "//----------------------------------------------------------------\n");
        fprintf(fp_client, "//----------------------------------------------------------------\n");

        //simple rsa
        prefix = "server";
        for (jj = begin_key_no; jj < simple_rsa_keys_vect.size()/2 + begin_key_no; jj++)
        {
            {
                OutputKeys& outkey = simple_rsa_keys_vect[(jj - begin_key_no) * 2]; //public_key : 0,2,4,6
                const char* public_key = outkey.public_key.data();
                int public_key_len = outkey.public_key_len;
                const char* private_key = outkey.private_key.data();
                int private_key_len = outkey.private_key_len;

                fprintf(fp_server, "\nstatic const unsigned char g_%s_slrsa_public_key%d[%lu] = {//{{{\n%s", prefix, jj, public_key_len, public_key);
                fprintf(fp_server, "};//}}}\n" );
                fprintf(fp_server, "static const size_t g_%s_slrsa_public_key%d_len = %lu;\n\n", prefix, jj, public_key_len);
            }

            {
                OutputKeys& outkey = simple_rsa_keys_vect[(jj - begin_key_no) * 2 + 1]; //private_key : 1,3,5,7
                const char* public_key = outkey.public_key.data();
                int public_key_len = outkey.public_key_len;
                const char* private_key = outkey.private_key.data();
                int private_key_len = outkey.private_key_len;

                fprintf(fp_server, "static const unsigned char g_%s_slrsa_private_key%d[%lu] = {//{{{\n%s", prefix, jj, private_key_len, private_key );
                fprintf(fp_server, "};//}}}\n" );
                fprintf(fp_server, "static const size_t g_%s_slrsa_private_key%d_len = %lu;\n\n", prefix, jj, private_key_len);
                fprintf(fp_server, "\n" );
            }
        }

        prefix = "client";
        for (jj = begin_key_no; jj < simple_rsa_keys_vect.size()/2 + begin_key_no; jj++)
        {
            {
                OutputKeys& outkey = simple_rsa_keys_vect[(jj - begin_key_no) * 2 + 1]; //public_key : 1,3,5,7
                const char* public_key = outkey.public_key.data();
                int public_key_len = outkey.public_key_len;
                const char* private_key = outkey.private_key.data();
                int private_key_len = outkey.private_key_len;

                fprintf(fp_client, "\nstatic const unsigned char g_%s_slrsa_public_key%d[%lu] = {//{{{\n%s", prefix, jj, public_key_len, public_key);
                fprintf(fp_client, "};//}}}\n" );
                fprintf(fp_client, "static const size_t g_%s_slrsa_public_key%d_len = %lu;\n\n", prefix, jj, public_key_len);
            }

            {
                OutputKeys& outkey = simple_rsa_keys_vect[(jj - begin_key_no) * 2]; //private_key : 0,2,4,6
                const char* public_key = outkey.public_key.data();
                int public_key_len = outkey.public_key_len;
                const char* private_key = outkey.private_key.data();
                int private_key_len = outkey.private_key_len;

                fprintf(fp_client, "static const unsigned char g_%s_slrsa_private_key%d[%lu] = {//{{{\n%s", prefix, jj, private_key_len, private_key );
                fprintf(fp_client, "};//}}}\n" );
                fprintf(fp_client, "static const size_t g_%s_slrsa_private_key%d_len = %lu;\n\n", prefix, jj, private_key_len);
                fprintf(fp_client, "\n" );
            }
        }

        fprintf(fp_server, "\n\n#endif // end of #ifdef _SERVER_RSA_SIGN_KEY_H_\n\n\n");
        fprintf(fp_client, "\n\n#endif // endof #ifdef _CLIENT_RSA_SIGN_KEY_H_\n\n\n");

        fflush(fp_server);
        fflush(fp_client);

        fclose(fp_server);
        fclose(fp_client);
    } // end of Output C++ header file






    //Output php header file
    {
        //client keys
        // k1: public_key1=rsa_keys_vect[1].public_key, private_key1=rsa_keys_vect[0].private_key
        // k2: public_key2=rsa_keys_vect[3].public_key, private_key2=rsa_keys_vect[2].private_key
        // k1: public_key3=rsa_keys_vect[5].public_key, private_key3=rsa_keys_vect[4].private_key
        // k2: public_key4=rsa_keys_vect[7].public_key, private_key4=rsa_keys_vect[6].private_key

        FILE* fp_php_client = fopen("client_rsa_key.php", "w+");
        fprintf(fp_php_client, "<?php\n"
            "$sign_private_keys = array(\n"
            "\t//{{{ simple rsa private keys\n"
            "\t'simple' => array(\n"
            );

      
        for (int i = 0, jj = begin_key_no; jj < simple_rsa_keys_vect.size()/2 + begin_key_no; jj++, i++)
        {
            OutputKeys& outkey = simple_rsa_keys_vect[(jj - begin_key_no) * 2];
            const char* private_key = outkey.private_key.data();
            int private_key_len = outkey.private_key_len;
            fprintf(fp_php_client, "\t\t%d => pack('C%lu', %s),\n", jj, private_key_len, private_key);
        }
        fprintf(fp_php_client, "\t),\n//}}}\n");

        fprintf(fp_php_client, "\t'openssl' => array(//{{{\n");
        for (int i = 0, jj = begin_key_no; jj < openssl_rsa_keys_vect.size()/2 + begin_key_no; jj++, i++)
        {
            OutputKeys& outkey = openssl_rsa_keys_vect[(jj - begin_key_no) * 2];
            const char* private_key = outkey.private_key.data();
            int private_key_len = outkey.private_key_len;
            fprintf(fp_php_client, "\t\t%d => pack('C%lu', %s),\n", jj, private_key_len, private_key);
        }
        fprintf(fp_php_client, "\t),\n//}}}\n);\n\n");


        fprintf(fp_php_client, "$sign_public_keys = array(\n"
            "\t//{{{ simple rsa public keys\n"
            "\t'simple' => array(\n"
            );
        for (int i = 0, jj = begin_key_no; jj < simple_rsa_keys_vect.size()/2 + begin_key_no; jj++, i++)
        {
            OutputKeys& outkey = simple_rsa_keys_vect[(jj - begin_key_no) * 2 + 1];
            const char* public_key = outkey.public_key.data();
            int public_key_len = outkey.public_key_len;
            fprintf(fp_php_client, "\t\t%d => pack('C%lu', %s),\n", jj, public_key_len, public_key);
        }
        fprintf(fp_php_client, "\t),\n//}}}\n");

        {
            fprintf(fp_php_client, "\t'openssl' => array(//{{{\n");
            for (int i = 0, jj = begin_key_no; jj < openssl_rsa_keys_vect.size()/2 + begin_key_no; jj++, i++)
            {
                OutputKeys& outkey = openssl_rsa_keys_vect[(jj - begin_key_no) * 2 + 1];
                const char* public_key = outkey.public_key.data();
                int public_key_len = outkey.public_key_len;
                fprintf(fp_php_client, "\t\t%d => pack('C%lu', %s),\n", jj, public_key_len, public_key);
            }
            fprintf(fp_php_client, "\t),\n//}}}\n);\n\n");
        }

        fflush(fp_php_client);
        fclose(fp_php_client);
    }

    printf("Generate key OK!\n");
#ifdef WIN32
    system( "pause" );
#endif

    return 0;
}
