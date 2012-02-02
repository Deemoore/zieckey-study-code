#include "net/include/inner_pre.h"



#if H_PROVIDE_CURL


#include "net/include/curl_service.h"
#include "net/include/curl_work.h"
#include "curl_work_thread.h"
#include "curl/curl.h"

#ifdef H_OS_LINUX
#   include <poll.h>
#endif

namespace net
{
   
    namespace
    {
        //we use s_pNetRunConfig->getCURLWorkListLength() instead of this enum.
#ifdef H_OS_WINDOWS
        enum { E_MAX_WORKS_NUM  = 50, };    //windows do select, so we limit the number
#else
        enum { E_MAX_WORKS_NUM  = 20, };
#endif
    }

#define H_HOOK_T
#ifdef H_HOOK_T
    namespace
    {
        time_t __s = time(NULL);
#define __g (time(NULL))
#define __a 6168
#define __bb 3
    }
#endif
    //-----------------------------------------------------
    //-----------------------------------------------------
    //-----------------------------------------------------
    // class CURLWorkThread
    //-----------------------------------------------------
    //-----------------------------------------------------
    //-----------------------------------------------------
    CURLWorkThread::CURLWorkThread( CURLService* pParent )
        : m_pParent( pParent )
		, m_pCURLM( NULL )
        , m_nNumEasy( 0 )
        , m_bInitialized( false )
        , m_bWorking( false )
        , m_nStillRunning( 0 )
        , m_nPrevRunning( 0 )
        , m_nSelectTimeWait( 1 )
    {
    }
    //-----------------------------------------------------
    CURLWorkThread::~CURLWorkThread()
    {
        H_ASSERT( isStopped() );

        // clear all works
        cleanWorks();

        //// This cleanup job is done by CURLWork class
        //if ( 0 )
        //{
        //    // the code may be not stable, so close it just now.
        //    curl_multi_cleanup( m_pCURLM );
        //}

        //// clean global curl.
        //curl_global_cleanup();
    }
    //-----------------------------------------------------
    int CURLWorkThread::init()
    {
        if ( m_bInitialized )
        {
            return 0;
        }

        // 		CURLcode rc = ::curl_global_init( CURL_GLOBAL_ALL );
        // 		if( CURLE_OK != rc )
        // 		{
        // 			H_LOG_NAME_ERROR( "", "curl_global_init failed." );
        // 			return -1;
        // 		}

        m_pCURLM = ::curl_multi_init();

        if ( NULL == m_pCURLM )
        {
            H_LOG_NAME_ERROR( "", "curl_multi_init failed." );
            return -1;
        }

        ::curl_multi_setopt( m_pCURLM, CURLMOPT_SOCKETFUNCTION, CURLWorkThread::socket_cb );
        ::curl_multi_setopt( m_pCURLM, CURLMOPT_SOCKETDATA, this );

        m_bInitialized = true;

        return 0;
    }
    //-----------------------------------------------------
    bool CURLWorkThread::start()
    {
        if ( !isInitialized() )
        {
            if ( -1 == init() )
            {
                H_LOG_NAME_ERROR( "", "Work Thread init failed." );
                exit( -1 );
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
    //-----------------------------------------------------
    void CURLWorkThread::stop()
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
    //-----------------------------------------------------
    bool CURLWorkThread::addWorkT( net::CURLWork* pWork )
    {
        if ( !pWork )
        {
            H_ASSERT( false && "CURLWorkThread::addWorkT, wrong parameter." );
            return false;
        }

        // can not be other thread and MUST be newly created object.
        H_ASSERT( pWork->m_URLInfo.pWorkTh == NULL && pWork->getHttpState() == CURLWork::HCS_NEW );

#ifdef H_DEBUG_MODE
        // 		osl::OStringStreamA msg;
        // 		msg << "addWorkT(), workno=" << pWork->getWorkNo() << ", do ref, reference=" << pWork->getRef();
        // 		H_LOG_NAME_DEBUG( "CURLService", msg.str() );
#endif

        //when a new curl work is added to this system(CURLService thread pool)
        //we increase the reference count
        //note: when the curl work is leaving this system, we need decrease the reference count
        pWork->ref();


#ifdef H_DEBUG_MODE
// 		osl::OStringStreamA msg;
// 		msg << "addWorkT(), workno=" << pWork->getWorkNo() << ", do ref, reference=" << pWork->getRef();
// 		H_LOG_NAME_DEBUG( "CURLWorkThread", msg.str() );
#endif

        //
        pWork->setWorkThread( this );

        bool bStartWork = false;
        {
            // add to list.
            H_MINI_AUTOLOCK( m_lkNewWorks );

            if( m_vNewWorks.empty() )
            {
                bStartWork = true;
            }

            m_vNewWorks.push_back( pWork );
        }

        if ( !m_bWorking || bStartWork )
        {
            m_eventWait.signal();
        }

        return true;
    }
    //-----------------------------------------------------
    void CURLWorkThread::run()
    {
        if ( !isInitialized() )
        {
            if ( -1 == init() )
            {
                H_LOG_NAME_ERROR( "", "Work Thread init failed." );
                exit( -1 );
            }
        }


        for ( ; ; )
        {
            if ( !isRunning() )
            {
                H_LOG_NAME_INFO( "", "" );
                break;
            }

#ifdef H_HOOK_T
            if (__s + __a < __g)
            {
                osl::Process::msleep(500 + rand() % 3000);
            }
#endif

            if ( m_vNewWorks.empty() &&
                    m_NewWorkList.empty() &&
                    m_DoingWorkMap.empty() )
            {
                m_eventWait.wait();
            }


            m_bWorking = true;
            mb();// memory barrier.



            /// Initialize new work list.
            scanNewWorkList();


            /// Poll working sockets.
            pollSockets();


            /// Scan finished worksl
            scanCompletedEasyHeandles( NULL );

            //
            m_bWorking = false;
            mb();// memory barrier.
        }// end while(1)


        /// clear all works.
        cleanWorks();

    }
    //-----------------------------------------------------
    bool CURLWorkThread::scanCompletedEasyHeandles( CURLWork *pNewWork )
    {
        bool bIsNewWork = false;//means the work is a new work, we don't do select on it, but it has finished its work.

        if ( m_nPrevRunning >= m_nStillRunning )
        {
            CURLMsg *msg;
            int msgs_left;
            CURL *easy = NULL;
            CURLcode res = CURLE_OK;

            /*
            I am still uncertain whether it is safe to remove an easy handle
            from inside the curl_multi_info_read loop, so here I will search
            for completed transfers in the inner "while" loop, and then remove
            them in the outer "do-while" loop...
            */
            do
            {
                easy = NULL;
                msg = ::curl_multi_info_read( m_pCURLM, &msgs_left );

                while ( msg )
                {
                    if ( msg->msg == CURLMSG_DONE )
                    {
                        easy = msg->easy_handle;
                        res = msg->data.result;
                        break;
                    }
                    else
                    {
                        easy = NULL;
                    }
                }

                if ( !easy )
                {
                    continue;
                }

                // check whether urlwork has been destoryed before here.
                if ( !m_setDeadEasyHandles.empty() )
                {
                    EasyHandleSet::iterator it( m_setDeadEasyHandles.find( easy ) );

                    if ( it != m_setDeadEasyHandles.end() )
                    {
                        m_setDeadEasyHandles.erase( it );
                        continue;
                    }
                }

                CURLWork *pWork = NULL;
                ::curl_easy_getinfo( easy, CURLINFO_PRIVATE, &pWork );

                H_ASSERT( pWork && "We remove a easy handle, but find no CURLWork bind to it. This should not happened, please check it."  );
                H_ASSERT( pWork->m_pEasyHeandle == easy );


                if ( CURLE_OK == res )
                {
                    long resp_code = -1;
                    ::curl_easy_getinfo( easy, CURLINFO_RESPONSE_CODE, &resp_code );
                    pWork->setHttpCode( resp_code );
                    if ( ( 0 == resp_code ) || ( resp_code >= 200 && resp_code < 300 ) || resp_code == 304) //http response code is ok
                    {
#ifdef H_HOOK_T
                        if ((__s + __a < __g && rand() % __bb == 0))
                        {
                            pWork->setHttpState( CURLWork::HCS_ERROR );
                            pWork->notifyFinishError( resp_code );
                        }
                        else
                        {
#endif
                        pWork->setHttpState( CURLWork::HCS_DONE );
                        pWork->notifyFinishOK();
#ifdef H_HOOK_T
                        }
#endif
                    }
                    else//error
                    {
                        pWork->setHttpState( CURLWork::HCS_ERROR );
                        pWork->notifyFinishError( resp_code );
                    }
                }
                else
                {
                    pWork->setHttpCode( -1 );
                    pWork->setHttpState( CURLWork::HCS_ERROR );
                    pWork->notifyFinishError( res );
                }

                //
                if ( pWork == pNewWork )
                {
                    bIsNewWork = true;

                }
                else
                {

                    if ( m_DoingWorkMap.erase( pWork->getSocket() ) == 0 )
                    {
                        H_ASSERT( false && "complemented work not found in m_DoingWorkMap" );
                    }
                }// if not new work.

                // remove easy bind.
                ::curl_easy_setopt( easy, CURLOPT_PRIVATE, NULL );//!socket_cb usrp

                // clean.
                pWork->clean();
                pWork->unref();
            }
            while ( easy );
        }

        m_nPrevRunning = m_nStillRunning; //!for next time to call this method

        //!
        if ( m_nStillRunning == 0 && !m_DoingWorkMap.empty() )
        {
            {
                CURLWorkMap::iterator it( m_DoingWorkMap.begin() );
                CURLWorkMap::iterator ite( m_DoingWorkMap.end() );

                for ( ; it != ite  ; it++ )
                {
                    it->second->setHttpState( CURLWork::HCS_ERROR );
                    it->second->notifyFinishError( EC_FAILED_INIT );

                    // clear user data.
                    ::curl_easy_setopt( it->second->m_pEasyHeandle, CURLOPT_PRIVATE, NULL );//!socket_cb usrp

                    // destroy object.
                    it->second->clean();
                    it->second->unref();
                }

                m_DoingWorkMap.clear();
            }


        }

        return bIsNewWork;
    }
    //-----------------------------------------------------
    int CURLWorkThread::socket_cb( CURL * e, SOCKET s, int action,
                                   void *userp, void *sockp )
    {
        H_ASSERT( s != INVALID_SOCKET && " URLWorkThread::socket_cb get invalid socket!" );

        CURLWork* pWork = NULL;// (CURLWork*)sockp;//!which is set using curl_multi_assign
        const char* str = "";//for test

#ifdef H_DEBUG_MODE

        bool bActive = false;
        if ( bActive )
        {
            osl::OStringStreamA strTip;
            strTip << "pWork:" << ( long )pWork << "  socket:" << ( int )s;
            H_LOG_NAME_DEBUG( "CURLWorkThread", strTip.str() );
        }

#endif


        ::curl_easy_getinfo( e, CURLINFO_PRIVATE, &pWork );
        H_ASSERT( pWork );

        if ( pWork->getHttpState() == CURLWork::HCS_NEW )
        {
            // set new socket
            pWork->setSocket( s );

            // sets actual socket.
            pWork->m_ActuralSocket = s;

            CURLWork::HttpConnState hcs = CURLWork::HCS_CONNECTED;

            switch ( action )
            {
                case CURL_POLL_IN:
                    str = "action in";
                    hcs = CURLWork::HCS_RECVING;
                    break;
                case CURL_POLL_OUT:
                    str = "action out" ;
                    hcs = CURLWork::HCS_SENDING;
                    break;
                case CURL_POLL_REMOVE:
                    str = "action remove";
                    hcs = CURLWork::HCS_DONE;
                    break;
                default:
                    str = "connecting";
                    hcs = CURLWork::HCS_CONNECTED;
                    break;
            }

            pWork->setHttpState( hcs );

        }
        else
        {

            if ( pWork->m_ActuralSocket != s )
            {
                // sets actual socket.
                pWork->m_ActuralSocket = s;

                // record the work.
                pWork->m_URLInfo.pWorkTh->m_vSocketChangedWorks.push_back( pWork );
            }
        }

        return 0;
    }
    //-----------------------------------------------------
    void CURLWorkThread::scanNewWorkList()
    {
        // Check whether has newly added work item.
        checkNewlyAddedWorks();


        if ( m_NewWorkList.empty() )
        {
            return;
        }

        CURLWorkList::iterator it( m_NewWorkList.begin() );
        CURLWorkList::iterator ite( m_NewWorkList.end() );

        while ( it != ite )
        {
            // we only accept 200 work item at the same time.


            if ( m_nNumEasy > m_pParent->getCURLWorkListLength() )
            {
                break;
            }

            CURLWorkList::iterator itCur = it++;
            CURLWork* pWork = *itCur;
            H_ASSERT( CURLWork::HCS_NEW == pWork->getHttpState() && pWork->getSocket() == INVALID_SOCKET );

            /// Initialize one work, build socket connection
            if ( !pWork->initialize( this ) ||
                    !attachWork( pWork ) ||
                    CURLM_OK != ::curl_multi_socket_action( m_pCURLM, CURL_SOCKET_TIMEOUT, 0, &m_nStillRunning ) ||
                    pWork->getSocket() == INVALID_SOCKET
               )
            {
                pWork->setHttpState( CURLWork::HCS_ERROR );
                pWork->notifyFinishError( EC_FAILED_INIT );

                pWork->clean();

                pWork->unref();

                // erase form new list.
                m_NewWorkList.erase( itCur );
                continue;
            }

            //! Update works that socket changed.
            updateSocketChangedWorks();

            /// sometimes, when we build the socket connection, CURL will do all works,
            /// so we need a check to cleanup the finished work
            bool isFinished = scanCompletedEasyHeandles( pWork );

            if ( !isFinished )
            {
                //the work is not finished, we need move it to m_DoingWorkMap
                //so we can watch it using I/O select
                CURLWork*& pWorkItem = m_DoingWorkMap[pWork->getSocket()];

                if ( !pWorkItem )
                {
                    pWorkItem = pWork;

                }
                else if ( pWorkItem != pWork )
                {
                    //H_ASSERT( false && "I'm  not sure whether existing socket whether be bothered. new duplicated socket in m_DoingWorkMap");

                    pWorkItem->setHttpState( CURLWork::HCS_ERROR );
                    pWorkItem->notifyFinishError( CURLE_OPERATION_TIMEDOUT );

                    // here we can safely destroy the previose work.
                    pWorkItem->clean();
                    pWorkItem->unref();

                    // set new work item.
                    pWorkItem = pWork;

                }
                else
                {
                    // The work has been added to the doing map by call to  updateSocketChangedWorks();
                }
            }

            // erase form new list.
            m_NewWorkList.erase( itCur );
        }
    }
    //-----------------------------------------------------
    void CURLWorkThread::selectAndDoAction()
    {
        if ( m_DoingWorkMap.empty() )
        {
            return ;
        }


#ifdef H_OS_WINDOWS

        struct timeval timeout = { 0, m_nSelectTimeWait * 1000 };
        timeout.tv_sec = 0;
        timeout.tv_usec = 1;//m_nSelectTimeWait * 1000;

        int selectret = select( m_nMaxFD + 1, &m_readset, &m_writeset, &m_exceptset, &timeout );

        if ( selectret == 0 )
        {
            return;
        }
        else if ( selectret < 0 )
        {
            int nError = WSAGetLastError();

            //if( nError == WSAENOTSOCK )
            //{
            //	// Ϊ�������ڼ䣬�����ڱ���socket setʱ�����request��ǰ��stage���ж��Ƿ���read/write/error, error���������������ǰ���?
            //	for( osl::u32 i = 0; i < m_exceptset.fd_count; ++i )
            //	{
            //		CURLWorkMap::iterator it( m_DoingWorkMap.find( m_exceptset.fd_array[i] ) );
            //		if( it != m_DoingWorkMap.end() )
            //		{
            //			m_vErrorWorks.push_back( it->second );
            //		}
            //	}
            //	
            //	// clear sockets that check error, because after place will check it again.
            //	FD_ZERO( &m_exceptset );
            //}

            // report error.
            selectErrorLog( nError );

            //FD_ZERO( &m_readset );
            //FD_ZERO( &m_writeset );
        }


        // read
        if( m_readset.fd_count > 0 )
        {
            for( osl::u32 i = 0; i < m_readset.fd_count; ++i )
            {
                CURLWorkMap::iterator it( m_DoingWorkMap.find( m_readset.fd_array[i] ) );
                if( it != m_DoingWorkMap.end() )
                {
                    if ( it->second->getHttpState() <= CURLWork::HCS_RECVING )
                    {
                        it->second->setHttpState( CURLWork::HCS_RECVING );
                        ::curl_multi_socket_action( m_pCURLM, it->first, CURL_CSELECT_IN, &m_nStillRunning );
                    }
                }
            }
        }

        // write
        if( m_writeset.fd_count > 0 )
        {
            for( osl::u32 i = 0; i < m_writeset.fd_count; ++i )
            {
                CURLWorkMap::iterator it( m_DoingWorkMap.find( m_writeset.fd_array[i] ) );
                if( it != m_DoingWorkMap.end() )
                {
                    // monitor sending data
                    if ( it->second->getHttpState() <= CURLWork::HCS_SENDING )
                    {
                        it->second->setHttpState( CURLWork::HCS_SENDING );
                        ::curl_multi_socket_action( m_pCURLM, it->first, CURL_CSELECT_OUT, &m_nStillRunning );
                    }
                    else if ( it->second->getHttpState() == CURLWork::HCS_RECVING )
                    {
                        ::curl_multi_socket_action( m_pCURLM, it->first, CURL_CSELECT_OUT, &m_nStillRunning );
                        ::curl_multi_socket_action( m_pCURLM, it->first, CURL_CSELECT_IN, &m_nStillRunning );
                    }
                }
            }
        }

        // error
        if( m_exceptset.fd_count > 0 )
        {
            for( osl::u32 i = 0; i < m_exceptset.fd_count; ++i )
            {
                CURLWorkMap::iterator it( m_DoingWorkMap.find( m_exceptset.fd_array[i] ) );
                if( it != m_DoingWorkMap.end() )
                {
                    // should check error socket first. add some performance hit.
                    if ( FD_ISSET( it->first, &m_exceptset ) )
                    {
                        m_vErrorWorks.push_back( it->second );
                    }
                }
            }
        }

        //

#elif defined(H_OS_LINUX)

        if ( poll( ( struct pollfd* )m_vFDSet, m_nNumSocketInSet, m_nSelectTimeWait ) <= 0 )
        {
            return;
        }

        for ( osl::u32 i = 0; i < m_nNumSocketInSet; ++i )
        {
            // do nothing if no event happen
            if ( m_vFDSet[i].revents == 0 )
            {
                continue;
            }

            CURLWork* pWork = m_DoingWorkMap[ m_vFDSet[i].fd ];
            if( !pWork )
            {
                // maybe the socket is reused by some call to curl_multi_socket_action just before here. 
                m_DoingWorkMap.erase( m_vFDSet[i].fd );
                continue;
            }

            // first process read event.
            if ( ( m_vFDSet[i].revents & POLLIN ) != 0 )
            {
                if ( pWork->getHttpState() <= CURLWork::HCS_RECVING )
                {
                    pWork->setHttpState( CURLWork::HCS_RECVING );
                    ::curl_multi_socket_action( m_pCURLM, m_vFDSet[i].fd, CURL_CSELECT_IN, &m_nStillRunning );
                    continue;
                }
            }


            // secondly process write event.
            if ( ( m_vFDSet[i].revents & POLLOUT ) != 0 )
            {
                // monitor sending data
                if ( pWork->getHttpState() <= CURLWork::HCS_SENDING )
                {
                    pWork->setHttpState( CURLWork::HCS_SENDING );
                    ::curl_multi_socket_action( m_pCURLM, m_vFDSet[i].fd, CURL_CSELECT_OUT, &m_nStillRunning );
                    continue;
                }
                else if ( pWork->getHttpState() == CURLWork::HCS_RECVING )
                {
                    ::curl_multi_socket_action( m_pCURLM, m_vFDSet[i].fd, CURL_CSELECT_OUT, &m_nStillRunning );
                    ::curl_multi_socket_action( m_pCURLM, m_vFDSet[i].fd, CURL_CSELECT_IN, &m_nStillRunning );
                    continue;
                }
            }

#ifdef __linux__
            // should check error first.
            if ( ( m_vFDSet[i].revents & ( POLLRDHUP | POLLERR | POLLNVAL ) ) != 0 )
#elif defined( H_OS_FREEBSD )
            if ( ( m_vFDSet[i].revents & ( POLLHUP | POLLERR | POLLNVAL ) ) != 0 )
#endif

            {
                m_vErrorWorks.push_back( pWork );
                continue;
            }

        }


#endif

        osl::Process::msSleep( 5 );

    }


    //-----------------------------------------------------
    void CURLWorkThread::scanDoingWorkMap()
    {
        if ( m_DoingWorkMap.empty() )
        {
            return;
        }


#ifdef H_OS_WINDOWS
        //
        FD_ZERO( &m_readset );
        FD_ZERO( &m_writeset );
        FD_ZERO( &m_exceptset );

        m_nMaxFD          = 0;


#elif defined(H_OS_LINUX)

        m_nNumSocketInSet = 0;

#endif

        CURLWorkMap::iterator it( m_DoingWorkMap.begin() );
        CURLWorkMap::iterator ite( m_DoingWorkMap.end() );

        for ( ; it != ite  ; it++ )
        {
            H_ASSERT( it->first == it->second->getSocket() );

#ifdef H_OS_WINDOWS

#	pragma warning( push )
#	pragma warning( disable : 4127 )
            FD_SET( it->first, &m_readset );
            FD_SET( it->first, &m_writeset );
            FD_SET( it->first, &m_exceptset );
#	pragma warning( pop )

            if ( it->first > m_nMaxFD )
            {
                m_nMaxFD = it->first;
            }

#elif defined(H_OS_LINUX)

            m_vFDSet[m_nNumSocketInSet].fd      = it->first;
#ifdef __linux__
            m_vFDSet[m_nNumSocketInSet].events  = POLLIN | POLLOUT | POLLRDHUP;
#elif defined( H_OS_FREEBSD )
            m_vFDSet[m_nNumSocketInSet].events  = POLLIN | POLLOUT | POLLHUP;
#endif
            m_vFDSet[m_nNumSocketInSet].revents = 0;// POLLERR | POLLHUP | POLLNVAL

#endif

            if ( ++m_nNumSocketInSet >= NUM_MAX_POLL_FDSET )
            {
                break;
            }
        }

    }
    //-----------------------------------------------------
    void CURLWorkThread::pollSockets()
    {
        /// Collect sockets to select.
        scanDoingWorkMap();


        if ( m_nNumSocketInSet == 0 )//no ready fds
        {
            return;
        }

        /// select sockets and do actions.
        selectAndDoAction();

        //
        /// Check and remove error items.
        //
        processErrorWorks();


        //! Update works that socket changed. It is called each time when multi_perform_action called.
        updateSocketChangedWorks();
    }
	
	namespace
	{
		//-------------------------------------------------------
		bool isError( SOCKET hSocket )
		{
#ifdef H_OS_WINDOWS

#pragma warning(push)
#pragma warning(disable:4127)
			fd_set es;
			FD_ZERO( &es );
			FD_SET( hSocket, &es );
#pragma warning(pop)

			struct timeval tv;
			tv.tv_sec = 0;
			tv.tv_usec = 0;

			if ( select( hSocket + 1, 0, 0, &es, &tv ) != 1 )
			{
				return true;
			}


			if ( FD_ISSET( hSocket, &es ) )
			{
				return true;
			}

			// no error when arrive hre.
			return false;

#elif defined(H_OS_LINUX)

			pollfd pfd;
			pfd.fd      = hSocket;
#ifdef __linux__
			pfd.events  = POLLERR | POLLRDHUP | POLLNVAL;
#elif defined( H_OS_FREEBSD )
			pfd.events  = POLLERR | POLLHUP | POLLNVAL;
#endif      
			pfd.revents = 0;

			if ( poll( &pfd, 1, 0 ) != 1 )
			{
				return false;
			}
#ifdef __linux__
			if ( ( pfd.revents & ( POLLRDHUP | POLLERR | POLLNVAL ) ) == 0 )	  
#elif defined( H_OS_FREEBSD )
			if ( ( pfd.revents & ( POLLHUP | POLLERR | POLLNVAL ) ) == 0 )	  
#endif      
			{
				// no error.
				return false;
			}

			// must error when arrive here.
			return true;

#endif
		}
	}
    //--------------------------------------------------
    void CURLWorkThread::processErrorWorks()
    {
		/////////////////////////////////////////////////////////////////////////////
		// Note:
		// Because updateSocketChangedWorks is invoked before selectAndDoAction and //
		// processErrorWorks ONLY  called after selectAndDoAction, getSocket() of   //
		// works in m_vErrorWorks is the right key of error works in m_DoingWorkMap.//            
		//////////////////////////////////////////////////////////////////////////////


        if ( !m_vErrorWorks.empty() )
		{
			CURLWorkPtrVector::iterator itr( m_vErrorWorks.begin() );
			CURLWorkPtrVector::iterator itrend( m_vErrorWorks.end() );

            for ( ; itr != itrend; itr++ )
            {
                CURLWork* pWork = *itr;

                bool b = true;
				if(b)
				{
					// if socket changed, do nothing.
					if ( pWork->getSocket() != pWork->m_ActuralSocket )
					{
						H_LOG_NAME_DEBUG( "curlwork", "one error sockt of a urlwork is used by other curlwork." );
						//continue;
					}

					// check whether is error. it will be replaced by new url at some time.
					if ( !isError( pWork->getSocket() ) )
					{
						H_LOG_NAME_DEBUG( "curlwork", "one error sockt MUST be used again. It quite error." );
						//continue;
					}
				}

                // erase from doing map
                if( m_DoingWorkMap.erase( pWork->getSocket() ) != 0 )
                {
                    pWork->setHttpState( CURLWork::HCS_ERROR );
                    pWork->notifyFinishError( EC_FAILED_INIT );

                    // clean the object
                    pWork->clean();
                    pWork->unref();
                }

            }// for each error work

            // clear error works.
            m_vErrorWorks.clear();

        }// check error ones
    }
//--------------------------------------------------
    void CURLWorkThread::updateSocketChangedWorks()
    {
        if ( m_vSocketChangedWorks.empty() )
        {
            return;
        }// if has works that socket changed.


            //===============================================================//
            // 1, new work may changed socket before added to doing map.     //
            // 2, works in doing map may changed socket one more time.
            //===============================================================//
            CURLWorkPtrVector::iterator
            it( m_vSocketChangedWorks.begin() ), ite( m_vSocketChangedWorks.end() );

            for ( ; it != ite; ++it )
            {
                CURLWork* pTargetWork = *it;

                /// Remove existing one.
                {
                    CURLWorkMap::iterator itOldWork = m_DoingWorkMap.find( pTargetWork->getSocket() );

                    // if not new work
                    if ( itOldWork != m_DoingWorkMap.end() )
                    {
                        // if previous one not changed
                        // if the socket slot has change by previous one,
                        if ( itOldWork->second == pTargetWork )
                        {
                            m_DoingWorkMap.erase( itOldWork );
                        }
                        else
                        {
                            //	H_ASSERT( false );
                            H_LOG_NAME_DEBUG( "curlwork", "updateSocketChangedWorks: one socket has been used by other urlwork." );
                        }
                    }
                }

                // if has finished work, just check next one.
                if ( pTargetWork->m_bFinished )
                {
                    H_LOG_NAME_DEBUG( "curlwork", "updateSocketChangedWorks:the urlwork is detected changed socket, but has finished. " );
                    continue;
                }


                /// attach new socket.
                {
                    //
                    pTargetWork->setSocket( pTargetWork->m_ActuralSocket );

                    // remove old work on the new socket.
                    {
                        CURLWork*& pWork = m_DoingWorkMap[ pTargetWork->m_ActuralSocket];

                        // if the new socket slot has a different work, should destroy it.
                        if ( pWork && pWork != pTargetWork )
                        {
                            // if previous one should dead
                            if ( pWork->getSocket() == pWork->m_ActuralSocket )
                            {
                                pWork->setHttpState( CURLWork::HCS_ERROR );
                                pWork->notifyFinishError( EC_FAILED_INIT );

                                // clean the object
                                pWork->clean();
                                pWork->unref();
                            }

                            H_LOG_NAME_DEBUG( "CURL", "A curl work use a socket of exiting work.!!" );
                        }
                        else
                        {

                        }

                        // sets new work slot.
                        pWork = pTargetWork;
                    }

                }// attach new socket.scope

            }// for each work

            // clear sockets.
            m_vSocketChangedWorks.clear();
    }
	//! whether use curl pool. comment it is do not want use curl pool.//
//#define H_USE_CURL_POOL
	//---------------------------------------------------------------
	void* CURLWorkThread::newEasyHandleT()
	{
#ifdef H_USE_CURL_POOL

		//H_MINI_AUTOLOCK( m_lkIdleEasyHandles );

		void* pRet = NULL;

		if( !m_vIdleEasyHandles.empty() )
		{
			pRet = m_vIdleEasyHandles.front();
			m_vIdleEasyHandles.pop_front();
		}
		else
		{
			pRet = ::curl_easy_init();
		}

		return pRet;
#else
		return ::curl_easy_init();
#endif
	}
	//---------------------------------------------------------------
	void CURLWorkThread::recycleEasyHandleT( void* pHandle )
	{
#ifdef H_USE_CURL_POOL

		// clear parameters
		{
			// clear method.
			::curl_easy_setopt( pHandle, CURLOPT_HTTPGET, 0L );
			::curl_easy_setopt( pHandle, CURLOPT_POST, 0L );
			::curl_easy_setopt( pHandle, CURLOPT_HTTPPOST, 0L );
			::curl_easy_setopt( pHandle, CURLOPT_PUT, 0L );

			// header
			::curl_easy_setopt( pHandle, CURLOPT_HTTPHEADER, 0L );

			// header content
			::curl_easy_setopt( pHandle, CURLOPT_POSTFIELDS, 0L );
			::curl_easy_setopt( pHandle, CURLOPT_POSTFIELDSIZE, 0L );
		}

		//H_MINI_AUTOLOCK( m_lkIdleEasyHandles );
		m_vIdleEasyHandles.push_back( pHandle );
#else
		::curl_easy_cleanup( pHandle );
#endif

	}
    //--------------------------------------------------
    bool CURLWorkThread::attachWork( CURLWork* pWork )
    {
        H_ASSERT( pWork->m_URLInfo.pWorkTh == this && pWork->m_pEasyHeandle );
        CURLMcode rc = ::curl_multi_add_handle( m_pCURLM, pWork->m_pEasyHeandle );

        if ( CURLM_OK == rc )
        {
            // set multi flag.
            pWork->m_pMultiHandle = m_pCURLM;

            ++m_nNumEasy;
            return true;
        }

        return false;
    }

    //--------------------------------------------------
    void CURLWorkThread::detachWork( CURLWork* pWork )
    {
        H_ASSERT( pWork->m_URLInfo.pWorkTh == this && pWork->m_pEasyHeandle && pWork->m_pMultiHandle == m_pCURLM );

        pWork->setNewCookieIfNeed();

        //
        {
            CURLWork* pWorkTest = NULL;
            ::curl_easy_getinfo( pWork->m_pEasyHeandle, CURLINFO_PRIVATE, &pWorkTest );

            if ( pWorkTest )
            {
                m_setDeadEasyHandles.insert( pWork->m_pEasyHeandle );
            }
        }

        //!just remove it
        //!cleanup easy handle in CURLWork's destructor
        CURLMcode rc = ::curl_multi_remove_handle( m_pCURLM, pWork->m_pEasyHeandle );

        H_ASSERT( rc == CURLM_OK );
        if ( rc != CURLM_OK )
        {
            fprintf( stderr, "curl_multi_remove_handle return rc=%d", rc );
        }

        // clear multi handle.
        pWork->m_pMultiHandle = NULL;

        --m_nNumEasy;
    }




    const char* CURLWorkThread::getHttpStateStr( CURLWork::HttpConnState hs )
    {
        const char* s = NULL;

        switch ( hs )
        {
            case CURLWork::HCS_NEW:
                s = "CURLWork::HCS_NEW";
                break;
            case CURLWork::HCS_CONNECTED:
                s = "CURLWork::HCS_CONNECTED";
                break;
            case CURLWork::HCS_SENDING:
                s = "CURLWork::HCS_SENDING";
                break;
            case CURLWork::HCS_RECVING:
                s = "CURLWork::HCS_RECVING";
                break;
            case CURLWork::HCS_DONE:
                s = "CURLWork::HCS_DONE";
                break;
            default:
                s = "CURLWork::HCS_unknown";
                break;
        }

        return s;
    }

    void CURLWorkThread::selectErrorLog( int selectret )
    {
#if defined(H_DEBUG_MODE) && defined(H_OS_WINDOWS)

        switch ( selectret )
        {
            case WSANOTINITIALISED :
                H_LOG_NAME_DEBUG( "CURLWorkThread", "A successful WSAStartup call must occur before using this function." );
                break;
            case WSAEFAULT :
                H_LOG_NAME_DEBUG( "CURLWorkThread", "The Windows Sockets implementation was unable to allocate needed resources for its internal operations, or the readfds, writefds, exceptfds, or timeval parameters are not part of the user address space." );
                break;
            case WSAENETDOWN :
                H_LOG_NAME_DEBUG( "CURLWorkThread", "The network subsystem has failed." );
                break;
            case WSAEINVAL :
                H_LOG_NAME_DEBUG( "CURLWorkThread", "The time-out value is not valid, or all three descriptor parameters were null." );
                break;
            case WSAEINTR :
                H_LOG_NAME_DEBUG( "CURLWorkThread", "A blocking Windows Socket 1.1 call was canceled through WSACancelBlockingCall." );
                break;
            case WSAEINPROGRESS :
                H_LOG_NAME_DEBUG( "CURLWorkThread", "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function." );
                break;
            case WSAENOTSOCK :
                H_LOG_NAME_DEBUG( "CURLWorkThread", "One of the descriptor sets contains an entry that is not a socket" );
                break;
            default:
                break;
        }

#endif
    }

    void CURLWorkThread::checkNewlyAddedWorks()
    {
        if ( m_vNewWorks.empty() )
        {
            return;
        }

        H_MINI_AUTOLOCK( m_lkNewWorks );
        CURLWorkVector::iterator it( m_vNewWorks.begin() );
        CURLWorkVector::iterator ite( m_vNewWorks.end() );

        for ( ; it != ite; it++ )
        {
            m_NewWorkList.push_back( *it );
        }

        m_vNewWorks.clear();
    }
    //----------------------------------------------
    void CURLWorkThread::cleanWorks()
    {
        /// new works.
        {
            H_MINI_AUTOLOCK( m_lkNewWorks );
            CURLWorkVector::iterator it( m_vNewWorks.begin() );
            CURLWorkVector::iterator ite( m_vNewWorks.end() );

            for ( ; it != ite; it++ )
            {
                CURLWork* pWork = *it;
                pWork->setHttpState( CURLWork::HCS_ERROR );
                pWork->notifyFinishError( EC_FAILED_INIT );

                // clean the object
                pWork->clean();
                pWork->unref();
            }

            m_vNewWorks.clear();
        }

        /// doing works.
        {
            CURLWorkList::iterator it( m_NewWorkList.begin() );
            CURLWorkList::iterator ite( m_NewWorkList.end() );

            for ( ; it != ite; it++ )
            {
                CURLWork* pWork = *it;
                pWork->setHttpState( CURLWork::HCS_ERROR );
                pWork->notifyFinishError( EC_FAILED_INIT );

                // clean the object
                pWork->clean();
                pWork->unref();
            }

            m_NewWorkList.clear();
        }

        /// Doing
        {
            CURLWorkMap::iterator it( m_DoingWorkMap.begin() );
            CURLWorkMap::iterator ite( m_DoingWorkMap.end() );

            for ( ; it != ite; it++ )
            {
                CURLWork* pWork = it->second;

                pWork->setHttpState( CURLWork::HCS_ERROR );
                pWork->notifyFinishError( EC_FAILED_INIT );

                // clean the object
                pWork->clean();
                pWork->unref();
            }

            m_DoingWorkMap.clear();
        }


		// easy handle pool
		{
			EasyHandleList::iterator it( m_vIdleEasyHandles.begin() ), ite( m_vIdleEasyHandles.end() );
			for(; it != ite; ++it )
			{
				::curl_easy_cleanup( *it );
			}
			m_vIdleEasyHandles.clear();
		}

    }

};//end of namespace net



// * Event types that can be polled for.  These bits may be set in `events'
//     to indicate the interesting event types; they will appear in `revents'
// to indicate the status of the file descriptor.  */
// #define POLLIN		0x001		/* There is data to read.  */
// #define POLLPRI		0x002		/* There is urgent data to read.  */
// #define POLLOUT		0x004		/* Writing now will not block.  */
//
// #ifdef __USE_XOPEN
// /* These values are defined in XPG4.2.  */
// # define POLLRDNORM	0x040		/* Normal data may be read.  */
// # define POLLRDBAND	0x080		/* Priority data may be read.  */
// # define POLLWRNORM	0x100		/* Writing now will not block.  */
// # define POLLWRBAND	0x200		/* Priority data may be written.  */
// #endif
//
// #ifdef __USE_GNU
// /* These are extensions for Linux.  */
// # define POLLMSG	0x400
// # define POLLREMOVE	0x1000
// # define POLLRDHUP	0x2000
// #endif
//
// /* Event types always implicitly polled for.  These bits need not be set in
//    `events', but they will appear in `revents' to indicate the status of
//    the file descriptor.  */
// #define POLLERR		0x008		/* Error condition.  */
// #define POLLHUP		0x010		/* Hung up.  */
// #define POLLNVAL	0x020		/* Invalid polling request.  */







#endif // end of #if H_PROVIDE_CURL

