#include "osl/include/QOSLibPrerequisits.h"
#include <iostream>

// force to be compiled.

#include "osl/include/mem_alloc.h"

#include "osl/include/QObject.h"
#include "osl/include/QString.h"
#include "osl/include/QStringUtil.h"

#if H_PROVIDE_LOG_SYSTEM
// #	define H_LOG_SYSTEM_USE_LOG4CXX
    #include "osl/include/QLog.h"
    #include "osl/include/QLogManager.h"
#endif


// #if H_PROVIDE_THREAD_EVENT_LOCK
// #include "osl/include/QThread.h"
// #endif

#if H_PROVIDE_TIMER
    #include "osl/include/QTimer.h"
#endif

#include "osl/include/process_ext.h"

#include "../../../config.h"


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
    namespace donotuseit
    {
        const char* _bugreport  = "bug report to=" PACKAGE_BUGREPORT;
        const char* _packetstring  = "packet name=" PACKAGE_STRING;
        const char* _packetversion = "version=" PACKAGE_VERSION;
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
        //
        MemAlloc::initialize();

        StringUtil::initialize();

#if H_PROVIDE_LOG_SYSTEM
	    new LogManager();
#endif

#if H_PROVIDE_TIMER
        Timer::createInstance();
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
		delete s_pLogManager;
#endif

        StringUtil::uninitialize();


        MemAlloc::uninitialize();

    }

};//namespace

