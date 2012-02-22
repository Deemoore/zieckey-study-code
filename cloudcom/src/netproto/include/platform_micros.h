
#ifndef NETPROTO_PLATFROM_MICROS_H_
#define NETPROTO_PLATFROM_MICROS_H_


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <float.h>


//! Whether is debug mode
#ifdef _DEBUG
#	ifndef H_DEBUG_MODE
#		define H_DEBUG_MODE
#	endif
#endif

//! Define NDEBUG
#ifndef _DEBUG
#   ifndef NDEBUG
#       define NDEBUG
#   endif
#endif

//! Define Operation System.
#if ( defined(WIN32) || defined(WIN64) )
#	ifndef H_OS_WINDOWS
#		define H_OS_WINDOWS
#	endif
#	ifndef H_WINDOWS_API
#		define H_WINDOWS_API
#	endif

#elif defined(_XBOX)
#   pragma error "XBOX Platform Not Supported. Abort! Abort!"
//#	define H_OS_XBOX
//#	define H_WINDOWS_API

#elif defined(MACOSX)
#   pragma error "MACOSX Platform Not Supported. Abort! Abort!"
//#	define H_OS_MACOSX

#elif ( defined(__sparc__) || defined(__sun__) )
#   pragma error "SOLARIS Platform Not Supported. Abort! Abort!"
//#	define H_OS_SOLARIS

#elif ( defined(__linux__) || defined( __gnu_linux__) || defined(__GNUC__) )
#	define H_OS_LINUX

#else
#   pragma error "Unknown Platform Not Supported. Abort! Abort!"

#endif

#if defined( __FreeBSD__ )
#define  H_OS_FREEBSD
#endif



//! Find the arch type
#if defined(__x86_64__) || defined(__amd_64__) || defined(_M_X64)
#	ifndef H_ARCH_64
#		define H_ARCH_64
#	endif
#else
#	ifndef H_ARCH_32
#		define H_ARCH_32
#	endif
#endif



//! Endian
#ifdef H_OS_SOLARIS
#	ifndef H_BIG_ENDIAN
#		define H_BIG_ENDIAN
#	endif
#else
#	ifndef H_LITTLE_ENDIAN
#		define H_LITTLE_ENDIAN
#	endif
#endif



//! Finds the compiler type and version.
#if defined( _MSC_VER )
#	ifndef H_COMPILER_MSVC
#		define H_COMPILER_MSVC
#	endif
#	ifndef H_COMP_VER
#		define H_COMP_VER _MSC_VER
#	endif
#	if H_COMP_VER < 1300
#		pragma error "Not supported compiler version. Abort! Abort!"
#	endif

#elif defined( __GNUC__ )
#	ifndef H_COMPILER_GNUC
#		define H_COMPILER_GNUC
#	endif
#	ifndef H_COMP_VER
#		define H_COMP_VER (((__GNUC__)*100) + \
                           (__GNUC_MINOR__*10) + \
                           __GNUC_PATCHLEVEL__)
#	endif

#elif defined( __BORLANDC__ )
#	ifndef H_COMPILER_BORL
#	   define H_COMPILER_BORL
#	endif
#	ifndef H_COMP_VER
#		define H_COMP_VER __BCPLUSPLUS__
#	endif
#else
#   pragma error "No known compiler. Abort! Abort!"

#endif



#include <stdio.h> // TODO: Although included elsewhere this is required at least for mingw



//! See if we can use __forceinline or if we need to use __inline instead
#ifndef FORCEINLINE
#	ifdef  H_COMPILER_MSVC
#		define FORCEINLINE __forceinline
#	else
#		define FORCEINLINE __inline
#	endif
#endif


//! Use '/' as internal path splitor.
#ifndef H_PATH_SPLITOR
#	define H_PATH_SPLITOR  '/'
#endif


// For generating compiler warnings - should work on any compiler
// As a side note, if you start your message with 'Warning: ', the MSVC
// IDE actually does catch a warning :)
#ifndef H_HUOTE_INPLACE
#	define H_HUOTE_INPLACE(x) # x
#endif
#ifndef H_HUOTE
#	define H_HUOTE(x)         H_HUOTE_INPLACE(x)
#endif
#ifndef H_WARN
#	define H_WARN( x )        message( __FILE__ "(" HUOTE( __LINE__ ) ") : " x "\n" )
#endif


