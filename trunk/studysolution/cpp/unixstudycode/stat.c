#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main( int argc, char* argv[] )
{
    struct stat st;
    const char* sockfile = "/home/weizili/memcached.sock";
    int ret = stat( sockfile, &st );
    if ( ret != 0 )
    {
        printf("%s not exist\n", sockfile);
        return 0;
    }


    if( S_ISSOCK(st.st_mode) )
    {
        printf("%s exist, and it is a socket\n", sockfile);
    }
    else
    {
        printf("%s exist, but it is not a socket\n", sockfile);
    }
    return 0;
}
