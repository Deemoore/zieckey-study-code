#include "libtest/include/inner_pre.h"
#include "libtest/include/lib_test.h"
#include "osl/include/thread.h"
#include "osl/include/file_util.h"
#include "osl/include/utility.h"
#include "osl/include/timer.h"
#include "osl/include/random.h"

#include "wraputil/include/memcached.h"

#include <fstream>

#ifdef H_PROVIDE_LIBMEMCACHED

//#define _RECONSTRUCT_DATA

namespace 
{
    typedef std::list< std::string > stringlist;
    stringlist g_md5list;

#ifdef _RECONSTRUCT_DATA
    const char* g_dirty_data_file = "/home/weizili/dirty_data_stidx.txt";
#endif

    struct WriteDataFunctor 
    {
        WriteDataFunctor( std::ofstream& fos )
            : fos_(fos) {}

        void operator()( const std::string& key )
        {
            fos_.write( key.c_str(), key.length() );
            fos_.write( "\n", 1 );
        }

        private:
            std::ofstream& fos_;
    };

    /*
    bool ismd5( const char* key )
    {
        static char md5table[256];// 
        memset( md5table, 0, sizeof(md5table) );
        const char* md5char = "0123456789abcdefABCDEF";
    }*/

    void readmd5s( const osl::StringA& mdbdir )
    {
        osl::StringAList mdbs;
        osl::FileUtil::listAllFiles( mdbdir, mdbs );
        std::cout << "mdbdir=" << mdbdir.c_str() << " files count=" << mdbs.size() << std::endl;
        osl::StringAList::iterator it(mdbs.begin()), ite(mdbs.end());
        for ( ; it != ite; ++it )
        {
            osl::StringA& path = *it;
            std::cout << "Try to read " << path.c_str() << std::endl;
            FILE *fp = fopen( path.c_str(), "r" );
            uint8_t buffer[36];
            uint8_t data[65536];
            size_t nkey = 32;
            size_t i = 0;
            for( ; !feof( fp ); ++i )
            {
                size_t rc = fread( buffer, nkey + 4, 1, fp );

                if( rc != 1 )
                {
                    continue;
                }

                uint8_t *key = buffer;

                //uint32_t flags = buffer[nkey+1];
                uint16_t ndata = 0;
                ndata |= ( ( uint16_t ) buffer[nkey+2] << 8 );
                ndata |= ( ( uint16_t ) buffer[nkey+3] << 0 );

                if( ndata )
                {
                    fread( data, ndata, 1, fp );
                }

                std::string k( reinterpret_cast<const char *>( key ), nkey );

                g_md5list.push_back(k);
            }
            std::cout << "read md5 count:" << i << std::endl;
            fclose( fp );
        }

        
#ifdef _RECONSTRUCT_DATA
        std::ofstream fos( g_dirty_data_file, std::ios::out | std::ios::binary );
        std::for_each( g_md5list.begin(), g_md5list.end(), WriteDataFunctor(fos) );
        fos.flush();
#endif
    }


    void test1( wu::Memcached& mc )
    {//{{{
        osl::StringA value;
        osl::StringA errmsg;
        osl::StringA key[] = { "6e9ec3c3797d2e32ea8d04fba3216dc6", "49f13a2dd0a4e43959788df27ec7227a" };
        size_t keynum = sizeof(key)/sizeof(key[0]);
        wu::Memcached::StringAStringAMap ssm;
        for ( size_t i = 0; i < keynum; ++i )
        {
            ssm[key[i]] = "";
            if ( mc.get( key[i], 1, value, errmsg ) )
            {
                printf("key=%s value=%s\n", key[i].c_str(), value.c_str() );
            }
            else
            {
                fprintf( stderr, "%s\n", errmsg.c_str() );
            }
        }


        if ( mc.mget( 0, ssm, errmsg ) >= 0 )
        {
            printf("memcached_mget OK\n" );
        }
        else
        {
            fprintf( stderr, "memcached_mget failed:%s\n", errmsg.c_str() );
        }
    }//}}}

    struct InsertElement
    {
        InsertElement( osl::StringAList& md5svect )
            : md5list_(md5svect ) {}

        void operator()( const std::string& key )
        {
            md5list_.push_back( key.c_str() );
        }

        private:
        osl::StringAList& md5list_;
    };

    class TestMemcachedThread : public osl::Thread
    {
        enum {
            METHOD_SET,
            METHOD_DELETE,
            METHOD_GET,
            METHOD_NUM
        };

