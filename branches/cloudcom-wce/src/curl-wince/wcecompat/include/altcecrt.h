/***
*altcecrt.h - definitions/declarations for time routines
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file has declarations of time routines and defines
*       the structure returned by the localtime and gmtime routines and
*       used by asctime.
*
****/

#if     _MSC_VER > 1000 /*IFSTRIP=IGN*/
#pragma once
#endif

#ifndef _INC_ALTCECRT
#define _INC_ALTCECRT

#if defined(_M_ARM) && !defined(_M_ARMT) && (_WIN32_WCE < 0x0500)
#pragma comment(lib, "secchk.lib")
#endif

#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")
#pragma comment(linker, "/nodefaultlib:oldnames.lib")

#include <sal.h>

#ifdef  __cplusplus

extern "C" {

#pragma warning(disable: 4201) // nameless unions are part of C++

#endif  /* __cplusplus */

#ifndef _CE_CRT_ALLOW_WIN_MINMAX
// This prevents the windows defines for min and max from conflictly with the CRT/CSL
#define NOMINMAX
#endif

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

#include <tchar.h>
#include <time.h>

#ifndef _CRTIMP
#ifdef  CRTDLL
#define _CRTIMP __declspec(dllexport)
#else   /* ndef CRTDLL */
#ifdef  _DLL
#define _CRTIMP __declspec(dllimport)
#else   /* ndef _DLL */
#define _CRTIMP
#endif  /* _DLL */
#endif  /* CRTDLL */
#endif  /* _CRTIMP */

#if !defined(__CRTDECL)
#if defined(_M_CEE_PURE)
#define __CRTDECL
#else
#define __CRTDECL   __cdecl
#endif
#endif

#include <crtdefs.h>


// Adding a definition since we dont compile realloc.c
#if (_WIN32_WCE < 0x600)
#if !defined(_CRTBLD)
#define _recalloc(p, n, s) realloc(p, n*s) /* we don't need this for CRT build */
#endif
#endif //#if (_WIN32_WCE < 0x600)

// crtdbg.h

typedef void *_HFILE; /* file handle pointer */

#define _CRT_WARN           0
#define _CRT_ERROR          1
#define _CRT_ASSERT         2
#define _CRT_ERRCNT         3

#define _CRTDBG_MODE_FILE      0x1
#define _CRTDBG_MODE_DEBUG     0x2
#define _CRTDBG_MODE_WNDW      0x4
#define _CRTDBG_REPORT_MODE    -1

#define _CRTDBG_INVALID_HFILE ((_HFILE)-1)
#define _CRTDBG_HFILE_ERROR   ((_HFILE)-2)
#define _CRTDBG_FILE_STDOUT   ((_HFILE)-4)
#define _CRTDBG_FILE_STDERR   ((_HFILE)-5)
#define _CRTDBG_REPORT_FILE   ((_HFILE)-6)

typedef int (__cdecl * _CRT_REPORT_HOOK)(int, char *, int *);

#ifndef _DEBUG

 /****************************************************************************
 *
 * Debug OFF
 * Debug OFF
 * Debug OFF
 *
 ***************************************************************************/

/*  We allow our basic _ASSERT macros to be overridden by pre-existing definitions. 
    This is not the ideal mechanism, but is helpful in some scenarios and helps avoid
    multiple definition problems */

#ifndef _ASSERT
#define _ASSERT(expr) ((void)0)
#endif 

#ifndef _ASSERTE
#define _ASSERTE(expr) ((void)0)
#endif

#define _CrtSetReportHook(f)                ((_CRT_REPORT_HOOK)0)
#define _CrtGetReportHook()                 ((_CRT_REPORT_HOOK)0)
#define _CrtSetReportMode(t, f)             ((int)0)
#define _CrtSetReportFile(t, f)             ((_HFILE)0)

#else   /* _DEBUG */

#include <kfuncs.h>

 /****************************************************************************
 *
 * Debug ON
 * Debug ON
 * Debug ON
 *
 ***************************************************************************/

_CRTIMP _CRT_REPORT_HOOK __cdecl _CrtSetReportHook
(
    _In_opt_ _CRT_REPORT_HOOK
);

_CRTIMP _CRT_REPORT_HOOK __cdecl _CrtGetReportHook
(
    void
);

_CRTIMP int __cdecl _CrtSetReportMode(
	_In_ int,
        _In_ int
        );

_CRTIMP _HFILE __cdecl _CrtSetReportFile(
        _In_ int,
        _In_opt_ _HFILE
        );

_CRTIMP int __cdecl _CrtDbgReportW(
        _In_ int,
        _In_opt_z_ const wchar_t *,
        _In_ int,
        _In_opt_z_ const wchar_t *,
        _In_opt_z_ const wchar_t *,
        ...);

/* Asserts */

#ifndef _CRT_WIDE
#define __CRT_WIDE(x) L ## x
#define _CRT_WIDE(x) __CRT_WIDE(x)
#endif

#if     _MSC_VER >= 1300 || !defined(_M_IX86) || defined(_CRT_PORTABLE) /*IFSTRIP=IGN*/
#define _ASSERT_BASE(expr, msg) \
        (void) ((expr) || \
                (1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, msg)) || \
                (_CrtDbgBreak(), 0))
