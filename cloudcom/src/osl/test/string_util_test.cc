
#include "osl/include/test_common.h"
#include "osl/include/exp.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"

#include <iostream>
#include <string>

namespace
{

    void test_convert()
    {

        /// WS mbs
        //         {
        //             osl::HashMap<osl::QUUID, int> idMap;
        // 
        //             osl::StringA strTip = "ansi中文test";
        //             osl::StringA strRet2 = osl::StringUtil::wsToMbs( osl::StringUtil::mbsToWs( strTip ) );
        // 
        //             H_TEST_ASSERT ( strTip == strRet2 );
        //         }

#ifdef H_OS_WINDOWS
        /// Utf8
        {
            osl::StringA strTip = "ansi中文test";
            osl::StringA strTipRet = osl::StringUtil::utf8ToMbs( osl::StringUtil::mbsToUtf8( strTip ) );

            H_TEST_ASSERT ( strTip == strTipRet );
        }
#endif
    }

    void test_xtoa()
    {

    }

    void test_string_util()
    {
        using namespace osl;

        //cout << "bool StringUtil::startsWith( const StringA& str, const StringA& pattern, bool bCaseSensitive )"<<endl;
        H_TEST_ASSERT( !StringUtil::startsWith( "abcdef" , "aBc" ) );
        H_TEST_ASSERT( StringUtil::startsWith( "abcdef" , "aBc" , false ) );

        H_TEST_ASSERT( !StringUtil::startsWith( "abcdef" , "12" ) );
        H_TEST_ASSERT( !StringUtil::startsWith( "abcdef" , "123" , false ) );

        H_TEST_ASSERT( !StringUtil::startsWith( "abcdef" , "abcdefasda" ) );
        H_TEST_ASSERT( !StringUtil::startsWith( "abcdef" , "abcdefass" , false ) );

        // cout << "bool StringUtil::endsWith( const StringA& str, const StringA& pattern, bool bCaseSensitive )" << endl;

        H_TEST_ASSERT( !StringUtil::endsWith( "abcdef" , "dEf" ) );
        H_TEST_ASSERT( StringUtil::endsWith( "abcdef" , "dEf" , false ) );

        H_TEST_ASSERT( !StringUtil::endsWith( "abcdef" , "a32" ) );
        H_TEST_ASSERT( !StringUtil::endsWith( "abcdef" , "a32" , false ) );

        H_TEST_ASSERT( !StringUtil::endsWith( "abcdef" , "asds2abcdef" ) );
        H_TEST_ASSERT( !StringUtil::endsWith( "abcdef" , "xczxxabcdef" , false ) );

        //cout<<"equalsIgnoreCase"<<endl;

        H_TEST_ASSERT( StringUtil::equalsIgnoreCase( "abc" , "AbC" ) );
        H_TEST_ASSERT( !StringUtil::equalsIgnoreCase( "abc" , "AbCea" ) );

        //cout<<"bool StringUtil::contains( const StringA& motherStr, const char pattern, bool caseSensitive )"<<endl;
        H_TEST_ASSERT( !StringUtil::contains( "abcdef" , 'C' , true ) );
        H_TEST_ASSERT( !StringUtil::contains( "abcdef" , 'x' , true ) );
        H_TEST_ASSERT( StringUtil::contains( "abcdef" , 'C' , false ) );
        H_TEST_ASSERT( !StringUtil::contains( "abcdef" , 'x' , false ) );

        //cout<<"bool StringUtil::contains( const StringW& motherStr, const wchar_t pattern, bool caseSensitive )"<<endl;
        H_TEST_ASSERT( !StringUtil::contains( L"abcdef" , L'C' , true ) );
        H_TEST_ASSERT( !StringUtil::contains( L"abcdef" , L'x' , true ) );
        H_TEST_ASSERT(  StringUtil::contains( L"abcdef" , L'C' , false ) );
        H_TEST_ASSERT( !StringUtil::contains( L"abcdef" , L'x' , false ) );

        //cout<<"bool StringUtil::contains( const StringA& motherStr, const StringA& pattern, bool caseSensitive )"<<endl;
        H_TEST_ASSERT( !StringUtil::contains( "abcdef" , "BCD" , true ) );
        H_TEST_ASSERT( !StringUtil::contains( "abcdef" , "efg" , true ) );
        H_TEST_ASSERT(  StringUtil::contains( "abcdef" , "BcD" , false ) );
        H_TEST_ASSERT( !StringUtil::contains( "abcdef" , "efg" , false ) );

        //cout<<"bool StringUtil::contains( const StringW& motherStr, const StringW& pattern, bool caseSensitive )"<<endl;
        H_TEST_ASSERT( !StringUtil::contains( L"abcdef" , L"BCD" , true ) );
        H_TEST_ASSERT( !StringUtil::contains( L"abcdef" , L"efg" , true ) );
        H_TEST_ASSERT(  StringUtil::contains( L"abcdef" , L"BcD" , false ) );
        H_TEST_ASSERT( !StringUtil::contains( L"abcdef" , L"efg" , false ) );


        H_TEST_ASSERT( StringUtil::BLANK == "" );
        H_TEST_ASSERT( StringUtil::BLANKA == "" );
        H_TEST_ASSERT( StringUtil::BLANKW == L"" );
        // 
        //         H_TEST_ASSERT( "true" == StringUtil::true_String );
        //         H_TEST_ASSERT( "false" == StringUtil::false_String );
        //         H_TEST_ASSERT( "0" == StringUtil::zero_String );
    }

