#ifndef _QNETWORKLIB_CURLWORK_H__
#define _QNETWORKLIB_CURLWORK_H__




#if H_PROVIDE_CURL


#include "osl/include/process_ext.h"
#include "osl/include/lock.h"

// 
// #include <sys/types.h>
// #include <sys/stat.h>

// #ifdef H_OS_WINDOWS
// #include <process.h>
// #elif defined(H_OS_LINUX)
// #include <unistd.h>
// #endif


// FD:
struct curl_slist;
struct curl_httppost;
struct curl_httppost;
//enum CURLcode;

namespace net
{
	class CURLWorkThread;
	class CURLService;
	class CURLWorkListener;
	class HttpHeaderParser;



	/*! @enum HTTP Error Code	 */
	enum HttpErrorCode
	{
		EC_NO_ERROR = 3000,	//! no error
		EC_HOST_UNREACHABLE,
		EC_COULDNT_CONNECT,
		EC_REMOTE_ACCESS_DENIED,
		EC_UPLOAD_FAILED,
		EC_HTTP_POST_ERROR,
		EC_SEND_ERROR,
		EC_RECV_ERROR,
		EC_REMOTE_DISK_FULL,
		EC_REMOTE_FILE_EXISTS,
		EC_REMOTE_FILE_NOT_FOUND,
		EC_FAILED_INIT,
		EC_TIMEOUT,
		EC_UNKNOWN_ERROR
	};

	enum { HTTP_TIMEOUT  = 600, }; //http action timeout , seconds

	/*! @class CURLWork HCURLService.h "HCURLService.h"
	*  @brief
	*		This is the work class.
	*/
	class _EXPORT_NET CURLWork : public osl::Object
	{
		H_ALLOC_OBJECT( CURLWork );
	public:
		H_DEF_MAP(      osl::StringA, osl::StringA, StringAStringAMap );
		H_DEF_MULTIMAP( osl::StringA, osl::StringA, StringAStringAMultiMap );

		/*! @enum HTTP Connection State	 */
		enum HttpConnState
		{
			HCS_NEW = 2000,	//!	new url
			HCS_CONNECTED,	//! 2001 has establish connection
			HCS_SENDING,	//! 2002 sending data
			HCS_RECVING,	//! 2003 receiving data
			HCS_DONE,		//! 2004 has done all the things, to be deleted
			HCS_ERROR		//! 2005 something error
		};

		//! Compress method.
//         enum CompressionMethod
//         {
//             ECM_NO_COMPRESSION = Z_NO_COMPRESSION,                             //! no compress
//             ECM_BZIP_BEST_SPEED = Z_BEST_SPEED,                 //! use bzip and use fast compress.
//             ECM_BZIP_BEST_COMPRESSION = Z_BEST_COMPRESSION,     //! use bzip and use minimal size compress.
//             ECM_DEFAULT_COMPRESSION = Z_DEFAULT_COMPRESSION,    //! the default compression
//         };

		enum { HTTP_CONTENT_SIZE = 4096 };
		enum { URL_DEFAULT_SIZE = 256 };

		//--------------------------------------------------------------------
		/*! @class CURLWorkListener
		*  @brief
		*	This listener interface is used for notifying callers
		*/
		class _EXPORT_NET Listener : public osl::RefTarget
		{
		public:
			//! \brief <b>Summary:</b>
			//! 	This function is called by CURLWork(observable) to notify
			//! Listeners that this curl work is done, and the received data
			//! from server is preserved in m_ptrRecvMDStream
			//! \note This function is called in another thread, you <b>MUST</b>
			//!     be care about the multi thread-safe problem
			//! \param  pw, the CURLWork which is listened by this listener.
			//! you can call CURLWork::getRecvDataStream() to get the server response string.
			virtual void onFinishOKT( net::CURLWork* pw ) = 0;


			//! \brief <b>Summary:</b>
			//! 	This function is called by CURLWork(observable) to notify
			//! Listeners that the work is no done because something error.
			//! \note This function is called in another thread, you <b>MUST</b>
			//!     be care about the multi thread-safe problem
			//! \param hec, error code
			//! \param errmsg, describes the error message
			//! \param pw, the CURLWork which is listened by this listener
			virtual void onFinishErrorT( net::HttpErrorCode hec, const osl::StringA& errmsg, net::CURLWork* pw ) = 0;

