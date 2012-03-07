#include "libtest/include/inner_pre.h"



#include "libtest/include/test_object.h"

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


namespace LibTest
{
    void TThreads::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        testAll();
    }

    void TThreads::testAll()
    {
        test();
    }

    static volatile osl::u32 s_nLocked = 0;

	class MyThread : public osl::Thread
    {
    public:
        osl::MiniLock&    m_lk;

        explicit MyThread( osl::MiniLock& lk ) : m_lk( lk )
        {
        }

    public:
        void run()
        {
            int c = 0;

            for ( int i = 0; i < ( 1 << 28 ); ++i )
            {
                m_lk.lock();

                if ( ++s_nLocked != 1 )
                {
                    H_LOG_NAME_ERROR( "test", "mini lock error." );
                    exit( 0 );
                }

                {
                    for ( int j = 0; j < 10000; ++j )
                    {
                        c++;
                    }
                }

                --s_nLocked;
                m_lk.unlock();

            }
        }
    private:
        MyThread( const MyThread& );
        MyThread&operator=( const MyThread& );
    };

    void TThreads::test()
    {
        osl::MiniLock    m_lk;

        //osl::u64 tmStart = s_pTimer->getImmediateMilliseconds();


        s_nLocked = 0;

		osl::ThreadPtr    m_vThreads[4];

        for ( int i = 0; i < 4; ++i )
        {
            m_vThreads[i] = new MyThread( m_lk );
            m_vThreads[i]->start();
        }


        osl::Process::msSleep( 10 );

        for ( int i = 0; i < 4; ++i )
        {
            m_vThreads[i]->join();
        }


        //osl::u64 tmElapsed = s_pTimer->getImmediateMilliseconds() - tmStart;
// 
//         osl::OStringStreamA strTip;
//         strTip << "lock cost time: " << tmElapsed;
//         H_LOG_NAME_INFO( "test", strTip.str() );

    }
}

CREATE_FUNCTION( TThreads );
