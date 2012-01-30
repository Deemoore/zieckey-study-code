#pragma once

#include "osl/include/shell.h"

namespace LibTest
{

    class ITestObject : public osl::Object
    {
    public:
        virtual ~ITestObject() {}
        virtual void update() {}
        virtual void testAll() = 0;
        virtual const char* getCommand() = 0;   //! get the command string
        virtual const char* getDesc() = 0;      //! get the command description string
        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell ) = 0;
    };

    typedef osl::RefPtr<ITestObject> ITestObjectPtr;

} // end of namespace LibTest

#define CREATE_FUNCTION(x)                  \
    using namespace LibTest;                    \
    ITestObject* Create_##x()                   \
{                                           \
    return H_NEW x;                         \
}                                           \









