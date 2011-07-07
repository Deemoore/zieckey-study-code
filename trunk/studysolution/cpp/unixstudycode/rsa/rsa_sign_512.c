#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/md5.h>
//#include <md5.h>
#define  MD5Init    MD5_Init
#define  MD5Update  MD5_Update
#define  MD5Final   MD5_Final


//int nid=NID_sha1;
int nid=NID_sha1;
//int nid=64;


/*
* rsa_type = 1, return privatekey
* rsa_type = 2, return publickey
*/
RSA* create_rsa( const u_char* key, size_t key_len, int iBits, int rsa_type )
{/*{{{*/

    BIGNUM * bne = NULL;
    int ret = 0;
    RSA* rsa = NULL;

/*    bne = BN_new();
    ret = BN_set_word( bne, RSA_F4 );
    rsa = RSA_new();
    ret = RSA_generate_key_ex( rsa, iBits, bne, NULL );

    if( ret != 1 )
    {
        return NULL;
    }
*/
    BIO* b = NULL;
    b = BIO_new( BIO_s_mem() );
    BIO_write( b, key, key_len );

    if( rsa_type == 1 )
    {
        rsa = d2i_RSAPrivateKey_bio( b, NULL );
    }
    else if( rsa_type == 2 )
    {
        rsa = d2i_RSAPublicKey_bio( b, NULL );
    }

    BIO_free( b );

    return rsa;
}/*}}}*/


RSA* Rsagenkey()
{
    int iBits=512;
    unsigned long e=RSA_F4;
    BIGNUM* bne;
    int ret=0,len=0;
    RSA* rsa;


    bne=BN_new();
    ret=BN_set_word(bne, e);
    rsa=RSA_new();
    ret=RSA_generate_key_ex(rsa, iBits, bne, NULL);


    if(ret==1)
        return rsa;
    else
        return NULL;
}
void Sign(RSA* rsa, unsigned char* bData, unsigned int iDatalen)
{
    unsigned char bSign[1024]= {0};
    unsigned int iSignlen=sizeof(bSign);

    int ret,i;

    iSignlen=RSA_size(rsa);

    ret=RSA_sign(nid, bData, iDatalen, bSign, &iSignlen, rsa);

    
    printf("\nsign_len:%d\n",iSignlen);
    for(i=0;i<iSignlen;i++)
        printf("%d ",bSign[i]);
    printf("\n");
    
    if(ret!=1)
    {
        int l;
        char s[1024];
        FILE* f;

        f=fopen("/dev/stdout", "w");
        ERR_print_errors_fp(f);

        l=ERR_get_error();
        ERR_error_string_n(l,s,sizeof(s));
        perror(s);
        exit(1);
    }
}

int main (int argc, const char * argv[]) {


    RSA* rsa;
    unsigned char bData[32] = "59f0aa0a1c3f65f459f0aa0a1c3f65f4";
    unsigned int iDatalen;
    int i=0,ret;
    iDatalen=sizeof(bData);
    rsa=Rsagenkey();

    unsigned char  public_key[1024],private_key[1024];
    int len_public,len_private,len;
    BIO *b;
    b=BIO_new(BIO_s_mem());
    ret=i2d_RSAPublicKey_bio(b,rsa);
    len_public=BIO_read(b,public_key,1024);

    printf("\npublic_len:%d\n",len_public);

    for(i=0; i<len_public; i++)
        printf("%d,",public_key[i]);

    printf("\n");

    ret=i2d_RSAPrivateKey_bio(b,rsa);

    len_private=BIO_read(b,private_key,1024);
    BIO_free(b);

    printf("\nprivate_len:%d\n",len_private);

    for(i=0; i<len_private; i++)
        printf("%d,",private_key[i]);
    printf("\n");

    struct timeval btv;
    gettimeofday(&btv, NULL);

    //for(i=0; i<100; i++)
    {
        Sign(rsa,bData,iDatalen);
    }

    struct timeval tv;
    gettimeofday(&tv, NULL);
    long cost = 1000000 * (tv.tv_sec - btv.tv_sec) + (tv.tv_usec - btv.tv_usec);
    printf("\nsign_cost:%d\n",cost);


    RSA* rsa_private = create_rsa( private_key, len_private, 512, 1 );
    Sign(rsa_private,bData,iDatalen);


    return 0;
}
