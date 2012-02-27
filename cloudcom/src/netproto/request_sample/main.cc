

#include "netproto/include/exp.h"

#include "message_request.h"


#ifdef H_OS_WINDOWS
#	ifdef H_DEBUG_MODE
#		pragma comment(lib,"cppunitd_dll.lib")
#		pragma comment(lib,"libcurld_imp.lib")
#       pragma comment(lib, "zlib_d.lib")
#	else
#		pragma comment(lib,"cppunit_dll.lib")
#		pragma comment(lib,"libcurl_imp.lib")
#       pragma comment(lib, "zlib.lib")
#	endif
#	pragma comment(lib,"Ws2_32.lib")
#endif

int main(int argc, char* argv[])
{
    const char* url = "http://build7.kill.corp.qihoo.net:8018/tutorial.php";
    const char* data = "0123456789";
    std::string result;

    if (do_http_request(url, data, result))
    {
        printf("Server response data:[%s]\n", result.data());
    }
    else
    {
        fprintf(stderr, "Error message:[%s]\n", result.data());
    }

    do_tutorial_test();
    do_p2sp_key_test();
    do_msv_test();

#ifdef H_OS_WINDOWS
    system( "pause" );
#endif

    // Return error code 1 if the one of test failed.
    return 0;
} 
