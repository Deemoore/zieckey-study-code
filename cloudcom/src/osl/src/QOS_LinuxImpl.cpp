#include "osl/include/QOSLibPrerequisits.h"


#include "osl/include/QMemAlloc.h"
#include "osl/include/QString.h"
#include "osl/include/QStringUtil.h"
#include "osl/include/QFileUtil.h"

#include "osl/include/QMyOS.h"

#ifdef H_OS_LINUX

#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>
#include <sched.h>


namespace osl
{

    //////////////////////////////////////////////////////////////////////////
    //                   SysInfo
    //////////////////////////////////////////////////////////////////////////
    struct NetStat
    {
        const char *dev;
        int up;
        u64 last_read_recv, last_read_trans; //last read total num
        u64 recv, trans; //real total num
        double recv_speed, trans_speed;

        void clear()
        {
            memset( this, 0, sizeof( NetStat ) );
        }
    };

    class SysInfo
    {
    public:
        SysInfo()
        {
            m_oldcpuinfo.clear();
            cpuinfo( &m_oldcpuinfo );

            m_oldProcInfo.clear();
            getProcInfo( getpid(), &m_oldProcInfo );

            for ( int i = 0; i < SYSINFO_DEV_MAX; i++ )
            {
                netstats[ i ].clear();
            }

            current_time = time( NULL );
        }
        ~SysInfo()
        {
        }
    public:
        unsigned int getCpuCount()
        {
            int nCount = 0;
            char buf[ SYSINFO_BUF_LEN ];
            FILE* fp = fopen( "/proc/cpuinfo", "r" );

            if ( fp )
            {
                while ( fgets( buf, sizeof( buf ), fp ) )
                {
                    if ( strstr( buf, "processor" ) )
                    {
                        nCount++;
                    }
                }

                fclose( fp );
            }

            return nCount;
        }
        //----------------------------------------------
        float getCpuFrequency()
        {
            float fFreq = 0;
            char buf[ SYSINFO_BUF_LEN ];
            FILE* fp = fopen( "/proc/cpuinfo", "r" );

            if ( fp )
            {
                while ( fgets( buf, sizeof( buf ), fp ) )
                {
                    if ( strstr( buf, "cpu MHz" ) )
                    {
                        char* szFreq = strchr( buf, ':' );
                        szFreq++;

                        while ( szFreq[ 0 ] == ' ' )
                        {
                            szFreq++;
                        }

                        fFreq = atof( szFreq );
                        break;
                    }
                }

                fclose( fp );
            }

            return fFreq;
        }
        //----------------------------------------------
        unsigned long getTotalMemory()
        {
            MemoryInfo stmemory;
            memoryinfo( &stmemory );
            return stmemory.total;
        }
        //----------------------------------------------
        void getCpuUsage( CPUUsagInfo* pCpuUsageInfo )
        {
            CPUInfo ci;
            cpuinfo( &ci );
            float idle = ci.idle - m_oldcpuinfo.idle;
            float total = ci.total - m_oldcpuinfo.total;

            ProcInfo pi;
            getProcInfo( getpid(), &pi );

            float pTime = pi.utime + pi.stime + pi.cutime + pi.cstime - m_oldProcInfo.utime - m_oldProcInfo.stime - m_oldProcInfo.cutime - m_oldProcInfo.cstime;

            m_oldcpuinfo = ci;
            m_oldProcInfo = pi;

            if ( static_cast<int>( total ) != 0 )
            {
                pCpuUsageInfo->system = 1.0 - idle / total;
                pCpuUsageInfo->proc = pTime / total;
            }
            else
            {
                pCpuUsageInfo->system = 0;
                pCpuUsageInfo->proc = 0;
            }
        }
        //----------------------------------------------
        void getMemoryUsage( MemoryUsageInfo* pMemoryUsageInfo )
        {
            MemoryInfo stmemory;
            memoryinfo( &stmemory );

            ProcInfo pi;
            getProcInfo( getpid(), &pi );

            pMemoryUsageInfo->system = stmemory.used;
            pMemoryUsageInfo->procvirtual = pi.vsize / 1024;
        }
        //----------------------------------------------
        void getNetFaceSpeed( const char* szDev, struct NetSpeedInfo* pSpeedInfo )
        {
            pSpeedInfo->recvspeed = 0;
            pSpeedInfo->sendspeed = 0;
            last_time = current_time;
            current_time = time( NULL );
            delta_time = current_time - last_time;

            if ( delta_time == 0 )
            {
                return;
            }

            update_NetStats( szDev, delta_time );
            struct NetStat* ns = get_NetStat( szDev );

            pSpeedInfo->recvspeed = ns->recv_speed / 1024;
            pSpeedInfo->sendspeed = ns->trans_speed / 1024;
        }
        //----------------------------------------------
        void getLoadAvr( struct LoadAverage* pstLA )
        {
            pstLA->one = 0;
            pstLA->five = 0;
            pstLA->fifteen = 0;

            char buf[ SYSINFO_BUF_LEN ];
            buf[ 0 ] = '\0';
            FILE* fp = fopen( "/proc/loadavg", "r" );

            if ( fp )
            {
                fread( buf, sizeof( buf ), sizeof( char ), fp );
                fclose( fp );
            }

            char* start = buf;
            char* end = strchr( buf, ' ' );

            if ( end )
            {
                *end = '\0';
                pstLA->one = atof( start );
                start = end + 1;
                end = strchr( end + 1, ' ' );
            }

            if ( end )
            {
                *end = '\0';
                pstLA->five = atof( start );
                start = end + 1;
                end = strchr( end + 1, ' ' );
            }

            if ( end )
            {
                *end = '\0';
                pstLA->fifteen = atof( start );
            }
        }
    private:
        void cpuinfo( CPUInfo* pcpuinfo )
        {
            pcpuinfo->clear();
            FILE *fp = fopen( "/proc/stat", "r" );

            if ( fp )
            {
                if ( fscanf( fp, "cpu %lld %lld %lld %lld", &pcpuinfo->user, &pcpuinfo->nice,
                             &pcpuinfo->system, &pcpuinfo->idle ) < 4 )
                {
                    pcpuinfo->clear();
                }

                fclose( fp );
            }

            pcpuinfo->total = ( pcpuinfo->user + pcpuinfo->nice + pcpuinfo->system + pcpuinfo->idle );
        }
        void memoryinfo( MemoryInfo* pstMemory )
        {
            pstMemory->clear();
            char buf[ SYSINFO_BUF_LEN ];
            FILE* fp = fopen( "/proc/meminfo", "r" );

            if ( fp )
            {
                fscanf( fp, "MemTotal: %lu %s\n", &pstMemory->total, buf );
                fscanf( fp, "MemFree: %lu %s\n", &pstMemory->mfree, buf );
                fscanf( fp, "Buffers: %lu %s\n", &pstMemory->buffers, buf );
                fscanf( fp, "Cached: %lu %s\n", &pstMemory->cached, buf );

                pstMemory->used = pstMemory->total - pstMemory->mfree;

                fclose( fp );
            }
        }
        //----------------------------------------------
        int getProcInfo( pid_t pid, ProcInfo * pinfo )
        {
            char szFileName [_POSIX_PATH_MAX],
                 szStatStr [2048],
                 *s, *t;
            FILE *fp;
            struct stat st;

            if ( NULL == pinfo )
            {
                errno = EINVAL;
                return -1;
            }

            sprintf( szFileName, "/proc/%u/stat", ( unsigned ) pid );

            if ( -1 == access ( szFileName, R_OK ) )
            {
                return ( pinfo->pid = -1 );
            } /** if **/

            if ( -1 != stat ( szFileName, &st ) )
            {
                pinfo->euid = st.st_uid;
                pinfo->egid = st.st_gid;
            }
            else
            {
                pinfo->euid = pinfo->egid = -1;
            }


            if ( ( fp = fopen ( szFileName, "r" ) ) == NULL )
            {
                return ( pinfo->pid = -1 );
            } /** IF_NULL **/

            if ( ( s = fgets ( szStatStr, 2048, fp ) ) == NULL )
            {
                fclose ( fp );
                return ( pinfo->pid = -1 );
            }

            /** pid **/
            sscanf ( szStatStr, "%u", &( pinfo->pid ) );
            s = strchr ( szStatStr, '(' ) + 1;
            t = strchr ( szStatStr, ')' );
            strncpy ( pinfo->exName, s, t - s );
            pinfo->exName [t - s] = '\0';

            sscanf ( t + 2, "%c %d %d %d %d %d %u %u %u %u %u %d %d %d %d %d %d %u %u %d %u %u %u %u %u %u %u %u %d %d %d %d %u",
                     /*       1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33*/
                     &( pinfo->state ),
                     &( pinfo->ppid ),
                     &( pinfo->pgrp ),
                     &( pinfo->session ),
                     &( pinfo->tty ),
                     &( pinfo->tpgid ),
                     &( pinfo->flags ),
                     &( pinfo->minflt ),
                     &( pinfo->cminflt ),
                     &( pinfo->majflt ),
                     &( pinfo->cmajflt ),
                     &( pinfo->utime ),
                     &( pinfo->stime ),
                     &( pinfo->cutime ),
                     &( pinfo->cstime ),
                     &( pinfo->counter ),
                     &( pinfo->priority ),
                     &( pinfo->timeout ),
                     &( pinfo->itrealvalue ),
                     &( pinfo->starttime ),
                     &( pinfo->vsize ),
                     &( pinfo->rss ),
                     &( pinfo->rlim ),
                     &( pinfo->startcode ),
                     &( pinfo->endcode ),
                     &( pinfo->startstack ),
                     &( pinfo->kstkesp ),
                     &( pinfo->kstkeip ),
                     &( pinfo->signal ),
                     &( pinfo->blocked ),
                     &( pinfo->sigignore ),
                     &( pinfo->sigcatch ),
                     &( pinfo->wchan ) );
            fclose ( fp );
            return 0;
        }
        //----------------------------------------------
        struct NetStat *get_NetStat( const char *dev )
        {
            unsigned int i = 0;

