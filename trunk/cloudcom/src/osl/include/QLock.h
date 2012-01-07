#ifndef QOSLIB_LOCKER_H__
#define QOSLIB_LOCKER_H__

#if H_PROVIDE_THREAD_EVENT_LOCK

#ifdef H_DEBUG_MODE
//#	define H_STAT_LOCK
#endif

#ifdef H_DEBUG_MODE
//#	define H_STAT_MINI_LOCK
#endif

#ifdef H_DEBUG_MODE
//#	define H_STAT_SPIN_LOCK
#endif

#if ( defined(H_STAT_LOCK) || defined(H_STAT_MINI_LOCK) || defined(H_STAT_SPIN_LOCK) )
//#	include "HLogManager.h"
#endif

namespace osl
{

    static  int  s_nAnyCounter;

    //! The struct simulates a system lock atom.
    //! \remark It can only be used when chance of co-current conflict is very small.
    //! It use
    template<typename Locker>
    struct ScopedLock
    {
        Locker&   m_Lock;

        //! Constructor for the lock.
        //! \remark It will wait until a lock is free.
        //! \param bLock Lock object. It MUST be modified by volatile.
        ScopedLock( Locker& lk ) : m_Lock( lk )
        {
            m_Lock.lock();
        }

        ScopedLock( Locker* plk ) : m_Lock( *plk )
        {
            m_Lock.lock();
        }

        ~ScopedLock()
        {
            m_Lock.unlock();
        }
    private:
        ScopedLock( const ScopedLock& );
        ScopedLock&operator=( const ScopedLock& );
    };

    //! The struct simulates a system lock atom.
    //! \remark It can only be used when chance of co-current conflict is very small.
    //! It use
    template<typename Locker>
    struct ScopedTryLock
    {
        Locker&      m_Lock;
        bool      m_bLocked;
        //! Constructor for the lock.
        //! \remark It will wait until a lock is free.
        //! \param bLock Lock object. It MUST be modified by volatile.
        ScopedTryLock( Locker& lk ) : m_Lock( lk )
        {
            m_bLocked = m_Lock.tryLock();
        }

        ~ScopedTryLock()
        {
            if ( m_bLocked )
            {
                m_Lock.unlock();
            }
        }
    };



    //! A lightweight lock which use user level code.
    //! We use a double lock to alleviate chance of error.
    //! \warning The lock is not quit safe and can ONLY be used
    //! for cases where actually there is a few conflicts may happen.
    struct _EXPORT_OSLIB MiniLock
    {
        typedef ScopedLock<MiniLock>  MyScopedLock;


        MiniLock() : m_nNumEnterThread( 0 ), m_nNumWaitThread( 0 ), m_bLocked(0)
        {
#ifdef H_STAT_MINI_LOCK
            nNumConflicts = 0;
#endif
        };

#ifdef H_STAT_MINI_LOCK
        u32    nNumConflicts;
#endif

        //
        bool needWait()
        {
            return ( m_bLocked != 0 || m_nNumWaitThread != m_nNumEnterThread );
        }

        void lock()
        {
            // if locked, should enter wait mode.
            if ( InterlockedInc32( &m_nNumEnterThread ) > 1 )
            {
                // wait lock for the lock
                for(;;)
                {
                    // add wait count.
                    InterlockedInc32( &m_nNumWaitThread );

                    // get wait lock
                    while ( needWait() )
                    {
#ifdef H_STAT_MINI_LOCK
                        ++nNumConflicts;
                        OStringStreamA strTip;
                        strTip << "MiniLock conflicts:" << nNumConflicts;
                        H_LOG_NAME_WARN( "", strTip.str() );
#endif
                        // spin for a while.
                        int nNumSpin = 2000;
                        int i = 0;

                        while ( i < nNumSpin && needWait() )
                        {
                            ++i;
                            ++s_nAnyCounter;
                        }

                        // if can not wait to enter,just sleep for a while
                        if( i >= nNumSpin )
                        {
                            OS::msSleep( 0 );
                        }
                    }

                    // 维持计数平衡
                    InterlockedDec32( &m_nNumWaitThread );

                    // 先关锁
                    if ( InterlockedInc32( &m_bLocked ) > 1 )
                    {
                        InterlockedDec32( &m_bLocked );
                        continue;
                    }

                    // 有一个人获得了锁，逃离等待，进入。。
                    return;
                }
            }

            // lock it.
            InterlockedInc32( &m_bLocked );
        }

