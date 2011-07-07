#pragma once

#include "hcommon/include/HCommonLibAllExp.h"

#define P2PNS_NAMESPACE_BEGIN namespace P2PNS{
#define P2PNS_NAMESPACE_END };

P2PNS_NAMESPACE_BEGIN

//! Module symbol export
#ifdef H_WINDOWS_API
#	ifndef  H_STATIC_LIB_P2PNEGSERVER
#		ifdef  H_P2PNEGSERVER_EXPORTS
#			define _EXPORT_P2PNEGSERVER __declspec(dllexport)
#		else
#			define _EXPORT_P2PNEGSERVER __declspec(dllimport)
#		endif
#	else
#		define _EXPORT_P2PNEGSERVER
#	endif
#else
#	define _EXPORT_P2PNEGSERVER
#endif // H_STATIC_LIB_



    //! Initialize
    bool initializeP2PNegServer();

    //! initialize
    void uninitializeP2PNegServer();


P2PNS_NAMESPACE_END



