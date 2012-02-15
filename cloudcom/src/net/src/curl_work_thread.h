#ifndef _QNETWORKLIB_CURLWORK_THREAD_H__
#define _QNETWORKLIB_CURLWORK_THREAD_H__




#if H_PROVIDE_CURL

#ifdef H_OS_LINUX
#include <poll.h>
#endif


namespace net
{
    class CURLWork;
    class CURLService;
//enum HttpConnState;


    /*! @class CURLWorkThread
    *  @brief
    *
    */
    class CURLWorkThread : public osl::Thread
    {
    public:
        CURLWorkThread( CURLService* pParent );
        ~CURLWorkThread();

        /**
        * @brief <b>Summary:</b>
        *	Initiate this CURLM session
        * @return	0, if success. <br>
        *			-1, if failed.
        *****************************************************************/
        int	init();

        bool start();

        //! Overridden from osl::Thread to stop the thread.
        void stop();

        //! Add a work to this thread to process.
        //! \return false if failed to add work to the queue.
        bool addWorkT( CURLWork* pWork );

        //! return the string associated with http state
        const char* getHttpStateStr( CURLWork::HttpConnState hs );

        bool isInitialized() const
        {
            return m_bInitialized;
        }

		//! Gets parent.
		CURLService* getParent() const
		{
			return m_pParent;
		}

		//! Gets a new easy handle from the pool, after use it, just return it by call to recycleEasyHandleT.
		void* newEasyHandleT();

		//! Recycle easy handle to the pool.
		void recycleEasyHandleT( void* pHandle );

    protected:
        //! Overridden from osl::Thread. The real thread method.
        void run();

    private:
        /**
        * @brief <b>Summary:</b>
        *		Check for completed transfers, and remove their easy handles
        * @param pNewWork New Work to test in completed message queue.
        * @return true if pNewWork is finished and cleaned.
        * @return void
        **********************************************************************/
        bool scanCompletedEasyHeandles( CURLWork* pNewWork );

        //! called by removeCompletedEasyHeandles
        //! \param res CURLMode
        int removeEasyHandle( void* easy, osl::u32 res );

        /**
        * @brief <b>Summary:</b>
        *		The curl_multi_socket_action functions inform the
        *	application about updates in the socket (file descriptor) status by
        *	doing none, one, or multiple calls to the socket callback function
        *	set with CURLMOPT_SOCKETFUNCTION option to curl_multi_setopt.<br>
        *		We use this method to bound the socket s to a CURLWork.
        * @param[in] e, easy handle
        * @param[in] s, socket (fd)
        * @param[in] action, like CURL_POLL_OUT, CURL_POLL_IN...
        * @param[in] usrptr, the user ptr,
        *		set with CURLMOPT_SOCKETDATA option to curl_multi_setopt.
        * @param[in] sockp, a private pointer
        *	previously set with curl_multi_assign to be this s socket.
        * @return The callback MUST return 0.
        **********************************************************************/
        static int socket_cb( void * e, SOCKET s,
                              int action, void *userp, void *sockp );

        // Max number of poll socket set.
        enum { NUM_MAX_POLL_FDSET = 256, };

    private:
		CURLService*               m_pParent;   //! Parent io service
        osl::Lock		              m_lock;
        osl::Event               m_eventWait;
        void*                       m_pCURLM;   //!CURLM
        osl::u32                  m_nNumEasy;   //! number of easy handle in m_pCURLM
        bool                  m_bInitialized;   //! whether is Initialized
        volatile bool             m_bWorking;   //! Whether is working now.
        int                  m_nStillRunning;   //! number of still running easy
        //! handles within the multi handle
        int                   m_nPrevRunning;  //! number of running handles last time


        H_DEF_LIST( CURLWork*, CURLWorkList );
		H_DEF_VECTOR( CURLWork*, CURLWorkVector );
		H_DEF_VECTOR( CURLWorkPtr, CURLWorkPtrVector );
        H_DEF_SET( void*, EasyHandleSet );

        //key:SOCKET fd, value pCURLWork*
        H_DEF_MAP( SOCKET, CURLWork*, CURLWorkMap );

