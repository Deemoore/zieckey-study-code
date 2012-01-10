#include "osl/include/inner_pre.h"


#if H_PROVIDE_THREAD_EVENT_LOCK


#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"
#include "osl/include/thread.h"
#include "osl/include/process_ext.h"
#include "osl/include/scoped_int_counter.h"

#include "osl/include/lock.h"

#ifdef H_OS_LINUX
//#define H_LINUX_THREAD_PRIORITY
#endif




#ifdef H_OS_WINDOWS
#	include <process.h>
#elif defined(H_OS_LINUX)

#endif

namespace osl
{
#ifdef H_OS_WINDOWS
	DWORD           s_thread_key = 0;
#elif defined(H_OS_LINUX)
	pthread_key_t   s_thread_key = 0;
#else

#endif

#ifdef H_OS_WINDOWS
    volatile long s_nNumWorkingThread = 0;
#elif defined(H_OS_LINUX)
    volatile s32  s_nNumWorkingThread = 0;
#endif

#ifdef H_OS_WINDOWS
    volatile long s_nNumThreads = 0;
#elif defined(H_OS_LINUX)
    volatile s32  s_nNumThreads = 0;
#endif

	Thread*   s_pMainThread = NULL;

	class MainThread : public Thread
	{
	public:
		MainThread()
		{
			s_pMainThread = this;

#ifdef H_OS_WINDOWS
			m_hThread = ::GetCurrentThread();
			s_thread_key = TlsAlloc();
			TlsSetValue( s_thread_key , this );

#elif defined(H_OS_LINUX)
			//m_hThread
			pthread_key_create( &s_thread_key, NULL );
			pthread_setspecific( s_thread_key, this );
#else

#endif
			m_nState = S_RUNNING;
		}
		~MainThread()
		{
			m_nState = S_NULL;

			s_pMainThread = NULL;
#ifdef H_OS_WINDOWS
			TlsFree( s_thread_key );

#elif defined(H_OS_LINUX)

#else

#endif
			s_thread_key = 0;


		}