            if ( !dev )
            {
                return 0;
            }

            /* find interface stat */
            for ( i = 0; i < 16; i++ )
            {
                if ( netstats[i].dev && strcmp( netstats[i].dev, dev ) == 0 )
                {
                    return &netstats[i];
                }
            }

            /* wasn't found? add it */
            if ( i == 16 )
            {
                for ( i = 0; i < 16; i++ )
                {
                    if ( netstats[i].dev == 0 )
                    {
                        netstats[i].dev = strndup( dev, SYSINFO_BUF_LEN );
                        return &netstats[i];
                    }
                }
            }

            fprintf( stderr, "too many interfaces used (limit is 16)" );
            return 0;
        }
        //----------------------------------------------
        void clear_NetStats( void )
        {
            memset( netstats, 0, sizeof( netstats ) );
        }
        void update_NetStats( const char* dev, double delta )
        {
            FILE *net_dev_fp;

            // FIXME: arbitrary size chosen to keep code simple.
            int i = 0;
            char buf[256] = {0};

            /* open file and ignore first two lines */
            if ( !( net_dev_fp = fopen( "/proc/net/dev", "r" ) ) )
            {
                fprintf( stderr, "fopen failed.\n" );
                clear_NetStats();
                return;
            }

            fgets( buf, 255, net_dev_fp );  /* garbage */
            fgets( buf, 255, net_dev_fp );  /* garbage (field names) */

            /* read each interface */
            for ( i = 0; i < 16; i++ )
            {
                struct NetStat *ns = NULL;
                unsigned char *s = NULL, *p = NULL;
                unsigned long long r = 0, t = 0;
                unsigned long long last_recv = 0, last_trans = 0;

                if ( fgets( buf, 255, net_dev_fp ) == NULL )
                {
                    /*File EOF*/
                    break;
                }

                /*Skip Space*/
                p = ( unsigned char* )buf;

                while ( isspace( ( int ) *p ) )
                {
                    p++;
                }

                /*s: network interface name*/
                s = p;

                /*Skip Network Interface Name*/
                while ( *p && *p != ':' )
                {
                    p++;
                }

                if ( *p == '\0' )
                {
                    continue;
                }

                *p = '\0';

                /*p: reveive bytes*/
                p++;

                /*Judge Network Interface or Not?*/
                if ( strcmp( ( const char* )s, ( const char* )dev ) != 0 )
                {
                    continue;
                }

                /*Get struct NetStat*/
                ns = get_NetStat( ( const char* )s );
                ns->up = 1;

                last_recv = ns->recv;
                last_trans = ns->trans;
                /* bytes packets errs drop fifo frame compressed multicast|bytes ... */
                sscanf( ( const char* )p, "%lld  %*d     %*d  %*d  %*d  %*d   %*d        %*d       %lld",  &r, &t );

                /* if recv or trans is less than last time, an overflow happened */
                if ( r < ns->last_read_recv )
                {
                    last_recv = 0;
                }
                else
                {
                    ns->recv += ( r - ns->last_read_recv );
                }

                ns->last_read_recv = r;

                if ( t < ns->last_read_trans )
                {
                    last_trans = 0;
                }
                else
                {
                    ns->trans += ( t - ns->last_read_trans );
                }

                ns->last_read_trans = t;

                /* calculate speeds */
                if ( last_recv == 0 )
                {
                    ns->recv_speed = 0;
                }
                else
                {
                    ns->recv_speed = ( ns->recv - last_recv ) / delta;
                }

                if ( last_trans == 0 )
                {
                    ns->trans_speed = 0;
                }
                else
                {
                    ns->trans_speed = ( ns->trans - last_trans ) / delta;
                }

                break;
            }

            fclose( net_dev_fp );
        }

