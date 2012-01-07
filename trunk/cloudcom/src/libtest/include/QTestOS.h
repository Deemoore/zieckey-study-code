#pragma once

#include "libtest/include/QTestObject.h"



namespace LibTest
{
    class TOS : public ITestObject
    {
    public:
        virtual const char* getCommand()
        {
            return "test_os";
        }
        virtual const char* getDesc()
        {
            return "test_os";
        }
        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
        virtual void testAll();

    private:
        void test();
        void test_getFullPathDir();
    };
} // end of namespace LibTest
