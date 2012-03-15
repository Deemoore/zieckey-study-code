//! \file   HStringUtil.h
//! \brief  StringUtil和StringUtilW
#ifndef OSLIB_STRING_UTIL_H_
#define OSLIB_STRING_UTIL_H_

#include "osl/include/string_ext.h"

namespace osl
{
	//! \brief u64整数转换成字符串
	//! \param[in]  val
	//! \param[out] buf
	_EXPORT_OSLIB void xtoa( u64 val, char *buf );

	//! \brief u64整数转换成字符串
	//! \param[in]  val
	//! \param[out] buf
	_EXPORT_OSLIB void xtoa( u64 val, wchar_t *buf );

    //! 字符串的一些常用操作
    class _EXPORT_OSLIB StringUtil
    {
    public:
        typedef OStringStream StrStreamType;

        //! \brief     ANSI to Unicode
        static StringW mbsToWs( const StringA& strMbs )
        {
            return mbsToWs( strMbs.c_str(), ( u32 )strMbs.length() );
        };
        //! \brief     ANSI to Unicode
        static StringW mbsToWs( const StringA::value_type* szVal, u32 nLen );

        //! \brief     Unicode to ANSI
        static StringA  wsToMbs( const StringW& strWs )
        {
            return wsToMbs( strWs.c_str(), ( u32 )strWs.length() );
        };
        //! \brief     Unicode to ANSI
        static StringA  wsToMbs( const StringW::value_type* szVal, u32 nLen );

        //! \brief     utf-8 to Unicode
        static StringW utf8ToWs( const StringA& strMbs )
        {
            return utf8ToWs( strMbs.c_str(), ( u32 )strMbs.length() );
        };
        //! \brief     utf-8 to Unicode
        static StringW utf8ToWs( const StringA::value_type* szVal, u32 nLen );

        //! \brief     Unicode to utf-8
        static StringA  wsToUtf8( const StringW& strWs )
        {
            return wsToUtf8( strWs.c_str(), ( u32 )strWs.length() );
        };
        //! \brief     Unicode to utf-8
        static StringA  wsToUtf8( const StringW::value_type* szVal, u32 nLen );

        //! \brief     ANSI to utf-8
        static StringA mbsToUtf8( const StringA& strMbs )
        {
            return wsToUtf8( mbsToWs( strMbs ) );
        };

        //! \brief     utf-8 to ANSI
        static StringA utf8ToMbs( const StringA& strMbs )
        {
            return wsToMbs( utf8ToWs( strMbs ) );
        };

        //! \brief     utf16 to tf8
        static bool utf16ToUtf8( StringA& strOut, u16* pSrc, u32 nLen );

        //! \brief     utf8 to utf16 . Not Implemented yet.
        static bool utf8ToUtf16( StringW& strOut, u8* pSrc, u32 nLen );


        //!	\brief Removes any whitespace characters, which are standard space or TABs and so on.
        //!     The user may specify whether they want to trim only the
        //!    beginning or the end of the String ( the default action is
        //!    to trim both).
        //!	\param str[in,out], the source string, and the result will stored in it.
        //!	\param delims[in], all the characters in this string will be trimmed.
        //!	\param left, trim the beginning of the string
        //!	\param right, trim the end of the string
        static void trim( StringA& str, bool left = true, bool right = true );
        static void trim( StringW& str, bool left = true, bool right = true );
        static void trim( StringA& str, const StringA& delims, bool left = true, bool right = true );
        static void trim( StringW& str, const StringW& delims, bool left = true, bool right = true );
        static void trim( StringA& str, const char* delims, bool left = true, bool right = true );
        static void trim( StringW& str, const wchar_t* delims, bool left = true, bool right = true );


        /**
        *   \deprecated 废弃的接口。don't using these tow functions, there are substituted by
        *	void split( Vector<StringA>& resultSubstrsVec, const StringA& str, const StringA& delims = "\t\n ", unsigned int maxSplits = 0 );
        */
//         static Vector<StringA> split( const StringA& str, const StringA& delims = "\t\n ", unsigned int maxSplits = 0 );
//         //! \deprecated
//         static Vector<StringW> split( const StringW& str, const StringW& delims = L"\t\n ", unsigned int maxSplits = 0 );


