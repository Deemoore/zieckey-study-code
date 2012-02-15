#include "libtest/include/inner_pre.h"

#ifdef H_OS_WINDOWS
#include <direct.h> 
#endif 

#include "libtest/include/test_object.h"



namespace LibTest
{
    class TProcess : public ITestObject
    {
    public:
        virtual const char* getCommand()
        {
            return "test_os";
        }
        virtual const char* getDesc()
        {
            return "test_os";
        }
        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
        virtual void testAll();

    private:
        void test();
        void test_getFullPathDir();
    };
} // end of namespace LibTest


namespace LibTest
{
    void TProcess::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        testAll();
    }

    void TProcess::testAll()
    {
        test();
        test_getFullPathDir();
    }

    using namespace osl;
    void TProcess::test()
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
			u32 nNumProcessor = osl::Process::getNumProcessor();

			if ( nNumProcessor == 0 )
			{
				H_LOG_ERROR( pShell->getErrorOut(), "Process getNumProcessor" );
			}
			else
			{
				osl::StringStreamA strTip;
				strTip << "Process getNumProcessor:" <<  nNumProcessor;
				H_LOG_ERROR( pShell->getStdOut(), strTip.str() );
			}
		}


		//
		{
			String strOSVersion =  osl::Process::getOperationSystemVersion();
			H_LOG_INFO( pShell->getStdOut(), strOSVersion );
		}


		{
			u32 nTotalMemory = osl::Process::getTotalMemoryMB();

			if ( nTotalMemory < ( 1 << 9 ) )
			{
				H_LOG_ERROR( pShell->getErrorOut(), "Process getTotalMemoryMB" );
			}
			else
			{
				osl::StringStreamA strTip;
				strTip << "Process getTotalMemoryMB:" <<  nTotalMemory;
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
				osl::Process::getSystemMemoryMB( &nTotalMemory, &nAvailable );
				{
					osl::StringStreamA strTip;
					strTip << "Eat mem: " << ( nMemEat >> 20 ) << " Process getTotalMemoryMB:" <<  nTotalMemory << "  Available; " << nAvailable;
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
				osl::Process::getSystemMemoryMB( &nTotalMemory, &nAvailable );
				{
					osl::StringStreamA strTip;
					strTip << "Return mem: " << ( nMemEat >> 20 ) << " Process getTotalMemoryMB:" <<  nTotalMemory << "  Available; " << nAvailable;
					H_LOG_INFO( pShell->getStdOut(), strTip.str() );
				}
			}
		}

	}

    void TProcess::test_getFullPathDir()
    {
        osl::StringA strv2path = osl::Process::getFullPathDir( "v2", 10 );
        std::cout << "v2 path=" << strv2path.c_str() << std::endl;

        osl::StringA strconfpath = osl::Process::getConfDir();
        std::cout << "conf path=" << strconfpath.c_str() << std::endl;

        osl::StringA strserverpath = osl::Process::getFullPathDir( "server", 10 );
        std::cout << "server path=" << strserverpath.c_str() << std::endl;

        strconfpath = osl::Process::getConfDir();
        std::cout << "conf path=" << strconfpath.c_str() << std::endl;

        osl::StringA strbinpath = osl::Process::getFullPathDir( "bin", 10 );
        std::cout << "bin path=" << strbinpath.c_str() << std::endl;

        strconfpath = osl::Process::getConfDir();
        std::cout << "conf path=" << strconfpath.c_str() << std::endl;

        osl::StringA strtrunkpath = osl::Process::getFullPathDir( "trunk", 10 );
        std::cout << "trunk path=" << strtrunkpath.c_str() << std::endl;

        strconfpath = osl::Process::getConfDir();
        std::cout << "conf path=" << strconfpath.c_str() << std::endl;
    }
}

CREATE_FUNCTION( TProcess );