			//! \brief <b>Summary:</b>
			//! 	This function is called by CURLWork(observable) to notify
			//! Listeners that the work is beginning to work
			//! \note This function is called in another thread, you <b>MUST</b>
			//!     be care about the multi thread-safe problem
			virtual void onWorkStartT( net::CURLWork* pw ) {};


			//! \brief <b>Summary:</b>
			//!     This function is called by CURLWork(observable) to notify
			//!   Listeners that how much percent of the work has been finished.
			//!   The value range is 0.0~1.0 , like 1.0 means 100% and 0.25 means 25%
			//! \note At percent, ONLY HttpGetWork's listeners will be called
			//! \note This function is called in another thread, you <b>MUST</b>
			//!     be care about the multi thread-safe problem
			//! \param fPercent The percent
			virtual void onWorkingPercentage( net::CURLWork* pw, double fPercent ) {};
		};//end of class Listener

	public:
		CURLWork();

		virtual ~CURLWork();

		void addListener( Listener* pl );

		//! \brief <b>Summary:</b>
		//!     Add parameter to this post.
		//!     like key="username" , value="qihoo"
		//!     like key="password" , value="123456"
		//! \note If add the same more than one time,
		//!       the new key-value will be append as new key-value(s), NOT override the old key-value.
		//! \param[in] key, the name of the parameter
		//! \param[in] value, the value
		//! \return true, if add successfully
		//!	    false, if add failed
		bool addParameter( const osl::StringA& key, const osl::StringA& value );
		bool addParameter( const char* key, const char* value );

		//! Sets/Gets params map. The method SHOULD be called before work started.
		bool setParameters( const StringAStringAMultiMap& mapParams )
		{
			m_mapParams = mapParams;
			return true;
		}

		//! Gets parameter pairs map.
		const StringAStringAMultiMap& getParameters()const
		{
			return	m_mapParams;
		}

		//! \brief: add a HTTP header line
		//! e.g: key="Content-Type", value="text/xml"
		bool addHeader( const char* key, const char* value );
		bool addHeader( const osl::StringA& key, const osl::StringA& value );
		bool addHeader( const char* key, size_t keylen, const char* value, size_t valuelen );

		//! \brief: add a HTTP header line
		//! e.g: "Content-Type: text/xml"
		bool addHeader( const char* headlerline );



		//! \brief: Add a permanent cookie
		//! \remark: This will effect all the CURLWorks in the future in the program life cycle.
		//! \param[in]: const osl::StringA & key, the name of the cookie, e.g:JSESSIONID
		//! \param[in]: const osl::StringA & value, the value, e.g:35F80024B82D01EB82047EDB8D81F9AE
		//! \return: bool
		static bool addPermanentCookie( const osl::StringA& key, const osl::StringA& value );
		static bool addPermanentCookie( const char* key, const char* value );

		//! \brief: Set a new permanent cookie, this will clear the old permanent cookie
		//! \remark: This will effect all the CURLWorks in the future in the program life cycle.
		//! \param[in]: osl::StringA & cookie, the cookie string,
		//!     like "JSESSIONID=35F80024B82D01EB82047EDB8D81F9AE; domain=192.168.0.44;"
		//! \return: bool
		static bool setPermanentCookie( const osl::StringA& cookie );
		static bool setPermanentCookie( const char* cookie );

		//! clear all the permanent cookies
		//! \remark: This will effect all the CURLWorks in the future in the program life cycle.
		static void clearPermanentCookie()
		{
			m_staticCookieString = "";
		}


		//! \brief: Add a dynamic cookie, which is disposable cookie.
		//! \remark: This cookie ONLY effects this CURLWork and don't effect any other CURLWorks.
		//! \param[in]: const osl::StringA & key, the name of the cookie, e.g:md5
		//! \param[in]: const osl::StringA & value, the value, e.g:f119c865306c35e64eb00f65d7279664
		//! \return: bool
		bool addDynamicCookie( const osl::StringA& key, const osl::StringA& value );
		bool addDynamicCookie( const char* key, const char* value );

		void clearDynamicCookie()
		{
			m_mapDynamicCookies.clear();
		}

		void setUserData( void* pUserData );
		void* getUserData() const;

		void setObjectUserData( osl::Object* pUserData );
		osl::Object* getObjectUserData() const;



		//! \brief <b>Summary:</b>
		//! 	This function return a data pointer, which points the HTTP body
		//! data we receive from web server. If you want to use the data, you
		//! MUST call MemoryDataStream::ref() to hold the data, and when you
		//! don't need the data, you MUST call MemoryDataStream.unref().
		//! @return a MemoryDataStream pointer
		//osl::MemoryDataStream* getRecvDataStream() const;
        osl::MemoryDataStreamPtr getRecvDataStream() const
        {
            return m_ptrRecvMDStream;
        }


