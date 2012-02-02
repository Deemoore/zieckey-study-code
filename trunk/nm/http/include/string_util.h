//! \file   HStringUtil.h
//! \brief  StringUtil和StringUtilW
#ifndef nmIB_STRING_UTIL_H_
#define nmIB_STRING_UTIL_H_
#include "stdafx.h"
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>

namespace nm
{
#define atoi64 _atoi64
#define atoll _atoi64
#define atoi32 atoi
#define atof64 atof

	typedef unsigned int       u32;
	typedef int                s32;
	typedef unsigned short     u16;
	typedef short              s16;
	typedef unsigned char       u8;
	typedef char                s8;
	typedef float              f32;
	typedef double             f64;
	typedef unsigned long long u64;
	typedef long long          s64;

	//! \brief u64整数转换成字符串
	//! \param[in]  val
	//! \param[out] buf
	static void xtoa( u64 val, char *buf );

	//! \brief u64整数转换成字符串
	//! \param[in]  val
	//! \param[out] buf
	static void xtoa( u64 val, wchar_t *buf );

    //! 字符串的一些常用操作
    class  StringUtil
    {
    public:
		typedef std::ostringstream StrStreamType;

        //! \brief     ANSI to Unicode
        static std::wstring mbsToWs( const std::string& strMbs )
        {
            return mbsToWs( strMbs.c_str(), ( u32 )strMbs.length() );
        };
        //! \brief     ANSI to Unicode
        static std::wstring mbsToWs( const std::string::value_type* szVal, u32 nLen );

        //! \brief     Unicode to ANSI
        static std::string  wsToMbs( const std::wstring& strWs )
        {
            return wsToMbs( strWs.c_str(), ( u32 )strWs.length() );
        };
        //! \brief     Unicode to ANSI
        static std::string  wsToMbs( const std::wstring::value_type* szVal, u32 nLen );

        //! \brief     utf-8 to Unicode
        static std::wstring utf8ToWs( const std::string& strMbs )
        {
            return utf8ToWs( strMbs.c_str(), ( u32 )strMbs.length() );
        };
        //! \brief     utf-8 to Unicode
        static std::wstring utf8ToWs( const std::string::value_type* szVal, u32 nLen );

        //! \brief     Unicode to utf-8
        static std::string  wsToUtf8( const std::wstring& strWs )
        {
            return wsToUtf8( strWs.c_str(), ( u32 )strWs.length() );
        };
        //! \brief     Unicode to utf-8
        static std::string  wsToUtf8( const std::wstring::value_type* szVal, u32 nLen );

        //! \brief     ANSI to utf-8
        static std::string mbsToUtf8( const std::string& strMbs )
        {
            return wsToUtf8( mbsToWs( strMbs ) );
        };

        //! \brief     utf-8 to ANSI
        static std::string utf8ToMbs( const std::string& strMbs )
        {
            return wsToMbs( utf8ToWs( strMbs ) );
        };

        //! \brief     utf16 to tf8
        static bool utf16ToUtf8( std::string& strOut, u16* pSrc, u32 nLen );

        //! \brief     utf8 to utf16 . Not Implemented yet.
        static bool utf8ToUtf16( std::wstring& strOut, u8* pSrc, u32 nLen );


        //!	\brief Removes any whitespace characters, which are standard space or TABs and so on.
        //!     The user may specify whether they want to trim only the
        //!    beginning or the end of the String ( the default action is
        //!    to trim both).
        //!	\param str[in,out], the source string, and the result will stored in it.
        //!	\param delims[in], all the characters in this string will be trimmed.
        //!	\param left, trim the beginning of the string
        //!	\param right, trim the end of the string
        static void trim( std::string& str, bool left = true, bool right = true );
        static void trim( std::wstring& str, bool left = true, bool right = true );
        static void trim( std::string& str, const std::string& delims, bool left = true, bool right = true );
        static void trim( std::wstring& str, const std::wstring& delims, bool left = true, bool right = true );
        static void trim( std::string& str, const char* delims, bool left = true, bool right = true );
        static void trim( std::wstring& str, const wchar_t* delims, bool left = true, bool right = true );


