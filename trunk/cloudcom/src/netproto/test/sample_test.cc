
#include "osl/include/test_common.h"

#include <iostream>

TEST_UNIT(sample_test)
{
    std::cout << "Sample Test OK!\n";

    H_TEST_ASSERT(printf("Please using H_TEST_ASSERT instead of assert, H_ASSERT, CPPUNIT_ASSERT!\n"));
    H_TEST_ASSERT(false || printf("If assert failed, we can use printf to print this some error message, because printf return int!\n"));
}
