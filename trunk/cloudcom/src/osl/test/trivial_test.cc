
#include "osl/include/test_common.h"
#include "osl/include/exp.h"

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
        char buf[1024] = {};
        snprintf(buf, sizeof(buf), "%s%s", s1, s2);
        H_TEST_ASSERT(s.size() == strlen(s1) + strlen(s2));
        H_TEST_ASSERT(s == buf);
    }

    void test_std_string_resize()
    {
        std::string s = "1234567890";
        s.resize(10);
        H_TEST_ASSERT(s == "1234567890");
        s.resize(5);
        H_TEST_ASSERT(s == "12345");
        s.resize(20);
        H_TEST_ASSERT(strncmp(s.data(), "12345", 5) == 0);
    }
}

TEST_UNIT(trivial_std_string_test)
{
    test_std_string_append();
    test_std_string_resize();
}