        /**
        *   \deprecated 废弃的接口。don't using these tow functions, there are substituted by
        *	void split( std::vector<std::string>& resultSubstrsVec, const std::string& str, const std::string& delims = "\t\n ", unsigned int maxSplits = 0 );
        */
        static std::vector<std::string> split( const std::string& str, const std::string& delims = "\t\n ", unsigned int maxSplits = 0 );
        //! \deprecated
        static std::vector<std::wstring> split( const std::wstring& str, const std::wstring& delims = L"\t\n ", unsigned int maxSplits = 0 );


        /** Returns a Stringstd::vector that contains all the substrings delimited
        * by the characters in the passed <code>delims</code> argument.
        * @param resultSubstrsVec[out], the result substrings are stored here.
        * @param delims A list of delimiter characters to split by
        * @param maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
        *     parameters is > 0, the splitting process will stop after this many splits, left to right.
        * @return void
        */

		static void split( std::vector<std::string>& resultSubstrsVec, const std::string& str, const std::string& delims = "\t\n ", unsigned int maxSplits = 0 );
//        static void split( std::stringstd::vector& resultSubstrsVec, const std::string& str, const std::string& delims = "\t\n ", unsigned int maxSplits = 0 );
        static void split( std::vector<std::wstring>& resultSubstrsVec, const std::wstring& str, const std::wstring& delims = L"\t\n ", unsigned int maxSplits = 0 );

        /**
        * Split a string into tow strings using the special characters .
        * e.g. src="abc, hello wrold "  if delims="," then left="abc", right=" hello wrold "
        * \warning If any of delimiters was found, we just return, left string and right string will not be changed.
        * @param src The source string
        * @param left The left string separated by delims
        * @param left The right string separated by delims
        * @param delims A list of delimiter characters to split by. We only use the first one when come up against a delimiter
        */
        static void split( const std::string& src, std::string& left, std::string& right, const std::string& delims = "\t\n " );
        static void split( const std::wstring& src, std::wstring& left, std::wstring& right, const std::wstring& delims = L"\t\n " );
        static void split( const std::string& src, std::string& left, std::string& right, const char* delims = "\t\n " );
        static void split( const std::wstring& src, std::wstring& left, std::wstring& right, const wchar_t* delims = L"\t\n " );
		
