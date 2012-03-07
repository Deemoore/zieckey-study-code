#include "libtest/include/inner_pre.h"


#include "libtest/include/test_object.h"
#include "osl/include/scoped_mem.h"

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


namespace LibTest
{
    void TMemoryDataStream::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        testAll();
    }

    void TMemoryDataStream::testAll()
    {
        test();
    }
    class T1
    {
    public:
        int a;
        int b;
    public:
        friend osl::MemoryDataStream& operator <<( osl::MemoryDataStream& out, const T1& val )
        {
            out << val.a << val.b;
            return out;
        }

        friend osl::MemoryDataStream& operator >>( osl::MemoryDataStream& out, T1& val )
        {
            out >> val.a >> val.b;
            return out;
        }
    };

    struct test_struct1
    {
        int i;
        HCHAR sz[32];
    };
    struct test_struct2
    {
        int i;
        HCHAR sz[32];
        osl::StringA str ;
    };



    void TMemoryDataStream::test()
    {

        {
            {
                osl::ScopedMem pMem( 200 );

                if ( pMem.isNull() )
                {
                    H_LOG_NAME_ERROR( "test", "Constructor error." );
                }
            }

            {
                void* pBuf = H_ALLOC( 11 );
                {
                    osl::ScopedMem pMem( pBuf );

                    if ( pMem.isNull() )
                    {
                        H_LOG_NAME_ERROR( "test", "Assigner error." );
                    }
                }
            }


            {
                void* pBuf = H_ALLOC( 11 );
                {
                    osl::ScopedMem pMem( pBuf );
                    memset( pMem, 0, 11 );
                }
            }
        }


        //
        //std::cout << "testMemoryDataStream";

        osl::MemoryDataStream* pDS = H_NEW osl::MemoryDataStream();

        osl::StringA strI = "adfasdfas";
        osl::u32 u321I = 1;
        osl::f32 f321I = 0.5f;
        T1 t1I;

        test_struct1 stru_1 = { 111, "test_stru" };
        stru_1.i += 0;

        test_struct2 stru_2;
        stru_2.i = 222 ;
        strcpy( stru_2.sz , "22222" );
        stru_2.str = "test_stru2";


        {
            *pDS << strI
                 << u321I
                 << f321I
                 << t1I ;

            //*pDS<<stru_1<<stru_2;
            //std::cout << str << u321

        }

        osl::MemoryDataStream out;
        out.write( pDS->getCurReadBuffer(), pDS->getReadableSize() );

        //out.saveToFile( "e:\\aaa\\adc\\ddd\\aab.txt");
        //out.saveToFile( "aaa\\adc\\ddd\\aab.txt");

        osl::StringA strO;
        osl::u32 u321O = 1;
        osl::f32 f321O = 0.5f;
        T1 t1O;

        test_struct1 stru_3 ;
        test_struct2 stru_4 ;
        {
            out >> strO
                >> u321O
                >> f321O
                >> t1O >> stru_3 /*>> stru_4*/;
        }

        H_ASSERT( strI == strO &&
                  u321I == u321O &&
                  f321I == f321O );
        //out.isReadBad();

        //out.isWriteBad();

        /**pDS >> std::cout*/;//compiler error

        delete pDS;
    }
}//endof namespace

CREATE_FUNCTION( TMemoryDataStream );

IS_POD_TYPE( LibTest::test_struct1, true );
