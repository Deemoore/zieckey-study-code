//! \file   HStringUtil.cpp
//! \brief   
#include "stdafx.h"
#include "include/string_util.h"
#include <assert.h>
#include <string>
#include <vector>

namespace
{
    using namespace nm;

    //! Scoped memory block. When lifetime out, memory in the object will be freed.
    //! \warning The object SHOULD ONLY be used on stack.
    struct ScopedMem
    {
        void*   pRep;
        ScopedMem( const ScopedMem& r );    //!< 勿加实现
    public:

        ScopedMem(): pRep( 0 ) {}

        ScopedMem( void* _rep )
            :pRep( _rep )
        {
        }

        //! Construct a sized memory.
        ScopedMem(size_t nSize)
        {
            alloc(nSize);
        }

        ~ScopedMem()
        {
            if ( pRep )
            {
                ::free( pRep );
            }
        }

        inline ScopedMem& operator=( void*pBuf )
        {
            if ( pRep )
            {
                ::free( pRep );
            }

            pRep = pBuf;
            return *this;
        }

        operator unsigned char*()const
        {
            return static_cast<unsigned char*>(pRep);
        }
        unsigned char* get() const
        {
            return static_cast<unsigned char*>(pRep);
        }

        unsigned char* getPointer() const
        {
            return static_cast<unsigned char*>(pRep);
        }

        template<class T>
        T* getPointer()const
        {
            return static_cast<T*>(pRep);
        }

        inline bool isNull( void ) const
        {
            return pRep == 0;
        }

        //! Allocate sized memory.
        void alloc( size_t nSize )
        {
            if ( pRep )
            {
                ::free( pRep );
            }

            pRep = ::malloc( nSize );
        }
    };



	//! \brief 字符串->u64
	inline u64 atou64( const char* buf )
	{
#ifdef H_OS_LINUX
		return strtoull( buf , NULL , 10 );
#else
		u64 ret = 0;
		if( 1 == sscanf( buf , "%I64u" , &ret ) )
		{
			return ret;
		}
		else
		{
			return 0;
		}
#endif
	}
	//! \brief 字符串->u64
	inline u64 atou64( const wchar_t* buf )
	{
#ifdef H_OS_LINUX
		return wcstoull( buf , NULL , 10 );
#else
		u64 ret = 0;
		if( 1 == swscanf( buf , L"%I64u" , &ret ) )
		{
			return ret;
		}
		else
		{
			return 0;
		}
#endif
	}

	inline char* u64toa( u64 val, char *buf )
	{
		assert( sizeof( u64 ) == 8 );
		xtoa( val , buf );
		return buf;
	}
	inline wchar_t* u64toa( u64 val, wchar_t *buf )
	{
		assert( sizeof( u64 ) == 8 );
		xtoa( val , buf );
		return buf;
	}
	inline u32 atou32( const char* buf )
	{
		return strtoul( buf , NULL , 10 );
	}
	inline u32 atou32( const wchar_t* buf )
	{
		return wcstoul( buf , NULL , 10 );
	}

	inline char* u32toa( u32 val, char *buf )
	{
#ifdef H_OS_LINUX
		xtoa( val , buf );
		return buf;
#else
		assert( sizeof( unsigned long ) == 4 );
		return _ultoa( val , buf , 10 ) ;
#endif
	}
	inline wchar_t* u32toa( u32 val, wchar_t *buf )
	{
#ifdef H_OS_LINUX
		xtoa( val , buf );
		return buf;
#else
		assert( sizeof( unsigned long ) == 4 );
		return _ultow( val , buf , 10 ) ;
#endif
	}


	inline s64 atos64( const char* buf )
	{
#ifdef H_OS_LINUX
		return atoll( buf );
#else
		return _atoi64( buf );
#endif
	}
	inline s64 atos64( const wchar_t* buf )
	{
#ifdef H_OS_LINUX
		return wcstoll( buf , NULL , 10 );
#else
		return _wtoi64( buf );
#endif
	}

	inline char* s64toa( s64 val , char* buf )
	{
		if ( val < 0 )
		{
			*buf = '-';
			xtoa( -val , buf + 1 );
		}
		else
		{
			xtoa( val , buf );
		}

		return buf;
	}
	inline wchar_t* s64toa( s64 val , wchar_t* buf )
	{
		if ( val < 0 )
		{
			*buf = L'-';
			xtoa( -val , buf + 1 );
		}
		else
		{
			xtoa( val , buf );
		}

		return buf;
	}

	inline s32 atos32( const char* buf )
	{
		return atoi( buf );
	}
	inline s32 atos32( const wchar_t* buf )
	{
		return wcstol( buf , 0 , 10 );
	}
	inline char* s32toa( s32 val , char* buf )
	{
		return s64toa( val , buf );
	}

	inline wchar_t* s32toa( s32 val , wchar_t* buf )
	{
		return s64toa( val , buf );
	}

	inline f32 atof32( const wchar_t* buf )
	{
		return (f32)wcstod( buf , NULL );
	}
	inline f32 atof32( const char* buf )
	{
		return (f32)strtod( buf , NULL );
	}
	inline f64 atof64( const wchar_t* buf )
	{
		return wcstod( buf , NULL );
	}
	inline f64 atof64( const char* buf )
	{
		return strtod( buf , NULL );
	}


	//! \brief     字符串 -> 值类型(f64 f32 u64 s64 u32 s32 u8)
    //! \tparam StringType 字符串类型可以是std::wstring std::string std::string std::wstring
    //! \param[in] strVal 数值字符串
    //! \param[out]val  结果
    template<class StringType>
    inline void StringToValue( const StringType & strVal , f64& val )
    {
        val = atof64( strVal.c_str() );
    }
    
