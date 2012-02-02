#include "net/include/inner_pre.h"

#if H_PROVIDE_CURL


#include "net/include/curl_service.h"
#include "net/include/curl_work.h"
#include "curl_work_thread.h"
#include "net/include/http_get_work.h"
#include "curl/curl.h"


namespace net
{



    //-----------------------------------------------------
    //-----------------------------------------------------
    //-----------------------------------------------------
    // class CURLWork
    //-----------------------------------------------------
    //-----------------------------------------------------

    class OnFinishOKFunctor
    {
        CURLWork* m_pWork;
    public:
        OnFinishOKFunctor( CURLWork* pWork  ): m_pWork( pWork ) {}

        void operator()( CURLWork::Listener* pListener ) const
        {
            // onSocketEventT derived class.
            pListener->onFinishOKT( m_pWork );
        }
    private:
        OnFinishOKFunctor& operator=(const OnFinishOKFunctor&);
    };

    class OnFinishErrorFuntor
    {
        HttpErrorCode m_nError;
        const osl::StringA m_strDesc;
        CURLWork* m_pWork;

    public:
        OnFinishErrorFuntor( HttpErrorCode nError, const osl::StringA& strDesc, CURLWork* pWork )
            : m_nError( nError ), m_strDesc( strDesc ), m_pWork( pWork ) {}

        void operator()( CURLWork::Listener* pListener ) const
        {
            pListener->onFinishErrorT( m_nError, m_strDesc, m_pWork );
        }
    private:
        OnFinishErrorFuntor& operator=(const OnFinishErrorFuntor&);
    };


    struct OnWorkingStartFuntor
    {
        CURLWork* m_pWork;
        OnWorkingStartFuntor( CURLWork* pWork )
            : m_pWork( pWork ) {}

        void operator()( CURLWork::Listener* pListener ) const
        {
            pListener->onWorkStartT( m_pWork );
        }
    private:
        OnWorkingStartFuntor& operator=(const OnWorkingStartFuntor&);
    };


    class OnWorkingPercentageFunctor
    {
        CURLWork* m_pWork;
        float  m_fPercent;
    public:
        OnWorkingPercentageFunctor( CURLWork* pWork, double fPercent )
            : m_pWork( pWork ), m_fPercent( fPercent ) {}

        void operator()( CURLWork::Listener* pListener ) const
        {
            // onSocketEventT derived class.
            pListener->onWorkingPercentage( m_pWork, m_fPercent );
        }
    private:
        OnFinishOKFunctor& operator=(const OnFinishOKFunctor&);
    };

    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // CURLWork
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    

    int CURLWork::m_nTotalNo = 0;//! total number of works. for stat
    std::string CURLWork::m_staticCookieString = "";/*JSESSIONID=35F80024B82D01EB82047EDB8D81F9AE; domain=192.168.0.44;*/

    CURLWork::CURLWork()
            : m_timeout( HTTP_TIMEOUT )
            , m_curl_slist( NULL )
            , m_formpost( NULL )
            , m_lastformpost( NULL )
            , m_ptrURLData( H_NEW osl::MemoryDataStream( URL_DEFAULT_SIZE ) )
            , m_pEasyHeandle( NULL )
            , m_bInitialized( false )
            , m_bBlockingDoHttpRequest( false )
			, m_bCompressOperateResultFlag( true )
            , m_nHttpCode( -1 )
            , m_nHttpBodyTotalLenght( 0 )
            , m_ptrRecvMDStream( H_NEW osl::MemoryDataStream( HTTP_CONTENT_SIZE ) )
			, m_bFinished	( false )
			, m_pUserData( NULL )
            , m_pMultiHandle( NULL )
    {
        m_eHttpErrorCode = EC_NO_ERROR;

        m_nNo = m_nTotalNo++;
    }

    //------------------------------------------------------------
    CURLWork::~CURLWork()
    {
        if ( m_bBlockingDoHttpRequest )
        {
            clean();
        }
        
        H_ASSERT( !m_pEasyHeandle );
    }

    //------------------------------------------------------------
    bool CURLWork::clean()
    {
        if ( !m_pEasyHeandle )
        {
            return true;
        }

        // set finished flag.
        m_bFinished = true;

        if ( !m_bBlockingDoHttpRequest )
        {
            CURLWorkThread* pWorkTh = m_URLInfo.pWorkTh;
            H_ASSERT( pWorkTh );

            if ( m_pMultiHandle )
            {
                pWorkTh->detachWork( this );
            }


            // remove easy handle.
            pWorkTh->recycleEasyHandleT( m_pEasyHeandle );
        }
        else
        {
            // set null user data.
            ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_PRIVATE, NULL );//!socket_cb usrp
        }

