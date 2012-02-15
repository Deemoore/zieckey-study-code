#ifndef _QNETWORKLIB_CURLSERVICE_H__
#define  _QNETWORKLIB_CURLSERVICE_H__

#if H_PROVIDE_CURL

#include "osl/include/assert_ext.h"
#include "osl/include/thread.h"

namespace net
{
	class 	CURLWork;
	class	CURLWorkListener;
	class	CURLWorkThread;


	/*! 
	*  @brief
	*		This is the CURLService class, a wrapper of libcurl.
	*/
	class _EXPORT_NET CURLService : public osl::Object
	{
		H_ALLOC_OBJECT( CURLService )
	public:

		//
		enum { MAX_NUM_THREADS = 32, };

	public:
#define SELECT_TIME_WAIT 100
		/**
		* @brief <b>Summary:</b>
		*	The constructor
		* @param[in] nNumThreads, the number of thread in thread-pool
		**********************************************************************/
		CURLService( int nNumThreads );
		~CURLService();

		//! Sets name for the work set. It should be invoked before start(...)
		void setName( const osl::StringA& strName );

		//! Gets workset name.
		const osl::StringA& getName()const
		{
			return m_strName;
		}

		//! \brief Initiate this CURLService session
		//! \return	return true if start successfully
		bool start();

		//! \brief Do clean work of this CURLService session
		void stop();

		//! Gets number of working thread.
		osl::u32 getNumWorkThread()const
		{
			return m_nNumThreads;
		}

		//! Add a work
		//! \return false if failed to add work.
		bool addWorkT( CURLWork* pWork );

		//! Query whether is initialize.
		bool isInitialized()const
		{
			return m_bInitialized;
		}

		////! Gets a new easy handle from the pool, after use it, just return it by call to recycleEasyHandleT.
		//void* newEasyHandleT();

		////! Recycle easy handle to the pool.
		//void recycleEasyHandleT( void* pHandle );

		void setCURLWorkListLength( osl::u32 nLength )
		{
			m_nCURLWorkListLength = nLength;
		}


		osl::u32 getCURLWorkListLength() const
		{
			return m_nCURLWorkListLength;
		}

	private:
		CURLWorkThread* getBestThread()
		{
			H_ASSERT( m_nNumThreads > 0 );
			static osl::u32 iThread = 0;
			return ( CURLWorkThread* )
				m_vWorkThread[ iThread++ % m_nNumThreads ].getPointer();
		}

	private:

		osl::ThreadPtr   m_vWorkThread[ MAX_NUM_THREADS ];

		int		                              m_nNumThreads;  //! the number os thread in the pool
		bool                               	 m_bInitialized;  //! whether is Initialized


		osl::StringA                            m_strName;   //! name of the work-set.

		osl::u32                    m_nCURLWorkListLength;


	private:
		//! Hide default constructor
		CURLService();
		CURLService( const CURLService& );
	};

	typedef osl::RefPtr<CURLService>  CURLServicePtr;
}; // end of namespace net


#endif // end of #if H_PROVIDE_CURL


#endif // end of #ifdef _QNETWORKLIB_CURLSERVICE_H__


