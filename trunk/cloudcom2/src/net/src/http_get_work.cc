#include "net/include/inner_pre.h"




#if H_PROVIDE_CURL





#include "net/include/curl_work.h"
#include "net/include/http_get_work.h"
#include "curl/curl.h"
#include "net/include/curl_service.h"
#include "curl_work_thread.h"

namespace net
{

	//-------------------------------------------------------------------------
	
	//------------------------------------------------------------
	HttpGetWork::HttpGetWork()
	{
		m_bHasAddedInterrogationMark = false;
	}
	//------------------------------------------------------------
	HttpGetWork::HttpGetWork( const osl::StringA& url )
	{
		m_ptrURLData->write( url.c_str(), url.length() );
		
		m_bHasAddedInterrogationMark = osl::StringUtil::contains( url, '?' );
	}
	//------------------------------------------------------------
	HttpGetWork::HttpGetWork( osl::MemoryDataStream* pURL )
	{
		H_ASSERT(pURL);
		m_ptrURLData->write( pURL->getCache(), pURL->getSize() );
		const char* szStart = (const char*)pURL->getCache();
		const char* szEnd   = (const char*)pURL->getCache() + pURL->getSize();
		m_bHasAddedInterrogationMark = std::find( szStart, szEnd, '?' ) != szEnd;
	}

    HttpGetWork::HttpGetWork( const char* pURL, const osl::u32 len )
    {
        H_ASSERT(pURL);
        m_ptrURLData->write( pURL, len );
        const char* szEnd   = (const char*)pURL + len;
        m_bHasAddedInterrogationMark = std::find( pURL, pURL, '?' ) != szEnd;
    }
    //------------------------------------------------------------
// 	bool HttpGetWork::addParameter( const osl::StringA& key, const osl::StringA& value )
// 	{
// 		return addParameter( key.c_str(), key.length(), value.c_str(), value.length() );
// 	}
// 	//------------------------------------------------------------
// 	bool HttpGetWork::addParameter( const char* key, const char* value )
// 	{
// 		return addParameter( key, strlen(key), value, strlen(value) );
// 	}
// 
// 	//------------------------------------------------------------
// 	bool HttpGetWork::addParameter( const char* key, size_t keylen, const char* value, size_t valuelen )
// 	{
// 		H_ASSERT( m_ptrURLData->getSize() && "url MUST be set first" );
// 
// 		if( !m_bHasAddedInterrogationMark )
// 		{
// 			m_ptrURLData->write( '?' );
// 			m_bHasAddedInterrogationMark = true;
// 		}
// 		else
// 		{
// 			m_ptrURLData->write( "&", 1 );
// 		}
// 
// 		m_ptrURLData->write( key, keylen );
// 		m_ptrURLData->write( '=' );
// 		m_ptrURLData->write( value, valuelen );
// 
// 		return true;
// 	}

	////------------------------------------------------------------
	//void HttpGetWork::setUrl( const osl::StringA &url )
	//{
	//	if ( osl::StringUtil::contains( url, '?' ) )
	//	{
	//		m_ptrURLData->write( url.c_str(), url.length() );
	//	} 
	//	else
	//	{
	//		const int size = 64;
	//		char buf[size]={0};
	//		snprintf( buf, size, "%d", (osl::u32)s_pTimer->getDate() );
	//		m_ptrURLData->write( url.c_str(), url.length() );
	//		m_ptrURLData->write( "?", 1 );
	//		m_ptrURLData->write( buf, strlen(buf) );
	//		m_ptrURLData->write( "=0", 2 );
	//	}
	//}
	//------------------------------------------------------------
	bool HttpGetWork::init( CURLWorkThread* pThread )
	{
		if ( m_bInitialized )
		{
			return true;
		}

		H_ASSERT( this->getWorkThread() == pThread && "CURLWork::init failed, because of wrong workthread"  ) ;

        if ( m_bBlockingDoHttpRequest )
        {
            m_pEasyHeandle = ::curl_easy_init();
        }
        else
        {
            m_pEasyHeandle = pThread->newEasyHandleT();
        }

		if ( NULL == m_pEasyHeandle )
		{
			H_LOG_NAME_ERROR( "CURLWork", "curl_easy_init in init failed" );
			return false;
		}

// 		if( !m_bHasAddedInterrogationMark )
// 		{
// 			m_bHasAddedInterrogationMark = true;
// 
// 			m_ptrURLData->write( '?' );
// 
// 			const int size = 64;
// 			char buf[size]={0};
// 			snprintf( buf, size, "%d=0", (osl::u32)s_pTimer->getDate() );
// 		
// 			m_ptrURLData->write( buf, strlen(buf) );
// 		}

        if( m_mapParams.size() > 0 )
        {
            StringAStringAMultiMap::iterator it( m_mapParams.begin() ), ite( m_mapParams.end() );
            for ( ; it != ite; ++it )
            {
                if ( m_bHasAddedInterrogationMark )
                {
                    m_ptrURLData->write( "&", 1 );
                }
                else
                {
                    m_ptrURLData->write( "?", 1 );
                    m_bHasAddedInterrogationMark = true;
                }
                const osl::StringA& key = it->first;
                const osl::StringA& value = it->second;
                m_ptrURLData->write( key.c_str(), key.length() );
                m_ptrURLData->write( "=", 1 );
                m_ptrURLData->write( value.c_str(), value.length() );
            }
        }

		m_ptrURLData->write( "\0", 1 );
		m_URLInfo.url = ( const char* )m_ptrURLData->getCache();

		// sets common parameters
		setCurlCommonOpt();

		::curl_easy_setopt( m_pEasyHeandle, CURLOPT_HTTPGET, 1L );

		if ( m_curl_slist )
		{
			::curl_easy_setopt( m_pEasyHeandle, CURLOPT_HTTPHEADER, m_curl_slist );
		}

		m_bInitialized = true;
		return true;
	}
	

};//namespace






#endif // end of #if H_PROVIDE_CURL

