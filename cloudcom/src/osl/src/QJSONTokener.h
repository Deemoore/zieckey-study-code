#pragma once
#if H_PROVIDE_JSON

#include "osl/include/QTokener.h"

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

};//end of namespace json




#endif //#if H_PROVIDE_JSON



