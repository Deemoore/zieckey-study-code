#ifndef _OSLIB_GETOPT_H_
#define _OSLIB_GETOPT_H_

#if ( defined(__linux__) || defined( __gnu_linux__) || defined(__GNUC__) )
#include <unistd.h>
#else

#include "osl/include/inner_pre.h"

//TODO error test failed!
    #ifdef __cplusplus
    extern "C" {
    #endif

        _EXPORT_OSLIB extern char* optarg;
        _EXPORT_OSLIB extern int  optind;
        _EXPORT_OSLIB extern int  opterr;
        _EXPORT_OSLIB extern int  optopt;
        _EXPORT_OSLIB int getopt(int argc, char** argv, char* optstr);

    #ifdef __cplusplus
    }
#endif//end of __GNUC_

#endif

#endif
