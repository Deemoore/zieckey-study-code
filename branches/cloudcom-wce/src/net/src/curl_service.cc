#include "net/include/inner_pre.h"

#if H_PROVIDE_CURL

#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/thread.h"
#include "osl/include/process_ext.h"
#include "osl/include/lock.h"

#include "net/include/curl_service.h"
#include "net/include/curl_work.h"
#include "curl_work_thread.h"
#include "curl/curl.h"


namespace net
{
    //-----------------------------------------------------
    // class CURLService
    //-----------------------------------------------------
    

    CURLService::CURLService( int nNumThreads )
        : m_bInitialized( false )
    {
        m_nNumThreads = nNumThreads > 0 ? nNumThreads : 2/*s_pNetRunConfig->getCURLThreadCount()*/;
        if ( m_nNumThreads <= 0 )
        {
            m_nNumThreads = osl::Process::getNumProcessor();
        }

		m_strName = "CURLService";

        m_nCURLWorkListLength = 200;
    }
	//--------------------------------------------
    bool CURLService::addWorkT( CURLWork* pWork )
    {
        CURLWorkThread* pThread = getBestThread();

        if ( pThread )
        {
            return pThread->addWorkT( pWork );
        }

        return false;
    }
	//--------------------------------------------
    CURLService::~CURLService()
    {
        stop();
    }
	//--------------------------------------------
	void CURLService::setName( const osl::StringA& strName )
	{
		m_strName = strName;
	}
    //--------------------------------------------
    bool CURLService::start()
    {
        // assure stop the thread.
        if ( isInitialized() )
        {
            return true;
        }

        CURLcode rc = ::curl_global_init( CURL_GLOBAL_ALL );

        if ( CURLE_OK != rc )
        {
            H_LOG_NAME_ERROR( "", "curl_global_init failed." );
            return -1;
        }

        //init work thread
        for ( int i = 0; i < m_nNumThreads; i++ )
        {
            // work thread
            m_vWorkThread[ i ] = H_NEW CURLWorkThread( this );

            {
                osl::OStringStreamA strTip;
                strTip << m_strName << ": " << i;
                m_vWorkThread[ i ]->setName( strTip.str() );
            }

            if (!m_vWorkThread[ i ]->start())
            {
                return false;
                break;
            }
            

            while ( !( m_vWorkThread[ i ]->isRunning() ) )
            {
                osl::Process::msSleep( 5 );
            }
        }

        m_bInitialized = true;

        return true;
    }


    void CURLService::stop()
    {
        if ( !m_bInitialized )
        {
            return;
        }

        // stop threads.
        for ( int i = 0; i < m_nNumThreads; i++ )
        {
            if ( m_vWorkThread[ i ] )
            {
                m_vWorkThread[ i ]->join();
                m_vWorkThread[ i ] = NULL;
            }
        }

        // clean global curl.
        bool bActive = false;
        if ( bActive )
        {
            // the code may not be stable, so close it just for now.
            ::curl_global_cleanup();
        }


        m_bInitialized = false;

        H_LOG_NAME_DEBUG( "", "CURLService stopped." );
    }
//	//! whether use curl pool. comment it is do not want use curl pool.
//#define H_USE_CURL_POOL
//	//---------------------------------------------------------------
//	void* CURLService::newEasyHandleT()
//	{
//#ifdef H_USE_CURL_POOL
//
//		H_MINI_AUTOLOCK( m_lkIdleEasyHandles );
//
//		void* pRet = NULL;
//
//		if( !m_vIdleEasyHandles.empty() )
//		{
//			pRet = m_vIdleEasyHandles.front();
//			m_vIdleEasyHandles.pop_front();
//		}
//		else
//		{
//			pRet = ::curl_easy_init();
//		}
//
//		return pRet;
//#else
//		return ::curl_easy_init();;
//#endif
//	}
//	//---------------------------------------------------------------
//	void CURLService::recycleEasyHandleT( void* pHandle )
//	{
//#ifdef H_USE_CURL_POOL
//
//		// clear parameters
//		{
//			// clear method.
//			::curl_easy_setopt( pHandle, CURLOPT_HTTPGET, 0L );
//			::curl_easy_setopt( pHandle, CURLOPT_POST, 0L );
//			::curl_easy_setopt( pHandle, CURLOPT_HTTPPOST, 0L );
//			::curl_easy_setopt( pHandle, CURLOPT_PUT, 0L );
//
//			// header
//			::curl_easy_setopt( pHandle, CURLOPT_HTTPHEADER, 0L );
//
//			// header content
//			::curl_easy_setopt( pHandle, CURLOPT_POSTFIELDS, 0L );
//			::curl_easy_setopt( pHandle, CURLOPT_POSTFIELDSIZE, 0L );
//		}
//
//		H_MINI_AUTOLOCK( m_lkIdleEasyHandles );
//		m_vIdleEasyHandles.push_back( pHandle );
//#else
//		::curl_easy_cleanup( pHandle );
//#endif
//
//	}
    //----------------------------------------------------------------------
//     void CURLService::setNewCookieIfNeed( CURLWork* pWork )
//     {
//         struct curl_slist * pCookieList = NULL;
//         CURLcode res = ::curl_easy_getinfo( pWork->m_pEasyHeandle, CURLINFO_COOKIELIST, &pCookieList );
//         if ( /*res != CURLE_OK || */!pCookieList )
//             return;
//
//
//         osl::OStringStreamA cookieTemp;
//         struct curl_slist* pCur = pCookieList;
//         while ( pCur )
//         {
//             cookieTemp << pCur->data;
//             cookieTemp << "\t";
//             pCur = pCur->next;
//         }
//
//         osl::HVector<osl::StringA> vec;
//         osl::StringUtil::split( vec, cookieTemp.str() );
//
//         osl::OStringStreamA cookie;
//
//         osl::StringA tokenname = "JSESSIONID";
//         for ( size_t i = 0; i < vec.size(); i++ )
//         {
//             if ( vec[i] == tokenname )
//             {
//                 if ( i + 1 < vec.size() )
//                 {
//                     cookie << tokenname << "=" << vec[i+1] << "; ";
//                     break;
//                 }
//             }
//         }
//
//         cookie << "domain=" << vec[0] << "; ";
//         m_staticStringCookie = cookie.str();
//         ::curl_slist_free_all( pCookieList );
//     }

};//end of namespace net


#endif // end of #if H_PROVIDE_CURL


