#pragma once

#include "libtest/include/QTestObject.h"



namespace LibTest
{
    class TMemoryDataStream : public ITestObject
    {
    public:
        virtual const char* getCommand()
        {
            return "test_MemoryDataStream";
        }
        virtual const char* getDesc()
        {
            return "test_MemoryDataStream";
        }
        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
        virtual void testAll();

    private:
        void test();
    };
} // end of namespace LibTest