    private:
        CPUInfo	m_oldcpuinfo;
        ProcInfo	m_oldProcInfo;
        struct NetStat netstats[ SYSINFO_DEV_MAX ];
        time_t current_time;
        time_t last_time;
        time_t delta_time;
    };

    SysInfo  s_sysInfo;

    //----------------------------------------------------------
    String OS::getOperationSystemVersion()
    {
        OStringStream strTip;
        struct utsname LinuxInfo;
        uname( &LinuxInfo );

        strTip << LinuxInfo.sysname
               <<  " "
               << LinuxInfo.release
               << " "
               << LinuxInfo.version
               << " "
               << LinuxInfo.machine;

        return strTip.str();
    }
    //----------------------------------------------------------
    bool OS::copyToClipboard( const String& strText )
    {
        assert( false && "Not Implemented Yet!" );
		return false;
    }
    //----------------------------------------------------------
    String OS::getTextFromClipboard()
    {
        assert( false && "Not Implemented Yet!" );
        return StringUtil::BLANK;
        //return m_pImpl->getTextFromClipboard();
	}
	//----------------------------------------------------------
	String OS::getDisplayDriverName()
	{
		return "unknown";
	}
	//----------------------------------------------------------
	String OS::getDisplayCardName()
	{
		return "unknown";
	}
	//----------------------------------------------------------
	String OS::getProcessorName()
	{
		return "unknown";
	}
    void OS::updataCpuUsage()
    {
        assert( false && "Not Implemented Yet!" );
    }
	//----------------------------------------------------------
    f64 OS::getProcessorFrequencyMHz()
    {
        return s_sysInfo.getCpuFrequency() / ( 1 << 20 );
    }
    //! Gets Processor frequency.
    f64 getProcessorFrequency()
    {
        return s_sysInfo.getCpuFrequency();
    }
    //----------------------------------------------------------
    u32 OS::getNumProcessor()
    {
        return sysconf( _SC_NPROCESSORS_ONLN );
    }
    //----------------------------------------------------------
    void OS::setMaxProcessorNumber( osl::u32 nNum )
    {
        osl::u32 nNumMaxProcessor = getNumProcessor();

        if( nNum > nNumMaxProcessor )
        {
            nNum = nNumMaxProcessor;
        }

        osl::u32 nProcessorMask = 0;

        for( osl::u32 i = 0; i < nNum; ++i )
        {
            nProcessorMask |= ( 1 << i );
        }

        setProcessAffinity( nProcessorMask );
    }
    //----------------------------------------------------------
    void OS::setProcessAffinity( osl::u32 nProcessorMask )
    {
#ifdef __linux__
        cpu_set_t st;
        CPU_ZERO( &st );

        bool bValid = false;

        for( osl::u32 i = 0; i < 32; ++i )
        {
            if( ( nProcessorMask & ( 1 << i ) ) != 0 )
            {
                CPU_SET( i, &st );

                bValid = true;
            }
        }

        if( !bValid )
        {
            CPU_SET( 0, &st );
        }

        ::sched_setaffinity( 0, sizeof( cpu_set_t ), &st );
#endif
    }
    //----------------------------------------------------------
    osl::u32 OS::getProcessAffinity()
    {
#ifdef __linux__
        cpu_set_t st;
        CPU_ZERO( &st );

        osl::u32 nProcessorMask = 0;

        if( sched_getaffinity( 0, sizeof( cpu_set_t ), &st ) == 0 )
        {
            for( osl::u32 i = 0; i < 32; ++i )
            {
                if( CPU_ISSET( i, &st ) )
                {
                    nProcessorMask |= ( 1 << i );
                }
            }
        }

        return nProcessorMask;
#endif
		return 0;
    }
    //----------------------------------------------------------
    bool OS::getSystemMemoryMB( u32* Total, u32* Avail )
    {
#ifdef __linux__
        long ps = sysconf( _SC_PAGESIZE );
        long pp = sysconf( _SC_PHYS_PAGES );
        long ap = sysconf( _SC_AVPHYS_PAGES );

        if ( ( ps == -1 ) || ( pp == -1 ) || ( ap == -1 ) )
        {
            return false;
        }

        if ( Total )
        {
            *Total = ( ( ps * ( long long )pp ) >> 20 );
        }

        if ( Avail )
        {
            *Avail = ( ( ps * ( long long )ap ) >> 20 );
        }
#endif
        return true;
    }
    //----------------------------------------------
    u64 OS::getTotalMemoryMB()
    {
        return s_sysInfo.getTotalMemory() >> 20;
    }
    //----------------------------------------------
    void OS::getCpuUsage( CPUUsagInfo* pCpuUsageInfo )
    {
        s_sysInfo.getCpuUsage( pCpuUsageInfo );
    }
    //----------------------------------------------
    void OS::getMemoryUsage( MemoryUsageInfo* pMemoryUsageInfo )
    {
        s_sysInfo.getMemoryUsage( pMemoryUsageInfo );
    }
    //----------------------------------------------
    void OS::getNetFaceSpeed( const char* szDev, struct NetSpeedInfo* pSpeedInfo )
    {
        s_sysInfo.getNetFaceSpeed( szDev, pSpeedInfo );
    }
    //----------------------------------------------
    void OS::getLoadAvr( LoadAverage* pstLA )
    {
        s_sysInfo.getLoadAvr( pstLA );
    }
    //----------------------------------------------------------
    void OS::msSleep( u32 nMilliseconds )
    {
        usleep( nMilliseconds * 1000 );
    }

