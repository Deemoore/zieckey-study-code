#ifndef _H_LOG_LINUXIMPL_
#define _H_LOG_LINUXIMPL_


#if H_PROVIDE_LOG_SYSTEM



//#ifdef H_OS_LINUX

#include <fstream>
#include <log4cxx/logger.h>
#include <log4cxx/logmanager.h>
//#include <log4cxx/basicconfigurator.h>
//#include <log4cxx/helpers/exception.h>
//#include <log4cxx/propertyconfigurator.h>
//using namespace log4cxx;

namespace osl
{

    //! Log implemention.
    class Log::Impl
    {
    public:

        //! Constructor.
        //! \param strName Log name.It is also log file name.
        //! \param nOptions
        //!
        Impl( const StringA& strName, u32 nOptions,
              const StringA& strLogHost, const StringA& strLogPort  )
            : m_nOptions( nOptions ),m_strName(strName), m_pLog4cxx( ( log4cxx::Logger* )0 )
        {
            m_pLog4cxx = log4cxx::LogManager::getLogger( strName.c_str() );

            if ( !m_pLog4cxx )
            {
                m_pLog4cxx = log4cxx::LogManager::getRootLogger();
            }

            if ( !m_pLog4cxx )
            {
                m_vEnable[LML_DEBUG] = H_FLAG_ISSET( m_nOptions, Log::O_DEBUG );
                m_vEnable[LML_TRACE] = H_FLAG_ISSET( m_nOptions, Log::O_TRACE );
                m_vEnable[LML_INFO]  = H_FLAG_ISSET( m_nOptions, Log::O_INFO  );
                m_vEnable[LML_WARN]  = H_FLAG_ISSET( m_nOptions, Log::O_WARN  );
                m_vEnable[LML_ERROR] = H_FLAG_ISSET( m_nOptions, Log::O_ERROR );
                m_vEnable[LML_FATAL] = H_FLAG_ISSET( m_nOptions, Log::O_FATAL );

                if ( H_FLAG_ISSET( m_nOptions, Log::O_TOFILE ) )
                {
                    m_fileStream.open( ( m_strName + ".log" ).c_str(),
                                       std::ios_base::binary | std::ios_base::out | std::ios_base::trunc );

                    const unsigned char bom[2] = { 0xff , 0xfe };
                    m_fileStream.write( reinterpret_cast<const char*>( bom ), 2 );

                    // header.
                    {
                        String strTip =
                            "***************************************\r\n"
                            "                Qihoo Log             \r\n"
                            " Please address it to Qihoo ltd.     \r\n"
                            " email: weizili@360.cn           \r\n"
                            "***************************************";

                        m_fileStream.write( strTip.c_str(), strTip.size() * sizeof( String::value_type ) );
                    }
                }
            }

        }
        //----------------------------------------------
        ~Impl()
        {

        }
        //----------------------------------------------
        void logMessage( const StringA& message, LogMessageLevel lml )
        {
            logMessage( message.c_str(), message.length, lml, NULL, 0 );
        }
        void logMessage( const char* message, size_t len, LogMessageLevel lml, const char* filename = NULL, int lineno )
        {
            if ( m_pLog4cxx )
            {
                switch ( lml )
                {
                    case LML_DEBUG:
                        m_pLog4cxx->debug( message );
                        break;
                    case LML_TRACE:
                        m_pLog4cxx->trace( message );
                        break;
                    case LML_INFO:
                        m_pLog4cxx->info( message );
                        break;
                    case LML_WARN:
                        m_pLog4cxx->warn( message );
                        break;
                    case LML_ERROR:
                        m_pLog4cxx->error( message );
                        break;
                    case LML_FATAL:
                        m_pLog4cxx->fatal( message );
                        break;
                    default:
                        break;
                }

                return;
            }

            /*
            if ( !m_vEnable[lml] )
            {
                return;
            }

            /// Time
            String::value_type szTime[256];
            {
                struct tm *pTime;
                time_t ctTime;
                time( &ctTime );
                pTime = localtime( &ctTime );

                memset( szTime, 0, sizeof( szTime ) );
                sprintf( szTime, ( "\r\n%2d:%2d:%2d:  %s :" ),
                         pTime->tm_hour, pTime->tm_min, pTime->tm_sec,
                         Log::getLevelName( lml ) );
            }

            // show in debug output window
            if ( H_FLAG_ISSET( m_nOptions, Log::O_DEBUG )  || s_pLogManager->isAllStdOut() )
            {
				printf( szTime );
				puts( message );
				fflush( stdout );
                //std::cout << szTime << message << std::endl;
                //std::cout.flush();
            }

            // Write time into log
            if ( H_FLAG_ISSET( m_nOptions, Log::O_TOFILE ) )
            {
                /// Time
                {
                    m_fileStream.write( ( char* )szTime, ( std::streamsize )strlen( szTime ) * sizeof( String::value_type ) );
                }

                /// Message
                if ( message.size() )
                {
                    m_fileStream.write( message.c_str(), ( std::streamsize )message.length() * sizeof( String::value_type ) );
                }


                // Flush stcmdream to ensure it is written (incase of a crash, we need log to be up to date)
                if ( m_fileStream.flush().bad() )
                {
                    m_fileStream.close();
                }
            }

            // onSocketEventT log listeners
            //H_NOTIFY_LISTENER_2( LogListener, lml, message )
            */
        }
        //----------------------------------------------
        void logMessage( const StringW& message,	LogMessageLevel lml )
        {
            logMessage( StringUtil::wsToMbs( message ), lml );
        }
        //----------------------------------------------
        bool isDebugEnabled() const
        {
            return H_FLAG_ISSET( m_nOptions, Log::O_DEBUG );
        }
        //----------------------------------------------
        bool isInfoEnabled() const
        {
            return H_FLAG_ISSET( m_nOptions, Log::O_INFO );
        }

        //! Query whether warning is enabled.
        bool isWarnEnabled() const
        {
            return H_FLAG_ISSET( m_nOptions, Log::O_WARN );
        }

        //! Query whether error is enabled,
        bool isErrorEnabled() const
        {
            return H_FLAG_ISSET( m_nOptions, Log::O_ERROR );
        }

        //! Query fatal error is enabled,
        bool isFatalEnabled() const
        {
            return H_FLAG_ISSET( m_nOptions, Log::O_FATAL );
        }

        //! Query whether trace information is enabled,
        bool isTraceEnabled() const
        {
            return H_FLAG_ISSET( m_nOptions, Log::O_TRACE );
        }

        //! Query whether the log level of lml is enabled
        bool isLogEnabled( Log::Options leveloption ) const
        {
            return H_FLAG_ISSET( m_nOptions, leveloption );
        }

    private:
        std::ofstream	m_fileStream;	//! file stream to receive log.
        u32               m_nOptions;   //! Options
        String		  	   m_strName;	//! Log and log file name

        bool       m_vEnable[LML_NUM];

        log4cxx::LoggerPtr    m_pLog4cxx;
    };
};


#endif // #if H_PROVIDE_LOG_SYSTEM



//#endif// if define H_OS_LINUX
#endif//endoffile
