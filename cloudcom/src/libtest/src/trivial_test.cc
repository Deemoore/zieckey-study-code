#include "libtest/include/inner_pre.h"

#include "osl/include/file_util.h"
#include "osl/include/process_ext.h"
#include "osl/include/md5.h"
#include "osl/include/rsa_wrapper.h"
#include "osl/include/json.h"

#include "libtest/include/lib_test.h"

//#include "qh_palloc.h"

osl::u32 c_nNumMaxVisiblePatch = 9;




namespace LibTest
{
    class TTrivial : public ITestObject
    {
    public:
        virtual const char* getCommand()
        {
            return "test_trivial";
        }
        virtual const char* getDesc()
        {
            return "test_trivial   this cmd will test all the trivial test case.";
        }
        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
        virtual void testAll();

    private:
        void test_string_resize();
        void test_std_string(); // test std::string::resize()
        void test_atof();//test atof c library
        void fillContent( osl::StringA& out );
        void testStringTrim();
        void testLog4cxxForWindows();
        void testSelectTimeout();
        void testTypeid();
        void testDynamicCast();
        void testSpiralNumber();
        void testHashMap();
        void testGetDirFiles( osl::StringA path, osl::StringAVector& files ) ;

        void testRingBuffer();

        void testBZipCompress();

        //move from osl written by zhouhe, 
        void testmem();

        //class AppShell
        //void testAppShell();

        void testIntegerConvert();

        void testSysErrorCode();

        //! test
        void test_FileUtil_concatenatePath();

        void test_vector3df();

        void test_stringbuf();

        void test_md5();

        void test_rsa();

        void qh_pool();

        void qh_pool_test_3();

        void qh_pool_test_2();

        void qh_pool_test_1();


        void test_map_1();
        void test_hash_map_1();

        void test_json_merge_1();
    };












    //#define H_TEST_SELECT_TIMEOUT
#ifdef H_TEST_SELECT_TIMEOUT
#    ifdef H_OS_WINDOWS
#        include "winsock2.h"
#        pragma comment(lib,"Ws2_32.lib")
#    else
#        include <sys/select.h>
#        include <sys/types.h>
#        include <unistd.h>
#        include <sys/time.h>
#        include <sys/socket.h>
#    endif
#endif



#ifdef H_TEST_SELECT_TIMEOUT
    class SelectThread : public osl::Thread
    {
    public:
        void run()
        {
            m_tsout.tv_sec = 10000000;
            m_tsout.tv_nsec = 1000000 ;

            m_timeout.tv_sec = 10000000;
            m_timeout.tv_usec = 1000000 ;



            SOCKET maxfd = -1;
            int selectret = -1;

            FD_ZERO( &readset );
            FD_ZERO( &writeset );
            FD_ZERO( &exceptset );

            SOCKET sk = socket( AF_INET, SOCK_STREAM, 0 );
            FD_SET( sk, &readset );
            FD_SET( sk, &writeset );
            FD_SET( sk, &exceptset );

            osl::OStringStreamA strTip;
            strTip << "cur time:";
            H_LOG_NAME_DEBUG( "", "enter time" );

            //selectret = select( maxfd+1, &readset, &writeset, &exceptset, &m_timeout );
            selectret = pselect( maxfd + 1, &readset, &writeset, &exceptset, &m_tsout, NULL );

            if ( selectret < 0 )
            {

            }

            H_LOG_NAME_DEBUG( "", "exit time" );
        }

        void clear()
        {
            m_timeout.tv_sec  = 0;
            m_timeout.tv_usec = 0;

            m_tsout.tv_sec  = 0;
            m_tsout.tv_nsec = 0;

            FD_ZERO( &readset );
            FD_ZERO( &writeset );
            FD_ZERO( &exceptset );

            H_LOG_NAME_DEBUG( "", "clear time" );
        }
        fd_set readset, writeset, exceptset ;
        struct timeval m_timeout;
        struct timespec m_tsout;
    };
#endif

} // end of namespace LibTest



namespace LibTest
{