        //! Try lock
        bool tryLock()
        {
			// lock it.
			if( InterlockedInc32( &m_bLocked ) > 1 )
			{
				InterlockedDec32( &m_bLocked );
				return false;
			}

			/// Test lock for m_bLock.
			if ( InterlockedInc32( &m_nNumEnterThread ) > 1 )
			{
				InterlockedDec32( &m_nNumEnterThread );
				InterlockedDec32( &m_bLocked );
				return false;
			}
			return true;
        }

        void unlock()
        {
            assert( m_nNumEnterThread > 0 );
            InterlockedDec32( &m_nNumEnterThread );

            // lock it.
            assert( m_bLocked > 0 );
            InterlockedDec32( &m_bLocked );
        }

    private:
        volatile AtomicInt32            m_nNumEnterThread;   //! Number of thread enter the lock
        volatile AtomicInt32             m_nNumWaitThread;   //! Number of thread wait the lock.
        volatile AtomicInt32                    m_bLocked;   //! whether is locked.

    };




    //! A lightweight lock which use user level code.
    //! \warning The lock is not quit safe and can ONLY be used
    //! for cases where actually there is few conflicts may happen.
    struct _EXPORT_OSLIB SpinLock
    {
        typedef ScopedLock<SpinLock>  MyScopedLock;


        SpinLock() : m_nNumEnterThread( 0 ), m_nNumWaitThread( 0 ), m_bLocked( 0 )
        {
#ifdef H_STAT_SPIN_LOCK
            nNumConflicts = 0;
#endif
        };

#ifdef H_STAT_SPIN_LOCK
        u32    nNumConflicts;
#endif

        //
        bool needWait()
        {
           return ( m_bLocked != 0 || m_nNumWaitThread != m_nNumEnterThread );
        }

        void lock()
        {
            // if locked, should enter wait mode.
            if ( InterlockedInc32( &m_nNumEnterThread ) > 1 )
            {
                // wait lock for the lock
                for(;;)
                {
                    // add wait count.
                    InterlockedInc32( &m_nNumWaitThread );

                    // get wait lock
                    while ( needWait() )
                    {
#ifdef H_STAT_MINI_LOCK
                        ++nNumConflicts;
                        OStringStreamA strTip;
                        strTip << "MiniLock conflicts:" << nNumConflicts;
                        H_LOG_NAME_WARN( "", strTip.str() );
#endif
                        // spin for a while.
                        int nNumSpin = 2000;
                        int i = 0;

                        while ( i < nNumSpin && needWait() )
                        {
                            ++i;
                            ++s_nAnyCounter;
                        }

                        // if can not wait to enter,just sleep for a while
                        if( i >= nNumSpin )
                        {
                            OS::msSleep( 0 );
                        }
                    }

                    // 维持计数平衡
                    InterlockedDec32( &m_nNumWaitThread );

                    // 先关锁
                    if ( InterlockedInc32( &m_bLocked ) > 1 )
                    {
                        InterlockedDec32( &m_bLocked );
                        continue;
                    }
                    
                     // 有一个人获得了锁，逃离等待，进入。。
                    return;
                }
            }

            // lock it.
            InterlockedInc32( &m_bLocked );

        }

        //! Try lock
        bool tryLock()
        {
			// lock it.
			if( InterlockedInc32( &m_bLocked ) > 1 )
			{
				InterlockedDec32( &m_bLocked );
				return false;
			}

			/// Test lock for m_bLock.
			if ( InterlockedInc32( &m_nNumEnterThread ) > 1 )
			{
				InterlockedDec32( &m_nNumEnterThread );
				InterlockedDec32( &m_bLocked );
				return false;
			}
			return true;
        }

        void unlock()
        {
            assert( m_nNumEnterThread > 0 );
            InterlockedDec32( &m_nNumEnterThread );

            // lock it.
            assert( m_bLocked > 0 );
            InterlockedDec32( &m_bLocked );
        }
    private:
        volatile AtomicInt32            m_nNumEnterThread;   //! Number of thread enter the lock
        volatile AtomicInt32             m_nNumWaitThread;   //! Number of thread wait the lock.
        volatile AtomicInt32                    m_bLocked;   //! whether is locked.
    };




