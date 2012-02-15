#pragma once

#include "libtest/include/test_object.h"


namespace LibTest
{

#define s_pLibTest (TLibTest::getSingletonPtr() )
    class TLibTest : public osl::Thread, public osl::Singleton<TLibTest>
    {
        H_DEF_MAP( osl::StringA , ITestObjectPtr, ITestObjectPtrMap );
		ITestObjectPtrMap m_mapTestUnit;
        typedef ITestObjectPtrMap::iterator Iterator;
    public:
        TLibTest( void );
        ~TLibTest( void );

        void processCommand( const osl::StringA& );

        void onShellCommand( osl::AppShell::Command* pCmd, osl::AppShell* pShell );

        void showCommandDescriptions();

        void runAllTestUnit( osl::AppShell::Command* pCmd, osl::AppShell* pShell );

        virtual bool start();

        H_DEF_LIST( ITestObjectPtr, ITestObjectPtrList );
        static ITestObjectPtrList* getTestObjectList();

    private:
        //osl::Thread
        void run();
        void update();

        void initialize();
        void uninitialize();

        void registerTestUnit( ITestObject* object );

        void registerAllTestUnit(); //! register all you command here

        void registerOSLibTestUnit();
        void registerNetworkTestUnit();
		void registerCommonTestUnit();
        void registerAppUtilTestUnit();
		void registerTools();

    private:
        osl::AppShell* m_pShell;

        TLibTest( const TLibTest& );
        TLibTest& operator=( const TLibTest& );
        osl::MiniLock     m_lkObject;
        osl::StringList   m_CmdList;
    };

} // end of namespace LibTest


/**
* @param cmd - the command name
*/
#define TEST( cmd ) \
class TestObject##cmd : public LibTest::ITestObject\
{\
public:\
    virtual const char* getCommand() {return #cmd;}\
    virtual const char* getDesc() {return #cmd " the desc";}\
    virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell ){testAll();}\
    void testAll();\
};\
struct MagicClass##cmd\
{\
    MagicClass##cmd()\
    {\
        LibTest::TLibTest::ITestObjectPtrList* objlist = LibTest::TLibTest::getTestObjectList();\
        objlist->push_back( H_NEW TestObject##cmd() );\
    }\
} MagicClass##cmd##instance;\
    void TestObject##cmd::testAll()
 

/**
* @param cmd - the command name
* @param cmddesc - the command description 
* @note we can process more parameters
*/
#define TEST_INVOKE( cmd, cmddesc ) \
class TestObject##cmd : public LibTest::ITestObject\
{\
public:\
    virtual const char* getCommand() {return #cmd;}\
    virtual const char* getDesc() {return #cmddesc;}\
    virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );\
    void testAll(){}\
};\
struct MagicClass##cmd\
{\
    MagicClass##cmd()\
    {\
        LibTest::TLibTest::ITestObjectPtrList* objlist = LibTest::TLibTest::getTestObjectList();\
        objlist->push_back( H_NEW TestObject##cmd() );\
    }\
} MagicClass##cmd##instance;\
    void TestObject##cmd::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
     