        CURLWorkVector                                   m_vNewWorks;
        osl::MiniLock                                 m_lkNewWorks;

        CURLWorkList		                           m_NewWorkList; //! which has not been watched
        CURLWorkMap		                              m_DoingWorkMap;//! which has been watched
        CURLWorkPtrVector                      m_vSocketChangedWorks;   //! work list for works that socket just changed.
        int	                                       m_nSelectTimeWait; //! the timeout when do select, miliseconds

        EasyHandleSet                           m_setDeadEasyHandles;


#ifdef H_OS_WINDOWS

        // For temporary usage.
        fd_set                                             m_readset;
        fd_set								     		  m_writeset;
        fd_set									         m_exceptset;
        osl::u32                                            m_nMaxFD;    //! Number of socket in select socket set.

#elif defined(H_OS_LINUX)

        /*struct PollFD
        {
            int                   fd;
            osl::s16        events;
            osl::s16       revents;
        };*/

        struct pollfd                   m_vFDSet[NUM_MAX_POLL_FDSET];
#endif

        osl::u32                                 m_nNumSocketInSet;    //! Number of socket in select socket set.

        // For temporary usage
        CURLWorkPtrVector                     m_vErrorWorks;// only for temporary usage
	
		//! easy handle list.
		H_DEF_LIST(void*, EasyHandleList );
		EasyHandleList                   m_vIdleEasyHandles;
		//osl::MiniLock                 m_lkIdleEasyHandles;

    private:

        friend class CURLWork;

        //! Hide default constructor
        CURLWorkThread( const CURLWorkThread& );


        //! Clean all the works.
        void cleanWorks();

        //! Attach a work to the thread.
        //! \note One work CAN ONLY be attached one thread and one time.
        bool attachWork( CURLWork* pWork );

        //! Detach work from the tread.
        void detachWork( CURLWork* pWork );

        /**
        * @brief <b>Summary:</b>
        *		Scan the new work list : m_NewWorkList.
        *		If the state of any work in m_NewWorkList is change from
        *	HCS_NEW to other state, move this work to m_DoingWorkMap.<br>
        * @details called by run() method
        * @exception {} {}
        * @return { void }
        *****************************************************************/
        void scanNewWorkList();

        //! Check whether has newly added work item.
        //! Swap items in m_vNewWorks to m_NewWorkList
        void checkNewlyAddedWorks();

        /**
        * @brief <b>Summary:</b>
        *		Scan the doing work list : m_DoingWorkMap.
        *		If the state of any work in m_DoingWorkMap is HCS_DONE,
        *	remove this work from the list to m_DoneWorkMap,
        *	and set the doneTime <br>
        *		Else, add the work to the watched fd set.
        * @param[in] readset, the read set fd to be watched
        * @param[in] writeset, the write set fd to be watched
        * @param[in] exceptset, the error fd to be watched
        * @param[in] maxfd, the max SOCKET(fd)
        * @details called by run() method
        * @exception {} {}
        * @return { void }
        *****************************************************************/
        void scanDoingWorkMap();

        //! Poll sockets.
        void pollSockets();

        //! Update works that socket changed. It is called each time when multi_perform_action called.
        void updateSocketChangedWorks();

        void selectErrorLog( int selectret );

        /**
        * @brief <b>Summary:</b>				HTTP_POST = 1000,
        *		Scan the doing work list : m_DoingWorkMap.
        *		If the state of any work in m_DoingWorkMap is HCS_DONE,
        *	remove this work from the list to m_DoneWorkMap,
        *	and set the doneTime <br>
        *		Else, add the work to the watched fd set.
        * @param[in] readset, the read set fd to be watched
        * @param[in] writeset, the write set fd to be watched
        * @param[in] exceptset, the error fd to be watched
        * @param[in] maxfd, the max SOCKET(fd)
        * @param[out] vErrorWorks, holds the exception socket works
        * @details called by run() method
        * @exception {} {}
        * @return { void }
        *****************************************************************/
        void selectAndDoAction();


        //! Process error works. m_vErrorWorks will be processed.
        void processErrorWorks();


    }; // end of class CURLWorkThread



}; // end of namespace net


#endif // end of #if H_PROVIDE_CURL


#endif




