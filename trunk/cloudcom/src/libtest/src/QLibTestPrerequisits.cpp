
#include "libtest/include/QLibTestPrerequisits.h"



#ifdef H_OS_WINDOWS
#	ifdef H_DEBUG_MODE
#		pragma comment(lib,"libcurld_imp.lib")
#	else
#		pragma comment(lib,"libcurl_imp.lib")
#	endif
    #ifdef H_OS_WINCE
    #	pragma comment(lib,"Ws2.lib")
    #else
    #	pragma comment(lib,"Ws2_32.lib")
    #endif
#endif

