
#include "osl/include/test_common.h"
#include "osl/include/auto_delete.h"
#include <iostream>

namespace
{
    void test_auto_free()
    {
        char* p = (char*)malloc(1024);
        H_TEST_ASSERT(p);
        {
            osl::ext::auto_free<char> p_auto_free(p);
            (void)p_auto_free;
        }
        H_TEST_ASSERT(p == NULL);
    }

    void test_auto_delete()
    {
        char* p = new char;
        H_TEST_ASSERT(p);
        {
            osl::ext::auto_delete<char> p_auto_delete(p);
            (void)p_auto_delete;
        }
        H_TEST_ASSERT(p == NULL);
    }


    void test_auto_delete_array()
    {
        char* p = new char[1024];
        H_TEST_ASSERT(p);
        {
            osl::ext::auto_delete_array<char> p_auto_delete(p);
            (void)p_auto_delete;
        }
        H_TEST_ASSERT(p == NULL);
    }
}

TEST_UNIT(test_auto_free_delete)
{
    test_auto_free();
    test_auto_delete();
    test_auto_delete_array();
}

