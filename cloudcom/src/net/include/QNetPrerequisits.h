
#ifndef _QNETWORKLIB_H_NETPREREQUISITS_H__
#define _QNETWORKLIB_H_NETPREREQUISITS_H__


//! Most commonly used headers.
#include "osl/include/osl_exp.h"

#include "net/include/QNetConfig.h"

#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/thread.h"
#include "osl/include/process_ext.h"
#include "osl/include/lock.h"
#include "osl/include/event.h"

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