        /** Returns a StringVector that contains all the substrings delimited
        * by the characters in the passed <code>delims</code> argument.
        * @param resultSubstrsVec[out], the result substrings are stored here.
        * @param delims A list of delimiter characters to split by
        * @param maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
        *     parameters is > 0, the splitting process will stop after this many splits, left to right.
        * @return void
        */

        static void split( Vector<StringA>& resultSubstrsVec, const StringA& str, const StringA& delims = "\t\n ", unsigned int maxSplits = 0 );
        static void split( std::vector<StringA>& resultSubstrsVec, const StringA& str, const StringA& delims = "\t\n ", unsigned int maxSplits = 0 );
        static void split( Vector<StringW>& resultSubstrsVec, const StringW& str, const StringW& delims = L"\t\n ", unsigned int maxSplits = 0 );
        static void split( std::vector<StringW>& resultSubstrsVec, const StringW& str, const StringW& delims = L"\t\n ", unsigned int maxSplits = 0 );
        


        /**
        * Split a string into tow strings using the special characters .
        * e.g. src="abc, hello wrold "  if delims="," then left="abc", right=" hello wrold "
        * \warning If any of delimiters was found, we just return, left string and right string will not be changed.
        * @param src The source string
        * @param left The left string separated by delims
        * @param left The right string separated by delims
        * @param delims A list of delimiter characters to split by. We only use the first one when come up against a delimiter
        */
        static void split( const StringA& src, StringA& left, StringA& right, const StringA& delims = "\t\n " );
        static void split( const StringW& src, StringW& left, StringW& right, const StringW& delims = L"\t\n " );
        static void split( const StringA& src, StringA& left, StringA& right, const char* delims = "\t\n " );
        static void split( const StringW& src, StringW& left, StringW& right, const wchar_t* delims = L"\t\n " );

