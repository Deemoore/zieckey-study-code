#ifndef _QNETWORKLIB_HTTPPOSTWORK_H__
#define _QNETWORKLIB_HTTPPOSTWORK_H__



#if H_PROVIDE_CURL




namespace net
{

	//! Http Post request work. CURLOPT_POST. CURLOPT_HTTPPOST
	//! \par all parameter pair is packed in PostFields stream. m_ptrSendMDStream.
	//! \par  Parameter pairs packed in post form fields. correspond to curl CURLFORM_COPYNAME --- key, CURLFORM_COPYCONTENTS -- value,
	//! \par  Data to send is sent as binary data. corresponds to curl :
	//! \code CURLFORM_COPYNAME, "name",	CURLFORM_BUFFER, "data"
	//!       , CURLFORM_BUFFERPTR  , ( char* )m_ptrSendMDStream->getCache()
	//!       ,	CURLFORM_BUFFERLENGTH, ( long )m_ptrSendMDStream->getSize(),
	class _EXPORT_NET HttpPostFile : public CURLWork
	{
		H_ALLOC_OBJECT( HttpPostFile );
	public:

		//! Send data item.
		struct SendDataItem
		{
            //Content-Disposition: form-data; name="file"; filename="ntuser.ini"
			osl::StringA               name;  // the 'name' field
			osl::StringA           filename;  // the 'filename' field
			osl::MemoryDataStreamPtr  pData;
		};
		H_DEF_LIST(SendDataItem, SendDataItemList);

	public:

		/**
		* @brief <b>Summary:</b>
		*		The constructor. When you new(ed) a work, you need call
		*	CURLService->addWorkT() to bind this work to a process CURLService
		*	which does the actual job. And you needn't worry about this work's
		*	memory delete jobs, because the CURLService will handle it.
		* @note This class is only used for file upload. Upload parameter MUST be called after constructed.
		* @param[in] url, the url, we duplicate it
		*	eg1:"http://192.168.0.40/filewebserver/post.php"
		* @param[in] timeout, is an upper bound on the amount of time elapsed
		*	before the work is done(success or fail), seconds.
		* @return
		**********************************************************************/
		HttpPostFile( const osl::StringA& url, int timeout = HTTP_TIMEOUT );


		/** File upload work.
		* @param pURLData URL data stream. It will be take over by the object, caller MUST NOT modify it later.
		*/
		HttpPostFile( osl::MemoryDataStream* pURLData, int timeout = HTTP_TIMEOUT );

        //! \brief <b>Summary:</b>
        //!     Add parameter to this post. The parameter can be binary data
        //!     like key="username" , value="qihoo"
        //!     like key="password" , value="123456"
        //! \note If add the same more than one time,
        //!       the new key-value will be append as new key-value(s), NOT override the old key-value.
        //! \param[in] key, the name of the parameter
        //! \param[in] value, the value
        //! \return true, if add successfully
        //!	    false, if add failed
        bool addParameter( const char* key, const void* value, const size_t valuelen );


        //! \brief <b>Summary:</b>
        //!		Set the send data memory buffer instead of sending local file.
        //!	\remark Add data as default file name with "name" and data name "filename". 
        //! \code 
        //!     <code> 
        //!     ::curl_formadd( &m_formpost,
        //!                     &m_lastformpost,
        //!                     CURLFORM_COPYNAME, strNameField.c_str(),
        //!                     CURLFORM_BUFFER, strFileNameField.c_str(),
        //!                     CURLFORM_BUFFERPTR, ( char* )psds->getCache(),
        //!                     CURLFORM_BUFFERLENGTH, ( long )psds->getSize(),
        //!                     CURLFORM_END );
        //!     <code/>
        //!     This LIBCURL code will send a HTTP body content:
        //!             Content-Disposition: form-data; name="file"; filename="filename"
        //!             Content-Type: application/octet-stream
        //! \param[in] psds, the pointer which holds the data
        //! \return MemoryDataStream pointer, point to data which need to server
		void addSendDataItem( const osl::StringA& strNameField, const osl::StringA& strFileNameField, osl::MemoryDataStream* psds );
        void addSendDataItem( const char* strNameField, const char* strFileNameField, osl::MemoryDataStream* psds );


		//! \brief <b>Summary:</b>
		//!		Set the send data memory buffer instead of sending local file.
		//!	\remark Add data as default file name with "name" and data name "filename". 
        //! The same to call <code>addSendDataItem( "name", "filename", psds );<code/>
		void addSendDataItem( osl::MemoryDataStream* psds );


		//! Sets send data item list. The previous data list will be replaced.
		//! \remark The method CAN ONLY be called before work started.
		void setSendDataItemList( const SendDataItemList& vData )
		{
			m_vSendDatas =vData;
		}

		//! Gets send data item list.
		const SendDataItemList& getSendDataItemList()const
		{
			return m_vSendDatas;
		}

	protected:
		SendDataItemList                 m_vSendDatas; //!hold the send data

	protected:
		/**
		* @brief <b>Summary:</b>
		*	Initiate a CURL session to process this work.
		* @return	0, if success. <br>
		*			-1, if failed.
		*****************************************************************/
		virtual bool	init( CURLWorkThread* pThread );

	};

	typedef osl::RefPtr<HttpPostFile>  HttpPostFilePtr;

};//namespace



#endif // end of #if H_PROVIDE_CURL


#endif // end of #ifdef _QNETWORKLIB_HTTPPOSTWORK_H__


