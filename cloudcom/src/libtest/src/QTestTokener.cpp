

#include "qlibtest/include/QLibTestPrerequisits.h"
#include "qlibtest/include/QLibTest.h"
#include "qoslib/include/QTokener.h"
namespace
{
	void test_0()
	{
		const char* text = "0";
		osl::Tokener token(text);
		osl::StringA s = token.nextSlice().toString();
		H_ASSERT(s == "0");

		text = "0\t";
		token.reset(text);
		s = token.nextSlice().toString();
		H_ASSERT(s == "0");
	}

	void test_1()
	{
		const char* text = "a\t\nb\t c\td";
		osl::Tokener token(text);
		osl::StringA s = token.nextString();
		H_ASSERT(s == "a");
		token.skipSpaces();
		s = token.nextString();
		H_ASSERT(s == "b");
		token.skipSpaces();
		s = token.nextString();
		H_ASSERT(s == "c");
		token.skipSpaces();
		s = token.nextString();
		H_ASSERT(s == "d");

		token.reset(text);
		token.skipSpaces();
		s = token.nextSlice().toString();
		H_ASSERT(s == "a");
		token.skipSpaces();
		s = token.nextSlice().toString();
		H_ASSERT(s == "b");
		token.skipSpaces();
		s = token.nextSlice().toString();
		H_ASSERT(s == "c");
		token.skipSpaces();
		s = token.nextSlice().toString();
		H_ASSERT(s == "d");
	}


}
TEST( test_tokener )
{
	test_0();
	test_1();

}