		m_pEasyHeandle = NULL;


        // dirty socket
        m_URLInfo.sockfd = INVALID_SOCKET;

        if ( m_curl_slist )
        {
            curl_slist_free_all( m_curl_slist );
            m_curl_slist = NULL;
        }

        if ( m_formpost )
        {
            curl_formfree( m_formpost );
            m_formpost = NULL;
        }

        // remove all listeners.
        {
            H_MINI_AUTOLOCK( m_lkListenerList );

            ListenerList::iterator it = m_ListenerList.begin();
            ListenerList::iterator ite = m_ListenerList.end();

            for ( ; it != ite; ++it )
            {
                it->first->unref();
            }

            m_ListenerList.clear();
        }

        return true;
    }

    //------------------------------------------------------------
    bool CURLWork::addPermanentCookie( const osl::StringA& key, const osl::StringA& value )
    {
        return addPermanentCookie( key.c_str(), value.c_str() );
    }

    //------------------------------------------------------------
    bool CURLWork::addPermanentCookie( const char* key, const char* value )
    {
        osl::OStringStreamA os;
        size_t len = m_staticCookieString.length();
        if ( len > 0 )
        {
            os << m_staticCookieString;
            size_t index = m_staticCookieString.find_last_not_of(" \t\r");
            if ( index != osl::StringA::npos && m_staticCookieString[index] != ';' )
            {
                os << "; ";
            }
        }
        os << key << "=" << value << "; ";
        m_staticCookieString = os.str().c_str();
        return true;
    }

    //------------------------------------------------------------
    bool CURLWork::setPermanentCookie( const osl::StringA& cookie )
    {
        return setPermanentCookie( cookie.c_str() );
    }

    //------------------------------------------------------------
    bool CURLWork::setPermanentCookie( const char* cookie )
    {
        m_staticCookieString = cookie;
        return true;
    }

    //------------------------------------------------------
    bool CURLWork::addParameter( const osl::StringA& key, const osl::StringA& value )
    {
        return addParameter( key.c_str(), value.c_str() );
    }
    //------------------------------------------------------
    bool CURLWork::addParameter( const char* key, const char* value )
    {
        // keep the values.
        m_mapParams.insert( StringAStringAMultiMap::value_type(key, value) );

        return true;
    }

    //-------------------------------------------------------------------
    bool CURLWork::addHeader( const char* key, const char* value )
    {
        size_t keylen = strlen( key );
        size_t valuelen = strlen( value );
        return addHeader( key, keylen, value, valuelen );
    }

    //-------------------------------------------------------------------
    bool CURLWork::addHeader( const char* key, size_t keylen, const char* value, size_t valuelen )
    {
        char* content = (char*)H_ALLOC_NAME( keylen + valuelen + 1 + 1, "CURLWork::addHeader" );// "key:value"
        strncpy( content, key, keylen );
        content[keylen] = ':';
        strncpy( content + keylen + 1, value, valuelen );
        content[keylen + valuelen + 1] = '\0';
        bool retv = addHeader( content );
        osl::MemAlloc::free( content );
        return retv;
    }

    //-------------------------------------------------------------------
    bool CURLWork::addHeader( const char* headlerline )
    {
        m_curl_slist = ::curl_slist_append( m_curl_slist, headlerline );
        return (m_curl_slist != NULL) ? true : false;
    }

    //-------------------------------------------------------------------
    bool CURLWork::addHeader( const osl::StringA& key, const osl::StringA& value )
    {
        return addHeader( key.c_str(), key.length(), value.c_str(), value.length() );
    }

    //----------------------------------------------------------------------
    void CURLWork::setCurlCommonOpt()
    { 
        ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_URL, this->getUrl() );
        ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_NOSIGNAL, (long)1L );
        ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_TIMEOUT, (long)m_timeout );
        ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_PRIVATE, this );//!socket_cb user pointer

        ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_HTTP_VERSION, (long)CURLOPT_HTTP_VERSION);

        ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_WRITEFUNCTION, CURLWork::writeFunc );
        ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_WRITEDATA, this );//this will be used in writeFunc as the usrptr
        

        ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_HEADER, (long)0L );
        //if ( this->isResponseWithHeader() ) //Now we always receive the HTTP header.
        {
            m_ptrRecvHeaderMDStream = H_NEW osl::MemoryDataStream( HTTP_CONTENT_SIZE );
            ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_HEADERFUNCTION, CURLWork::writeHeaderFunc );
            ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_WRITEHEADER, this );//this will be used in writeHeaderFunc as the usrptr
        }
        
        //::curl_easy_setopt( m_pEasyHeandle, CURLOPT_COOKIEFILE, "" ); // just to start the cookieTemp engine
        //::curl_easy_setopt( m_pEasyHeandle, CURLOPT_VERBOSE, (long)1L );
		::curl_easy_setopt( m_pEasyHeandle, CURLOPT_CONNECTTIMEOUT, (long)10L );
		

        bool bHasPermanentCookie = (m_staticCookieString.length() > 0) && (m_staticCookieString.find( '=', 0 ) > 0) ;
        bool bHasDynamicCookie   = !m_mapDynamicCookies.empty();
        if ( bHasPermanentCookie || bHasDynamicCookie )
        {
            osl::OStringStreamA os;
            if ( bHasDynamicCookie )
            {
                StringAStringAMap::iterator it(  m_mapDynamicCookies.begin() );
                StringAStringAMap::iterator ite( m_mapDynamicCookies.end() );
                for ( ; it != ite; ++it )
                {
                    os << it->first << "=" << it->second << "; ";
                }
            }

            if ( bHasDynamicCookie )
            {
                os << m_staticCookieString;
            }
                
            //::curl_easy_setopt( m_pEasyHeandle, CURLOPT_COOKIE, m_staticCookieString.c_str() );

        }


        addHeader("Content-Type: application/json");

