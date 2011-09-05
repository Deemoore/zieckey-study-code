
#include <string.h>

#include "hello.h"

char const* greet()
{
       return "hello, world";
}

void fill( Result& r)
{
    memset(r.a, 'a', sizeof(r.a) );
    memset(r.a, 'b', sizeof(r.b) );
    r.a[sizeof(r.a) - 1] = 0;
    r.b[sizeof(r.b) - 1] = 0;
}
