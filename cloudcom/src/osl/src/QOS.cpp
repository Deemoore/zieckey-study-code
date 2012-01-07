#include "osl/include/QOSLibPrerequisits.h"

#include "osl/include/QMemAlloc.h"
#include "osl/include/QString.h"
#include "osl/include/QStringUtil.h"
#include "osl/include/QFileUtil.h"

#include "osl/include/QMyOS.h"


#ifdef H_OS_WINDOWS
#	include <direct.h>
#elif defined( H_OS_FREEBSD )
#	include <sys/sysctl.h>
#elif defined( H_OS_LINUX )
#endif

namespace osl
{


    

    /////////////////////////////////////////////////////////////
    //                            OS
    /////////////////////////////////////////////////////////////
    ////----------------------------------------------------------
    //OS* OS::m_pOS = NULL;
    ////----------------------------------------------------------
    //OS::OS()
    //{

    //}
    ////----------------------------------------------------------
    //const wchar_t* OS::getOperationSystemVersion()
    //{
    //
    //}
    ////----------------------------------------------------------
    //void OS::copyToClipboard(const String& strText )
    //{

    //}
    ////----------------------------------------------------------
    //String OS::getTextFromClipboard()
    //{
    //	//return m_pImpl->getTextFromClipboard();
    //}
    ////----------------------------------------------------------
    //u64 OS::getProcessorSpeedMHz()
    //{
    //
    //}
    ////----------------------------------------------------------
    //bool OS::getSystemMemory(u32* Total, u32* Avail)
    //{

    //}
    ////----------------------------------------------------------
    //void OS::sleep( u32 nMilliseconds )
    //{
    //
    //}

    StringA OS::getBinDir( bool bWithEndSlash /*= false */ )
    {
		static char* s_szBinDirWithNoEndSlash = NULL;
        static char* s_szBinDirWithEndSlash = NULL;

		if( !s_szBinDirWithNoEndSlash )
		{
            static char bufWithNoEndSlash[ 1024 ]={0};
            static char bufWithEndSlash[ 1024 ]={0};

#ifdef H_OS_WINDOWS
			::GetModuleFileNameA( NULL, bufWithNoEndSlash, sizeof ( bufWithNoEndSlash ) );
#elif defined( H_OS_FREEBSD )
			{
				int mib[4];
				mib[0] = CTL_KERN;
				mib[1] = KERN_PROC;
				mib[2] = KERN_PROC_PATHNAME;
				mib[3] = -1;
				size_t cb = sizeof(bufWithNoEndSlash);
				int ret = sysctl(mib, 4, bufWithNoEndSlash, &cb, NULL, 0);
                if ( 0 != ret )
                {
                    fprintf( stderr, "sysctl called failed, errno=%d %s", errno, strerror( errno ) );
                }
			}
#elif defined(H_OS_LINUX)
			int count = readlink ( "/proc/self/exe", bufWithNoEndSlash, 1024 );
			if ( count < 0 || count >= 1024 )
			{
				printf ( "Failed to %s\n", __func__ );
				return "";
			}
			bufWithNoEndSlash[ count ] = '\0';

#endif
			osl::StringA qualifiedName = bufWithNoEndSlash;
			osl::StringA outBasename;
			osl::StringA outPath;
			osl::FileUtil::splitFileName ( qualifiedName, outBasename, outPath, true );
			//std::replace( outPath.begin(), outPath.end(), '\\', '/' );

            /*
            fprintf( stdout, "fullpath=%s\n", bufWithNoEndSlash );
            fprintf( stdout, "outPath=%s\n", outPath.c_str() );
            fprintf( stdout, "outBasename=%s\n", outBasename.c_str() );
            */

            if ( 0 == outPath.length() || 0 == strlen( bufWithNoEndSlash ) )
            {
                outPath = "./";
                fprintf( stderr, "getBinDir() error, we cannot get the binary directly dir: %s\n", bufWithNoEndSlash );
            }

			// copy string.
			strncpy( bufWithEndSlash, outPath.c_str(), outPath.length() );
			bufWithEndSlash[outPath.length()] = 0;

			strncpy( bufWithNoEndSlash, outPath.c_str(), outPath.length() - 1 );
			bufWithNoEndSlash[outPath.length() - 1] = 0;

            s_szBinDirWithNoEndSlash = bufWithNoEndSlash;
            s_szBinDirWithEndSlash   = bufWithEndSlash;
		}

		if ( bWithEndSlash )
		{
			return s_szBinDirWithEndSlash;
		}
		else
		{
			return s_szBinDirWithNoEndSlash;
		}
	}

