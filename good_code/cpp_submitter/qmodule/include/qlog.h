#ifndef _QLOG_H_
#define _QLOG_H_

#include "qlogtypes.h"

#ifdef __cplusplus

#ifdef _WIN32

/**
 * ��μ�¼level������Ϣ����־������ name �У�fmt��ʽ�� printf ��ͬ.
 */
#define qLog(name, level, fmt, ...)	QPub::qLogAll(name, level, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * ��μ�¼������Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.
 */
#define qLogTrace(name, fmt, ...)	QPub::qLogAll(name, QPub::TRACE, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * ��μ�¼������Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.
 */
#define qLogDebug(name, fmt, ...)	QPub::qLogAll(name, QPub::DEBUG, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * ��μ�¼��ʾ��Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.
 */
#define qLogInfo(name, fmt, ...)	QPub::qLogAll(name, QPub::INFO,  0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )


#define qLogWarn(name, fmt, ...)	QPub::qLogAll(name, QPub::WARN, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * ��μ�¼Ӧ�ô�����Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.
 */
#define qAppError(name, fmt, ...)	QPub::qLogAll(name, QPub::ERR, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * ��μ�¼ϵͳ������Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.(����ϵͳ������Ϣ)
 */
#define qSysError(name, fmt, ...)	QPub::qLogAll(name, QPub::ERR, errno, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * ��μ�¼Ӧ�ô�����Ϣ����־��� name �в��׳��쳣���� 0��fmt��ʽ�� printf ��ͬ.
 */
#define qAppThrow(name, fmt, ...)	QPub::qLogAll(name, QPub::ERR, 0, true, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * ��μ�¼ϵͳ������Ϣ����־��� name �в��׳��쳣���� errno��fmt��ʽ�� printf ��ͬ.
 */
#define qSysThrow(name, fmt, ...)	QPub::qLogAll(name, QPub::ERR, errno, true, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * ��μ�¼������Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.(����eNo��Ӧ��ϵͳ������Ϣ)
 */
#define qLogError(name, eNo, fmt, ...)	QPub::qLogAll(name, QPub::ERR, eNo, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

/**
 * ��μ�¼������Ϣ����־��� name �в��׳��쳣���� eNo��fmt��ʽ�� printf ��ͬ.
 */
#define qLogThrow(name, eNo, fmt, ...)	QPub::qLogAll(name, QPub::ERR, eNo, true, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

#define qLogFatal(name, fmt, ...)	QPub::qLogAll(name, QPub::FATAL, 0, false, __FILE__, __LINE__, fmt, ## __VA_ARGS__ )

#else

/**
 * ��μ�¼level������Ϣ����־������ name �У�fmt��ʽ�� printf ��ͬ.
 */
