#include "libtest/include/QLibTestPrerequisits.h"

#include "libtest/include/QTestObject.h"
#include "osl/include/QTimer.h"

namespace LibTest
{
    class TMemAlloc : public ITestObject
    {
    public:
        virtual const char* getCommand()
        {
            return "test_memalloc";
        }
        virtual const char* getDesc()
        {
            return "test_memalloc --type=0(all)|1(effective)\n\twhen type=1, using other 5 parameters: --memsize=1,1048576 --everycount=5 --totalcount=5 --premalloccount=1024 --usemempool=true|false";
        }
        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
        virtual void testAll();

    private:
        void test_count();
        void test_alloc_free();

        void test_effective( u32 premalloccout = 2048, u32 memsizefrom = 1, u32 memsizeto = 1024 * 1024, u32 everymalloccount = 2, u32 totalcount = 2, bool bUseMemPool = true );
    };
} // end of namespace LibTest



namespace LibTest
{
    using namespace osl;

    void TMemAlloc::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        osl::AppShell::Command::Param* pParam = pCmd->getParam( "type" );
        if ( pParam )
        {
            if ( pParam->strVal == "0" || pParam->strVal == "all" )
            {
                testAll();
            }
            else if ( pParam->strVal == "1" || pParam->strVal == "effective" )
            {
                //test_memalloc --type=1 --memsizeto=1,1024 --everycount=10 --totalcount=10 --premalloccount=1024 --usemempool=true
                u32 premalloccount = 2048;
                u32 memsizefrom = 1024 * 1024;
                u32 memsizeto = 1024 * 1024;
                u32 everycount = 10;
                u32 totalcount = 10;
                bool usemempool = true;

                pParam = pCmd->getParam( "premalloccount" );
                if ( pParam )
                {
                    premalloccount = atoi( pParam->strVal.c_str() );
                }

                pParam = pCmd->getParam( "memsize" );
                if ( pParam )
                {
                    osl::StringA strFrom;
                    osl::StringA strTo;
                    osl::StringUtil::split( pParam->strVal, strFrom, strTo, "," );
                    memsizefrom = atoi( strFrom.c_str() );
                    memsizeto = atoi( strTo.c_str() );
                }

                pParam = pCmd->getParam( "everycount" );
                if ( pParam )
                {
                    everycount = atoi( pParam->strVal.c_str() );
                }


                pParam = pCmd->getParam( "totalcount" );
                if ( pParam )
                {
                    totalcount = atoi( pParam->strVal.c_str() );
                }

                pParam = pCmd->getParam( "usemempool" );
                if ( pParam )
                {
                    if ( pParam->strVal == "true" )
                    {
                        usemempool = true;
                    }
                    else
                    {
                        usemempool = false;
                    }
                }

                test_effective( premalloccount, memsizefrom, memsizeto, everycount, totalcount, usemempool );
            }
        }
        else
        {
            testAll();
        }
    }

    void TMemAlloc::testAll()
    {
        test_count();
        test_alloc_free();
        test_effective();
    }
    class TestClass1
    {
        H_ALLOCRAW_OPERATORS( TestClass1 );
        int a ;
        int b;
    };


    void TMemAlloc::test_count()
    {
        const osl::u32 OBJ_NUMBSER = 5;
        {
            TestClass1* pClass[OBJ_NUMBSER]={};
            for ( osl::u32 i = 0; i < OBJ_NUMBSER ; ++i )
            {
                pClass[i] = H_NEW TestClass1;
                pClass[i]->a = rand();
                pClass[i]->b = rand();
                pClass[i]->a = rand();
                pClass[i]->b = rand();
                pClass[i]->a = rand();
                pClass[i]->b = rand();
                pClass[i]->a = rand();
                pClass[i]->b = rand();
            }

            for ( osl::u32 i = 0; i < OBJ_NUMBSER ; ++i )
            {
                pClass[i]->a = rand();
                pClass[i]->b = rand();
                pClass[i]->a = rand();
                pClass[i]->b = rand();
                pClass[i]->a = rand();
                pClass[i]->b = rand();
                pClass[i]->a = rand();
                pClass[i]->b = rand();
            }

            const osl::u32 nNumInst = H_GET_CLASS_INSTANCE_NUM( TestClass1 );
            (void)nNumInst;
            H_ASSERT( OBJ_NUMBSER == nNumInst );

            H_ASSERT( OBJ_NUMBSER == osl::MemAlloc::getNumInstancesByClassName( "TestClass1" ) );

            for ( osl::u32 i = 0; i < OBJ_NUMBSER ; ++i )
            {
                delete pClass[i];
            }

            const osl::u32 nNumInst2 = H_GET_CLASS_INSTANCE_NUM( TestClass1 );
            (void)nNumInst2;
            H_ASSERT( 0 == nNumInst2 );

            H_ASSERT( 0 == osl::MemAlloc::getNumInstancesByClassName( "TestClass1" ) );
        }
    }

    void TMemAlloc::test_alloc_free()
    {
        {
            void* pAlloc0 = MemAlloc::alloc( 0 );
            H_ASSERT( NULL == pAlloc0 );

            MemAlloc::free( pAlloc0 );

        }
        {
            void* pAlloc1 = MemAlloc::alloc( 1 );
            MemAlloc::free( pAlloc1 );
        }
    }

    void TMemAlloc::test_effective( u32 premalloccout /*= 2048*/, u32 memsizefrom /*= 1*/, u32 memsizeto /*= 1024 * 1024*/, u32 everymalloccount /*= 2*/, u32 totalcount /*= 2*/, bool bUseMemPool /*= true */ )
    {
        const u32 ONE_MILLION = 1048576; // 1M = 1024 * 1024
        (void)(ONE_MILLION);

        unsigned int seed = 52623236;
        srand( seed );

        u64 tbegin = s_pTimer->getImmediateMicroseconds(); // begin timing
        (void)tbegin;

        void** pPreAllocArray = NULL;//
        if ( bUseMemPool )
        {
            pPreAllocArray = (void**)osl::MemAlloc::alloc( premalloccout * sizeof(void*) );
        }
        else
        {                    
            pPreAllocArray = (void**)malloc( premalloccout * sizeof(void*) );
        }

        for ( u32 i = 0; i < premalloccout; ++i )
        {
            if ( bUseMemPool )
            {
                pPreAllocArray[i] = osl::MemAlloc::alloc( rand() % 1048576 );
            }
            else
            {                    
                pPreAllocArray[i] = malloc( rand() % 1048576  );
            }
        }

        for ( u32 i = 0; i < totalcount; ++i )
        {
            for ( u32 size = memsizefrom; size <= memsizeto; ++size )
            {
                for ( u32 count = 0; count < everymalloccount; ++count )
                {
                    if ( bUseMemPool )
                    {
                        void* p = osl::MemAlloc::alloc( size );
                        u32 index = rand() % premalloccout;
                        osl::MemAlloc::free( pPreAllocArray[index] );
                        pPreAllocArray[index] = p;
                    }
                    else
                    {                    
                        void* p = malloc( size );
                        u32 index = rand() % premalloccout;
                        free( pPreAllocArray[index] );
                        pPreAllocArray[index] = p;
                    }
                }
            }
        }//end of for

        for ( u32 i = 0; i < premalloccout; ++i )
        {
            if ( bUseMemPool )
            {
                osl::MemAlloc::free( pPreAllocArray[i] );
            }
            else
            {                    
                free( pPreAllocArray[i] );
            }
        }


        if ( bUseMemPool )
        {
            osl::MemAlloc::free( pPreAllocArray );
        }
        else
        {                    
            free( pPreAllocArray );
        }
                                                            
    }
}