		//! \brief <b>Summary:</b>
		//! 	This function return a data pointer, which points the HTTP
		//! header data we receive from web server. If you want to use the data,
		//! you MUST call MemoryDataStream::ref() to hold the data, and when you
		//! don't need the data, you MUST call MemoryDataStream.unref().
		//! \remark If the withheader flag is not set, this call will return NULL.
		//! \return a MemoryDataStream pointer
		//osl::MemoryDataStream* getRecvHeaderDataStream() const;
        osl::MemoryDataStreamPtr getRecvHeaderDataStream() const
        {
            return m_ptrRecvHeaderMDStream;
        }


		//! \brief Set whether we will call curl_easy_perform
		//!        to do a HTTP synchronized request
		//! \param bool val -
		//! \return void -
		void setBlockingDoHttpRequest( bool val )
        {
            m_bBlockingDoHttpRequest = val;
		}

        bool isBlockingDoHttpRequest() const { return m_bBlockingDoHttpRequest; }


        //! \brief Do a HTTP synchronized request
        //!     We will call curl_easy_perform to do this work.
        //! \warning DO NOT call this method if m_bBlockingDoHttpRequest = false
        //! \return bool - return true if successfully
        //!         if return false, you can call getHttpErrorCode 
        //!         or getHttpErrorCodeStr to get more information
        bool doHttpBlockingRequest();

		//! Gets url data which may include post parameters.
		//! \note The returned object MAY not include the end '\0'.
		//osl::MemoryDataStream* getURLDataStream()const;
        osl::MemoryDataStreamPtr getURLDataStream()const
        {
            return m_ptrURLData;
        }

		const char* getUrl() const;
		void setUrl( const char* url );

		static osl::u32 getWorkTotalCount();
		int getWorkNo() const;

        //! in seconds
		void setTimeOut( int timeout );
		int getTimeOut() const;

		//! Gets header information.
		bool isResponseWithHeader() const;

		//! \param nWithHeader, 1 with header, 0 without header
		void setResponseWithHeader( bool bWithHeader );

		CURLWork::HttpConnState getHttpState() const;

		bool isCompressOK() const;
		bool isUncompressOK() const;

		long getHttpCode() const;

        net::HttpErrorCode getHttpErrorCode() const { return m_eHttpErrorCode; }
        osl::StringA getHttpErrorCodeStr() const;

    public:
        static bool initCURLGlobal();
        static void cleanupCURLGlobal();

	protected:
		//! \brief <b>Summary:</b>
		//!     Initiate a CURL session to process this work.
		//! \return false if failed to initialize the work.
		virtual bool init( CURLWorkThread* pThread ) = 0;

		//! Notification that the work has finished.
		//! It is called by notifyFinishOK(...) and notifyFinishError(...).
		//! \remark Derived class SHOULD overwrite the method
		virtual void onWorkFinishedT() {};

	protected:

		class URLInfo;

		bool initialize( const CURLWorkThread* caller );


		//! Query whether is initialized.
		bool isInitialized();

		/**
		* @brief <b>Summary:</b>
		*		This function gets called by libcurl as soon as
		*	there is HTTP body data received which needs to be processed.<br>
		*		The size of the data pointed to by ptr is size multiplied
		*	with nmemb, it will not be zero terminated. <br>
		* @param[in] data, point to the received data
		* @param[in] size, the size
		* @param[in] nmemb, the unit
		* @param[in]  usrptr, the user ptr,
		*			set by option CURLOPT_WRITEDATA...
		* @return	the number of bytes actually taken care of. <br>
		*		If that amount differs from the amount passed to your function,
		*	it'll signal an error to the library and it will abort the transfer
		*	and return CURLE_WRITE_ERROR.
		**********************************************************************/
		static size_t writeFunc( void* ptr, size_t size, size_t nmemb, void *usrptr );



		/**
		* @brief <b>Summary:</b>
		*		This function gets called by libcurl as soon as
		*	there is HTTP header data received which needs to be processed.<br>
		*		The size of the data pointed to by ptr is size multiplied
		*	with nmemb, it will not be zero terminated. <br>
		* @param[in] data, point to the received data
		* @param[in] size, the size
		* @param[in] nmemb, the unit
		* @param[in]  usrptr, the user ptr,
		*			set by option CURLOPT_WRITEDATA...
		* @return	the number of bytes actually taken care of. <br>
		*		If that amount differs from the amount passed to your function,
		*	it'll signal an error to the library and it will abort the transfer
		*	and return CURLE_WRITE_ERROR.
		**********************************************************************/
		static size_t writeHeaderFunc( void* ptr, size_t size, size_t nmemb, void *usrptr );

