#ifndef _QLOG_MANAGER_INLINE_H_
#define _QLOG_MANAGER_INLINE_H_

#ifndef H_OS_WINCE

#include <errno.h>

#include "osl/include/log.h"
#include <stdio.h>
#include <stdarg.h>

namespace osl
{
    namespace LogPub
    {
        inline void logAll( const StringA& name, LogMessageLevel level, const char* filename, const char* funcname, int lineno, const char* fmt, ... )
        {
            Log* pLog = LogManager::getSingletonPtr()->getLog( name );
            if ( !pLog || !pLog->isLogEnabled(level) )
            {
                return;
            }

            const size_t BUF_SIZE = 1024 * 128;
            char s[BUF_SIZE];
            int writen = snprintf( s, sizeof(s), "%s:%s:%d - ", filename, funcname, lineno );
            if ( writen <= 0 )
            {
                fprintf( stderr, "snprintf return error, errno=%d\n", errno );
                return;
            }
            va_list ap;
            va_start(ap,fmt);
            int len = vsnprintf(s + writen, sizeof(s) - writen, fmt, ap);
            va_end(ap);

            if ( len > 0 )
            {
                pLog->logMessage( s, len + writen, level );
            }
        }
    }
}

#ifdef H_OS_WINDOWS

/**
* 变参记录跟踪信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logTrace(name, fmt, ...)	osl::LogPub::logAll(name, ::osl::LML_TRACE, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__ )

/**
* 变参记录调试信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logDebug(name, fmt, ...)	osl::LogPub::logAll(name, ::osl::LML_DEBUG, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__ )

/**
* 变参记录提示信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logInfo(name, fmt, ...)	    osl::LogPub::logAll(name, ::osl::LML_INFO, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__ )

/**
* 变参记录警告信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logWarn(name, fmt, ...)	    osl::LogPub::logAll(name, ::osl::LML_WARN, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__ )

/**
* 变参记录错误信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logError(name, fmt, ...)	osl::LogPub::logAll(name, ::osl::LML_ERROR, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__ )

/**
* 变参记录致命错误信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logFatal(name, fmt, ...)	osl::LogPub::logAll(name, ::osl::LML_FATAL, __FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__ )

#else


/**
* 变参记录跟踪信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logTrace(name, fmt, args...)	osl::LogPub::logAll(name, ::osl::LML_TRACE, __FILE__, __func__, __LINE__, fmt, ##args )

/**
* 变参记录调试信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logDebug(name, fmt, args...)	osl::LogPub::logAll(name, ::osl::LML_DEBUG, __FILE__, __func__, __LINE__, fmt, ##args )

/**
* 变参记录提示信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logInfo(name, fmt, args...)	    osl::LogPub::logAll(name, ::osl::LML_INFO, __FILE__, __func__, __LINE__, fmt, ##args )

/**
* 变参记录警告信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logWarn(name, fmt, args...)	    osl::LogPub::logAll(name, ::osl::LML_WARN, __FILE__, __func__, __LINE__, fmt, ##args )

/**
* 变参记录错误信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logError(name, fmt, args...)	osl::LogPub::logAll(name, ::osl::LML_ERROR, __FILE__, __func__, __LINE__, fmt, ##args )

/**
* 变参记录致命错误信息到日志类别 name 中，fmt格式与 printf 相同.
*/
#define logFatal(name, fmt, args...)	osl::LogPub::logAll(name, ::osl::LML_FATAL, __FILE__, __func__, __LINE__, fmt, ##args )


#endif



#endif // #ifndef H_OS_WINCE

#endif // #ifndef _QLOG_MANAGER_INLINE_H_



