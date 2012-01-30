
#include "osl/include/test_common.h"

#include <iostream>
#include <time.h>

TEST_UNIT(sample_test)
{
    std::cout << "Sample Test OK!\n";

    H_TEST_ASSERT(printf("Please using H_TEST_ASSERT instead of assert, H_ASSERT, CPPUNIT_ASSERT!\n"));
    H_TEST_ASSERT(false || printf("If assert failed, we can use printf to print this some error message, because printf return int!\n"));
}

TEST_UNIT(sample_a)
{
    {
        struct tm *newtime;
        __int64 ltime;
        char buff[80];

        _time64( &ltime );

        // Obtain coordinated universal time:
        newtime = _gmtime64( &ltime ); // C4996
        // Note: _gmtime64 is deprecated; consider using _gmtime64_s
        asctime_s( buff, sizeof(buff), newtime );
        printf( "Coordinated universal time is %s\n", buff );

    }
    time_t tnow = time(NULL);
    tm * p = gmtime(&tnow);
    tm mytm = *p;
    mytm.tm_hour = 1;
    time_t tother = mktime(&mytm);
    std::cout << tother;
}