#else
#define _ASSERT_BASE(expr, msg) \
        do { if (!(expr) && \
                (1 == _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, msg))) \
             _CrtDbgBreak(); } while (0)
#endif

#ifndef _ASSERT
#define _ASSERT(expr)   _ASSERT_BASE((expr), NULL)
#endif

#ifndef _ASSERTE
#define _ASSERTE(expr)  _ASSERT_BASE((expr), _CRT_WIDE(#expr))
#endif

#define _CrtDbgBreak() DebugBreak()

#endif  /* _DEBUG */

// limits.h
#ifndef SIZE_MAX
#ifdef _WIN64 
#define SIZE_MAX _UI64_MAX
#else
#define SIZE_MAX UINT_MAX
#endif
#endif
#ifndef LLONG_MAX
#define LLONG_MAX     9223372036854775807i64       /* maximum signed long long int value */
#endif
#ifndef LLONG_MIN
#define LLONG_MIN   (-9223372036854775807i64 - 1)  /* minimum signed long long int value */
#endif
#ifndef ULLONG_MAX
#define ULLONG_MAX    0xffffffffffffffffui64       /* maximum unsigned long long int value */
#endif

// malloc.h
#ifndef _malloca
#define _malloca malloc
#endif
#ifndef _freea
#define _freea free
#endif

// errno.h

/* Error Codes */

#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EINTR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#define EAGAIN          11
#define ENOMEM          12
#define EACCES          13
#define EFAULT          14
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define EINVAL          22
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32
#define EDOM            33
#define ERANGE          34
#define EDEADLK         36
// The CE SDK's have this constant defined to a value already
//#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
// The CE SDK's have this constant defined to a value already
//#define ENOTEMPTY       41
#define EILSEQ          42
#define STRUNCATE       80

// internal.h

 #ifndef _UINTPTR_T_DEFINED
 #ifdef  _WIN64
typedef unsigned __int64    uintptr_t;
 #else
typedef unsigned int   uintptr_t;
 #endif
 #define _UINTPTR_T_DEFINED
 #endif

_CRTIMP void __cdecl _invalid_parameter(_In_opt_z_ const wchar_t *, _In_opt_z_ const wchar_t *, _In_opt_z_ const wchar_t *, unsigned int, uintptr_t);
#ifndef _DEBUG
#if !defined(_NATIVE_WCHAR_T_DEFINED) && defined(_M_CEE_PURE)
extern "C++"
#endif
_CRTIMP 
void __cdecl _invalid_parameter_noinfo(void);
#endif


// stdio.h
#define FILENAME_MAX    260

