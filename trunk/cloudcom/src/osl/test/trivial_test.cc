
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
        char* p10 = &s[0];
        H_TEST_ASSERT(s == "1234567890");
        s.resize(5);
        char* p5 = &s[0];
        H_TEST_ASSERT(s == "12345");
        s.resize(8);
        char* p8 = &s[0];
        H_TEST_ASSERT(p8 == p5 && p5 == p10);
        H_TEST_ASSERT(strncmp(s.data(), "12345", 5) == 0);
        s.resize(100);
        char* p100 = &s[0];
        H_TEST_ASSERT(strncmp(s.data(), "12345", 5) == 0);
        H_TEST_ASSERT(p100 != p8);
    }

    void test_std_string_assign_append()
    {
        unsigned char key1[] = {0x30, 0x81, 0x00, 0x02, 0x81, 0x81, 0x00, 0xe2, 0xc7, 0x68, 0x22, 0x2d, 0x8d, 0xbd, 0xb5, 0x0e};
        unsigned char key2[] = {0x30, 0x01, 0x00, 0x02, 0x00, 0x81, 0x00, 0xe2, 0xc7, 0x68, 0x22, 0x2d, 0x8d, 0xbd, 0xb5, 0x0e, 0xb5, 0x0e};
        std::string s1;
        std::string s2;
        s1 = std::string((char*)key1, sizeof(key1));
        s2.assign((char*)key1, sizeof(key1));
        H_TEST_ASSERT(s1.size() == sizeof(key1));
        H_TEST_ASSERT(s2.size() == sizeof(key1));
        H_TEST_ASSERT(s1 == s2);
        H_TEST_ASSERT(memcmp(s1.data(), s2.data(), sizeof(key1)) == 0);

        const char* sz = "11111";
        s2.assign(sz);
        H_TEST_ASSERT(s2 == sz);

        s1.append((char*)key2, sizeof(key2));
        H_TEST_ASSERT(s1.length() == sizeof(key1) + sizeof(key2));
        unsigned char buf[1024] = {};
        memcpy(buf, (char*)key1, sizeof(key1));
        memcpy(buf + sizeof(key1), (char*)key2, sizeof(key2));
        H_TEST_ASSERT(memcmp(s1.data(), buf, s1.length()) == 0);
    }
}

TEST_UNIT(trivial_std_string_test)
{
    test_std_string_append();
    test_std_string_resize();
    test_std_string_assign_append();
}