        struct QueryMemcachedFunctor
        {//{{{
            osl::StringA errmsg;
            osl::StringA value;
            osl::StringA logname;
            wu::Memcached& mc_;

            QueryMemcachedFunctor( wu::Memcached& mc ) : mc_(mc) {
                logname = osl::StringA("operatormd5count_") + osl::StringUtil::valueOf((u64)currenttime_);
            }

#ifndef H_STD_STRING
            void operator()( const std::string& key )
            {
                if ( mc_.get( key.c_str(), key.size(), 1, value, errmsg ) )
                {
                    H_MINI_AUTOLOCK( operatormd5countlock_ );
                    operatormd5count_++;
                    if ( operatormd5count_ % 1000 == 0 )
                    {
                        logTrace( logname, "%lu", operatormd5count_ );
                    }
                }
                else
                {
                    logError( "TestMemcached", "get key=%s failed, %s", key.c_str(), errmsg.c_str() );
                }
            }
#endif

            void operator()( const osl::StringA& key )
            {
                if ( mc_.get( key, 1, value, errmsg ) )
                {
                    H_MINI_AUTOLOCK( operatormd5countlock_ );
                    operatormd5count_++;
                    if ( operatormd5count_ % 1000 == 0 )
                    {
                        logTrace( logname, "%lu", operatormd5count_ );
                    }
                }
                else
                {
                    logError( "TestMemcached", "get key=%s failed, %s", key.c_str(), errmsg.c_str() );
                }
            }
        };//}}}

    public:
        TestMemcachedThread( const osl::StringA& host, const osl::StringA& port, const osl::StringA& method )
            : mc_( "xxxx", host.c_str(), port.c_str() )
        {
            memset( method_, 0, sizeof(method_) );

            if ( osl::StringUtil::contains( method, "set" ) )
            {
                method_[METHOD_SET] = true;
            }
            if ( osl::StringUtil::contains( method, "get" ) )
            {
                method_[METHOD_GET] = true;
            }
            if ( osl::StringUtil::contains( method, "delete" ) )
            {
                method_[METHOD_DELETE] = true;
            }

            std::cout << "method=" << method.c_str() 
                << ", set=" << method_[METHOD_SET]
                << ", get=" << method_[METHOD_GET]
                << ", delete=" << method_[METHOD_DELETE] << std::endl;

            const char* md5s[] = { //{{{
                "3a1db3ac6b9060ec2127fdace00a4f35",
                "6663fe4118a907401ef9f76fff5ca76e",
                "d6f11634bd2458bddd0211aa03793423",
                "e5ff35e33fa2a6446006d22776ff4179",
                "013373191d692e2b246c7a2a07a49bcd",
                "50e6bc1ab912ab6ed40b500f803a2de9",
                "3e3c8fa8a93f3c72060351aec02265fe",
                "71ffe37ec78a952a11e3608b007ea9ad",
                "8d98dbfda322f47e7d734c7945dd0eb9",
                "98521f8766575de0432cf602f30d70f6",
                "70d42d3e809731bfdf668dca9043c2aa",
                "6b81e593bc12d9681a41e775ae687be3",
                "24c6068e63442d482476ba13bf1ccef1",
                "edf91eeff0511cff3662627f4d7c80b3",
                "73e61f15b38663a99265a5e2ce450074",
                "3db22f52d596e4a255ed268600ae7eb8",
                "d912e5f109e21a91b5a36e45cad47eb9",
                "d42f58da72b9df5694865b3834cea588",
                "0a1054d0d66597d2c56bf5df6254d840",
                "8a13439fe62660f54946386e894a64cc",
                "94ae780c4809a40a25535c1ef48b1632",
                "d2c871a89a017912427e5afe07bddc56",
                "0f6af4974f83ea7a1416a7e6b8cca4e0",
                "e91d46cdc31b024d9aefae51d8296dcc",
                "d3173818d2744511d2e07025fe54805d",
                "1ce1f9bd0361b406c705953c57b4a75e",
                "5029e4e4ea06884c7f0ef6003f332c64",
                "741889124b427bb042e75580bd090ce4",
                "ca69be370659f4917fdc29e228d2542c",
                "06a79fabdd9d297ca8f90d303567025c",
                "0b37473f136016028c62b93d58f43b93",
                "6d8be534e3d2ea31d43b90063b78fea7",
                "d8fd2a50fdefebdf89ec3d89c62d50ab",
                "7678235935cae4c8aace322d9a4c89fb",
                "54d6438f317966b75a8cb911ab7587a7",
                "ddaa334132c0c0e3ee514f1dac6b3361",
                "c867cdc9d85e7c244415cf2101b8d6c4",
                "86499ca48acbd338449d6a434ac435b1",
                "80e9833af69c691129e0adbbda3569be",
                "e2b0256248157dfba696a68a1b83a18f",
                "3edcd9b0d48cef2107dee0cbc864062d",
                "3c73e13aa2a859a5257e931af9fd50e0",
                "a65183e332730c2d09abdee0744703e4",
                "5f8676c994f41b49e074b45c0f2d5dd5",
                "81f77bd9a1903966c173a50d25c24b4e",
                "d4458539c6602c098c6ca2928586ae3b",
                "ca40df41d46ac4fb1cf2449b0c6e7a05",
                "519088ae74a77ebef979a1a17867f714",
                "9db814b9a75bc8cced872315352ab2d4",
                "224a370e3e27ca86fb792c8b5114ebfe",
                "9f443f89f254430d1dfa73303aac2d1f",
                "11a5707f1a7ac3e5839fb49228ad276e"
            }; //}}}

            size_t md5ssize = H_ARRAY_SIZE( md5s );
            for ( size_t i = 0; i < md5ssize; ++i )
            {
                md5list_.push_back( md5s[i] );
            }


#ifdef _RECONSTRUCT_DATA
            {
                osl::StringA errmsg;
                for ( size_t i = 0; i < md5list_.size(); ++i )
                {
                    //if( !mc_.set( md5list_[i], values[randint.next() % valuessize], errmsg ) )
                    if( !mc_.erase( md5list_[i], errmsg ) )
                    {
                        std::cout << "set value failed!" << std::endl;
                    }
                }
            }
#endif


            if ( !g_md5list.empty() )
            {
                std::cout << "md5 count=" << md5list_.size();
                std::for_each( g_md5list.begin(), g_md5list.end(), InsertElement(md5list_) );
                std::cout << "After get the mdb md5, count=" << md5list_.size();
            }
            
            totalcount_++;
        }