// stdlib.h
#if (_WIN32_WCE < 0x600)
// WinCE 6.0 provides these functions in the OS CRT so we don't need them here
_CRTIMP errno_t __cdecl _itoa_s(int, _Out_z_cap_(_Size) char *, size_t _Size, int);
_CRTIMP errno_t __cdecl _itow_s (int, _Out_z_cap_(_Size) wchar_t *, size_t _Size, int);
_CRTIMP errno_t __cdecl _ltoa_s(long, _Out_z_cap_(_Size) char *, size_t _Size, int);
_CRTIMP errno_t __cdecl _ltow_s (long, _Out_z_cap_(_Size) wchar_t *, size_t _Size, int);
_CRTIMP errno_t __cdecl _ultoa_s(unsigned long, _Out_z_cap_(_Size) char *, size_t _Size, int);
_CRTIMP errno_t __cdecl _ultow_s (unsigned long, _Out_z_cap_(_Size) wchar_t *, size_t _Size, int);
#endif // (_WIN32_WCE <= 0x600)

_CRTIMP __int64   __cdecl _wcstoi64(const wchar_t *, _In_ _Deref_pre_valid_ wchar_t **, int);
_CRTIMP unsigned __int64  __cdecl _wcstoui64(const wchar_t *, _In_ _Deref_pre_valid_ wchar_t **, int);

#define _MAX_DRIVE  3   /* max. length of drive component */
#define _MAX_DIR    256 /* max. length of path component */
#define _MAX_FNAME  256 /* max. length of file name component */
#define _MAX_EXT    256 /* max. length of extension component */

// string.h
#if (_WIN32_WCE < 0x600)
// WinCE 6.0 provides these functions in the OS CRT so we don't need them here
_CRTIMP errno_t __cdecl memcpy_s(void *, size_t, const void *, size_t);
_CRTIMP errno_t __cdecl memmove_s(void *, size_t, const void *, size_t);
_CRTIMP errno_t __cdecl strcat_s(_Inout_z_cap_(_SizeInBytes) char *, _In_ size_t _SizeInBytes, _In_z_ const char *);
_CRTIMP errno_t __cdecl strcpy_s(_Out_cap_(_SizeInBytes) char *, _In_ size_t _SizeInBytes, _In_z_ const char *);
_CRTIMP errno_t __cdecl strncpy_s(_Out_cap_(_SizeInBytes) char *, _In_ size_t _SizeInBytes, _In_z_ const char *, _In_ size_t);
_CRTIMP errno_t __cdecl wcscat_s(_Inout_z_cap_(_SizeInWords) wchar_t *, _In_ size_t _SizeInWords, _In_z_ const wchar_t *);
_CRTIMP errno_t __cdecl wcscpy_s(_Out_cap_(_SizeInWords) wchar_t *, _In_ size_t _SizeInWords, _In_z_ const wchar_t *);
_CRTIMP errno_t __cdecl wcsncpy_s(_Out_cap_(_SizeInWords) wchar_t *, _In_ size_t _SizeInWords, _In_z_ const wchar_t *, _In_ size_t);
_CRTIMP size_t __cdecl wcsnlen(const wchar_t *, size_t);
#endif // (_WIN32_WCE <= 0x600)

// tchar.h
#if defined(UNICODE) || defined(_UNICODE)
#define __targv     __wargv
#define _itot_s    	_itow_s
#define _ltot_s     _ltow_s
#define _tcscat_s   wcscat_s
#define _tcscpy_s   wcscpy_s
#define _tcsdec     _wcsdec
#define _tcsftime   wcsftime
#define _tcsinc     _wcsinc
#define _tcsncpy_s  wcsncpy_s
#define _tcsnlen    wcsnlen
#define _tmakepath_s    _wmakepath_s
#define _tsplitpath_s   _wsplitpath_s
#define _ultot_s    _ultow_s
#endif // #if defined(UNICODE) || defined(_UNICODE)

