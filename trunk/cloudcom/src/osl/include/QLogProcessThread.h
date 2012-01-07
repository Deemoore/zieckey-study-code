#ifndef	H_LOG_PROCESS_THREAD_H
#define	H_LOG_PROCESS_THREAD_H


#if H_PROVIDE_LOG_SYSTEM



//#define H_USING_THREAD_TO_WRITE_LOG




#if H_USING_THREAD_TO_WRITE_LOG
    #if !H_PROVIDE_THREAD_EVENT_LOCK
        #error "The log system depend on osl::Thread, please recompile osl with H_PROVIDE_THREAD_EVENT_LOCK flag on, H_PROVIDE_THREAD_EVENT_LOCK is difined in libcommon/src/osl/include/osl_config.h"
    #endif
#endif

#include "osl/include/QThread.h"
#include "osl/include/QEvent.h"
#include "osl/include/QMyOS.h"
#include "osl/include/QLock.h"
#include "osl/include/QString.h"
#include "osl/include/QStringUtil.h"

namespace osl
{
	class  CLogItem
	{
	friend class Log;
		H_ALLOCRAW_OPERATORS(CLogItem);
	public:
		//		CLogItem(){};
		~CLogItem(){ m_pLog = NULL; };
		CLogItem(Log* log, const StringA& strMsg, LogMessageLevel lvl):m_pLog(log),m_strMsg(strMsg),m_eLvl(lvl){};
		//CLogItem(Log* log, const StringW strMsg, LogMessageLevel lvl):m_pLog(log),m_strMsg(strMsg),m_eLvl(lvl){};

		Log* m_pLog;	
		StringA m_strMsg;	
		//StringW m_strMsgW;

		//union msg m_strMsg;		
		LogMessageLevel m_eLvl; 

	};

	class LogProcessThread : public Thread
	{
	friend class Log;
	public:
		H_DEF_LIST(CLogItem*,LogItemList);
		LogProcessThread( void );

		virtual ~LogProcessThread( void );

		bool start();
		void stop();
		bool isInitialized() const
		{
			return m_bInitialized;
		}

    private:
        //void wake();
        int init();
        void doLogMessages();
		void pushLogItem( Log* log, const StringA& message, LogMessageLevel lml= LML_INFO );
		void pushLogItem( Log* log, const StringW& message,	LogMessageLevel lml = LML_INFO );
		//osl::MiniLock* getLock()
		//{
		//	return &m_listLogItemLock;
		//}
		//LogItemList* getLogItemList()
		//{
		//	return &m_listLogItem;
		//}

        //! override from Thread
        virtual void run();

		LogItemList   m_listLogItemToBeProcessed;

		osl::MiniLock	  m_listLogItemLock;
		osl::Event	m_eventWait;
		bool			m_bInitialized;
		bool			m_bIsProcessing;
		LogItemList     m_listLogItemBeingProcessed;
	};

};


#endif // #if H_PROVIDE_LOG_SYSTEM



#endif //	H_LOG_PROCESS_THREAD_H