    void TTrivial::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        testAll();
    }

    void TTrivial::testAll()
    {
        test_json_merge_1();

        test_map_1();
        test_hash_map_1();

        //qh_pool();

        test_rsa();

        test_md5();

        test_FileUtil_concatenatePath();
        //testAppShell();
        test_string_resize();
        test_std_string();
        test_atof();
        testStringTrim();
        testLog4cxxForWindows();
        testSelectTimeout();
        testTypeid();
        testDynamicCast();
        testSpiralNumber();
        testHashMap();
        testIntegerConvert();

        testRingBuffer();

        test_vector3df();

        test_stringbuf();

        testBZipCompress();

        testSysErrorCode();
    }

    void TTrivial::test_FileUtil_concatenatePath()
    {

        {
            osl::StringA pre = "a/b/";
            osl::StringA post = "c/d.txt";
            osl::StringA newpath = osl::FileUtil::concatenatePath( pre, post );
            H_ASSERT( newpath == "a/b/c/d.txt" );
        }
        {
            osl::StringA pre = "a/b/";
            osl::StringA post = "/c/d.txt";
            osl::StringA newpath = osl::FileUtil::concatenatePath( pre, post );
            H_ASSERT( newpath == "a/b/c/d.txt" );
        }
        {
            osl::StringA pre = "a/b";
            osl::StringA post = "c/d.txt";
            osl::StringA newpath = osl::FileUtil::concatenatePath( pre, post );
            H_ASSERT( newpath == "a/b/c/d.txt" );
        }
        {
            osl::StringA pre = "a/b";
            osl::StringA post = "/c/d.txt";
            osl::StringA newpath = osl::FileUtil::concatenatePath( pre, post );
            H_ASSERT( newpath == "a/b/c/d.txt" );
        }
    }

    void TTrivial::test_std_string()
    {
        //test a string which contain '\0' in the middle of the char sequence
        {
            osl::MemoryDataStream ds;
            ds.write( "hello", sizeof("hello") );
            ds << int(0);
            ds.write( "world", sizeof("world") );
            osl::StringA s_key_size((const char*)ds.getCache(), ds.getSize() );
            std::cout << "osl::String s_key_size content=\"" << s_key_size << "\"" << std::endl ;
            std::cout << "osl::String s_key_size length=" << s_key_size.length() << std::endl;
            std::cout << "osl::String s_key_size size=" << s_key_size.size() << std::endl;

            osl::StringA s_key_size_copied = s_key_size;
            std::cout << "osl::String s_key_size_copied content=\"" << s_key_size_copied << "\"" << std::endl ;
            std::cout << "osl::String s_key_size_copied length=" << s_key_size_copied.length() << std::endl;

            osl::StringA s_key((const char*)ds.getCache() );
            std::cout << "osl::String s_key_size content=\"" << s_key << "\"" << std::endl ;
            std::cout << "osl::String s_key_size length=" << s_key.length() << std::endl;
            std::cout << "osl::String s_key_size size=" << s_key.size() << std::endl;

            osl::StringA s_key_copied = s_key;
            std::cout << "osl::String s_key_size_copied content=\"" << s_key_copied << "\"" << std::endl ;
            std::cout << "osl::String s_key_size_copied length=" << s_key_copied.length() << std::endl;

        }

#ifdef H_OS_WINDOWS
        osl::StringA s;
        size_t size = 10;
        s.resize( size );
        std::cout << "size()=" << s.size() << std::endl;
        std::cout << "length()=" << s.length() << std::endl;

        s = "Jane";
        osl::StringA name( "1" );
        fillContent( ( osl::StringA )name ); //wrong!!!!

        fillContent( static_cast<osl::StringA>( name ) ); //wrong!!!

        fillContent( name );//ok
        name = "1";
        fillContent( ( osl::StringA& )name ); //ok
        name = "1";
        fillContent( static_cast<osl::StringA&>( name ) ); //ok

        size = 20;
#endif
    }

    void TTrivial::test_string_resize()
    {
        osl::StringA s;
        s.resize( 10 );
        std::cout << "size()=" << s.size() << std::endl;
        std::cout << "length()=" << s.length() << std::endl;

        const char* szhello = "hello world";
        s.resize( strlen( szhello ) );
        strcpy( &s[0], szhello );

        std::cout << "size()=" << s.size() << std::endl;

        s.resize( 15 );
        std::cout << "size()=" << s.size() << std::endl;
        std::cout << "length()=" << s.length() << std::endl;

        const char* pori = s.c_str();
        s.resize( 5 );
        const char* pnew = s.c_str();

        if ( pori == pnew )
        {
            std::cout << "resize small don't change the memory." << std::endl;
        }
        else
        {
            std::cout << "resize small changed the memory." << std::endl;
        }

        osl::StringW ws;
        ws.resize( 10 );
        ws = L"hello world";

        std::cout << "size()=" << ws.size() << std::endl;
        std::cout << "length()=" << ws.length() << std::endl;

        ws.resize( 5 );

        std::cout << "size()=" << ws.size() << std::endl;
        std::cout << "length()=" << ws.length() << std::endl;

    }


    void TTrivial::test_atof()
    {
        //test atof
        const char* sDouble = "15.";
        double d = atof( sDouble );
        sDouble = "0.0000000000";
        d = atof( sDouble );
        int a;
        a = 1;
    }


    void TTrivial::fillContent( osl::StringA& out )
    {
        out = "hello little Jane.";
    }


    void TTrivial::testStringTrim()
    {
        osl::StringA s = "   \t   aaabbb   \t   ";
        osl::StringUtil::trim( s );
        printf( "after trim:'%s'\n", s.c_str() );
    }

    void TTrivial::testLog4cxxForWindows()
    {
        H_LOG_NAME_DEBUG( "a", "aaaaaaaaaaa" );
        H_LOG_NAME_INFO( "b", "bbbb" );
        H_LOG_NAME_ERROR( "c", "ccc" );
        H_LOG_NAME_WARN( "d", "ddd" );
        H_LOG_NAME_TRACE( "e", "eee" );

        H_LOG_NAME_DEBUG( "a", "aaaaaaaaaaa" );
        H_LOG_NAME_INFO( "b", "bbbb" );
        H_LOG_NAME_ERROR( "c", "ccc" );
        H_LOG_NAME_WARN( "d", "ddd" );
        H_LOG_NAME_TRACE( "e", "eee" );

        H_LOG_NAME_DEBUG( "a", "aaaaaaaaaaa" );
        H_LOG_NAME_INFO( "b", "bbbb" );
        H_LOG_NAME_ERROR( "c", "ccc" );
        H_LOG_NAME_WARN( "d", "ddd" );
        H_LOG_NAME_TRACE( "e", "eee" );

    }

    void TTrivial::testTypeid()
    {
        //const type_info si = ;
        //printf( "%s\n", typeid( osl::Base64 ).name() );//print 'class Base64'
        //printf("%s\n", typeid(osl::Base64).raw_name() );//print '**Base64@osl**'
    }

    void TTrivial::testDynamicCast()
    {
//         Json::JSONBoolean jb( true );
//         Json::JSONInteger ji( 12 );
//         Json::Object* pbool = &jb;
//         Json::Object* pint = &ji;
// 
//         if ( dynamic_cast<Json::JSONInteger*>( pbool ) )
//         {
//             printf( "dynamic_cast failed.\n" );
//         }
//         else
//         {
//             printf( "dynamic_cast successfully.\n" );
//         }
// 
//         if ( dynamic_cast<Json::JSONBoolean*>( pbool ) )
//         {
//             printf( "dynamic_cast successfully.\n" );
//         }
//         else
//         {
//             printf( "dynamic_cast failed.\n" );
//         }
// 
//         if ( dynamic_cast<Json::JSONInteger*>( pint ) )
//         {
//             printf( "dynamic_cast successfully.\n" );
//         }
//         else
//         {
//             printf( "dynamic_cast failed.\n" );
//         }
// 
//         printf( "==================\n" );
    }

    void TTrivial::testGetDirFiles( osl::StringA path, osl::StringAVector& files )
    {
#ifdef H_OS_WINDOWS

        long   hFile   =   0;
        struct _finddata_t fileinfo;

        osl::StringA p;

        if   ( ( hFile   =   _findfirst( p.assign( path ).append( "/*" ).c_str(), &fileinfo ) )   !=   -1 )
        {

            do
            {
                if   ( ( fileinfo.attrib   &   _A_SUBDIR ) )
                {
                    if   ( strcmp( fileinfo.name, "." )   !=   0   &&   strcmp( fileinfo.name, ".." )   !=   0 )
                    {
                        testGetDirFiles(   p.assign( path ).append( "/" ).append( fileinfo.name ), files   );
                    }
                }
                else
                {
                    files.push_back(   p.assign( path ).append( "/" ).append( fileinfo.name )  );
                }
            }
            while ( _findnext(   hFile,   &fileinfo   )   ==   0 );

            _findclose( hFile );
        }

#endif
    }


    void TTrivial::testSpiralNumber()
    {
        //i        x,y
        //0        0,0
        //1     0,-1
        //2     1,-1
        //3     1,0
        //4     1,1
        //5     0,1                //    20    19    18    17    16
        //6     -1,1            //    21    6    5    4    15
        //7     -1,0            //    22    7    pid    3    14
        //8     -1,-1            //    23    8    1    2    13
        //9     -1,-2            //    24    9    10    11    12
        //10     0,-2
        //11     1,-2
        //12     2,-2
        //13     2,-1
        //14     2,0
        //...

        //osl::u32 centX = PATCHID_X( m_idPatch.idPatch );
        //osl::u32 centY = PATCHID_Y( m_idPatch.idPatch );

        return;

        osl::OStringStreamA log;
        log << "\n\n\n\n\n\n\n\n\n";

        bool isX = false;
        bool isIncrease = false;
        osl::u32 circleMaxNum[5] = { 3 * 3 - 1, 5 * 5 - 1, 7 * 7 - 1, 9 * 9 - 1, 11 * 11 - 1}; // 5 is ok now. if need update, it should be update to a more bigger number
        osl::s32 circleIndex = 1;
        osl::s32 xOffset = 0;
        osl::s32 yOffset = 1;

        for ( osl::u32 i = 0; i < c_nNumMaxVisiblePatch * c_nNumMaxVisiblePatch; i++ )
        {
            //u32 x = i % c_nNumMaxVisiblePatch + c_nNumMaxVisiblePatch / 2;
            if ( i >= circleMaxNum[circleIndex-1] )
            {
                circleIndex++;
            }

            if ( isX ) // x
            {
                if ( isIncrease ) //increase
                {
                    xOffset++;

                    if ( xOffset >= circleIndex )//now it turns to y
                    {
                        isX = false;

                        if ( yOffset > 0 )// now it turns to decreasing
                        {
                            isIncrease = false;
                        }
                    }
                }
                else //decrease
                {
                    xOffset--;

                    if ( xOffset <= 0 - circleIndex )//now it turns to y
                    {
                        isX = false;

                        if ( yOffset < 0 )// now it turns to increasing
                        {
                            isIncrease = true;
                        }
                    }
                }
            }
            else // y
            {
                if ( isIncrease ) //increase
                {
                    yOffset++;

                    if ( yOffset >= circleIndex )//now it turns to x
                    {
                        isX = true;

                        if ( xOffset > 0 )// now it turns to decreasing
                        {
                            isIncrease = false;
                        }
                    }
                }
                else //decrease
                {
                    yOffset--;

                    if ( yOffset <= 0 - circleIndex )//now it turns to x
                    {
                        isX = true;

                        if ( xOffset <= 0 )// now it turns to increasing
                        {
                            isIncrease = true;
                        }
                    }
                }
            }


            //         offset.x = 0;
            //         offset.y = 0;
            //         Patch::m_U32Offset[0] = offset;

            //         printf( "offset.x = %d;\n", xOffset );
            //         printf( "offset.y = %d;\n", yOffset );
            //         printf( "Patch::m_U32Offset[%d] = offset;\n\n", i );

            //         printf( "Patch::m_U32Offset[%d].x = %d;\n", i, xOffset );
            //         printf( "Patch::m_U32Offset[%d].y = %d;\n\n", i, yOffset );


            log << "case " << i << " :\n"
                << "x += " << xOffset << ";\n"
                << "y += " << yOffset << ";\n"
                << "break;\n";

            //         m_vAdjacentPatches[i] = m_idPatch;
            //        printf( "i=%d,(%d,%d)\n", i, xOffset, yOffset );
            //         if ( centX + xOffset >= 0 && centY + yOffset )
            //         {
            //             m_vAdjacentPatches[i] = PATCHID( centX + xOffset, centY + yOffset );
            //         }
        }//end of for

        log << "\n\n\n\n\n\n\n\n";
        H_LOG_NAME_DEBUG( "", log.str() );

    }




    void TTrivial::testHashMap()
    {
        typedef osl::HashMap<osl::u64, char*> Map;

        //for ( osl::u32 i = 0; i < 10000000000; i++ )
//         while ( 1 )
//         {
//             Map mymap;
//             {
//                 Map::iterator it( mymap.begin() ), ite( mymap.end() );
//
//                 for ( ; it != ite; it++ )
//                 {
//                     printf( "%s\n", it->second );
//                 }
//             }
//
//
//             {
//                 mymap.insert( std::pair<osl::u64, char*>( 1, "hello" ) );
//                 mymap.insert( std::pair<osl::u64, char*>( 2, "world" ) );
//                 mymap.insert( std::pair<osl::u64, char*>( 3, "my" ) );
//                 mymap.insert( std::pair<osl::u64, char*>( 4, "little" ) );
//
//
//                 Map::iterator it( mymap.begin() ), ite( mymap.end() );
//
//                 for ( ; it != ite; it++ )
//                 {
//                     printf( "%s\n", it->second );
//                 }
//
//                 printf( "\n\n--------\n\n" );
//             }
//         }
//
//
//         osl::Process::msSleep( 1111111 );
    }



    void TTrivial::testSelectTimeout()
    {
#ifdef H_TEST_SELECT_TIMEOUT
        {
            // test select work.
            osl::ThreadPtr pThread = new SelectThread;
            pThread->start();

            osl::Process::msSleep( 1000 );

            static_cast<SelectThread*>( pThread.getPointer() )->clear();

            osl::Process::msSleep( 10000 );
        }
#endif
    }

