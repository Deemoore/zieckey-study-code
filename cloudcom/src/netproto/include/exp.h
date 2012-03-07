#ifndef NETPROTO_ALL_EXPORT_H_
#define NETPROTO_ALL_EXPORT_H_


#include "netproto/include/inner_pre.h"

#ifdef H_OS_WINDOWS
//! Define import lib macro. Add it in ANY CPP file in target host module.
H_LINK_LIB( "netproto");
#endif

#include "netproto/include/data_stream.h"
#include "netproto/include/v1_message_packer.h"
#include "netproto/include/v1_message_unpacker.h"

#endif //#ifndef NETPROTO_ALL_EXPORT_H_


