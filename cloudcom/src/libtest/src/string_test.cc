#include "libtest/include/inner_pre.h"


#include <iostream>
using namespace std;


#include "libtest/include/test_object.h"



namespace LibTest
{
    class TString : public ITestObject
    {
    public:
        virtual const char* getCommand()
        {
            return "test_string";
        }
        virtual const char* getDesc()
        {
            return "test_string";
        }
        virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
        virtual void testAll();

    private:
        void test_convert();
        void test_xtoa();
        void test_string_util();
        void test_split();
    };
} // end of namespace LibTest


namespace LibTest
{
    void TString::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        testAll();
    }

    void TString::testAll()
    {
		osl::StringA str = "abcd";
		osl::StringA str1 = "abcd";

		bool bRet = ( str == str1 );
		cout<< bRet <<endl;
		bRet = ( str != str1 );
		cout<< bRet <<endl;

        test_convert();
        test_xtoa();
        test_string_util();
		test_split();
    }
    void TString::test_convert()
    {

        /// WS mbs
//         {
//             osl::HashMap<osl::QUUID, int> idMap;
// 
//             osl::StringA strTip = "ansi中文test";
//             osl::StringA strRet2 = osl::StringUtil::wsToMbs( osl::StringUtil::mbsToWs( strTip ) );
// 
//             H_ASSERT ( strTip == strRet2 );
//         }

        /// Utf8
        {
            osl::StringA strTip = "ansi中文test";
            osl::StringA strTipRet = osl::StringUtil::utf8ToMbs( osl::StringUtil::mbsToUtf8( strTip ) );

            H_ASSERT ( strTip == strTipRet );
        }

    }

    void TString::test_xtoa()
    {
		
    }

    void TString::test_string_util()
    {
		using namespace osl;

        //cout << "bool StringUtil::startsWith( const StringA& str, const StringA& pattern, bool bCaseSensitive )"<<endl;
        H_ASSERT( !StringUtil::startsWith( "abcdef" , "aBc" ) );
        H_ASSERT( StringUtil::startsWith( "abcdef" , "aBc" , false ) );

        H_ASSERT( !StringUtil::startsWith( "abcdef" , "12" ) );
        H_ASSERT( !StringUtil::startsWith( "abcdef" , "123" , false ) );

        H_ASSERT( !StringUtil::startsWith( "abcdef" , "abcdefasda" ) );
        H_ASSERT( !StringUtil::startsWith( "abcdef" , "abcdefass" , false ) );

        // cout << "bool StringUtil::endsWith( const StringA& str, const StringA& pattern, bool bCaseSensitive )" << endl;

        H_ASSERT( !StringUtil::endsWith( "abcdef" , "dEf" ) );
        H_ASSERT( StringUtil::endsWith( "abcdef" , "dEf" , false ) );

        H_ASSERT( !StringUtil::endsWith( "abcdef" , "a32" ) );
        H_ASSERT( !StringUtil::endsWith( "abcdef" , "a32" , false ) );

        H_ASSERT( !StringUtil::endsWith( "abcdef" , "asds2abcdef" ) );
        H_ASSERT( !StringUtil::endsWith( "abcdef" , "xczxxabcdef" , false ) );

        //cout<<"equalsIgnoreCase"<<endl;

        H_ASSERT( StringUtil::equalsIgnoreCase( "abc" , "AbC" ) );
        H_ASSERT( !StringUtil::equalsIgnoreCase( "abc" , "AbCea" ) );

        //cout<<"bool StringUtil::contains( const StringA& motherStr, const char pattern, bool caseSensitive )"<<endl;
        H_ASSERT( !StringUtil::contains( "abcdef" , 'C' , true ) );
        H_ASSERT( !StringUtil::contains( "abcdef" , 'x' , true ) );
        H_ASSERT( StringUtil::contains( "abcdef" , 'C' , false ) );
        H_ASSERT( !StringUtil::contains( "abcdef" , 'x' , false ) );

        //cout<<"bool StringUtil::contains( const StringW& motherStr, const wchar_t pattern, bool caseSensitive )"<<endl;
        H_ASSERT( !StringUtil::contains( L"abcdef" , L'C' , true ) );
        H_ASSERT( !StringUtil::contains( L"abcdef" , L'x' , true ) );
        H_ASSERT(  StringUtil::contains( L"abcdef" , L'C' , false ) );
        H_ASSERT( !StringUtil::contains( L"abcdef" , L'x' , false ) );

        //cout<<"bool StringUtil::contains( const StringA& motherStr, const StringA& pattern, bool caseSensitive )"<<endl;
        H_ASSERT( !StringUtil::contains( "abcdef" , "BCD" , true ) );
        H_ASSERT( !StringUtil::contains( "abcdef" , "efg" , true ) );
        H_ASSERT(  StringUtil::contains( "abcdef" , "BcD" , false ) );
        H_ASSERT( !StringUtil::contains( "abcdef" , "efg" , false ) );

        //cout<<"bool StringUtil::contains( const StringW& motherStr, const StringW& pattern, bool caseSensitive )"<<endl;
        H_ASSERT( !StringUtil::contains( L"abcdef" , L"BCD" , true ) );
        H_ASSERT( !StringUtil::contains( L"abcdef" , L"efg" , true ) );
        H_ASSERT(  StringUtil::contains( L"abcdef" , L"BcD" , false ) );
        H_ASSERT( !StringUtil::contains( L"abcdef" , L"efg" , false ) );


        H_ASSERT( StringUtil::BLANK == "" );
        H_ASSERT( StringUtil::BLANKA == "" );
        H_ASSERT( StringUtil::BLANKW == L"" );

        H_ASSERT( "true" == StringUtil::true_String );
        H_ASSERT( "false" == StringUtil::false_String );
        H_ASSERT( "0" == StringUtil::zero_String );



    }

	void TString::test_split()
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
			H_ASSERT( retval == TempVal );

			osl::f64 fvec[6]={};
			StringUtil::toF64Elements( strSplit , fvec , 6 , 0.0 );

// 			osl::s32 nVec[9]={};
// 			StringUtil::toS32Elements( strSplit , nVec , 9 , 0 );
// 			osl::s32 nVec2[9]={};
// 			copy( vec.begin() , vec.end() , nVec2 );
// 			H_ASSERT( 0 == memcmp( nVec , nVec2 , sizeof(nVec2) ) );


		}
		









		{
			StringA left , right;
			StringUtil::split( "1234" , left , right , ", " );
			H_ASSERT( left.empty() && right.empty() );
			cout << left << "\t" << right << endl;
			StringUtil::split( "12,34" , left , right , ", " );
			H_ASSERT( ( "12" == left ) && ( "34" == right ) );
			StringUtil::split( ",1234" , left , right , ", " );
			H_ASSERT( ( "" == left ) && ( "1234" == right ) );
			StringUtil::split( "1234," , left , right , ", " );
			H_ASSERT( ( "1234" == left ) && ( "" == right ) );
		}

	}

}
CREATE_FUNCTION( TString );