        //! 转化小写 tolower
        static void toLowerCase( StringA& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), tolower );
        }
        //! \copydoc StringUtil::toLowerCase(StringA)
        static void toLowerCase( StringW& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), towlower );
        }

        //! 转化大写 toupper
        static void toUpperCase( StringA& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), toupper );
        }
        //! \copydoc StringUtil::toUpperCase(StringA)
        static void toUpperCase( StringW& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), towupper );
        }

        //! string compare
        //! \param bCaseSensitive true If we compare the string with case sensitively
        static bool equals( const StringA& str1, const StringA& str2, bool bCaseSensitive = true );
        
        //! \brief string compare ignoring case sensitively
        static bool equalsIgnoreCase( const StringA& str1, const StringA& str2 );

        //! \brief  Convert a bool/int/float number to a string
        //! \param[in] the number
        //! \return  the string
        static StringA valueOf( bool val );
        static StringA valueOf( f64 val );  //!< \copydoc StringUtil::valueOf(bool)
        static StringA valueOf( s64 val );  //!< \copydoc StringUtil::valueOf(bool)
        static StringA valueOf( u64 val );  //!< \copydoc StringUtil::valueOf(bool)
        static StringA valueOf( s32 val );  //!< \copydoc StringUtil::valueOf(bool)
        static StringA valueOf( u32 val );  //!< \copydoc StringUtil::valueOf(bool)



        //! \brief 将数据数组转换成字符串,数据之间用,分隔
        //! \param[in] pEles 数据
        //! \param[in] nCount 数据长度
        //! \return 拼接好的字符串
        static StringA valueOf( f64* pEles, u32 nCount );
        static StringA valueOf( f32* pEles, u32 nCount ); //!< \copydoc StringUtil::valueOf(f64*,u32)
        static StringA valueOf( u64* pEles, u32 nCount ); //!< \copydoc StringUtil::valueOf(f64*,u32)
        static StringA valueOf( s64* pEles, u32 nCount ); //!< \copydoc StringUtil::valueOf(f64*,u32)
        static StringA valueOf( u32* pEles, u32 nCount ); //!< \copydoc StringUtil::valueOf(f64*,u32)
        static StringA valueOf( s32* pEles, u32 nCount ); //!< \copydoc StringUtil::valueOf(f64*,u32)
        static StringA valueOf( u8* pEles, u32 nCount );  //!< \copydoc StringUtil::valueOf(f64*,u32)

        //! \brief     Parses the string val interpreting its content 
        //!     as an bool/int/float number, which is returned 
        //! \param[in] the string
        static bool toBool( const StringA& val );
        static s64  toS64(  const StringA& val );   //!< \copydoc StringUtil::toBool
        static s32  toS32(  const StringA& val );   //!< \copydoc StringUtil::toBool
		static u64  toU64(  const StringA& val );   //!< \copydoc StringUtil::toBool
        static u32  toU32(  const StringA& val );   //!< \copydoc StringUtil::toBool
        static f32  toF32(  const StringA& val );   //!< \copydoc StringUtil::toBool
        static f64  toF64(  const StringA& val );   //!< \copydoc StringUtil::toBool
    
        //! \brief      将以特定分隔符（默认分隔符为 逗号或空格） 分隔的字符串拆分到数组中。
        //! \param[in] filter 分隔符集合，例如 filter=",:"，那么字符串将会以 逗号或分号 分割。
        //! \param[in]  val 字符串
        //! \param[out] pEles 输出数据
        //! \param[in]  nCount 输出数据个数
        //! \param[in]  valDefault 默认值
        //! \retval true 字符串中存在的数据个数小于等于nCount
        //! \retval false 字符串中有数据未解析 nCount过小.
        static bool  toF64Elements(  const StringA& val, f64* pEles, u32 nCount, f64 valDefault, const char* filter = ", " );
        static bool  toF32Elements(  const StringA& val, f32* pEles, u32 nCount, f32 valDefault, const char* filter = ", "  ); //!< \copydoc StringUtil::toF64Elements
        static bool  toU64Elements(  const StringA& val, u64* pEles, u32 nCount, u64 valDefault, const char* filter = ", "  ); //!< \copydoc StringUtil::toF64Elements
        static bool  toS64Elements(  const StringA& val, s64* pEles, u32 nCount, s64 valDefault, const char* filter = ", "  ); //!< \copydoc StringUtil::toF64Elements
        static bool  toU32Elements(  const StringA& val, u32* pEles, u32 nCount, u32 valDefault, const char* filter = ", "  ); //!< \copydoc StringUtil::toF64Elements
        static bool  toS32Elements(  const StringA& val, s32* pEles, u32 nCount, s32 valDefault, const char* filter = ", "  ); //!< \copydoc StringUtil::toF64Elements
        static bool  toU8Elements(   const StringA& val, u8*  pEles, u32 nCount,  u8 valDefault, const char* filter = ", "  );    //!< \copydoc StringUtil::toF64Elements

        /** Returns whether the string begins with the pattern passed in.
        @param pattern The pattern to compare with.
        @param bCaseSensitive Whether the match is case sensitive or not
        comparison, pattern should also be in lower case.
        */
        
        //! \brief     Returns whether the string begins with the pattern passed in.
        //! \param[in] pattern The pattern to compare with.
        //! \param[in] bCaseSensitive true case sensitive, false ignore the case
        static bool startsWith( const StringA& str, const StringA& pattern, bool bCaseSensitive = true );
        static bool startsWith( const StringW& str, const StringW& pattern, bool bCaseSensitive = true );//!< \copydoc StringUtil::startsWith(const StringA,const StringA&,bool)

        //! \brief     Returns whether the string ends with the pattern passed in.
        //! \param[in] pattern The pattern to compare with.
        //! \param[in] bCaseSensitive true case sensitive, false ignore the case
        static bool endsWith( const StringA& str, const StringA& pattern, bool bCaseSensitive = true );
        static bool endsWith( const StringW& str, const StringW& pattern, bool bCaseSensitive = true );//!< \copydoc StringUtil::endsWith(const StringA,const StringA&,bool)


        /** Simple pattern-matching routine allowing a wild card pattern.
        @param str String to test
        @param pattern Pattern to match against; which can include simple '*' wildcards
        @param bCaseSensitive Whether the match is case sensitive or not
        */
        static bool match( const StringA& str, const StringA& pattern, bool bCaseSensitive = true );
        static bool match( const StringW& str, const StringW& pattern, bool bCaseSensitive = true );


        //!	\brief Test whether the a string is contains another char or string.
        //!	\param motherStr, the string to test
        //!	\param pattern, the pattern string or char to find
        //! \param[in] bCaseSensitive true case sensitive, false ignore the case
        //!	\return bool, return true if the occurrence of pattern within the motherStr or false
        static bool contains( const StringA& motherStr, char pattern, bool bCaseSensitive = true );
        static bool contains( const StringW& motherStr, wchar_t pattern, bool bCaseSensitive = true );//!< \copydoc StringUtil::contains(const StringA&,char,bool)
        static bool contains( const StringA& motherStr, const StringA& pattern, bool bCaseSensitive = true );//!< \copydoc StringUtil::contains(const StringA&,char,bool)
        static bool contains( const StringW& motherStr, const StringW& pattern, bool bCaseSensitive = true );//!< \copydoc StringUtil::contains(const StringA&,char,bool)


        //! \brief 转化字符串为url字符串，get请求的地址中某些字符需要转义
        static StringA converToUrlString( const StringA& str );

        //! query whether parameter string is a float number string or not.
        static bool isFloatNumber( StringA& s );

        /// Constant blank string, useful for returning by ref where local does not exist
        static const String BLANK;
        static const StringW BLANKW;
        static const StringA BLANKA;
