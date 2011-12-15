#ifndef _QLOG_H_
#define _QLOG_H_

#include "qlogtypes.h"

#ifdef __cplusplus

#ifdef _WIN32

/**
 * 变参记录level级别信息到日志类别类别 name 中，fmt格式与 printf 相同.
 */
#define qLog(name, level, fmt, ...)	QPub::qLogAll(name, level, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * 变参记录跟踪信息到日志类别 name 中，fmt格式与 printf 相同.
 */
#define qLogTrace(name, fmt, ...)	QPub::qLogAll(name, QPub::TRACE, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * 变参记录调试信息到日志类别 name 中，fmt格式与 printf 相同.
 */
#define qLogDebug(name, fmt, ...)	QPub::qLogAll(name, QPub::DEBUG, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * 变参记录提示信息到日志类别 name 中，fmt格式与 printf 相同.
 */
#define qLogInfo(name, fmt, ...)	QPub::qLogAll(name, QPub::INFO,  0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )


#define qLogWarn(name, fmt, ...)	QPub::qLogAll(name, QPub::WARN, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * 变参记录应用错误信息到日志类别 name 中，fmt格式与 printf 相同.
 */
#define qAppError(name, fmt, ...)	QPub::qLogAll(name, QPub::ERR, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * 变参记录系统错误信息到日志类别 name 中，fmt格式与 printf 相同.(附加系统错误信息)
 */
#define qSysError(name, fmt, ...)	QPub::qLogAll(name, QPub::ERR, errno, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * 变参记录应用错误信息到日志类别 name 中并抛出异常整数 0，fmt格式与 printf 相同.
 */
#define qAppThrow(name, fmt, ...)	QPub::qLogAll(name, QPub::ERR, 0, true, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * 变参记录系统错误信息到日志类别 name 中并抛出异常整数 errno，fmt格式与 printf 相同.
 */
#define qSysThrow(name, fmt, ...)	QPub::qLogAll(name, QPub::ERR, errno, true, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * 变参记录错误信息到日志类别 name 中，fmt格式与 printf 相同.(附加eNo对应的系统错误信息)
 */
#define qLogError(name, eNo, fmt, ...)	QPub::qLogAll(name, QPub::ERR, eNo, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * 变参记录错误信息到日志类别 name 中并抛出异常整数 eNo，fmt格式与 printf 相同.
 */
#define qLogThrow(name, eNo, fmt, ...)	QPub::qLogAll(name, QPub::ERR, eNo, true, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

#define qLogFatal(name, fmt, ...)	QPub::qLogAll(name, QPub::FATAL, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

#else

/**
 * 变参记录level级别信息到日志类别类别 name 中，fmt格式与 printf 相同.
 */
