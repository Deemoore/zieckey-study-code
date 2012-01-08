#ifndef _QOSLIB_LOG_NTIMPL_H_
#define _QOSLIB_LOG_NTIMPL_H_



#if H_PROVIDE_LOG_SYSTEM



#include <iosfwd>
#include <fstream>
#include <iostream>

#include "osl/include/QLogManager.h"
#include "osl/include/process_ext.h"
#include "osl/include/QFileUtil.h"

namespace osl
{

    //! Log implementation.
    class Log::Impl
    {
    public:

        //! Constructor.
        //! \param strName Log name.It is also log file name.
        //! \param nOptions
        //!
        Impl( const StringA& strName, u32 nOptions,
              const StringA& strLogHost,
              const StringA& strLogPort  )
            : m_strName(strName), m_nOptions( nOptions )
        {
            m_strLogFile = getLogDir() + StringA("/") + m_strName + ".log";

            m_vEnable[LML_DEBUG] = H_FLAG_ISSET( m_nOptions, Log::O_DEBUG );
            m_vEnable[LML_TRACE] = H_FLAG_ISSET( m_nOptions, Log::O_TRACE );
            m_vEnable[LML_INFO]  = H_FLAG_ISSET( m_nOptions, Log::O_INFO  );
            m_vEnable[LML_WARN]  = H_FLAG_ISSET( m_nOptions, Log::O_WARN  );
            m_vEnable[LML_ERROR] = H_FLAG_ISSET( m_nOptions, Log::O_ERROR );
            m_vEnable[LML_FATAL] = H_FLAG_ISSET( m_nOptions, Log::O_FATAL );

            if ( H_FLAG_ISSET( m_nOptions, Log::O_TOFILE ) )
            {
                m_fileStream.open( m_strLogFile.c_str(),
                                   std::ios_base::binary | std::ios_base::out | std::ios_base::app );

                if ( !m_fileStream )
                {
                    fprintf( stderr, "cannot open file %s to write log\n", m_strLogFile.c_str() );
                }
                //char bom[2] = { char(0xff), char(0xfe)};
                //m_fileStream.write( bom, 2 );

                // header.
                /*
                {
                    String strTip =
                        "\n***************************************\n"
                        "                Qihoo Log             \n"
                        " Please address it to Qihoo ltd.     \n"
                        " email: weizili@360.cn           \n"
                        "***************************************";

                    m_fileStream.write( strTip.c_str(), strTip.size() * sizeof( String::value_type ) );
                }
                */
            }
        }
        //----------------------------------------------
        ~Impl()
        {

        }
        //----------------------------------------------
        StringA getLogDir()
        {
            StringA logdir = Process::getBinDir( false ) + "/../logs";
            if ( FileUtil::isFSFileExist(logdir) )
            {
                return logdir;
            }

            logdir = Process::getBinDir( false ) + "/../log";
            if ( FileUtil::isFSFileExist(m_strLogFile) )
            {
                return logdir;
            }

            logdir = Process::getBinDir( false ) + "/log";
            if ( FileUtil::isFSFileExist(m_strLogFile) )
            {
                return logdir;
            }

            logdir = Process::getBinDir( false ) + "/logs";
            if ( FileUtil::isFSFileExist(m_strLogFile) )
            {
                return logdir;
            }

            logdir = Process::getBinDir( false ) + "/log";
            if ( !FileUtil::makeFSDir( logdir ) )
            {
                fprintf( stderr, "mkdir failed : %s\n", logdir.c_str() );
                return Process::getBinDir( false );
            }

            return logdir;
        }

        //----------------------------------------------
        void logMessage( const char* message, size_t len, LogMessageLevel lml, const char* filename = NULL, int lineno = -1 )
        {
            if ( !m_vEnable[lml] )
            {
                return;
            }

            /// Time And Level
            StringA::value_type szTime[1024];
            {
                struct tm *pTime;
                time_t ctTime;
                time( &ctTime );
                pTime = localtime( &ctTime );

                memset( szTime, 0, sizeof( szTime ) );

                snprintf( szTime, sizeof(szTime), "%4d/%.2d/%.2d %.2d:%.2d:%.2d %s - ", 
                    pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday,
                    pTime->tm_hour, pTime->tm_min, pTime->tm_sec, Log::getLevelName( lml ) );
            }


            // show in debug output window
            if ( H_FLAG_ISSET( m_nOptions, Log::O_DEBUG ) || s_pLogManager->isAllStdOut() )
            {
                // to console.
                std::cout << szTime << m_strName.c_str() << " - ";
                if ( filename && lineno >= 0 ) 
                {
                    std::cout << filename << ":" << lineno << " - ";
                }
                std::cout << message << std::endl;
                std::cout.flush();
            }

            // Write time into log
            if ( H_FLAG_ISSET( m_nOptions, Log::O_TOFILE ) )
            {
                /// Time
                {
                    m_fileStream.write( szTime, ( std::streamsize )strlen( szTime ) * sizeof( StringA::value_type ) );
                    checkerror();
                }

                ///file name and line number
                {
                    if ( filename )
                    {
                        m_fileStream.write( filename, ( std::streamsize )strlen( filename ) );
                        checkerror();
                        m_fileStream.write( ":", 1 );
                        checkerror();
                    }

                    if ( lineno >= 0 )
                    {
                        m_fileStream << lineno;
                        checkerror();
                        m_fileStream.write( " - ", sizeof(" - ") - 1 );
                        checkerror();
                    }
                }

                /// Message
                if ( len )
                {
                    m_fileStream.write( message, ( std::streamsize )( len * sizeof( StringA::value_type ) ) );
                    checkerror();
                }

                m_fileStream << std::endl;
                //checkerror();


                // Flush iostream to ensure it is written (in case of a crash, we need log to be up to date)
                /*if ( m_fileStream.flush().bad() )
                  {
                  m_fileStream.close();

                  m_fileStream.open( m_strLogFile.c_str(),
                  std::ios_base::binary | std::ios_base::out | std::ios_base::app );
                  }*/
            }

            // onSocketEventT log listeners
            //H_NOTIFY_LISTENER_2( LogListener, lml, message )
        }
        //----------------------------------------------
        void logMessage( const StringA& message, LogMessageLevel lml )
        {
            logMessage( message.c_str(), message.length(), lml );
        }
        //----------------------------------------------
        void logMessage( const StringW& message, LogMessageLevel lml )
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

        //! Check the fstream error state, if it is in a bad state we will close it and reopen it.
        void checkerror()
        {
            if ( m_fileStream.bad() || !m_fileStream.good() )
            {
                m_fileStream.close();
                m_fileStream.open( m_strLogFile.c_str(),
                            std::ios_base::binary | std::ios_base::out | std::ios_base::app );
            }
        }
    private:
        std::ofstream	m_fileStream;	//! file stream to receive log.
        StringA		  	   m_strName;	//! Log
        StringA         m_strLogFile;   //! log file name
        u32               m_nOptions;   //! Options
        bool       m_vEnable[LML_NUM];
    };
};


#endif // #if H_PROVIDE_LOG_SYSTEM



#endif// #ifndef _QOSLIB_LOG_NTIMPL_H_


