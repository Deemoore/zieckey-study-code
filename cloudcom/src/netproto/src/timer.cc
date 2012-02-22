#include "osl/include/inner_pre.h"



#if H_PROVIDE_TIMER

#include "osl/include/singleton.h"
#include "osl/include/string_ext.h"
#include "osl/include/timer.h"

#ifdef H_OS_WINDOWS

#elif defined(H_OS_LINUX)
#	include <sys/time.h>
#endif

namespace osl
{
    const u32 FREHUENCY_RESAMPLE_RATE = 200;

#ifdef H_OS_WINDOWS

    class TimerImpl
    {
        H_ALLOCRAW_OPERATORS( TimerImpl )
    public:

        //! Reset the timer.
        void reset( u32 lStartTime )
        {
            // MUST be on the top of the method.!!!
            // from milliseconds to microseconds
            m_nStartTime = lStartTime * 1000;

            QueryPerformanceFrequency( &m_nHiFrequency );
            QueryPerformanceCounter( &m_nStartHiTick );

            m_nStartLowTick  = GetTickCount();
            m_nLastLowTick   = m_nStartLowTick;

            m_nLastTime = 0;

            // Save the current process
            HANDLE mProc = GetCurrentProcess();

            // Get the current Affinity
            GetProcessAffinityMask( mProc, &mProcMask, &mSysMask );

            mThread = GetCurrentThread();
        }

        //! get immediate microscends.
        u64 getImmediateMicroseconds()
        {
            H_MINI_AUTOLOCK( m_lkTimer );

            LARGE_INTEGER nCurHiTick;

            // detect and compensate for performance counter leaps
            // (surprisingly common, see Microsoft KB: H274323)
            u64 nCurLowTick = GetTickCount();
            QueryPerformanceCounter( &nCurHiTick );

            u64 nLowTick = nCurLowTick - m_nStartLowTick;

            u64 nHiTick  = nCurHiTick.QuadPart - m_nStartHiTick.QuadPart;

            double fTmSeconds = ( double )nHiTick / ( double )m_nHiFrequency.QuadPart;

            // get milliseconds to check against GetTickCount
            u64 nHiTickMS = ( u64 ) ( 1000 * fTmSeconds );

            u64 tmCur = u64( 1000000.0 * fTmSeconds ) + m_nStartTime;

            signed long msecOff = ( signed long )( nHiTickMS - nLowTick );

            if ( msecOff < -100 || msecOff > 100 )
            {
                // adjust wrong loop.
                if ( nCurLowTick > m_nStartLowTick )
                {
                    m_nStartTime = m_nStartTime + ( nCurLowTick - m_nStartLowTick ) * 1000;
                }
                else
                {
                    m_nStartTime = m_nStartTime + ( ( m_nLastLowTick - m_nStartLowTick ) + ( nCurLowTick - m_nLastLowTick ) ) * 1000;
                }

                m_nStartLowTick   = nCurLowTick;
                m_nStartHiTick    = nCurHiTick;

                // gets current frequency
                QueryPerformanceFrequency( &m_nHiFrequency );

                // get last time.
                tmCur = m_nStartTime;
            }

            // set last tick.
            m_nLastLowTick = nCurLowTick;

            if ( m_nLastTime > tmCur )
            {
                return m_nLastTime;
            }

            m_nLastTime = tmCur;

            // scale by 1000000 for microseconds
            return m_nLastTime;
        }



    private:

        u64               m_nStartTime;   //! logic timer start time.
        u64                m_nLastTime;

        u64            m_nStartLowTick;
        u64             m_nLastLowTick;   //! last tick.

        LARGE_INTEGER   m_nStartHiTick;   //! machine timer start time.
        LARGE_INTEGER   m_nHiFrequency;


        DWORD           mProcMask;
        DWORD            mSysMask;
        HANDLE            mThread;

        MiniLock         m_lkTimer;
    };

#elif defined (H_OS_LINUX)

