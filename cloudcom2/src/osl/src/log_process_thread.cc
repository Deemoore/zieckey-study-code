#include "osl/include/inner_pre.h"


#if H_PROVIDE_LOG_SYSTEM



#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"
#include "osl/include/thread.h"
#include "osl/include/log.h"
#include "osl/include/log_manager.h"

#include "osl/include/log_process_thread.h"


namespace osl
{

	LogProcessThread::LogProcessThread( void )
	{

	}


	LogProcessThread::~LogProcessThread( void )
	{
	}

	bool LogProcessThread::start()
	{
		if ( !isInitialized() )
		{
			if ( -1 == init() )
			{
				H_LOG_NAME_ERROR( "", "LogProcessThread init failed." );
				return false;
			}
		}

		osl::Thread::start();

		// wait for start.
		while ( !isRunning() )
		{
			osl::Process::msSleep( 5 );
		}

		return true;
	}
	void LogProcessThread::stop()
	{
		osl::Thread::stop();

		m_eventWait.signal();

		// wait for exit.
		while ( !isStopped() )
		{
			osl::Process::msSleep( 5 );
			m_eventWait.signal();
		}

		H_LOG_NAME_DEBUG( "CURLWorkThread", "A work thread exited." );
	}
	int LogProcessThread::init()
	{
		if ( m_bInitialized )
		{
			return 0;
		}

		m_bInitialized = true;
		m_bIsProcessing = false;
		//m_listProcessingLogItem
		return 0;
	}
	void LogProcessThread::run()
	{

		for ( ; ; )
		{
			if ( !isRunning() )
			{
				H_LOG_NAME_INFO( "", "" );
				break;
			}

            if ( m_listLogItemToBeProcessed.empty() )
            {
                m_eventWait.wait();
            }	

			doLogMessages();


		}// end while(1)

	}
	void LogProcessThread::doLogMessages()
	{
		m_bIsProcessing = true;
		{
			H_MINI_AUTOLOCK( m_listLogItemLock );
			m_listLogItemBeingProcessed.swap( m_listLogItemToBeProcessed );
			
		}

		LogItemList::iterator  it = m_listLogItemBeingProcessed.begin();
		LogItemList::iterator  end = m_listLogItemBeingProcessed.end();

		for( ; it != end; ++it )
		{
			if( ( *it )->m_pLog != NULL )
			{
				( *it )->m_pLog->doLogMessage( ( *it )->m_strMsg, ( *it )->m_eLvl );
			}
		}//

		m_listLogItemBeingProcessed.clear();
		m_bIsProcessing = false;

	}

	void LogProcessThread::pushLogItem( Log* log, const osl::StringA &message, osl::LogMessageLevel lml)
	{
#ifdef H_USING_THREAD_TO_WRITE_LOG
		{
			H_MINI_AUTOLOCK( m_listLogItemLock );
			m_listLogItemToBeProcessed.push_back( H_NEW CLogItem(log,message,lml) );
		}
		if(!m_bIsProcessing)
		{
			m_eventWait.signal();
		}		
#endif
	}
	void LogProcessThread::pushLogItem( Log* log, const osl::StringW &message, osl::LogMessageLevel lml)
	{
#ifdef H_USING_THREAD_TO_WRITE_LOG
		{
			H_MINI_AUTOLOCK( m_listLogItemLock );
			m_listLogItemToBeProcessed.push_back( H_NEW CLogItem(log,StringUtil::wsToMbs( message ),lml) );
		}
		if(!m_bIsProcessing)
		{
			m_eventWait.signal();
		}	
#endif
	}


};//namespace



#endif // #if H_PROVIDE_LOG_SYSTEM