    void test_split()
    {
        using namespace osl;

        Vector<osl::f64> vec;
        vec.push_back( 12.3 );
        vec.push_back( 45.6 );
        vec.push_back( 78.9 );
        vec.push_back( 0.0f );

        StringA strSplit = "";
        strSplit += StringUtil::valueOf( vec[0] );
        strSplit += " ,    ";
        strSplit += StringUtil::valueOf( vec[1] );
        strSplit += "   ";
        strSplit += StringUtil::valueOf( vec[2] );
        strSplit +=  ",  ,";
        strSplit += StringUtil::valueOf( vec[3] );

        {
            Vector<StringA> retval = StringUtil::split( strSplit.c_str() , " ," );
            Vector<StringA> TempVal;
            TempVal.push_back( "1.230000e+001" );
            TempVal.push_back( "4.560000e+001" );
            TempVal.push_back( "7.890000e+001" );
            TempVal.push_back( "0.000000e+000" );
            H_TEST_ASSERT( retval == TempVal );

            osl::f64 fvec[6]={};
            StringUtil::toF64Elements( strSplit , fvec , 6 , 0.0 );

            // 			osl::s32 nVec[9]={};
            // 			StringUtil::toS32Elements( strSplit , nVec , 9 , 0 );
            // 			osl::s32 nVec2[9]={};
            // 			copy( vec.begin() , vec.end() , nVec2 );
            // 			H_TEST_ASSERT( 0 == memcmp( nVec , nVec2 , sizeof(nVec2) ) );


        }










        {
            StringA left , right;
            StringUtil::split( "1234" , left , right , ", " );
            H_TEST_ASSERT( left.empty() && right.empty() );
            //std::cout << left << "\t" << right << std::endl;
            StringUtil::split( "12,34" , left , right , ", " );
            H_TEST_ASSERT( ( "12" == left ) && ( "34" == right ) );
            StringUtil::split( ",1234" , left , right , ", " );
            H_TEST_ASSERT( ( "" == left ) && ( "1234" == right ) );
            StringUtil::split( "1234," , left , right , ", " );
            H_TEST_ASSERT( ( "1234" == left ) && ( "" == right ) );
        }

    }

    void test_std_string_append()
    {
        std::string s;
        const char* s1 = "errno=0\r\n";
        const char* s2 = "mid=731d8949087ebf6cb8b85a49779cab51\r\n";
        s.append(s1);
        s.append(s2);
        char buf[1024] = {};
        snprintf(buf, sizeof(buf), "%s%s", s1, s2);
        H_TEST_ASSERT(s.size() == strlen(s1) + strlen(s2));
        H_TEST_ASSERT(s == buf);
    }

    void test_std_string_resize()
    {
        std::string s = "1234567890";
        s.resize(10);
        char* p10 = &s[0];
        H_TEST_ASSERT(s == "1234567890");
        s.resize(5);
        char* p5 = &s[0];
        H_TEST_ASSERT(s == "12345");
        s.resize(8);
        char* p8 = &s[0];
        H_TEST_ASSERT(p8 == p5 && p5 == p10);
        H_TEST_ASSERT(strncmp(s.data(), "12345", 5) == 0);
        s.resize(100);
        char* p100 = &s[0];
        H_TEST_ASSERT(strncmp(s.data(), "12345", 5) == 0);
        H_TEST_ASSERT(p100 != p8);
    }

    void test_std_string_assign_append()
    {
        unsigned char key1[] = {0x30, 0x81, 0x00, 0x02, 0x81, 0x81, 0x00, 0xe2, 0xc7, 0x68, 0x22, 0x2d, 0x8d, 0xbd, 0xb5, 0x0e};
        unsigned char key2[] = {0x30, 0x01, 0x00, 0x02, 0x00, 0x81, 0x00, 0xe2, 0xc7, 0x68, 0x22, 0x2d, 0x8d, 0xbd, 0xb5, 0x0e, 0xb5, 0x0e};
        std::string s1;
        std::string s2;
        s1 = std::string((char*)key1, sizeof(key1));
        s2.assign((char*)key1, sizeof(key1));
        H_TEST_ASSERT(s1.size() == sizeof(key1));
        H_TEST_ASSERT(s2.size() == sizeof(key1));
        H_TEST_ASSERT(s1 == s2);
        H_TEST_ASSERT(memcmp(s1.data(), s2.data(), sizeof(key1)) == 0);

        const char* sz = "11111";
        s2.assign(sz);
        H_TEST_ASSERT(s2 == sz);

        s1.append((char*)key2, sizeof(key2));
        H_TEST_ASSERT(s1.length() == sizeof(key1) + sizeof(key2));
        unsigned char buf[1024] = {};
        memcpy(buf, (char*)key1, sizeof(key1));
        memcpy(buf + sizeof(key1), (char*)key2, sizeof(key2));
        H_TEST_ASSERT(memcmp(s1.data(), buf, s1.length()) == 0);
    }
}

TEST_UNIT(trivial_std_string_test)
{
    test_std_string_append();
    test_std_string_resize();
    test_std_string_assign_append();
}


TEST_UNIT(string_util_test_1)
{
    test_convert();
    test_xtoa();
    test_string_util();
    test_split();
}