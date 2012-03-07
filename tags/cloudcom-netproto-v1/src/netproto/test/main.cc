#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "netproto/include/exp.h"

#ifdef H_OS_WINDOWS
#	ifdef H_DEBUG_MODE
#		pragma comment(lib,"cppunitd_dll.lib")
#	else
#		pragma comment(lib,"cppunit_dll.lib")
#	endif
#	pragma comment(lib,"Ws2_32.lib")
#endif

int main(int argc, char* argv[])
{
    // Get the top level suite from the registry
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    // Adds the test to the list of test to run
    CppUnit::TextUi::TestRunner runner;

    runner.addTest( suite );

    // Change the default outputter to a compiler error format outputter
    runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(), std::cerr ) );

    // Run the tests.
    bool wasSucessful = runner.run();

#ifdef H_OS_WINDOWS
    system( "pause" );
#endif

    // Return error code 1 if the one of test failed.
    return wasSucessful ? 0 : 1;
} 
