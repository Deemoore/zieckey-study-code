#include "osl/include/inner_pre.h"


#include "osl/include/malloc_micro.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"
#include "osl/include/file_util.h"
#include "osl/include/process_ext.h"

#ifdef H_OS_WINDOWS
#	include "emmintrin.h"

#   ifdef __MINGW32__
#		define H_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX
#       include "basetyps.h"
#       include "io.h"
#   endif

#elif defined(H_OS_LINUX)

#	include <stdint.h>

#else

#endif




#ifdef H_OS_WINDOWS

#include "Psapi.h"
#pragma comment( lib, "Psapi.lib")

#include <shlobj.h>
#include <psapi.h> 

// 尝试从WMI获取，但是还是很不准确
//#define _WIN32_DCOM
//#include <iostream>
//using namespace std;
//#include <comdef.h>
//#include <Wbemidl.h>
//# pragma comment(lib, "wbemuuid.lib") 

namespace osl
{

    //----------------------------------------------------------
    StringA Process::getOperationSystemVersion()
    {
        bool IsNonNTWindows = false;

        OSVERSIONINFOEXA osvi;
        BOOL bOsVersionInfoEx;

        ZeroMemory( &osvi, sizeof( OSVERSIONINFOEXA ) );
        osvi.dwOSVersionInfoSize = sizeof( OSVERSIONINFOEXA );

        OStringStreamA strRet;
        bOsVersionInfoEx = GetVersionExA ( ( OSVERSIONINFOA* ) & osvi );

        if ( !bOsVersionInfoEx )
        {
            osvi.dwOSVersionInfoSize = sizeof( OSVERSIONINFOA );

            if ( ! GetVersionExA ( ( OSVERSIONINFOA * ) &osvi ) )
            {
                return strRet.str();
            }
        }

        switch ( osvi.dwPlatformId )
        {
            case VER_PLATFORM_WIN32_NT:

//				{
//					if ( osvi.dwMajorVersion <= 4 )
//					{
//						strRet << ( "Microsoft Windows NT " );
//
//					}
//
//					if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
//					{
//						strRet << ( "Microsoft Windows 2000 " );
//
//					}
//
//					if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
//					{
//						strRet << ( "Microsoft Windows XP " );
//
//					}
//
//					if ( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0 )
//					{
//						strRet << ( "Microsoft Windows Vista " );
//
//					}
//
//					if ( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1 )
//					{
//						strRet << ( "Microsoft Windows 7 " );
//
//					}
//
//					if ( bOsVersionInfoEx )
//					{
//#ifdef VER_SUITE_ENTERPRISE
//
//						if ( osvi.wProductType == VER_NT_WORKSTATION )
//						{
//#ifndef __BORLANDC__
//
//							if ( osvi.wSuiteMask & VER_SUITE_PERSONAL )
//							{
//								strRet << ( ( "Personal " ) );
//							}
//							else
//							{
//								strRet << ( ( "Professional " ) );
//							}
//
//#endif
//						}
//						else if ( osvi.wProductType == VER_NT_SERVER )
//						{
//							if ( osvi.wSuiteMask & VER_SUITE_DATACENTER )
//							{
//								strRet << ( ( "DataCenter Server " ) );
//							}
//							else if ( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
//							{
//								strRet << ( ( "Advanced Server " ) );
//							}
//							else
//							{
//								strRet << ( ( "Server " ) );
//							}
//						}
//
//#endif
//					}
//					else
//					{
//						HKEY hKey;
//						HCHAR szProductType[80];
//						DWORD dwBufLen;
//
//						RegOpenKeyExA( HKEY_LOCAL_MACHINE,
//							( "SYSTEM\\CurrentControlSet\\Control\\ProductOptions" ),
//							0, KEY_QUERY_VALUE, &hKey );
//						RegQueryValueExA( hKey, ( "ProductType" ), NULL, NULL,
//							( LPBYTE ) szProductType, &dwBufLen );
//						RegCloseKey( hKey );
//
//						if ( stricmp( ( "WINNT" ), szProductType ) == 0 )
//						{
//							strRet << ( ( "Professional " ) );
//						}
//
//						if ( stricmp( ( "LANMANNT" ), szProductType ) == 0 )
//						{
//							strRet << ( ( "Server " ) );
//						}
//
//						if ( stricmp( ( "SERVERNT" ), szProductType ) == 0 )
//						{
//							strRet << ( ( "Advanced Server " ) );
//						}
//					}
//
//					// Display version, service pack (if any), and build number.
//					if ( osvi.dwMajorVersion <= 4 )
//					{
//						strRet << ( "version " ) << osvi.dwMajorVersion
//							<< ( "." ) << osvi.dwMinorVersion
//							<< ( " " ) << osvi.szCSDVersion
//							<< ( " (Build " ) << ( osvi.dwBuildNumber & 0xFFFF ) << ( ")" );
//					}
//					else
//					{
//						strRet << osvi.szCSDVersion << ( " (Build" ) << ( osvi.dwBuildNumber & 0xFFFF ) << ( ")" );
//					}
//				}

				{

					SYSTEM_INFO si;
					ZeroMemory(&si, sizeof(SYSTEM_INFO));
					GetSystemInfo(&si);

					strRet << ( ( "Microsoft " ) );

					// Test for the specific product.
					if (osvi.dwMajorVersion == 6)
					{
						if (osvi.dwMinorVersion == 0)
						{
							if (osvi.wProductType == VER_NT_WORKSTATION)
							{	
								strRet << ( ( "Windows Vista " ) );
							}
							else
							{	
								strRet << ( ( "Windows Server 2008 " ) );
							}
						}
						else if (osvi.dwMinorVersion == 1)
						{
							if (osvi.wProductType == VER_NT_WORKSTATION)
							{	
								strRet << ( ( "Windows 7 " ) );
							}
							else
							{	
								strRet << ( ( "Windows Server 2008 R2 " ) );
							}
						}
						if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
						{
							strRet << ( ( ", 64-bit" ) );
						}
						else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
						{
							strRet << ( ( ", 32-bit" ) );
						}
					}

					if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
					{
						if (GetSystemMetrics(SM_SERVERR2))
						{
							strRet << ( ( "Windows Server 2003 R2, " ) );
						}
						else if (osvi.wSuiteMask == VER_SUITE_STORAGE_SERVER)
						{
							strRet << ( ( "Windows Storage Server 2003 " ) );
						}
						else if (osvi.wProductType == VER_NT_WORKSTATION
							&& si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
						{
							strRet << ( ( "Windows XP Professional x64 Edition " ) );
						}
						else
						{
							strRet << ( ( "Windows Server 2003, " ) );
						}

						// Test for the server type.
						if (osvi.wProductType != VER_NT_WORKSTATION)
						{
							if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
							{
								if ((osvi.wSuiteMask & VER_SUITE_DATACENTER) == VER_SUITE_DATACENTER)
								{
									strRet << ( ( "Datacenter Edition for Itanium-based Systems " ) );
								}
								else if ((osvi.wSuiteMask & VER_SUITE_ENTERPRISE) == VER_SUITE_ENTERPRISE)
								{
									strRet << ( ( "Enterprise Edition for Itanium-based Systems " ) );
								}
							}
							else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
							{
								if ((osvi.wSuiteMask & VER_SUITE_DATACENTER) == VER_SUITE_DATACENTER)
								{
									strRet << ( ( "Datacenter x64 Edition " ) );
								}
								else if ((osvi.wSuiteMask & VER_SUITE_ENTERPRISE) == VER_SUITE_ENTERPRISE)
								{
									strRet << ( ( "Enterprise x64 Edition " ) );
								}
								else
								{
									strRet << ( ( "Standard x64 Edition " ) );
								}
							}
							else
							{
								if ((osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER) == VER_SUITE_COMPUTE_SERVER)
								{
									strRet << ( ( "Compute Cluster Edition " ) );
								}
								else if ((osvi.wSuiteMask & VER_SUITE_DATACENTER) == VER_SUITE_DATACENTER)
								{
									strRet << ( ( "Datacenter Edition " ) );
								}
								else if ((osvi.wSuiteMask & VER_SUITE_ENTERPRISE) == VER_SUITE_ENTERPRISE)
								{
									strRet << ( ( "Enterprise Edition " ) );
								}
								else if ((osvi.wSuiteMask & VER_SUITE_BLADE) == VER_SUITE_BLADE)
								{
									strRet << ( ( "Web Edition " ) );
								}
								else
								{
									strRet << ( ( "Standard Edition " ) );
								}
							}
						}
					}
					if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
					{
						strRet << ( ( "Windows XP " ) );
						if ((osvi.wSuiteMask & VER_SUITE_PERSONAL) == VER_SUITE_PERSONAL)
						{
							strRet << ( ( "Home Edition " ) );
						}
						else
						{
							strRet << ( ( "Professional " ) );
						}
					}

					if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
					{
						strRet << ( ( "Windows 2000 " ) );
						if (osvi.wProductType == VER_NT_WORKSTATION)
						{
							strRet << ( ( "Professional " ) );
						}
						else
						{
							if ((osvi.wSuiteMask & VER_SUITE_DATACENTER) == VER_SUITE_DATACENTER)
							{
								strRet << ( ( "Datacenter Server " ) );
							}
							else if ((osvi.wSuiteMask & VER_SUITE_ENTERPRISE) == VER_SUITE_ENTERPRISE)
							{
								strRet << ( ( "Advanced Server " ) );
							}
							else
							{
								strRet << ( ( "Server " ) );
							}
						}
					}
					// Include service pack (if any) and build number.
					UINT uLen = strlen(osvi.szCSDVersion);
					if (uLen > 0)
					{
						strRet << ( ( " " ) );
						strRet << osvi.szCSDVersion;
					}

					char szBuf[80];
					sprintf(szBuf, " (build %d)", osvi.dwBuildNumber);
					strRet << szBuf;
				}

                break;

            case VER_PLATFORM_WIN32_WINDOWS:

                IsNonNTWindows = true;

                if ( osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0 )
                {
                    strRet << ( ( "Microsoft Windows 95 " ) );

                    if ( osvi.szCSDVersion[1] == H_STR( 'C' ) || osvi.szCSDVersion[1] == H_STR( 'B' ) )
                    {
                        strRet << ( ( "OSR2 " ) );
                    }
                }

                if ( osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10 )
                {
                    strRet << ( ( "Microsoft Windows 98 " ) );

                    if ( osvi.szCSDVersion[1] == ( 'A' ) )
                    {
                        strRet << ( ( "SE " ) );
                    }
                }

                if ( osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90 )
                {
                    strRet << ( ( "Microsoft Windows Me " ) );
                }

                break;

            case VER_PLATFORM_WIN32s:

                IsNonNTWindows = true;
                strRet << ( ( "Microsoft Win32s " ) );
                break;
        }

        return strRet.str();
    }
    //----------------------------------------------------------
    bool Process::copyToClipboard( const StringA& strText )
    {
        if ( !OpenClipboard( NULL ) || strText.size() == 0 )
        {
            return false;
        }

        EmptyClipboard();

        HGLOBAL clipbuffer = GlobalAlloc( GMEM_DDESHARE, strText.size() + 1 );
		if ( clipbuffer )
		{
			char * buffer = ( char* )GlobalLock( clipbuffer );

			if ( buffer)
			{
				strcpy( buffer, strText.c_str() );
			}
			GlobalUnlock( clipbuffer );
			SetClipboardData( CF_TEXT, clipbuffer );
		}
		else
		{

		}
		CloseClipboard();
		return true;
    }
    //----------------------------------------------------------
    StringA Process::getTextFromClipboard()
    {
        if ( !OpenClipboard( NULL ) )
        {
            return 0;
        }

        char * buffer = 0;

        HANDLE hData = GetClipboardData( CF_TEXT );
        buffer = ( char* )GlobalLock( hData );
        GlobalUnlock( hData );
        CloseClipboard();

        return buffer;
	}
	//----------------------------------------------------------
	StringA Process::getDisplayDriverName()
	{
		HRESULT hr;
		f64 fMHz = 0;

		HKEY Key;
		hr = RegOpenKeyExA( HKEY_LOCAL_MACHINE,
			( "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E968-E325-11CE-BFC1-08002BE10318}\\0000" ),
			0, KEY_READ, &Key );

		if ( hr == ERROR_SUCCESS )
		{
			DWORD dwSize=255,dwType=REG_SZ;
			char StringProviderName[256];
			char StringDriverVersion[256]; 
			char StringDriverDate[256]; 
			char String[1024];

			memset(String, 0, sizeof(char)*1024);

			hr = RegQueryValueExA( Key, ( "ProviderName" ), NULL, NULL, ( LPBYTE ) & StringProviderName, &dwSize );
			dwSize = 256;
			hr = RegQueryValueExA( Key, ( "DriverVersion" ), NULL, NULL, ( LPBYTE ) & StringDriverVersion, &dwSize );
			dwSize = 256;
			hr = RegQueryValueExA( Key, ( "DriverDate" ), NULL, NULL, ( LPBYTE ) & StringDriverDate, &dwSize );

			strcpy(String, StringProviderName);
			strcat(String, " Display Driver . Ver ");
			strcat(String, StringDriverVersion);
			strcat(String, ". Data ");
			strcat(String, StringDriverDate);

			RegCloseKey( Key );

			return String;
		}

		return "unknown";
	}
	//----------------------------------------------------------
	StringA Process::getDisplayCardName()
	{
		HRESULT hr;
		f64 fMHz = 0;

		HKEY Key;
		hr = RegOpenKeyExA( HKEY_LOCAL_MACHINE,
			( "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E968-E325-11CE-BFC1-08002BE10318}\\0000" ),
			0, KEY_READ, &Key );

		if ( hr == ERROR_SUCCESS )
		{
			DWORD dwSize=255,dwType=REG_SZ;
			char String[255];

			hr = RegQueryValueExA( Key, ( "DriverDesc" ), NULL, NULL, ( LPBYTE ) & String, &dwSize );

			RegCloseKey( Key );

			return String;
		}

		return "unknown";
	}
	//----------------------------------------------------------
	StringA Process::getProcessorName()
	{
		HRESULT hr;
		f64 fMHz = 0;

		HKEY Key;
		hr = RegOpenKeyExA( HKEY_LOCAL_MACHINE,
			( "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0" ),
			0, KEY_READ, &Key );

		if ( hr == ERROR_SUCCESS )
		{
			DWORD dwSize=255,dwType=REG_SZ;
			char String[256]; 

			hr = RegQueryValueExA( Key, ( "ProcessorNameString" ), NULL, NULL, ( LPBYTE ) & String, &dwSize );

			RegCloseKey( Key );

			return String;
		}

		return "unknown";
	}
    //----------------------------------------------------------
    f64 Process::getProcessorFrequencyMHz()
    {
        HRESULT hr;
        f64 fMHz = 0;

        HKEY Key;
        hr = RegOpenKeyExA( HKEY_LOCAL_MACHINE,
                            ( "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0" ),
                            0, KEY_READ, &Key );

        if ( hr == ERROR_SUCCESS )
        {
            DWORD nSpeed = 0;
            DWORD Size = sizeof( nSpeed );
            hr = RegQueryValueExA( Key, ( "~MHz" ), NULL, NULL, ( LPBYTE ) & nSpeed, &Size );

            fMHz = nSpeed;

            RegCloseKey( Key );
        }

        return fMHz;
	}
    //----------------------------------------------------------
    f64 Process::getProcessorFrequency()
    {
        return getProcessorFrequencyMHz() * ( 1 << 20 );
    }
    //----------------------------------------------------------
    u32 Process::getNumProcessor()
    {
        SYSTEM_INFO sysInfo;
        ::GetSystemInfo( &sysInfo );
        return sysInfo.dwNumberOfProcessors;
    }
    //----------------------------------------------------------
    void Process::setMaxProcessorNumber( osl::u32 nNum )
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
    void Process::setProcessAffinity( osl::u32 nProcessorMask )
    {
        // validate mask.
        {
            osl::u32 nCurProcessMask = 0;
            osl::u32 nSysMask = 0;

            if( !::GetProcessAffinityMask( ::GetCurrentProcess(), ( PDWORD_PTR )&nCurProcessMask, ( PDWORD_PTR )&nSysMask ) )
            {
                nSysMask = osl::u32( -1 );

                // log
                {
                    osl::OStringStreamA strTip;
                    strTip << "Process::setProcessAffinity " << " GetProcessAffinityMask " << Process::getLastErrorString();
                    ///H_LOG_NAME_ERROR( "sys", strTip.str() );
                }
            }

            if( ( nSysMask & nProcessorMask ) == 0 )
            {
                nProcessorMask = nSysMask;
            }
        }

        if( !::SetProcessAffinityMask( ::GetCurrentProcess(), ( DWORD_PTR )nProcessorMask ) )
        {
            // log
            {
                osl::OStringStreamA strTip;
                strTip << "Process::setProcessAffinity " << " SetProcessAffinityMask " << Process::getLastErrorString();
                //H_LOG_NAME_ERROR( "sys", strTip.str() );
            }
        }
    }
    //----------------------------------------------------------
    osl::u32 Process::getProcessAffinity( )
    {
        osl::u32 nProcessMask = 0;
        osl::u32 nSysMask = 0;

        if( ::GetProcessAffinityMask( ::GetCurrentProcess(), ( PDWORD_PTR )&nProcessMask, ( PDWORD_PTR )&nSysMask ) )
        {
            return nProcessMask;
        }

        // log
        {
            osl::OStringStreamA strTip;
            strTip << "Process::getProcessAffinity " << " GetProcessAffinityMask " << Process::getLastErrorString();
            //H_LOG_NAME_ERROR( "sys", strTip.str() );
        }

        return osl::u32( -1 );
    }
    //----------------------------------------------------------
    bool Process::getSystemMemoryMB( u32* Total, u32* Avail )
	{
		MEMORYSTATUSEX MemoryStatus;
		MemoryStatus.dwLength = sizeof( MEMORYSTATUSEX );


		if( GlobalMemoryStatusEx( &MemoryStatus ) )
		{
			if ( Total )
			{
				*Total = ( u32 )( MemoryStatus.ullTotalPhys >> 20 );
			}

			if ( Avail )
			{
				*Avail = ( u32 )( MemoryStatus.ullAvailPhys >> 20 );
			}
			return true;
		}
		else
		{
			return false;
		}
	}
    //----------------------------------------------
    u64 Process::getTotalMemoryMB()
    {

		MEMORYSTATUSEX MemoryStatus;
		MemoryStatus.dwLength = sizeof( MEMORYSTATUSEX );

        // cannot fail
        GlobalMemoryStatusEx( &MemoryStatus );

        H_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;

        return ( MemoryStatus.ullTotalPhys >> 20 );
    }
    //----------------------------------------------

#define SystemBasicInformation 0
#define SystemPerformanceInformation 2
#define SystemTimeInformation 3
#define SystemProcessInformation 5
#define SystemProcessorPerformanceInformation 8

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))

	typedef struct
	{
		LARGE_INTEGER liIdleTime;
		DWORD dwSpare[150];
	} SYSTEM_PERFORMANCE_INFORMATION;

	typedef struct
	{
		LARGE_INTEGER liKeBootTime;
		LARGE_INTEGER liKeSystemTime;
		LARGE_INTEGER liExpTimeZoneBias;
		ULONG uCurrentTimeZoneId;
		DWORD dwReserved;
	} SYSTEM_TIME_INFORMATION;

	//typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION {
	//	LARGE_INTEGER IdleTime;
	//	LARGE_INTEGER KernelTime;
	//	LARGE_INTEGER UserTime;
	//	LARGE_INTEGER DpcTime;
	//	LARGE_INTEGER InterruptTime;
	//	ULONG InterruptCount;
	//} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION, *PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

	/// 时间转换  
	static unsigned __int64 file_time_2_utc(const FILETIME* ftime)  
	{  
		LARGE_INTEGER li;  

		assert(ftime);  
		li.LowPart = ftime->dwLowDateTime;  
		li.HighPart = ftime->dwHighDateTime;  
		return li.QuadPart;  
	}  

	// ntdll!NtQuerySystemInformation (NT specific!)
	typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);

	PROCNTQSI NtQuerySystemInformation;

	static CPUUsagInfo   s_cpuUsageInfo = {0,0};
	void Process::updataCpuUsage( void )
	{
		// get number of processors in the system
		static int processor_count_ = -1;  

		if(processor_count_ == -1)  
		{  
			SYSTEM_INFO info;  
			GetSystemInfo(&info); 
			processor_count_ = (int)info.dwNumberOfProcessors;  
		}  

		// 1、获取系统总的CPU占用率
		// NtQuerySystemInformation

		static LARGE_INTEGER s_liOldIdleTime = {0,0};
		static LARGE_INTEGER s_liOldSystemTime = {0,0};
		//static double s_dbOldKernelTime = 0;
		//static double s_dbOldSystemTime = 0;
		//static double s_dbOldIdleTime = 0;

		SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
		SYSTEM_TIME_INFORMATION SysTimeInfo;

		double dbIdleTime = 0;
		double dbSystemTime = 0;
		double dbKernelTime = 0;
		//double dbCurrentKernelTime = 0;
		//double dbCurrentIdleTime = 0;
		//double dbCurrentSystemTime = 0;

		LONG status;
// 		ULONG ulSize;
// 		int idx;

		NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandleA("ntdll"),"NtQuerySystemInformation");

		if (!NtQuerySystemInformation)
			return;

		// get new system time
		status = NtQuerySystemInformation(SystemTimeInformation,&SysTimeInfo,sizeof(SysTimeInfo),0);
		if (status!=NO_ERROR)
			return;

		// get new CPU's idle time
		status =NtQuerySystemInformation(SystemPerformanceInformation,&SysPerfInfo,sizeof(SysPerfInfo),NULL);
		if (status != NO_ERROR)
			return;

		// get each Processor info
		//SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION l_cpuinfo[33];
		//memset(&l_cpuinfo, 0, sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION)*33);
		//status = NtQuerySystemInformation(SystemProcessorPerformanceInformation, &l_cpuinfo, sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * processor_count_, &ulSize);
		//if (status != NO_ERROR)
		//	return;

		//for (idx=0, dbCurrentKernelTime=0; idx<1; ++idx) {
		//	dbCurrentKernelTime += Li2Double(l_cpuinfo[idx].KernelTime);
		//}
		//for (idx=0, dbCurrentIdleTime=0; idx<1; ++idx) {
		//	dbCurrentIdleTime += Li2Double(l_cpuinfo[idx].IdleTime);
		//}
		//for (idx=0, dbCurrentSystemTime=0; idx<1; ++idx) {
		//	dbCurrentSystemTime += Li2Double(l_cpuinfo[idx].KernelTime);
		//	dbCurrentSystemTime += Li2Double(l_cpuinfo[idx].UserTime);
		//}

		// if it's a first call - skip it
		if (s_liOldIdleTime.QuadPart != 0)
	//	if (s_dbOldIdleTime != 0)
		{
			// CurrentValue = NewValue - OldValue
			dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(s_liOldIdleTime);
			dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(s_liOldSystemTime);
		//	dbIdleTime = dbCurrentIdleTime - s_dbOldIdleTime;
		//	dbSystemTime = dbCurrentSystemTime - s_dbOldSystemTime;
		//	dbKernelTime = dbCurrentKernelTime - s_dbOldKernelTime;

			if (dbSystemTime>0)
			{
				// CurrentCpuIdle = IdleTime / SystemTime
				dbIdleTime = dbIdleTime / dbSystemTime;
				dbKernelTime = dbKernelTime / dbSystemTime;

				// CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors
			//	dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)processor_count_; /* + 0.5; */
			//	dbKernelTime = 100.0 - dbKernelTime * 100.0 / (double)processor_count_; /* + 0.5; */

				s_cpuUsageInfo.system = 1.0f - (dbIdleTime / (double)processor_count_);
			}
		}

		// store new CPU's idle and system time
		s_liOldIdleTime = SysPerfInfo.liIdleTime;
		s_liOldSystemTime = SysTimeInfo.liKeSystemTime;
	//	s_dbOldKernelTime = dbCurrentKernelTime;
	//	s_dbOldSystemTime = dbCurrentSystemTime;
	//	s_dbOldIdleTime = dbCurrentIdleTime;


		// 2、获取进程的CPU占用率

		//上一次的时间  
		static __int64 s_dbOldUserTime = 0; 

		FILETIME creation_time;  
		FILETIME exit_time;  
		FILETIME kernel_time;  
		FILETIME user_time;  
		double dbUserTime = 0;
		double dbCurrentUserTime = 0;

		if (!GetProcessTimes(GetCurrentProcess(), &creation_time, &exit_time,  
			&kernel_time, &user_time))  
		{  
			// We don't assert here because in some cases (such as in the Task Manager)  
			// we may call this function on a process that has just exited but we have  
			// not yet received the notification.  
			return ;  
		}  
		dbCurrentUserTime = double(file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time)); 

		if (s_dbOldUserTime == 0)  
		{  
			// First call, just set the last values.  
			s_dbOldUserTime = dbCurrentUserTime;  
			return ;  
		}  

		dbUserTime = dbCurrentUserTime - s_dbOldUserTime;  

		if (dbUserTime <= 0 || dbSystemTime <= 0)  
		{
			s_dbOldUserTime = dbCurrentUserTime;  
			return ;  
		}

		// We add time_delta / 2 so the result is rounded.    
		s_dbOldUserTime = dbCurrentUserTime;  

		s_cpuUsageInfo.proc = (dbUserTime / dbSystemTime) / (double)processor_count_;

		//{
		//	//上一次的时间  
		//	static __int64 s_dbOldUserTime = 0; 

		//	FILETIME creation_time;  
		//	FILETIME exit_time;  
		//	FILETIME kernel_time;  
		//	FILETIME user_time;  
		//	double dbUserTime = 0;

		//	int cpu = -1;  

		//	if (!GetProcessTimes(GetCurrentProcess(), &creation_time, &exit_time,  
		//		&kernel_time, &user_time))  
		//	{  
		//		// We don't assert here because in some cases (such as in the Task Manager)  
		//		// we may call this function on a process that has just exited but we have  
		//		// not yet received the notification.  
		//		return ;  
		//	}  
		//	dbUserTime = double(file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time)) / processor_count_; 

		//	if ((last_system_time_ == 0) || (last_time_ == 0))  
		//	{  
		//		// First call, just set the last values.  
		//		last_system_time_ = system_time;  
		//		last_time_ = time;  
		//		return ;  
		//	}  

		//	system_time_delta = system_time - last_system_time_;  
		//	time_delta = time - last_time_;  

		//	if (time_delta == 0)  
		//		return ;  

		//	// We add time_delta / 2 so the result is rounded.  
		//	cpu = (int)((system_time_delta * 100 + time_delta / 2) / time_delta);  
		//	last_system_time_ = system_time;  
		//	last_time_ = time;  

		//	s_cpuUsageInfo.proc = double(cpu)*0.01f;
		//}

		// 尝试从WMI获取，但是还是很不准确
		//{
		//	static unsigned __int64 last_time_ = 0;  
		//	static unsigned __int64 last_system_time_ = 0;  

		//	FILETIME now;
		//	unsigned __int64 system_time = 0;
		//	unsigned __int64 time = 0;
		//	unsigned __int64 system_time_delta = 0;
		//	unsigned __int64 time_delta = 0;

		//	GetSystemTimeAsFileTime(&now); 
		//	time = file_time_2_utc(&now);  

		//	{
		//		HRESULT hres;

		//		// Step 1: --------------------------------------------------
		//		// Initialize COM. ------------------------------------------

		//		hres =  CoInitializeEx(0, COINIT_APARTMENTTHREADED); 
		//		if (FAILED(hres))
		//		{
		//			cout << "Failed to initialize COM library. Error code = 0x" 
		//				<< hex << hres << endl;
		//			return ;                  // Program has failed.
		//		}

		//		// Step 2: --------------------------------------------------
		//		// Set general COM security levels --------------------------
		//		// Note: If you are using Windows 2000, you need to specify -
		//		// the default authentication credentials for a user by using
		//		// a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
		//		// parameter of CoInitializeSecurity ------------------------

		//		hres =  CoInitializeSecurity(
		//			NULL, 
		//			-1,                          // COM authentication
		//			NULL,                        // Authentication services
		//			NULL,                        // Reserved
		//			RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		//			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		//			NULL,                        // Authentication info
		//			EOAC_NONE,                   // Additional capabilities 
		//			NULL                         // Reserved
		//			);


		//		if (FAILED(hres) && hres!=RPC_E_TOO_LATE)
		//		{
		//			cout << "Failed to initialize security. Error code = 0x" 
		//				<< hex << hres << endl;
		//			CoUninitialize();
		//			return ;                    // Program has failed.
		//		}

		//		// Step 3: ---------------------------------------------------
		//		// Obtain the initial locator to WMI -------------------------

		//		IWbemLocator *pLoc = NULL;

		//		hres = CoCreateInstance(
		//			CLSID_WbemLocator,             
		//			0, 
		//			CLSCTX_INPROC_SERVER, 
		//			IID_IWbemLocator, (LPVOID *) &pLoc);

		//		if (FAILED(hres))
		//		{
		//			cout << "Failed to create IWbemLocator object."
		//				<< " Err code = 0x"
		//				<< hex << hres << endl;
		//			CoUninitialize();
		//			return ;                 // Program has failed.
		//		}

		//		// Step 4: -----------------------------------------------------
		//		// Connect to WMI through the IWbemLocator::ConnectServer method

		//		IWbemServices *pSvc = NULL;

		//		// Connect to the root\cimv2 namespace with
		//		// the current user and obtain pointer pSvc
		//		// to make IWbemServices calls.
		//		hres = pLoc->ConnectServer(
		//			_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		//			NULL,                    // User name. NULL = current user
		//			NULL,                    // User password. NULL = current
		//			0,                       // Locale. NULL indicates current
		//			NULL,                    // Security flags.
		//			0,                       // Authority (e.g. Kerberos)
		//			0,                       // Context object 
		//			&pSvc                    // pointer to IWbemServices proxy
		//			);

		//		if (FAILED(hres))
		//		{
		//			cout << "Could not connect. Error code = 0x" 
		//				<< hex << hres << endl;
		//			pLoc->Release();     
		//			CoUninitialize();
		//			return ;                // Program has failed.
		//		}

		//		cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;


		//		// Step 5: --------------------------------------------------
		//		// Set security levels on the proxy -------------------------

		//		hres = CoSetProxyBlanket(
		//			pSvc,                        // Indicates the proxy to set
		//			RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		//			RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		//			NULL,                        // Server principal name 
		//			RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		//			RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		//			NULL,                        // client identity
		//			EOAC_NONE                    // proxy capabilities 
		//			);

		//		if (FAILED(hres))
		//		{
		//			cout << "Could not set proxy blanket. Error code = 0x" 
		//				<< hex << hres << endl;
		//			pSvc->Release();
		//			pLoc->Release();     
		//			CoUninitialize();
		//			return ;               // Program has failed.
		//		}

		//		// Step 6: --------------------------------------------------
		//		// Use the IWbemServices pointer to make requests of WMI ----
		//		IEnumWbemClassObject* pEnumerator = NULL;
		//		hres = pSvc->ExecQuery(
		//			bstr_t("WQL"), 
		//			bstr_t("SELECT PercentProcessorTime FROM Win32_PerfRawData_PerfProc_Process WHERE name = 'HMain_d'"),
		//			WBEM_FLAG_RETURN_WBEM_COMPLETE/*WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY*/, 
		//			NULL,
		//			&pEnumerator);

		//		if (FAILED(hres))
		//		{
		//			cout << "Query for operating system name failed."
		//				<< " Error code = 0x" 
		//				<< hex << hres << endl;
		//			pSvc->Release();
		//			pLoc->Release();
		//			CoUninitialize();
		//			return ;               // Program has failed.
		//		}

		//		// Step 7: -------------------------------------------------
		//		// Get the data from the query in step 6 -------------------

		//		IWbemClassObject *pclsObj = 0;
		//		ULONG uReturn = 0;

		//		while (pEnumerator)
		//		{
		//			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, 
		//				&pclsObj, &uReturn);

		//			if(0 == uReturn)
		//			{
		//				pclsObj = 0;
		//				break;
		//			}

		//			VARIANT vtProp;
		//			VariantInit(&vtProp);

		//			// Get the value of the Name property
		//			hr = pclsObj->Get(L"PercentProcessorTime", 0, &vtProp, 0, 0);

		//			system_time = unsigned __int64(_wtoi64(vtProp.bstrVal));  

		//			VariantClear(&vtProp);

		//			pclsObj->Release();
		//		}

		//		// Cleanup
		//		// ========

		//		pSvc->Release();
		//		pLoc->Release();
		//		if (pEnumerator)
		//		{
		//			pEnumerator->Release();
		//		}
		//		//if (pclsObj)
		//		//{
		//		//	pclsObj->Release();
		//		//}
		//		CoUninitialize();
		//	} 

		//	if ((last_system_time_ == 0) || (last_time_ == 0))  
		//	{  
		//		// First call, just set the last values.  
		//		last_system_time_ = system_time;  
		//		last_time_ = time;  
		//		return ;  
		//	}  

		//	system_time_delta = system_time - last_system_time_;  
		//	time_delta = time - last_time_;  

		//	if (time_delta == 0)  
		//		return ;  

		//	//// We add time_delta / 2 so the result is rounded.  
		//	s_cpuUsageInfo.proc = double(system_time_delta * 100 / time_delta / processor_count_ )*0.01f; 

		//	last_system_time_ = system_time;  
		//	last_time_ = time;  
		//}
	}

    void Process::getCpuUsage( CPUUsagInfo* pCpuUsageInfo )
    {
		if (pCpuUsageInfo)
		{
			pCpuUsageInfo->system = s_cpuUsageInfo.system;
			pCpuUsageInfo->proc = s_cpuUsageInfo.proc;
		}
    }
    //----------------------------------------------
    void Process::getMemoryUsage( MemoryUsageInfo* pMemoryUsageInfo )
    {
		PROCESS_MEMORY_COUNTERS counters = { sizeof(PROCESS_MEMORY_COUNTERS) };

		HANDLE hProcess = GetCurrentProcess();

		if( GetProcessMemoryInfo( hProcess , &counters, counters.cb ) )
		{
			pMemoryUsageInfo->system      = counters.WorkingSetSize;
			pMemoryUsageInfo->procvirtual = counters.WorkingSetSize;
		}
		else
		{
			DWORD dw = GetLastError();

			assert( false && "Not Implemented Yet!" );
		}
		CloseHandle( hProcess );
    }
    //----------------------------------------------
    void Process::getNetFaceSpeed( const char* szDev, struct NetSpeedInfo* pSpeedInfo )
    {
        assert( false && "Not Implemented Yet!" );
    }
    //----------------------------------------------
    void Process::getLoadAvr( LoadAverage* pstLA )
    {
        assert( false && "Not Implemented Yet!" );
    }
    //----------------------------------------------------------
    void Process::msSleep( u32 nMilliseconds )
    {
        ::Sleep( nMilliseconds );
    }
    //----------------------------------------------------------
    void Process::usSleep( u32 nUSeconds )
    {
        ::Sleep( nUSeconds * 1000 );
    }

    //----------------------------------------------------------
    void Process::pause()
    {
        system( "pause" );
    }


    //----------------------------------------------
    ProcessHandle s_hMyProcess = 0;
    //----------------------------------------------------------
    ProcessHandle Process::getCurrentProcessHandle()
    {
        return s_hMyProcess;
    }
    //----------------------------------------------------------
    bool Process::closeProcess( ProcessHandle hProcess )
    {
        return ::TerminateProcess( hProcess, 0 ) ? true : false;
    }
    //----------------------------------------------------------
    void Process::initialize()
    {
        if ( s_hMyProcess == 0 )
        {
			HANDLE hProcess = GetCurrentProcess();
            ::DuplicateHandle(  hProcess , hProcess , hProcess, &s_hMyProcess, DUPLICATE_SAME_ACCESS  , FALSE, DUPLICATE_SAME_ACCESS  );
			CloseHandle( hProcess );
        }
    }
    //----------------------------------------------
    void Process::uninitialize()
    {
        if ( s_hMyProcess )
        {
            ::CloseHandle( s_hMyProcess );
            s_hMyProcess = 0;
        }
    }
    //----------------------------------------------------------
    u32 Process::getNumMaxIOV()
    {
        return 10;
    };//namespace
    //----------------------------------------------------------
    void Process::setEnvironmentString( const char* szKey, const char* szValue )
    {
        ::SetEnvironmentVariableA( szKey, szValue );
    }
    //----------------------------------------------------------
    StringA Process::getEnvironmentString( const char* szKey )
    {
        char szBuf[1024];

        if ( GetEnvironmentVariableA( szKey, szBuf, 1024 ) )
        {
            return szBuf;
        }

        return StringUtil::BLANKA;
    }
    //----------------------------------------------------------
    StringA Process::getLastErrorString()
    {
        // Retrieve the system error message for the last-error code
        osl::OStringStreamA strError;

        LPVOID lpMsgBuf;
        DWORD dw = ::GetLastError();

        ::FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
            ( LPSTR ) &lpMsgBuf,
            0, NULL );

        // Display the error message and exit the process
        strError << "error id:" << dw << "  desc:" << ( LPCSTR )lpMsgBuf;

        LocalFree( lpMsgBuf );

        return strError.str();
    }

	StringA Process::getCurrentUserFolderPath()
	{
		char szPath[MAX_PATH] ={};
		SHGetSpecialFolderPathA( 0 , szPath , CSIDL_PROFILE , FALSE );
		return szPath;
	}
};//namespace


#endif // if windows.