#define qLog(name, level, fmt, args...) \
        QPub::qLogAll(name, level, 0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * ��μ�¼������Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.
 */
#define qLogTrace(name, fmt, args...) \
        QPub::qLogAll(name, QPub::TRACE, 0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * ��μ�¼������Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.
 */
#define qLogDebug(name, fmt, args...) \
        QPub::qLogAll(name, QPub::DEBUG, 0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * ��μ�¼��ʾ��Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.
 */
#define qLogInfo(name, fmt, args...) \
        QPub::qLogAll(name, QPub::INFO,  0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * ��μ�¼��ʾ��Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.
 */
#define qLogWarn(name, fmt, args...) \
        QPub::qLogAll(name, QPub::WARN,  0, false, __FILE__, __LINE__, fmt, ##args)



/**
 * ��μ�¼Ӧ�ô�����Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.
 */
#define qAppError(name, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, 0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * ��μ�¼ϵͳ������Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.(����ϵͳ������Ϣ)
 */
#define qSysError(name, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, errno, false, __FILE__, __LINE__, fmt, ##args)

/**
 * ��μ�¼Ӧ�ô�����Ϣ����־��� name �в��׳��쳣���� 0��fmt��ʽ�� printf ��ͬ.
 */
#define qAppThrow(name, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, 0, true, __FILE__, __LINE__, fmt, ##args)

/**
 * ��μ�¼ϵͳ������Ϣ����־��� name �в��׳��쳣���� errno��fmt��ʽ�� printf ��ͬ.
 */
#define qSysThrow(name, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, errno, true, __FILE__, __LINE__, fmt, ##args)

/**
 * ��μ�¼������Ϣ����־��� name �У�fmt��ʽ�� printf ��ͬ.(����eNo��Ӧ��ϵͳ������Ϣ)
 */
#define qLogError(name, eNo, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, eNo, false, __FILE__, __LINE__, fmt, ##args)

#define qLogFatal(name, fmt, args...) \
        QPub::qLogAll(name, QPub::FATAL,  0, false, __FILE__, __LINE__, fmt, ##args)

/**
 * ��μ�¼������Ϣ����־��� name �в��׳��쳣���� eNo��fmt��ʽ�� printf ��ͬ.
 */
#define qLogThrow(name, eNo, fmt, args...) \
        QPub::qLogAll(name, QPub::ERROR, eNo, true, __FILE__, __LINE__, fmt, ##args)

#endif

/**
 * ��ʽ��¼level������Ϣ����־��� name ��.
 */
#define qLogs(name,level)	 QPub::logstream(name,level,0,__FILE__,__LINE__).l_value()

/**
 * ��ʽ��¼������Ϣ����־��� name ��.
 */
#define qLogTraces(name)	 QPub::logstream(name,QPub::TRACE,0,__FILE__,__LINE__).l_value()

/**
 * ��ʽ��¼������Ϣ����־��� name ��.
 */
#define qLogDebugs(name)	 QPub::logstream(name,QPub::DEBUG,0,__FILE__,__LINE__).l_value()

/**
 * ��ʽ��¼��ʾ��Ϣ����־��� name ��.
 */
#define qLogInfos(name)		 QPub::logstream(name,QPub::INFO, 0,__FILE__,__LINE__).l_value()

/**
 * ��ʽ��¼��ʾ��Ϣ����־��� name ��.
 */
#define qLogWarns(name)		 QPub::logstream(name,QPub::WARN, 0,__FILE__,__LINE__).l_value()

/**
 * ��ʽ��¼Ӧ�ô�����Ϣ����־��� name ��.
 */
#define qAppErrors(name) 	 QPub::logstream(name,QPub::ERROR,0,__FILE__,__LINE__).l_value()

/**
 * ��ʽ��¼ϵͳ������Ϣ����־��� name ��.(����ϵͳ������Ϣ)
 */
#define qSysErrors(name) 	 QPub::logstream(name,QPub::ERROR,errno,__FILE__,__LINE__).l_value()

/**
 * ��ʽ��¼������Ϣ����־��� name ��.(����eNo��Ӧ��ϵͳ������Ϣ)
 */
#define qLogErrors(name,eNo) QPub::logstream(name,QPub::ERROR,eNo,__FILE__,__LINE__).l_value()


/**
 * ��¼Ӧ�ô�����Ϣ����־��� name �в��׳��쳣���� 0��logEventΪ�����.
 */
#define qAppThrows(name, logEvent) \
        qLogAndThrows(name, QPub::ERROR, 0, logEvent)

/**
 * ��¼ϵͳ������Ϣ����־��� name �в��׳��쳣���� errno��logEventΪ�����.
 */
#define qSysThrows(name, logEvent) \
        qLogAndThrows(name, QPub::ERROR, errno, logEvent)

#define qLogFatals(name)		 QPub::logstream(name,QPub::FATAL, 0,__FILE__,__LINE__).l_value()

/**
 * ��¼������Ϣ����־��� name �в��׳��쳣���� eNo��logEventΪ�����.
 */
#define qLogThrows(name, eNo, logEvent) \
        qLogAndThrows(name, QPub::ERROR, eNo, logEvent)



//////////////////////////////////////////////////////////////////////////////
// qLog���÷���
//////////////////////////////////////////////////////////////////////////////

#ifndef USE_STDOUT
//ʹ��qlog��
#include <vector>
namespace QPub
{
    /**
     * key/value�������Ͷ���
     */
    typedef std::pair<qstring, qstring> qpair;
    typedef std::vector<qpair> ConfigList;

    /**
     * �������ļ�������־����
     *
     * @param configfile �����ļ�����
     */
    QLOG_EXPORT void qLogConfig(const qstring& configfile);

    /**
     * ��key/value���������־����
     *
     * @param mlist  key/value����
     */
    QLOG_EXPORT void qLogConfig(ConfigList& mlist);

    /**
     * ����������־
     *
     * @note ���filename����CONSOLE����־��ʾ����Ļ�ϡ�
     * @param level    ��¼����
     * @param filename ��־�ļ���ǰ׺("CONSOLE","","/home/s/log/","../myapp_")
     */
    QLOG_EXPORT void qLogQuickConfig( QLEVEL level=INFO, const qstring& filename=QTEXT("CONSOLE") );

    /**
     * ��ʾ��ǰȫ�������־��Ϣ
     */
    QLOG_EXPORT void qLogViewConfig();

    /**
     * ���������־����
     */
    QLOG_EXPORT void qLogCleanConfig();

    /**
     * �ڶ������������ڼ��������ļ�����̬����
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

