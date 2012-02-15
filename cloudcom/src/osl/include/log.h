#ifndef _QOSLIB_LOG_H_
#define _QOSLIB_LOG_H_


#include "osl/include/inner_pre.h"
#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"

#if H_PROVIDE_LOG_SYSTEM


//#define H_LOG_SYSTEM_USE_LOG4CXX

#define H_EVENTLISTENER_HEADER(x)
#define H_NOTIFY_EVENTLISTENER_2(a,x,y,z)


namespace osl
{
    /** The importance of a logged message.*/
    enum LogMessageLevel
    {
        LML_TRACE = 0,    //!
        LML_DEBUG,        //! debug.
        LML_INFO,         //! Trivial information.
        LML_WARN,         //! General warning.
        LML_ERROR,        //! Error.
        LML_FATAL,        //! Fatal error.

        LML_NUM,
    };



    //! Log Item
    class _EXPORT_OSLIB Log : public Object
    {
	    friend	class	LogProcessThread;
        H_ALLOC_OBJECT( Log );
    public:

        //! Level supported by the log.
        enum Options
        {
            O_TRACE    = 1 << LML_TRACE,
            O_DEBUG    = 1 << LML_DEBUG,   //! debug

            O_INFO     = 1 << LML_INFO,   //! Information.
            O_WARN     = 1 << LML_WARN,   //! Warning
            O_ERROR    = 1 << LML_ERROR,
            O_FATAL    = 1 << LML_FATAL,   //! Fatal.

            O_STDOUT   = 1 << (LML_FATAL + 1),   //! Whether out put to standard out device
            O_TOFILE   = 1 << (LML_FATAL + 2),   //! Whether out put to local file.
            O_TOSERVER = 1 << (LML_FATAL + 3),   //! Whether out put to server.
        };


        // Event for log.
        enum Event
        {
            E_LOG,
        };

        //! Listener for the log.
        class Listener : public RefTarget
        {
        public:
            virtual void notify2( Event nEvent, Log* pLog, const osl::StringA& strOut, LogMessageLevel lml ) = 0;
            virtual void notify2( Event nEvent, Log* pLog, const osl::StringW& strOut, LogMessageLevel lml ) = 0;
        };

    public:

        //! Constructor.
        //! \param strName Log name.It is also log file name.
        //! \param nOptions Options control the log out put.
        //! \param strLogHost Log Host if want to out put information to log server.
        //! \param strLogPort Log Host service or port of log server.
        //!
        Log( const StringA& strName, u32 nOptions = O_TRACE | O_DEBUG | O_INFO | O_WARN | O_FATAL | O_STDOUT | O_TOFILE,
             const StringA& strLogHost = StringUtil::BLANKA, const StringA& strLogPort = StringUtil::BLANKA  );

        //!Destructor
        ~Log();


        //! Log a message to the debugger and to log file
        void logMessage( const StringA& message, LogMessageLevel lml );
        void logMessage( const char* message, size_t len, LogMessageLevel lml );
        void logMessage( const char* message, size_t len, LogMessageLevel lml, const char* filename, int lineno );

        //! Log a message to the debugger and to log file
        void logMessage( const StringW& message, LogMessageLevel lml );


        //! Query whether debug is enable.
        bool isDebugEnabled() const;

        //! Query whether information level is enabled
        bool isInfoEnabled() const;

        //! Query whether warning is enabled
        bool isWarnEnabled() const;

        //! Query whether error is enabled
        bool isErrorEnabled() const;

        //! Query fatal error is enabled
        bool isFatalEnabled() const;

        //! Query whether trace information is enabled
        bool isTraceEnabled() const;

        //! Query whether the log level of lml is enabled
        bool isLogEnabled( LogMessageLevel lml ) const;


        //! Gets log level name. "warning","error","trace","debug", "etc."
        static const char* getLevelName( LogMessageLevel nLML );

    private:
		void	doLogMessage( const StringA& message,	LogMessageLevel lml = LML_INFO );
		void	doLogMessage( const StringW& message,	LogMessageLevel lml = LML_INFO );

        class Impl;
        Impl                            *m_pImpl;

        static const char*  m_vLevelName[LML_NUM];


        H_EVENTLISTENER_HEADER( Listener );
    };

    typedef RefPtr<Log>   LogPtr;
};


#endif // #if H_PROVIDE_LOG_SYSTEM



#endif//endoffile

