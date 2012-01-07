#include "libtest/include/QLibTestPrerequisits.h"
#include "libtest/include/QLibTest.h"


using namespace osl;
using namespace net;

template<> LibTest::TLibTest* osl::Singleton<LibTest::TLibTest>::ms_Singleton = 0;


//! 需要和CREATE_FUNCTION一起使用
#define REGISTER_TEST(x)        registerTestUnit( Create_##x() );

#define DECLARATION_TEST(x)     LibTest::ITestObject* Create_##x();     

//qoslib
DECLARATION_TEST( TINIParser );
DECLARATION_TEST( TOS );
DECLARATION_TEST( TThreads );
DECLARATION_TEST( TMemoryDataStream );
DECLARATION_TEST( TThreadPool );
DECLARATION_TEST( TAppShell );
DECLARATION_TEST( TMemAlloc );
DECLARATION_TEST( TOS );
DECLARATION_TEST( TString );
DECLARATION_TEST( TThreads );
DECLARATION_TEST( TMemoryDataStream );
DECLARATION_TEST( TestIsPod );
DECLARATION_TEST( TestStl );
DECLARATION_TEST( TLog );
DECLARATION_TEST( TFileUtil );
DECLARATION_TEST( TBase64 );

//qnetworklib
DECLARATION_TEST( TCurl );

//
DECLARATION_TEST( TTrivial );

//apputil
DECLARATION_TEST( TCACenter );

//tools
DECLARATION_TEST( TLevelDBBenchAnalyse );


namespace LibTest
{

    TLibTest::ITestObjectPtrList* TLibTest::getTestObjectList()
    {
        if ( !aut::isAppUtilInitialized() )
        {
            osl::initializeOSLib();
            net::initializeNet();
            aut::initializeAppUtil();
        }
        
        static TLibTest::ITestObjectPtrList objlist;
        return &objlist;
    }

    TLibTest::TLibTest( void )
    {
        m_pShell = NULL;
    }

    TLibTest::~TLibTest( void )
    {
        m_mapTestUnit.clear();

        if ( m_pShell )
        {
            m_pShell->unref();
            m_pShell = NULL;
        }
    }

    void TLibTest::run()
    {
        while ( isRunning() )
        {
            update();
        }

        uninitialize();
    }

    void TLibTest::initialize()
    {
        if ( NULL == m_pShell )
        {
            m_pShell = new osl::AppShell();
            m_pShell->ref();
            //osl::preapreTestCommand( m_pShell );

            m_pShell->registerCommand( "test_all", osl::AppShell::CommandFunc( this, &TLibTest::runAllTestUnit ), "run all test-unit" );
        }
    }

    void TLibTest::uninitialize()
    {
        if ( m_pShell )
        {
            m_pShell->unref();
            m_pShell = NULL;
        }
    }

    bool TLibTest::start()
    {
        initialize();
        registerAllTestUnit();
        osl::Thread::start();
/*
        while ( !isRunning() )
        {
            osl::OS::msSleep( 5 );
        }
        */

        return true;
    }


    void TLibTest::update()
    {
        Iterator it( m_mapTestUnit.begin() ), ite( m_mapTestUnit.end() );

        for ( ; it != ite; it++ )
        {
            it->second->update();
        }

/*        s_pTimer->update();*/

        while ( !m_CmdList.empty() )
        {
            osl::StringA cmd = m_CmdList.front();
            {
                H_MINI_AUTOLOCK( m_lkObject );
                m_CmdList.pop_front();
            }
            m_pShell->processCommand( cmd );
        }

        osl::OS::msSleep( 5 );
    }

    void TLibTest::onShellCommand( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        Iterator iter = m_mapTestUnit.find( pCmd->getName() );

        if ( m_mapTestUnit.end() != iter )
        {
            iter->second->invoke( pCmd , pShell );
        }
    }

    void onShellCommandC( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        s_pLibTest->onShellCommand( pCmd , pShell );
    }

    void TLibTest::registerTestUnit( ITestObject* object )
    {
        m_mapTestUnit.insert( std::make_pair( object->getCommand() , object ) );
        m_pShell->registerCommand(  object->getCommand() , osl::AppShell::CommandFunc( &onShellCommandC ) , object->getDesc() );
    }

    void TLibTest::runAllTestUnit( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        {
            // test unit
            Iterator it( m_mapTestUnit.begin() ), ite( m_mapTestUnit.end() );

            for ( ; it != ite; it++ )
            {
                it->second->testAll();
            }
        }

        osl::AppShell::CommandMap::const_iterator it( m_pShell->getCommandMap().begin() ), ite( m_pShell->getCommandMap().end() );

        for ( ; it != ite; ++it )
        {
            // in case of recursive call.
            if ( it->first == "test_all" )
            {

                continue;
            }

            osl::StringA strCmd = it->first + osl::StringA( " -a" );
            std::cout << std::endl << "Run Command: " << strCmd << std::endl;
            m_pShell->processCommand( strCmd );
        }
    }


    void TLibTest::processCommand( const osl::StringA& cmd )
    {
        H_MINI_AUTOLOCK( m_lkObject );
        m_CmdList.push_back( cmd );
    }


    void TLibTest::showCommandDescriptions()
    {
        m_pShell->showCommandDescriptions();
    }

    void TLibTest::registerAllTestUnit()
    {
        ITestObjectPtrList* objlist = getTestObjectList();
        for ( ITestObjectPtrList::iterator it(objlist->begin()), ite(objlist->end()); it != ite; ++it )
        {
            registerTestUnit(*it);
        }
        
        registerOSLibTestUnit();
        registerNetworkTestUnit();
        registerCommonTestUnit();
        registerAppUtilTestUnit();
        registerTools();
    }

    void TLibTest::registerOSLibTestUnit()
    {
         REGISTER_TEST( TAppShell );
         REGISTER_TEST( TOS );
         REGISTER_TEST( TLog );
         REGISTER_TEST( TString );
         REGISTER_TEST( TThreads );
         REGISTER_TEST( TMemoryDataStream );
         REGISTER_TEST( TINIParser );
         REGISTER_TEST( TMemAlloc );
         REGISTER_TEST( TFileUtil );
         REGISTER_TEST( TBase64 );
         
         
    }

    void TLibTest::registerNetworkTestUnit()
    {

        //REGISTER_TEST( TCurl );

        //register your test unit here
    }


    void TLibTest::registerCommonTestUnit()
    {
       REGISTER_TEST( TTrivial );

        //register your test unit here
    }


	void TLibTest::registerTools()
	{
        REGISTER_TEST( TLevelDBBenchAnalyse );
	}

    void TLibTest::registerAppUtilTestUnit()
    {
        //REGISTER_TEST( TCACenter );
        
    }
} // end of namespace LibTest


