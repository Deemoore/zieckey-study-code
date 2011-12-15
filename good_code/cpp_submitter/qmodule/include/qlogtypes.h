#ifndef _QLOG_TYPES_H_
#define _QLOG_TYPES_H_

#ifdef __cplusplus

#include <cerrno>
#include <cstring>
#include <string>
#include <sstream>
#include <stdexcept>

namespace QPub
{
    /**
     * level枚举，用于日志配置
     */
    enum QLEVEL
    {
        ALL   = 0,
        TRACE = 0,
        DEBUG = 10000,
        INFO  = 20000,
        WARN  = 30000,
        ERR   = 40000,
#ifndef _WIN32
		ERROR = 40000,
#endif
        FATAL = 50000,
        OFF   = 60000
    };

//UNICODE支持
#ifdef UNICODE
    typedef std::wstring qstring;
    typedef std::wostream qostream;
    typedef std::wostringstream qostringstream;
    #define QTEXT(STRING) L##STRING
#else
    typedef std::string qstring;
    typedef std::ostream qostream;
    typedef std::ostringstream qostringstream;
    #define QTEXT(STRING) STRING
#endif // UNICODE

} //namespace QPub


#ifndef USE_STDOUT

#ifdef _WIN32
#  ifdef LOG4CPLUS_STATIC
#    define QLOG_EXPORT
#  else
#    ifdef LOG4CPLUS_BUILD_DLL
#      define QLOG_EXPORT __declspec(dllexport)
#    else
#      define QLOG_EXPORT __declspec(dllimport)
#    endif
#  endif
#else
#  define QLOG_EXPORT
#endif

//使用qlog库
namespace QPub
{
    /**
     * 判断日志是否记录
     *
     * @param name     日志类别
     * @param level    日志级别
	 *
	 * @return true: 记录日志
     */
	QLOG_EXPORT bool isLog(const qstring& name, int level);

    QLOG_EXPORT void qLogInternalDebug(bool isDebug);
    //用于支持变参格式化输出
#ifdef _WIN32
	QLOG_EXPORT void qLogAll(const qstring& name, int level, int eNo, bool bThrow, const char* file, int line, const char* fmt,...);
#else
    void qLogAll(const qstring& name, int level, int eNo, bool bThrow, const char* file, int line, const char* fmt,...)
		__attribute__ ((format (printf, 7, 8)));
#endif
    //用于支持流式输出
    QLOG_EXPORT void qLogAllStream(const qstring& name, int level, const qstring& message, const char* file, int line);

#if defined(_MSC_VER)
	#pragma warning( push )
	#pragma warning( disable : 4996 )
#endif

	/**
	 * qlog的stream接口
	 */
    class QLOG_EXPORT logstream : public qostringstream
	{
	public:
        logstream(const qstring& name, int level, int eNo, const char* file, int line)
		 : m_name(name), m_level(level), m_eNo(eNo), m_file(file), m_line(line) {}

		logstream& l_value() { return *this; }

		~logstream()
		{
			if( isLog(m_name, m_level) )
			{
				logstream& _s = *this;
				if ( m_eNo != 0 )
					_s << QTEXT(" -- (") << m_eNo << QTEXT(')') << strerror(m_eNo);
				qLogAllStream(m_name, m_level, _s.str(), m_file, m_line);
			}
		}

	private:
		qstring m_name;
		int m_level;
		int m_eNo;
		const char* m_file;
		int m_line;
		logstream( const logstream& );
		logstream& operator=( const logstream& );
	};
#if defined(_MSC_VER)
	#pragma warning( pop )
#endif

}

    #define qLogAndThrows(name, level, eNo, logStream) \
        do \
		{ \
            int m_eNo = eNo; \
            QPub::qostringstream _qbuf; \
            _qbuf << logStream; \
			if ( m_eNo != 0 ) \
                _qbuf << QTEXT(" -- (") << m_eNo << QTEXT(')') << strerror(m_eNo); \
			if ( QPub::isLog(name, level) ) \
               	QPub::qLogAllStream(name, level, _qbuf.str(), __FILE__, __LINE__); \
			throw std::runtime_error(_qbuf.str()); \
        } while(0)

#else
// -DUSE_STDOUT

//不使用qlog库
#include    <stdlib.h>
#include    <stdio.h>
#include    <ctype.h>
namespace QPub
{

    //#define qLogConfig(args...);
	inline void qLogConfig( const qstring& configfile ) {}

    inline void qLogQuickConfig ( QLEVEL level=INFO, const qstring& filename=QTEXT("CONSOLE") )
   	{
        char szEnv[64];
        sprintf ( szEnv, "%d", level );
        setenv ( "QLOG_LEVEL", szEnv, 1 );
    }

    inline void qLogViewConfig() {}

    inline void qLogCleanConfig() {}

	inline bool isLog(const qstring& name, int level)
	{
		int iLevelEnv = INFO;
		char* pszEnv = getenv ( "QLOG_LEVEL" );
		if ( pszEnv != NULL )
			iLevelEnv = atoi( pszEnv );
		if ( level < iLevelEnv )
			return false;
		return true;
	}

    class qLogMonitor
    {
    public:
        qLogMonitor(const qstring& filename, unsigned int millis = 60 * 1000) {};
        ~qLogMonitor() {};