//     bool operator!=( const osl::AppShell::Param& rhs, const osl::AppShell::Param& lhs )
//     {
//         return rhs.strName != lhs.strName || rhs.strVal != lhs.strVal;
//     }
//
    /*
        void TTrivial::testAppShell()
        {

        }
    */
    void TTrivial::testIntegerConvert()
    {
        using std::cout;
        using std::endl;

        char sz[64];
        cout << "\t\tu64toa atou64" << endl;
        {
            osl::xtoa( 0xEFFFFFFFFFFFFFFF , sz );
            osl::u64 l = osl::StringUtil::toU64( sz );
            cout << 0xEFFFFFFFFFFFFFFF << endl;
            cout << sz << endl;
            cout << l << endl;
        }
        cout << "\t\t负数s64toa atos64" << endl;
        {
            osl::xtoa( 0xEFFFFFFFFFFFFFFF , sz );
            osl::s64 l = osl::StringUtil::toS64( sz );
            cout << 0xEFFFFFFFFFFFFFFF << endl;
            cout << sz << endl;
            cout << l << endl;
        }
        cout << "\t\t s64toa atos64" << endl;
        {
            osl::xtoa( 0x7FFFFFFFFFFFFFFF , sz );
            osl::s64 l = osl::StringUtil::toS64( sz );
            cout << 0x7FFFFFFFFFFFFFFF << endl;
            cout << sz << endl;
            cout << l << endl;
        }

        cout << "\t\tu32toa atou32" << endl;

        {
            osl::xtoa( 0xEFFFFFFF , sz );
            osl::u32 l32 = osl::StringUtil::toU32( sz );

            cout << 0xEFFFFFFF << endl;
            cout << sz << endl;
            cout << l32 << endl;
        }
        cout << "\t\t负数 s32toa atos32 " << endl;
        {
            osl::xtoa( 0xEFFFFFFF , sz );//0xEFFFFFFF
            osl::s32 ls32 = osl::StringUtil::toS32( sz );

            cout << 0xEFFFFFFF << endl;
            cout << sz << endl;
            cout << ls32 << endl;
        }
        cout << "\t\ts32toa atos32" << endl;
        {
            osl::xtoa( 0x7FFFFFFF , sz );//0xEFFFFFFF
            osl::s32 ls32 = osl::StringUtil::toS32( sz );

            cout << 0x7FFFFFFF << endl;
            cout << sz << endl;
            cout << ls32 << endl;
        }
    }


    void TTrivial::testRingBuffer()
    {
//         net::PtrRingBuffer ringbuf( 4 );
//         const size_t sz = 10;
//         char words[sz][24] = {"hello", "world", "how", "are", "you", "weizili", "china" };
// 
//         for ( size_t i = 0; i < sz; ++i )
//         {
//             char* szstring = (char*)ringbuf.pop_front();
//         }
// 
// 
//         for ( size_t i = 0; i < sz; ++i )
//         {
//             ringbuf.push_back( words[i] );
//         }
// 
//         for ( size_t i = 0; i < sz; ++i )
//         {
//             char* szstring = (char*)ringbuf.pop_front();
//         }
    }

    void TTrivial::testBZipCompress()
    {
//         for ( size_t i = 10; i < 5000; i++ )
//         {
//             osl::StringA strFilePath = osl::Process::getConfDir() + "/" + "networklibconf.xml";
//             osl::MemoryDataStream databuf_src;
//             databuf_src.readRawFile( strFilePath );
// 
//             if ( databuf_src.getSize() > i )
//             {
//                 databuf_src.setSize( (osl::u32)i );
//             }
// 
//             int eCompressMethod = (int)Z_DEFAULT_COMPRESSION;
// 
//             unsigned long  nDestLength = databuf_src.getSize() + 100;
//             unsigned long  nSrcLength = databuf_src.getSize();
//             osl::MemoryDataStream databuf_compressed( nDestLength + 100 );
//             int retv = compress2( (Bytef*)databuf_compressed.getCache(), &nDestLength , 
//                 static_cast<const Bytef*>( databuf_src.getCache() ) , nSrcLength, eCompressMethod );
//             if ( Z_OK != retv )
//             {
//                 H_ASSERT( false && "compress failed." );
//             }
//             databuf_compressed.seekp( nDestLength );
// 
// 
//             unsigned long  nDestLen_decompressed = databuf_src.getSize() * 2;
//             osl::MemoryDataStream databuf_decompressed( nDestLen_decompressed );
//             retv = uncompress( (Bytef*)databuf_decompressed.getCache(), &nDestLen_decompressed, (const Bytef*)databuf_compressed.getCache(), nDestLength );
//             if ( Z_OK != retv )
//             {
//                 H_ASSERT( false && "decompress failed." );
//             }
//             databuf_decompressed.seekp( nDestLen_decompressed );
// 
//             H_ASSERT( databuf_src.getSize() == databuf_decompressed.getSize() && "test failed." );
//             for ( size_t i = 0; i < databuf_src.getSize(); i++ )
//             {
//                 H_ASSERT( databuf_src.charAt(i) == databuf_decompressed.charAt(i) && "failed." );
//             }
//             
//         }//end of for
// 
//         {
// 
//         }
    }

    namespace
    {
        struct _EXPORT_OSLIB memtest
        {
            memtest();
            ~memtest();
            static void *add( unsigned int size, void *address );
            static void sub( void *block );
            static void log();
        };

    }

    void TTrivial::testmem()
    {

    }

    void TTrivial::testSysErrorCode()
    {
        using namespace std;
//         cout << "WSAEWOULDBLOCK=" << WSAEWOULDBLOCK << endl;
//         cout << "EAGAIN=" << EAGAIN  << endl;
    }

    void TTrivial::test_vector3df()
    {
        
    }

    class mystringbuf : public std::stringbuf
    {
    public:
        char* getwritebuf()
        {
            return pbase();
        }
        
        size_t getreadablesize() 
        {
            return (size_t)in_avail();
        }
    };
    void TTrivial::test_stringbuf()
    {
        mystringbuf sb;
        sb.sputc( 'a' );
        sb.sputn( "bcdefgh", 7 );
        char* pd = sb.getwritebuf();
        std::string str = sb.str();
        std::cout << __func__ << " writebuf=" << pd << std::endl;
        std::cout << __func__ << " str=" << str.c_str() << std::endl;
        
    }

    void TTrivial::test_md5()
    {
        osl::MemoryDataStream ds;
        ds << "abcdaljdslfjalsdjfqpoiuerpoqiuewr9127834012384-08fjsd;lfjas;ldfa'sdfp['qpoweirqwuier-01984-2307419273sdajf;aj  jas;ldfjapoifuq987401234dsjfa;ljasjd;flasjdf;ljasd;fjasdfoihasdpoifhpasoidfpqwoeiurpqowief;lksdj;kxncv/zxcnv/,zxcv;wqejrpoweiur01239874012987502135861023987098uaesfpoisjd;fajsd;vlckxncv;zlkvj'sadpf]sadfsdfcxlvkaj;sdjifasdf";

        {
            //old HMD5, error
//             {
//                 osl::HMD5 md5( (const osl::u8*)ds.getCache(), ds.getSize() );
//                 osl::u8 result[33] = {};
//                 md5.getHexDigest( result );
//                 std::cout << result << std::endl;
//                 //H_ASSERT( strcmp( "127fe73c2db3436a948b1c41469dc9e0", (const char*)result ) == 0 );
//             }

            //new MD5
            {
                osl::MD5 md5;
                md5.update( (unsigned char *)ds.getCache(), ds.getSize() );
                md5.finalize();
                char result[33] ={'\0'} ; 
                md5.getHexDigest(result);
                std::cout << result << std::endl;
                //H_ASSERT( strncmp( "127fe73c2db3436a948b1c41469dc9e0", (const char*)result, 32 ) == 0 );
            }

            {
                char result1[33] = {0};
                {
                    osl::MD5 md5;
                    for ( unsigned int i = 0; i < ds.getSize(); ++i )
                    {
                        md5.update( ((unsigned char*)ds.getCache()) + i, 1 );
                    }
                    md5.finalize();
                    md5.getHexDigest( result1 );
                }

                char result8[33] = {0};
                {
                    osl::MD5 md5;
                    const int UNIT_LEN = 8;
                    int oct = ds.getSize()/UNIT_LEN;
                    for ( int i = 0; i < oct; ++i )
                    {
                        md5.update( ((unsigned char*)ds.getCache()) + i * UNIT_LEN, UNIT_LEN );
                    }
                    
                    int remain = ds.getSize() % UNIT_LEN;
                    if ( remain != 0 )
                    {
                        md5.update( ((unsigned char*)ds.getCache()) + ds.getSize() - remain, remain );
                    }
                    

                    md5.finalize();
                    md5.getHexDigest( result8 );
                }


                H_ASSERT( strcmp( result1, result8 ) == 0 );
            }
        }
    }

    void TTrivial::test_rsa()
    {
#if H_PROVIDE_RSA
        const size_t BUF_SIZE = 1024;
        const size_t KEY_LEN = 1024;
        unsigned char publickey [BUF_SIZE] = {0};
        unsigned char privatekey[BUF_SIZE] = {0};
        size_t publickey_len = 0;
        size_t privatekey_len = 0;
        bool ret = osl::Rsa::generateKey( KEY_LEN, publickey, &publickey_len, privatekey, &privatekey_len );
        std::cout << "osl::Rsa::generateKey return="  << ret << std::endl;
        if ( !ret )
        {
            return;
        }
        
        osl::Rsa rsa_private( privatekey, privatekey_len, osl::Rsa::KT_PRIVATE );
        osl::Rsa rsa_public ( publickey,  publickey_len,  osl::Rsa::KT_PUBLIC );
        const char* data = "asdfjlasjflasjdflajsdlkfjasdlkfajsdlkfjas;dlkf";
        size_t data_len = strlen(data);

        unsigned char sigret[2048] = {0};
        size_t siglen  = 0;

        ret = rsa_private.sign( osl::Rsa::ST_NID_sha1, (unsigned char*)data, data_len, sigret, &siglen );
        std::cout << "osl::Rsa::sign return="  << ret << std::endl;
        ret = rsa_public.verify( osl::Rsa::ST_NID_sha1, (unsigned char*)data, data_len, sigret, siglen );
        std::cout << "osl::Rsa::verify return="  << ret << std::endl;
#endif
    }

