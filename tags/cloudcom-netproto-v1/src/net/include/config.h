
#ifndef NETWORKLIB_CONFIG_H_
#define NETWORKLIB_CONFIG_H_

#include "osl/include/config.h"

//Define to 1 if you want to use curl wrapper lib
#define H_PROVIDE_CURL 1

//This curl lib wrapper dependent with H_PROVIDE_THREAD_EVENT_LOCK
#if H_PROVIDE_CURL 
	#if !H_PROVIDE_THREAD_EVENT_LOCK
		#error "The CURL wrapper depend on osl::Thread, please recompile osl with H_PROVIDE_THREAD_EVENT_LOCK flag on, H_PROVIDE_THREAD_EVENT_LOCK is difined in libcommon/src/osl/include/config.h"
	#endif
#endif

#endif