#define qLog(name, level, fmt, args...) \
        QPub::qLogAll(name, level, 0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * 变参记录跟踪信息到日志类别 name 中，fmt格式与 printf 相同.
 */
#define qLogTrace(name, fmt, args...) \
        QPub::qLogAll(name, QPub::TRACE, 0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * 变参记录调试信息到日志类别 name 中，fmt格式与 printf 相同.
 */
#define qLogDebug(name, fmt, args...) \
        QPub::qLogAll(name, QPub::DEBUG, 0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * 变参记录提示信息到日志类别 name 中，fmt格式与 printf 相同.
 */
#define qLogInfo(name, fmt, args...) \
        QPub::qLogAll(name, QPub::INFO,  0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * 变参记录提示信息到日志类别 name 中，fmt格式与 printf 相同.
 */
#define qLogWarn(name, fmt, args...) \
        QPub::qLogAll(name, QPub::WARN,  0, false, __FILE__, __LINE__, fmt, ##args)



/**
 * 变参记录应用错误信息到日志类别 name 中，fmt格式与 printf 相同.
 */
#define qAppError(name, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, 0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * 变参记录系统错误信息到日志类别 name 中，fmt格式与 printf 相同.(附加系统错误信息)
 */
#define qSysError(name, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, errno, false, __FILE__, __LINE__, fmt, ##args)

/**
 * 变参记录应用错误信息到日志类别 name 中并抛出异常整数 0，fmt格式与 printf 相同.
 */
#define qAppThrow(name, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, 0, true, __FILE__, __LINE__, fmt, ##args)

/**
 * 变参记录系统错误信息到日志类别 name 中并抛出异常整数 errno，fmt格式与 printf 相同.
 */
#define qSysThrow(name, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, errno, true, __FILE__, __LINE__, fmt, ##args)

/**
 * 变参记录错误信息到日志类别 name 中，fmt格式与 printf 相同.(附加eNo对应的系统错误信息)
 */
#define qLogError(name, eNo, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, eNo, false, __FILE__, __LINE__, fmt, ##args)

#define qLogFatal(name, fmt, args...) \
        QPub::qLogAll(name, QPub::FATAL,  0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * 变参记录错误信息到日志类别 name 中并抛出异常整数 eNo，fmt格式与 printf 相同.
 */
#define qLogThrow(name, eNo, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, eNo, true, __FILE__, __LINE__, fmt, ##args)

#endif

/**
 * 流式记录level级别信息到日志类别 name 中.
 */
#define qLogs(name,level)	 QPub::logstream(name,level,0,__FILE__,__LINE__).l_value()

/**
 * 流式记录跟踪信息到日志类别 name 中.
 */
#define qLogTraces(name)	 QPub::logstream(name,QPub::TRACE,0,__FILE__,__LINE__).l_value()

/**
 * 流式记录调试信息到日志类别 name 中.
 */
#define qLogDebugs(name)	 QPub::logstream(name,QPub::DEBUG,0,__FILE__,__LINE__).l_value()

/**
 * 流式记录提示信息到日志类别 name 中.
 */
#define qLogInfos(name)		 QPub::logstream(name,QPub::INFO, 0,__FILE__,__LINE__).l_value()

/**
 * 流式记录提示信息到日志类别 name 中.
 */
#define qLogWarns(name)		 QPub::logstream(name,QPub::WARN, 0,__FILE__,__LINE__).l_value()

/**
 * 流式记录应用错误信息到日志类别 name 中.
 */
#define qAppErrors(name) 	 QPub::logstream(name,QPub::ERROR,0,__FILE__,__LINE__).l_value()

/**
 * 流式记录系统错误信息到日志类别 name 中.(附加系统错误信息)
 */
#define qSysErrors(name) 	 QPub::logstream(name,QPub::ERROR,errno,__FILE__,__LINE__).l_value()

/**
 * 流式记录错误信息到日志类别 name 中.(附加eNo对应的系统错误信息)
 */
#define qLogErrors(name,eNo) QPub::logstream(name,QPub::ERROR,eNo,__FILE__,__LINE__).l_value()


/**
 * 记录应用错误信息到日志类别 name 中并抛出异常整数 0，logEvent为输出流.
 */
#define qAppThrows(name, logEvent) \
        qLogAndThrows(name, QPub::ERROR, 0, logEvent)

/**
 * 记录系统错误信息到日志类别 name 中并抛出异常整数 errno，logEvent为输出流.
 */
#define qSysThrows(name, logEvent) \
        qLogAndThrows(name, QPub::ERROR, errno, logEvent)

#define qLogFatals(name)		 QPub::logstream(name,QPub::FATAL, 0,__FILE__,__LINE__).l_value()

/**
 * 记录错误信息到日志类别 name 中并抛出异常整数 eNo，logEvent为输出流.
 */
#define qLogThrows(name, eNo, logEvent) \
        qLogAndThrows(name, QPub::ERROR, eNo, logEvent)



//////////////////////////////////////////////////////////////////////////////
// qLog配置方法
//////////////////////////////////////////////////////////////////////////////

#ifndef USE_STDOUT
//使用qlog库
#include <vector>
namespace QPub
{
    /**
     * key/value数组类型定义
     */
    typedef std::pair<qstring, qstring> qpair;
    typedef std::vector<qpair> ConfigList;

    /**
     * 从配置文件加载日志设置
     *
     * @param configfile 配置文件名。
     */
    QLOG_EXPORT void qLogConfig(const qstring& configfile);

    /**
     * 从key/value数组加载日志配置
     *
     * @param mlist  key/value数组
     */
    QLOG_EXPORT void qLogConfig(ConfigList& mlist);

    /**
     * 快速配置日志
     *
     * @note 如果filename等于CONSOLE，日志显示在屏幕上。
     * @param level    记录级别
     * @param filename 日志文件名前缀("CONSOLE","","/home/s/log/","../myapp_")
     */
    QLOG_EXPORT void qLogQuickConfig( QLEVEL level=INFO, const qstring& filename=QTEXT("CONSOLE") );

    /**
     * 显示当前全部类别日志信息
     */
    QLOG_EXPORT void qLogViewConfig();

    /**
     * 清除所有日志设置
     */
    QLOG_EXPORT void qLogCleanConfig();

    /**
     * 在对象生存周期内监视配置文件，动态配置
     */
    class QLOG_EXPORT qLogMonitor
    {
    public:
        qLogMonitor(const qstring& filename, unsigned int millis = 60 * 1000);
        ~qLogMonitor();

    private:
        // Disable copy
        qLogMonitor(const qLogMonitor&);
        qLogMonitor& operator=(qLogMonitor&);
        void* handle;
    };

}
#endif  //USE_QLOG

#else // __cplusplus

#include <errno.h>

#define qLog(name, level, fmt, args...) cLogAll(name, level, 0, __FILE__, __LINE__, fmt, ##args)

#define qLogTrace(name, fmt, args...)   cLogAll(name, CLOG_TRACE, 0, __FILE__, __LINE__, fmt, ##args)

#define qLogDebug(name, fmt, args...)   cLogAll(name, CLOG_DEBUG, 0, __FILE__, __LINE__, fmt, ##args)

#define qLogInfo(name, fmt, args...)    cLogAll(name, CLOG_INFO,  0, __FILE__, __LINE__, fmt, ##args)

#define qLogWarn(name, fmt, args...)    cLogAll(name, CLOG_WARN,  0, __FILE__, __LINE__, fmt, ##args)

#define qAppError(name, fmt, args...)   cLogAll(name, CLOG_ERROR, 0, __FILE__, __LINE__, fmt, ##args)

#define qSysError(name, fmt, args...)   cLogAll(name, CLOG_ERROR, errno, __FILE__, __LINE__, fmt, ##args)

#define qLogError(name, eNo, fmt, args...) cLogAll(name, CLOG_ERROR, eNo, __FILE__, __LINE__, fmt, ##args)

#define qLogFatal(name, fmt, args...)    cLogAll(name, CLOG_FATAL,  0, __FILE__, __LINE__, fmt, ##args)

#define qLogConfig cLogConfig
#define qLogCleanConfig cLogCleanConfig

#endif // __cplusplus

#endif  //_QLOG_H_

