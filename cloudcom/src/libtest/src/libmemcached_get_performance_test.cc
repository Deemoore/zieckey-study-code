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
        TestLibMemcachedGetPerformance( const osl::StringA& sock, const osl::StringA& host, const osl::StringA& port, size_t count, bool log )
            : mc_( sock.c_str(), host.c_str(), port.c_str() ), total_count_(count), log_enable_(log)
        {
            static int i = 0;
            setName(osl::StringUtil::valueOf(i++));
        }

        virtual bool start()
        {
            logTrace("libtest", " call...");
            return osl::Thread::start();
        }

        virtual void run()
        {
            double start = s_pTimer->getImmediateSeconds();
            logTrace("libtest", "Thread %s is running ... thread state=%d  total_count_=%lu", getName().c_str(), getState(), total_count_);
            osl::StringA errmsg;
            osl::StringA key;
            osl::StringA value;
            osl::Random randint( uint32_t(s_pTimer->getImmediateSeconds() * 1000000) + rand());
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
                    if (log_enable_)
                    {
                        logTrace("libtest", "thread %s key=%s value=%s", getName().c_str(), it->first.c_str(), it->second.c_str());
                    }
                }
            }


            double end = s_pTimer->getImmediateSeconds();
            logTrace("libtest", "Thread %s stopped  total_count_=%lu ops=%f", getName().c_str(), total_count_, total_count_/(end - start));
        }

   private:
        wu::Memcached mc_;
        size_t total_count_;
        bool log_enable_;
        
    };
}

TEST_INVOKE( test_libmemcached_get_performance , "test_libmemcached_get_performance --sock=/home/s/apps/CloudSafeLine/QueryEngine/MemDB/var/memcached.sock --host=localhost --port=10009 --thread=16 --count=1000000 --log=true" )
{
    osl::StringA sock = "/home/s/apps/CloudSafeLine/QueryEngine/MemDB/var/memcached.sock";
    osl::StringA hostname = "localhost";
    osl::StringA port = "10000";
    int threadnum = 1;
    size_t count     = 100000;
    bool log_enable = false;
    //test_memcached1 --host=localhost --port=10009 --thread=10 --method=get,set,delete
    osl::AppShell::Param* pp = pCmd->getParam("host");
    if ( pp ) hostname = pp->strVal;

    pp = pCmd->getParam("port");
    if ( pp ) port = pp->strVal;

    pp = pCmd->getParam("thread");
    if ( pp ) threadnum = atoi(pp->strVal.c_str());

    pp = pCmd->getParam("count");
    if ( pp ) count = atol(pp->strVal.c_str());

    pp = pCmd->getParam("log");
    if ( pp && pp->strVal == "true") log_enable = true;

    typedef osl::List<osl::ThreadPtr> ThreadPtrList;
    ThreadPtrList threads;
    for ( int i = 0; i < threadnum; ++i )
    {
        fprintf(stdout, "total thread : %d, current creating index %d\n", threadnum, i);
        TestLibMemcachedGetPerformance* pt = new TestLibMemcachedGetPerformance(sock, hostname, port, count, log_enable);
        threads.push_back(pt);

    }

   
    double start_time = s_pTimer->getImmediateSeconds();

    {
        ThreadPtrList::iterator it(threads.begin());
        ThreadPtrList::iterator ite(threads.end());
        for (; it != ite; ++it)
        {
            osl::Thread* pt = (*it);
            if (pt->start())
            {
                while (!pt->isRunning())
                {
                    logTrace("libtest", "waiting thread %s staring... running=%d, state=%d", pt->getName().c_str(), pt->isRunning(), pt->getState());
                    osl::Process::msleep(1);
                }
            }
        }
    }

    /*
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

    double end = s_pTimer->getImmediateSeconds();
    size_t total_count = count * threadnum;
    fprintf(stdout, "\n\ncount=%lu ops=%f\n", total_count, total_count/(end - start_time));
    */
}









TEST_INVOKE( test_libmemcached_test_get_get , "test_libmemcached_test_get_get --sock=/home/s/apps/CloudSafeLine/QueryEngine/MemDB/var/memcached.sock --host=localhost --port=10009 --thread=16 --count=1000000 --log=true" )
{
    osl::StringA sock = "/home/s/apps/CloudSafeLine/QueryEngine/MemDB/var/memcached.sock";
    osl::StringA hostname = "localhost";
    osl::StringA port = "10000";
    int threadnum = 1;
    size_t count     = 100000;
    bool log_enable = false;
    //test_memcached1 --host=localhost --port=10009 --thread=10 --method=get,set,delete
    osl::AppShell::Param* pp = pCmd->getParam("host");
    if ( pp ) hostname = pp->strVal;

    pp = pCmd->getParam("port");
    if ( pp ) port = pp->strVal;

    pp = pCmd->getParam("thread");
    if ( pp ) threadnum = atoi(pp->strVal.c_str());

    pp = pCmd->getParam("count");
    if ( pp ) count = atol(pp->strVal.c_str());

    pp = pCmd->getParam("log");
    if ( pp && pp->strVal == "true") log_enable = true;

    wu::Memcached mc_(sock.data(), hostname.data(), port.data());
    osl::Random randint( uint32_t(s_pTimer->getImmediateSeconds() * 1000000) + rand());
    for (size_t i = 0; i < count; ++i)
    {
        wu::Memcached::StringAStringAMap kvm;
        osl::StringA key, errmsg;
        for (int j = 0; j < 5; ++j)
        {
            key = osl::StringUtil::valueOf(osl::s64(i + j + randint.next()));
            kvm[key] = "";
        }
        if (mc_.mget(1, kvm, errmsg) < 0)
        {
            logTrace("libtest", "mget error:%s", errmsg.data());
        }
        
        wu::Memcached::StringAStringAMap kvm1;
        kvm1 = kvm;
        if (mc_.mget(1, kvm1, errmsg) < 0)
        {
            logTrace("libtest", "mget error:%s", errmsg.data());
        }
        wu::Memcached::StringAStringAMap::iterator it(kvm1.begin());
        wu::Memcached::StringAStringAMap::iterator ite(kvm1.end());
        for (; it != ite; ++it)
        {
            if (log_enable && it->second != "1")
            {
                logTrace("libtest", "error key=%s value=[%s]", it->first.c_str(), it->second.c_str());
            }
        }
    }
}


#endif

