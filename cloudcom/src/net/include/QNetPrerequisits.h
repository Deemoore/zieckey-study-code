
#ifndef _QNETWORKLIB_H_NETPREREQUISITS_H__
#define _QNETWORKLIB_H_NETPREREQUISITS_H__


//! Most commonly used headers.
#include "osl/include/QOSLibAllExp.h"

#include "net/include/QNetConfig.h"

#include "osl/include/QObject.h"
#include "osl/include/QString.h"
#include "osl/include/QThread.h"
#include "osl/include/QMyOS.h"
#include "osl/include/QLock.h"
#include "osl/include/QEvent.h"

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

};

#endif
