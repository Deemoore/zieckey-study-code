/*
	RSA.H - header file for RSA.C

	Copyright (c) J.S.A.Kapp 1994 - 1995.

	RSAEURO - RSA Library compatible with RSAREF(tm) 2.0.

	All functions prototypes are the Same as for RSAREF(tm).
	To aid compatiblity the source and the files follow the
	same naming comventions that RSAREF(tm) uses.  This should aid
	direct importing to your applications.

	This library is legal everywhere outside the US.  And should
	NOT be imported to the US and used there.

	All Trademarks Acknowledged.

	RSA Routines Header File.

	Revision 1.00 - JSAK 23/6/95, Final Release Version
*/

#include "global.h"

#ifdef __cplusplus
extern "C" {
#endif

/* RSA key lengths. */
	
#define MIN_RSA_MODULUS_BITS 508
/* 
	 PGP 2.6.2 Now allows 2048-bit keys changing below will allow this.
     It does lengthen key generation slightly if the value is increased.
*/
#define MAX_RSA_MODULUS_BITS 1024
#define MAX_RSA_MODULUS_LEN ((MAX_RSA_MODULUS_BITS + 7) / 8)
#define MAX_RSA_PRIME_BITS ((MAX_RSA_MODULUS_BITS + 1) / 2)
#define MAX_RSA_PRIME_LEN ((MAX_RSA_PRIME_BITS + 7) / 8)

/* RSA public and private key. */

typedef struct {
	unsigned short int bits;                     /* length in bits of modulus */
	unsigned char modulus[MAX_RSA_MODULUS_LEN];  /* modulus */
	unsigned char exponent[MAX_RSA_MODULUS_LEN]; /* public exponent */
} R_RSA_PUBLIC_KEY;

typedef struct {
	unsigned short int bits;                     /* length in bits of modulus */
	unsigned char modulus[MAX_RSA_MODULUS_LEN];  /* modulus */
	unsigned char publicExponent[MAX_RSA_MODULUS_LEN];     /* public exponent */
	unsigned char exponent[MAX_RSA_MODULUS_LEN]; /* private exponent */
	unsigned char prime[2][MAX_RSA_PRIME_LEN];   /* prime factors */
	unsigned char primeExponent[2][MAX_RSA_PRIME_LEN];     /* exponents for CRT */
	unsigned char coefficient[MAX_RSA_PRIME_LEN];          /* CRT coefficient */
} R_RSA_PRIVATE_KEY;

/* Random structure. */

typedef struct {
	unsigned int bytesNeeded;                    /* seed bytes required */
	unsigned char state[16];                     /* state of object */
	unsigned int outputAvailable;                /* number byte available */
	unsigned char output[16];                    /* output bytes */
} R_RANDOM_STRUCT;

/* Error codes. */

#define RE_CONTENT_ENCODING 0x0400
#define RE_DATA 0x0401
#define RE_DIGEST_ALGORITHM 0x0402
#define RE_ENCODING 0x0403
#define RE_KEY 0x0404
#define RE_KEY_ENCODING 0x0405
#define RE_LEN 0x0406
#define RE_MODULUS_LEN 0x0407
#define RE_NEED_RANDOM 0x0408
#define RE_PRIVATE_KEY 0x0409
#define RE_PUBLIC_KEY 0x040a
#define RE_SIGNATURE 0x040b
#define RE_SIGNATURE_ENCODING 0x040c
#define RE_ENCRYPTION_ALGORITHM 0x040d
/* Internal Error Codes */

#define RSA_IDOK    0
#define RSA_IDERROR 1

int RSAPublicEncrypt PROTO_LIST ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    R_RSA_PUBLIC_KEY *, R_RANDOM_STRUCT *));
int RSAPrivateEncrypt PROTO_LIST ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    R_RSA_PRIVATE_KEY *));
int RSAPublicDecrypt PROTO_LIST ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    R_RSA_PUBLIC_KEY *));
int RSAPrivateDecrypt PROTO_LIST ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    R_RSA_PRIVATE_KEY *));

#ifdef __cplusplus
}
#endif