// time.h
#ifndef _TIME64_T_DEFINED
#if     _INTEGRAL_MAX_BITS >= 64    /*IFSTRIP=IGN*/
typedef __int64 __time64_t;     /* 64-bit time value */
#endif
#define _TIME64_T_DEFINED
#endif

#ifndef _CRT_INSECURE_DEPRECATE
#define _CRT_INSECURE_DEPRECATE
#endif

_CRTIMP errno_t __cdecl _gmtime64_s(struct tm *ptm, const __time64_t *);
_CRTIMP errno_t __cdecl _localtime64_s(struct tm *ptm, const __time64_t *);

#if (_WIN32_WCE >= 0x600)
_CRTIMP size_t __cdecl wcsftime(wchar_t *, size_t, const wchar_t *, const struct tm *);
#else
// Necessary because the CE headers define the third parameter as char* instead of wchar_t*
#ifndef  __cplusplus
#define wcsftime(wstring, maxsize, wformat, timeptr) wcsftime(wstring, maxsize, (char*)stwformat, timeptr)
#else
// Provide a type safe version for C++
#define wcsftime(wstring, maxsize, wformat, timeptr) wcsftime(wstring, maxsize, reinterpret_cast<const char* const>(static_cast<const wchar_t* const>(wformat)), timeptr)
#endif
#endif	// #if _WIN32_WCE >= 0x600

_CRTIMP __time64_t __cdecl _mktime64(struct tm *);
_CRTIMP __time64_t __cdecl _time64(__time64_t *);

// wchar.h
_CRTIMP errno_t __cdecl _i64toa_s(__int64, _Out_z_cap_(_SizeInChars) char *, size_t _SizeInChars, int);
_CRTIMP errno_t __cdecl _i64tow_s(__int64, _Out_z_cap_(_SizeInChars) wchar_t *, size_t _SizeInChars, int);
_CRTIMP __int64 __cdecl _strtoi64(const char *, _Deref_opt_out_ char **, int);
_CRTIMP unsigned __int64 __cdecl _strtoui64(const char *, _Deref_opt_out_  char **, int);
_CRTIMP errno_t __cdecl _ui64toa_s(unsigned __int64, _Out_z_cap_(_Size) char *, size_t _Size, int);
_CRTIMP errno_t __cdecl _ui64tow_s(unsigned __int64, _Out_z_cap_(_Size) wchar_t *, size_t _Size, int);
_CRTIMP errno_t __cdecl _wmakepath_s(_Out_z_cap_(_Size) wchar_t *, size_t _Size, const wchar_t *, const wchar_t *, const wchar_t *,
        const wchar_t *);
_CRTIMP errno_t __cdecl _wsplitpath_s(const wchar_t *, _Out_opt_z_cap_(driveSizeInCharacters) wchar_t *, size_t driveSizeInCharacters, _Out_opt_z_cap_(dirSizeInCharacters) wchar_t *,
									  size_t dirSizeInCharacters, _Out_opt_z_cap_(nameSizeInCharacters) wchar_t *, size_t nameSizeInCharacters, _Out_opt_z_cap_(extSizeInCharacters) wchar_t *, size_t extSizeInCharacters);

__inline errno_t __CRTDECL wmemcpy_s(_Out_cap_post_count_(_N1,_N) wchar_t *_S1, size_t _N1, const wchar_t *_S2, size_t _N)
        {
            return memcpy_s(_S1, _N1*sizeof(wchar_t), _S2, _N*sizeof(wchar_t));
        }

__inline errno_t __CRTDECL wmemmove_s(_Out_cap_post_count_(_N1,_N) wchar_t *_S1, size_t _N1, const wchar_t *_S2, size_t _N)
        {
            return memmove_s(_S1, _N1*sizeof(wchar_t), _S2, _N*sizeof(wchar_t));
        }

#define _wcsinc(_pc)    ((_pc)+1)
#define _wcsdec(start, current) ((start >= current) ? NULL : (current - 1))

#ifdef  __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_ALTCECRT */


