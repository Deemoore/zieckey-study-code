#include "osl/include/osl_inner_pre.h"


#if H_PROVIDE_LOG_SYSTEM



#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"

#include "osl/include/log.h"

#include "osl/include/log_process_thread.h"

// #if ( defined(H_LOG_SYSTEM_USE_LOG4CXX) || defined(H_OS_LINUX) )
// #	include "log_impl.log4cxx.h"
// #else
// #	include "log_impl.h"
// #endif

#include "log_impl.std.h"

namespace osl
{
    const char*  Log::m_vLevelName[LML_NUM] =
    {
        "TRACE",        //! LML_TRACE = 0,        //!
        "DEBUG",		//! LML_DEBUG,   //! debug.

        "INFO ",
        "WARN ",      //! LML_WARN,         //! General warning.
        "ERROR",	    //! LML_ERROR,        //! Error.
        "FATAL",        //! LML_FATAL,        //! Fatal error.
    };
    //----------------------------------------------
    


    Log::Log( const StringA& strName, u32 nOptions,
              const StringA& strLogHost, const StringA& strLogPort )
    {
        m_pImpl = new Log::Impl( strName, nOptions, strLogHost, strLogPort );
    }
    //----------------------------------------------
    Log::~Log()
    {
        delete m_pImpl;
    }
    //----------------------------------------------
    void Log::logMessage( const char* message, size_t len, LogMessageLevel lml, const char* filename, int lineno )
    {
        H_NOTIFY_EVENTLISTENER_2( Listener, E_LOG, message, lml );

#ifdef H_USING_THREAD_TO_WRITE_LOG
        s_pLogManager->getLogProcessThread()->pushLogItem(this, message, lml);
#else
        m_pImpl->logMessage( message, len, lml, filename, lineno );
#endif
    }
    //----------------------------------------------
    void Log::logMessage( const char* message, size_t len, LogMessageLevel lml )
    {
        H_NOTIFY_EVENTLISTENER_2( Listener, E_LOG, message, lml );

#ifdef H_USING_THREAD_TO_WRITE_LOG
        s_pLogManager->getLogProcessThread()->pushLogItem(this, message, lml);
#else
        m_pImpl->logMessage( message, len, lml );
#endif
    }
    //----------------------------------------------
    void Log::logMessage( const StringA& message,	LogMessageLevel lml )
    {
        logMessage( message.c_str(), message.length(), lml );
    }
    //----------------------------------------------
    void Log::logMessage( const StringW& message,	LogMessageLevel lml )
    {
        H_NOTIFY_EVENTLISTENER_2( Listener, E_LOG, message, lml );

#ifdef H_USING_THREAD_TO_WRITE_LOG
        s_pLogManager->getLogProcessThread()->pushLogItem(this,message, lml);
#else        
        m_pImpl->logMessage( message, lml );
#endif
		
    }

    void Log::doLogMessage( const StringA& message,	LogMessageLevel lml )
	{
		m_pImpl->logMessage( message, lml );
	}
	void Log::doLogMessage( const StringW& message,	LogMessageLevel lml )
	{
		m_pImpl->logMessage( message, lml );
	}
    //----------------------------------------------
    bool Log::isDebugEnabled() const
    {
        return m_pImpl->isDebugEnabled();
    }
    //----------------------------------------------
    bool Log::isInfoEnabled() const
    {
        return m_pImpl->isInfoEnabled();
    }
    //----------------------------------------------
    bool Log::isWarnEnabled() const
    {
        return m_pImpl->isWarnEnabled();
    }
    //----------------------------------------------
    bool Log::isErrorEnabled() const
    {
        return m_pImpl->isErrorEnabled();
    }
    //----------------------------------------------
    bool Log::isFatalEnabled() const
    {
        return m_pImpl->isFatalEnabled();
    }
    //----------------------------------------------
    bool Log::isTraceEnabled() const
    {
        return m_pImpl->isTraceEnabled();
    }
    //----------------------------------------------
    bool Log::isLogEnabled( LogMessageLevel lml ) const
    {
        switch ( lml )
        {
            case LML_DEBUG:
                return m_pImpl->isLogEnabled( O_DEBUG );
                break;
            case LML_TRACE:
                return m_pImpl->isLogEnabled( O_TRACE );
                break;
            case LML_INFO:
                return m_pImpl->isLogEnabled( O_INFO );
                break;
            case LML_WARN:
                return m_pImpl->isLogEnabled( O_WARN );
                break;
            case LML_ERROR:
                return m_pImpl->isLogEnabled( O_ERROR );
                break;
            case LML_FATAL:
                return m_pImpl->isLogEnabled( O_FATAL );
                break;
            default:
                break;
        }

        return false;
    }
    //----------------------------------------------
    const char* Log::getLevelName( LogMessageLevel nLML )
    {
        if( u32( nLML ) < LML_NUM )
		{
			return m_vLevelName[nLML];
		}
		return NULL;
    }


	
};//namespace



#endif // #if H_PROVIDE_LOG_SYSTEM


