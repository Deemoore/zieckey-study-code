#include "netproto/include/inner_pre.h"
#include <iostream>

//-------------------------------------------------------
//Windows lib
#ifdef H_WINDOWS_API
#	pragma comment(lib,"Ws2_32.lib")

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
#if H_NPP_PROVIDE_OPENSSL_RSA
#ifdef H_WINDOWS_API
#	ifdef H_DEBUG_MODE
#		pragma comment(lib,"libeay32.lib")
#	else
#		pragma comment(lib,"libeay32.lib")
#	endif
#endif
#endif // end of #if ( H_PROVIDE_NET_CA_ENCRYPT )

//openssl
#if H_NPP_PROVIDE_IDEA_ENCRYPT && !H_NPP_PROVIDE_OPENSSL_RSA
#ifdef H_WINDOWS_API
#	ifdef H_DEBUG_MODE
#		pragma comment(lib,"idea.lib")
#	else
#		pragma comment(lib,"idea.lib")
#	endif
#endif
#endif // end of #if ( H_PROVIDE_NET_CA_ENCRYPT )

#ifdef H_WINDOWS_API
#	ifdef H_DEBUG_MODE
#		pragma comment(lib,"slrsa.lib")
#	else
#		pragma comment(lib,"slrsa.lib")
#	endif
#endif



namespace npp
{
    namespace donotuseit
    {
        const char* _bugreport  = "bug report to weizili";
        const char* _packetstring  = "packet name cloudcom";
        const char* _packetversion = "version 1.0.17";
    }
// 
//     namespace
//     {
//         class AutoInitModule
//         {
//         public:
//             AutoInitModule()
//             {
//                 initializeOSLib();
//             }
// 
//             ~AutoInitModule()
//             {
//                 uninitializeOSLib();
//             }
//         };
// 
//         static AutoInitModule auto_init_module;
//     }
// 
//     static bool s_bInitialized = false;
// 
//     //----------------------------------------------
//     bool isOSLibInitialized()
//     {
//         return s_bInitialized;
//     }
//     //----------------------------------------------
//     bool initializeOSLib()
//     {
//         if ( s_bInitialized )
//         {
//             return true;
//         }
// 
//         // Initialize net work.
// #ifdef H_OS_WINDOWS
//         {
//             WSADATA wsaData;
//             // Initialize Winsock 2.2
//             int nError =  WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) ;
// 
//             if ( nError )
//             {
//                 std::cout << "WSAStartup() failed with error: %d" << nError;
//                 return false;
//             }
//         }
// #endif
// 
// #if H_NPP_PROVIDE_MEMORY_POOL
//         MemAlloc::initialize();
// #endif
// 
//         StringUtil::initialize();
// 
// #if H_PROVIDE_LOG_SYSTEM
// 	    new LogManager();
// #endif
// 
// #if H_PROVIDE_TIMER
//         //Timer::createInstance();
//         new Timer();
// #endif//#if H_PROVIDE_TIMER
// 
//         Process::initialize();
//         Process::getBinDir();
// 
//         s_bInitialized = true;
// 
//         return true;
//     }
//     //----------------------------------------------
//     void uninitializeOSLib()
//     {
//         if ( !s_bInitialized )
//         {
//             return;
//         }
// 
//         s_bInitialized = false;
// 
//         Process::uninitialize();
// 
// #if H_PROVIDE_TIMER
//         Timer::destroyInstance();
// #endif//#if H_PROVIDE_TIMER
// 
// #if H_PROVIDE_LOG_SYSTEM
// 		delete s_pLogManager;
// #endif
// 
//         StringUtil::uninitialize();
// 
// 
// #if H_NPP_PROVIDE_MEMORY_POOL
//         MemAlloc::uninitialize();
// #endif
// 
//     }

};//namespace