    template<class StringType>
    inline void StringToValue( const StringType& strVal , f32& val )
    {
        val = atof32( strVal.c_str() );
    }   //!< \copydoc StringToValue(const StringType&,f64&)
  
    template<class StringType>
    inline void StringToValue( const StringType& strVal , u64& val )
    {
        val = atou64( strVal.c_str() );
    }   //!< \copydoc StringToValue(const StringType&,f64&)

    template<class StringType>
    inline void StringToValue( const StringType& strVal , s64& val )
    {
        val = atos64( strVal.c_str() );
    }   //!< \copydoc StringToValue(const StringType&,f64&)
    template<class StringType>
    void StringToValue( const StringType& strVal , u32& val )
    {
        val = atou32( strVal.c_str() );
    }   //!< \copydoc StringToValue(const StringType&,f64&)
    template<class StringType>
    void StringToValue( const StringType& strVal , s32& val )
    {
        val = atos32( strVal.c_str() );
    }   //!< \copydoc StringToValue(const StringType&,f64&)
    template<class StringType>
    void StringToValue( const StringType& strVal , u8& val )
    {
        val = atou32( strVal.c_str() );
    }   //!< \copydoc StringToValue(const StringType&,f64&)

}




#if defined(H_OS_WINDOWS) && !defined(H_OS_WINCE)
#   ifndef __MINGW32__
#       define __CONVERT__LOCALE__
#   endif
#endif


namespace nm
{

    struct NoCaseCompareChar
    {
        bool operator()(char l,char r)const
        {
            bool bEqual = ( l == r );
            if( bEqual )
                return true;
            if ( isalpha( static_cast<unsigned char>(l) ) )
            {
                if( isupper( static_cast<unsigned char>(l) ) )
                {
                    return l == toupper( r );
                }
                else
                {
                    return l == tolower( r );
                }
            }

            return bEqual;
        }
        bool operator()( wchar_t l , wchar_t r )const
        {
            bool bEqual = ( l == r );

            if( bEqual )
                return true;

            if ( iswalpha( l ) )
            {
                if( iswupper( l ) )
                {
                    return l == static_cast<wchar_t>(towupper( r ));
                }
                else
                {
                    return l == static_cast<wchar_t>(towlower( r ));
                }
            }

            return bEqual;
        }
    }no_case_compare_char;

    
    template<class T>
    bool stringUtil_StartsWith( const T& str, const T& pattern, bool bCaseSensitive )
    {
        //H_ASSERT( str.length() >= pattern.length() );
        if ( str.length() < pattern.length() )
        {
            return false;
        }

        if ( bCaseSensitive )
        {
            return std::equal( pattern.begin() , pattern.end() , str.begin() );
        }
        else
        {
            return std::equal( pattern.begin() , pattern.end() , str.begin() , no_case_compare_char );
        }
    }

    template<class T>
    bool stringUtil_EndsWith( const T& str, const T& pattern, bool bCaseSensitive )
    {
        //H_ASSERT( str.length() >= pattern.length() );
        if ( str.length() < pattern.length() )
        {
            return false;
        }

        if ( bCaseSensitive )
        {
            return equal( pattern.rbegin() , pattern.rend() , str.rbegin() );
        }
        else
        {
            return equal( pattern.rbegin() , pattern.rend() , str.rbegin() , no_case_compare_char );
        }
    }




    template<class T>
    struct nocase_equal_char  
    {
        T m_c;
        nocase_equal_char( T c ):m_c( c )
        {
        }
        bool operator()( T c )
        {
            return no_case_compare_char( m_c , c );
        }
    };


    template<class T>
    bool stringUtil_contains( const T& str , typename T::value_type c , bool bCaseSensitive )
    {
        if ( bCaseSensitive )
        {
            return str.find( c , 0 ) != T::npos ;
        }
        else
        {
            return str.end() != std::find_if( str.begin() , str.end() , nocase_equal_char<typename T::value_type>(c) );
        }
    }
    template<class T>
    bool stringUtil_contains( const T& strL , const T& strR , bool bCaseSensitive )
    {
        if ( bCaseSensitive )
        {
            return strL.end() != std::search( strL.begin() , strL.end() , strR.begin() , strR.end() );
        }
        else
        {
            return strL.end() != std::search( strL.begin() , strL.end() , strR.begin() , strR.end() , no_case_compare_char );
        }
    }

    template<class T>
    std::string stringUtil_valueOf( T* pEles, u32 nCount )
    {
        std::ostringstream str;
        str << pEles[0];

        for( u32 i = 1; i < nCount; ++i )
        {
            str << "," << pEles[i];
        }

        return str.str();
    }
    template<class T>
    std::wstring valueOfArrayW( T* pEles , u32 nCount )
    {
        std::wostringstream str;
        str << pEles[0];

        for( u32 i = 1; i < nCount; ++i )
        {
            str << L"," << pEles[i];
        }
        return str.str();
    }

	template<class StringType , class T>
	bool internal_StringUtil_toElements( const std::vector<StringType>& vVals, T* pEles, u32 nCount, T valDefault )
    {
        u32 nSizeEle = vVals.size();

        for( u32 i = 0; i < nCount; ++i )
        {
            if( i < nSizeEle )
            {
                StringToValue( vVals[i] , pEles[i] );
            }
            else
            {
                pEles[i] = valDefault;
            }
        }
        return nCount <= nSizeEle;
    }

    template<class T>
    bool stringUtil_toElements( const std::string& str, T* pEles, u32 nCount, T valDefault, const char* filter )
    {
        std::vector<std::string> vVals;
        StringUtil::split( vVals, str, filter, nCount );
        return internal_StringUtil_toElements( vVals , pEles , nCount , valDefault );
    }