#ifdef H_COMPILER_MSVC

// Turn off warnings generated by long std templates
// This warns about truncation to 255 characters in debug/browse info
#   pragma warning (disable : 4786)

// Turn off warnings generated by long std templates
// This warns about truncation to 255 characters in debug/browse info
#   pragma warning (disable : 4503)

// disable: "conversion from 'double' to 'float', possible loss of data
#   pragma warning (disable : 4244)

// disable: "truncation from 'double' to 'float'
#   pragma warning (disable : 4305)

// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#   pragma warning (disable : 4251)

// disable: "non dll-interface class used as base for dll-interface class"
// Happens when deriving from Singleton because bug in compiler ignores
// template export
#   pragma warning (disable : 4275)

// disable: "C++ Exception Specification ignored"
// This is because MSVC 6 did not implement all the C++ exception
// specifications in the ANSI C++ draft.
#   pragma warning( disable : 4290 )

// disable: "no suitable definition provided for explicit template
// instantiation request" Occurs in VC7 for no justifiable reason on all
// #includes of Singleton
#   pragma warning( disable: 4661)


// disable: "unsupported code format"
#   pragma warning( disable: 4819)

// disable: deprecation warnings when using CRT calls in VC8
// These show up on all C runtime lib code in VC8, disable since they clutter
// the warnings with things we may not be able to do anything about (e.g.
// generated code from nvparse etc). I doubt very much that these calls
// will ever be actually removed from VC anyway, it would break too much code.
#	pragma warning( disable: 4996)

#endif // if H_COMPILER_MSVC


//! USE wide char.
//#define H_WIDE_CHAR

#ifndef HCHAR
#	ifdef H_WIDE_CHAR
typedef wchar_t     HCHAR;
#	    define H_STR( x ) L##x
#	else
typedef char     HCHAR;
#		define H_STR( x ) (x)
#	endif
#endif

#include <wchar.h>


#ifdef H_OS_WINDOWS
#	include <emmintrin.h>
#   ifdef __MINGW32__
#       include <basetyps.h>
#       include <io.h>
#   endif
#elif defined(H_OS_LINUX)
#	include <stdint.h>
#endif


#ifdef H_COMPILER_MSVC

//! Defines for s{w,n}printf because these methods do not match the ISO C
//! standard on Windows platforms, but it does on all others.
//! These should be int snprintf(char *str, size_t size, const char *format, ...);
//! and int swprintf(wchar_t *wcs, size_t maxlen, const wchar_t *format, ...);
#	if defined(_MSC_VER)
#		define swprintf  _snwprintf //swprintf is using in linux
#		define snwprintf _snwprintf
#		define snprintf _snprintf
#	else
#		define snwprintf swprintf
#		define snprintf snprintf
#	endif

#	ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#		define _WCHAR_T_DEFINED
#	endif



//! Defines a small statement to work around a microsoft compiler bug.
/** The microsft compiler 7.0 - 7.1 has a bug:
When you call unmanaged code that returns a bool type value of false from managed code,
the return value may appear as true. See
http://support.microsoft.com/default.aspx?kbid=823071 for details.
Compiler version defines: VC6.0 : 1200, VC7.0 : 1300, VC7.1 : 1310, VC8.0 : 1400*/
#ifndef H_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX
#	if (H_COMP_VER > 1299) && (H_COMP_VER < 1400)
#		define H_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX __asm mov eax,100
#	else
#		define H_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX
#	endif // 
#endif

//! ignore VC8 warning deprecated
/** The microsoft compiler */
#	if H_COMP_VER > 1400
#		pragma warning( disable: 4996)
#ifndef _CRT_SECURE_NO_DEPRECATE
#			define _CRT_SECURE_NO_DEPRECATE 1
#		endif
#		ifndef _CRT_NONSTDC_NO_DEPRECATE
#			define _CRT_NONSTDC_NO_DEPRECATE 1
#		endif
#	endif


#endif // H_COMPILER_MSVC


// Declare the calling convention.
#ifndef H_CALLCONV
#	if defined(_STDCALL_SUPPORTED)
#		define H_CALLCONV __stdcall
#	else
#		define H_CALLCONV __cdecl
#	endif // H_OS_WINDOWS
#endif



