#ifndef _QNETWORKLIB_HTTPGETWORK_H_
#define _QNETWORKLIB_HTTPGETWORK_H_




#if H_PROVIDE_CURL




namespace net
{

	//! Http Get protocol work.  use CURLOPT_HTTPGET method.
	//! \par All parameters on the request is packed in url. e.g"?param1=p1&param2=p2&param3=p3"
	class _EXPORT_NET HttpGetWork : public CURLWork
	{
		H_ALLOC_OBJECT( HttpGetWork );

	public:
		//! Default constructor.
		HttpGetWork();

		//! \param[in]: const osl::StringA & url, a full path url, like :
		//!     "http://192.168.0.40/filewebserver/get.php?type=object&uuid=6543.jpg"
        HttpGetWork( const osl::StringA& url );
        HttpGetWork( const char* url, const osl::u32 len );
		HttpGetWork( osl::MemoryDataStream* pURL );

		//! De-constructor.
		~HttpGetWork(){}

	private:

		bool m_bHasAddedInterrogationMark; // whether it HTTP GET request URL has been added interrogation(?)

	private:
		/**
		* @brief <b>Summary:</b>
		*	Initiate a CURL session to process this work.
		* @return	0, if success. <br>
		*			-1, if failed.
		*****************************************************************/
		virtual bool	init( CURLWorkThread* pThread );

	};
	typedef osl::RefPtr<HttpGetWork>  HttpGetWorkPtr;

};//namespace



#endif // end of #if H_PROVIDE_CURL

#endif // end of  _QNETWORKLIB_HTTPGETWORK_H_


