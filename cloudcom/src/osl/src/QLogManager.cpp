#include "osl/include/QOSLibPrerequisits.h"


#if H_PROVIDE_LOG_SYSTEM

#include "osl/include/assert_ext.h"


#ifdef H_LOG_SYSTEM_USE_LOG4CXX
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#endif 


#ifdef H_OS_WINDOWS
#elif defined(H_OS_LINUX)
#   include <sys/stat.h>
#   include <stdarg.h>
#endif

#include <iostream>


#include "osl/include/object.h"
#include "osl/include/QString.h"
#include "osl/include/QStringUtil.h"
#include "osl/include/QThread.h"
#include "osl/include/QLog.h"
#include "osl/include/QLogManager.h"
#include "osl/include/QLogProcessThread.h"

namespace osl
{





    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////

    MiniLock  s_lkLogManager;

    //-----------------------------------------------------------------
    int LogManager::test_verify_point_index = 0;

    //-----------------------------------------------------------------------
    template<> LogManager* Singleton<LogManager>::ms_Singleton = 0;

    //-----------------------------------------------------------------------
    LogManager::LogManager()
    {
#if defined(H_LOG_SYSTEM_USE_LOG4CXX) 
        std::string strProperties = ( Process::getConfDir() + "/log4cxx.properties" ).c_str();
        struct stat vStat;

        if ( stat( strProperties.c_str(), &vStat ) == 0 )
        {
            log4cxx::PropertyConfigurator::configure( strProperties );
        }
        else
        {

            log4cxx::BasicConfigurator::configure();
        }
#endif

		//
		m_bAllStdOut = true;

        /*
        u32 nOptions = Log::O_ERROR | Log::O_FATAL | Log::O_WARN | Log::O_TOFILE | Log::O_INFO | Log::O_STDOUT | Log::O_TRACE;
#ifdef H_DEBUG_MODE
        nOptions |= Log::O_DEBUG;
#endif
        m_pDefaultLog = createLog( "default", nOptions );
        */

        //We don't need to create this Default log at start time.
        //getDefaultLog(); 

#ifdef H_USING_THREAD_TO_WRITE_LOG
        m_pLogProcessThread = H_NEW LogProcessThread();
        if( m_pLogProcessThread )
        {
            m_pLogProcessThread->start();
        }
        else
        {
            H_LOG_NAME_ERROR( "", "LogProcessThread build failed." );
        }
#endif

		//m_logProcessThread = H
    }
    //-----------------------------------------------------------------------
    LogManager::~LogManager()
    {
        //LOG_DEBUG_ONOFF( HSTR(""), 1 )
        //LOG_DEBUG( HSTR("") )

        //LOG_LEVEL_DEBUG( HSTR(""), 1 )
        //LOG_DEBUG_LEVEL_ONOFF( HSTR(""), 1, 1 )
#ifdef H_USING_THREAD_TO_WRITE_LOG
		delete m_pLogProcessThread;
		m_pLogProcessThread = NULL;
#endif
    }
    //-----------------------------------------------------------------------
	void LogManager::setAllStdOut( bool bAllStdOut )
	{
		m_bAllStdOut = bAllStdOut;
	}
    //-----------------------------------------------------------------------
    Log* LogManager::createLog( const String& name, u32 nOptions,
                                const StringA& strLogHost, const StringA& strLogPort )
    {
        H_MINI_AUTOLOCK( s_lkLogManager );

        LogPtr& pLog = m_mapLog[name];

        if ( !pLog )
        {
            pLog = H_NEW Log( name, nOptions, strLogHost, strLogPort );
        }

        return pLog.getPointer();
    }
    //-----------------------------------------------------------------------
    Log* LogManager::getDefaultLog()
    {
        if ( !m_pDefaultLog )
        {
            m_pDefaultLog = getLog( "" );
        }
        return m_pDefaultLog;
    }
    //-----------------------------------------------------------------------
    Log* LogManager::getLog( const StringA& name )
    {
        H_MINI_AUTOLOCK( s_lkLogManager );

        LogPtr& pLog = m_mapLog[name];

        if ( !pLog )
        {
            u32 nOptions = Log::O_ERROR | Log::O_FATAL | Log::O_WARN | Log::O_TOFILE | Log::O_INFO | Log::O_STDOUT | Log::O_TRACE;

#ifdef H_DEBUG_MODE
            nOptions |= Log::O_DEBUG;
#endif
            pLog = H_NEW Log( name, nOptions, "", "" );
        }

        H_ASSERT( pLog );

        return pLog.getPointer();

    }


}//namespace


#endif // #if H_PROVIDE_LOG_SYSTEM


