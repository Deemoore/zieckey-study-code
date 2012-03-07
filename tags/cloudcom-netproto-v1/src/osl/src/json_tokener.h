#pragma once
#if H_PROVIDE_JSON

#include "osl/include/tokener.h"
#include "osl/include/json.h"

namespace json
{
    //FD:
    class Object;

    /**
    * A JSONTokener takes a source string and extracts characters and tokens from
    * it. It is used by the JSONObject and JSONArray constructors to parse
    * JSON source strings.
    * @author Wei Zili
    * @version 2009-07-18
    */
    class JSONTokener : public osl::Tokener
    {
    public:
        /**
        *	Construct a JSONTokener from a string. You can use this token to
        * build a JSONObject
        *
        * @note	if needcopy = false, you MUST make sure the parameter string
        *	is available before we build the JSONObject.
        * @param s     A source string.
        */
        JSONTokener( const osl::StringA& s );

        JSONTokener( const char* ps, const osl::s32 ps_len = -1 );

        ~JSONTokener();


        /**
        * Get the characters up to the next close quote character.
        * Backslash processing is done. The formal JSON format does not
        * allow strings in single quotes, but an implementation is allowed to
        * accept them.
        * @param quote The quoting character, either
        *      <code>"</code>(osl::f64 quote) or
        *      <code>'</code>(single quote).
        * @param rs	the string we needed
        * @return true, if no error happened
        *	false, if Unterminated string.
        */
        bool nextString( char quote, osl::StringA& ___OUT rs );

        /**
        * Get the next value. The value can be a Boolean, Double, Integer,
        * JSONArray, JSONObject, Long, or osl::StringA, or the JSONObject.NULL object.
        * @return An object. or NULL if something wrong
        */
        Object* nextValue();

        /**
        * @brief skip comment strings
        *   Skip c-style or cpp-style comment
		* @note when return false, we don't skip any character
		* @return true, if skip successfully
		*		  false, if the comment format is wrong. 
        */
        bool skipComment();
        bool skipCStyleComment();   /* this is a c-style comment*/
        bool skipCppStyleComment(); // this is a cpp-style comment

        /** Convert an unicode number to UTF8 string */
        static osl::StringA convertUnicodeToUTF8( osl::u32 unicode );

        /** Convert an unicode 4 bytes escape string sequence to an unicode number */
        bool decodeUnicode4BytesSequence( osl::u32 &unicode );

        /** Convert an unicode escape string sequence to an unicode number */
        bool decodeUnicodeEscapeSequence( osl::u32 &unicode );

    private:
        enum { DEFAULT_BUFFER_SIZE = 512 };
    };

    inline JSONTokener::JSONTokener( const osl::StringA& s )
        : Tokener( s )
    {
    }

    inline JSONTokener::JSONTokener( const char* ps, const osl::s32 len )
        : Tokener( ps, len )
    {
    }

    inline JSONTokener::~JSONTokener()
    {
    }


    inline bool JSONTokener::nextString( char quote, osl::StringA& ___OUT rs )
    {
        osl::MemoryDataStream sb( DEFAULT_BUFFER_SIZE );
        char c = 0;

        for ( ;; )
        {
            c = next();

            switch ( c )
            {
            case 0:
                fprintf( stderr, "Unterminated string\n" );
                return false;
            case '\\':	//! Escape character
                c = next();

                switch ( c )
                {
                case 'b':
                    sb << '\b';
                    break;
                case 't':
                    sb << '\t';
                    break;
                case 'n':
                    sb << '\n';
                    break;
                case 'f':
                    sb << '\f';
                    break;
                case 'r':
                    sb << '\r';
                    break;
                case 'u':
                    {
                        //! e.g. \u1524 is a unicode character
                        osl::u32 unicode = 0;
                        if ( !decodeUnicodeEscapeSequence( unicode ) )
                        {
                            fprintf( stderr, "Illegal unicode escape.\n" );
                            return false;
                        }
                        osl::StringA utf8str = JSONTokener::convertUnicodeToUTF8( unicode );
                        sb.write(utf8str.c_str(), utf8str.length());
                    }

                    break;
                case '"':
                case '\'':
                case '\\':
                case '/':
                    sb << c;
                    break;
                default:
                    fprintf( stderr, "Illegal escape.[%c]\n", c );
                    return false;
                }

                break;
            default:

                if ( c == quote )
                {
                    rs = osl::StringA( ( char* )sb.getCache(), sb.getSize() );
                    return true;
                }

                sb << c;
                break;
            }
        } // end of for ( ;; )
    }

