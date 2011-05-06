#include <stdio.h>
typedef unsigned int u_int;
#include <sys/sysctl.h>

int main( int argc, char* argv[] )
{
    int mib[4];
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_PATHNAME;
    mib[3] = -1;
    char buf[1024];
    size_t cb = sizeof(buf);
    sysctl(mib, 4, buf, &cb, NULL, 0);

    printf( "path:%s\n", buf );

    return 0;
}


