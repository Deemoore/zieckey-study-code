
#ifndef _H_OSLIB_OS_
#define _H_OSLIB_OS_


#ifdef H_OS_WINDOWS
#	include <emmintrin.h>
#   ifdef __MINGW32__
#       include <basetyps.h>
#       include <io.h>
#   endif
#elif defined(H_OS_LINUX)
#	include <stdint.h>
#endif


#ifdef H_OS_WINDOWS
#define ThreadID DWORD
#else
#define ThreadID pthread_t
#endif

namespace osl
{
    class _EXPORT_OSLIB Byteswap
    {
    public:
        static u16 byteswap( u16 num );
        static s16 byteswap( s16 num );
        static u32 byteswap( u32 num );
        static s32 byteswap( s32 num );
        static f32 byteswap( f32 num );
    };

    class _EXPORT_OSLIB Randomizer
    {
    public:
        static void reset();	//!< reset seed
        static s32 rand();		//!< generate a rand number

        static s32 getRandInRange( s32 minv, s32 maxv );//!< get a number in the range [minv,maxv) 
    private:
        static s32 seed;
    };



#ifdef H_OS_WINDOWS

#		define InterlockedCmpXchng32              InterlockedCompareExchange
#		define InterlockedXchng32	              InterlockedExchange
#		define InterlockedInc32		              InterlockedIncrement
#		define InterlockedDec32		              InterlockedDecrement
#		define InterlockedExchangeAdd32( x, y )   InterlockedExchangeAdd( (volatile LONG*)x, (LONG)y )


#ifdef H_ARCH_64
#		define InterlockedCmpXchng64              InterlockedCompareExchange64
#		define InterlockedXchng64	              InterlockedExchange64
#		define InterlockedInc64		              InterlockedIncrement64
#		define InterlockedDec64		              InterlockedDecrement64
#		define InterlockedExchangeAdd64( x, y )   InterlockedExchangeAdd64( (volatile LONG64*)x, (LONG64)y )
#endif

#elif defined(H_OS_LINUX)

	    s32 __cmpxchg32( volatile ::osl::s32* ptr, s32 old, s32 n );
		    s32 __xchg32( volatile ::osl::s32* ptr, s32 x );
			    s32 __xadd32( volatile ::osl::s32* ptr, s32 i );

#		define InterlockedCmpXchng32(ptr,n,o)     ::osl::__cmpxchg32(ptr,o,n)
#		define InterlockedXchng32(ptr,v)          ::osl::__xchg32(ptr,v)
#		define InterlockedInc32(ptr)              ::osl::__xadd32(ptr,(::osl::s32)(1))
#		define InterlockedDec32(ptr)              ::osl::__xadd32(ptr,-1)
#		define InterlockedExchangeAdd32( x, y )   ::osl::__xadd32( (volatile ::osl::s32*)x, (::osl::s32)y )


#ifdef H_ARCH_64
				    long __cmpxchg64( volatile long* ptr, long old, long n );
					    long __xchg64( volatile long* ptr, long x );
						    long __xadd64( volatile long* ptr, long i );

#		define InterlockedCmpXchng64(ptr,n,o)     ::osl::__cmpxchg64( (volatile long*)ptr,o,n)
#		define InterlockedXchng64(ptr,v)          ::osl::__xchg64( (volatile long*)ptr,(long)v )
#		define InterlockedInc64(ptr)              ::osl::__xadd64( (volatile long*)ptr, (long)(1) )
#		define InterlockedDec64(ptr)              ::osl::__xadd64( (volatile long*)ptr,(long)-1 )
#		define InterlockedExchangeAdd64( x, y )   ::osl::__xadd64( (volatile long*)x, (long)y )
#endif


#endif // end if linux


#ifdef H_ARCH_32
#		define InterlockedCmpXchng                InterlockedCmpXchng32
#		define InterlockedXchng	                  InterlockedXchng32
#		define InterlockedInc		              InterlockedInc32
#		define InterlockedDec		              InterlockedDec32
#		define InterlockedXAdd( x, y )            InterlockedExchangeAdd32( x, y )

#elif defined(H_ARCH_64)

#		define InterlockedCmpXchng                InterlockedCmpXchng64
#		define InterlockedXchng	                  InterlockedXchng64
#		define InterlockedInc		              InterlockedInc64
#		define InterlockedDec		              InterlockedDec64
#		define InterlockedXAdd( x, y )            InterlockedExchangeAdd64( x, y )
#endif


//! Memory barrier.
#ifdef H_OS_WINDOWS
#	define mb()   _mm_mfence()
#elif defined(H_OS_LINUX)
#	define mb()  __sync_synchronize()
#else
#endif



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

        //! ����ϵͳ�汾�ַ���
        static StringA getOperationSystemVersion();

        //! ��ÿ�ִ�г����Ŀ¼
		//! get bin dir, such as "e:/deploy/server/debug"
        //! \param bWithEndSlash[in] true, End of the string With a SLASH "/".
        static StringA getBinDir( bool bWithEndSlash = false );