    private:
        // Disable copy
        qLogMonitor(const qLogMonitor&);
        qLogMonitor& operator=(qLogMonitor&);
        void* handle;
    };

	inline void qLogInternalDebug(bool isDebug) {}

	inline const qstring qLevelStr(int level) {
        switch ( level )
        {
        case TRACE:   return "TRACE";
        case DEBUG:   return "DEBUG";
        case INFO:    return "INFO ";
        case WARN:    return "WARN ";
        case ERR:     return "ERROR";
        case FATAL:   return "FATAL";
        case OFF:     return "OFF  ";
        };
        return qstring();
    }

    #include <stdarg.h>
    #define QLOG_MAX     10240
	#ifdef _WIN32
		#define snprintf _snprintf
	#endif
    //freebsd4.11环境，变参宏定义体在无args时不支持函数作为参数，所以用此函数处理
    inline void qLogAll(const qstring& name, int level, int eNo, bool bThrow, const char* file, int line, const char* fmt,...)
    {
        if ( fmt == NULL )
            return;

		bool bLog = isLog(name, level);
		if ( bLog || bThrow )
		{
        	char LogBuf[QLOG_MAX];
        	int cnt = 0;
        	//1.name
        	cnt += snprintf( LogBuf + cnt, QLOG_MAX - cnt, "[%s] ", name.c_str() );
        	if ( cnt >= QLOG_MAX )
			   cnt = QLOG_MAX - 1;
        	//2.level
        	cnt += snprintf( LogBuf + cnt, QLOG_MAX - cnt, "[%s] ", qLevelStr(level).c_str() );
        	if ( cnt >= QLOG_MAX )
			   cnt = QLOG_MAX - 1;
        	//3.file
        	if ( file != NULL )
        	{
            	cnt += snprintf( LogBuf + cnt, QLOG_MAX - cnt, "[%s:%d] ", file, line );
            	if ( cnt >= QLOG_MAX )
				   cnt = QLOG_MAX - 1;
        	}
        	//4.message
        	va_list ap;
        	va_start(ap,fmt);
        	cnt += vsnprintf( LogBuf + cnt, QLOG_MAX - cnt, fmt, ap );
			va_end(ap);
        	if ( cnt >= QLOG_MAX )
				cnt = QLOG_MAX - 1;

        	//5.error
			if ( eNo != 0 )
			{
				if ( cnt == 0 || *(LogBuf + cnt - 1) != '\n' )
					cnt += ::snprintf( LogBuf + cnt, QLOG_MAX - cnt, " -- (%d)%s", eNo, strerror(eNo) );
				else
				{
					--cnt;
					cnt += ::snprintf( LogBuf + cnt, QLOG_MAX - cnt, " -- (%d)%s\n", eNo, strerror(eNo) );
				}
				if ( cnt >= QLOG_MAX )
					cnt = QLOG_MAX - 1;
			}

        	if ( bLog )
				printf("%s\n", LogBuf);
        	if ( bThrow )
			   	throw std::runtime_error( std::string(LogBuf, cnt) );
		}
    }

	/**
	 * qlog的stream接口
	 */
	class logstream : public qostringstream
	{
	public:
		logstream(const qstring& name, int level, int eNo, const char* file, int line)
		 : m_name(name), m_level(level), m_eNo(eNo), m_file(file), m_line(line) {}

		logstream& l_value() { return *this; }

		~logstream()
		{
			if( isLog(m_name, m_level) )
			{
				logstream& _s = *this;
				if ( m_eNo != 0 )
					_s << QTEXT(" -- (") << m_eNo << QTEXT(')') << strerror(m_eNo);
				printf( "[%s] [%s] [%s:%d] %s\n", m_name.c_str(),
				    qLevelStr(m_level).c_str(), m_file, m_line, _s.str().c_str() );
			}
		}

	private:
		qstring m_name;
		int m_level;
		int m_eNo;
		const char* m_file;
		int m_line;
		logstream( const logstream& );
		logstream& operator=( const logstream& );
	};
}

    #define qLogAndThrows(name, level, eNo, logStream) \
		do \
		{ \
            int m_eNo = eNo; \
            QPub::qostringstream _qbuf; \
            _qbuf << "[" << name << "] [" \
                  << QPub::qLevelStr(level) << "] [" \
                  << __FILE__ << ":" << __LINE__ << "] "; \
            _qbuf << logStream; \
			if ( m_eNo != 0 ) \
                _qbuf << QTEXT(" -- (") << m_eNo << QTEXT(')') << strerror(m_eNo); \
			if ( QPub::isLog(name, level) ) \
			{ \
            	printf( _qbuf.str().c_str() ); \
				printf( "\n" ); \
			} \
			throw std::runtime_error(_qbuf.str()); \
        } while(0)

#endif  //USE_QLOG

#else // __cplusplus

#define CLOG_ALL (0)
#define CLOG_TRACE (0)
#define CLOG_DEBUG (10000)
#define CLOG_INFO  (20000)
#define CLOG_WARN  (30000)
#define CLOG_ERROR (40000)
#define CLOG_FATAL (50000)
#define CLOG_OFF   (60000)

void cLogAll(const char* name, int level, int eNo, const char* file, int line, const char* fmt,...)
		__attribute__ ((format (printf, 6, 7)));

void cLogConfig(const char* configfile);
void cLogCleanConfig();

#endif // __cplusplus

#endif  //_QLOG_TYPES_H_