// #ifdef USE_SSL
        //::curl_easy_setopt( m_pEasyHeandle, CURLOPT_SSL_VERIFYPEER, (long)0L ); // just for supporting ssl 
//#endif

		//! set keep alive and time out.
		//m_curl_slist = ::curl_slist_append( m_curl_slist, "Keep-Alive: timeout=500000, max=50000" );
         
    }

    //----------------------------------------------------------------------
    void CURLWork::setNewCookieIfNeed()
    {
//          struct curl_slist * pCookieList = NULL;
//          CURLcode res = ::curl_easy_getinfo( m_pEasyHeandle, CURLINFO_COOKIELIST, &pCookieList );
//          if ( /*res != CURLE_OK || */!pCookieList )
//              return;
//          
//          
//          osl::OStringStreamA cookieTemp;
//          struct curl_slist* pCur = pCookieList;
//          while ( pCur )
//          {
//              cookieTemp << pCur->data;
//              cookieTemp << "\t";
//              pCur = pCur->next;
//          }
//  
//          osl::HVector<osl::StringA> vec;
//          osl::StringUtil::split( vec, cookieTemp.str() );
//  
//          osl::OStringStreamA cookie;
//  
//          osl::StringA tokenname = "JSESSIONID";
//          for ( size_t i = 0; i < vec.size(); i++ )
//          {
//              if ( vec[i] == tokenname )
//              {
//                  if ( i + 1 < vec.size() )
//                  {
//                      cookie << tokenname << "=" << vec[i+1] << "; ";
//                      break;
//                  }
//              }
//          }
//  
//          cookie << "domain=" << vec[0] << "; ";
//          m_staticCookieString = cookie.str().c_str();
//          ::curl_slist_free_all( pCookieList );
    }

    size_t CURLWork::writeFunc( void* ptr, size_t size, size_t nmemb, void *usrptr )
    {
        CURLWork* pWork = ( CURLWork* ) usrptr;
        pWork->m_ptrRecvMDStream->write( ptr, size * nmemb );
        
        //At present, we will do it only in HttpGetWork
        if ( NULL != dynamic_cast<HttpGetWork*>(pWork) )
        {
            if ( pWork->m_nHttpBodyTotalLenght > 0 )
            {
                double fPercent = (double)pWork->getRecvDataStream()->getSize() / (double)pWork->m_nHttpBodyTotalLenght;
                pWork->notifyListeners( OnWorkingPercentageFunctor( pWork, fPercent ) );

//#ifdef H_DEBUG_MODE
//                osl::OStringStreamA log;
//                log << "Notify listeners the working percentage, body length=" 
//                    << pWork->m_nHttpBodyTotalLenght
//                    << ", percentage=" << fPercent;
//                H_LOG_NAME_DEBUG( "CURLWork", log.str() );
//#endif
            }
        }

        return nmemb * size;
    }

    size_t CURLWork::writeHeaderFunc( void* ptr, size_t size, size_t nmemb, void *usrptr )
    {
        //Content-Length: 4224
        CURLWork* pWork = ( CURLWork* ) usrptr;
        pWork->getRecvHeaderDataStream()->write( ptr, size * nmemb );
        return nmemb * size;
    }

    void CURLWork::notifyFinishOK()
    {
        if ( m_bFinished )
        {
            return;
        }

        // set finished flag.
        m_bFinished = true;

		// if ( getHttpMethod() == HTTP_DOWNLOAD_FILE ) // download file
        {
            onWorkFinishedT();
            notifyListeners( OnFinishOKFunctor( this ) );
            return;
        }

        //m_JsonObjectPtr = H_NEW Json::JSONObject();

        //bool isok = m_JsonObjectPtr->parse( ( char* )m_ptrRecvMDStream->getCache(), m_ptrRecvMDStream->getSize() ) > 0 ? true : false;

        //if ( isok )//recv string convert to json is successful
        //{
        //    Json::JSONString* code = m_JsonObjectPtr->getJSONString( "code" );

        //    if ( code ) // curl process is successful
        //    {
        //        osl::StringA sc(*code);
        //        osl::StringUtil::toLowerCase( sc );
        //        if ( sc == "ok" )
        //        {
        //            notifyListeners( OnFinishOKFunctor( this ) );
        //            return;
        //        }
        //    }
        //}

        ////come here means something is wrong
        //notifyFinishError( (osl::u32)-1, false );
    }

    void CURLWork::notifyFinishError( osl::u32 ce, bool bCheckWhetherFinished )
    {

        if ( m_bFinished && bCheckWhetherFinished )
        {
            return;
        }

        // set finished flag.
        m_bFinished = true;

        osl::String s;
        m_eHttpErrorCode = getCURLErrorCode(ce, s);

        osl::OStringStreamA msg;
        msg << "Error, response code=" << getHttpCode() << ", " << s;
//         if ( s_pNetRunConfig->isLogCURLError() || s_pNetRunConfig->isLogCURLTrivial() )
//         {
//             msg << ", "<< s << ", server response msg : "
//                 << osl::StringA( (const char*)m_ptrRecvMDStream->getCache(), m_ptrRecvMDStream->getSize() );
//             H_LOG_NAME_WARN( "CURLWork", msg.str() );
//         }

        onWorkFinishedT();
        notifyListeners( OnFinishErrorFuntor( m_eHttpErrorCode, msg.str(), this ) );
    }



    template<typename _Functor >
    void CURLWork::notifyListeners( const _Functor& func )
    {
        H_MINI_AUTOLOCK( m_lkListenerList );

        ListenerList::iterator it = m_ListenerList.begin();
        ListenerList::iterator ite = m_ListenerList.end();

        while ( it != ite )
        {
            if ( it->second )
            {
                func( it->first );
                ++it;
            }
            else
            {
                it->first->unref();
                ListenerList::iterator itCur = it++;
                m_ListenerList.erase( itCur );
            }
        }
    }

    void CURLWork::addListener( Listener* pl )
    {
		if( !pl )
		{
			return;
		}

        H_MINI_AUTOLOCK( m_lkListenerList );

        if ( m_bFinished )
        {
            pl->onFinishErrorT( EC_FAILED_INIT, "init error", this );
            return;
        }

        // ref it.
        pl->ref();

        ListenerList::iterator it = m_ListenerList.begin();
        ListenerList::iterator ite = m_ListenerList.end();

        for ( ; it != ite; ++it )
        {
            if ( it->first == pl )
            {
                it->second = true;
                return;
            }
        }

        m_ListenerList.push_back( ListenerEntry( pl, true ) );
    }

    bool CURLWork::initialize( const CURLWorkThread* caller )
    {
        notifyListeners( OnWorkingStartFuntor( this ) );
        return init( const_cast<CURLWorkThread*>( caller ) );
    }

    bool CURLWork::doHttpBlockingRequest()
    {
        H_ASSERT( m_bBlockingDoHttpRequest && "DO NOT call this method if m_bBlockingDoHttpRequest = false");
        if ( !m_bBlockingDoHttpRequest )
        {
            return false;
        }
        
        initialize( NULL );
        ::CURLcode ret = ::curl_easy_perform( m_pEasyHeandle );
        osl::StringA msg;
        m_eHttpErrorCode = getCURLErrorCode( ret, msg );
        if (ret == CURLE_OK)
        {
            if ( ( 0 == m_nHttpCode ) || ( m_nHttpCode >= 200 && m_nHttpCode < 300 ) || m_nHttpCode == 304 )
            {
                notifyFinishOK();
                return true;
            }
        }

        notifyFinishError(m_eHttpErrorCode);
        return false;
    }

    bool CURLWork::initCURLGlobal()
    {
        CURLcode rc = ::curl_global_init( CURL_GLOBAL_ALL );
        return CURLE_OK == rc;
    }

    void CURLWork::cleanupCURLGlobal()
    {
        ::curl_global_cleanup();
    }

    net::HttpErrorCode CURLWork::getCURLErrorCode( osl::u32 ce , osl::String &s )
    {
        HttpErrorCode hec;
        switch ( ce )
        {
        case CURLE_COULDNT_RESOLVE_PROXY:
        case CURLE_COULDNT_RESOLVE_HOST:
            hec = EC_HOST_UNREACHABLE;
            s = "Host is unreachable.";
            break;
        case CURLE_COULDNT_CONNECT:
            hec = EC_COULDNT_CONNECT;
            s = "Could not connect to host, the host maybe is busy.";
            break;
        case CURLE_REMOTE_ACCESS_DENIED:
            hec = EC_REMOTE_ACCESS_DENIED;
            s = "A service was denied by the server";
            break;
        case CURLE_UPLOAD_FAILED:
            hec = EC_UPLOAD_FAILED;
            s = "Upload failed";
            break;
        case CURLE_HTTP_POST_ERROR:
            hec = EC_HTTP_POST_ERROR;
            s = "Http post error";
            break;
        case CURLE_SEND_ERROR:
            hec = EC_SEND_ERROR;
            s = "Client sending error";
            break;
        case CURLE_RECV_ERROR:
            hec = EC_RECV_ERROR;
            s = "Client receiving error";
            break;
        case CURLE_REMOTE_DISK_FULL:
            hec = EC_REMOTE_DISK_FULL;
            s = "Remote server disk is full";
            break;
        case CURLE_REMOTE_FILE_EXISTS:
            hec = EC_REMOTE_FILE_EXISTS;
            s = "Remote file exists";
            break;
        case CURLE_REMOTE_FILE_NOT_FOUND:
            hec = EC_REMOTE_FILE_NOT_FOUND;
            s = "Remote file not found";
            break;
        case CURLE_OK:
            hec = EC_NO_ERROR;
            s = "No error";
            break;
        case CURLE_FAILED_INIT:
            hec = EC_FAILED_INIT;
            s = "Init failed or bad socket";
            break;
        case 404:
            hec = EC_REMOTE_FILE_NOT_FOUND;
            s = "Remote file not exist";
            break;
        case CURLE_OPERATION_TIMEDOUT:
            hec = EC_TIMEOUT;
            s = "tiemout";
            break;
        default:
            hec = EC_UNKNOWN_ERROR;
            s = "Unknown error, or server error";
            break;
        }

        return hec;
    }

    osl::StringA CURLWork::getHttpErrorCodeStr() const
    {
        H_CASE_STRING_BIGIN(m_eHttpErrorCode);
        H_CASE_STRING(EC_NO_ERROR);
        H_CASE_STRING(EC_HOST_UNREACHABLE);
        H_CASE_STRING(EC_COULDNT_CONNECT);
        H_CASE_STRING(EC_REMOTE_ACCESS_DENIED);
        H_CASE_STRING(EC_UPLOAD_FAILED);
        H_CASE_STRING(EC_HTTP_POST_ERROR);
        H_CASE_STRING(EC_SEND_ERROR);
        H_CASE_STRING(EC_RECV_ERROR);
        H_CASE_STRING(EC_REMOTE_DISK_FULL);
        H_CASE_STRING(EC_REMOTE_FILE_EXISTS);
        H_CASE_STRING(EC_REMOTE_FILE_NOT_FOUND);
        H_CASE_STRING(EC_FAILED_INIT);
        H_CASE_STRING(EC_TIMEOUT);
        H_CASE_STRING(EC_UNKNOWN_ERROR);
        H_CASE_STRING_END;
    }
}


#endif // end of #if H_PROVIDE_CURL