    class TimerImpl
    {
        H_ALLOCRAW_OPERATORS( TimerImpl )
    public:

        //! Reset the timer.
        void reset( u32 lStartTime )
        {
            // MUST be on the top of the method.!!!
            // from milliseconds to microseconds
            m_nStartTime = lStartTime * 1000;

            memset( &m_tickStart, 0, sizeof( m_tickStart ) );
            gettimeofday( &m_tickStart, 0 );
        }

        //! get immediate microscends.
        u64 getImmediateMicroseconds()
        {
            struct timeval tmCur;

            if ( gettimeofday( &tmCur, 0 ) != 0 )
            {
                return m_nLastTime;
            };

            m_nLastTime = ( ( tmCur.tv_sec - m_tickStart.tv_sec ) * 1000000 ) + ( tmCur.tv_usec - m_tickStart.tv_usec ) + m_nStartTime;

            return m_nLastTime;
        }



    private:

        struct timeval                 m_tickStart;

        u64                         m_nStartTime;
        u64                          m_nLastTime;

        //Lock                 m_lkTimer;
    };

#endif


    //-------------------------------------------------------
    template<> Timer* Singleton<Timer>::ms_Singleton = NULL;
    Lock Timer::m_lkForInit;

    //-------------------------------------------------------------------------
    Timer::Timer()
    {
        m_lLastMicrosecTime = 0;
        m_lLastMicrosecTime = 0;
        m_tmFrameStart      = 0;
		m_tmLastFrameTime   = 0;
        m_nNumDeletedItems = 0;
		m_tmCPUUsageTime = 0;

        // new a implemention.
        m_pImpl = H_NEW TimerImpl;

        // reset timer.
        reset();
    }

    Timer* Timer::createInstance()
    {
        if ( !ms_Singleton )
        {
            H_AUTOLOCK( m_lkForInit );

            if ( !ms_Singleton )
            {
                ms_Singleton = H_NEW Timer;
            }
        }

        return ms_Singleton;
    }

