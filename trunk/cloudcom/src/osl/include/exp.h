
#ifndef QOSLIB_ALL_EXPORT_H_
#define QOSLIB_ALL_EXPORT_H_


#include "osl/include/inner_pre.h"

#ifdef H_OS_WINDOWS
//! Define import lib macro. Add it in ANY CPP file in target host module.
H_LINK_LIB( "osl");
#endif

#include "osl/include/mem_alloc.h"
#include "osl/include/string_ext.h"
#include "osl/include/object.h"
#include "osl/include/string_util.h"
#include "osl/include/data_stream.h"


#if H_PROVIDE_LOG_SYSTEM
#include "osl/include/log_manager.h"
#endif

#endif //#ifndef QOSLIB_ALL_EXPORT_H_


