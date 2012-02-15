#ifndef _QNETWORKLIB_HTTPPOSTWORK_H_
#define _QNETWORKLIB_HTTPPOSTWORK_H_



#if H_PROVIDE_CURL




namespace net
{
	//! Http Post request work. CURLOPT_HTTPPOST 
	//! \remark the request NEVER post any data except a postfields stream which contains packed fields.
	//! \par all parameter pair is packed in PostFields stream. m_ptrSendMDStream. @see CURLOPT_POSTFIELDS.
	class _EXPORT_NET HttpPostWork : public CURLWork
	{
		H_ALLOC_OBJECT( HttpPostWork );
	public:
		//! \brief <b>Summary:</b>
		//!	    The constructor. When you new(ed) a work, you need call
		//! CURLService->addWorkT() to bind this work to a process CURLService
		//! which does the actual job. And you needn't worry about this work's
		//! memory delete jobs, because the CURLService will handle it.
		//! \node This class is only used for http post.
		//!     You can use HttpPostWork::addParameter to add data to post to server
		//! \param[in] url, the url, we will duplicate it.
		//!     eg1:"http://192.168.0.40/filewebserver/post.php"
        //! \param[in] len, the length of the url
		//! \param[in] timeout, is an upper bound on the amount of time elapsed
		//!     before the work is done(success or fail), seconds.
		HttpPostWork( const osl::StringA& url );
        HttpPostWork( const char* url, const osl::u32 len );
		HttpPostWork( osl::MemoryDataStream* pURL );


        //! \brief Append parameters to the HTTP post request
        //! \param strHttpBodyContent
        //!     like "user=jany&passwd=123456"
        //! \param len
        //! \return void
        void appendParameters( const osl::StringA& strHttpBodyContent );
        void appendParameters( const char* strHttpBodyContent, const osl::u32 len );

        //! \brief Set the HTTP body content of this post request
        //!     Most of the time, this function is called to send an already
        //!     formatted data content, like XML,json and so on.
        //! \note This will override this exist data which is added to this request before
        //! \warning Don't call <code>appendParameters</code> 
        //!     or <code>addParameters</code> in the same request
        //! \param strHttpRawBodyContent
        //!     like "This is a raw http body content data, no matter what format it is, we all support it"
        //! \param len
        //! \return void
        void setRawHttpBodyContent( const osl::StringA& strHttpRawBodyContent );
        void setRawHttpBodyContent( const char* strHttpRawBodyContent, const osl::u32 len );

	protected:
		//! \brief <b>Summary:</b>
		//£¡	Initiate a CURL session to process this work.
		//! \return	0, if success. <br>
		//!         -1, if failed.
		virtual bool	init( CURLWorkThread* pThread );

    private:
        osl::MemoryDataStreamPtr m_ptrPostData;

	};

	typedef osl::RefPtr<HttpPostWork>  HttpPostWorkPtr;

};//namespace



#endif // end of #if H_PROVIDE_CURL


#endif // end of #ifdef _QNETWORKLIB_HTTPPOSTWORK_H_


