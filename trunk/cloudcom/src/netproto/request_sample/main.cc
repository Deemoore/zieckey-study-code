

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
#ifdef H_OS_WINDOWS
    system( "pause" );
#endif

    // Return error code 1 if the one of test failed.
    return 0;
} 
