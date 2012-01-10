
#ifndef __TIMER_H__
#define __TIMER_H__

#if H_PROVIDE_TIMER

#include "osl/include/object.h"
#include "osl/include/function.h"
#include "osl/include/process_ext.h"
#include "osl/include/QLock.h"

namespace osl
{
    class  TimerImpl;

    // time in seconds
    typedef double HTime_Sec;


    //! The class encapsulates timer service.
    //! \remark The instance is created when the module initialized. you should NEVER
    //! create instance anywhere.
#define s_pTimer ( (osl::Timer*)osl::Timer::getSingletonPtr() )
    class _EXPORT_OSLIB Timer : public Singleton<Timer>
    {
        H_ALLOCRAW_OPERATORS( Timer )
    public:

        typedef Function0   TimerFunction;

    public:
        static Timer* createInstance();

        static void destroyInstance();

        //! Gets raw time in seconds.
        //! \remark Currently just do it like this. It is transient and subject to change.
        HTime_Sec getRawTimeInSeconds()
        {
            return getSeconds();
        }

        /** Add a timer to request queue and take effect in main thread.
         * @remark It is not thread safe and can ONLY be invoked in main thread.
        *  @param funcTimer Function to receive timer notification.
        *  @param msInterval Time interval to receive notification.in milliseconds.
        */
        void addTimer( const TimerFunction& funcTimer, u32 msInterval );

        /** Add a timer to request queue and take effect in main thread.
        *  @param funcTimer Function to receive timer notification.
        *  @param msInterval Time interval to receive notification.in milliseconds.
        */
        void addTimerT( const TimerFunction& funcTimer, u32 msInterval );


        /** Remove the timer */
        void removeTimerT( const TimerFunction& funcTimer );


        /** Remove the timer. It is not thread safe and can ONLY be invoked in main thread. */
        void removeTimer( const TimerFunction& funcTimer );


        //! Remove all the timers.
        //! \note The method CAN ONLY be called when system is going to dead.
        void removeAllTimers();


        /** Resets timer.
        *  @param lStartTime Time base to calculate relative application time in milliseconds.
        */
        void reset( u32 lStartTime = 0 );

        //! resume the timer, if never stopped, will start from 0.
        void start();

        //! stop the current timer.
        void stop();

        //! Query whether the timer is stopped.
        bool isStopped();

        /** Gets second time. */
        HTime_Sec getSeconds() const
        {
            return m_tmFrameStart;
        };

        //! Gets seconds from 1970,1,1
        u64 getDate();

        /** Gets immediate time in seconds. */
        HTime_Sec getImmediateSeconds();

        /** Returns milliseconds since initialization or last reset	*/
        u64 getMilliseconds() const
        {
            return m_lLastMillisecTime;
        };

        /** Returns milliseconds since initialization or last reset, only CPU time measured
        */
        u64 getImmediateMilliseconds();

        /** Returns microseconds since initialization or last reset
        */
        u64 getMicroseconds() ;

        /** Returns microseconds since initialization or last reset, only CPU time measured
        */
        u64 getImmediateMicroseconds();

        /** Update current frame time and dispatch time notification.
        *  @remark  It should be called during main application cycle.
        */
        void update();


		//! Gets last frame time. It is time span from last before update time to last update time.
		HTime_Sec getFrameTime()const
		{
			return m_tmLastFrameTime;
		}

		//! Gets time when the frame start. 
		float getFrameStartTime()const
		{
			return m_tmFrameStart;
		}

    private:

        /** Timer entry */
        struct TimerEntry
        {
            bool			  bDelete;
            TimerFunction   funcTimer;
            u32             msInterval;	// Timer interval by which to receive notification. in ms.
            u32             msLastTime;  // time when last event triggered. in ms
        };

        H_DEF_LIST( TimerEntry, TimerList );   // timer list


        //! Queued timer entry
        struct TimerRequest
        {
            TimerFunction   funcTimer;
            u32             msInterval;	// Timer interval by which to receive notification. in ms.
            bool               bDelete;   //! true delete, false add.
        };

        H_DEF_LIST( TimerRequest, TimerRequestList );


    private:

        MiniLock              m_lkTimerRequestList;   //! Lock for m_vTimerRequestList
        TimerRequestList       m_vTimerRequestList;   //! queued timer.
        AtomicInt32             m_nNumDeletedItems;

        TimerList                      m_listTimer;   //! Timer list

        u64                           m_lStartTime;	  //! Time base to calculate relative application time in microseconds.
        u64                    m_lLastMillisecTime;   //! Last updated time in milliseconds
        //HTime_Sec                m_fLastSecondTime;   //! Last updated time in seconds.
		HTime_Sec                   m_tmFrameStart;   //! time that last invoke update(...)
		float                    m_tmLastFrameTime;   //! last frame time.

        u64                    m_lLastMicrosecTime;   //! Last updated time in microseconds

        float                     m_tmCPUUsageTime;


        TimerImpl*                         m_pImpl;   //! platform Implementation.



    private:

        static Lock    m_lkForInit;//! the lock for create the instance

        //! Constructor can only be called in initializeUtils;
        Timer( void );

        //! Hide copy constructor.
        Timer( const Timer& );

        ~Timer( void );

        /** modify a timer.
        *  @param funcTimer Function to receive timer notification.
        *  @param msInterval Time interval to receive notification.in milliseconds.
        */
        void modifyTimer( const TimerFunction& funcTimer, bool bDelete, u32 msInterval );
    };


};//namespace

#endif //#if H_PROVIDE_TIMER

#endif // __TIMER_H__



