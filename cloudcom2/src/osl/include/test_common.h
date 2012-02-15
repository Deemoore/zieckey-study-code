#include <cppunit/extensions/HelperMacros.h>

#define TEST_UNIT( name ) \
    class CppUnitTestObjectClass_##name : public CppUnit::TestFixture \
    {\
        CPPUNIT_TEST_SUITE(CppUnitTestObjectClass_##name);\
        CPPUNIT_TEST(test_func_CppUnitTestObjectClass_##name);\
        CPPUNIT_TEST_SUITE_END();\
        public:\
        void setUp(){}\
        void tearDown(){}\
        void test_func_CppUnitTestObjectClass_##name ();\
    };\
    CPPUNIT_TEST_SUITE_REGISTRATION(CppUnitTestObjectClass_##name);\
    void CppUnitTestObjectClass_##name::test_func_CppUnitTestObjectClass_##name ()

#define H_TEST_ASSERT CPPUNIT_ASSERT