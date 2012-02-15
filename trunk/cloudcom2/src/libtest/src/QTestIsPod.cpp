
#include "libtest/include/QLibTestPrerequisits.h"
#include "libtest/include/QTestObject.h"
using namespace osl;
using namespace std;
namespace
{
    class TestIsPod : public LibTest::ITestObject
    {

        void testAll();
        const char* getCommand();
        const char* getDesc();
        void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );

        void test_is_pod();
    };

    void TestIsPod::testAll()
    {
        test_is_pod();
		puts( "test_ispod success!" );
    }

    const char* TestIsPod::getCommand()
    {
        return "test_ispod";
    }

    const char* TestIsPod::getDesc()
    {
        return "test_ispod";
    }

    void TestIsPod::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        testAll();
    }

    template<class T>
    T TestTypeStream( T& val )
    {
        osl::MemoryDataStream file;
        file << val;

        T retval;  
        file >> retval;
		H_ASSERT( 0 == memcmp( &val , &retval , sizeof(T) ) );
        return retval;
    }
    template<class T>
    void TestTypeStream( )
    {
        osl::MemoryDataStream file;
        T val;
        file << val;

        T retval;  
        file >> retval;
		H_ASSERT( 0 == memcmp( &val , &retval , sizeof(T) ) );
    }
#define OUTPUT_TYPE_IS_POD_VALUE(x,t) H_ASSERT( t == stdext::is_pod<x>::value ) ;
    void TestIsPod::test_is_pod()
    {


    }


}

CREATE_FUNCTION( TestIsPod );