    void Timer::destroyInstance()
    {
        if ( ms_Singleton )
        {
            H_AUTOLOCK( m_lkForInit );

            if ( ms_Singleton )
            {
                delete ms_Singleton;
                ms_Singleton = NULL;
            }
        }
    }
    //-------------------------------------------------------------------------
    Timer::~Timer()
    {
        delete m_pImpl;
    }
    //-------------------------------------------------------------------------
    void Timer::update()
    {
        // not empty
        {
            TimerRequestList vTimerRequestList;

            {
                H_MINI_AUTOLOCK( m_lkTimerRequestList );
                vTimerRequestList.swap( m_vTimerRequestList );

                // clear the count. it is safe in blocked code.
                m_nNumDeletedItems = 0;
            }

            //!
            if( !vTimerRequestList.empty() )
            {
                m_nNumDeletedItems -= vTimerRequestList.size();

                TimerRequestList::iterator it( vTimerRequestList.begin() ), ite( vTimerRequestList.end() );

                for( ; it != ite; ++it )
                {
                    modifyTimer( it->funcTimer,  it->bDelete, it->msInterval );
                }
            }
        }


        //!
        m_lLastMicrosecTime = getImmediateMicroseconds();
        m_lLastMillisecTime = u32( m_lLastMicrosecTime / 1000 );

        HTime_Sec fLastSecondTime   = m_lLastMicrosecTime / 1000000.0f;

		// update frame time
		m_tmLastFrameTime = float( fLastSecondTime - m_tmFrameStart );
		m_tmFrameStart    = fLastSecondTime;
		m_tmCPUUsageTime += m_tmLastFrameTime;

		if (m_tmCPUUsageTime>1.0f)
		{
#ifdef H_OS_WINDOWS
			Process::updataCpuUsage();
#endif
			m_tmCPUUsageTime = 0;
		}
		

        // onSocketEventT listeners
        TimerList::iterator itrTL = m_listTimer.begin();


        AtomicInt32 nCheckCount = 0;

        while ( itrTL != m_listTimer.end() )
        {
            if ( !itrTL->bDelete )
            {
                u32 msSpan = m_lLastMillisecTime - itrTL->msLastTime;

                if ( msSpan >= itrTL->msInterval )
                {
                    // accumulate time. and MUST consider the round value.
                    itrTL->msLastTime = msSpan + itrTL->msLastTime;

                    // 因为可能发生并发的定时器在由异步线程发起的析构器中删除的问题，所以要确保正确删除。!!这样做也只是让大部分情况可以正常，有临界条件下是不可靠的。
                    if( InterlockedInc32( &m_nNumDeletedItems ) > ++nCheckCount )
                    {
                        H_MINI_AUTOLOCK( m_lkTimerRequestList );

                        if( !m_vTimerRequestList.empty() )
                        {
                            TimerRequestList::iterator it( m_vTimerRequestList.begin() ), ite( m_vTimerRequestList.end() );

                            for( ; it != ite; ++it )
                            {
                                if( it->bDelete && it->funcTimer == itrTL->funcTimer )
                                {
                                    //
                                    InterlockedDec32( &m_nNumDeletedItems );
                                    continue;
                                }
                            }
                        }
                    }

                    // 这里是有并发危险: 当下面的这个方法被调用之前，且在上述检查进行之后，回调函数的主人的生命期可能正好结束。但是概率较低。稍后解决。

                    // if has been removed at other thread, just
                    if( itrTL->funcTimer.getFunctionBase() )
                    {
                        itrTL->funcTimer();
                    }
                }

                ++itrTL;

            }
            else
            {
                // delete the entry.
                TimerList::iterator itrDelete = itrTL++;
                m_listTimer.erase( itrDelete );
            }
        }
    }
    //----------------------------------------------------------
    void Timer::modifyTimer( const TimerFunction& funcTimer, bool bDelete, u32 msInterval )
    {
        TimerList::iterator itrTL, itrTLE;

        itrTL = m_listTimer.begin();
        itrTLE = m_listTimer.end();

        while ( ( itrTL != itrTLE ) && ( itrTL->funcTimer != funcTimer ) )
        {
            itrTL++;
        }

        if ( itrTL == itrTLE )
        {
            if( !bDelete )
            {
                TimerEntry  timerEntry;
                timerEntry.bDelete      = false;
                timerEntry.funcTimer    = funcTimer;
                timerEntry.msInterval    = msInterval;
                //timerEntry.lElapsedTime = 0;
                timerEntry.msLastTime   = m_lLastMillisecTime;

                m_listTimer.push_back( timerEntry );
            }
        }
        else
        {
            if( bDelete )
            {
                m_listTimer.erase( itrTL );
            }
        }

    }
    //----------------------------------------------------------
    void Timer::addTimer( const TimerFunction& funcTimer, u32 msInterval )
    {
        TimerList::iterator itrTL, itrTLE;

        itrTL = m_listTimer.begin();
        itrTLE = m_listTimer.end();

        while ( ( itrTL != itrTLE ) && ( itrTL->funcTimer != funcTimer ) )
        {
            itrTL++;
        }

        if ( itrTL == itrTLE )
        {
            TimerEntry  timerEntry;
            timerEntry.bDelete      = false;
            timerEntry.funcTimer    = funcTimer;
            timerEntry.msInterval    = msInterval;
            //timerEntry.lElapsedTime = 0;
            timerEntry.msLastTime   = m_lLastMillisecTime;

            m_listTimer.push_back( timerEntry );
        }
        else
        {
            itrTL->bDelete = false;
            itrTL->msInterval = msInterval;
        }
    }
    //----------------------------------------------------------
    void Timer::removeTimer( const TimerFunction& funcTimer )
    {
        TimerList::iterator itrTL, itrTLE;

        itrTL = m_listTimer.begin();
        itrTLE = m_listTimer.end();

        while ( ( itrTL != itrTLE ) && ( itrTL->funcTimer != funcTimer ) )
        {
            itrTL++;
        }

        if ( itrTL != itrTLE )
        {
            itrTL->bDelete = true;
        }
    }
    //----------------------------------------------------------
    void Timer::addTimerT( const TimerFunction& funcTimer, u32 msInterval )
    {
        H_MINI_AUTOLOCK( m_lkTimerRequestList );

        m_vTimerRequestList.push_back( TimerRequest() );
        m_vTimerRequestList.back().funcTimer  = funcTimer;
        m_vTimerRequestList.back().msInterval = msInterval;
        m_vTimerRequestList.back().bDelete    = false;
    }
    //----------------------------------------------------------
    void Timer::removeTimerT( const TimerFunction& funcTimer )
    {
        H_MINI_AUTOLOCK( m_lkTimerRequestList );

        m_vTimerRequestList.push_back( TimerRequest() );
        m_vTimerRequestList.back().funcTimer  = funcTimer;
        m_vTimerRequestList.back().msInterval = 0;
        m_vTimerRequestList.back().bDelete    = true;


        InterlockedInc32( &m_nNumDeletedItems );
    }
    //----------------------------------------------------------
    void Timer::removeAllTimers()
    {
        H_MINI_AUTOLOCK( m_lkTimerRequestList );
        m_listTimer.clear();
        m_vTimerRequestList.clear();
    }
    //-------------------------------------------------------------------------
    void Timer::reset( u32 lStartTime )
    {
        // MUST be on the top of the method.!!!
        // from milliseconds to microseconds
        m_lStartTime = lStartTime * 1000;

        m_pImpl->reset( lStartTime );

        m_lLastMicrosecTime = getImmediateMicroseconds();
        m_lLastMillisecTime = u32( m_lLastMicrosecTime / 1000 );
        m_tmFrameStart     = m_lLastMicrosecTime / 1000000.0f;
		m_tmLastFrameTime  = 0;

        TimerList::iterator itrTL = m_listTimer.begin();

        while ( itrTL != m_listTimer.end() )
        {
            itrTL->msLastTime = m_lLastMillisecTime;

            // move to next iterator
            ++itrTL;
        }

    }
    //----------------------------------------------------------
    void Timer::start()
    {

    }
    //----------------------------------------------------------
    void Timer::stop()
    {

    }
    //----------------------------------------------------------
    bool Timer::isStopped()
    {
        return false;
    }
    //-------------------------------------------------------------------------
    u64  Timer::getMicroseconds()
    {
        return m_lLastMicrosecTime;
    }
    //-------------------------------------------------------------------------
    HTime_Sec Timer::getImmediateSeconds()
    {
        return getImmediateMicroseconds() / 1000000.0f;
    }
    //-------------------------------------------------------------------------
    u64 Timer::getImmediateMilliseconds()
    {
        return u32( getImmediateMicroseconds() / 1000 );
    }
    //-------------------------------------------------------------------------
    u64  Timer::getImmediateMicroseconds()
    {
        return m_pImpl->getImmediateMicroseconds();
    }

#ifdef H_OS_WINDOWS
    //----------------------------------------------
    u64 Timer::getDate()
    {
#   ifndef __MINGW32__
        return ( u64 )_time32( NULL );
#	else
        return time( NULL );
#	endif
    };

#elif defined(H_OS_LINUX)
    //----------------------------------------------
    u64 Timer::getDate()
    {
        struct timeval tm;

        if ( gettimeofday( &tm, NULL ) != 0 )
        {
            return 0;
        }

        return tm.tv_sec;//return (u32)_time32( NULL );
    };
#endif

};//namespace
#endif //#if H_PROVIDE_TIMER

