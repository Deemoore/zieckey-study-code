
#include "osl/include/test_common.h"

#include <iostream>
#include <string>

namespace
{
    void test_std_string_append()
    {
        std::string s;
        const char* s1 = "errno=0\r\n";
        const char* s2 = "mid=731d8949087ebf6cb8b85a49779cab51\r\n";
        s.append(s1);
        s.append(s2);
        H_TEST_ASSERT(s.size() == strlen(s1) + strlen(s2));
    }
}

TEST_UNIT(trivial_test)
{
    test_std_string_append();
}
