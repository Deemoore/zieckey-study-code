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

    static int FLAGS_md5_index = 4;

    osl::Slice SpliteCommand(const char* command, size_t len)
    {
        int count = 0;
        const char* begin = command;
        size_t slice_start = 0;
        for (size_t i = 0; i < len; ++i)
        {
            if (begin[i] == '\t')
            {
                ++count;
                if (count == FLAGS_md5_index)
                {
                    return osl::Slice(begin+i+1, 32);
                }
            }
        }

        return osl::Slice();
    }
}

TEST_INVOKE( test_libmemcached_set_performance , "test_libmemcached_set_performance --sock=/home/s/apps/CloudSafeLine/QueryEngine/MemDB/var/memcached.sock --host=localhost --port=10009 --upload_url=/the/file/to/upload_url.log --log=true" )
{
    osl::StringA sock = "/home/s/apps/CloudSafeLine/QueryEngine/MemDB/var/memcached.sock";
    osl::StringA upload_url_file="/tmp/upload_url.log";
    osl::StringA hostname = "localhost";
    osl::StringA port = "10000";
    bool log_enable = false;
    //test_memcached1 --host=localhost --port=10009 --thread=10 --method=get,set,delete
    osl::AppShell::Param* pp = pCmd->getParam("host");
    if ( pp ) hostname = pp->strVal;

    pp = pCmd->getParam("sock");
    if ( pp ) sock = pp->strVal;

    pp = pCmd->getParam("port");
    if ( pp ) port = pp->strVal;

    pp = pCmd->getParam("upload_url");
    if ( pp ) upload_url_file = pp->strVal;

    pp = pCmd->getParam("log");
    if ( pp && pp->strVal == "true") log_enable = true;

    wu::Memcached mc_(sock.data(), hostname.data(), port.data());

    std::fstream fs(upload_url_file.data());
    if (!fs.good())
    {
        std::cout << "Open file [" << upload_url_file.c_str() << "] failed!" << std::endl;
        return;
    }


    std::string line;
    size_t count = 0;
    size_t failed_count = 0;
    double fbegin = s_pTimer->getImmediateSeconds();
    osl::StringA errmsg;
    while (std::getline(fs, line).good())
    {
        osl::Slice md5 = SpliteCommand(line.data(), line.size());
        if (md5.size() == 32 && osl::MD5::isValidMD5(md5.data(), md5.size()))
        {
            count++;
            if (!mc_.set(md5.data(), md5.size(), "1", 1, errmsg))
            {
                if (log_enable)
                {
                    logTrace("libtest", "set key=[%s] faield:%s", std::string(md5.data(), 32).data(), errmsg.data());
                }
                failed_count++;
            }
            if (log_enable || count%100 == 0)
            {
                std::cout << ".";
                std::cout.flush();
            }
        }
    }
    
    double fend = s_pTimer->getImmediateSeconds();
    double cost = fend - fbegin;
    logTrace("libtest", "\ncount=%lu failed_count=%lu cost=%f qps=%f", count, failed_count, cost, (count - failed_count)/cost);
}


#endif