    inline Object* JSONTokener::nextValue()
    {
        char c = nextClean();
        if ( '/' == c )
        {
            if ( !skipComment() )
            {
                printf("wrong format of comment");
                return NULL;
            }
        }
        else
        {
            back();
        }

        c = nextClean();
        switch ( c )
        {
        case '"':
        case '\'':
            {
                osl::StringA strvalue;
                if ( nextString( c, strvalue ) )
                {
                    return H_NEW JSONString( strvalue );
                }
                else
                {
                    return NULL;
                }

            }
        case '{':
            back();
            return H_NEW JSONObject( this );
        case '[':
        case '(':
            back();
            return H_NEW JSONArray( this );
        default:
            //Handle unquoted text like: true, false, or null, or it can be a number.
            break;
        }

        /*
        * Handle unquoted text. This could be the values true, false, or
        * null, or it can be a number. An implementation (such as this one)
        * is allowed to also accept non-standard forms.
        *
        * Accumulate characters until we reach the end of the text or a
        * formatting character.
        */

        osl::MemoryDataStream sb( DEFAULT_BUFFER_SIZE );
        osl::StringA specialchars( ",:]}/\\\"[{;=#" );

        while ( c >= ' ' && specialchars.find( c ) == osl::StringA::npos )
        {
            sb.write( c );
            c = next();
        }

        back();

        osl::StringA s( ( char* )sb.getCache(), sb.getSize() );

        if ( s == "" )
        {
            printf( "Miss value\n" );
            return NULL;
        }

        return JSONObject::stringToValue( s );
    }


    //--------------------------------------------------------------------------
    inline bool JSONTokener::skipComment()
    {
        char c = next();
        bool successful = false;

        if ( c == '*' )
        {
            successful = skipCStyleComment();
        }
        else if ( c == '/' )
        {
            successful = skipCppStyleComment();
        }

        if ( !successful )
        {
            back();
            return false;
        }

        return true;
    }

    //--------------------------------------------------------------------------
    inline bool JSONTokener::skipCStyleComment()
    {
        osl::u32 iCurrentPos = getCurPos();
        while ( !isEnd() )
        {
            if ( next() == '*' && current() == '/' )
            {
                next();//skip '/'
                return true;
            }
        }

        setCurrentPos( iCurrentPos );
        return false;
    }


    //--------------------------------------------------------------------------
    inline bool JSONTokener::skipCppStyleComment()
    {
        osl::u32 iCurrentPos = getCurPos();
        {
            if ( skipToNextLine() )
            { 
                return true;
            }
            // 			while ( !isEnd() )
            // 			{
            // 				char c = next();
            // 
            // 				if (  c == '\r'  ||  c == '\n' )
            // 				{
            // 					return true;
            // 				}
            // 			}
        }

        setCurrentPos( iCurrentPos );
        return false;
    }


    //----------------------------------------------------------------------------
    inline osl::StringA JSONTokener::convertUnicodeToUTF8( osl::u32 unicode )
    {
        osl::StringA result;

        // based on description from http://en.wikipedia.org/wiki/UTF-8

        if ( unicode <= 0x7f )
        {
            result.resize( 1 );
            result[0] = static_cast<char>( unicode );
        }
        else if ( unicode <= 0x7FF )
        {
            result.resize( 2 );
            result[1] = static_cast<char>( 0x80 | ( 0x3f & unicode ) );
            result[0] = static_cast<char>( 0xC0 | ( 0x1f & ( unicode >> 6 ) ) );
        }
        else if ( unicode <= 0xFFFF )
        {
            result.resize( 3 );
            result[2] = static_cast<char>( 0x80 | ( 0x3f & unicode ) );
            result[1] = 0x80 | static_cast<char>( ( 0x3f & ( unicode >> 6 ) ) );
            result[0] = 0xE0 | static_cast<char>( ( 0xf & ( unicode >> 12 ) ) );
        }
        else if ( unicode <= 0x10FFFF )
        {
            result.resize( 4 );
            result[3] = static_cast<char>( 0x80 | ( 0x3f & unicode ) );
            result[2] = static_cast<char>( 0x80 | ( 0x3f & ( unicode >> 6 ) ) );
            result[1] = static_cast<char>( 0x80 | ( 0x3f & ( unicode >> 12 ) ) );
            result[0] = static_cast<char>( 0xF0 | ( 0x7 & ( unicode >> 18 ) ) );
        }

        return result;
    }

    //----------------------------------------------------------------------------
    inline bool JSONTokener::decodeUnicodeEscapeSequence( osl::u32 &unicode )
    {
        if ( !decodeUnicode4BytesSequence( unicode ) )
        {
            return false;
        }

        if ( unicode >= 0xD800 && unicode <= 0xDBFF )
        {
            // surrogate pairs
            if ( getReadableSize() < 6 )
            {
                return false;
            }

            unsigned int surrogatePair;

            if ( next() == '\\' && next() == 'u' )
            {
                if ( decodeUnicode4BytesSequence( surrogatePair ) )
                {
                    unicode = 0x10000 + ( ( unicode & 0x3FF ) << 10 ) + ( surrogatePair & 0x3FF );
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    //----------------------------------------------------------------------------
    inline bool JSONTokener::decodeUnicode4BytesSequence( osl::u32 &unicode )
    {
        enum { Unicode_Len = 4 };// an unicode has 4 bytes

        if ( getReadableSize() < Unicode_Len )
        {
            return false;
        }

        unicode = 0;

        for ( int index = 0; index < Unicode_Len; ++index )
        {
            char c = next();
            unicode = unicode << 4;

            if ( c >= '0'  &&  c <= '9' )
            {
                unicode += c - '0';
            }
            else if ( c >= 'a'  &&  c <= 'f' )
            {
                unicode += c - 'a' + 10;
            }
            else if ( c >= 'A'  &&  c <= 'F' )
            {
                unicode += c - 'A' + 10;
            }
            else
            {
                return false;
            }
        }

        return true;
    }

};//end of namespace json




#endif //#if H_PROVIDE_JSON