    //----------------------------------------------------------
    void OS::pause()
    {
        //system( "pause" );
        ::pause();
    }

    //----------------------------------------------------------
    void OS::usSleep( u32 nUSeconds )
    {
        usleep( nUSeconds );
    }
    //----------------------------------------------------------
    ProcessHandle OS::getCurrentProcessHandle()
    {
        return getpid();
    }
    //----------------------------------------------------------
    bool OS::closeProcess( ProcessHandle hProcess )
    {
        kill( hProcess, 9 );
        return true;
    }
    //----------------------------------------------------------
    u32 OS::getNumMaxIOV()
    {
        return sysconf( _SC_IOV_MAX );
    };//namespace
    //----------------------------------------------------------
    void OS::setEnvironmentString( const char* szKey, const char* szValue )
    {
        setenv( szKey, szValue, true );
    }
    //----------------------------------------------------------
    StringA OS::getEnvironmentString( const char* szKey )
    {
        const char* szBuf = getenv( szKey );

        if ( szBuf )
        {
            return szBuf;
        }

        return StringUtil::BLANKA;
    }
    //----------------------------------------------------------
    StringA OS::getLastErrorString()
    {
        // Retrieve the system error message for the last-error code
        osl::OStringStreamA strError;

        // Display the error message and exit the process
        strError << "error id:" << errno << " desc:";

        switch( errno )
        {
            case EACCES:
                {
                    strError << "Permission denied (POSIX.1)";
                };
            case EAGAIN :
                {
                    strError << "EAGAIN. would block.";
                }
                break;
            default:
                strError << "unknown";
                break;
        };

        return strError.str();
    }

	StringA OS::getCurrentUserFolderPath()
	{

		return StringUtil::BLANKA;
	}

	//----------------------------------------------------------
	void OS::initialize()
	{

	}

	//----------------------------------------------------------
	void OS::uninitialize()
	{

	}
};//namespace
#endif
