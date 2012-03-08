
#include "osl/include/test_common.h"
#include <iostream>
#include <string>

namespace
{
    static bool g_print_string = false;
    static bool g_print_int = false;
    static bool g_print_double = false;
    class Base
    {
    public:
        virtual void print(const std::string& message) = 0;
    };

    class Derive : public Base
    {
    public:
        virtual void print(const std::string& message)
        {
            //std::cout << "print(const std::string& message) : " << message << std::endl;
            g_print_string = true;
        }

        void print(int i)
        {
            //std::cout << "print(int i) : " << i << std::endl;
            g_print_int = true;
        }


        void print(double f)
        {
            //std::cout << "print(double f) : " << d << std::endl;
            g_print_double = true;
        }
    };
}

TEST_UNIT(virturl_function_override_test)
{
    Derive d;
    d.print(1);
    d.print("aaaaa");
    d.print(1.003f);
    H_TEST_ASSERT(g_print_string);
    H_TEST_ASSERT(g_print_int);
    H_TEST_ASSERT(g_print_double);
}
