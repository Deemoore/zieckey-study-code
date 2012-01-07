#ifndef _QOSLIB_LOGMANAGER_
#define _QOSLIB_LOGMANAGER_



#if H_PROVIDE_LOG_SYSTEM




#include "osl/include/singleton.h"
#include "osl/include/QLog.h"

namespace osl
{



    /** The log manager handles the creation and retrieval of logs for the
    *    application.
    *  @note The instance will be created automatically by the module.
    */
#define s_pLogManager	( ::osl::LogManager::getSingletonPtr() )
    class _EXPORT_OSLIB LogManager : public Singleton<LogManager>
    {
		friend class Log;
		//friend class LogProcessThread;
        H_ALLOCRAW_OPERATORS( LogManager );
    public:
        H_DEF_MAP( String, LogPtr, LogMap );

        // shared by all test log.
        static int test_verify_point_index;
    public:
        LogManager();
        ~LogManager();

        //! Creates a new log with the given name.
        //! \param strName Log name.It is also log file name.
        //! \param nOptions Options control the log out put.
        //! \param strLogHost Log Host if want to out put information to log server.
        //! \param strLogPort Log Host service or port of log server.
        //!
        Log* createLog( const StringA& name,  u32 nOptions = Log::O_DEBUG | Log::O_INFO | Log::O_WARN | Log::O_FATAL | Log::O_STDOUT | Log::O_TOFILE,
                        const StringA& strLogHost = StringUtil::BLANKA, const StringA& strLogPort = StringUtil::BLANKA );

        /** Get named log.
        *  @return NULL if the log with the name does not exist.
        */
        Log* getLog( const StringA& strName );

        /** Returns a pointer to the default log.*/
        Log* getDefaultLog();

		//! Sets whether set all to stdout.
		void setAllStdOut( bool bAllStdOut );
		
		//! Query whether all log output to stdout
		bool isAllStdOut()const
		{
			return m_bAllStdOut;
		}
		
    protected:
		class LogProcessThread* getLogProcessThread()
		{
			return  m_pLogProcessThread;
		}

        LogMap m_mapLog;

		class LogProcessThread* m_pLogProcessThread;

        /// The default log to which output is done
        Log* m_pDefaultLog;

		bool      m_bAllStdOut;  //! whether all log is out put to std out. default is false.
    };

};//namespace

#endif // #if H_PROVIDE_LOG_SYSTEM





//! Logs a message to a specified logger with a specified level.
//! \param logger the logger to be used.
//! \param level the level to log.
//! \param message the message string to log.
//!
#define H_LOG(logger, level, message) {													 \
    osl::Log* pLog_998866_ = (logger);												 \
    if( (logger) == NULL ) pLog_998866_ = osl::LogManager::getSingletonPtr()->getDefaultLog(); \
    if( pLog_998866_ ) pLog_998866_->logMessage( (message), (level) ); }

#define H_LOG_NAME( logName, level, message) {	\
    osl::StringA logName_99886666_ = (logName);												 \
    osl::Log* pLog_99888866_ = osl::LogManager::getSingletonPtr()->getLog( logName_99886666_ ); \
    if( pLog_99888866_ ) pLog_99888866_->logMessage( (message), (level) ); }




//! Log message with debug level.
#ifdef H_DEBUG_MODE
#	define H_LOG_DEBUG( logger, message )  H_LOG( (logger), osl::LML_DEBUG, message )
#else
#	define H_LOG_DEBUG( logger, message )
#endif

//! Log message with Trace level.
#define H_LOG_TRACE( logger, message )  H_LOG( (logger), osl::LML_TRACE, message )

//! Log message with Trace level.
#define H_LOG_INFO( logger, message )   H_LOG( (logger), osl::LML_INFO, message )

//! Log message with Trace level.
#define H_LOG_WARN( logger, message )   H_LOG( (logger), osl::LML_WARN, message )

//! Log message with Trace level.
#define H_LOG_ERROR( logger, message )  H_LOG( (logger), osl::LML_ERROR, message )

//! Log message with Trace level.
#define H_LOG_FATAL( logger, message )  H_LOG( (logger), osl::LML_FATAL, message )



//-----------------------
#ifdef H_DEBUG_MODE
#	define H_LOG_NAME_DEBUG( strName, message )  H_LOG_NAME( (strName), osl::LML_DEBUG, message )
#else
#	define H_LOG_NAME_DEBUG( strName, message )
#endif

//! Log message with Trace level.
#define H_LOG_NAME_TRACE( strName, message )  H_LOG_NAME( (strName), osl::LML_TRACE, message )

//! Log message with Trace level.
#define H_LOG_NAME_INFO( strName, message )   H_LOG_NAME( (strName), osl::LML_INFO, message )

//! Log message with Trace level.
#define H_LOG_NAME_WARN( strName, message )   H_LOG_NAME( (strName), osl::LML_WARN, message )

//! Log message with Trace level.
#define H_LOG_NAME_ERROR( strName, message )  H_LOG_NAME( (strName), osl::LML_ERROR, message )

//! Log message with Trace level.
#define H_LOG_NAME_FATAL( strName, message )  H_LOG_NAME( (strName), osl::LML_FATAL, message )

//-------------------------------------------------
//! Logs a message to record the testing verify point.
//! \param name, string, the log name, we usually use Common::VERIFY_JUMP...
//! \param isPass, bool, whether this point is pass
//! \param message, string, the message
#define H_LOG_TEST( name, isPass, message ) {								\
    osl::StringStreamA __msg_887645523;									\
    __msg_887645523 << " "<< (osl::LogManager::test_verify_point_index++) << " " << ( isPass ? "pass" : "failed" ) << "- " << message;	\
    if ( isPass ) { \
    H_LOG_NAME_WARN( name, __msg_887645523.str() );			\
    } else { H_LOG_NAME_ERROR( name, __msg_887645523.str() ); } }








#endif//endoffile




// if assert is enabled.
// #ifdef H_DEBUG_MODE
// 
// #define H_RETURN_IF( exp )
// #define H_RETURN_VALUE_IF( exp, value )
// #define H_RETURN_LOG_IF( exp, logmsg )
// #define H_RETURN_VALUE_LOG_IF( exp, logmsg )
// 
// #define H_CONTINUE_IF( exp )
// #define H_CONTINUE_LOG_IF( exp, logmsg )
// 
// #define H_BREAK_IF( exp ) {if(exp) break;}
// #define H_BREAK_LOG_IF( exp, logmsg )
// 
// #else

// #define H_RETURN_IF( exp ) {if((exp)) return;}
// #define H_RETURN_VALUE_IF( exp, value ) {if(exp) return value;}
// #define H_RETURN_LOG_IF( exp, logmsg ) {if(exp){H_LOG_NAME_INFO("H_RETURN_LOG_IF", logmsg); return;} }
// #define H_RETURN_VALUE_LOG_IF( exp, logmsg ) {if(exp){H_LOG_NAME_INFO("H_RETURN_VALUE_LOG_IF", logmsg); return value;} }

// #define H_CONTINUE_IF( exp ) {if(exp) continue;}
// #define H_CONTINUE_LOG_IF( exp, logmsg ) {if(exp){H_LOG_NAME_INFO("H_CONTINUE_LOG_IF", logmsg); continue;} }
// 
// #define H_BREAK_IF( exp ) {if(exp) break;}
// #define H_BREAK_LOG_IF( exp, logmsg ) {if(exp){H_LOG_NAME_INFO("H_BREAK_LOG_IF", logmsg); break;} }


/*#endif*/





#include "osl/include/QLogManager.inl.h"






