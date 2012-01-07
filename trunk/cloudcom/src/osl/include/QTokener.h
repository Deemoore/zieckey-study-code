#ifndef _QOSLIB_TOKENER_H_
#define _QOSLIB_TOKENER_H_

#if H_PROVIDE_APPSHELL

#include "osl/include/assert_ext.h"

namespace osl
{
    /**
    * A Tokener takes a source string and extracts characters and tokens from
    * it. It is used help to parse strings.
    * @version 2009-11-11
    */
    class _EXPORT_OSLIB Tokener
    {
    public:
        /**
        *	Construct a Tokener from a string.
        * @note	if needcopy = false, you MUST make sure the parameter string
        *	is available before we delete this Tokener.
        * @param s     A source string.
        */
        Tokener()
        {
            reset("", 0);
        }

        Tokener( const StringA& s );

        Tokener( const char* ps, const s32 ps_len = -1);

        /**
         * Calling this method is similar to reconstruct a new Tokener
         */
        void reset(const char* ps, const s32 ps_len = -1);
 
        ~Tokener();



        /**
        * Back up one character. This provides a sort of lookahead capability,
        * so that you can test for a digit or letter before attempting to parse
        * the next number or identifier.
        */
        bool back();

        /**
        * Get the next character in the source string.
        * This function will make the current position flag move to next position
        * @return The next character, or 0 if past the end of the source string.
        */
        char next();

        /**
        * Get the current character in the source string.
        *
        * @return The current character, or 0 if past the end of the source string.
        */
        char current();

        /**
        * Get the next char in the string, skipping whitespace.
        * @return  A character, or 0 if there are no more characters.
        */
        char nextClean();


        /**
        * Get the characters up to the next character <code>quote</code>.
        * Backslash processing is done.
        * If <code>quote</code> is not found, we do nothing and just
        * return a string empty "".
        * @param quote The quoting character, either
        *      <code>"</code>(double quote) or
        *      <code>'</code>(single quote) or
        *      other character
        * @return the string
        */
        StringA nextString( char quote );
        Slice nextSlice( char quote );

        /**
        * Get the characters up to the next white space( or tab, \n, \r, \0 ) character.
        *
        * @return the string
        */
        StringA nextString();

        
        Slice nextSlice();

        /**
        * Skip characters until the next character is the requested character.
        * If the requested character is not found, no characters are skipped.
        * @param to A character to skip to.
        * @return The requested character, or zero if the requested character
        * is not found.
        */
        char skipTo( char to );


        /**
        * Skip characters until come to a new line.
        * @remark If there is no new line, this function will do nothing.
        * @return true if successfully or false when failed.
        */
        bool skipToNextLine();



        /**
		* Skip characters until the previous character is the requested character.
		* If the requested character is not found, no characters are skipped.
		* @param to A character to skip to.
		* @return The requested character, or zero if the requested character
		* is not found.
		*/
		char skipBackTo( char to );

        /**
        * Skip all whitespace, tab, \n
        * @return false if arrived end of string.
        */
        bool skipSpaces();


        /**
        * Get the hex value of a character (base16).
        * @param c A character between '0' and '9' or between 'A' and 'F' or
        * between 'a' and 'f'.
        * @return  An int between 0 and 15, or -1 if c was not a hex digit.
        */
        static int dehexchar( char c );

        /** Gets current read position in the buffer. It also serve as length of buffer parsed. */
        u32 getCurPos()const
        {
            return m_iCurPos;
        }

        /** Query whether it is the end of the string.*/
        bool isEnd() const
        {
            if ( m_iCurPos >= m_len || m_pSrcString[m_iCurPos] == '\0' )
            {
                return true;
            }

            return false;
        }

        /** Gets size of data that can read from the current read position. */
        u32 getReadableSize() const
        {
            return m_len - m_iCurPos;
        }

	protected:
		void setCurrentPos( osl::u32 icurentpos )
		{
			m_iCurPos = icurentpos;
		}

    private:
        char*			  m_pSrcString;	 //! the source text string to be parsed
        u32                  m_iCurPos;  //! At first, set it 0
        u32                      m_len;  //!
        //char			   m_cLastChar;	 //! the char we get at last time
        //bool			m_bUseLastChar;  //! whether to use the char we get at last time
        //bool			     m_bCopied;	 //! m_pOrigString is new(ed),we need delete it
    };

    inline Tokener::Tokener( const StringA& s )
    {
        reset(s.c_str(), s.length());
    }

    inline Tokener::Tokener( const char* ps, const s32 len )
    {
        reset(ps, len);
    }

