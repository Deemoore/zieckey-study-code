#include "net/include/inner_pre.h"



#if H_PROVIDE_CURL



#include "curl/curl.h"


#include "net/include/curl_work.h"
#include "net/include/curl_service.h"


#include "net/include/http_post_file.h"
#include "curl_work_thread.h"


namespace net
{
	//-------------------------------------------------------------------------
	
	//----------------------------------------------
	HttpPostFile::HttpPostFile( const osl::StringA& url,int timeout )
	{
		m_timeout = timeout;
		m_ptrURLData->write( url.c_str(), url.length() );
	}
	//-------------------------------------------------------------------------
	HttpPostFile::HttpPostFile(  osl::MemoryDataStream* pURL, int timeout )
	{
		m_timeout = timeout;
		m_ptrURLData = pURL;
	}

    bool HttpPostFile::addParameter( const char* key, const void* value, const size_t valuelen )
    {
        //we use osl::StringA to hold the binary data, that is right
        //see the unit test case : TTrivial::test_std_string()
        m_mapParams.insert( StringAStringAMultiMap::value_type(key, osl::StringA( (char*)value, valuelen )) );
        return true;
    }

	////------------------------------------------------------
	//bool HttpPostFile::addParameter( const osl::StringA& key, const osl::StringA& value )
	//{
	//	return addParameter( key.c_str(), value.c_str() );
	//}
	////------------------------------------------------------
	//bool HttpPostFile::addParameter( const char* key, const char* value )
	//{
	//	// keep the values.
	//	m_mapParams[key] = value;
	//	return true;
	//}
	//------------------------------------------------------
	void HttpPostFile::addSendDataItem( const osl::StringA& strNameField, const osl::StringA& strFileNameField, osl::MemoryDataStream* psds )
	{
        addSendDataItem( strNameField.c_str(), strFileNameField.c_str(), psds );
	}
	//------------------------------------------------------
	void HttpPostFile::addSendDataItem( osl::MemoryDataStream* psds )
	{
		addSendDataItem( "file", "filename", psds );
	}

    void HttpPostFile::addSendDataItem( const char* strNameField, const char* strFileNameField, osl::MemoryDataStream* psds )
    {
        H_ASSERT(psds);
        m_vSendDatas.push_back( SendDataItem() );
        SendDataItem& item = m_vSendDatas.back();
        item.name     = strNameField;
        item.filename = strFileNameField;
        item.pData    = psds;
    }

    //------------------------------------------------------
	bool HttpPostFile::init( CURLWorkThread* pThread )
	{
		//static bool m_bInitialized = true;
		if ( m_bInitialized )
		{
			return true;
		}

		//
		H_ASSERT( this->getWorkThread() == pThread && "CURLWork::init failed, because of wrong workthread"  ) ;

		m_pEasyHeandle = pThread->newEasyHandleT();

		if ( NULL == m_pEasyHeandle )
		{
			H_LOG_NAME_ERROR( "CURLWork", "curl_easy_init in init failed" );
			return false;
		}


		// check parameters
		m_ptrURLData->write( "\0", 1 );
		m_URLInfo.url = ( char* )m_ptrURLData->getCache();


		// sets common parameters
		setCurlCommonOpt();
		//::curl_easy_setopt( m_pEasyHeandle, CURLOPT_VERBOSE, 1L );

		CURLFORMcode result = ( CURLFORMcode )0;

		/// parameters.
		{
			StringAStringAMultiMap::const_iterator it( m_mapParams.begin() ), ite( m_mapParams.end() );
			for(; it != ite; ++it )
			{
				result = ::curl_formadd( &m_formpost,
					&m_lastformpost,
					CURLFORM_COPYNAME, it->first.c_str(),
					CURLFORM_PTRCONTENTS, it->second.c_str(),
                    CURLFORM_CONTENTSLENGTH, (long)it->second.length(),
					CURLFORM_END );

				if(  result != CURL_FORMADD_OK )
				{
					return false;
				}
			}
		}

		///
		if ( !m_vSendDatas.empty() )
		{
			SendDataItemList::const_iterator it( m_vSendDatas.begin() ), ite( m_vSendDatas.end() );
			for(; it != ite; ++it )
			{
				result = ::curl_formadd( &m_formpost,
					&m_lastformpost,
					CURLFORM_COPYNAME, it->name.c_str(),
					CURLFORM_BUFFER, it->filename.c_str(),
					CURLFORM_BUFFERPTR, ( char* )it->pData->getCache(),
					CURLFORM_BUFFERLENGTH, ( long )it->pData->getSize(),
					CURLFORM_END );

				if(  result != CURL_FORMADD_OK )
				{
					return false;
				}
			}
		}


		::curl_easy_setopt( m_pEasyHeandle, CURLOPT_HTTPPOST, m_formpost );
		m_curl_slist = ::curl_slist_append( m_curl_slist, "Expect:" );
		::curl_easy_setopt( m_pEasyHeandle, CURLOPT_HTTPHEADER, m_curl_slist );

		m_bInitialized = true;
		return true;
	}

};//namespace



#endif // end of #if H_PROVIDE_CURL

