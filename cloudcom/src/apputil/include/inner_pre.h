
#ifndef _QNETWORKLIB_H_NETPREREQUISITS_H__
#define _QNETWORKLIB_H_NETPREREQUISITS_H__


//! Most commonly used headers.
#include "net/include/exp.h"

#include "apputil/include/config.h"


namespace aut
{


    //! Module symbol export
#ifdef H_WINDOWS_API
#	ifndef  H_STATIC_LIB_APP_UTIL
#		ifdef  H_APP_UTIL_EXPORTS
#			define _EXPORT_APPUTIL __declspec(dllexport)
#		else
#			define _EXPORT_APPUTIL __declspec(dllimport)
#		endif
#	else
#		define _EXPORT_APPUTIL
#	endif
#else
#	define _EXPORT_APPUTIL 
#endif // H_STATIC_LIB_


    //! Is net initialized.
    _EXPORT_APPUTIL bool isAppUtilInitialized();

    //! Initialize the library. It should be called before call any thing from the library.
    _EXPORT_APPUTIL bool initializeAppUtil();

    //! Uninitialize the net library.
    _EXPORT_APPUTIL void uninitializeAppUtil();

};

#endif