		//! Gets current work thread of the job
		CURLWorkThread* getWorkThread() const;

		void setHttpCode( long code );

	protected:

		//! Called by thread when work finished successfully.
		void notifyFinishOK();//! call Listener.onWorkDone


		//!	\brief Called by thread when work finished wrongly.
		//!    it will call Listener.onWorkError CURLCode
		//!	\param codeError,
		//!	\param bCheckWhetherFinished, whether check it is finished.
		//!	\return void,
		void notifyFinishError( osl::u32 codeError, bool bCheckWhetherFinished = true );

        
        //! \brief 
        //! \param osl::u32 ce - the CURLcode 
        //! \param[out] osl::String & s - 
        //! \return net::HttpErrorCode - 
        HttpErrorCode getCURLErrorCode( osl::u32 ce, osl::String &s );

		template<typename _Functor >
		void notifyListeners( const _Functor& func );

		//! the cookie string is used to connect with web server as an authority.
		void setCurlCommonOpt();//! all curl will set this options.
		void setNewCookieIfNeed();//! called after the work is done

	protected:
		static std::string      m_staticCookieString;//using std::string because of it is a static variable
		StringAStringAMap        m_mapDynamicCookies;
		StringAStringAMultiMap           m_mapParams;

	protected:

		/*! @struct URLInfo HCURLService.h "HCURLService.h"
		*  @brief
		*		This struct maintain all the info about a url.
		*/
		class URLInfo
		{
		public:
			const char*         url;	//!	the url
			volatile SOCKET  sockfd;	//!	socket fd
			HttpConnState	  state;	//! the perform state
			CURLWorkThread*	pWorkTh;	//! the thread process this url. Every thread has a CURL_Multi handle,
			//!and any easy_handle can and only can attach to one multi handle
			bool         withheader;	//! http response header,
		public:
			URLInfo(): url( NULL ), sockfd( INVALID_SOCKET ),
				state( HCS_NEW ), pWorkTh( NULL ), withheader( false )
			{}
		}; // end of class URLInfo


        bool               m_bBlockingDoHttpRequest; //! if true, we will call curl_easy_perform to do a HTTP synchronized request

	protected:
		//! Attributes for derived classes
		long                              m_timeout;//! the upper bound time which will take. in seconds
		//double                     m_ftmCreateTime;//! the time this work is created

		curl_slist*                    m_curl_slist;
		curl_httppost*                   m_formpost;
		curl_httppost*               m_lastformpost;

		URLInfo                           m_URLInfo;

		osl::MemoryDataStreamPtr       m_ptrURLData; //!hold the url and query data

		void*	                     m_pEasyHeandle;   //! curl easy handle
		//CURLService*                 m_pIOService;   //! which io service the work attached to. it is managed by derived class

		bool                         m_bInitialized; //! whether is Initialized


		bool           m_bCompressOperateResultFlag; //! true for successfully compress or uncompress. false for failed

		long                            m_nHttpCode; //! The http code, like: 200,201,304,404 ...

        HttpErrorCode              m_eHttpErrorCode;

		HttpHeaderParser*       m_pHttpHeaderParser;
		osl::s64             m_nHttpBodyTotalLenght;

		osl::MemoryDataStreamPtr       m_ptrRecvMDStream; //! hold the received HTTP body data
		osl::MemoryDataStreamPtr m_ptrRecvHeaderMDStream; //! hold the received HTTP header data

	private:

		int                                    m_nNo;//!work number
		static int                        m_nTotalNo;//!total works count, for stat

		bool		                     m_bFinished;//! whether this work is finished

		void*                            m_pUserData;//! A user data associated with this work. we just store this pointer.
		osl::ObjectPtr          m_ptrHObjectUserData;

		//! second bool param:	false, means need to remove it
		//!						true, means need to onSocketEventT it
		typedef std::pair<Listener*, bool>  ListenerEntry;
		H_DEF_LIST( ListenerEntry, ListenerList );
		ListenerList                 m_ListenerList;
		osl::MiniLock            m_lkListenerList;   // lock for m_ListenerList

