#ifndef _NOSLIBPREREQUISITS_H
#define _NOSLIBPREREQUISITS_H

//! Compile configuration.
#include "hoslib/include/HCompileConfig.h"

//! include std headers
#include "hoslib/include/HStdHeaders.h"


// add windows include first.
#ifdef H_OS_WINDOWS
//#define WIN32_LEAN_AND_MEAN
#	include <winsock2.h>
#	include <windows.h>
#elif defined(H_OS_LINUX)
#	include <pthread.h>
#endif

//#define H_YOG_SERVER_FOR_YOG  //use YOG server as the YOG server

#define H_YOG_SERVER_FOR_NEW_RELEASE_VERSION  //use YOG server as the new HiPiHi virtual world server

//#define H_HEYUAN_SERVER     //use HEYUAN server as the new HiPiHi virtual world server


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
typedef unsigned int	 DWORD_PTR;
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



namespace OSLib
{

#ifdef H_ARC_64
    typedef unsigned long      u64;
    typedef long               s64;
#else
    typedef unsigned long long u64;
    typedef long long          s64;
#endif
    typedef unsigned int       u32;
    typedef int                s32;
    typedef unsigned short     u16;
    typedef short              s16;
    typedef unsigned char       u8;
    typedef char                s8;
    typedef float              f32;
    typedef double             f64;


#ifdef H_OS_WINDOWS
    typedef long                 AtomicInt32;
    typedef __int64               AtomicInt64;

#   ifdef H_ARCH_32
    typedef AtomicInt32            AtomicInt;
#   else
    typedef AtomicInt64            AtomicInt;
#   endif

#elif defined(H_OS_LINUX)

    typedef s32                 AtomicInt32;
    typedef long                AtomicInt64;

#   ifdef H_ARCH_32
    typedef AtomicInt32       AtomicInt;
#   else
    typedef AtomicInt64       AtomicInt;
#		endif
#endif


    //! Platform pointer.
#   ifdef H_ARCH_32
    typedef u32              PointerInt;
#   else
    typedef u64              PointerInt;
#   endif


#define H_S32_MAX	0x7fffffff  //! signed 32 bit long int max number
#define H_U32_MAX	0xffffffff  //! unsigned 32 bit long int max number

#define H_S64_MAX	0x7fffffffffffffff  //! signed 64 bit long int max number
#define H_U64_MAX	0xffffffffffffffff  //! unsigned 64 bit long int max number



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
    //#define max(a,b)            (((a) > (b)) ? (a) : (b))


    // Set/Clear/Test flag bit
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
    //! creates four CC codes used in Irrlicht for simple ids
    //! some compilers can create those by directly writing the
    //! code like 'code', but some generate warnings so we use this macro here
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

    //! Module symbol export
#ifdef H_WINDOWS_API
#	ifndef  H_STATIC_LIB_OSLIB
#		ifdef  H_OSLIB_EXPORTS
#			define _EXPORT_OSLIB __declspec(dllexport)
#		else
#			define _EXPORT_OSLIB __declspec(dllimport)
#		endif
#	else
#		define _EXPORT_OSLIB
#	endif
#else
#	define _EXPORT_OSLIB
#endif // H_STATIC_LIB_


    //! Initialize the library. It should be called before call any thing from the library.
    _EXPORT_OSLIB bool isOSLibInitialized();

    //! Initialize the library. It should be called before call any thing from the library.
    _EXPORT_OSLIB bool initializeOSLib();


    //! uninitialize lib
    _EXPORT_OSLIB void uninitializeOSLib();


    //! Do unit test for the module.
    class AppShell;
    //_EXPORT_OSLIB void preapreTestCommand( AppShell* pShell );
}; // end of namespace OSLib


#include "hoslib/include/HMemAlloc.h"
#include "hoslib/include/HSTLAllocator.h"
#include "hoslib/include/HSTLContainers.h"
#include "hoslib/include/HString.h"
#include "hoslib/include/HClassType.h"
#include "hoslib/include/HOS.h"
#include "hoslib/include/HObject.h"
#include "hoslib/include/HStringUtil.h"
#include "hoslib/include/HEventListeners.h"
#include "hoslib/include/HLog.h"
#include "hoslib/include/HSingleton.h"
#include "hoslib/include/HLock.h"
#include "hoslib/include/HLogManager.h"
#include "hoslib/include/HFunction.h"
#include "hoslib/include/HFunctionList.h"
#include "hoslib/include/HTimer.h"
#include "hoslib/include/HFastVector.h"
#include "hoslib/include/HDataStream.h"
#include "hoslib/include/HUUID.h"

#endif	//_NOSLIBPREREQUISITS_H



