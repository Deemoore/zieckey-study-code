#include "libtest/include/QLibTestPrerequisits.h"

#ifdef H_OS_WINDOWS
#include <direct.h> 
#endif 

#include "libtest/include/QTestOS.h"

namespace LibTest
{
    void TOS::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        testAll();
    }

    void TOS::testAll()
    {
        test();
        test_getFullPathDir();
    }

    using namespace osl;
    void TOS::test()
    {
        osl::AppShell* pShell = new osl::AppShell;
        {
            osl::u16 n = -1;
            osl::s32 b = ( osl::s16 )n;

            if ( b != -1 )
            {
                osl::StringStreamA strTip;
                strTip << "osl::u16(-1) to s32:" <<  b;

                H_LOG_NAME_INFO( "", strTip.str() );
            }

        }

        {
            osl::u16 n = -1;
            osl::s32 b = ( osl::s16 )n;

            if ( b != -1 )
            {
                osl::StringStreamA strTip;
                strTip << "osl::u16(-1) to s32:" <<  b;

                H_LOG_NAME_INFO( "", strTip.str() );
            }
        }


        {
            char szPath[512];
#ifdef H_OS_WINDOWS
            _getcwd( szPath, 512 );
#else
            getcwd( szPath, _MAX_PATH );
#endif

            H_LOG_INFO( pShell->getStdOut(), szPath );
        }

		{
			u32 nNumProcessor = osl::OS::getNumProcessor();

			if ( nNumProcessor == 0 )
			{
				H_LOG_ERROR( pShell->getErrorOut(), "OS getNumProcessor" );
			}
			else
			{
				osl::StringStreamA strTip;
				strTip << "OS getNumProcessor:" <<  nNumProcessor;
				H_LOG_ERROR( pShell->getStdOut(), strTip.str() );
			}
		}


		//
		{
			String strOSVersion =  osl::OS::getOperationSystemVersion();
			H_LOG_INFO( pShell->getStdOut(), strOSVersion );
		}


		{
			u32 nTotalMemory = osl::OS::getTotalMemoryMB();

			if ( nTotalMemory < ( 1 << 9 ) )
			{
				H_LOG_ERROR( pShell->getErrorOut(), "OS getTotalMemoryMB" );
			}
			else
			{
				osl::StringStreamA strTip;
				strTip << "OS getTotalMemoryMB:" <<  nTotalMemory;
				H_LOG_ERROR( pShell->getStdOut(), strTip.str() );
			}
		}


		{
			osl::u32 nMemEat = 0;
			// eat some memory
			std::vector<void*> vBufs;
			{
				while( nMemEat < ( 1 << 30 ) )
				{
					osl::u32 nSize = rand() * ( rand() % 1000 ) + 1;
					void* pMem = osl::MemAlloc::alloc( nSize );

					if( !pMem )
					{
						break;
					}

					nMemEat += nSize;
					vBufs.push_back( pMem );

				};
			}

			{
				u32 nTotalMemory = 0;
				u32 nAvailable   = 0;
				osl::OS::getSystemMemoryMB( &nTotalMemory, &nAvailable );
				{
					osl::StringStreamA strTip;
					strTip << "Eat mem: " << ( nMemEat >> 20 ) << " OS getTotalMemoryMB:" <<  nTotalMemory << "  Available; " << nAvailable;
					H_LOG_INFO( pShell->getStdOut(), strTip.str() );
				}
			}


			{
				std::vector<void*>::iterator it( vBufs.begin() ), ite( vBufs.end() );
				for(; it != ite; ++it )
				{
					osl::MemAlloc::free( *it );
				}
			}



			{
				u32 nTotalMemory = 0;
				u32 nAvailable   = 0;
				osl::OS::getSystemMemoryMB( &nTotalMemory, &nAvailable );
				{
					osl::StringStreamA strTip;
					strTip << "Return mem: " << ( nMemEat >> 20 ) << " OS getTotalMemoryMB:" <<  nTotalMemory << "  Available; " << nAvailable;
					H_LOG_INFO( pShell->getStdOut(), strTip.str() );
				}
			}
		}

	}

    void TOS::test_getFullPathDir()
    {
        osl::StringA strv2path = osl::OS::getFullPathDir( "v2", 10 );
        std::cout << "v2 path=" << strv2path.c_str() << std::endl;

        osl::StringA strconfpath = osl::OS::getConfDir();
        std::cout << "conf path=" << strconfpath.c_str() << std::endl;

        osl::StringA strserverpath = osl::OS::getFullPathDir( "server", 10 );
        std::cout << "server path=" << strserverpath.c_str() << std::endl;

        strconfpath = osl::OS::getConfDir();
        std::cout << "conf path=" << strconfpath.c_str() << std::endl;

        osl::StringA strbinpath = osl::OS::getFullPathDir( "bin", 10 );
        std::cout << "bin path=" << strbinpath.c_str() << std::endl;

        strconfpath = osl::OS::getConfDir();
        std::cout << "conf path=" << strconfpath.c_str() << std::endl;

        osl::StringA strtrunkpath = osl::OS::getFullPathDir( "trunk", 10 );
        std::cout << "trunk path=" << strtrunkpath.c_str() << std::endl;

        strconfpath = osl::OS::getConfDir();
        std::cout << "conf path=" << strconfpath.c_str() << std::endl;
    }
}

CREATE_FUNCTION( TOS );