    //! Critical section lock.
    struct _EXPORT_OSLIB  Lock
    {
        typedef ScopedLock<Lock>         MyScopedLock;
        typedef ScopedTryLock<Lock>   MyScopedTryLock;

#ifdef H_STAT_LOCK
        u32    nNumConflicts;
#endif


        Lock( u32 nSpinCount = 4000 )
            : m_nLockCount( 0 )
        {
#ifdef H_STAT_LOCK
            nNumConflicts = 0;
#endif

#ifdef H_OS_WINDOWS

            if ( !::InitializeCriticalSectionAndSpinCount( &m_lockMem, nSpinCount ) )
            {
                //H_ASSERT( false && "failed to creaet lock.");
            }

#elif defined(H_OS_LINUX)
            pthread_mutex_init( &m_Mutex, NULL );
#endif

        };
        ~Lock()
        {
#ifdef H_OS_WINDOWS
            ::DeleteCriticalSection( &m_lockMem );
#elif defined(H_OS_LINUX)
            pthread_mutex_destroy( &m_Mutex );
#endif
        };

        void lock()
        {
#ifdef H_STAT_LOCK

            if ( m_nLockCount > 0 )
            {
                ++nNumConflicts;
                OStringStreamA strTip;
                strTip << "Lock conflicts:" << nNumConflicts;
                H_LOG_NAME_WARN( "", strTip.str() );
            }

#endif


#ifdef H_OS_WINDOWS
            EnterCriticalSection( &m_lockMem );
#elif defined(H_OS_LINUX)
            pthread_mutex_lock( &m_Mutex );
#endif
            ++m_nLockCount;
        }

        void unlock()
        {
            --m_nLockCount;

            //
            assert( m_nLockCount >= 0 && "Error use on lock." );

#ifdef H_OS_WINDOWS
            LeaveCriticalSection( &m_lockMem );
#elif defined(H_OS_LINUX)
            pthread_mutex_unlock ( &m_Mutex );
#endif
        }

        //! try lock. It will not block anyway.
        //! \return false if not get the lock.
        bool tryLock()
        {
#ifdef H_OS_WINDOWS

            // Take the lock if we can; regardless don't block.
            // 'result' is FALSE if we took the lock or already held
            //   it amd TRUE if another thread already owns the lock.
            if ( !TryEnterCriticalSection( &m_lockMem ) )
            {
                ++m_nLockCount;
                return true;
            }

#elif defined(H_OS_LINUX)

            if ( 0 == pthread_mutex_trylock( &m_Mutex ) )
            {
                ++m_nLockCount;
                return true;
            }

#endif
            return false;
        }

        bool isLocked()
        {
            bool bLocked = tryLock();

            if ( bLocked )
            {
                unlock();
            }

            return bLocked;
        }

#ifdef H_OS_WINDOWS
        CRITICAL_SECTION       m_lockMem;
#elif defined(H_OS_LINUX)
        pthread_mutex_t          m_Mutex;
#endif
        volatile s32        m_nLockCount;  //! number of blocked on the lock.
    };



    //! a null lock which do no lock at all.
    struct _EXPORT_OSLIB NullLock
    {
        typedef ScopedLock<NullLock>  MyScopedLock;

        NullLock()
        {
        };
        void lock()
        {
        }
        //! Try lock
        bool tryLock()
        {
            return true;
        }

        void unlock()
        {
        }
    };



    //! The macro define a autolock guard.
#define H_MINI_AUTOLOCK( lockParam )     volatile osl::MiniLock::MyScopedLock malk_##lockParam(lockParam);
#define H_MINI_AUTOTRYLOCK( lockParam )  volatile osl::MiniLock::MyScopedTryLock malk_##lockParam(lockParam);

    //! The macro define a autolock guard.
#define H_SPIN_AUTOLOCK( lockParam )     volatile osl::SpinLock::MyScopedLock malk_##lockParam(lockParam);
#define H_SPIN_AUTOTRYLOCK( lockParam )  volatile osl::SpinLock::MyScopedTryLock malk_##lockParam(lockParam);

    //! The macro define a autolock guard.
#define H_AUTOLOCK( lockParam )     volatile osl::Lock::MyScopedLock malk_##lockParam(lockParam);
#define H_AUTOTRYLOCK( lockParam )  volatile osl::Lock::MyScopedTryLock malk_##lockParam(lockParam);
};

#endif // #if H_PROVIDE_THREAD_EVENT_LOCK

#endif // end of file.