    inline void Tokener::reset( const char* ps, const s32 len )
    {
        m_iCurPos = 0;
        m_len     = len; 
        if ( len < 0 && ps )
        {
            m_len = strlen( ps );
        }

        m_pSrcString = const_cast<char*>( ps );
    }
    //----------------------------------------------------------------------------
    inline Tokener::~Tokener()
    {
    }

    //----------------------------------------------------------------------------
    inline bool Tokener::back()
    {
        if ( m_iCurPos <= 0 )
        {
            printf( "Stepping back two steps is not supported\n" );
            return false;
        }

        m_iCurPos -= 1;
        return true;
    }


    //----------------------------------------------------------------------------
    inline int Tokener::dehexchar( char c )
    {
        if ( c >= '0' && c <= '9' )
        {
            return c - '0';
        }

        if ( c >= 'A' && c <= 'F' )
        {
            return c - ( 'A' - 10 );
        }

        if ( c >= 'a' && c <= 'f' )
        {
            return c - ( 'a' - 10 );
        }

        return -1;
    }

    inline char Tokener::next()
    {
        if ( isEnd() )
        {
            //! End of string
            ++m_iCurPos;
            return 0;
        }

        return m_pSrcString[m_iCurPos++];
    }

    //----------------------------------------------------------------------------
    inline char Tokener::current()
    {
        if ( isEnd() )
        {
            return 0;
        }

        return m_pSrcString[m_iCurPos];
    }


    //--------------------------------------------------------------------------
    inline char Tokener::nextClean()
    {
        for ( ;; )
        {
            char c = next();

            if ( c == 0 || c > ' ' )
            {
                return c;
            }
        }
    }

    inline StringA Tokener::nextString()
    {
        return nextSlice().toString();
    }

    inline Slice Tokener::nextSlice()
    {
        if ( isEnd() )
        {
            return "";
        }

        u32 startpos = m_iCurPos;

        for ( ;; )
        {
			if (next() <= ' ')
			{
                return Slice( m_pSrcString + startpos, m_iCurPos - startpos - 1);
			}
			 
			if (isEnd())
			{
                return Slice( m_pSrcString + startpos, m_len - startpos );
			}
        }

        //H_ASSERT(false && "Logic ERROR. The rutuine SHOULD NOT come there.");
        //return Slice("", 0);
    }

    inline StringA Tokener::nextString( char quote )
    {
        return nextSlice().toString();
    }

    inline Slice Tokener::nextSlice( char quote )
    {
        u32 startpos = m_iCurPos;

        while ( next() != quote )
        {
            if ( isEnd() )
            {
                m_iCurPos = startpos;
                return "";
            }
        }

        assert( m_iCurPos > startpos );
        return Slice( m_pSrcString + startpos, m_iCurPos - startpos - 1 );
    }

    inline char Tokener::skipTo( char to )
    {
        char c;
        int startIndex = this->m_iCurPos;

        do
        {
            c = next();

            if ( c == 0 )
            {
                m_iCurPos = startIndex;
                return c;
            }
        }
        while ( c != to );

        back();
        return c;
    }

	inline char Tokener::skipBackTo( char to )
	{

		int startIndex = this->m_iCurPos;

		do
		{
			
			if ( !back() )
			{
				m_iCurPos = startIndex;
				return 0;
			}
		}
		while ( current() != to );
		char c = current();
		next();
		return c;
	}


//     void Tokener::skipSpaces()
//     {
//         while ( char c = m_pSrcString[m_iCurPos] )
//         {
//             if ( c == ' '  ||  c == '\t'  ||  c == '\r'  ||  c == '\n' )
//                 ++m_iCurPos;
//             else
//                 break;
//         }
//     }

    //--------------------------------------------------------------------------
    inline bool Tokener::skipSpaces()
    {
        for ( ;; )
        {
            char c = next();

            if ( c > ' ' )
            {
                back();
                return true;
            }
            else if ( c == 0 )
            {
                back();
                return true;
            }
            else
            {
                //changed by wuqiu
                //if(c!=' ')  return false;
                continue;
            }
        }
    }


    inline bool Tokener::skipToNextLine()
    {
        /*
        Windows line ending char is 0x0D0A
        Linux/Unix line ending char is 0x0A
        So, we just skipTo( 0x)A )
        */
        char c = skipTo( (char)0x0a ); 
        if ( c == 0 )
        {
            return false;
        }

        // skip the last char of this line, and then go to a new line
        next(); 
        return true;
    }


};//end of namespace os



#endif // #if H_PROVIDE_APPSHELL


#endif // #ifdef _QOSLIB_TOKENER_H_