    template<class T>
    bool stringUtil_toElements( const std::wstring& val, T* pEles, u32 nCount, T valDefault, const wchar_t* filter )
    {
        std::vector<std::wstring> vVals;
        StringUtil::split( vVals, val, filter, nCount );

        return internal_StringUtil_toElements( vVals , pEles , nCount , valDefault );
    }

    template<class StringType>
    void stringUtil_trim( StringType& str, typename StringType::const_pointer delims, bool left, bool right )
    {
        if ( right )
        {
            str.erase( str.find_last_not_of( delims ) + 1 );    // trim right
        }

        if ( left )
        {
            str.erase( 0, str.find_first_not_of( delims ) );    // trim left
        }
    }

    //! \brief     分割字符串
    //! \tparam    StringType 字符串类型 std::string std::wstring
    //! \tparam    std::vector的第二个参数
    //! \param[in] ret 分割的结果
    //! \param[in] str 要分割的字符串
    //! \param[in] delims 分割符
    //! \param[in] maxSplits 
    template<class StringType , class _ContainerName>
    void stringUtilSplit( std::vector<StringType,_ContainerName>& ret,const StringType& str
        , const StringType& delims, unsigned int maxSplits)
    {
        unsigned int numSplits = 0;

        // Use STL methods
        size_t start, pos;
        start = 0;

        do
        {
            pos = str.find_first_of( delims, start );

            if ( pos == start )
            {
                // Do nothing
                start = pos + 1;
            }
            else if ( pos == std::string::npos || ( maxSplits && numSplits == maxSplits ) )
            {
                // Copy the rest of the string
                ret.push_back( str.substr( start ) );
                break;
            }
            else
            {
                // Copy up to delimiter
                ret.push_back( str.substr( start, pos - start ) );
                start = pos + 1;
            }

            // parse up to next real data
            start = str.find_first_not_of( delims, start );
            ++numSplits;

        }
        while ( pos != std::string::npos );

    }

    template<typename StringType>
    void stringUtil_Split( const StringType& src, StringType& left, StringType& right, typename StringType::const_pointer pDelims , size_t nDelimsLength )
    {
        typename StringType::const_iterator iter = find_first_of( src.begin() , src.end() , pDelims , pDelims + nDelimsLength );
        if ( src.end() == iter )
        {
            return ;
        }

        left.assign( src.begin() , iter );
        iter++;
        right.assign( iter , src.end() );

    }
}

namespace
{
    std::string private_true_String;   //! "true"
    std::string private_false_String;  //! "false"
    std::string private_zero_String;   //! "0"
}

namespace nm
{

    //-----------------------------------------------------------------------
    /*const String  StringUtil::BLANK;*/
    const std::wstring StringUtil::BLANKW;
    const std::string StringUtil::BLANKA;
    const std::string& StringUtil::true_String  = private_true_String;   //! "true"
    const std::string& StringUtil::false_String = private_false_String;  //! "false"
    const std::string& StringUtil::zero_String  = private_zero_String;   //! "0"


#ifdef __CONVERT__LOCALE__
    _locale_t s_nLocale = 0;
#endif