        void run()
        {
            const char* values[] = { //{{{
                "00000000000000000000000000000000000000000000000000",
                "11111111111111111111",
                "2222222222222222222222222222222",
                "3333333333",
                "444444444444444444444444",
                "5555555555555555555555555555555555555",
                "66666666666666666666666666666666666666666666",
                "7777777777777",
                "88888888888888888888888888",
                "99999999999999999999999999999999999999999999999",
            };
            size_t valuessize = H_ARRAY_SIZE( values );
            (void)valuessize;
            //}}}

#define MYCHECK(a) {if(totalcount_==1) H_ASSERT((a)&&"failed!");} //we can make sure the result when only one thread

            osl::Random randint( uint32_t(s_pTimer->getSeconds() * 1000000) );
        
            osl::StringA errmsg;

            osl::StringA logname = osl::StringA("operatormd5count_") + osl::StringUtil::valueOf((u64)currenttime_);

            /*
            for ( size_t i = 0; i < md5list_.size(); ++i )
            {
                //if( !mc_.set( md5list_[i], values[randint.next() % valuessize], errmsg ) )
                if( !mc_.erase( md5list_[i], errmsg ) )
                {
                    std::cout << "set value failed!" << std::endl;
                }
            }
            */

#ifdef _RECONSTRUCT_DATA
            return;
#endif
            
            //std::for_each( g_md5list.begin(), g_md5list.end(), QueryMemcachedFunctor(mc_) );

           
            osl::StringA value;
            for( size_t i = 0; ; i++ )
            {
                int method = randint.next() % METHOD_NUM;
                osl::StringA key = osl::StringUtil::valueOf(osl::u64(i));
                if ( i % 2 == 0 )
                {
                    key = GetElement(md5list_, randint.next()%md5list_.size());
                }
                switch ( method )
                {
                    case METHOD_SET:
                        if ( method_[method] && !mc_.set( key, values[randint.next() % valuessize], errmsg ) )
                        {
                            //std::cout << "set value failed!" << std::endl;
                            logError( "TestMemcached.ERROR", "set value failed, %s, %s", key.c_str(), errmsg.c_str() );
                            //exit(1);
                        }
                        else
                        {
                            //logTrace( "TestMemcached.set", "set key=%s", key.c_str() );
                        }
                        break;
                    case METHOD_DELETE:
                        if ( method_[method] && !mc_.erase( key, errmsg ) )
                        {
                            std::cout << "delete value failed!" << std::endl;
                            exit(1);
                        }
                        break; 
                    case METHOD_GET:
                        if ( method_[method] && !mc_.get( key, 0, value, errmsg ) )
                        {
                            if ( !osl::StringUtil::contains( errmsg, "NOT FOUND" ) )
                            {
                                //logTrace( "TestMemcached", "%lu", operatormd5count_ );
                                logError( "TestMemcached.ERROR", "get value failed, %s %s", key.c_str(), errmsg.c_str() );
                            }
                        }
                        else
                        {
                            H_MINI_AUTOLOCK( operatormd5countlock_ );
                            operatormd5count_++;
                            if ( operatormd5count_ % 1000 == 0 )
                            {
                                logTrace( logname, "%lu", operatormd5count_ );
                            }
                        }
                        break;
                    default:
                        break;
                };
            }
        }

