#include "net/include/QNetPrerequisits.h"


#include "osl/include/QObject.h"
#include "osl/include/QString.h"
#include "osl/include/QThread.h"
#include "osl/include/process_ext.h"
#include "osl/include/QLock.h"

#include "net/include/QCURLWork.h"
#include "net/include/QCURLService.h"
#include "net/include/QHttpGetWork.h"
#include "net/include/QHttpPostFile.h"
#include "net/include/QHttpPostWork.h"


#ifdef H_WINDOWS_API
#	ifdef H_DEBUG_MODE
#		pragma comment(lib,"libcurld_imp.lib")
#	else
#		pragma comment(lib,"libcurl_imp.lib")
#	endif
//! linked in OSLIB
#	pragma comment(lib,"Ws2_32.lib")
#endif


#ifdef H_OS_LINUX
#include <signal.h>
// set signal handler
void sig_pipe( int id )
{
	//H_LOG_NAME_DEBUG( "", "a pipe arrived.");
    // do nothing.
	//printf( "signal pipe:%d", id );
}
void sig_child( int )
{
    //H_LOG_NAME_DEBUG( "", "a child thread terminated." );
    // do nothing.
}

#endif

namespace net
{

    static bool s_bInitialized = false;

    //----------------------------------------------
    bool isNetInitialized()
    {
        return s_bInitialized;
    }
    //----------------------------------------------
    bool initializeNet()
    {
        // initialize.
        osl::initializeOSLib();

        if ( s_bInitialized )
        {
            return true;
        }

#ifdef H_WINDOWS_API

#elif defined(H_OS_LINUX)

        // set signal handler
/*		if( 0 )		//! added by heda,we need core dump to back trace bug
        {

            //if( signal( SIGPIPE, sig_pipe )== SIG_ERR )
            if ( signal( SIGPIPE, sig_pipe ) == SIG_ERR )
            {
                H_LOG_NAME_ERROR( "", "Can not set SIGPIPE signal handler." );
            }

            if ( signal( SIGSEGV, sig_pipe ) == SIG_ERR )
            {
                H_LOG_NAME_ERROR( "", "Can not set SIGSEGV signal handler." );
            }

            if ( signal( SIGXCPU, sig_pipe ) == SIG_ERR )
            {
                H_LOG_NAME_ERROR( "", "Can not set SIGXCPU signal handler." );
            }

            if ( signal( SIGPWR, sig_pipe ) == SIG_ERR )
            {
                H_LOG_NAME_ERROR( "", "Can not set SIGPWR signal handler." );
            }
        }*/

#endif

#if H_PROVIDE_CURL
        CURLWork::initCURLGlobal();
#endif
		

        s_bInitialized = true;

        return true;
    }
    //----------------------------------------------
    void uninitializeNet()
    {
        if ( !s_bInitialized )
        {
            return;
        }

        s_bInitialized = false;

#if H_PROVIDE_CURL
        CURLWork::cleanupCURLGlobal();
#endif
    }
};

