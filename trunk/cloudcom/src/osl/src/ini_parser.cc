#include "osl/include/inner_pre.h"


#if H_PROVIDE_INI_PARSER

#include "osl/include/ini_parser.h"
#include "osl/include/object.h"
#include "osl/include/data_stream.h"
#include "osl/include/tokener.h"

#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"

namespace osl
{
	//---------------------------------------------------------
    INIParser::INIParser( bool case_sensitive /*= true*/ ) : case_sensitive_(case_sensitive)
    {
    }

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
                section_map_[key] = value;
            }
		}

		fclose( fp );
		return true;
        *///}}}
	}

    bool INIParser::parse( const char* data, size_t datalen )
    {
        return parse( data, datalen, "\n", "=" );
    }

    bool INIParser::parse( const char* data, size_t datalen, const char* linesep, const char* kvsep )
    {
        if ( !data || 0 == datalen || !linesep || !kvsep )
        {
            return false;
        }

        kv_separator_ = kvsep;
        line_separator_ = linesep;

        const char* linebegin = data;
        const char* lineend = NULL;
        const char* kvseppos = NULL;
        size_t lineseplen = strlen( linesep );
        size_t kvseplen   = strlen( kvsep );
        StringA line;
        StringA section = "";
        char section_open = '[';
        char section_end = ']';
        while ( linebegin )
        {
            linebegin = skipCommit( linebegin );
            linebegin = skipSpaces( linebegin );
            if ( !linebegin || linebegin >= data + datalen )
            {
                //parse finished
                break;
            }

            if (*linebegin == section_open)
            {
                lineend = strchr(linebegin, section_end);
                if (!lineend || lineend <= linebegin)
                {
                    //fprintf(stderr, "Parse error, section format error!");
                    return false;
                }

                section = StringA(linebegin + 1, lineend - linebegin - 1);
                StringUtil::trim( section, " \t\r", true, true );
                if (!case_sensitive_)
                {
                    std::transform( section.begin(), section.end(), section.begin(), towlower );
                }
                lineend = strstr( lineend, linesep );
                if (!lineend)
                {
                    //parse finished
                    break;
                }
                
                linebegin = lineend + lineseplen;
                
                continue;
            }
            
            lineend = strstr( linebegin, linesep );
            kvseppos = strstr( linebegin, kvsep );
            if ( !kvseppos || ( lineend && kvseppos >= lineend ) )
            {
                //parse finished
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
            StringUtil::trim( value, " \t\r\n", true, true );
            if ( key.length() )
            {
                if (!case_sensitive_)
                {
                     std::transform( key.begin(), key.end(), key.begin(), towlower );
                }
                
                section_map_[section][key] = value;
            }

            if ( !lineend )
            {
                //parse finished
                break;
            }

            linebegin = lineend + lineseplen;
        }

        return true;
    }

	//---------------------------------------------------------
	const char* INIParser::get( const StringA& key ) const
	{
        return get("", key);
	}

    const char* INIParser::get( const StringA& section, const StringA& key ) const
    {
        StringA section_lower;
        StringA key_lower;

        const StringA* pkey = &key;
        const StringA* psection = &section;
        if (!case_sensitive_)
        {
            section_lower = section;
            key_lower = key;
            std::transform( section_lower.begin(), section_lower.end(), section_lower.begin(), towlower );
            std::transform( key_lower.begin(), key_lower.end(), key_lower.begin(), towlower );
            pkey = &key_lower;
            psection = &section_lower;
        }

        SectionMap::const_iterator sectionit = section_map_.find(*psection);
        if (sectionit == section_map_.end())
        {
            return NULL;
        }

        StringAStringAMap::const_iterator it = sectionit->second.find(*pkey);

        if ( it == sectionit->second.end() )
        {
            return NULL;
        }

        return ( it->second ).c_str();
    }


    void INIParser::set( const StringA& section, const StringA& key, const StringA& value )
    {
        section_map_[section][key] = value;
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
        for ( ; t && *t != '\0' && *t >= 0 && *t <= ' '; ++t )
        {
            ;
        }
        return t;
    }

    const INIParser::StringAStringAMap& INIParser::getDefaultKeyValueMap()
    {
        return getKeyValueMap("");
    }

    const INIParser::StringAStringAMap& INIParser::getKeyValueMap(const StringA& section)
    {
        StringAStringAMap& ret = section_map_[section];
        return ret;
    }


    StringA INIParser::serialize() const
    {
        StringA s;
        serialize(s);
        return s;
    }

    void INIParser::serialize( StringA& output ) const
    {
        MemoryDataStream stream;
        serialize(stream);
        output = StringA(stream.data(), stream.size());
    }

    void INIParser::serialize( MemoryDataStream& stream ) const
    {
        stream.reserve(4096);
        _serialize(stream);
    }

    void INIParser::serialize( std::ostream& stream ) const
    {
        _serialize(stream);
    }

    template<class _stream_t>
    void osl::INIParser::_serialize( _stream_t& stream ) const
    {
        assert(line_separator_.length() > 0);
        assert(kv_separator_.length() > 0);
        if (line_separator_.empty() || kv_separator_.empty())
        {
            return;
        }
        
        SectionMap::const_iterator it_sectioin(section_map_.begin());
        SectionMap::const_iterator ite_sectioin(section_map_.end());
        for (; it_sectioin != ite_sectioin; ++it_sectioin)
        {
            if (it_sectioin->first.length() > 0)
            {
                stream.write("[", 1);
                stream.write(it_sectioin->first.c_str(), it_sectioin->first.length());
                stream.write("]", 1);
                stream.write(line_separator_.c_str(), line_separator_.size());
            }

            StringAStringAMap::const_iterator it(it_sectioin->second.begin());
            StringAStringAMap::const_iterator ite(it_sectioin->second.end());
            for (; it != ite; ++it)
            {
                stream.write(it->first.c_str(), it->first.length());
                stream.write(kv_separator_.c_str(), kv_separator_.size());
                stream.write(it->second.c_str(), it->second.length());
                stream.write(line_separator_.c_str(), line_separator_.size());
            }
            stream.write(line_separator_.c_str(), line_separator_.size());
            stream.write(line_separator_.c_str(), line_separator_.size());
        }
    }

}// end of namespace osl


#endif // end of #if H_PROVIDE_INI_PARSER


