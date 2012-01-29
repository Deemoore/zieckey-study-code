#ifndef __H_OSLIB_THREAD_H__
#define __H_OSLIB_THREAD_H__

#include "osl/include/inner_pre.h"
#include "osl/include/object.h"
#include "osl/include/string_ext.h"

#if H_PROVIDE_THREAD_EVENT_LOCK

#ifdef H_OS_WINDOWS

#elif defined(H_OS_LINUX)

#	include <signal.h>
#endif

namespace osl
{
    class _EXPORT_OSLIB Thread : public Object
    {
        H_ALLOC_OBJECT( Thread )
    public:


    public:

#ifdef H_OS_WINDOWS
        typedef HANDLE           ThreadHandle;
#elif defined(H_OS_LINUX)
        typedef pthread_t        ThreadHandle;	// thread id
#endif

        //! Enumerated Type for thread priority
        enum ThreadPriority
        {

            THREAD_PRIORITY_MAX = 0,  /**< The maximum possible priority  */
            THREAD_PRIORITY_HIGH,     /**< A high (but not max) setting   */
            THREAD_PRIORITY_NOMINAL,  /**< An average priority            */
            THREAD_PRIORITY_LOW,      /**< A low (but not min) setting    */
            THREAD_PRIORITY_MIN,      /**< The minimum possible priority */
            THREAD_PRIORITY_DEFAULT   /**< Priority scheduling default    */

        };

        //! Enumerated Type for thread scheduling policy
        //enum ThreadPolicy {

        //	THREAD_SCHEDULE_FIFO,        /**< First in, First out scheduling         */
        //	THREAD_SCHEDULE_ROUND_ROBIN, /**< Round-robin scheduling (LINUX_DEFAULT) */
        //	THREAD_SCHEDULE_TIME_SHARE,  /**< Time-share scheduling (IRIX DEFAULT)   */
        //	THREAD_SCHEDULE_DEFAULT      /**< Default scheduling                     */
        //};


        //! Thread state.
        enum ThreadState
        {
            S_NULL = 0,  //! Thread is not initialized.
            S_STARTING,  //! Thread is starting, but has enter run(...) method.
            S_RUNNING,   //! Thread is running in run(...) method.
            S_STOPPING,  //! Thread is required stopping.

            S_FORCECHAR = 0xff,
        };

    public:
        //! Constructor.
        Thread();
        //! Deconstructor.
        //! \note When thread object is destoryed, the thread created on it will be terminated forcely.
        ~Thread();


        //! Sets thread running priority.
        //! \remark It can ONLY be called before call start.
        void setPriority( ThreadPriority nPriority );

        //! Gets current thread priority.
        ThreadPriority getPriority()const
        {
            return m_nPriority;
        }

        //! Sets thread processor affinity. e.g. "00001" us first processor.
        void setThreadAffinity( osl::u32 nMask );


        //! Start the thread.
        //! \remark It can ONLY start thread when thread is stopped or never started.
        //!         Also, the method can be overwrote by derived class to ease work on check any extended states.
        //! \return false if can not start. You can only start a thread when state is S_NULL,
        virtual bool start();

        //! Stop the thread.
        //! \remark It only send a exit flag and it is up to derived thread object to response the flag.
        //!         Also, the method can be overwrote by derived class to ease work on check any extended states.
        //! it will not blocked.
        virtual void stop();

        //! Join the work thread. It will wait for exit of the thread.
        //! \param msWait How long to wait before the thread is exited.
        //! \remark It is called by main thread to stop the thread. It will block, so derived class MUST
        //! response S_STOPPING flag.
        //! \return false if can not wait the thread to exit and wait time out.
        virtual bool join( u32 msWait = u32( -1 ) );

        //! Terminate the working thread.
        //! \reamrk Main thread can call the method to force to terminate the thread.
        //! \warning It is quite dangerous!!!
        virtual void terminate();


        //! Query whether the thread is running.
        bool isRunning()const
        {
            return m_nState == S_RUNNING;
        }

        //! Query whether the thread has been stopped.
        bool isStopped()const
        {
            return m_nState == S_NULL;
        }


        //! Sets name for the thread.
        void setName( const String& strName )
        {
            m_strName = strName;
        }

        //! Gets name of the thread.
        const String& getName()const
        {
            return m_strName;
        }

        //! Gets handle.
        ThreadHandle getThreadHandle()const
        {
            return m_hThread;
        }

        //! Gets current thread. Get it from thread local storage.
        static Thread* getCurrentThread();


        //! Gets working thread number
        //! \note Main thread is NOT counted.
        static s32 getNumWorkingThread();

    protected:

        //! Thread function.
        //! \note Derived class should check S_STOPPING flag and to give up thread.
        virtual void run() = 0;


    private:
        friend   class        MainThread;   //! Main thread
        volatile ThreadState    m_nState;   //! object state. It is maintained by thread.
        ThreadPriority       m_nPriority;

        String                 m_strName;   //! Thread Name;

        //ThreadPolicy           m_nPolicy;
        ThreadHandle           m_hThread;

#ifdef H_OS_LINUX
        pthread_attr_t     m_thread_attr;
#endif

    private:

        //! Thread procedure
#ifdef H_OS_WINCE
        static unsigned int WINAPI ThreadProc( void* pvArg );
#elif defined(H_OS_WINDOWS)
        static unsigned int __stdcall ThreadProc( void* pvArg );
#elif defined(H_OS_LINUX)
        static void* ThreadProc( void* pvArg );
#endif

    private:
        //! Hide copy constructor.
        H_DISALLOW_COPY_AND_ASSIGN(Thread);

        // Do the thread work.
        void doWork();
    };

    typedef RefPtr<Thread>  ThreadPtr;

};

#endif // #if H_PROVIDE_THREAD_EVENT_LOCK

#endif  // end of file.




