#ifndef _NNETPROTOPREREQUISITS_H
#define _NNETPROTOPREREQUISITS_H

#include "netproto/include/config.h"

//! Compile configuration.
#include "netproto/include/platform_micros.h"

//! include std headers
#include "netproto/include/std_headers.h"

// add windows include first.
#ifdef H_OS_WINDOWS
#	include <winsock2.h>
#	include <windows.h>
#elif defined(H_OS_LINUX)
#	include <pthread.h>
#endif

//! Define something used by windows and not defined by Linux.
#ifdef H_OS_LINUX

#ifndef SOCKET
#	define SOCKET int		    /**< SOCKET definition */
#endif
#ifndef INVALID_SOCKET
#	define INVALID_SOCKET -1	/**< invalid socket definition */
#endif

typedef unsigned char        BYTE;
typedef unsigned short	     WORD;
typedef unsigned int        DWORD;
typedef unsigned int	DWORD_PTR;
#ifndef PTRINT
#	define PTRINT
#endif
#ifndef HIWORD
#	define HIWORD(l)        WORD((DWORD(l) & 0xffff0000) >> 16)
#endif
#ifndef LOWORD
#	define LOWORD(l)        WORD(DWORD(l) & 0xffff )
#endif

#ifndef MAKEWORD
#	define MAKEWORD( l,h)     (((WORD(BYTE(l)) & 0xff))|((WORD(BYTE(h)) & 0xff) << 8 ))
#endif

#ifndef LOBYTE
#	define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#endif

#ifndef HIBYTE
#	define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))
#endif

#	ifndef _HASH_SEED
#		define _HASH_SEED  (size_t)0xdeadbeef
#	endif

#endif

#ifndef MAKEDWORD
#	define MAKEDWORD( l,h)    (((DWORD(WORD(l)) & 0xffff)) | ((DWORD(WORD(h)) & 0xffff) << 16 ))
#endif


namespace npp
{


    //useful macros
#ifndef H_SAFE_DELETE
#	define H_SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif
#ifndef H_SAFE_DELETE_ARRAY
#	define H_SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif

    // safe ref/unref
#ifndef H_SAFE_REF
#	define H_SAFE_REF(p)          { if(p) { (p)->ref();  } }
#endif
#ifndef H_SAFE_UNREF
#	define H_SAFE_UNREF(p)		   { if(p) { (p)->unref(); (p)=NULL; } }
#endif



    // std::set/Clear/Test flag bit
#ifndef H_FLAG_SET
#	define H_FLAG_SET(    flag, bits )  ( (flag)  |= (bits) )
#endif
#ifndef H_FLAG_CLEAR
#	define H_FLAG_CLEAR( flag, bits )   ( (flag)  &= ~(bits) )
#endif
#ifndef H_FLAG_ISSET
#	define H_FLAG_ISSET(  flag, bits )  ( ((flag) & (bits) )?true:false )
#endif
#ifndef H_BYTE_ALIGN
#	define H_BYTE_ALIGN( val, align )   ( ( (val) + ( (align) - 1 )) & ~(align) )
#endif

#ifndef H_MAKE_ID
#	define H_MAKE_ID(c0, c1, c2, c3)                         \
    ((u32)(u8)(c0) | ((u32)(u8)(c1) << 8) |   \
     ((u32)(u8)(c2) << 16) | ((u32)(u8)(c3) << 24 ))
#endif


    //! absolute value
    // a MUST be signed value.
#define H_ABS(a)   ( ( (a) >> 31 ^ (a) ) + ( ( (unsigned int)(a) ) >> 31 ) )

    //! Micro of disable the copy and assignment constructor.
#define H_DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);               \
    TypeName& operator=(const TypeName&)


#ifndef ___IN
#	define ___IN //! in parameter
#endif

#ifndef ___OUT
#	define ___OUT //! out parameter
#endif


#ifndef H_MAX
#	define H_MAX(a,b) (((a)>(b)) ? (a) : (b))
#endif

#ifndef H_MIN
#define H_MIN(a,b) (((a)<(b)) ? (a) : (b))
#endif


#define H_CASE_STRING_BIGIN(state) switch(state){
#define H_CASE_STRING(state) case state:return #state;break;
#define H_CASE_STRING_END  default: return "unknown"; break; }

// #ifdef H_DEBUG_MODE
//     #define H_ASSERT assert
// #else
//     #define H_ASSERT
// #endif
//     


//do nothing now, after we write log system code we will use these micros
// #define H_LOG_NAME_DEBUG( strName, message )  
// #define H_LOG_NAME_TRACE( strName, message )  
// #define H_LOG_NAME_INFO( strName, message )   
// #define H_LOG_NAME_WARN( strName, message )   
// #define H_LOG_NAME_ERROR( strName, message )  
// #define H_LOG_NAME_FATAL( strName, message )  

}; // end of namespace npp

#endif	//_NNETPROTOPREREQUISITS_H




