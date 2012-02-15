#include "libtest/include/QLibTestPrerequisits.h"

#include "libtest/include/QTestObject.h"
#include "osl/include/log.h"
#include "osl/include/log_manager.h"

namespace
{
    class TLog : public LibTest::ITestObject
    {
        void testAll();
        const char* getCommand();
        const char* getDesc();
        void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );


        void test_1();
    };

    const char* TLog::getCommand()
    {
        return "test_log";
    }

    const char* TLog::getDesc()
    {
        return "test_log";
    }

    void TLog::testAll()
    {
        test_1();
    }

    void TLog::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        testAll();
    }

    void TLog::test_1()
    {
        H_LOG_NAME_DEBUG( "TestLog", "debug" );
        H_LOG_NAME_TRACE( "TestLog", "trace" );
        H_LOG_NAME_INFO( "TestLog", "info" );
        H_LOG_NAME_WARN( "TestLog", "warning" );
        H_LOG_NAME_ERROR( "TestLog", "error" );
        H_LOG_NAME_FATAL( "TestLog", "fatal" );

        logTrace( "TestLog", "log trace, using VA parameter" );
        logDebug( "TestLog", "log debug, using VA parameter" );
        logInfo( "TestLog", "log info, using VA parameter" );
        logWarn( "TestLog", "log warn, using VA parameter" );
        logError( "TestLog", "log error, using VA parameter" );
        logFatal( "TestLog", "log fatal, using VA parameter" );


        int i = 0;
        logTrace( "TestLog", "log %s %d, using VA parameter", "trace", i++ );
        logDebug( "TestLog", "log %s %d, using VA parameter", "debug", i++ );
        logInfo( "TestLog", "log %s %d, using VA parameter", "info", i++ );
        logWarn( "TestLog", "log %s %d, using VA parameter", "warn", i++ );
        logError( "TestLog", "log %s %d, using VA parameter", "error", i++ );
        logFatal( "TestLog", "log %s %d, using VA parameter", "fatal", i++ );

        osl::u32 u = 100;
        logTrace( "TestLog", "log %s %d, %u", "ttttttttt", i++, u++  );
        logDebug( "TestLog", "log %s %d, %u", "dddddddddd", i++, u++ );
        logInfo( "TestLog", "log %s %d, %u", "info", i++, u++ );
        logWarn( "TestLog", "log %s %d, %u", "warn", i++, u++ );
        logError( "TestLog", "log %s %d, %u", "error", i++, u++ );
        logFatal( "TestLog", "log %s %d, %u", "fatal", i++, u++ );
    }
}





CREATE_FUNCTION( TLog );












