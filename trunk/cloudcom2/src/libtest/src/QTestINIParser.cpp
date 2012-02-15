#include "libtest/include/QLibTestPrerequisits.h"

#include "libtest/include/QTestObject.h"
#include "osl/include/file_util.h"
#include "osl/include/ini_parser.h"

namespace
{
    class TINIParser : public LibTest::ITestObject
    {
        void testAll();
        const char* getCommand();
        const char* getDesc();
        void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );


        void test_1();
        void test_2();
        void test_3();
        void test_4();
        void test_5();
    };

    const char* TINIParser::getCommand()
    {
        return "test_iniparser";
    }

    const char* TINIParser::getDesc()
    {
        return "test_iniparser";
    }

    void TINIParser::testAll()
    {
        test_1();
        test_2();
        test_3();
        test_4();
        test_5();

        std::cout << "test_INIParser OK!" << std::endl;
    }

    void TINIParser::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        testAll();
    }

    void TINIParser::test_1()
    {
        osl::StringA strTestDataDirPath = osl::Process::getBinDir( true ) + "../data/libtestdata/qoslib/iniparser";
        osl::StringAList files;
        osl::FileUtil::getFiles( strTestDataDirPath, files, false );
        osl::StringAList::iterator it( files.begin() );
        osl::StringAList::iterator ite( files.end() );

        for ( ; it != ite; ++it )
        {
            osl::INIParser parser;
            parser.parse( *it );

            if ( osl::StringUtil::contains( *it, "auth.ini" ) )
            {
                {
                    osl::StringA key = "USER_VERIFY_INTF";
                    osl::StringA value = "http://192.168.0.181:8360/datasafe/interface_check.php";
                    assert( value == parser.get( key ) );
                }

                {
                    osl::StringA key = "KEY_ADMIN_INTF";
                    osl::StringA value = "http://192.168.0.181:8360/datasafe/interface_getkey.php";
                    assert( value == parser.get( key ) );
                }


                {
                    osl::StringA key = "OP_END_INTF";
                    osl::StringA value = "http://192.168.0.181:8360/datasafe/interface_done.php";
                    assert( value == parser.get( key ) );
                }


                {
                    osl::StringA key = "REQ_TIMEOUT";
                    osl::StringA value = "30";
                    assert( value == parser.get( key ) );
                }
            }
            else
            {
                const osl::StringAStringAMap& kvmap = parser.getKeyValueMap();
                osl::StringAStringAMap::const_iterator itm( kvmap.begin() );
                osl::StringAStringAMap::const_iterator itme( kvmap.end() );
                for ( ; itm != itme; ++itm )
                {
                    std::cout << itm->first << "=" << itm->second << std::endl;
                }
            }
        }
        
    }

    void TINIParser::test_2()
    {
        osl::StringA strTestDataDirPath = osl::Process::getBinDir( true ) + "../data/libtestdata/qoslib/iniparser";
        osl::StringAList files;
        osl::FileUtil::getFiles( strTestDataDirPath, files, false );
        osl::StringAList::iterator it( files.begin() );
        osl::StringAList::iterator ite( files.end() );

        for ( ; it != ite; ++it )
        {
            osl::MemoryDataStream ds;
            ds.readRawFile( *it );
            osl::INIParser parser;
            parser.parse( (const char*)ds.getCache(), ds.getSize() );

            if ( osl::StringUtil::contains( *it, "auth.ini" ) )
            {
                {
                    osl::StringA key = "USER_VERIFY_INTF";
                    osl::StringA value = "http://192.168.0.181:8360/datasafe/interface_check.php";
                    assert( value == parser.get( key ) );
                }

                {
                    osl::StringA key = "KEY_ADMIN_INTF";
                    osl::StringA value = "http://192.168.0.181:8360/datasafe/interface_getkey.php";
                    assert( value == parser.get( key ) );
                }


                {
                    osl::StringA key = "OP_END_INTF";
                    osl::StringA value = "http://192.168.0.181:8360/datasafe/interface_done.php";
                    assert( value == parser.get( key ) );
                }


                {
                    osl::StringA key = "REQ_TIMEOUT";
                    osl::StringA value = "30";
                    assert( value == parser.get( key ) );
                }
            }
            else
            {
                const osl::StringAStringAMap& kvmap = parser.getKeyValueMap();
                osl::StringAStringAMap::const_iterator itm( kvmap.begin() );
                osl::StringAStringAMap::const_iterator itme( kvmap.end() );
                for ( ; itm != itme; ++itm )
                {
                    std::cout << itm->first << "=" << itm->second << std::endl;
                }
            }
        }
    }

    void TINIParser::test_3()
    {
        const char* rawdata = "mid=ac9219aa5232c4e519ae5fcb4d77ae5b\r\n"
            "#this is a commit\r\n"
            "#commit=this is a commit\r\n"
            "//anothercomit=this is a commit\r\n"
            "product=360se\r\n"
            "combo=sedl\r\n"
            "\r\n"
            "version=4.4\r\n"
            "            \r\n"
            "            \n"
            "appext=\r\n"
            "sample_0=a05ae0fdd08f22f895c8ae84fb55e89f\ne:/the/path/to/sample1\n12635838\n1\n2d361a19246a3ebf4a043d8e31009d77|9d145f6facb9bfe90c902fb85cdbacee|bb3a1cdea67508dc89a24359c00dcdf9\n\n1\n\nW25hbWVdCm1vZHVsZT1xZHgKZGVzY3JpcHRpb249UURYIERhdGEgZVhjaGFuZ2UgcHJvamVjdAogICAKW2RlcGVuZF0KbW9kdWxlMT1DbG91ZExvZy0xLjAuNAo=\r\n"
            "\r\n"
            "sample_1=570836cd47fff497e2b74b98cc7ad687\ne:/the/path/to/sample2\n87687323\n1\n85419bbe8a1f55dea1b3d3e583eba96b|a177b861d3020c04fc2a0847f2268e5d|366cb9b61c23671a56104ce09cd4a5b6\n\n1\n\nPD9waHAKCmlmICgkYXJnYyAhPSAyKSB7CglwcmludGYoIlV\r\n"
            "\r\n"
            "            \r\n"
            "\r\n";
        size_t rawdatalen = strlen( rawdata );
        osl::INIParser parser;
        parser.parse( rawdata, rawdatalen, "\r\n", "=" );

        {
            {
                osl::StringA key = "mid";
                osl::StringA value = "ac9219aa5232c4e519ae5fcb4d77ae5b";
                assert( value == parser.get( key ) );
            }

            {
                osl::StringA key = "product";
                osl::StringA value = "360se";
                assert( value == parser.get( key ) );
            }

            {
                osl::StringA key = "combo";
                osl::StringA value = "sedl";
                assert( value == parser.get( key ) );
            }

            {
                osl::StringA key = "version";
                osl::StringA value = "4.4";
                assert( value == parser.get( key ) );
            }

            {
                osl::StringA key = "appext";
                osl::StringA value = "";
                assert( value == parser.get( key ) );
            }

            {
                osl::StringA key = "sample_0";
                osl::StringA value = "a05ae0fdd08f22f895c8ae84fb55e89f\ne:/the/path/to/sample1\n12635838\n1\n2d361a19246a3ebf4a043d8e31009d77|9d145f6facb9bfe90c902fb85cdbacee|bb3a1cdea67508dc89a24359c00dcdf9\n\n1\n\nW25hbWVdCm1vZHVsZT1xZHgKZGVzY3JpcHRpb249UURYIERhdGEgZVhjaGFuZ2UgcHJvamVjdAogICAKW2RlcGVuZF0KbW9kdWxlMT1DbG91ZExvZy0xLjAuNAo=";
                assert( value == parser.get( key ) );
            }

            {
                osl::StringA key = "sample_1";
                osl::StringA value = "570836cd47fff497e2b74b98cc7ad687\ne:/the/path/to/sample2\n87687323\n1\n85419bbe8a1f55dea1b3d3e583eba96b|a177b861d3020c04fc2a0847f2268e5d|366cb9b61c23671a56104ce09cd4a5b6\n\n1\n\nPD9waHAKCmlmICgkYXJnYyAhPSAyKSB7CglwcmludGYoIlV";
                assert( value == parser.get( key ) );
            }
        }

        const osl::StringAStringAMap& kvmap = parser.getKeyValueMap();
        osl::StringAStringAMap::const_iterator it( kvmap.begin() );
        osl::StringAStringAMap::const_iterator ite( kvmap.end() );
        for ( ; it != ite; ++it )
        {

        }
        
    }


    void TINIParser::test_4()
    {
        const char* rawdata = "mid=ac9219aa5232c4e519ae5fcb4d77ae5b\r\n"
            "product=360se\r\n"
            "combo=sedl\r\n"
            "version=4.4\r\n"
            "appext=";
        size_t rawdatalen = strlen( rawdata );
        osl::INIParser parser;
        parser.parse( rawdata, rawdatalen, "\r\n", "=" );

        {
            {
                osl::StringA key = "mid";
                osl::StringA value = "ac9219aa5232c4e519ae5fcb4d77ae5b";
                assert( value == parser.get( key ) );
            }

            {
                osl::StringA key = "product";
                osl::StringA value = "360se";
                assert( value == parser.get( key ) );
            }

            {
                osl::StringA key = "combo";
                osl::StringA value = "sedl";
                assert( value == parser.get( key ) );
            }

            {
                osl::StringA key = "version";
                osl::StringA value = "4.4";
                assert( value == parser.get( key ) );
            }

            {
                osl::StringA key = "appext";
                osl::StringA value = "";
                assert( value == parser.get( key ) );
            }
        }

        const osl::StringAStringAMap& kvmap = parser.getKeyValueMap();
        osl::StringAStringAMap::const_iterator it( kvmap.begin() );
        osl::StringAStringAMap::const_iterator ite( kvmap.end() );
        for ( ; it != ite; ++it )
        {

        }

    }

    void TINIParser::test_5()
    {
        osl::MemoryDataStream ds;
#ifdef H_OS_WINDOWS
        if ( !ds.readRawFile("E:/download/msv.request.content.444d0c2443dde24a120647d4e9db307d") )
#else
        if ( !ds.readRawFile("/da1/weizili/msv.request.content.444d0c2443dde24a120647d4e9db307d") )
#endif
        {
            return;
        }
        osl::INIParser parser;
        parser.parse( (const char*)ds.getCache(), ds.getSize(), "\r\n", "=" );

        {
            osl::StringA key = "mid";
            osl::StringA value = "ac9219aa5232c4e519ae5fcb4d77ae5b";
            osl::StringA value1 = parser.get( key );
        }

    }
}





CREATE_FUNCTION( TINIParser );