//         static const StringA& true_String;   //! "true"
//         static const StringA& false_String;  //! "false"
//         static const StringA& zero_String;   //! "0"

        //! initialize / uninitialize. called by the module initialization.
        static void initialize();
        static void uninitialize();

    };

    //! 字符串的一些常用操作(宽字符版本)
    class _EXPORT_OSLIB StringUtilW
    {
    public:
        //! \brief     数据到字符串的转换
        //! \param[in] val 数据
        //! \return    转换之后的字符串
        static StringW valueOf( bool val );
        static StringW valueOf( f64 val );  //!< \copydoc StringUtilW::valueOf(bool)
        static StringW valueOf( s64 val );  //!< \copydoc StringUtilW::valueOf(bool)
        static StringW valueOf( u64 val );  //!< \copydoc StringUtilW::valueOf(bool)
        static StringW valueOf( s32 val );  //!< \copydoc StringUtilW::valueOf(bool)
        static StringW valueOf( u32 val );  //!< \copydoc StringUtilW::valueOf(bool)

        //! \brief 将数据数组转换成字符串,数据之间用,分隔
        //! \param[in] pEles 数据
        //! \param[in] nCount 数据长度
        //! \return 拼接好的字符串
        static StringW valueOf( f64* pEles, u32 nCount ); 
        static StringW valueOf( f32* pEles, u32 nCount ); //!< \copydoc StringUtilW::valueOf(f64*,u32)
        static StringW valueOf( u64* pEles, u32 nCount ); //!< \copydoc StringUtilW::valueOf(f64*,u32)
        static StringW valueOf( s64* pEles, u32 nCount ); //!< \copydoc StringUtilW::valueOf(f64*,u32)
        static StringW valueOf( u32* pEles, u32 nCount ); //!< \copydoc StringUtilW::valueOf(f64*,u32)
        static StringW valueOf( s32* pEles, u32 nCount ); //!< \copydoc StringUtilW::valueOf(f64*,u32)
        static StringW valueOf( u8* pEles, u32 nCount );  //!< \copydoc StringUtilW::valueOf(f64*,u32)

        //! \brief     字符串转化成指定类型
        //! \param[in] 字符串
        static bool toBool( const StringW& val );
        static s64  toS64(  const StringW& val );   //!< \copydoc StringUtilW::toBool
        static s32  toS32(  const StringW& val );   //!< \copydoc StringUtilW::toBool
        static f64  toF64(  const StringW& val );   //!< \copydoc StringUtilW::toBool

        //! \brief      将以特定分隔符（默认分隔符为 逗号或空格） 分隔的字符串拆分到数组中。
        //! \param[in] filter 分隔符集合，例如 filter=",:"，那么字符串将会以 逗号或分号 分割。
        //! \param[in]  val 字符串
        //! \param[out] pEles 输出数据
        //! \param[in]  nCount 输出数据个数
        //! \param[in]  valDefault 默认值
        //! \retval true 字符串中存在的数据个数小于等于nCount
        //! \retval false 字符串中有数据未解析 nCount过小.
        static bool  toF64Elements(  const StringW& val, f64* pEles, u32 nCount, f64 valDefault, const wchar_t* filter = L", " );
        static bool  toF32Elements(  const StringW& val, f32* pEles, u32 nCount, f32 valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements
        static bool  toU64Elements(  const StringW& val, u64* pEles, u32 nCount, u64 valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements
        static bool  toS64Elements(  const StringW& val, s64* pEles, u32 nCount, s64 valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements
        static bool  toU32Elements(  const StringW& val, u32* pEles, u32 nCount, u32 valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements
        static bool  toS32Elements(  const StringW& val, s32* pEles, u32 nCount, s32 valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements
        static bool  toU8Elements(   const StringW& val, u8*  pEles, u32 nCount, u8  valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements

        //! \copydoc StringUtil::toLowerCase(StringA)
        static void toLowerCase( StringW& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), towlower );
        }
        //! \copydoc StringUtil::toUpperCase(StringA)
        static void toUpperCase( StringW& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), towupper );
        }

        static void split( Vector<StringW>& resultSubstrsVec, const StringW& str, const StringW& delims = L"\t\n ", unsigned int maxSplits = 0 );
        static void split( std::vector<StringW>& resultSubstrsVec, const StringW& str, const StringW& delims = L"\t\n ", unsigned int maxSplits = 0 );
    };


    //! 万能的类型转换.前提要求支持输入输出流
    //! \tparam DestType 目标类型
    //! \tparam SrcType  原类型
    template<class DestType, class SrcType>
    DestType lexical_cast( SrcType src )
    {
        StringStreamA conv;
        DestType val;

        if ( !( ( conv << src ) && ( conv >> val ) ) )
        {
            throw std::bad_cast();
        }

        return val;
    }

    //----------------------------------------------------------------------------
    inline StringA StringUtil::valueOf( bool b )
    {
        return b ? "true" : "false";
    }

    //----------------------------------------------------------------------------
    inline StringW StringUtilW::valueOf( bool b )
    {
        return b ? L"true" : L"false";
    }

    //-----------------------------------------------------------------------------------
    inline bool StringUtil::toBool( const StringA& val )
    {
        return strcmp( val.c_str(), "true" ) == 0 ? true : false;
    }

    //-----------------------------------------------------------------------------------
    inline s64 StringUtil::toS64( const StringA& val )
    {
        return atoi64( val.c_str() );
    }

    //----------------------------------------------------------------------------------
    inline s32 StringUtil::toS32( const StringA& val )
    {
        return atoi32( val.c_str() );
    }

    //-----------------------------------------------------------------------------------
    inline f64 StringUtil::toF64( const StringA& val )
    {
        return atof64( val.c_str() );
    }

    //-----------------------------------------------------------------------------------
    inline f32 StringUtil::toF32( const StringA& val )
    {
        return atof( val.c_str() );
    }

    inline bool StringUtilW::toBool( const StringW& val )
    {
        return wcscmp( val.c_str(), L"true" ) == 0 ? true : false;
    }
    inline f64  StringUtilW::toF64(  const StringW& val )
    {
        return wcstod( val.c_str() , NULL );
    }

} // namespace

#endif

