#include "libtest/include/QLibTestPrerequisits.h"

#include "libtest/include/QTestObject.h"
#include "osl/include/file_util.h"
#include "osl/include/tokener.h"

namespace
{
    class TLevelDBBenchAnalyse : public LibTest::ITestObject
    {
        void testAll();
        const char* getCommand();
        const char* getDesc();
        void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );


        void analyse( const osl::StringA& benchlogfile );



        struct Op
        {
            Op() { opt = 0.0; ops = 0; tops = 0; index = 0;}

            double opt;     //the operator time
            s32    ops;     //the operators per second
            s32    tops;    //the total operators
            s32    index;
        };


        bool parse( const osl::StringA& onerecord, Op& op );
    };

    const char* TLevelDBBenchAnalyse::getCommand()
    {
        return "test_ldbbench";
    }

    const char* TLevelDBBenchAnalyse::getDesc()
    {
        return "test_ldbbench --file=bench.log";
    }

    void TLevelDBBenchAnalyse::testAll()
    {
    }

    void TLevelDBBenchAnalyse::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        osl::StringA benchlog = "bklog";
        osl::AppShell::Param* pp = pCmd->getParam( "file" );
        if ( pp )
        {
            benchlog = pp->strVal;
        }

        analyse( benchlog );
    }

    

    void TLevelDBBenchAnalyse::analyse( const osl::StringA& benchlogfile )
    {
        osl::MemoryDataStream ds;
        if ( !ds.readRawFile( benchlogfile ) )
        {
            logWarn( LOG_NAME, "Cannot open file %s", benchlogfile.c_str() );
            return;
        }

        osl::MemoryDataStream filterlogbuf;
        filterlogbuf.setBufferSize( ds.getSize() / 4 );
        
        osl::MemoryDataStream diffopsbuf;
        diffopsbuf.setBufferSize( 4096 );

        osl::Tokener token( (char*)ds.getCache(), (s32)ds.getSize() );
        osl::StringA line;

        Op lastop;
        Op curop;

        s32 threshholdop = 10000;

        for ( s32 i = 0; !token.isEnd(); i++ )
        {
            line = token.nextString( '\n' );
            curop.index = i;
            if ( parse( line, curop ) )
            {
                if ( curop.ops < threshholdop && lastop.index + 1 < i )
                {
                    filterlogbuf.write( line.c_str(), line.size() );
                    logInfo( "analyse.log", "index=%d diffops=%d ops=%d", i, curop.index - lastop.index, curop.ops );

                    osl::StringA diffops = osl::StringUtil::valueOf( curop.index - lastop.index );
                    diffopsbuf.write( diffops.c_str(), diffops.size() );
                    diffopsbuf.write( ' ' );

                    lastop = curop;
                }
            }
        }
        
        filterlogbuf.saveToFile( osl::Process::getBinDir(true) + "../log/filter.log" );
        diffopsbuf.saveToFile( osl::Process::getBinDir(true) + "../log/diffops.txt" );
    }

    bool TLevelDBBenchAnalyse::parse( const osl::StringA& onerecord, Op& op )
    {
        const char* difftime = "difftime=";
        const char* ops = "ops=";
        const char* finished = "finished ";

        const char* begin = onerecord.c_str();
        char* pos = const_cast<char*>(begin);

        pos = strstr( pos, difftime );
        if ( !pos )
        {
            logWarn( LOG_NAME, "Cannot find \"%s\"", difftime );
            return false;
        }
        op.opt = atof( pos + strlen(difftime) );

        pos = strstr( pos, ops );
        if ( !pos )
        {
            logWarn( LOG_NAME, "Cannot find \"%s\"", ops );
            return false;
        }
        op.ops = atoi( pos + strlen(ops) );

        pos = strstr( pos, finished );
        if ( !pos )
        {
            logWarn( LOG_NAME, "Cannot find \"%s\"", finished );
            return false;
        }
        op.tops = atoi( pos + strlen(finished) );

        return true;
    }

}





CREATE_FUNCTION( TLevelDBBenchAnalyse );








