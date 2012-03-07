#include "libtest/include/inner_pre.h"

#include "libtest/include/test_object.h"
#include "osl/include/file_util.h"
#include "osl/include/utility.h"

namespace LibTest
{
    class TFileUtil : public ITestObject
    {
    public:
        virtual const char* getCommand()
        {
            return "test_fileutil";
        }
        virtual const char* getDesc()
        {
            return "test_fileutil";
        }
        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
        virtual void testAll();

    private:
        void test1();
        void test_getFiles();
    };



    void TFileUtil::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        testAll();
    }

    void TFileUtil::testAll()
    {
        test_getFiles();
    }

    void TFileUtil::test_getFiles()
    {
        {
            osl::StringAList files;
            osl::FileUtil::getFiles( ".", files );
            std::cout << "osl::FileUtil::getFiles( \".\", files ):\n";
            std::copy( files.begin() , files.end() , std::ostream_iterator<osl::StringA>( std::cout , "\n" ) );
        }

        {
            osl::StringAList files;
            osl::Util::listAllFiles( "../..", files, 0 );
            std::cout << "\n\n\nosl::FileUtil::listAllFiles( \"../..\", files, 0 ):\n";
            std::copy( files.begin() , files.end() , std::ostream_iterator<osl::StringA>( std::cout , "\n" ) );
        }


        {
            osl::StringAList files;
            osl::Util::listAllFiles( "../..", files, 1 );
            std::cout << "\n\n\nosl::FileUtil::listAllFiles( \"../..\", files, 1 ):\n";
            std::copy( files.begin() , files.end() , std::ostream_iterator<osl::StringA>( std::cout , "\n" ) );
        }


        {
            osl::StringAList files;
            osl::Util::listAllFiles( "../..", files, 2 );
            std::cout << "\n\n\nosl::FileUtil::listAllFiles( \"../..\", files, 2 ):\n";
            std::copy( files.begin() , files.end() , std::ostream_iterator<osl::StringA>( std::cout , "\n" ) );
        }
    }

} // end of namespace LibTest



CREATE_FUNCTION( TFileUtil );


