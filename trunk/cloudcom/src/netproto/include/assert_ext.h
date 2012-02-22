/****************************** Module Header ********************************\
    Name: assert_ext.h
 Created: 2012/01/07 7:1:2012 17:27
  Author: weizili

 Purpose: 
\*****************************************************************************/
#ifndef OSLIB_ASSERT_EXT_H_
#define OSLIB_ASSERT_EXT_H_

#include "netproto/include/platform_micros.h"

//only use VC
//typedef char __error__[(expr)];
#define __static_assert2( expr , line ) typedef char __compiler_check__false__##line##__ [(expr)];
#define __static_assert1( expr , line ) __static_assert2( (expr) , line )

//! \def static_assert(expr,error) 
//! \brief static assert, now only can work on VC, similar with C++0x static_assert
#define static_assert(expr,error) __static_assert1( (expr) ,  __LINE__ )

namespace npp
{
    //! Trace the message.If in debug mode, it will print both to default log and output window,
    //! if in release mode, it only print to default log.
    _EXPORT_OSLIB void h_trace( const char* fmt, ... );

#ifdef H_OS_WINDOWS
    // no matter use or do not use ASSERT, we define the function.
    _EXPORT_OSLIB void h_assert( const wchar_t *expr,
        const wchar_t *filename,
        unsigned lineno );
#else

    // no matter use or do not use ASSERT, we define the function.
    _EXPORT_OSLIB void h_assert( const char *expr,
        const char *filename,
        unsigned lineno );

#endif
}

    // if assert is enabled.
#ifdef H_DEBUG_MODE
    #ifdef H_OS_WINDOWS
#define H_ASSERT( exp )  ( (exp) || (::npp::h_assert( L ## #exp, _CRT_WIDE(__FILE__), __LINE__), 0) )
    #else
        #define H_ASSERT( exp )  ( (exp) || (::npp::h_assert(#exp, __FILE__, __LINE__), 0) )
    #endif
    
#else
    #define H_ASSERT( exp )
#endif

namespace npp
{
    inline void h_trace( const char* fmt, ... )
    {
#ifdef H_DEBUG_MODE
        char out[2048] = {};

        va_list body;
        va_start( body, fmt );
        vsnprintf( out, sizeof(out), fmt, body ); //
        va_end( body );

        printf("%s\n", out);
#else
        // do nothing.
#endif
    }


#ifdef H_OS_WINDOWS
    //----------------------------------------------------------
    inline void h_assert( const wchar_t *expr,
                          const wchar_t *filename,
                          unsigned lineno )
    {
#ifdef H_DEBUG_MODE
    #ifdef H_OS_WINDOWS
        _wassert( expr, filename, lineno );
    #endif
#endif
    }
#else
    //----------------------------------------------------------
    inline void h_assert( const char *expr,
        const char *filename,
        unsigned lineno )
    {
#ifdef H_DEBUG_MODE
    #ifdef H_OS_FREEBSD
        __assert( __func__, filename, lineno, expr );
    #elif defined(H_OS_LINUX)
        __assert( expr, filename, lineno );
    #endif
#endif
    }
#endif
}


#endif //end of #ifndef OSLIB_ASSERT_EXT_H_