//////////////////////////////////////////////////////////////////////////
//                              Link Helper Macro                       //
//  Use: H_LINK_LIB(libname) to import a library.                       //
//////////////////////////////////////////////////////////////////////////
//------------------------------------------------------
#ifdef H_OS_WINDOWS
#	define H_LINK_OS_FLAG 1
#else
#	define H_LINK_OS_FLAG 0
#endif

#ifdef H_DEBUG_MODE
#	define H_LINK_FILE_DEBUG_FLAG 1
#else
#	define H_LINK_FILE_DEBUG_FLAG 0
#endif

#define H_LINK_FILE_DEBUG_1( filename )	__pragma ( comment( lib , filename##"_d"##".lib" ))
#define H_LINK_FILE_DEBUG_0( filename )	__pragma (comment( lib , filename##".lib" ))

#define H_LINK_FILE_DEBUG_P(filename,y)   H_LINK_FILE_DEBUG_##y(filename)

#define H_LINK_FILE_0(filename,y)
#define H_LINK_FILE_1(filename,y)         H_LINK_FILE_DEBUG_P(filename,y)

#define H_LINK_FILE_PP( filename , sys )  H_LINK_FILE_##sys( filename , H_LINK_FILE_DEBUG_FLAG )
#define H_LINK_FILE_P( filename , sys )   H_LINK_FILE_PP( filename , sys )


//
#ifndef __MINGW32__
#   define H_LINK_LIB( filename )           H_LINK_FILE_P( filename , H_LINK_OS_FLAG )
#else
#   define H_LINK_LIB( filename )
#endif

// End for Library link macros.
//------------------------------------------------------




/*
* Sizes for buffers used by the _makepath() and _splitpath() functions.
* note that the sizes include space for 0-terminator
*/
#ifndef _MAX_PATH
#	define _MAX_PATH   260 /* max. length of full pathname */
#endif

#ifndef _MAX_DIR
#	define _MAX_DIR    256 /* max. length of path component */
#endif

#ifndef _MAX_FNAME
#	define _MAX_FNAME  256 /* max. length of file name component */
#endif

#ifndef _MAX_EXT
#	define _MAX_EXT    256 /* max. length of extension component */
#endif

#endif // _H_COMPILECONFIG__


#ifndef NOMINMAX
#	define NOMINMAX
#endif


#ifdef H_OS_WINDOWS
#   define atoi64 _atoi64
#   define atoll _atoi64
#else
#   define atoi64 atoll
#   define _atoi64 atoll
#endif
#define atoi32 atoi
#define atof64 atof

#ifdef H_OS_WINDOWS
#   define strcasecmp stricmp
#   define strncasecmp strnicmp
#else
#   define stricmp strcasecmp //Linux
#   define strnicmp strncasecmp //Linux
#endif



#ifdef H_OS_WINDOWS
#   define rmdir _rmdir
#else
#   define _rmdir rmdir //Linux
#endif


//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
#undef H_DISALLOW_EVIL_CONSTRUCTORS
#define H_DISALLOW_EVIL_CONSTRUCTORS(TypeName)			\
	TypeName(const TypeName&);                          \
	void operator=(const TypeName&)