		bool start()
		{
			return true;
		}
		void stop()             {}
		bool join( u32 msWait )
		{
			return false;
		}
		virtual void terminate() {}
		void run()
		{
			// do nothing.
		}
	};



	
	//----------------------------------------------
	Thread::Thread()
		: m_nState( Thread::S_NULL )
		, m_nPriority( Thread::THREAD_PRIORITY_NOMINAL )
		, m_hThread( 0 )
	{
		if ( InterlockedInc32( &s_nNumThreads ) == 1 && !s_pMainThread )
		{
			H_NEW MainThread();
		}

		// set initial name.
		m_strName = "Unknown Thread";

#ifdef H_LINUX_THREAD_PRIORITY
        pthread_attr_init( &m_thread_attr );
        pthread_attr_setschedpolicy( &m_thread_attr, SCHED_RR );
#endif
	}
	//----------------------------------------------
	Thread::~Thread()
	{
		// thread.
		if ( InterlockedDec32( &s_nNumThreads ) == 1 && s_pMainThread )
		{
			delete s_pMainThread;
		}

		if ( m_nState != S_NULL )
		{
			terminate();
		}

#ifdef H_LINUX_THREAD_PRIORITY
        pthread_attr_destroy( &m_thread_attr );
#endif
	}
	//----------------------------------------------
	Thread* Thread::getCurrentThread()
	{
#ifdef H_OS_WINDOWS
		// return thread.
		return ( Thread* )TlsGetValue( s_thread_key );
#elif defined(H_OS_LINUX)
		return static_cast<Thread *>( pthread_getspecific( s_thread_key ) );
#endif

	}
	//----------------------------------------------
	s32 Thread::getNumWorkingThread()
	{
		return s_nNumWorkingThread;
	}
	//----------------------------------------------
	void Thread::setPriority( Thread::ThreadPriority nPriority )
	{
		m_nPriority = nPriority;

		if ( !m_hThread )
		{
			return;
		}

#ifdef H_OS_WINDOWS

		int nOSPriority = THREAD_PRIORITY_NORMAL;

		switch ( m_nPriority )
		{
		case THREAD_PRIORITY_MAX:
			nOSPriority = THREAD_PRIORITY_HIGHEST;
			break;
		case THREAD_PRIORITY_HIGH:
			nOSPriority = THREAD_PRIORITY_ABOVE_NORMAL;
			break;
		case THREAD_PRIORITY_NOMINAL:
			nOSPriority = THREAD_PRIORITY_NORMAL;
			break;
		case THREAD_PRIORITY_LOW:
			nOSPriority = THREAD_PRIORITY_BELOW_NORMAL;
			break;
		case THREAD_PRIORITY_MIN:
			nOSPriority = THREAD_PRIORITY_LOWEST;
			break;
		case THREAD_PRIORITY_DEFAULT:
		default:
			nOSPriority = THREAD_PRIORITY_NORMAL;
			break;
		}

		::SetThreadPriority( m_hThread, nOSPriority );

#elif defined(H_OS_LINUX)
#	ifdef H_LINUX_THREAD_PRIORITY
		struct sched_param param;
		switch ( m_nPriority )
		{
		case THREAD_PRIORITY_MAX:
			param.sched_priority = 99;
			break;
		case THREAD_PRIORITY_HIGH:
			param.sched_priority = 80;
			break;
		case THREAD_PRIORITY_NOMINAL:
			param.sched_priority = 70;
			break;
		case THREAD_PRIORITY_LOW:
			param.sched_priority = 60;
			break;
		case THREAD_PRIORITY_MIN:
			param.sched_priority = 50;
			break;
		case THREAD_PRIORITY_DEFAULT:
		default:
			param.sched_priority = 70;
			break;
		}
		pthread_attr_setschedparam( &m_thread_attr, &param );
#	endif //end if H_LINUX_THREAD_PRIORITY
#endif
	}
	//----------------------------------------------
	void Thread::setThreadAffinity( osl::u32 nMask )
	{
		osl::u32 nProcessMask = Process::getProcessAffinity();

		if( ( nMask & nProcessMask ) == 0 )
		{
			nMask = nProcessMask;
		}

#ifdef H_OS_WINDOWS

		::SetThreadAffinityMask( NULL, (DWORD_PTR)&nMask );

#elif defined(H_OS_LINUX)

		Process::setProcessAffinity( nMask );

		// TODO: I cannot make sure whether the way is right. Please correct it if wrong.
// 		cpu_set_t st;
// 		CPU_ZERO( &st );
// 
// 		for( osl::u32 i = 0; i < 32; ++i )
// 		{
// 			if( ( nMask & ( 1 << i ) ) != 0 )
// 			{
// 				CPU_SET( i, &st );
// 			}
// 		}
// 
// 		::sched_setaffinity( m_hThread, sizeof(cpu_set_t), &st );

#endif
	}
	//----------------------------------------------
	bool Thread::start()
	{
		if ( m_nState == S_NULL )
		{
			// sett state.
			m_nState = S_STARTING;

			// assure thread is null.
			m_hThread = 0;

			// create thread and start it.

#ifdef H_OS_WINDOWS
			m_hThread = ( HANDLE )::_beginthreadex( NULL, 0, &Thread::ThreadProc, this, 0, 0 );
            if ( m_hThread )
            {
                setPriority( m_nPriority );
                return true;
            }
#elif defined(H_OS_LINUX)
            setPriority( m_nPriority );
#ifdef H_LINUX_THREAD_PRIORITY
			int ret = pthread_create( &m_hThread, &m_thread_attr, &Thread::ThreadProc, this );
#else
			int ret = pthread_create( &m_hThread, NULL, &Thread::ThreadProc, this );
#endif
            if ( 0 == ret ) // create successfully
            {
                return true;
            }
#endif
			// reset state.
			m_nState = S_NULL;
		}

		return false;
	}
	//----------------------------------------------
	void Thread::stop()
	{
		if ( m_nState != S_NULL )
		{
			m_nState = S_STOPPING;
		}
	}
	//----------------------------------------------
	bool Thread::join( u32 msWait )
	{
		if ( !m_hThread )
		{
			return true;
		}

		// stop first,
		stop();

#ifdef H_OS_WINDOWS

		if ( WAIT_OBJECT_0 == ::WaitForSingleObject( m_hThread, msWait ) )
		{
			m_hThread = 0;
			m_nState = S_NULL;
			return true;
		}

#elif defined(H_OS_LINUX)

		// 		if( m_hThread != 0 )
		// 		{
		// 			pthread_join( m_hThread, 0 );
		// 			return true;
		// 		}
		u32 msSpan = 5;

		while ( m_nState != S_NULL )
		{
			Process::msSleep( msSpan );

			if ( msWait < msSpan )
			{
				break;
			}

			msWait -= msSpan;
		}

		if ( m_nState == S_NULL )
		{
			assert( m_hThread == 0 );
			return true;
		}

#endif

		return true;
	}
	//----------------------------------------------
	void Thread::terminate()
	{
		if ( m_hThread )
		{
#ifdef H_OS_WINDOWS

			//::TerminateThread( m_hThread, 1 );
			m_hThread = NULL;
#elif defined(H_OS_LINUX)
			m_hThread = 0;
			//pthread_kill ( m_hThread, 9 );
#endif

			m_nState = S_NULL;
		}
	}
	//----------------------------------------------
#ifdef H_OS_WINDOWS
#define MS_VC_EXCEPTION 0x406D1388

#pragma pack(push,8)
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; // Must be 0x1000.
		const char * szName; // Pointer to name (in user addr space).
		DWORD dwThreadID; // Thread ID (-1=caller thread).
		DWORD dwFlags; // Reserved for future use, must be zero.
	} THREADNAME_INFO;
