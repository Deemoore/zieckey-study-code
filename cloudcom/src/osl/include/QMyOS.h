
#ifndef _H_OSLIB_OS_
#define _H_OSLIB_OS_





namespace osl
{


#define SYSINFO_BUF_LEN	512
#define SYSINFO_DEV_MAX 16
#define _POSIX_PATH_MAX 256


    //! Load Average
    struct LoadAverage
    {
        float one;
        float five;
        float fifteen;
    };

    //! Cpu information.
    struct CPUInfo
    {
        unsigned long long total;
        unsigned long long user;
        unsigned long long nice;
        unsigned long long system;
        unsigned long long idle;

    public:
        void clear()
        {
            this->total = 0;
            this->user = 0;
            this->nice = 0;
            this->system = 0;
            this->idle = 0;
        }
    };

    struct MemoryInfo
    {
        unsigned long total;
        unsigned long used;
        unsigned long mfree;
        unsigned long shared;
        unsigned long buffers;
        unsigned long cached;

        void clear()
        {
            memset( this, 0, sizeof( MemoryInfo ) );
        }
    };


    struct NetSpeedInfo
    {
        float recvspeed;
        float sendspeed;
    };

    typedef struct StatsStructProc
    {
        int           pid;                      /** The process id. **/
        char          exName [_POSIX_PATH_MAX]; /** The filename of the executable **/
        char          state; /** 1 **/          /** R is running, S is sleeping,
													D is sleeping in an uninterruptible wait,
													Z is zombie, T is traced or stopped **/
        unsigned      euid,                      /** effective user id **/
               egid;                      /** effective group id */
        int           ppid;                     /** The pid of the parent. **/
        int           pgrp;                     /** The pgrp of the process. **/
        int           session;                  /** The session id of the process. **/
        int           tty;                      /** The tty the process uses **/
        int           tpgid;                    /** (too long) **/
        unsigned int    flags;                    /** The flags of the process. **/
        unsigned int    minflt;                   /** The number of minor faults **/
        unsigned int    cminflt;                  /** The number of minor faults with childs **/
        unsigned int    majflt;                   /** The number of major faults **/
        unsigned int  cmajflt;                  /** The number of major faults with childs **/
        int           utime;                    /** user mode jiffies **/
        int           stime;                    /** kernel mode jiffies **/
        int     cutime;                   /** user mode jiffies with childs **/
        int           cstime;                   /** kernel mode jiffies with childs **/
        int           counter;                  /** process's next timeslice **/
        int           priority;                 /** the standard nice value, plus fifteen **/
        unsigned int  timeout;                  /** The time in jiffies of the next timeout **/
        unsigned int  itrealvalue;              /** The time before the next SIGALRM is sent to the process **/
        int           starttime; /** 20 **/     /** Time the process started after system boot **/
        unsigned int  vsize;                    /** Virtual memory size **/
        unsigned int  rss;                      /** Resident Set Size **/
        unsigned int  rlim;                     /** Current limit in bytes on the rss **/
        unsigned int  startcode;                /** The address above which program text can run **/
        unsigned int    endcode;                  /** The address below which program text can run **/
        unsigned int  startstack;               /** The address of the start of the stack **/
        unsigned int  kstkesp;                  /** The current value of ESP **/
        unsigned int  kstkeip;                 /** The current value of EIP **/
        int     signal;                   /** The bitmap of pending signals **/
        int           blocked; /** 30 **/       /** The bitmap of blocked signals **/
        int           sigignore;                /** The bitmap of ignored signals **/
        int           sigcatch;                 /** The bitmap of catched signals **/
        unsigned int  wchan;  /** 33 **/        /** (too long) **/
        int     sched,        /** scheduler **/
          sched_priority;       /** scheduler priority **/

        const StatsStructProc& operator =( const StatsStructProc& sp )
        {
            this->utime = sp.utime;
            this->stime = sp.stime;
            this->cutime = sp.cutime;
            this->cstime = sp.cstime;
            return *this;
        }

        void clear()
        {
            memset( this, 0, sizeof( StatsStructProc ) );
        }


    } ProcInfo;

    struct CPUUsagInfo
    {
        float system;
        float proc;
    };

    struct MemoryUsageInfo
    {
        unsigned long system;
        unsigned long procvirtual;
    };

//! Process handle
#ifdef H_OS_WINDOWS
    typedef HANDLE   ProcessHandle;
#elif defined(H_OS_LINUX)
    typedef u32      ProcessHandle;
#endif

    //! Operation System wrapper.
    class _EXPORT_OSLIB OS
    {
    public:

        //! 返回系统版本字符串
        static StringA getOperationSystemVersion();

        //! 获得可执行程序的目录
		//! get bin dir, such as "e:/deploy/server/debug"
        //! \param bWithEndSlash[in] true, End of the string With a SLASH "/".
        static StringA getBinDir( bool bWithEndSlash = false );

        //! 获得配置文件路径，依赖于 getBinDir()，例如：
        //! \note 当前路径就是 getBinDir()
        //! 1.  bin/xxx.exe         ../etc/xxx.cfg
        //! 2.  bin/Debug/xxx.exe   ../etc/xxx.cfg
        //! 3.  bin/Debug/xxx.exe   ../../etc/xxx.cfg
        //! 4.  xxx.exe             ./etc/xxx.cfg
		//! get config file dir, with no ends '/', such as "e:/deploy/server/etc"
        static StringA getConfDir();