        //! ��������ļ�·���������� getBinDir()�����磺
        //! \note ��ǰ·������ getBinDir()
        //! 1.  bin/xxx.exe         ../etc/xxx.cfg
        //! 2.  bin/Debug/xxx.exe   ../etc/xxx.cfg
        //! 3.  bin/Debug/xxx.exe   ../../etc/xxx.cfg
        //! 4.  xxx.exe             ./etc/xxx.cfg
		//! get config file dir, with no ends '/', such as "e:/deploy/server/etc"
        static StringA getConfDir();

        //! \brief ���ĳ���ļ��е�ȫ·���������������ϼ���Ŀ¼������·����ȡ�
        //! \note The current path is the directory using getBinDir()
        //! \param strFolderName The name of the directory. like "etc"
        //! \param nDepth The searching depth with upward direction(parent folder)
        //! \return osl::StringA The full path of the direction. If no find, return StringA("")
        static StringA getFullPathDir( const StringA& strFolderName, u32 nDepth = 0 );

        //! �����ַ�����������
        static bool copyToClipboard( const String& strText );

        //! ��ü������е�����
		static StringA getTextFromClipboard();

		//! ����Կ���������
		//! \return �Կ���������
		static StringA getDisplayDriverName();

		//! ����Կ�����
		//! \return �Կ�����
		static StringA getDisplayCardName();

		//! ��ô���������
		//! \return ����������
		static StringA getProcessorName();

		//! ��ô�����Ƶ��
        //! \return f64 ������Ƶ�ʣ���λM Hz
        static f64 getProcessorFrequencyMHz();

        //! ��ô�����Ƶ��
		//! \return f64 ������Ƶ�ʣ���λHz
        static f64 getProcessorFrequency();

        //! ��ô���������
        static u32 getNumProcessor();

        static ThreadID getCurrentThreadId();

        //! Sets max processor number the process can use. It will call setProcessAffinity as implemention.
        static void setMaxProcessorNumber( osl::u32 nNum );

        //! Sets proces affinity. from LSB to MSB. e.g. "0000001" is first processor.
        static void setProcessAffinity( osl::u32 nProcessorMask );

        //! Gets proces affinity. from LSB to MSB. e.g. "0000001" is first processor.
        static osl::u32 getProcessAffinity();

        //! ���ϵͳ�ڴ�����gets the total and available system RAM
        //! \param Total ϵͳ�����ڴ�����
        //! \param Avail ���������ڴ�����
        //! \retval true �ɹ� Total Avail ����
        static bool getSystemMemoryMB( u32* Total, u32* Avail );

        //! ���ϵͳ�ڴ�����
        static u64 getTotalMemoryMB();

        //! ���cpuʹ����
        //! \param pCpuUsageInfor [in,out]  Receive information.
		static void getCpuUsage( CPUUsagInfo* pCpuUsageInfo );
		static void updataCpuUsage( void );

        //! ����ڴ�ʹ����
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

        //! ��õ�ǰ�߳̾��Gets process handle of the process.
        static ProcessHandle getCurrentProcessHandle();

        //! ��������
        static bool closeProcess( ProcessHandle hProcess );

        //! Gets max number of writev and readv iovec number.
        //! \remark for linux it return sysconf(_SC_IOV_MAX), for windows, it is 10
        static u32 getNumMaxIOV();


        //! \brief  ���û�������
        //! \param	const char * szKey
        //! \param	const char * szValue
        static void setEnvironmentString( const char* szKey, const char* szValue );
        //! \brief  ��ȡ��������
        //! \param	const char * szKey
        //! \return osl::StringA
        static StringA getEnvironmentString( const char* szKey );

        //! \brief A system call, to pause the program
        //! \warning This function is only used in main() routine.
        //!		DO NOT use this function at any other place.
        static void pause();

        //! \brief ����������Ӧ��������Ϣ
        static StringA getLastErrorString();

        //! \brief �õ���ǰ��¼���û���
        static StringA getCurrentUserName();

		//! \brief �õ���ǰ�û���·��
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


#	ifdef H_DEBUG_MODE
#		ifdef H_OS_WINDOWS
    inline int trace( const char* pFmt , ... )
    {
        static __declspec( thread ) char g_trace_str_array[1024] = {0};
        va_list args;
        va_start( args, pFmt );
        const int length = _vsnprintf( g_trace_str_array , 1023 , pFmt , args );
        OutputDebugStringA( g_trace_str_array );
        return length;
    }
#		else
    inline int trace( const char* pFmt , ... )
    {
        return 0;
    }
#		endif
#else
    inline int trace( const char* pFmt , ... )
    {
        return 0;
    }
#	endif

};//namespace

/*
#	ifdef TRACE
#		undef TRACE
#	endif

#	define TRACE osl::trace
*/



#define DEBUG_FILE_LINE_2_P(x,y) ( x " " #y )
#define DEBUG_FILE_LINE_2(x,y) DEBUG_FILE_LINE_2_P(x,y)
#define DEBUG_FILE_LINE DEBUG_FILE_LINE_2( __FILE__ , __LINE__ )




#endif