#pragma pack(pop)

	void SetThreadName( DWORD dwThreadID,const char* threadName)
	{
		Sleep(10);
		THREADNAME_INFO info;
		info.dwType = 0x1000;
		info.szName = threadName;
		info.dwThreadID = dwThreadID;
		info.dwFlags = 0;

		__try
		{
			RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
		}
	}
	//__declspec(thread) char threadname[256]="unknown";
	unsigned int __stdcall Thread::ThreadProc( void* pvArg )
	{
		// maybe is stopping
		Thread* pThis = ( Thread* )pvArg;
		pThis->ref();

		// set thread local staroge.
		TlsSetValue( s_thread_key , pvArg );


#ifdef H_DEBUG_MODE

		((Thread*)pvArg)->doWork();
#else
		{
			_try
			{
				((Thread*)pvArg)->doWork();
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				assert( false && "Thread crashed, Please check it!!!");
			}
		}
#endif

		// 
		pThis->unref();

		return 0;
	}

	//----------------------------------------------
#elif defined(H_OS_LINUX)
	//__thread char threadname[256]="unknown";
	void* Thread::ThreadProc( void* pvArg )
	{
		// maybe is stopping
		ThreadPtr pThis = ( Thread* )pvArg;

		// set thread local staroge.
		pthread_setspecific( s_thread_key, pvArg );

		pThis->doWork();

		return 0;
	}
#endif


	//----------------------------------------------
	void Thread::doWork()
	{
		//strcpy(threadname,m_strName.c_str());
#ifdef H_OS_WINDOWS
		SetThreadName( (DWORD)-1, m_strName.c_str());
#endif
		
#ifdef H_OS_WINDOWS
        ScopedIntCounterThreadsafe<volatile long> autocount( s_nNumWorkingThread );
#elif defined(H_OS_LINUX)
        ScopedIntCounterThreadsafe<volatile s32> autocount( s_nNumWorkingThread );
#endif

#ifdef H_RECORD_LOG
		{
			OStringStream strTip;
			strTip << "Thread \"" << getName() << "\" Started..." ;
			H_LOG_NAME_DEBUG( "", strTip.str() );
		}
#endif
		


		//if( s_nNumWorkingThreads
		// maybe is stopping
		if ( m_nState != S_STARTING )
		{
			m_nState = S_NULL;

#ifdef H_OS_WINDOWS
			m_hThread = NULL;
#else
			m_hThread = 0;
#endif
			return;
		}


		// set running flag.
		m_nState = S_RUNNING;

		// call run method.
		run();

#ifdef H_RECORD_LOG
		{
			OStringStream strTip;
			strTip << "Thread \"" << getName() << "\" Stopped." ;
			H_LOG_NAME_DEBUG( "", strTip.str() );
		}
#endif

		// set state.
		m_nState = S_NULL;

		// clear thread flag.
		m_hThread = 0;
	}

};//namespace



#endif // #if H_PROVIDE_THREAD_EVENT_LOCK