    //------------------------------------------------------
    void StringUtil::initialize()
    {
        private_true_String  = "true";
        private_false_String = "false";
        private_zero_String  = "0";
    }
    //------------------------------------------------------
    void StringUtil::uninitialize()
    {
        private_true_String = BLANKA;
        private_false_String = BLANKA;
        private_zero_String = BLANKA;
    }
    //---------------------------------------------------
    std::wstring StringUtil::mbsToWs( const std::string::value_type* szVal, u32 nLen )
    {
		if ( (NULL == szVal ) || ( 0 == nLen) )
		{
			return StringUtil::BLANKW;
		}

        u32 nCharCount =  ( u32 )nLen + 2 ;

        assert( szVal );

        std::wstring::value_type* pStr = reinterpret_cast<std::wstring::value_type*>( malloc( sizeof( std::wstring::value_type ) * nCharCount ) );
        ScopedMem pMem( pStr );

#ifdef __CONVERT__LOCALE__

        if ( s_nLocale == 0 )
        {
            s_nLocale = _create_locale( LC_ALL, ".ACP" );
        }

        size_t nNewLen = _mbstowcs_l( pStr, szVal, nCharCount, s_nLocale );
#else
        size_t nNewLen = mbstowcs( ( std::wstring::value_type* )pStr, szVal, nCharCount );
#endif

        if ( int( nNewLen ) < 0 )
        {
            return StringUtil::BLANKW;
        }

        return std::wstring ( pStr, nNewLen );
    }
    //---------------------------------------------------
    std::string StringUtil::wsToMbs( const std::wstring::value_type* szVal, u32 nLen )
    {
        //#if H_OS == H_OS_WINDOWS
        // at most double size of width character string.
        u32 nCharCount =  ( u32 )nLen * 2 + 2 ;

        if ( nCharCount < 2 )
        {
            return std::string();
        }

        char* pStr = ( char* )malloc( nCharCount );
        ScopedMem pMem( pStr );

#ifdef __CONVERT__LOCALE__

        // convert to multi-byte string
        if ( s_nLocale == 0 )
        {
            s_nLocale = _create_locale( LC_ALL, ".ACP" );
        }

        // convert to multi-byte string
        // nLen excludes ending null.
        size_t nNewLen = _wcstombs_l( pStr, const_cast<std::wstring::value_type*>(szVal), nCharCount, s_nLocale );
#else
        size_t nNewLen = wcstombs( pStr, const_cast<std::wstring::value_type*>(szVal), nCharCount );
#endif

        if ( int( nNewLen ) < 0 )
        {
            return StringUtil::BLANKA;
        }

        return std::string( pStr, nNewLen );
    }
    //---------------------------------------------------------------------
    std::wstring StringUtil::utf8ToWs( const std::string::value_type* szVal, u32 nLen  )
    {
        // at most double size of width character string.
        u32 nCharCount =  ( u32 )nLen * 2 + 2 ;

        if ( nCharCount < 2 )
        {
            return StringUtil::BLANKW;
        }

        std::wstring::value_type* pStr = ( std::wstring::value_type* )malloc( sizeof( std::wstring::value_type ) * nCharCount);
        ScopedMem pMem( pStr );

        int nNewLen = 0;
#ifdef H_OS_WINDOWS

        // convert to multi-byte string
        nNewLen = MultiByteToWideChar( CP_UTF8, 0, szVal,
                                       -1, pStr, nCharCount );

#elif defined(H_OS_LINUX)
        assert( false );
        return  StringUtil::BLANKW;
#endif

        if ( nNewLen < 0 )
        {
            return StringUtil::BLANKW;
        }

        return std::wstring ( pStr, nNewLen - 1 );
    }
    //---------------------------------------------------------------------
    std::string  StringUtil::wsToUtf8( const std::wstring::value_type* szVal, u32 nLen )
    {
        // convert to multi-byte string
        //boost::text_encoding::encoded_string<boost::text_encoding::charset::utf8, std::string > strRet = strWs.c_str();
        //return strRet.c_str();

        // at most double size of width character string.
        u32 nCharCount =  ( u32 )nLen * 3 + 1 ;

        if ( nCharCount < 2 )
        {
            return std::string();
        }

        char* pStr = ( char* )malloc( nCharCount );
        ScopedMem pMem( pStr );

        int nNewLen = 0;
#ifdef H_OS_WINDOWS

        // convert to multi-byte string
        nNewLen = WideCharToMultiByte( CP_UTF8, 0, ( wchar_t* ) szVal,
                                       -1, pStr, nCharCount, NULL, NULL );

#elif defined(H_OS_LINUX)

        assert( false );
        return StringUtil::BLANKA;
#endif

        if ( nNewLen <= 0 )
        {
            return StringUtil::BLANKA;
        }

        return std::string( pStr, nNewLen - 1 );
    }
    //-----------------------------------------------------------------------
    void StringUtil::trim( std::string& str, const char* delims, bool left, bool right )
    {
        stringUtil_trim( str , delims , left , right );
    }
    void StringUtil::trim( std::wstring& str, const wchar_t* delims, bool left, bool right )
    {
        stringUtil_trim( str , delims , left , right );
    }

    void StringUtil::trim( std::string& str, bool left, bool right )
    {
        const char* delims = " \t\r";
        StringUtil::trim( str, delims, left, right );
    }

    void StringUtil::trim( std::string& str, const std::string& delims, bool left, bool right )
    {
        StringUtil::trim( str, delims.c_str(), left, right );
    }

    void StringUtil::trim( std::wstring& str, bool left, bool right )
    {
        const wchar_t* delims = L" \t\r";
        trim( str, delims, left, right );
    }

    void StringUtil::trim( std::wstring& str, const std::wstring& delims, bool left, bool right )
    {
        trim( str, delims.c_str(), left, right );
    }

    //-------------------------------------------------------------------
    std::vector<std::string> StringUtil::split( const std::string& str, const std::string& delims, unsigned int maxSplits )
    {
        std::vector<std::string> ret;
        StringUtil::split( ret, str, delims, maxSplits );
        return ret;
    }

    void StringUtil::split( std::vector<std::string>& ret, const std::string& str, const std::string& delims, unsigned int maxSplits )
    {
        stringUtilSplit( ret , str , delims , maxSplits );
    }

    std::vector<std::wstring> StringUtil::split( const std::wstring& str, const std::wstring& delims, unsigned int maxSplits )
    {
        std::vector<std::wstring> ret;
        StringUtil::split( ret, str, delims, maxSplits );
        return ret;
    }

    void StringUtil::split( std::vector<std::wstring>& ret, const std::wstring& str, const std::wstring& delims, unsigned int maxSplits )
    {
        stringUtilSplit( ret , str , delims , maxSplits );
    }

    void StringUtil::split( const std::string& src, std::string& left, std::string& right, const char* delims/* = "\t\n "*/ )
    {
        stringUtil_Split( src , left , right , delims , strlen( delims ) );
    }

    void StringUtil::split( const std::string& src, std::string& left, std::string& right, const std::string& delims/* = "\t\n "*/ )
    {
        split( src, left, right, delims.c_str() );
    }

    void StringUtil::split( const std::wstring& src, std::wstring& left, std::wstring& right, const wchar_t* delims/* = L"\t\n "*/ )
    {
        stringUtil_Split( src , left , right , delims , wcslen( delims ) );
    }

    void StringUtil::split( const std::wstring& src, std::wstring& left, std::wstring& right, const std::wstring& delims/* = L"\t\n "*/ )
    {
        split( src, left, right, delims.c_str() );
    }

    //-----------------------------------------------------------------------
    bool StringUtil::startsWith( const std::string& str, const std::string& pattern, bool bCaseSensitive )
    {
        return stringUtil_StartsWith( str , pattern , bCaseSensitive );
    }

    bool StringUtil::startsWith( const std::wstring& str, const std::wstring& pattern, bool bCaseSensitive )
    {
        return stringUtil_StartsWith( str , pattern , bCaseSensitive );
    }

