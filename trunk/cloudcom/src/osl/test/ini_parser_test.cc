#include "osl/include/test_common.h"

#include "osl/include/ini_parser.h"
#include "osl/include/process_ext.h"
#include "osl/include/data_stream.h"
#include "osl/include/file_util.h"

namespace
{

    void test_1()
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
                    H_TEST_ASSERT( value == parser.get( key ) );
                }

                {
                    osl::StringA key = "KEY_ADMIN_INTF";
                    osl::StringA value = "http://192.168.0.181:8360/datasafe/interface_getkey.php";
                    H_TEST_ASSERT( value == parser.get( key ) );
                }


                {
                    osl::StringA key = "OP_END_INTF";
                    osl::StringA value = "http://192.168.0.181:8360/datasafe/interface_done.php";
                    H_TEST_ASSERT( value == parser.get( key ) );
                }


                {
                    osl::StringA key = "REQ_TIMEOUT";
                    osl::StringA value = "30";
                    H_TEST_ASSERT( value == parser.get( key ) );
                }
            }
            else
            {
                const osl::INIParser::StringAStringAMap& kvmap = parser.getDefaultKeyValueMap();
                osl::INIParser::StringAStringAMap::const_iterator itm( kvmap.begin() );
                osl::INIParser::StringAStringAMap::const_iterator itme( kvmap.end() );
                for ( ; itm != itme; ++itm )
                {
                    //std::cout << itm->first << "=" << itm->second << std::endl;
                }
            }
        }
    }

    void test_2()
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
                    H_TEST_ASSERT( value == parser.get( key ) );
                }

                {
                    osl::StringA key = "KEY_ADMIN_INTF";
                    osl::StringA value = "http://192.168.0.181:8360/datasafe/interface_getkey.php";
                    H_TEST_ASSERT( value == parser.get( key ) );
                }


                {
                    osl::StringA key = "OP_END_INTF";
                    osl::StringA value = "http://192.168.0.181:8360/datasafe/interface_done.php";
                    H_TEST_ASSERT( value == parser.get( key ) );
                }


                {
                    osl::StringA key = "REQ_TIMEOUT";
                    osl::StringA value = "30";
                    H_TEST_ASSERT( value == parser.get( key ) );
                }
            }
            else
            {
                const osl::INIParser::StringAStringAMap& kvmap = parser.getDefaultKeyValueMap();
                osl::INIParser::StringAStringAMap::const_iterator itm( kvmap.begin() );
                osl::INIParser::StringAStringAMap::const_iterator itme( kvmap.end() );
                for ( ; itm != itme; ++itm )
                {
                    //std::cout << itm->first << "=" << itm->second << std::endl;
                }
            }
        }
    }

    void test_3()
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
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "product";
                osl::StringA value = "360se";
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "combo";
                osl::StringA value = "sedl";
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "version";
                osl::StringA value = "4.4";
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "appext";
                osl::StringA value = "";
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "sample_0";
                osl::StringA value = "a05ae0fdd08f22f895c8ae84fb55e89f\ne:/the/path/to/sample1\n12635838\n1\n2d361a19246a3ebf4a043d8e31009d77|9d145f6facb9bfe90c902fb85cdbacee|bb3a1cdea67508dc89a24359c00dcdf9\n\n1\n\nW25hbWVdCm1vZHVsZT1xZHgKZGVzY3JpcHRpb249UURYIERhdGEgZVhjaGFuZ2UgcHJvamVjdAogICAKW2RlcGVuZF0KbW9kdWxlMT1DbG91ZExvZy0xLjAuNAo=";
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "sample_1";
                osl::StringA value = "570836cd47fff497e2b74b98cc7ad687\ne:/the/path/to/sample2\n87687323\n1\n85419bbe8a1f55dea1b3d3e583eba96b|a177b861d3020c04fc2a0847f2268e5d|366cb9b61c23671a56104ce09cd4a5b6\n\n1\n\nPD9waHAKCmlmICgkYXJnYyAhPSAyKSB7CglwcmludGYoIlV";
                H_TEST_ASSERT( value == parser.get( key ) );
            }
        }

        const osl::INIParser::StringAStringAMap& kvmap = parser.getDefaultKeyValueMap();
        osl::INIParser::StringAStringAMap::const_iterator it( kvmap.begin() );
        osl::INIParser::StringAStringAMap::const_iterator ite( kvmap.end() );
        for ( ; it != ite; ++it )
        {

        }

    }


    void test_4()
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
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "product";
                osl::StringA value = "360se";
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "combo";
                osl::StringA value = "sedl";
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "version";
                osl::StringA value = "4.4";
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "appext";
                osl::StringA value = "";
                H_TEST_ASSERT( value == parser.get( key ) );
            }
        }

        const osl::INIParser::StringAStringAMap& kvmap = parser.getDefaultKeyValueMap();
        osl::INIParser::StringAStringAMap::const_iterator it( kvmap.begin() );
        osl::INIParser::StringAStringAMap::const_iterator ite( kvmap.end() );
        for ( ; it != ite; ++it )
        {

        }

    }

    void test_5()
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

    void test_section_6()
    {
        const char* rawdata = 
            "             \r\n"
            " mid=ac9219aa5232c4e519ae5fcb4d77ae5b\r\n"
            " product=360se\r\n"
            "             \r\n"
            " [360se] \r\n"
            "             \r\n"
            "combo=sedl\r\n"
            "version=4.4\r\n"
            "             \r\n"
            "             \r\n"
            "[a ]  \r\n"
            "             \r\n"
            "appext=0\r\n"
            "appext1=1\r\n"
            "             \r\n"
            "[b] \r\n"
            "             \r\n"
            "appext=b0\r\n"
            "appext1=b1\r\n"
            "             \r\n"
            "[ c]\r\n"
            "             \r\n"
            "appext=c0\r\n"
            "appext1=c1\r\n"
            "             \r\n"
            "             \r\n"
            "             \r\n";

        size_t rawdatalen = strlen( rawdata );
        osl::INIParser parser;
        parser.parse( rawdata, rawdatalen, "\r\n", "=" );

        {
            osl::StringA key = "mid";
            osl::StringA value = "ac9219aa5232c4e519ae5fcb4d77ae5b";
            H_TEST_ASSERT( value == parser.get( key ) );
        }

        {
            osl::StringA key = "product";
            osl::StringA value = "360se";
            H_TEST_ASSERT( value == parser.get( key ) );
        }

        {
            osl::StringA key = "combo";
            osl::StringA value = "sedl";
            H_TEST_ASSERT( value == parser.get( "360se", key ) );
        }

        {
            osl::StringA key = "version";
            osl::StringA value = "4.4";
            H_TEST_ASSERT( value == parser.get( "360se", key ) );
        }

        {
            osl::StringA section = "a";
            osl::StringA key = "appext";
            osl::StringA value = "0";
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appext1";
            value = "1";
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "b";
            osl::StringA key = "appext";
            osl::StringA value = "b0";
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appext1";
            value = "b1";
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "c";
            osl::StringA key = "appext";
            osl::StringA value = "c0";
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appext1";
            value = "c1";
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }
    }

    void test_case_senstive_7()
    {
        const char* rawdata = 
            "             \r\n"
            " Mid=ac9219aa5232c4e519ae5fcb4d77ae5b\r\n"
            " prOduct=360se\r\n"
            "             \r\n"
            " [360sE] \r\n"
            "             \r\n"
            "combo=sedl\r\n"
            "version=4.4\r\n"
            "             \r\n"
            "             \r\n"
            "[A ]  \r\n"
            "appext=0\r\n"
            "appext1=1\r\n"
            "             \r\n"
            "[B]  \r\n"
            "             \r\n"
            "appext=b0\r\n"
            "appext1=b1\r\n"
            "             \r\n"
            "[ c]  \r\n"
            "             \r\n"
            "appext=c0\r\n"
            "appext1=c1\r\n"
            "             \r\n"
            "             \r\n"
            "[hold住]\r\n"
            "有木有=不想上班的有木有!!!!\r\n";

        size_t rawdatalen = strlen( rawdata );
        osl::INIParser parser(false);
        parser.parse( rawdata, rawdatalen, "\r\n", "=" );

        {
            osl::StringA key = "mId";
            osl::StringA value = "ac9219aa5232c4e519ae5fcb4d77ae5b";
            H_TEST_ASSERT( value == parser.get( key ) );
        }

        {
            osl::StringA key = "proDuct";
            osl::StringA value = "360se";
            H_TEST_ASSERT( value == parser.get( key ) );
        }

        {
            osl::StringA key = "comBo";
            osl::StringA value = "sedl";
            H_TEST_ASSERT( value == parser.get( "360se", key ) );
        }

        {
            osl::StringA key = "veRsioN";
            osl::StringA value = "4.4";
            H_TEST_ASSERT( value == parser.get( "360se", key ) );
        }

        {
            osl::StringA section = "A";
            osl::StringA key = "appext";
            osl::StringA value = "0";
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appeXt1";
            value = "1";
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "b";
            osl::StringA key = "apPext";
            osl::StringA value = "b0";
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appext1";
            value = "b1";
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "c";
            osl::StringA key = "appExt";
            osl::StringA value = "c0";
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appexT1";
            value = "c1";
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            
            if (parser.isCaseSensitive())
            {
                //含有中文的地方必须要case_senstive
                osl::StringA section = "hold住";
                osl::StringA key = "有木有";
                osl::StringA value = "不想上班的有木有!!!!";
                H_TEST_ASSERT( value == parser.get( section, key ) );
            }
            else
            {
                osl::INIParser parser_case_senstive(true);
                parser_case_senstive.parse( rawdata, rawdatalen, "\r\n", "=" );
                H_TEST_ASSERT(parser_case_senstive.isCaseSensitive());
                osl::StringA section = "hold住";
                osl::StringA key = "有木有";
                osl::StringA value = "不想上班的有木有!!!!";
                H_TEST_ASSERT( value == parser_case_senstive.get( section, key ) );
            }
        }
    }


    void test_set_8()
    {
        osl::INIParser parser;

        {
            osl::StringA key = "mid";
            osl::StringA value = "ac9219aa5232c4e519ae5fcb4d77ae5b";
            parser.set("", key, value);
            H_TEST_ASSERT( value == parser.get( key ) );
        }

        {
            osl::StringA key = "product";
            osl::StringA value = "360se";
            parser.set("", key, value);
            H_TEST_ASSERT( value == parser.get( key ) );
        }

        {
            osl::StringA section = "360se";
            osl::StringA key = "combo";
            osl::StringA value = "sedl";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "360se";
            osl::StringA key = "version";
            osl::StringA value = "4.4";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "a";
            osl::StringA key = "appext";
            osl::StringA value = "0";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appext1";
            value = "1";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );


            key = "appext1";
            value = "3";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );


            key = "appext1";
            value = "3   ddddssaa     dddd";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );


            key = "appext1";
            value = "3   FFFFFFFFFFFF     dddd";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "b";
            osl::StringA key = "appext";
            osl::StringA value = "b0";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appext1";
            value = "b1";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );


            value = "bccccccccccccccccccccc1";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );

            value = "你懂的cccccc";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );

            value = "不管你信不信，反正我信了aaaa";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );

            value = "浮云bbb";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "c";
            osl::StringA key = "appext";
            osl::StringA value = "c0";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appext1";
            value = "c1";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "不要仰视哥";
            osl::StringA key = "哥是一个神话";
            osl::StringA value = "hold住";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appext1";
            value = "c1";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }
    }


    void test_output_9()
    {
        osl::INIParser parser;

        {
            osl::StringA key = "mid";
            osl::StringA value = "ac9219aa5232c4e519ae5fcb4d77ae5b";
            parser.set("", key, value);
            H_TEST_ASSERT( value == parser.get( key ) );
        }

        {
            osl::StringA key = "product";
            osl::StringA value = "360se";
            parser.set("", key, value);
            H_TEST_ASSERT( value == parser.get( key ) );
        }

        {
            osl::StringA section = "360se";
            osl::StringA key = "combo";
            osl::StringA value = "sedl";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "360se";
            osl::StringA key = "version";
            osl::StringA value = "4.4";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "a";
            osl::StringA key = "appext";
            osl::StringA value = "0";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appext1";
            value = "1";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "b";
            osl::StringA key = "appext";
            osl::StringA value = "b0";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appext1";
            value = "b1";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "c";
            osl::StringA key = "appext";
            osl::StringA value = "c0";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "appext1";
            value = "c1";
            parser.set(section, key, value);
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        parser.setKVSeparator("=");
        parser.setLineSeparator("\n");
        osl::StringA output = parser.serialize();
        osl::INIParser test_parser;
        H_TEST_ASSERT(test_parser.parse(output.data(), output.length()));

        {
            std::ostringstream oss;
            parser.serialize(oss);
            H_TEST_ASSERT(oss.str() == output);
        }

        {

            {
                osl::StringA key = "mid";
                osl::StringA value = "ac9219aa5232c4e519ae5fcb4d77ae5b";
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "product";
                osl::StringA value = "360se";
                H_TEST_ASSERT( value == parser.get( key ) );
            }

            {
                osl::StringA key = "combo";
                osl::StringA value = "sedl";
                H_TEST_ASSERT( value == parser.get( "360se", key ) );
            }

            {
                osl::StringA key = "version";
                osl::StringA value = "4.4";
                H_TEST_ASSERT( value == parser.get( "360se", key ) );
            }

            {
                osl::StringA section = "a";
                osl::StringA key = "appext";
                osl::StringA value = "0";
                H_TEST_ASSERT( value == parser.get( section, key ) );

                key = "appext1";
                value = "1";
                H_TEST_ASSERT( value == parser.get( section, key ) );
            }

            {
                osl::StringA section = "b";
                osl::StringA key = "appext";
                osl::StringA value = "b0";
                H_TEST_ASSERT( value == parser.get( section, key ) );

                key = "appext1";
                value = "b1";
                H_TEST_ASSERT( value == parser.get( section, key ) );
            }

            {
                osl::StringA section = "c";
                osl::StringA key = "appext";
                osl::StringA value = "c0";
                H_TEST_ASSERT( value == parser.get( section, key ) );

                key = "appext1";
                value = "c1";
                H_TEST_ASSERT( value == parser.get( section, key ) );
            }
        }
    }

    

    void test_chinese_10()
    {
        const char* rawdata = 
            "             \r\n"
            " 伤不起=学法语的人你伤不起啊\r\n"
            " 卖萌=当我们都去卖萌，都去装可爱的时候，说明这个世界还是萌的，还是可爱的。\r\n"
            "             \r\n"
            " [坑爹] \r\n"
            "             \r\n"
            "天龙八部=你妹啊!\r\n"
            "你妹=你妹是个很深奥的问题！\r\n"
            "             \r\n"
            "             \r\n"
            "[悲催 ]  \r\n"
            "             \r\n"
            " 悲惨得催人泪下=一般表示不称意，不顺心，失败，伤心，悔恨等意思   \r\n"
            "appext1=1\r\n"
            "             \r\n"
            "[普通青年] \r\n"
            "             \r\n"
            "文艺青年=2B青年\r\n";

        size_t rawdatalen = strlen( rawdata );
        osl::INIParser parser;
        parser.parse( rawdata, rawdatalen, "\r\n", "=" );

        {
            osl::StringA key = "伤不起";
            osl::StringA value = "学法语的人你伤不起啊";
            H_TEST_ASSERT( value == parser.get( key ) );
        }

        {
            osl::StringA key = "卖萌";
            osl::StringA value = "当我们都去卖萌，都去装可爱的时候，说明这个世界还是萌的，还是可爱的。";
            H_TEST_ASSERT( value == parser.get( key ) );
        }


        {
            osl::StringA section = "坑爹";
            osl::StringA key = "天龙八部";
            osl::StringA value = "你妹啊!";
            H_TEST_ASSERT( value == parser.get( section, key ) );

            key = "你妹";
            value = "你妹是个很深奥的问题！";
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "悲催";
            osl::StringA key = "悲惨得催人泪下";
            osl::StringA value = "一般表示不称意，不顺心，失败，伤心，悔恨等意思";
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }

        {
            osl::StringA section = "普通青年";
            osl::StringA key = "文艺青年";
            osl::StringA value = "2B青年";
            H_TEST_ASSERT( value == parser.get( section, key ) );
        }
    }


    class ParserListener : public osl::INIParser::Listener
    {
    public:
        virtual void onValue(osl::INIParser& parser, const osl::StringA& section, const osl::StringA& key, const osl::StringA& value)
        {
            parser.stopParse(true);
        }
    };


    void test_stop_parse_11()
    {
        const char* rawdata = 
            "             \r\n"
            " Mid=ac9219aa5232c4e519ae5fcb4d77ae5b\r\n"
            " prOduct=360se\r\n"
            "             \r\n"
            " [360sE] \r\n"
            "             \r\n"
            "combo=sedl\r\n"
            "version=4.4\r\n"
            "             \r\n"
            "             \r\n"
            "[A ]  \r\n"
            "appext=0\r\n"
            "appext1=1\r\n"
            "             \r\n"
            "[B]  \r\n"
            "             \r\n"
            "appext=b0\r\n"
            "appext1=b1\r\n"
            "             \r\n"
            "[ c]  \r\n"
            "             \r\n"
            "appext=c0\r\n"
            "appext1=c1\r\n"
            "             \r\n"
            "             \r\n"
            "[hold住]\r\n"
            "有木有=不想上班的有木有!!!!\r\n";

        size_t rawdatalen = strlen( rawdata );
        osl::INIParser parser(false);
        ParserListener listener;
        parser.addListener(&listener);
        parser.parse( rawdata, rawdatalen, "\r\n", "=" );
    }


}

TEST_UNIT(ini_parser)
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
}

TEST_UNIT(ini_parser_section_6)
{
    test_section_6();
}

TEST_UNIT(test_case_senstive_7)
{
    test_case_senstive_7();
}

TEST_UNIT(test_set_8)
{
    test_set_8();
}

TEST_UNIT(test_output_9)
{
    test_output_9();
}

TEST_UNIT(test_chinese_10)
{
    test_chinese_10();
}

TEST_UNIT(test_stop_parse_11)
{
    test_stop_parse_11();
}