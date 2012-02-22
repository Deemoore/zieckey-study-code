#ifndef QOSLIB_ALL_EXPORT_H_
#define QOSLIB_ALL_EXPORT_H_


#include "netproto/include/inner_pre.h"

#ifdef H_OS_WINDOWS
//! Define import lib macro. Add it in ANY CPP file in target host module.
H_LINK_LIB( "osl");
#endif

#include "netproto/include/data_stream.h"


#endif //#ifndef QOSLIB_ALL_EXPORT_H_