    osl::StringA GetElement( const osl::StringAList& md5list, size_t index )        
    {
        osl::StringAList::const_iterator it(md5list.begin());
        osl::StringAList::const_iterator ite(md5list.end());
        for ( size_t i = 0; it != ite; ++it, ++i )
        {
            if ( i == index )
            {
                return *it;
            }
        }
        return *md5list.begin();
    }

    private:
        wu::Memcached mc_;
        
        osl::StringAList md5list_;

        bool method_[METHOD_NUM];
        static size_t totalcount_;

        static osl::AtomicInt32 operatormd5count_;
        static osl::MiniLock operatormd5countlock_;
        static time_t currenttime_;
    };
    size_t TestMemcachedThread::totalcount_ = 0;
    osl::AtomicInt32 TestMemcachedThread::operatormd5count_ = 0;
    osl::MiniLock TestMemcachedThread::operatormd5countlock_;
    time_t TestMemcachedThread::currenttime_ = time(NULL);

}



TEST( test_memcached )
{
    wu::Memcached mc( "xxx", "mid.kill.corp.qihoo.net", "11211" );
    test1( mc );

    const size_t kThreadNum = 1;
    TestMemcachedThread* threads[kThreadNum] = {}; 
    for ( size_t i = 0; i < kThreadNum; ++i )
    {
        threads[i] = new TestMemcachedThread("localhost", "10009", "set,get");
        threads[i]->start();
    }
}

//namespace
//{
//    class TMemcached : public LibTest::ITestObject
//    {
//        virtual void testAll();
//        virtual const char* getCommand();
//        virtual const char* getDesc();
//        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
//    };
//
//    const char* TMemcached::getCommand()
//    {
//        return "test_memcached1";
//    }
//
//    const char* TMemcached::getDesc()
//    {
//        return "test_memcached1";
//    }
//
//    void TMemcached::testAll()
//    {
//    }
//
//    void TMemcached::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
//    {
//        testAll();
//    }
//
//}
//
//CREATE_FUNCTION( TMemcached );

TEST_INVOKE( test_memcached1, "test_memcached1 --host=localhost --port=10009 --thread=10 --method=get|set|delete --mdbdir=/tmp/mdb" )
        //invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
{
    osl::StringA hostname = "localhost";
    osl::StringA port = "10009";
    int threadnum = 1;
    osl::StringA method = "get|set|delete";
    osl::StringA mdbdir = "/home/weizili/mdb";

    //test_memcached1 --host=localhost --port=10009 --thread=10 --method=get,set,delete
    osl::AppShell::Param* pp = pCmd->getParam("host");
    if ( pp ) hostname = pp->strVal;

    pp = pCmd->getParam("port");
    if ( pp ) port = pp->strVal;

    pp = pCmd->getParam("thread");
    if ( pp ) threadnum = atoi(pp->strVal.c_str());

    pp = pCmd->getParam("method");
    if ( pp ) method = pp->strVal;

    pp = pCmd->getParam("mdbdir");
    if ( pp ) mdbdir = pp->strVal;

    //readmd5s( mdbdir );

    for ( int i = 0; i < threadnum; ++i )
    {
        TestMemcachedThread* pt = new TestMemcachedThread(hostname, port, method);
#ifndef _RECONSTRUCT_DATA
        pt->start();
#endif
        (void)pt;
    }
}













#endif// #ifdef H_PROVIDE_LIBMEMCACHED



