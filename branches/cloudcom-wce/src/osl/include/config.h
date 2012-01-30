
#ifndef _OSLIB_CONFIG_H_
#define _OSLIB_CONFIG_H_

//Define to 1 if you want to use memory pool
#define H_PROVIDE_MEMORY_POOL 0

//Define to 1 if you want to use JSON parser
#define H_PROVIDE_JSON 1

//Define to 1 if you want to use XML parser
#define H_PROVIDE_XML_TINY 0

//Define to 1 if you want to use INI parser
#define H_PROVIDE_INI_PARSER 1 

//Define to 1 if you want to use multi-thread
#define H_PROVIDE_THREAD_EVENT_LOCK 1

//Define to 1 if you want to use log4cxx as your log system
#ifdef WINCE
#define H_PROVIDE_LOG_SYSTEM 0
#else
#define H_PROVIDE_LOG_SYSTEM 1
#endif

//Define to 1 if you want to parse command line parameters
#define H_PROVIDE_APPSHELL 1

//Define to 1 if you want to use MD5 algorithm
#define H_PROVIDE_MD5 1

//Define to 1 if you want to use RSA algorithm, using openssl
#define H_PROVIDE_RSA 0

//Define to 1 if you want to use CRC32 algorithm
#define H_PROVIDE_CRC32 1

//Define to 1 if you want to use BASE64 algorithm
#define H_PROVIDE_BASE64 1

//Define to 1 if you want to use IDEA encrypt wrapper helpers
#ifdef WINCE
#define H_PROVIDE_IDEA_ENCRYPT 0
#else
#define H_PROVIDE_IDEA_ENCRYPT 1
#endif

//Define to 1 if you want to use UUID algorithm
#define H_PROVIDE_UUID 0

//Define to 1 if you want to use a management of DLL
#ifdef WINCE
#define H_PROVIDE_DLL_MANAGER 0
#else
#define H_PROVIDE_DLL_MANAGER 1
#endif

//Define to 1 if you want to use Timer
#ifdef WINCE
#define H_PROVIDE_TIMER 0
#else
#define H_PROVIDE_TIMER 1
#endif

#endif

