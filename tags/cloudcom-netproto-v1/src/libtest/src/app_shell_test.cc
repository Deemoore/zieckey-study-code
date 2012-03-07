#include "libtest/include/inner_pre.h"

#include "libtest/include/test_object.h"


namespace LibTest
{
    class TAppShell : public ITestObject
    {
    public:
        virtual const char* getCommand()
        {
            return "test_appshell";
        }
        virtual const char* getDesc()
        {
            return "test_appshell";
        }
        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
        virtual void testAll();

    private:
        void test();
    };
} // end of namespace LibTest


namespace LibTest
{
    void TAppShell::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        testAll();
    }

    void TAppShell::testAll()
    {
        test();
    }

    bool c_vArrived[5];


    void onCM1( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        c_vArrived[0] = true;
        std::cout << "cmd is:";
        pCmd->dump( std::cout );
    }
    void onCM2( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        c_vArrived[1] = true;
        std::cout << "cmd is:";
        pCmd->dump( std::cout );
    }
    void onCM3( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        c_vArrived[2] = true;
        std::cout << "cmd is:";
        pCmd->dump( std::cout );
    }
    void onCM4( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        c_vArrived[3] = true;
        std::cout << "cmd is:";
        pCmd->dump( std::cout );
    }
    void onCM5( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        c_vArrived[4] = true;
        std::cout << "cmd is:";
        pCmd->dump( std::cout );
    }



    void TAppShell::test()
    {
        osl::AppShell* pTShell = new osl::AppShell;
        memset( c_vArrived, 0, sizeof( c_vArrived ) );

        pTShell->registerCommand( "cm1", &onCM1, "cm1" );
        pTShell->registerCommand( "cm2", &onCM2, "cm2" );
        pTShell->registerCommand( "cm3", &onCM3, "cm3" );
        pTShell->registerCommand( "cm4", &onCM4, "cm4" );
        pTShell->registerCommand( "cm5", &onCM5, "cm5" );

        //
        {
            std::cout << std::endl << "Should be:" << "cm1 -12 --11 123 '456' \"789\" 'afadfad\"asdfasd\"'" << std::endl;
            pTShell->processCommand( "cm1 -12 --11 123 '456' \"789\" 'afadfad\"asdfasd\"' "  );
        }

        //
        {
            //std::cout << std::endl << "Should be:" << "cm1_1 \"'afa\"" << std::endl;
            //pTShell->processCommand( "cm1_1 \"'afa\""  );
        }

        {
            std::cout << std::endl << "Should be:" << "cm2 -ad --ac asdfa --ad=ddc target1 target2" << std::endl;
            pTShell->processCommand( "cm2 -ad --ac asdfa --ad=ddc target1 target2" );
        }

        {
            std::cout << std::endl << "Should be:" << "cm3 target1 -ad --ac asdfa --ad=ddc target1 target2 " << std::endl;
            pTShell->processCommand( "cm3 target1 -ad --ac asdfa --ad=ddc target1 target2" );
        }

        {
            std::cout << std::endl << "Should be:" << "cm4 target1 -ad --a\'c asdfa --ad=ddc target1 target2" << std::endl;
            pTShell->processCommand( "cm4 target1 -ad --a\\'c asdfa --ad=ddc target1 target2"  );
        }

        {
            std::cout << std::endl << "Should be:" << "cm5 target1 -ad --ca a\\'sdfa --ad=ddc target1 target2" << std::endl;
            pTShell->processCommand( "cm5 target1 -ad --ca a\\'sdfa --ad=ddc target1 target2" );
        }


        /// check
        {
            for ( int i = 0; i < 5; ++i )
            {
                if ( c_vArrived[i] != true )
                {
                    osl::OStringStream strTip;
                    strTip << "Appshell error on test:" << i;
                    //H_ASSERT()
                    H_LOG_ERROR( pTShell->getErrorOut(), strTip.str() );
                }
            }
        }

        delete pTShell;
    }

}//end of namespace LibTest


CREATE_FUNCTION( TAppShell );