    bool StringUtil::endsWith( const std::string& str, const std::string& pattern, bool bCaseSensitive )
    {
        return stringUtil_EndsWith( str , pattern , bCaseSensitive );
    }

    bool StringUtil::endsWith( const std::wstring& str, const std::wstring& pattern, bool bCaseSensitive )
    {
        return stringUtil_EndsWith( str , pattern , bCaseSensitive );
    }

    //-----------------------------------------------------------------------
    bool StringUtil::match( const std::string& str, const std::string& pattern, bool caseSensitive )
    {
        std::string tmpStr = str;
        std::string tmpPattern = pattern;

        if ( !caseSensitive )
        {
            StringUtil::toLowerCase( tmpStr );
            StringUtil::toLowerCase( tmpPattern );
        }

        std::string::const_iterator strIt = tmpStr.begin();
        std::string::const_iterator patIt = tmpPattern.begin();
        std::string::const_iterator lastWildCardIt = tmpPattern.end();

        while ( strIt != tmpStr.end() && patIt != tmpPattern.end() )
        {
            if ( *patIt == '*' )
            {
                lastWildCardIt = patIt;
                // Skip over looking for next character
                ++patIt;

                if ( patIt == tmpPattern.end() )
                {
                    // Skip right to the end since * matches the entire rest of the string
                    strIt = tmpStr.end();
                }
                else
                {
                    // scan until we find next pattern character
                    while ( strIt != tmpStr.end() && *strIt != *patIt )
                    {
                        ++strIt;
                    }
                }
            }
            else
            {
                if ( *patIt != *strIt )
                {
                    if ( lastWildCardIt != tmpPattern.end() )
                    {
                        // The last wildcard can match this incorrect sequence
                        // rewind pattern to wildcard and keep searching
                        patIt = lastWildCardIt;
                        lastWildCardIt = tmpPattern.end();
                    }
                    else
                    {
                        // no wildwards left
                        return false;
                    }
                }
                else
                {
                    ++patIt;
                    ++strIt;
                }
            }

        }

        // If we reached the end of both the pattern and the string, we succeeded
        if ( patIt == tmpPattern.end() && strIt == tmpStr.end() )
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    //-----------------------------------------------------------------------
    bool StringUtil::match( const std::wstring& str, const std::wstring& pattern, bool caseSensitive )
    {
        std::wstring tmpStr = str;
        std::wstring tmpPattern = pattern;

        if ( !caseSensitive )
        {
            StringUtil::toLowerCase( tmpStr );
            StringUtil::toLowerCase( tmpPattern );
        }

        std::wstring::const_iterator strIt = tmpStr.begin();
        std::wstring::const_iterator patIt = tmpPattern.begin();
        std::wstring::const_iterator lastWildCardIt = tmpPattern.end();

        while ( strIt != tmpStr.end() && patIt != tmpPattern.end() )
        {
            if ( *patIt == L'*' )
            {
                lastWildCardIt = patIt;
                // Skip over looking for next character
                ++patIt;

                if ( patIt == tmpPattern.end() )
                {
                    // Skip right to the end since * matches the entire rest of the string
                    strIt = tmpStr.end();
                }
                else
                {
                    // scan until we find next pattern character
                    while ( strIt != tmpStr.end() && *strIt != *patIt )
                    {
                        ++strIt;
                    }
                }
            }
            else
            {
                if ( *patIt != *strIt )
                {
                    if ( lastWildCardIt != tmpPattern.end() )
                    {
                        // The last wildcard can match this incorrect sequence
                        // rewind pattern to wildcard and keep searching
                        patIt = lastWildCardIt;
                        lastWildCardIt = tmpPattern.end();
                    }
                    else
                    {
                        // no wildwards left
                        return false;
                    }
                }
                else
                {
                    ++patIt;
                    ++strIt;
                }
            }

        }

        // If we reached the end of both the pattern and the string, we succeeded
        if ( patIt == tmpPattern.end() && strIt == tmpStr.end() )
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    //------------------------------------------------------------
    bool StringUtil::contains( const std::string& motherStr, char pattern, bool caseSensitive )
    {
        return stringUtil_contains( motherStr , pattern , caseSensitive );
    }

    bool StringUtil::contains( const std::wstring& motherStr, wchar_t pattern, bool caseSensitive )
    {
        return stringUtil_contains( motherStr , pattern , caseSensitive );
    }

    bool StringUtil::contains( const std::string& motherStr, const std::string& pattern, bool caseSensitive )
    {
        return stringUtil_contains( motherStr , pattern , caseSensitive );
    }

    bool StringUtil::contains( const std::wstring& motherStr, const std::wstring& pattern, bool caseSensitive )
    {
        return stringUtil_contains( motherStr , pattern , caseSensitive );
    }

    //------------------------------------------------------------
    std::string StringUtil::converToUrlString( const std::string& str )
    {
        std::string strDest;
        strDest.reserve( str.size() );

        for( std::string::const_iterator iter = str.begin() ; iter != str.end() ; ++iter )
        {
            switch ( *iter )
            {
                case '\r':
                case '\n':
                    continue;
                case ' ':
                    strDest += "%20";
                    continue;
                case '\t':
                    strDest += "%09" ;
                    continue;
                case '"':
                    strDest += "%22" ;
                    continue;
            }

            strDest.append( 1 , *iter );
        }

        return strDest;
    }
    //------------------------------------------------------
    std::string StringUtil::valueOf( f64* pEles, u32 nCount )
    {
        return stringUtil_valueOf<f64>( pEles , nCount );
    }

    std::string StringUtil::valueOf( f32* pEles, u32 nCount )
    {
        return stringUtil_valueOf<f32>( pEles , nCount );
    }

    std::string StringUtil::valueOf( u64* pEles, u32 nCount )
    {
        return stringUtil_valueOf<u64>( pEles , nCount );
    }

    std::string StringUtil::valueOf( s64* pEles, u32 nCount )
    {
        return stringUtil_valueOf<s64>( pEles , nCount );
    }

    std::string StringUtil::valueOf( u32* pEles, u32 nCount )
    {
        return stringUtil_valueOf<u32>( pEles , nCount );
    }

    std::string StringUtil::valueOf( s32* pEles, u32 nCount )
    {
        return stringUtil_valueOf<s32>( pEles , nCount );
    }

    std::string StringUtil::valueOf( u8* pEles, u32 nCount )
    {
        return stringUtil_valueOf<u8>( pEles , nCount );
    }

	std::string StringUtil::valueOf( s64 i )
	{
		char sz[64] = {};
		s64toa( i , sz );
		return sz;
	}

	std::string StringUtil::valueOf( u64 i )
	{
		char sz[64] = {};
		u64toa( i , sz );
		return sz;
	}

	std::string StringUtil::valueOf( s32 i )
	{
		char sz[64] = {};
		s32toa( i , sz );
		return sz;
	}

	std::string StringUtil::valueOf( u32 i )
	{
		char sz[64] = {};
		u32toa( i , sz );
		return sz;
	}

	std::string StringUtil::valueOf( f64 f )
	{
		char szTemp[64]={};

		if ( _snprintf( szTemp , 63 , "%e" , f ) )
		{
			return szTemp;
		}
		else
		{
			return StringUtil::BLANKA;
		}
	}

    //------------------------------------------------------
    bool StringUtil::toF64Elements(  const std::string& val, f64* pEles, u32 nCount, f64 valDefault, const char* filter/* = ", "*/ )
    {
        return stringUtil_toElements<f64>( val , pEles , nCount , valDefault , filter );
    }

    bool StringUtil::toF32Elements(  const std::string& val, f32* pEles, u32 nCount, f32 valDefault, const char* filter/* = ", "*/ )
    {
        return stringUtil_toElements<f32>( val , pEles , nCount , valDefault , filter );
    }

    bool StringUtil::toU64Elements(  const std::string& val, u64* pEles, u32 nCount, u64 valDefault, const char* filter/* = ", "*/ )
    {
        return stringUtil_toElements<u64>( val , pEles , nCount , valDefault , filter );
    }

    bool StringUtil::toS64Elements(  const std::string& val, s64* pEles, u32 nCount, s64 valDefault, const char* filter/* = ", "*/ )
    {
        return stringUtil_toElements<s64>( val , pEles , nCount , valDefault , filter );
    }
    //------------------------------------------------------
    bool StringUtil::toU32Elements(  const std::string& val, u32* pEles, u32 nCount, u32 valDefault, const char* filter/* = ", "*/ )
    {
        return stringUtil_toElements<u32>( val , pEles , nCount , valDefault , filter );
    }

    bool StringUtil::toS32Elements(  const std::string& val, s32* pEles, u32 nCount, s32 valDefault, const char* filter/* = ", "*/ )
    {
        return stringUtil_toElements<s32>( val , pEles , nCount , valDefault , filter );
    }

    bool StringUtil::toU8Elements(  const std::string& val, u8* pEles, u32 nCount, u8 valDefault, const char* filter/* = ", "*/ )
    {
        return stringUtil_toElements<u8>( val , pEles , nCount , valDefault , filter );
    }
    //------------------------------------------------------
    s32 _utf16_to_utf8_len ( const u16 *str, s32 len, s32 *items_read )
    {
        s32 ret, in_pos;
        u16 ch;
        bool surrogate;

        ret = 0;
        in_pos = 0;
        surrogate = false;

        while ( len < 0 ? str [in_pos] : in_pos < len )
        {
            ch = str [in_pos];

            if ( surrogate )
            {
                if ( ch >= 0xDC00 && ch <= 0xDFFF )
                {
                    ret += 4;
                }
                else
                {
                    ///* invalid surrogate pair */
                    //if (error) {
                    //	g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_ILLEGAL_SEQUENCE, "invalid utf-16 sequence at %d (missing surrogate tail)", in_pos);
                    //	if (items_read)
                    //		*items_read = in_pos;
                    //	return -1;
                    //} /* otherwise just ignore. */
                    return -1;
                }

                surrogate = false;
            }
            else
            {
                /* fast path optimization */
                if ( ch < 0x80 )
                {
                    for ( ; len < 0 ? str [in_pos] : in_pos < len; in_pos++ )
                    {
                        if ( str [in_pos] < 0x80 )
                        {
                            ++ret;
                        }
                        else
                        {
                            break;
                        }
                    }

                    continue;
                }
                else if ( ch < 0x0800 )
                {
                    ret += 2;
                }
                else if ( ch >= 0xD800 && ch <= 0xDBFF )
                {
                    surrogate = true;
                }
                else if ( ch >= 0xDC00 && ch <= 0xDFFF )
                {
                    ///* invalid surrogate pair */
                    //if (error) {
                    //	g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_ILLEGAL_SEQUENCE, "invalid utf-16 sequence at %d (missing surrogate head)", in_pos);
                    //	if (items_read)
                    //		*items_read = in_pos;
                    //	return -1;
                    //} /* otherwise just ignore. */
                    return -1;
                }
                else
                {
                    ret += 3;
                }
            }

            in_pos++;
        }

        if ( items_read )
        {
            *items_read = in_pos;
        }

        return ret;
    }

    u8*	_utf16_to_utf8 ( std::string& strOut, const u16 *str, s32 len, s32 *items_read, s32 *items_written )
    {
        /* The conversion logic is almost identical to UTF8Encoding.GetBytes(),
        but error check is always done at utf16_to_utf8_len() so that
        the conversion core below simply resets erroreous bits */
        s32 utf8_len;
        u8 *ret = NULL;
        s32 in_pos, out_pos;
        u16 ch;
        s32 codepoint = 0;
        u16 surrogate = 0;

        in_pos = 0;
        out_pos = 0;
        surrogate = 0;

        if ( items_written )
        {
            *items_written = 0;
        }

        utf8_len = _utf16_to_utf8_len ( str, len, items_read );

        //if (error)
        //	if (*error)
        //		return NULL;
        if ( utf8_len <= 0 )
        {
            return NULL;
        }

        strOut.resize( utf8_len );
        ret = ( u8* )&strOut[0];

        //ret = g_malloc ((1+utf8_len) * sizeof (gchar));

        while ( len < 0 ? str [in_pos] : in_pos < len )
        {
            ch = str [in_pos];

            if ( surrogate )
            {
                if ( ch >= 0xDC00 && ch <= 0xDFFF )
                {
                    codepoint = 0x10000 + ( ch - 0xDC00 ) + ( ( surrogate - 0xD800 ) << 10 );
                    surrogate = 0;
                }
                else
                {
                    surrogate = 0;
                    /* invalid surrogate pair */
                    continue;
                }
            }
            else
            {
                /* fast path optimization */
                if ( ch < 0x80 )
                {
                    for ( ; len < 0 ? str [in_pos] : in_pos < len; in_pos++ )
                    {
                        if ( str [in_pos] < 0x80 )
                        {
                            ret [out_pos++] = ( u8 )( str [in_pos] );
                        }
                        else
                        {
                            break;
                        }
                    }

                    continue;
                }
                else if ( ch >= 0xD800 && ch <= 0xDBFF )
                {
                    surrogate = ch;
                }
                else if ( ch >= 0xDC00 && ch <= 0xDFFF )
                {
                    /* invalid surrogate pair */
                    continue;
                }
                else
                {
                    codepoint = ch;
                }
            }

            in_pos++;

            if ( surrogate != 0 )
            {
                continue;
            }

            if ( codepoint < 0x80 )
            {
                ret [out_pos++] = ( u8 ) codepoint;
            }
            else if ( codepoint < 0x0800 )
            {
                ret [out_pos++] = ( u8 ) ( 0xC0 | ( codepoint >> 6 ) );
                ret [out_pos++] = ( u8 ) ( 0x80 | ( codepoint & 0x3F ) );
            }
            else if ( codepoint < 0x10000 )
            {
                ret [out_pos++] = ( u8 ) ( 0xE0 | ( codepoint >> 12 ) );
                ret [out_pos++] = ( u8 ) ( 0x80 | ( ( codepoint >> 6 ) & 0x3F ) );
                ret [out_pos++] = ( u8 ) ( 0x80 | ( codepoint & 0x3F ) );
            }
            else
            {
                ret [out_pos++] = ( u8 ) ( 0xF0 | ( codepoint >> 18 ) );
                ret [out_pos++] = ( u8 ) ( 0x80 | ( ( codepoint >> 12 ) & 0x3F ) );
                ret [out_pos++] = ( u8 ) ( 0x80 | ( ( codepoint >> 6 ) & 0x3F ) );
                ret [out_pos++] = ( u8 ) ( 0x80 | ( codepoint & 0x3F ) );
            }
        }

        ret [out_pos] = 0;

        if ( items_written )
        {
            *items_written = out_pos;
        }

        return ret;
    }


    //! Convert from utf16 to tf8 string.
    bool StringUtil::utf16ToUtf8( std::string& strOut, u16* pSrc, u32 nLen )
    {
        if( _utf16_to_utf8( strOut, pSrc, nLen, 0, 0 ) )
        {
            return true;
        }

        return false;
    }

    //! Convert from utf8 to utf16 string. Not Implemented yet.
    bool StringUtil::utf8ToUtf16( std::wstring& strOut, u8* pSrc, u32 nLen )
    {
        assert( false && "not support now" );
        return false;
    }

    //------------------------------------------------------------
    bool StringUtil::equals( const std::string& str1, const std::string& str2, bool bCaseSensitive /*= true */ )
    { 
        if ( bCaseSensitive )
        {
            return ( str1 == str2 ) ? true : false;
        }
        else 
        {
            return equalsIgnoreCase( str1, str2 );
        }
    }

    //-------------------------------------------------------------------
    bool StringUtil::equalsIgnoreCase( const std::string& str1, const std::string& str2 )
    {
        if ( str1.length() == str2.length() )
        {
            return std::equal( str1.begin() , str1.end() , str2.begin() , no_case_compare_char );
        }
        return false;
    }

	bool StringUtil::isFloatNumber( std::string& s )
	{
		if ( s.find( '.' ) != std::string::npos
			|| s.find( 'e' ) != std::string::npos
			|| s.find( 'E' ) != std::string::npos )
		{
			return true;
		}

		return false;
	}

	u64 StringUtil::toU64( const std::string& val )
	{
		return atou64( val.c_str() );
	}

	u32 StringUtil::toU32( const std::string& val )
	{
		return atou32( val.c_str() );
	}

    template<class T>
    inline void internal_xtoa( u64 val, T *buf )
    {
        T *p;                /* pointer to traverse string */
        T *firstdig;         /* pointer to first digit */
        T temp;              /* temp char */
        u64 digval;         /* value of digit */
        p = buf;

        firstdig = p;           /* save pointer to first digit */

        do
        {
            digval = ( val % 10 );
            val /= 10;       /* get next digit */

            /* convert to ascii and store */
            *p++ = static_cast<T>( digval + T('0') );   /* a digit */
        }
        while ( val > 0 );

        /* We now have the digit of the number in the buffer, but in reverse
        *         order.  Thus we reverse them now. */
        *p-- = T('\0');            /* terminate string; p points to last digit */

        do
        {
            temp = *p;
            *p = *firstdig;
            *firstdig = temp;   /* swap *p and *firstdig */
            --p;
            ++firstdig;         /* advance to next two digits */
        }
        while ( firstdig < p ); /* repeat until halfway */
    }


    /* helper routine that does the main job. */
    void xtoa( u64 val, char *buf )
    {
        return internal_xtoa<char>(val,buf);
    }

    void xtoa( u64 val, wchar_t *buf )
    {
        internal_xtoa<wchar_t>( val , buf );
    }

    //-------------------------------------------------------------------
    std::wstring StringUtilW::valueOf( f64* pEles, u32 nCount )
    {
        return valueOfArrayW<f64>( pEles , nCount );
    }

    std::wstring StringUtilW::valueOf( f32* pEles, u32 nCount )
    {
        return valueOfArrayW<f32>( pEles , nCount );
    }

    std::wstring StringUtilW::valueOf( u64* pEles, u32 nCount )
    {
        return valueOfArrayW<u64>( pEles , nCount );
    }

    std::wstring StringUtilW::valueOf( s64* pEles, u32 nCount )
    {
        return valueOfArrayW<s64>( pEles , nCount );
    }

    std::wstring StringUtilW::valueOf( u32* pEles, u32 nCount )
    {
        return valueOfArrayW<u32>( pEles , nCount );
    }

    std::wstring StringUtilW::valueOf( s32* pEles, u32 nCount )
    {
        return valueOfArrayW<s32>( pEles , nCount );
    }

    std::wstring StringUtilW::valueOf( u8* pEles, u32 nCount )
    {
        return valueOfArrayW<s8>( reinterpret_cast<s8*>(pEles) , nCount );
    }

	std::wstring StringUtilW::valueOf( s64 i )
	{
		wchar_t sz[64] = {};
		s64toa( i , sz );
		return sz;
	}

	std::wstring StringUtilW::valueOf( u64 i )
	{
		wchar_t sz[64] = {};
		u64toa( i , sz );
		return sz;
	}

	std::wstring StringUtilW::valueOf( s32 i )
	{
		wchar_t sz[64] = {};
		s32toa( i , sz );
		return sz;
	}

	std::wstring StringUtilW::valueOf( u32 i )
	{
		wchar_t sz[64] = {};
		u32toa( i , sz );
		return sz;
	}

	std::wstring StringUtilW::valueOf( f64 f )
	{
		std::wostringstream oss;
		oss << f;
		return oss.str();
// 		wchar_t szTemp[64]={};
// 		if ( swprintf( szTemp , 63 , L"%e" , f ) )
// 		{
// 			return szTemp;
// 		}
// 		else
// 		{
// 			return StringUtil::BLANKW;
// 		}
	}

    //-------------------------------------------------------------------
    bool StringUtilW::toF64Elements( const std::wstring& val, f64* pEles, u32 nCount, f64 valDefault, const wchar_t* filter/* = L", " */ )
    {
        return stringUtil_toElements<f64>( val , pEles , nCount , valDefault , filter );
    }

    bool StringUtilW::toF32Elements( const std::wstring& val, f32* pEles, u32 nCount, f32 valDefault, const wchar_t* filter/* = L", " */ )
    {
        return stringUtil_toElements<f32>( val , pEles , nCount , valDefault , filter );
    }

    bool StringUtilW::toU64Elements( const std::wstring& val, u64* pEles, u32 nCount, u64 valDefault, const wchar_t* filter/* = L", " */ )
    {
        return stringUtil_toElements<u64>( val , pEles , nCount , valDefault , filter );
    }

    bool StringUtilW::toS64Elements( const std::wstring& val, s64* pEles, u32 nCount, s64 valDefault, const wchar_t* filter/* = L", " */ )
    {
        return stringUtil_toElements<s64>( val , pEles , nCount , valDefault , filter );
    }

    bool StringUtilW::toU32Elements( const std::wstring& val, u32* pEles, u32 nCount, u32 valDefault, const wchar_t* filter/* = L", " */ )
    {
        return stringUtil_toElements<u32>( val , pEles , nCount , valDefault , filter );
    }

    bool StringUtilW::toS32Elements( const std::wstring& val, s32* pEles, u32 nCount, s32 valDefault, const wchar_t* filter/* = L", " */ )
    {
        return stringUtil_toElements<s32>( val , pEles , nCount , valDefault , filter );
    }

    bool StringUtilW::toU8Elements( const std::wstring& val, u8* pEles, u32 nCount, u8 valDefault, const wchar_t* filter/* = L", " */ )
    {
        return stringUtil_toElements<u8>( val , pEles , nCount , valDefault , filter );
    }
    //-------------------------------------------------------------------
    void StringUtilW::split( std::vector<std::wstring>& ret, const std::wstring& str, const std::wstring& delims, unsigned int maxSplits )
    {
        stringUtilSplit( ret , str , delims , maxSplits );
    }

	s64 StringUtilW::toS64( const std::wstring& val )
	{
		return atos64( val.c_str() );
	}

	s32 StringUtilW::toS32( const std::wstring& val )
	{
		return atos32( val.c_str() );
	}


}