CREATE_FUNCTION( TMemAlloc );



/*


说一下osl::MemAlloc测试情况。


测试的用例是这样的，在同一个线程中，
1、首先分配premalloccount个大小为随机值的内存，存到一个预先分配内存数组中
2、内存的分配大小从memsize的第一个参数（1字节）到memsize的第二个参数（1024字节）种。
每次分配一个内存，就将该内存随机替换掉预先分配内存数组中的一个内存节点，然后释放被替换的那个内存节点
3、重复步骤2 everycount次
4、重复步骤 2、3 totalcount次。


test_memalloc --type=1 --memsize=1,1024 --everycount=100 --totalcount=100 --premalloccount=1024 --usemempool=true
using osl::MemAlloc, time=2.69835s, 2698.35ms, 2698353us
using system malloc, time=4.77547s, 4775.47ms, 4775473us

test_memalloc --type=1 --memsize=1,1024 --everycount=100 --totalcount=100 --premalloccount=4096 --usemempool=true
using osl::MemAlloc, time=3.1464s, 3146.4ms, 3146398us
using system malloc, time=8.63616s, 8636.16ms, 8636160us

test_memalloc --type=1 --memsize=1,1024 --everycount=100 --totalcount=1000 --premalloccount=4096 --usemempool=true
using osl::MemAlloc, time=31.3206s, 31320.6ms, 31320610us
using system malloc, time=91.1649s, 91164.9ms, 91164933us



test_memalloc --type=1 --memsize=1024,10480 --everycount=1 --totalcount=1 --premalloccount=4096 --usemempool=true
using osl::MemAlloc, time=0.020044s, 20.044ms, 20044us
using system malloc, time=0.06075s, 60.75ms, 60750us


test_memalloc --type=1 --memsize=1024,104857 --everycount=1 --totalcount=1 --premalloccount=4096 --usemempool=true
using osl::MemAlloc, time=0.205851s, 205.851ms, 205851us
using system malloc, time=1.28215s, 1282.15ms, 1282153us


test_memalloc --type=1 --memsize=1024,104857 --everycount=10 --totalcount=10 --premalloccount=4096 --usemempool=true
using osl::MemAlloc, time=4.1825s, 4182.49ms, 4182495us
using system malloc, time=128.55s, 128550ms, 128549533us


test_memalloc --type=1 --memsize=1024,104857 --everycount=100 --totalcount=10 --premalloccount=4096 --usemempool=true
using osl::MemAlloc, time=38.8263s, 38826.3ms, 38826285us
using system malloc, time=1292.26s, 1.29226e+006ms, 1292264698us



test_memalloc --type=1 --memsize=1024,104857 --everycount=100 --totalcount=100 --premalloccount=4096 --usemempool=true
using osl::MemAlloc, time=385.517s, 385517ms, 385516567us
using system malloc, time=12926.9s, 1.29269e+007ms, 12926892452us



test_memalloc --type=1 --memsize=1024,1048576 --everycount=1 --totalcount=1 --premalloccount=4096 --usemempool=true

*/
