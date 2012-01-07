
#ifndef QAPP_UTILITY_ALL_EXPORT_H_
#define QAPP_UTILITY_ALL_EXPORT_H_


#include "net/include/QNetworkLibAllExp.h"

#include "apputil/include/QAppUtilConfig.h"

#ifdef H_OS_WINDOWS
H_LINK_LIB( "apputil")
#endif // end of #ifdef H_OS_WINDOWS
//! Define import lib macro. Add it in ANY CPP file in target host module.

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

}





#endif // end of #ifndef QAPP_UTILITY_ALL_EXPORT_H_



