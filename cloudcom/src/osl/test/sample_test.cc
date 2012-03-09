
#include "osl/include/test_common.h"

#include <iostream>

namespace
{
    void test()
    {
        const char* page_info = " 1 , 5 , 7 ";
        int type = atoi(page_info);
        H_TEST_ASSERT(type == 1);

        const char* pos = strchr(page_info, ',');
        H_TEST_ASSERT(pos);
        int start = atoi(pos + 1);
        H_TEST_ASSERT(start == 5);

        pos = strchr(pos + 1, ',');
        H_TEST_ASSERT(pos);
        int end = atoi(pos + 1);
        H_TEST_ASSERT(end == 7);
    }
}

TEST_UNIT(sample_test)
{
//     std::cout << "Sample Test OK!\n";
// 
//     H_TEST_ASSERT(printf("Please using H_TEST_ASSERT instead of assert, H_TEST_ASSERT, CPPUNIT_ASSERT!\n"));
//     H_TEST_ASSERT(false || printf("If assert failed, we can use printf to print this some error message, because printf return int!\n"));

    test();
}
