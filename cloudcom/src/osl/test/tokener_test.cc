
#include "osl/include/test_common.h"

#include "osl/include/tokener.h"

namespace
{

    void test_token_0()
    {
        const char* text = "0";
        osl::Tokener token(text);
        osl::StringA s = token.nextSlice().toString();
        H_TEST_ASSERT(s == "0");

        text = "0\t";
        token.reset(text);
        s = token.nextSlice().toString();
        H_TEST_ASSERT(s == "0");
    }

    void test_token_1()
    {
        const char* text = "a\t\nb\t c\td";
        osl::Tokener token(text);
        osl::StringA s = token.nextString();
        H_TEST_ASSERT(s == "a");
        token.skipSpaces();
        s = token.nextString();
        H_TEST_ASSERT(s == "b");
        token.skipSpaces();
        s = token.nextString();
        H_TEST_ASSERT(s == "c");
        token.skipSpaces();
        s = token.nextString();
        H_TEST_ASSERT(s == "d");

        token.reset(text);
        token.skipSpaces();
        s = token.nextSlice().toString();
        H_TEST_ASSERT(s == "a");
        token.skipSpaces();
        s = token.nextSlice().toString();
        H_TEST_ASSERT(s == "b");
        token.skipSpaces();
        s = token.nextSlice().toString();
        H_TEST_ASSERT(s == "c");
        token.skipSpaces();
        s = token.nextSlice().toString();
        H_TEST_ASSERT(s == "d");
    }

}

TEST_UNIT( test_tokener )
{
    test_token_0();
    test_token_1();
}