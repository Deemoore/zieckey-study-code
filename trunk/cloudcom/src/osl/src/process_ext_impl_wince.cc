#include "osl/include/inner_pre.h"


#include "osl/include/mem_alloc.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"
#include "osl/include/file_util.h"
#include "osl/include/process_ext.h"

#ifdef H_OS_WINCE

namespace osl
{
    StringA Process::getOperationSystemVersion()
    {
        assert(false && "Not support!");
        return "";
    }
    
    StringA Process::getTextFromClipboard()
    {
        assert(false && "Not support!");
        return "";
	}
	//---------------------------------------------------------
	StringA Process::getDisplayDriverName()
	{
        assert(false && "Not support!");
        return "";
	}
	//----------------------------------------------------------
	StringA Process::getDisplayCardName()
	{
        assert(false && "Not support!");
        return "";
	}
	//----------------------------------------------------------
	StringA Process::getProcessorName()
	{
        assert(false && "Not support!");
        return "";
	}
    //----------------------------------------------------------
    f64 Process::getProcessorFrequencyMHz()
    {
        assert(false && "Not support!");
        return 0.0;
	}
    //----------------------------------------------------------
    f64 Process::getProcessorFrequency()
    {
        return getProcessorFrequencyMHz() * ( 1 << 20 );
    }
    //----------------------------------------------------------
    u32 Process::getNumProcessor()
    {
        assert(false && "Not support!");
        return 0;
    }
    //----------------------------------------------------------
    void Process::setMaxProcessorNumber( osl::u32 nNum )
    {
        assert(false && "Not support!");
    }
    //----------------------------------------------------------
    void Process::setProcessAffinity( osl::u32 nProcessorMask )
    {
        assert(false && "Not support!");
    }
    //----------------------------------------------------------
    osl::u32 Process::getProcessAffinity( )
    {
        assert(false && "Not support!");
        return osl::u32( -1 );
    }
    //----------------------------------------------------------
    bool Process::getSystemMemoryMB( u32* Total, u32* Avail )
	{
		assert(false && "Not support!");
			return false;
	}
    //----------------------------------------------
    u64 Process::getTotalMemoryMB()
    {
assert(false && "Not support!");
return 0;
    }
    //----------------------------------------------

    void Process::getCpuUsage( CPUUsagInfo* pCpuUsageInfo )
    {
assert(false && "Not support!");
    }
    //----------------------------------------------
    void Process::getMemoryUsage( MemoryUsageInfo* pMemoryUsageInfo )
    {
        assert(false && "Not support!");
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
        assert(false && "Not support!");
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
        assert(false && "Not support!");
    }
    //----------------------------------------------------------
    StringA Process::getEnvironmentString( const char* szKey )
    {
        assert(false && "Not support!");
        return StringUtil::BLANKA;
    }
    //----------------------------------------------------------
    StringA Process::getLastErrorString()
    {
#ifdef H_OS_WINCE
        assert(false && "Not support!");
        return "";
#else

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
#endif
    }

	StringA Process::getCurrentUserFolderPath()
	{
        assert(false && "Not support!");
        return StringUtil::BLANKA;
	}
};//namespace


#endif // if windows.