// from google3/base/basictypes.h
// The H_ARRAYSIZE(arr) macro returns the # of elements in an array arr.
// The expression is a compile-time constant, and therefore can be
// used in defining new arrays, for example.
//
// H_ARRAYSIZE catches a few type errors.  If you see a compiler error
//
//   "warning: division by zero in ..."
//
// when using H_ARRAYSIZE, you are (wrongfully) giving it a pointer.
// You should only use H_ARRAYSIZE on statically allocated arrays.
//
// The following comments are on the implementation details, and can
// be ignored by the users.
//
// ARRAYSIZE(arr) works by inspecting sizeof(arr) (the # of bytes in
// the array) and sizeof(*(arr)) (the # of bytes in one array
// element).  If the former is divisible by the latter, perhaps arr is
// indeed an array, in which case the division result is the # of
// elements in the array.  Otherwise, arr cannot possibly be an array,
// and we generate a compiler error to prevent the code from
// compiling.
//
// Since the size of bool is implementation-defined, we need to cast
// !(sizeof(a) & sizeof(*(a))) to size_t in order to ensure the final
// result has type size_t.
//
// This macro is not perfect as it wrongfully accepts certain
// pointers, namely where the pointer size is divisible by the pointee
// size.  Since all our code has to go through a 32-bit compiler,
// where a pointer is 4 bytes, this means all pointers to a type whose
// size is 3 or greater than 4 will be (righteously) rejected.
//
// Kudos to Jorg Brown for this simple and elegant implementation.
#undef H_ARRAYSIZE
#define H_ARRAYSIZE(a) \
	((sizeof(a) / sizeof(*(a))) / \
	static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

#define H_ARRAY_SIZE H_ARRAYSIZE

// namespace npp 
// {
// 	namespace internal {
// 		template <bool>
// 		struct CompileAssert {
// 		};
// 	}  // namespace internal
// #undef GOOGLE_COMPILE_ASSERT
// #define GOOGLE_COMPILE_ASSERT(expr, msg) 
// 	typedef ::npp::internal::CompileAssert<(bool(expr))> 
// 	msg[bool(expr) ? 1 : -1]
// } // namespace npp 
// 

#ifdef H_OS_WINDOWS
    #include <direct.h>
    #include <process.h>
#elif defined( H_OS_FREEBSD )
    #include <sys/sysctl.h>
#elif defined( H_OS_LINUX )
    #include <unistd.h>
    #include <errno.h>
#endif


#ifdef H_OS_WINDOWS
    #define ThreadID DWORD
#else
    #define ThreadID pthread_t
#endif


#ifndef H_ATTRIBUTE_ALWAYS_INLINE
#if defined(__GNUC__) && (__GNUC__ > 3 ||(__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
// For functions we want to force inline.
// Introduced in gcc 3.1.
#define H_ATTRIBUTE_ALWAYS_INLINE __attribute__ ((always_inline))
#else
// Other compilers will have to figure it out for themselves.
#define H_ATTRIBUTE_ALWAYS_INLINE
#endif
#endif



    //! Module symbol export
#ifdef H_WINDOWS_API
#   ifndef  H_STATIC_LIB_NETPROTO
#       ifdef  H_NETPROTO_EXPORTS
#           define _EXPORT_NETPROTO __declspec(dllexport)
#           define _EXPORT_NETPROTO_C extern "C" __declspec(dllexport)
#		else
#           define _EXPORT_NETPROTO __declspec(dllimport)
#           define _EXPORT_NETPROTO_C extern "C" __declspec(dllimport)
#       endif
#	else
#       define _EXPORT_NETPROTO
#       define _EXPORT_NETPROTO_C
#   endif
#else
#   define _EXPORT_NETPROTO
#endif // H_STATIC_LIB_





#ifdef H_OS_WINDOWS
    #define __func__            __FUNCTION__
    #define __PRETTY_FUNCTION__ __FUNCTION__

    #ifdef H_ARCH_64
    typedef unsigned long      uint64_t;
    typedef long               int64_t;
    #else
    typedef unsigned long long uint64_t;
    typedef long long          int64_t;
    #endif //end of H_ARCH_64
    typedef unsigned int       uint32_t;
    typedef int                int32_t;
    typedef unsigned short     uint16_t;
    typedef short              int16_t;
    typedef unsigned char      uint8_t;
    typedef char               int8_t;
#endif /* #ifdef H_OS_WINDOWS */










namespace npp
{

#ifdef H_ARCH_64
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
    typedef __int64              AtomicInt64;

#   ifdef H_ARCH_32
    typedef AtomicInt32            AtomicInt;
#   else
    typedef AtomicInt64            AtomicInt;
#   endif

#elif defined(H_OS_LINUX)

    typedef s32                  AtomicInt32;
    typedef long                 AtomicInt64;

#   ifdef H_ARCH_32
    typedef AtomicInt32            AtomicInt;
#   else
    typedef AtomicInt64            AtomicInt;
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
}



/**
* Alignment macros
*/

/* H_ALIGN() is only to be used to align on a power of 2 boundary */
#define H_ALIGN(size, boundary) (((size) + ((boundary) - 1)) & ~((boundary) - 1))

/** Default alignment */
#define H_ALIGN_DEFAULT(size) H_ALIGN(size, 8)

