#pragma once

#include "libtest/include/QTestObject.h"



namespace LibTest
{
    class TString : public ITestObject
    {
    public:
        virtual const char* getCommand()
        {
            return "test_string";
        }
        virtual const char* getDesc()
        {
            return "test_string";
        }
        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
        virtual void testAll();

    private:
        void test_convert();
        void test_xtoa();
        void test_string_util();
		void test_split();
    };
} // end of namespace LibTest
