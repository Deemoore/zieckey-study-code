#include "osl/include/inner_pre.h"
#include <iostream>

// force to be compiled.

#include "osl/include/malloc_micro.h"

#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"

#if H_PROVIDE_LOG_SYSTEM
// #	define H_LOG_SYSTEM_USE_LOG4CXX
    #include "osl/include/log.h"
    #include "osl/include/log_manager.h"
#endif


// #if H_PROVIDE_THREAD_EVENT_LOCK
// #include "osl/include/thread.h"
// #endif

#if H_PROVIDE_TIMER
    #include "osl/include/timer.h"
#endif

#include "osl/include/process_ext.h"

//-------------------------------------------------------
//Windows lib
#ifdef H_WINDOWS_API
#	pragma comment(lib,"Ws2_32.lib")

// 	#ifdef _DEBUG // Debug mode so use debug library
// 	#  pragma comment(lib, "libcd.lib")
// 	#else // Release mode: do not use debug library
// 	#  pragma comment(lib, "libc.lib")
// 	#endif




// if use log4.
#ifdef H_LOG_SYSTEM_USE_LOG4CXX
	H_LINK_LIB( "log4cxx" );
#endif

#if H_PROVIDE_PCRE
#   ifdef H_DEBUG_MODE
#		pragma comment(lib, "pcre_d.lib")
#   else
#		pragma comment(lib, "pcre.lib")
#   endif
#endif

#else

#endif // H_WINDOWS_API
//-------------------------------------------------------



//openssl
#if H_PROVIDE_IDEA_ENCRYPT || H_PROVIDE_RSA
#ifdef H_WINDOWS_API
#	ifdef H_DEBUG_MODE
#		pragma comment(lib,"libeay32.lib")
#	else
#		pragma comment(lib,"libeay32.lib")
#	endif
#endif
#endif // end of #if ( H_PROVIDE_NET_CA_ENCRYPT && H_PROVIDE_IDEA_ENCRYPT )



namespace osl
{
    namespace _donotuseit
    {
        const char* _build_message =
            "=== bug report to [weizili@360.cn]. "
            "packet name [libqoslib.so]. "
            "packet version [1.0.18]. "
            "build time: [" __DATE__ " " __TIME__ "] ===";

        char _buf[2048] = {};
        static int _count = snprintf(_buf, sizeof(_buf), "%s", _build_message);
    }

    namespace
    {
        class AutoInitModule
        {
        public:
            AutoInitModule()
            {
                initializeOSLib();
            }

            ~AutoInitModule()
            {
                uninitializeOSLib();
            }
        };

        static AutoInitModule auto_init_module;
    }

    static bool s_bInitialized = false;

    //----------------------------------------------
    bool isOSLibInitialized()
    {
        return s_bInitialized;
    }
    //----------------------------------------------
    bool initializeOSLib()
    {
        if ( s_bInitialized )
        {
            return true;
        }

        // Initialize net work.
#ifdef H_OS_WINDOWS
        {
            WSADATA wsaData;
            // Initialize Winsock 2.2
            int nError =  WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) ;

            if ( nError )
            {
                std::cout << "WSAStartup() failed with error: %d" << nError;
                return false;
            }
        }
#endif

#if H_PROVIDE_MEMORY_POOL
        MemAlloc::initialize();
#endif

#if H_PROVIDE_LOG_SYSTEM
        LogManager::createInstance();
#endif

#if H_PROVIDE_TIMER
        Timer::createInstance();
        //new Timer();
#endif//#if H_PROVIDE_TIMER

        Process::initialize();
        Process::getBinDir();

        s_bInitialized = true;

        return true;
    }
    //----------------------------------------------
    void uninitializeOSLib()
    {
        if ( !s_bInitialized )
        {
            return;
        }

        s_bInitialized = false;

        Process::uninitialize();

#if H_PROVIDE_TIMER
        Timer::destroyInstance();
#endif//#if H_PROVIDE_TIMER

#if H_PROVIDE_LOG_SYSTEM
		LogManager::destroyInstance();
#endif

#if H_PROVIDE_MEMORY_POOL
        MemAlloc::uninitialize();
#endif

    }

};//namespace

