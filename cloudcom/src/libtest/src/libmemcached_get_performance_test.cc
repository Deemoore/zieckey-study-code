#include "libtest/include/inner_pre.h"
#include "libtest/include/lib_test.h"
#include "osl/include/thread.h"
#include "osl/include/file_util.h"
#include "osl/include/utility.h"
#include "osl/include/timer.h"
#include "osl/include/md5.h"
#include "osl/include/random.h"

#include "wraputil/include/memcached.h"

#include <fstream>

#ifdef H_PROVIDE_LIBMEMCACHED

namespace 
{
    class TestLibMemcachedGetPerformance : public osl::Thread
    {
    public:
        TestLibMemcachedGetPerformance( const osl::StringA& sock, const osl::StringA& host, const osl::StringA& port, size_t count )
            : mc_( sock.c_str(), host.c_str(), port.c_str() ), total_count_(count)
        {
            static int i = 0;
            setName(osl::StringUtil::valueOf(i));
        }

        virtual bool start()
        {
            logTrace("libtest", " call...");
            return osl::Thread::start();
        }

        virtual void run()
        {
            logTrace("libtest", "Thread %s is running ... thread state=%d  total_count_=%lu\n", getName().c_str(), getState(), total_count_);
            osl::StringA errmsg;
            osl::StringA key;
            osl::StringA value;
            osl::Random randint( uint32_t(s_pTimer->getSeconds() * 1000000) + rand());
            for (size_t i = 0; i < total_count_; ++i)
            {
                wu::Memcached::StringAStringAMap kvm;
                for (int j = 0; j < 5; ++j)
                {
                    key = osl::StringUtil::valueOf(osl::s64(i + j + randint.next()));
                    kvm[key] = "";
                }
                mc_.mget(1, kvm, errmsg);
                wu::Memcached::StringAStringAMap::iterator it(kvm.begin());
                wu::Memcached::StringAStringAMap::iterator ite(kvm.end());
                
                for (; it != ite; ++it)
                {
                    (void)(it);
                }
            }
        }

   private:
        wu::Memcached mc_;
        size_t total_count_;
        
    };
}

TEST_INVOKE( test_libmemcached_get_performance , "test_libmemcached_get_performance --sock=/home/s/apps/CloudSafeLine/QueryEngine/MemDB/var/memcached.sock --host=localhost --port=10009 --thread=16 --count=1000000" )
{
    osl::StringA sock = "/home/s/apps/CloudSafeLine/QueryEngine/MemDB/var/memcached.sock";
    osl::StringA hostname = "localhost";
    osl::StringA port = "10000";
    int threadnum = 1;
    size_t count     = 100000;
    //test_memcached1 --host=localhost --port=10009 --thread=10 --method=get,set,delete
    osl::AppShell::Param* pp = pCmd->getParam("host");
    if ( pp ) hostname = pp->strVal;

    pp = pCmd->getParam("port");
    if ( pp ) port = pp->strVal;

    pp = pCmd->getParam("thread");
    if ( pp ) threadnum = atoi(pp->strVal.c_str());

    pp = pCmd->getParam("count");
    if ( pp ) count = atol(pp->strVal.c_str());

    double start_time = s_pTimer->getSeconds();
    typedef osl::List<osl::ThreadPtr> ThreadPtrList;
    ThreadPtrList threads;
    for ( int i = 0; i < threadnum; ++i )
    {
        fprintf(stdout, "total thread : %d, current creating index %d\n", threadnum, i);
        TestLibMemcachedGetPerformance* pt = new TestLibMemcachedGetPerformance(sock, hostname, port, count);
        if (pt->start())
        {
            while (!pt->isRunning())
            {
                logTrace("libtest", "waiting thread %d staring... running=%d, state=%d\n", i, pt->isRunning(), pt->getState());
                osl::Process::msleep(1000);
            }
            threads.push_back(pt);
        }
    }

    bool finished = true;
    while (!finished)
    {
        fprintf(stdout, ".");
        finished = true;
        ThreadPtrList::iterator it(threads.begin());
        ThreadPtrList::iterator ite(threads.end());
        for (; it != ite; ++it)
        {
            if ((*it)->isRunning())
            {
                finished = false;
                osl::Process::msleep(100);
                break;
            }
        }
    }

    double end = s_pTimer->getSeconds();
    size_t total_count = count * threadnum;
    fprintf(stdout, "\n\ncount=%lu ops=%f\n", total_count, total_count/(end-start_time));
}









#endif// #ifdef H_PROVIDE_LIBMEMCACHED



