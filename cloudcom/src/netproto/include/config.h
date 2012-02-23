#ifndef _NETPROTO_CONFIG_H_
#define _NETPROTO_CONFIG_H_

//Define to 1 if you want to use memory pool
#define H_PROVIDE_MEMORY_POOL 0

//Define to 1 if you want to use MD5 algorithm
#define H_PROVIDE_MD5 1

//Define to 1 if you want to use RSA algorithm, using openssl
#define H_PROVIDE_RSA 1
#define H_USING_OPENSSL_RSA H_PROVIDE_RSA

//Define to 1 if you want to use BASE64 algorithm
#define H_PROVIDE_BASE64 1

//Define to 1 if you want to use IDEA encrypt wrapper helpers
#define H_PROVIDE_IDEA_ENCRYPT 1


#endif

