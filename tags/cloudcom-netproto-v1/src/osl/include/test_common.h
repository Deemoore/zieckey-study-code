#include <cppunit/extensions/HelperMacros.h>

/**
 *    How to write a unit test: 
 *    Please see <code>osl/test/sample_test.cc</code>
 *
 *    Usage:
 *
 *    TEST_UNIT(sample_test)
 *    {
 *        int a = 1;
 *        int b = a;
 *        H_TEST_ASSERT(a == b);
 *        int c = a + b;
 *        H_TEST_ASSERT(c == a + b);
 *
 *        H_TEST_ASSERT(printf("Please using H_TEST_ASSERT instead of assert, H_ASSERT, CPPUNIT_ASSERT!\n"));
 *        H_TEST_ASSERT(false || printf("If assert failed, we can use printf to print this some error message, because printf return int!\n"));
 *    }
 */

#define TEST_UNIT( name ) \
    class CppUnitTestObjectClass_##name : public CppUnit::TestFixture \
    {\
        CPPUNIT_TEST_SUITE(CppUnitTestObjectClass_##name);\
        CPPUNIT_TEST(test_func_CppUnitTestObjectClass_##name);\
        CPPUNIT_TEST_SUITE_END();\
        public:\
            void setUp(){}\
            void tearDown(){}\
        private:\
            void test_func_CppUnitTestObjectClass_##name ();\
    };\
    CPPUNIT_TEST_SUITE_REGISTRATION(CppUnitTestObjectClass_##name);\
    void CppUnitTestObjectClass_##name::test_func_CppUnitTestObjectClass_##name()

#define H_TEST_ASSERT CPPUNIT_ASSERT



