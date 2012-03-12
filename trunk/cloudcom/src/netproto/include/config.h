#ifndef _NETPROTO_TOTAL_CONFIG_H_
#define _NETPROTO_TOTAL_CONFIG_H_

//Define to 1 if you want to use memory pool
//#define H_NPP_PROVIDE_MEMORY_POOL 0

//Define to 1 if you want to use MD5 algorithm
#define H_NPP_PROVIDE_MD5 1

//Define to 1 if you want to use RSA algorithm, using openssl
#define H_NPP_PROVIDE_OPENSSL_RSA 1

//Define to 1 if you want to use IDEA encrypt wrapper helpers
#define H_NPP_PROVIDE_IDEA_ENCRYPT 1

//Define to 1 if you want to use zlib
#define H_NPP_PROVIDE_ZLIB 1

//Define to 1 if you want to support protocol version 1
#define H_NPP_SUPPORT_PROTO_V1 1

//Define to 1 if you want to support protocol version 2 in server
#define H_NPP_SUPPORT_PROTO_SERVER_V2 1

//Define to 1 if you want to support protocol version 2 in client
#define H_NPP_SUPPORT_PROTO_CLIENT_V2 1


#endif

