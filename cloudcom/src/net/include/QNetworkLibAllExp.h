#ifndef QNETWORKLIB_ALL_EXPORT_H_
#define QNETWORKLIB_ALL_EXPORT_H_


#include "osl/include/osl_exp.h"

#include "net/include/QNetConfig.h"

#ifdef H_OS_WINDOWS
//! Define import lib macro. Add it in ANY CPP file in target host module.
H_LINK_LIB( "net")
#endif // end of #ifdef H_OS_WINDOWS

namespace net
{


    //! Module symbol export
#ifdef H_WINDOWS_API
#	ifndef  H_STATIC_LIB_NET
#		ifdef  H_NET_EXPORTS
#			define _EXPORT_NET __declspec(dllexport)
#		else
#			define _EXPORT_NET __declspec(dllimport)
#		endif
#	else
#		define _EXPORT_NET
#	endif
#else
#	define _EXPORT_NET
#endif // H_STATIC_LIB_


    //! Is net initialized.
    _EXPORT_NET bool isNetInitialized();

    //! Initialize the library. It should be called before call any thing from the library.
    _EXPORT_NET bool initializeNet();

    //! Uninitialize the net library.
    _EXPORT_NET void uninitializeNet();

}







#endif // end of #ifndef QNETWORKLIB_ALL_EXPORT_H_