/*
    namespace
    {
        struct SArray
        {
            char* _B16;  
            char* _B24;  
            char* _B32;  
            char* _B40;  
            char* _B48;  
            char* _B56;  
            char* _B64;  
            char* _B72;  
            char* _B80;  
            char* _B88;  
            char* _B96;  
            char* _B114; 
            char* _B128; 
            char* _B136; 
            char* _B144; 
            char* _B152; 
            char* _B160; 
            char* _B168; 
            char* _B176; 
            char* _B184; 
            char* _B192;

            qh_pool_t* pool;

            SArray( qh_pool_t* pool ) 
            { 
                memset( this, 0, sizeof(SArray) );
                this->pool = pool;
            }

            ~SArray()
            {
                freemem();
            }

            void allocmem()
            {
                int len = 8;
                _B16  = (char*)qh_palloc( pool, (len = len + 8) );
                _B24  = (char*)qh_palloc( pool, (len = len + 8) );
                _B32  = (char*)qh_palloc( pool, (len = len + 8) );
                _B40  = (char*)qh_palloc( pool, (len = len + 8) );
                _B48  = (char*)qh_palloc( pool, (len = len + 8) );
                _B56  = (char*)qh_palloc( pool, (len = len + 8) );
                _B64  = (char*)qh_palloc( pool, (len = len + 8) );
                _B72  = (char*)qh_palloc( pool, (len = len + 8) );
                _B80  = (char*)qh_palloc( pool, (len = len + 8) );
                _B88  = (char*)qh_palloc( pool, (len = len + 8) );
                _B96  = (char*)qh_palloc( pool, (len = len + 8) );
                _B114 = (char*)qh_palloc( pool, (len = len + 8) );
                _B128 = (char*)qh_palloc( pool, (len = len + 8) );
                _B136 = (char*)qh_palloc( pool, (len = len + 8) );
                _B144 = (char*)qh_palloc( pool, (len = len + 8) );
                _B152 = (char*)qh_palloc( pool, (len = len + 8) );
                _B160 = (char*)qh_palloc( pool, (len = len + 8) );
                _B168 = (char*)qh_palloc( pool, (len = len + 8) );
                _B176 = (char*)qh_palloc( pool, (len = len + 8) );
                _B184 = (char*)qh_palloc( pool, (len = len + 8) );
                _B192 = (char*)qh_palloc( pool, (len = len + 8) );
            }

            void setvalue()
            {
                int len = 16;
                char a = 'A';
                memset( _B16  , a, len ); len = len + 8; a++;
                memset( _B24  , a, len ); len = len + 8; a++;
                memset( _B32  , a, len ); len = len + 8; a++;
                memset( _B40  , a, len ); len = len + 8; a++;
                memset( _B48  , a, len ); len = len + 8; a++;
                memset( _B56  , a, len ); len = len + 8; a++;
                memset( _B64  , a, len ); len = len + 8; a++;
                memset( _B72  , a, len ); len = len + 8; a++;
                memset( _B80  , a, len ); len = len + 8; a++;
                memset( _B88  , a, len ); len = len + 8; a++;
                memset( _B96  , a, len ); len = len + 8; a++;
                memset( _B114 , a, len ); len = len + 8; a++;
                memset( _B128 , a, len ); len = len + 8; a++;
                memset( _B136 , a, len ); len = len + 8; a++;
                memset( _B144 , a, len ); len = len + 8; a++;
                memset( _B152 , a, len ); len = len + 8; a++;
                memset( _B160 , a, len ); len = len + 8; a++;
                memset( _B168 , a, len ); len = len + 8; a++;
                memset( _B176 , a, len ); len = len + 8; a++;
                memset( _B184 , a, len ); len = len + 8; a++;
                memset( _B192 , a, len ); len = len + 8; a++;
            }

            void checkvalue()
            {
                int len = 16;
                char a = _B16[0];
                assert( assertto( _B16  , len, a ) ); len = len + 8; a++;
                assert( assertto( _B24  , len, a ) ); len = len + 8; a++;
                assert( assertto( _B32  , len, a ) ); len = len + 8; a++;
                assert( assertto( _B40  , len, a ) ); len = len + 8; a++;
                assert( assertto( _B48  , len, a ) ); len = len + 8; a++;
                assert( assertto( _B56  , len, a ) ); len = len + 8; a++;
                assert( assertto( _B64  , len, a ) ); len = len + 8; a++;
                assert( assertto( _B72  , len, a ) ); len = len + 8; a++;
                assert( assertto( _B80  , len, a ) ); len = len + 8; a++;
                assert( assertto( _B88  , len, a ) ); len = len + 8; a++;
                assert( assertto( _B96  , len, a ) ); len = len + 8; a++;
                assert( assertto( _B114 , len, a ) ); len = len + 8; a++;
                assert( assertto( _B128 , len, a ) ); len = len + 8; a++;
                assert( assertto( _B136 , len, a ) ); len = len + 8; a++;
                assert( assertto( _B144 , len, a ) ); len = len + 8; a++;
                assert( assertto( _B152 , len, a ) ); len = len + 8; a++;
                assert( assertto( _B160 , len, a ) ); len = len + 8; a++;
                assert( assertto( _B168 , len, a ) ); len = len + 8; a++;
                assert( assertto( _B176 , len, a ) ); len = len + 8; a++;
                assert( assertto( _B184 , len, a ) ); len = len + 8; a++;
                assert( assertto( _B192 , len, a ) ); len = len + 8; a++;
            }

            void freemem()
            {
                qh_pfree( pool, _B16  );   _B16  = NULL;
                qh_pfree( pool, _B24  );   _B24  = NULL;
                qh_pfree( pool, _B32  );   _B32  = NULL;
                qh_pfree( pool, _B40  );   _B40  = NULL;
                qh_pfree( pool, _B48  );   _B48  = NULL;
                qh_pfree( pool, _B56  );   _B56  = NULL;
                qh_pfree( pool, _B64  );   _B64  = NULL;
                qh_pfree( pool, _B72  );   _B72  = NULL;
                qh_pfree( pool, _B80  );   _B80  = NULL;
                qh_pfree( pool, _B88  );   _B88  = NULL;
                qh_pfree( pool, _B96  );   _B96  = NULL;
                qh_pfree( pool, _B114 );   _B114 = NULL;
                qh_pfree( pool, _B128 );   _B128 = NULL;
                qh_pfree( pool, _B136 );   _B136 = NULL;
                qh_pfree( pool, _B144 );   _B144 = NULL;
                qh_pfree( pool, _B152 );   _B152 = NULL;
                qh_pfree( pool, _B160 );   _B160 = NULL;
                qh_pfree( pool, _B168 );   _B168 = NULL;
                qh_pfree( pool, _B176 );   _B176 = NULL;
                qh_pfree( pool, _B184 );   _B184 = NULL;
                qh_pfree( pool, _B192 );   _B192 = NULL;
            }

            static bool assertto( const char* array, int arraysize, int content )
            {
                for ( int j = 0; j < arraysize; ++j )
                {
                    if ( array[j] != content )
                    {
                        return false;
                    }
                }

                return true;
            } 
        };
    }

    void TTrivial::qh_pool()
    {
        std::cout << "\n\n\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+ begin " << __FUNCTION__ << " =+=+=+=+=+=+=+=+=+=+=+=+=+=+\n\n\n";

        qh_pool_test_1();
        qh_pool_test_2();
        qh_pool_test_3();
        

        std::cout << "\n\n\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+ end " << __FUNCTION__ << " =+=+=+=+=+=+=+=+=+=+=+=+=+=+\n\n\n";
    }

    void TTrivial::qh_pool_test_1()
    {
        {
            qh_pool_t* pool = qh_create_pool( 1024 * 1024, 128 ); //1M pool
            qh_destroy_pool(pool);
        }
    }


    void TTrivial::qh_pool_test_2()
    {
        qh_pool_t* pool = qh_create_pool( 1024, 128 ); //1M pool
        for ( int i = 1; i < 10000; i++)
        {
            int len = i * 2;
            void* p1 = qh_palloc( pool, len );
            memset( p1, 'A', len );
            assert( SArray::assertto((char*)p1, len, 'A' ) );
            qh_pfree( pool, p1 );

            void* p2 = qh_palloc( pool, len );
            memset( p2, 'B', len );
            assert( SArray::assertto((char*)p2, len, 'B' ) );
            qh_pfree( pool, p2 );
        }
        qh_destroy_pool(pool);
    }

    void TTrivial::qh_pool_test_3()
    {
        qh_pool_t* pool = qh_create_pool( 1024 * 1024, 32 ); //1M pool

        for ( int i = 0; i < 20; ++i )
        {
            SArray sa( pool );
            sa.allocmem();
            sa.setvalue();
            sa.checkvalue();
            sa.freemem();
        }

        qh_destroy_pool(pool);
    }
    */

    struct str_less
    {/*{{{*/
        bool operator()(const char* s1, const char* s2) const
        {
            return strcmp(s1, s2) < 0;
        }
    };/*}}}*/

    void TTrivial::test_map_1()
    {
        typedef std::map< const char*, int, str_less> StrIntMap;
        StrIntMap simap;
        std::string s1 = std::string("aaa");
        std::string s2 = std::string("aaa");
        std::string s3 = std::string("aaa");

        const char* key1 = s1.c_str();
        const char* key2 = s2.c_str();
        const char* key3 = s3.c_str();

        const char* key1_dup = strdup(key1);
        const char* key2_dup = strdup(key2);
        const char* key3_dup = strdup(key3);

        std::cout << "key1=0x" << std::hex << (long)key1 << std::endl;
        std::cout << "key2=0x" << std::hex << (long)key2 << std::endl;
        std::cout << "key3=0x" << std::hex << (long)key3 << std::endl;
        std::cout << "key1_dup=0x" << std::hex << (long)key1_dup << std::endl;
        std::cout << "key2_dup=0x" << std::hex << (long)key2_dup << std::endl;
        std::cout << "key3_dup=0x" << std::hex << (long)key3_dup << std::endl;


        std::cout << std::dec;

        simap[key1] = 1;
        simap[key2] = 2;
        simap[key3] = 3;

        simap[key1_dup] = 11;
        simap[key2_dup] = 22;
        simap[key3_dup] = 33;

        StrIntMap::iterator it;

        it = simap.find( key1 );
        std::cout << "key1->value=" << it->second << std::endl;
        assert( it->first == key1 );

        it = simap.find( key2 );
        std::cout << "key2->value=" << it->second << std::endl;
        assert( it->first == key1 );

        it = simap.find( key3 );
        std::cout << "key3->value=" << it->second << std::endl;
        assert( it->first == key1 );


        it = simap.find( key1_dup );
        std::cout << "key1_dup->value=" << it->second << std::endl;
        assert( it->first == key1 );

        it = simap.find( key2_dup );
        std::cout << "key2_dup->value=" << it->second << std::endl;
        assert( it->first == key1 );

        it = simap.find( key3_dup );
        std::cout << "key3_dup->value=" << it->second << std::endl;
        assert( it->first == key1 );

        it = simap.find( "" );
    }



    void TTrivial::test_hash_map_1()
    {
#ifdef H_OS_WINDOWS
        typedef stdext::hash_map< const char*, int, ::stdext::hash_compare< const char*, str_less > > StrIntMap;
        StrIntMap simap;
        std::string s1 = std::string("aaa");
        std::string s2 = std::string("aaa");
        std::string s3 = std::string("aaa");

        const char* key1 = s1.c_str();
        const char* key2 = s2.c_str();
        const char* key3 = s3.c_str();

        const char* key1_dup = strdup(key1);
        const char* key2_dup = strdup(key2);
        const char* key3_dup = strdup(key3);

        std::cout << "key1=0x" << std::hex << (long)key1 << std::endl;
        std::cout << "key2=0x" << std::hex << (long)key2 << std::endl;
        std::cout << "key3=0x" << std::hex << (long)key3 << std::endl;
        std::cout << "key1_dup=0x" << std::hex << (long)key1_dup << std::endl;
        std::cout << "key2_dup=0x" << std::hex << (long)key2_dup << std::endl;
        std::cout << "key3_dup=0x" << std::hex << (long)key3_dup << std::endl;

        std::cout << std::dec;

        simap[key1] = 1;
        simap[key2] = 2;
        simap[key3] = 3;

        simap[key1_dup] = 11;
        simap[key2_dup] = 22;
        simap[key3_dup] = 33;

        StrIntMap::iterator it;

        it = simap.find( key1 );
        std::cout << "key1->value=" << it->second << std::endl;
        assert( it->first == key1 );

        it = simap.find( key2 );
        std::cout << "key2->value=" << it->second << std::endl;
        assert( it->first == key1 );

        it = simap.find( key3 );
        std::cout << "key3->value=" << it->second << std::endl;
        assert( it->first == key1 );


        it = simap.find( key1_dup );
        std::cout << "key1_dup->value=" << it->second << std::endl;
        assert( it->first == key1 );

        it = simap.find( key2_dup );
        std::cout << "key2_dup->value=" << it->second << std::endl;
        assert( it->first == key1 );

        it = simap.find( key3_dup );
        std::cout << "key3_dup->value=" << it->second << std::endl;
        assert( it->first == key1 );

        it = simap.find( "" );
#endif
        
    }

    void TTrivial::test_json_merge_1()
    {
        json::JSONObject j1;
        json::JSONObject j2;
        const char* key1 = "apple";
        const char* key2 = "orange";
        const char* value1 = "value1";
        const char* value1_1 = "value1_1";
        const char* value2 = "value2";
        j1.put( key1, value1 );


        j2.put( key1, value1_1 );
        j2.put( key2, value2 );


        j1.merge( &j2, false );
        assert( j1.getString( key1 ) == value1 );
        assert( j1.getString( key2 ) == value2 );

        j1.merge( &j2, true );
        assert( j1.getString( key1 ) == value1_1 );
        assert( j1.getString( key2 ) == value2 );

        std::cout << "verify JSONObject::merge pass" << std::endl;
    }

}//end of namespace LibTest

CREATE_FUNCTION( TTrivial );







