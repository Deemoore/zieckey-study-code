#pragma once

#include "libtest/include/QTestObject.h"



namespace LibTest
{
    class TThreads : public ITestObject
    {
    public:
        virtual const char* getCommand()
        {
            return "test_threads";
        }
        virtual const char* getDesc()
        {
            return "test_threads";
        }
        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
        virtual void testAll();

    private:
        void test();
    };
} // end of namespace LibTest
