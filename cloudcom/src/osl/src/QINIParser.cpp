#include "osl/include/QOSLibPrerequisits.h"


#if H_PROVIDE_INI_PARSER

#include "osl/include/QString.h"
#include "osl/include/QStringUtil.h"
#include "osl/include/QINIParser.h"
#include "osl/include/QObject.h"
#include "osl/include/QDataStream.h"
#include "osl/include/QTokener.h"

namespace osl
{
	//---------------------------------------------------------
	bool INIParser::parse( const StringA& filename )
	{
		return parse( filename.c_str() );
	}

	bool INIParser::parse( const char* filename )
	{
        MemoryDataStream ds;
        if ( !ds.readRawFile(filename) )
        {
            return false;
        }
        
        return parse( (const char*)ds.getCache(), ds.getSize(), "\n", "=" );

        //----- OR ------
        //{{{// old code
        
        /*
		FILE *fp = ::fopen( filename, "r" );

		if ( fp == NULL )
		{
			return false;
		}

		const int MAX_LINE_SIZE = 256;

		char line[MAX_LINE_SIZE] = { '\0' };

		while ( !feof( fp ) )
		{
			char* fgets_ret = fgets( line, MAX_LINE_SIZE - 1, fp );

			if( fgets_ret == NULL )
			{
				break;
			}

			StringA key;
			StringA value;
			StringUtil::split( line, key, value, "=:" );
			StringUtil::trim( key, " \t\n", true, true );
			StringUtil::trim( value, " \t\n", true, true );
            if ( key.length() && value.length() )
            {
                m_mapINIKeyValue[key] = value;
            }
		}

		fclose( fp );
		return true;
        *///}}}
	}

    bool INIParser::parse( const char* data, size_t datalen )
    {
        return parse( data, datalen, "\n", "=" );

        //----- OR ------
        //{{{// old code

        /*
        const char* linebegin = data;
        const char* lineend = NULL;
        StringA line;
        while ( linebegin )
        {
            lineend = strchr( linebegin, '\n' );
            if ( !lineend )
            {
                break;
            }


            line = StringA( linebegin, lineend - linebegin );
            StringA key;
            StringA value;
            StringUtil::split( line, key, value, "=:" );
            StringUtil::trim( key, " \t\n", true, true );
            StringUtil::trim( value, " \t\n", true, true );
            if ( key.length() && value.length() )
            {
                m_mapINIKeyValue[key] = value;
            }

            linebegin = lineend + 1;
        }

        //the last line need special process
        if ( (size_t)(linebegin - data) < datalen )
        {
            line = StringA( linebegin, data + datalen - linebegin );
            StringA key;
            StringA value;
            StringUtil::split( line, key, value, "=:" );
            StringUtil::trim( key, " \t\n", true, true );
            StringUtil::trim( value, " \t\n", true, true );
            if ( key.length() && value.length() )
            {
                m_mapINIKeyValue[key] = value;
            }
        }

        return true;
        */ //}}}
    }

    bool INIParser::parse( const char* data, size_t datalen, const char* linesep, const char* kvsep )
    {
        if ( !data || 0 == datalen || !linesep || !kvsep )
        {
            return false;
        }

        const char* linebegin = data;
        const char* lineend = NULL;
        const char* kvseppos = NULL;
        size_t lineseplen = strlen( linesep );
        size_t kvseplen   = strlen( kvsep );
        StringA line;
        while ( linebegin )
        {
            linebegin = skipCommit( linebegin );
            linebegin = skipSpaces( linebegin );
            if ( !linebegin || linebegin >= data + datalen )
            {
                break;
            }
            
            lineend = strstr( linebegin, linesep );
            kvseppos = strstr( linebegin, kvsep );
            if ( !kvseppos || ( lineend && kvseppos >= lineend ) )
            {
                break;
            }
            
            StringA key   = StringA( linebegin, kvseppos - linebegin );
            StringA value;
            if ( lineend )
            {
                value = StringA( kvseppos + kvseplen, lineend - kvseppos - kvseplen );
            }
            else
            {
                value = StringA( kvseppos + kvseplen, data + datalen - kvseppos - kvseplen );
            }

            StringUtil::trim( key, " \t", true, true );
            if ( StringUtil::startsWith( key, "#") || StringUtil::startsWith( key, "//") )
            {
                //this line is a commit
                continue;
            }

            StringUtil::trim( value, " \t\r\n", true, true );
            if ( key.length() )
            {
                m_mapINIKeyValue[key] = value;
            }

            if ( !lineend )
            {
                break;
            }

            linebegin = lineend + lineseplen;
        }

        return true;
    }

	//---------------------------------------------------------
	const char* INIParser::get( const StringA& key ) const
	{
		StringAStringAMap::const_iterator it = m_mapINIKeyValue.find( key );

		if ( it == m_mapINIKeyValue.end() )
		{
			return NULL;
		}

		return ( it->second ).c_str();
	}

    const char* INIParser::skipCommit( const char* szsrc )
    {
        bool commit = false;
        Tokener token(szsrc);

        char c = token.nextClean();
        if ( c == '#' )
        {
            commit = true;
        }
        else if ( c == '/' && token.nextClean() == '/' )
        {
            commit = true;
        }

        if ( commit )
        {
            //If next line is also a committed string,
            //we need to continue skip it.
            token.skipToNextLine();
            return skipCommit( szsrc + token.getCurPos() );
        }
        

        return szsrc;
    }

    const char* INIParser::skipSpaces( const char* szsrc )
    {
        const char* t = szsrc;
        for ( ; t && *t != '\0' && *t <= ' '; ++t )
        {
            ;
        }
        return t;
    }
}// end of namespace osl


#endif // end of #if H_PROVIDE_INI_PARSER