	private:

		// Attributes managed by Thread.
		void*                          m_pMultiHandle;  //! multi handle to which the easy handle is bound to.
		SOCKET                        m_ActuralSocket;   //! newly allocated socket. It may differenct from m_URLInfo.socketid

	private:
		//! Hide default constructor to force derived class must call
		//! this CURLWork( const URLInfo* urlinfo ) constructor
		CURLWork( const CURLWork& );
		friend class CURLService;
		friend class CURLWorkThread;

		//! Sets/Gets socket hand of the url request.
		SOCKET 	getSocket() const;
		void  	setSocket( SOCKET sock );

		//! Sets/Gets http state.
		void setHttpState( CURLWork::HttpConnState s );

		//! Sets work thread. Called by Service
		void setWorkThread( CURLWorkThread*  th );

		// Clean the object. It is called by thread when the easy handle should be cleared.
		bool clean();

	};  // end of class CURLWork

	typedef osl::RefPtr<CURLWork>  CURLWorkPtr;
	class HttpPostWork;
	class HttpPostFile;














	//-------------------------------------------------------------------
	//-------------------------------------------------------------------
	//-------------------------------------------------------------------
	inline void CURLWork::setUserData( void* pUserData )
	{
		m_pUserData = pUserData;
	}
	inline void* CURLWork::getUserData() const
	{
		return m_pUserData;
	}

	inline void CURLWork::setObjectUserData( osl::Object* pUserData )
	{
		m_ptrHObjectUserData = pUserData;
	}
	inline osl::Object* CURLWork::getObjectUserData() const
	{
		return m_ptrHObjectUserData;
	}

	inline bool CURLWork::isInitialized()
	{
		return m_bInitialized;
	}

	inline SOCKET 	CURLWork::getSocket() const
	{
		return m_URLInfo.sockfd;
	}
	inline void  	CURLWork::setSocket( SOCKET sock )
	{
		m_URLInfo.sockfd = sock;
	}

	inline void CURLWork::setHttpState( CURLWork::HttpConnState s )
	{
		m_URLInfo.state = s;
	}
	inline void CURLWork::setWorkThread( CURLWorkThread*  th )
	{
		m_URLInfo.pWorkTh = th;
	}
	inline CURLWorkThread* CURLWork::getWorkThread() const
	{
		return m_URLInfo.pWorkTh;
	}

// 	inline osl::MemoryDataStream* CURLWork::getRecvDataStream() const
// 	{
// 		return m_ptrRecvMDStream.getPointer();
// 	}
// 
// 	inline osl::MemoryDataStream* CURLWork::getRecvHeaderDataStream() const
// 	{
// 		return m_ptrRecvHeaderMDStream.getPointer();
// 	}
// 
// 	inline osl::MemoryDataStream* CURLWork::getURLDataStream()const
// 	{
// 		return m_ptrURLData.getPointer();
// 	}

	inline const char* CURLWork::getUrl() const
	{
		return m_URLInfo.url;
	}
	inline void	CURLWork::setUrl( const char* url )
	{
		m_URLInfo.url = url;
	}

	inline osl::u32 CURLWork::getWorkTotalCount()
	{
		return m_nTotalNo;
	}

	inline int CURLWork::getWorkNo() const
	{
		return m_nNo;
	}

	inline  void CURLWork::setTimeOut( int timeout )
	{
		m_timeout = timeout;    //! in seconds
	}
	inline int CURLWork::getTimeOut() const
	{
		return m_timeout;
	}

	inline bool CURLWork::isResponseWithHeader() const
	{
		return m_URLInfo.withheader;
	}

	inline void CURLWork::setResponseWithHeader( bool bWithHeader )
	{
		if ( bWithHeader )
		{
			m_URLInfo.withheader = 1L;
		}
		else
		{
			m_URLInfo.withheader = 0L;
		}
	}

	inline CURLWork::HttpConnState CURLWork::getHttpState() const
	{
		return m_URLInfo.state;
	}

	inline bool CURLWork::isCompressOK() const
	{
		return m_bCompressOperateResultFlag;
	}

	inline bool CURLWork::isUncompressOK() const
	{
		return m_bCompressOperateResultFlag;
	}

	inline void CURLWork::setHttpCode( long code )
	{
		m_nHttpCode = code;
	}

	inline long CURLWork::getHttpCode() const
	{
		return m_nHttpCode;
	}

}; // end of namespace net




#endif // end of #if H_PROVIDE_CURL



#endif
