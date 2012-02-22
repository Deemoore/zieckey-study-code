#include "osl/include/inner_pre.h"


#if H_PROVIDE_THREAD_EVENT_LOCK


#include "osl/include/event.h"

#ifdef H_OS_WINDOWS

#elif defined(H_OS_LINUX)

#	include <time.h>
#	include <sys/time.h>

#endif


namespace osl
{
	//----------------------------------------------
	Event::Event()
	{
#ifdef H_OS_WINDOWS

		m_hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

#elif defined(H_OS_LINUX )
		pthread_mutex_init( &m_hMutex, NULL );
		pthread_cond_init( &m_hCond, NULL );
        signaled_ = false;
#endif

	}
	//----------------------------------------------
	Event::~Event()
	{
#ifdef H_OS_WINDOWS

		CloseHandle( m_hEvent );

#elif defined(H_OS_LINUX )

		pthread_mutex_destroy( &m_hMutex );
		pthread_cond_destroy( &m_hCond );

#endif

	}
	//----------------------------------------------
	bool Event::wait( u32 msWait )
	{
#ifdef H_OS_WINDOWS

		return ( WaitForSingleObject( m_hEvent, msWait ) == WAIT_OBJECT_0 ) ? true : false;

#elif defined(H_OS_LINUX )

		{
			struct timeval tp;
			struct timespec ts;
			gettimeofday( &tp, NULL );
			ts.tv_sec = tp.tv_sec;
			ts.tv_nsec = tp.tv_usec * 1000;
			int second = msWait / 1000;
			int nsecond = ( msWait % 1000 ) * 1000 * 1000;
			ts.tv_sec += second;
			ts.tv_nsec += nsecond;

			if ( ts.tv_nsec > 1000000000 )
			{
				ts.tv_nsec -= 1000000000;
				ts.tv_sec++;
			}

			int rc = 1;
			pthread_mutex_lock( &m_hMutex );

			if (!signaled_)
			{
				rc = ( pthread_cond_timedwait( &m_hCond, &m_hMutex, &ts ) == 0 );
			}

			signaled_ = false;
			pthread_mutex_unlock( &m_hMutex );

			return rc == 0 ? true : false;
		}
#endif
	}

	//----------------------------------------------
	void Event::signal()
	{
#ifdef H_OS_WINDOWS

		SetEvent( m_hEvent );

#elif defined(H_OS_LINUX )

		pthread_mutex_lock( &m_hMutex );
		signaled_ = true;
		pthread_cond_signal( &m_hCond );
		pthread_mutex_unlock( &m_hMutex );
#endif
	}

};//namespace


#endif // end of #if H_PROVIDE_THREAD_EVENT_LOCK

