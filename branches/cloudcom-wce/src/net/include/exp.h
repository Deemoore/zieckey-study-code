#ifndef QNETWORKLIB_ALL_EXPORT_H_
#define QNETWORKLIB_ALL_EXPORT_H_


#include "osl/include/exp.h"

#include "net/include/config.h"

#ifdef H_OS_WINDOWS
//! Define import lib macro. Add it in ANY CPP file in target host module.
//H_LINK_LIB( "net")
#pragma comment(lib, "net.lib")
#endif // end of #ifdef H_OS_WINDOWS

namespace net
{
#	define _EXPORT_NET
    //! Is net initialized.
    _EXPORT_NET bool isNetInitialized();

    //! Initialize the library. It should be called before call any thing from the library.
    _EXPORT_NET bool initializeNet();

    //! Uninitialize the net library.
    _EXPORT_NET void uninitializeNet();

}






#include "net/include/curl_work.h"
#include "net/include/http_get_work.h"
#include "net/include/http_post_file.h"
#include "net/include/http_post_work.h"
#include "net/include/curl_service.h"

#endif // end of #ifndef QNETWORKLIB_ALL_EXPORT_H_



