#pragma once

#include "hcommon/include/HCommonLibAllExp.h"

#define P2PC_NAMESPACE_BEGIN namespace P2PC{
#define P2PC_NAMESPACE_END };

P2PC_NAMESPACE_BEGIN

//! Module symbol export
#ifdef H_WINDOWS_API
#	ifndef  H_STATIC_LIB_P2PCLIENT
#		ifdef  H_P2PCLIENT_EXPORTS
#			define _EXPORT_P2PCLIENT __declspec(dllexport)
#		else
#			define _EXPORT_P2PCLIENT __declspec(dllimport)
#		endif
#	else
#		define _EXPORT_P2PCLIENT
#	endif
#else
#	define _EXPORT_P2PCLIENT
#endif // H_STATIC_LIB_



    //! Initialize
    _EXPORT_P2PCLIENT bool initializeP2PClient();

    //! initialize
    _EXPORT_P2PCLIENT void uninitializeP2PClient();


P2PC_NAMESPACE_END