        //! 转化小写 tolower
        static void toLowerCase( std::string& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), tolower );
        }
        //! \copydoc StringUtil::toLowerCase(std::string)
        static void toLowerCase( std::wstring& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), towlower );
        }

        //! 转化大写 toupper
        static void toUpperCase( std::string& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), toupper );
        }
        //! \copydoc StringUtil::toUpperCase(std::string)
        static void toUpperCase( std::wstring& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), towupper );
        }

        //! 比较字符串
        //! \param bCaseSensitive true 为大小写敏感,false为忽略大小写
        static bool equals( const std::string& str1, const std::string& str2, bool bCaseSensitive = true );
        
        //! \brief 忽略大小写比较字符串
        static bool equalsIgnoreCase( const std::string& str1, const std::string& str2 );

        //! \brief     数据到字符串的转换
        //! \param[in] val 数据
        //! \return    转换之后的字符串
        static std::string valueOf( bool val );
        static std::string valueOf( f64 val );  //!< \copydoc StringUtil::valueOf(bool)
        static std::string valueOf( s64 val );  //!< \copydoc StringUtil::valueOf(bool)
        static std::string valueOf( u64 val );  //!< \copydoc StringUtil::valueOf(bool)
        static std::string valueOf( s32 val );  //!< \copydoc StringUtil::valueOf(bool)
        static std::string valueOf( u32 val );  //!< \copydoc StringUtil::valueOf(bool)



        //! \brief 将数据数组转换成字符串,数据之间用,分隔
        //! \param[in] pEles 数据
        //! \param[in] nCount 数据长度
        //! \return 拼接好的字符串
        static std::string valueOf( f64* pEles, u32 nCount );
        static std::string valueOf( f32* pEles, u32 nCount ); //!< \copydoc StringUtil::valueOf(f64*,u32)
        static std::string valueOf( u64* pEles, u32 nCount ); //!< \copydoc StringUtil::valueOf(f64*,u32)
        static std::string valueOf( s64* pEles, u32 nCount ); //!< \copydoc StringUtil::valueOf(f64*,u32)
        static std::string valueOf( u32* pEles, u32 nCount ); //!< \copydoc StringUtil::valueOf(f64*,u32)
        static std::string valueOf( s32* pEles, u32 nCount ); //!< \copydoc StringUtil::valueOf(f64*,u32)
        static std::string valueOf( u8* pEles, u32 nCount );  //!< \copydoc StringUtil::valueOf(f64*,u32)

        //! \brief     字符串转化成指定类型
        //! \param[in] 字符串
        static bool toBool( const std::string& val );
        static s64  toS64(  const std::string& val );   //!< \copydoc StringUtil::toBool
        static s32  toS32(  const std::string& val );   //!< \copydoc StringUtil::toBool
		static u64  toU64(  const std::string& val );   //!< \copydoc StringUtil::toBool
        static u32  toU32(  const std::string& val );   //!< \copydoc StringUtil::toBool
        static f32  toF32(  const std::string& val );   //!< \copydoc StringUtil::toBool
        static f64  toF64(  const std::string& val );   //!< \copydoc StringUtil::toBool
    
        //! \brief      将以特定分隔符（默认分隔符为 逗号或空格） 分隔的字符串拆分到数组中。
        //! \param[in] filter 分隔符集合，例如 filter=",:"，那么字符串将会以 逗号或分号 分割。
        //! \param[in]  val 字符串
        //! \param[out] pEles 输出数据
        //! \param[in]  nCount 输出数据个数
        //! \param[in]  valDefault 默认值
        //! \retval true 字符串中存在的数据个数小于等于nCount
        //! \retval false 字符串中有数据未解析 nCount过小.
        static bool  toF64Elements(  const std::string& val, f64* pEles, u32 nCount, f64 valDefault, const char* filter = ", " );
        static bool  toF32Elements(  const std::string& val, f32* pEles, u32 nCount, f32 valDefault, const char* filter = ", "  ); //!< \copydoc StringUtil::toF64Elements
        static bool  toU64Elements(  const std::string& val, u64* pEles, u32 nCount, u64 valDefault, const char* filter = ", "  ); //!< \copydoc StringUtil::toF64Elements
        static bool  toS64Elements(  const std::string& val, s64* pEles, u32 nCount, s64 valDefault, const char* filter = ", "  ); //!< \copydoc StringUtil::toF64Elements
        static bool  toU32Elements(  const std::string& val, u32* pEles, u32 nCount, u32 valDefault, const char* filter = ", "  ); //!< \copydoc StringUtil::toF64Elements
        static bool  toS32Elements(  const std::string& val, s32* pEles, u32 nCount, s32 valDefault, const char* filter = ", "  ); //!< \copydoc StringUtil::toF64Elements
        static bool  toU8Elements(   const std::string& val, u8*  pEles, u32 nCount,  u8 valDefault, const char* filter = ", "  );    //!< \copydoc StringUtil::toF64Elements

        /** Returns whether the string begins with the pattern passed in.
        @param pattern The pattern to compare with.
        @param bCaseSensitive Whether the match is case sensitive or not
        comparison, pattern should also be in lower case.
        */
        
        //! \brief     Returns whether the string begins with the pattern passed in.
        //! \param[in] pattern The pattern to compare with.
        //! \param[in] bCaseSensitive true 为大小写敏感,false为忽略大小写
        static bool startsWith( const std::string& str, const std::string& pattern, bool bCaseSensitive = true );
        static bool startsWith( const std::wstring& str, const std::wstring& pattern, bool bCaseSensitive = true );//!< \copydoc StringUtil::startsWith(const std::string,const std::string&,bool)

        //! \brief     Returns whether the string ends with the pattern passed in.
        //! \param[in] pattern The pattern to compare with.
        //! \param[in] bCaseSensitive true 为大小写敏感,false为忽略大小写
        static bool endsWith( const std::string& str, const std::string& pattern, bool bCaseSensitive = true );
        static bool endsWith( const std::wstring& str, const std::wstring& pattern, bool bCaseSensitive = true );//!< \copydoc StringUtil::endsWith(const std::string,const std::string&,bool)


        /** Simple pattern-matching routine allowing a wildcard pattern.
        @param str String to test
        @param pattern Pattern to match against; which can include simple '*' wildcards
        @param bCaseSensitive Whether the match is case sensitive or not
        */
        static bool match( const std::string& str, const std::string& pattern, bool bCaseSensitive = true );
        static bool match( const std::wstring& str, const std::wstring& pattern, bool bCaseSensitive = true );


        //!	\brief Test whether the a string is contains another char or string.
        //!	\param motherStr, the string to test
        //!	\param pattern, the pattern string or char to find
        //!	\param bCaseSensitive true 为大小写敏感,false为忽略大小写
        //!	\return bool, return true if the occurrence of pattern within the motherStr or false
        static bool contains( const std::string& motherStr, char pattern, bool bCaseSensitive = true );
        static bool contains( const std::wstring& motherStr, wchar_t pattern, bool bCaseSensitive = true );//!< \copydoc StringUtil::contains(const std::string&,char,bool)
        static bool contains( const std::string& motherStr, const std::string& pattern, bool bCaseSensitive = true );//!< \copydoc StringUtil::contains(const std::string&,char,bool)
        static bool contains( const std::wstring& motherStr, const std::wstring& pattern, bool bCaseSensitive = true );//!< \copydoc StringUtil::contains(const std::string&,char,bool)


        //! \brief 转化字符串为url字符串，get请求的地址中某些字符需要转义
        static std::string converToUrlString( const std::string& str );

        //! query whether parameter string is a float number string or not.
        static bool isFloatNumber( std::string& s );

        /// Constant blank string, useful for returning by ref where local does not exist
        //static const String BLANK;
        static const std::wstring BLANKW;
        static const std::string BLANKA;
        static const std::string& true_String;   //! "true"
        static const std::string& false_String;  //! "false"
        static const std::string& zero_String;   //! "0"

        //! initialize / uninitialize. called by the module initialization.
        static void initialize();
        static void uninitialize();

    };

    //! 字符串的一些常用操作(宽字符版本)
    class StringUtilW
    {
    public:
        //! \brief     数据到字符串的转换
        //! \param[in] val 数据
        //! \return    转换之后的字符串
        static std::wstring valueOf( bool val );
        static std::wstring valueOf( f64 val );  //!< \copydoc StringUtilW::valueOf(bool)
        static std::wstring valueOf( s64 val );  //!< \copydoc StringUtilW::valueOf(bool)
        static std::wstring valueOf( u64 val );  //!< \copydoc StringUtilW::valueOf(bool)
        static std::wstring valueOf( s32 val );  //!< \copydoc StringUtilW::valueOf(bool)
        static std::wstring valueOf( u32 val );  //!< \copydoc StringUtilW::valueOf(bool)

        //! \brief 将数据数组转换成字符串,数据之间用,分隔
        //! \param[in] pEles 数据
        //! \param[in] nCount 数据长度
        //! \return 拼接好的字符串
        static std::wstring valueOf( f64* pEles, u32 nCount ); 
        static std::wstring valueOf( f32* pEles, u32 nCount ); //!< \copydoc StringUtilW::valueOf(f64*,u32)
        static std::wstring valueOf( u64* pEles, u32 nCount ); //!< \copydoc StringUtilW::valueOf(f64*,u32)
        static std::wstring valueOf( s64* pEles, u32 nCount ); //!< \copydoc StringUtilW::valueOf(f64*,u32)
        static std::wstring valueOf( u32* pEles, u32 nCount ); //!< \copydoc StringUtilW::valueOf(f64*,u32)
        static std::wstring valueOf( s32* pEles, u32 nCount ); //!< \copydoc StringUtilW::valueOf(f64*,u32)
        static std::wstring valueOf( u8* pEles, u32 nCount );  //!< \copydoc StringUtilW::valueOf(f64*,u32)

        //! \brief     字符串转化成指定类型
        //! \param[in] 字符串
        static bool toBool( const std::wstring& val );
        static s64  toS64(  const std::wstring& val );   //!< \copydoc StringUtilW::toBool
        static s32  toS32(  const std::wstring& val );   //!< \copydoc StringUtilW::toBool
        static f64  toF64(  const std::wstring& val );   //!< \copydoc StringUtilW::toBool

        //! \brief      将以特定分隔符（默认分隔符为 逗号或空格） 分隔的字符串拆分到数组中。
        //! \param[in] filter 分隔符集合，例如 filter=",:"，那么字符串将会以 逗号或分号 分割。
        //! \param[in]  val 字符串
        //! \param[out] pEles 输出数据
        //! \param[in]  nCount 输出数据个数
        //! \param[in]  valDefault 默认值
        //! \retval true 字符串中存在的数据个数小于等于nCount
        //! \retval false 字符串中有数据未解析 nCount过小.
        static bool  toF64Elements(  const std::wstring& val, f64* pEles, u32 nCount, f64 valDefault, const wchar_t* filter = L", " );
        static bool  toF32Elements(  const std::wstring& val, f32* pEles, u32 nCount, f32 valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements
        static bool  toU64Elements(  const std::wstring& val, u64* pEles, u32 nCount, u64 valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements
        static bool  toS64Elements(  const std::wstring& val, s64* pEles, u32 nCount, s64 valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements
        static bool  toU32Elements(  const std::wstring& val, u32* pEles, u32 nCount, u32 valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements
        static bool  toS32Elements(  const std::wstring& val, s32* pEles, u32 nCount, s32 valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements
        static bool  toU8Elements(   const std::wstring& val, u8*  pEles, u32 nCount, u8  valDefault, const wchar_t* filter = L", "  );//!< \copydoc StringUtilW::toF64Elements

        //! \copydoc StringUtil::toLowerCase(std::string)
        static void toLowerCase( std::wstring& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), towlower );
        }
        //! \copydoc StringUtil::toUpperCase(std::string)
        static void toUpperCase( std::wstring& str )
        {
            std::transform( str.begin(), str.end(), str.begin(), towupper );
        }

        static void split( std::vector<std::wstring>& resultSubstrsVec, const std::wstring& str, const std::wstring& delims = L"\t\n ", unsigned int maxSplits = 0 );

    };


    //! 万能的类型转换.前提要求支持输入输出流
    //! \tparam DestType 目标类型
    //! \tparam SrcType  原类型
    template<class DestType, class SrcType>
    DestType lexical_cast( SrcType src )
    {
		std::ostringstream conv;
        DestType val;

        if ( !( ( conv << src ) && ( conv >> val ) ) )
        {
            throw std::bad_cast();
        }

        return val;
    }

    //----------------------------------------------------------------------------
    inline std::string StringUtil::valueOf( bool b )
    {
        return b ? "true" : "false";
    }

    //----------------------------------------------------------------------------
    inline std::wstring StringUtilW::valueOf( bool b )
    {
        return b ? L"true" : L"false";
    }

    //-----------------------------------------------------------------------------------
    inline bool StringUtil::toBool( const std::string& val )
    {
        return strcmp( val.c_str(), "true" ) == 0 ? true : false;
    }

    //-----------------------------------------------------------------------------------
    inline s64 StringUtil::toS64( const std::string& val )
    {
        return atoi64( val.c_str() );
    }

    //----------------------------------------------------------------------------------
    inline s32 StringUtil::toS32( const std::string& val )
    {
        return atoi32( val.c_str() );
    }

    //-----------------------------------------------------------------------------------
    inline f64 StringUtil::toF64( const std::string& val )
    {
        return atof64( val.c_str() );
    }

    //-----------------------------------------------------------------------------------
    inline f32 StringUtil::toF32( const std::string& val )
    {
        return (f32)atof64( val.c_str() );
    }

    inline bool StringUtilW::toBool( const std::wstring& val )
    {
        return wcscmp( val.c_str(), L"true" ) == 0 ? true : false;
    }
    inline f64  StringUtilW::toF64(  const std::wstring& val )
    {
        return wcstod( val.c_str() , NULL );
    }

} // namespace

#endif

