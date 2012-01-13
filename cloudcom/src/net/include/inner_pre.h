
#ifndef _QNETWORKLIB_H_NETPREREQUISITS_H__
#define _QNETWORKLIB_H_NETPREREQUISITS_H__


#include "osl/include/exp.h"

#include "osl/include/lock.h"
#include "osl/include/event.h"

#include "net/include/config.h"

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
