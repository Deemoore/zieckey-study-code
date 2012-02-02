#include "net/include/inner_pre.h"



#if H_PROVIDE_CURL


#include "curl/curl.h"


#include "net/include/curl_work.h"
#include "net/include/http_post_work.h"
#include "net/include/curl_service.h"
#include "curl_work_thread.h"

namespace net
{

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	// HttpPostWork
	//-------------------------------------------------------------------------
	
	//-------------------------------------------------------------------------
	HttpPostWork::HttpPostWork( const osl::StringA& url )
	{
		m_ptrURLData->write( url.c_str(), url.length() );
        m_ptrPostData = H_NEW osl::MemoryDataStream( HTTP_CONTENT_SIZE );
	}

    HttpPostWork::HttpPostWork( const char* url, const osl::u32 len )
    {
        m_ptrURLData->write( url, (osl::u32)len );
        m_ptrPostData = H_NEW osl::MemoryDataStream( HTTP_CONTENT_SIZE );
    }
    //-------------------------------------------------------------------------
	HttpPostWork::HttpPostWork(  osl::MemoryDataStream* pURL )
	{
        m_ptrURLData->write( pURL->getCache(), pURL->getSize() );
        m_ptrPostData = H_NEW osl::MemoryDataStream( HTTP_CONTENT_SIZE );
	}

// 	//-------------------------------------------------------------------------
// 		bool HttpPostWork::addParameter( const osl::StringA& key, const osl::StringA& value )
// 		{
// 			addParameter( key.c_str(), value.c_str() );
// 	
// 			return true;
// 		}
// 		//-------------------------------------------------------------------------
// 		bool HttpPostWork::addParameter( const char* key, const char* value )
// 		{
// 			if( !m_pParameters )
// 			{
// 				m_pParameters = H_NEW osl::MemoryDataStream( HTTP_CONTENT_SIZE );
// 			}
// 	
// 			if ( 0 == m_pParameters->getSize() )
// 			{
// 				m_pParameters->write( ( void* )key, strlen( key ) );
// 				m_pParameters->write( "=", 1 );
// 				m_pParameters->write( ( void* )value, strlen( value ) );
// 			}
// 			else
// 			{
// 				m_pParameters->write( "&", 1 );
// 				m_pParameters->write( ( void* )key, strlen( key ) );
// 				m_pParameters->write( "=", 1 );
// 				m_pParameters->write( ( void* )value, strlen( value ) );
// 			}
// 	
// 			return true;
// 		}
	//-------------------------------------------------------------------------
// 	void HttpPostWork::setParameters( osl::MemoryDataStream* pParamsData )
// 	{
// 		m_pParameters = pParamsData;
// 	}
	//-------------------------------------------------------------------------
	bool HttpPostWork::init( CURLWorkThread* pThread )
	{
		//static bool m_bInitialized = true;
		if ( m_bInitialized )
		{
			return true;
		}

		H_ASSERT( this->getWorkThread() == pThread && "CURLWork::init failed, because of wrong workthread"  ) ;

		//
		m_pEasyHeandle = pThread->newEasyHandleT();

		if ( NULL == m_pEasyHeandle )
		{
			H_LOG_NAME_ERROR( "CURLWork", "curl_easy_init in init failed" );
			return false;
		}

		m_ptrURLData->write( "\0", 1 );
		m_URLInfo.url = ( char* )m_ptrURLData->getCache();


		//sets common parameters,
		setCurlCommonOpt();

		::curl_easy_setopt( m_pEasyHeandle, CURLOPT_POST, 1L );
		
		if( m_mapParams.size() > 0 )
		{            
            bool bAlreadyHasParameters = (m_ptrPostData->getSize() > 0);
            StringAStringAMultiMap::iterator it( m_mapParams.begin() ), ite( m_mapParams.end() );
            for ( ; it != ite; ++it )
            {
                if ( bAlreadyHasParameters )
                {
                    m_ptrPostData->write( "&", 1 );
                }
                else
                {
                    bAlreadyHasParameters = true;
                }

                const osl::StringA& key = it->first;
                const osl::StringA& value = it->second;
                m_ptrPostData->write( key.c_str(), key.length() );
                m_ptrPostData->write( "=", 1 );
                m_ptrPostData->write( value.c_str(), value.length() );
            }
		}

        ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_POSTFIELDS, m_ptrPostData->getCache() );
        ::curl_easy_setopt( m_pEasyHeandle, CURLOPT_POSTFIELDSIZE, m_ptrPostData->getSize() );

		//m_curl_slist = ::curl_slist_append( m_curl_slist, "Expect:" );
		//m_curl_slist = ::curl_slist_append( m_curl_slist, "Accept-Charset: gb2312,utf-8;q=0.7,*;q=0.7" );
		::curl_easy_setopt( m_pEasyHeandle, CURLOPT_HTTPHEADER, m_curl_slist );

		m_bInitialized = true;
		return true;
	}

    void HttpPostWork::appendParameters( const osl::StringA& strHttpBodyContent )
    {
        appendParameters( strHttpBodyContent.c_str(), (osl::u32)strHttpBodyContent.length() );
    }

    void HttpPostWork::appendParameters( const char* strHttpBodyContent, const osl::u32 len )
    {
        const char* pData = strHttpBodyContent;
        osl::u32 datalen = len;

        //trim the leading and ending '&'
        {
            if ( strHttpBodyContent[0] == '&' )
            {
                pData = strHttpBodyContent + 1;
                H_ASSERT( datalen >= 1 );
                datalen -= 1;
            }

            if ( strHttpBodyContent[len - 1] == '&' )
            {
                H_ASSERT( datalen >= 1 );
                datalen -= 1;
            }
        }

        if ( m_ptrPostData->getSize() == 0 )
        {
            m_ptrPostData->write( pData, datalen );
        }
        else
        {
            m_ptrPostData->write( "&", 1 );
            m_ptrPostData->write( pData, datalen );
        }
    }

    void HttpPostWork::setRawHttpBodyContent( const osl::StringA& strHttpRawBodyContent )
    {
        setRawHttpBodyContent( strHttpRawBodyContent.c_str(), (osl::u32)strHttpRawBodyContent.length() );
    }

    void HttpPostWork::setRawHttpBodyContent( const char* strHttpRawBodyContent, const osl::u32 len )
    {
        m_ptrPostData->reset();
        m_ptrPostData->write( strHttpRawBodyContent, len ); 
    }
}//namespace





#endif // end of #if H_PROVIDE_CURL