        //! \brief 获得某个文件夹的全路径。可以设置向上级父目录的搜索路径深度。
        //! \note The current path is the directory using getBinDir()
        //! \param strFolderName The name of the directory. like "etc"
        //! \param nDepth The searching depth with upward direction(parent folder)
        //! \return osl::StringA The full path of the direction. If no find, return StringA("")
        static StringA getFullPathDir( const StringA& strFolderName, u32 nDepth = 0 );

        //! 拷贝字符串到剪贴板
        static bool copyToClipboard( const String& strText );

        //! 获得剪贴板中的文字
		static StringA getTextFromClipboard();

		//! 获得显卡驱动名称
		//! \return 显卡驱动名称
		static StringA getDisplayDriverName();

		//! 获得显卡名称
		//! \return 显卡名称
		static StringA getDisplayCardName();

		//! 获得处理器名称
		//! \return 处理器名称
		static StringA getProcessorName();

		//! 获得处理器频率
        //! \return f64 处理器频率，单位M Hz
        static f64 getProcessorFrequencyMHz();

        //! 获得处理器频率
		//! \return f64 处理器频率，单位Hz
        static f64 getProcessorFrequency();

        //! 获得处理器个数
        static u32 getNumProcessor();

        static ThreadID getCurrentThreadId();

        //! Sets max processor number the process can use. It will call setProcessAffinity as implemention.
        static void setMaxProcessorNumber( osl::u32 nNum );

        //! Sets proces affinity. from LSB to MSB. e.g. "0000001" is first processor.
        static void setProcessAffinity( osl::u32 nProcessorMask );

        //! Gets proces affinity. from LSB to MSB. e.g. "0000001" is first processor.
        static osl::u32 getProcessAffinity();

        //! 获得系统内存数据gets the total and available system RAM
        //! \param Total 系统物理内存总量
        //! \param Avail 可用物理内存总量
        //! \retval true 成功 Total Avail 可用
        static bool getSystemMemoryMB( u32* Total, u32* Avail );

        //! 获得系统内存总量
        static u64 getTotalMemoryMB();

        //! 获得cpu使用率
        //! \param pCpuUsageInfor [in,out]  Receive information.
		static void getCpuUsage( CPUUsagInfo* pCpuUsageInfo );
		static void updataCpuUsage( void );

        //! 获得内存使用率
        //! \param pMemoryUsageInfo [in,out]  Receive information.
        static void getMemoryUsage( MemoryUsageInfo* pMemoryUsageInfo );

        //! Gets net face speed.
        //! \param szDev [in,out]  Receive information.
        static void getNetFaceSpeed( const char* szDev, struct NetSpeedInfo* pSpeedInfo );

        //! Gets system load .
        //! \param szDev [in,out]  Receive information.
        static void getLoadAvr( LoadAverage* pstLA );

		//!  Sleep millseconds
        //! Sleep for a while.It will sleep the calling thread.
        //! \param nMilliseconds 10^(-3) seconds.
        static void msSleep( u32 nMilliseconds );
        static void msleep( u32 nMilliseconds ) { msSleep(nMilliseconds); }

		//! Sleep microseconds
        //! \param nUSeconds 10^(-6) seconds.
        static void usSleep( u32 nUSeconds );
        static void usleep( u32 nUSeconds ) { usSleep(nUSeconds); }

        //! 获得当前线程句柄Gets process handle of the process.
        static ProcessHandle getCurrentProcessHandle();

        //! 结束进程
        static bool closeProcess( ProcessHandle hProcess );

        //! Gets max number of writev and readv iovec number.
        //! \remark for linux it return sysconf(_SC_IOV_MAX), for windows, it is 10
        static u32 getNumMaxIOV();


        //! \brief  设置环境变量
        //! \param	const char * szKey
        //! \param	const char * szValue
        static void setEnvironmentString( const char* szKey, const char* szValue );
        //! \brief  获取环境变量
        //! \param	const char * szKey
        //! \return osl::StringA
        static StringA getEnvironmentString( const char* szKey );

        //! \brief A system call, to pause the program
        //! \warning This function is only used in main() routine.
        //!		DO NOT use this function at any other place.
        static void pause();

        //! \brief 获得最后错误对应的描述信息
        static StringA getLastErrorString();

        //! \brief 得到当前登录的用户名
        static StringA getCurrentUserName();

		//! \brief 得到当前用户的路径
		static StringA getCurrentUserFolderPath();


        //! Initialize the os module. It is called by initializeOSLib when start the module.
        //! \remark No other method in the module can be called here.
        static void initialize();

        //! uninitialize the os module. It is called by initializeOSLib when shutdown the module.
        //! \remark No other method in the module can be called here.
        static void uninitialize();
    private:
        //! Default constructor can only be called by initializeUtils.
        OS();

        //! Hide copy constructor.
        OS( const OS& );

        ~OS();
    };


};//namespace

#define DEBUG_FILE_LINE_2_P(x,y) ( x " " #y )
#define DEBUG_FILE_LINE_2(x,y) DEBUG_FILE_LINE_2_P(x,y)
#define DEBUG_FILE_LINE DEBUG_FILE_LINE_2( __FILE__ , __LINE__ )

#endif




