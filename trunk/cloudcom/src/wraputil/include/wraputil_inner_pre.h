#ifndef _WRAPUTIL_INNER_PRE_H__
#define _WRAPUTIL_INNER_PRE_H__


//! Most commonly used headers.
#include "osl/include/osl_exp.h"

namespace wu
{
    //! Module symbol export
#ifdef H_WINDOWS_API
#	ifndef  H_STATIC_LIB_WRAPUTIL
#		ifdef  H_WRAPUTIL_EXPORTS
#			define _EXPORT_WRAPUTIL __declspec(dllexport)
#		else
#			define _EXPORT_WRAPUTIL __declspec(dllimport)
#		endif
#	else
#		define _EXPORT_WRAPUTIL
#	endif
#else
#	define _EXPORT_WRAPUTIL
#endif // H_STATIC_LIB_


    //! Is net initialized.
    _EXPORT_WRAPUTIL bool isWrapUtilInitialized();

    //! Initialize the library. It should be called before call any thing from the library.
    _EXPORT_WRAPUTIL bool initializeWrapUtil();

    //! Uninitialize the net library.
    _EXPORT_WRAPUTIL void uninitializeWrapUtil();

};

#endif