	StringA OS::getConfDir()
	{
		static char* s_szConfDir = NULL;
		static char buf[ 1024 ]={0};
		if ( s_szConfDir )
		{
			return s_szConfDir;
		}

		StringA strConfDir = OS::getFullPathDir( "etc", 4 );
		strncpy( buf, strConfDir.c_str(), strConfDir.length() );
		s_szConfDir = buf;
		return s_szConfDir;


		//-----------------------------------------------------------
		//-----------------------------------------------------------
		//-----------------------------------------------------------
		// old implement
		// 		static char* s_szConfDir = NULL;
		// 
		// 		if( !s_szConfDir )
		// 		{
		// 			// 1.  bin/xxx.exe         ../etc/xxx.cfg
		// 			// 2.  bin/Debug/xxx.exe   ../etc/xxx.cfg
		// 			// 3.  bin/Debug/xxx.exe   ../../etc/xxx.cfg
		// 			// 4.  xxx.exe             ./etc/xxx.cfg
		// 
		// 			static char buf[ 1024 ]={0};
		// 			
		// 			
		// 			osl::StringA strBinDir = getBinDir();
		// 			//const char* szBinDir = strBinDir.c_str();
		// 
		// 			// test
		// 			{
		// 				osl::StringA strExt = "/etc";
		// 				osl::u32 iDepth = 0;
		// 				
		// 				do
		// 				{
		// 					osl::StringA strTest = osl::FileUtil::concatenatePath( strBinDir, strExt );
		// 					if( FileUtil::isFSFileExist( strTest ) )
		// 					{
		// 						strcpy( buf, strTest.c_str() );
		// 						s_szConfDir = buf;
		// 						break;
		// 					}
		// 
		// 					strExt = "/.." + strExt;
		// 
		// 				}while( iDepth++ < 4 );
		// 
		// 				if( !s_szConfDir )
		// 				{
		// 					strcpy( buf, strBinDir.c_str() );
		// 					s_szConfDir = buf;
// 				}
// 			}
// 		}
// 
// 		return s_szConfDir;
    }



    StringA OS::getFullPathDir( const StringA& strFolderName, u32 nDepth /*= 0*/ )
    {

        StringA strCurDir = getBinDir();

        u32 iDepth = 0;
        do
        {
            StringA strTest = FileUtil::concatenatePath( strCurDir, strFolderName );
            if( FileUtil::isFSFileExist( strTest ) )
            {
                return strTest;
            }

            strCurDir = FileUtil::getParentDirName( strCurDir, true );

        } while( iDepth++ < nDepth );

        return "";
    }


    osl::StringA OS::getCurrentUserName()
    {

#ifdef H_OS_WINDOWS
        char sz[128]={};
    	DWORD dwLen = 127;
        if( GetUserNameA( sz , &dwLen ) )
        {
            return sz;
        }
        else
        {
            return StringUtil::BLANKA;
        }
#elif defined(H_OS_LINUX)
        const char* pUserName = getlogin();
        if( pUserName )
        {
            return osl::StringA( pUserName );
        }
        else
        {
            return StringUtil::BLANKA;
        }
#endif
    }

    ThreadID OS::getCurrentThreadId()
    {
#ifdef H_OS_WINDOWS
        return ::GetCurrentThreadId();
#else
        return ::pthread_self();
#endif
    }
};//namespace



