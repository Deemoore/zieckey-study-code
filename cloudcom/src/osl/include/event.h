#ifndef _EVENTWAIT_H
#define _EVENTWAIT_H

#if H_PROVIDE_THREAD_EVENT_LOCK

#ifdef H_OS_WINDOWS
#include <Windows.h>
#endif

namespace osl
{


    //! Event object. Only two thread can share the object.
    //! \note 1. Always reset the event when waited.
    //!       2. Not signaled when created.
    class _EXPORT_OSLIB Event
    {
    public:
        //! Create a new event.
        //! \note 1. Always reset the event when waited.
        //!       2. Not signaled when created.
        Event();
        ~Event();

        //! Wait for a span, until signaled or time out.
        //! \param msWait How long to wait before signaled.
        //! \return true if signaled, otherwise is time out or error.
        bool wait( u32 msWait = u32( -1 ) );

        //! send signal for the event.
        void signal();

    private:

#ifdef H_OS_WINDOWS

        HANDLE            m_hEvent;


#elif defined(H_OS_LINUX )

        pthread_mutex_t   m_hMutex;
        pthread_cond_t     m_hCond;
        bool             signaled_;
#endif

    private:
        //! Hide copy constructor.
        Event( const Event& );

    };


};

#endif // #if H_PROVIDE_THREAD_EVENT_LOCK

#endif	//_EVENTWAIT_H
