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
    INIParser::INIParser( bool case_sensitive /*= true*/ ) 
        : case_sensitive_(case_sensitive)
        , stop_parsing_(false)
    {
    }

    INIParser::~INIParser()
    {
        listeners_.clear();
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

    class INIParser::SequenceParseListener : public INIParser::ParseListener
    {
    public:
        SequenceParseListener(INIParser* parser) : parser_(parser) { parser_->addParseListener(this); }

        ~SequenceParseListener() { parser_->removeParserListener(this); }

        virtual void onValue(::osl::INIParser& parser, const ::osl::StringA& section, const ::osl::StringA& key, const ::osl::StringA& value)
        {
            INIParser::StringAList* keys = NULL;
            SectionList::reverse_iterator it = parser_->section_list_.rbegin();
            if (it != parser_->section_list_.rend() && it->first == section)
            {
                keys = &(it->second);
            }
            else
            {
                parser_->section_list_.push_back(std::make_pair<StringA, INIParser::StringAList>(section, INIParser::StringAList()));
                keys = &(parser_->section_list_.rbegin()->second);
            }
            keys->push_back(key);
        }

    private:
        INIParser* parser_;
    };

    bool INIParser::parse( const char* data, size_t datalen, const char* linesep, const char* kvsep )
    {
        if ( !data || 0 == datalen || !linesep || !kvsep )
        {
            return false;
        }

        SequenceParseListener listener(this);

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
        while ( linebegin && !stop_parsing_ )
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
                if (!listeners_.empty())
                {
                    ListenerList::iterator it(listeners_.begin());
                    ListenerList::iterator ite(listeners_.end());
                    for (; it != ite; ++it)
                    {
                        (*it)->onValue(*this, section, key, value);
                    }
                }
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

    void INIParser::addParseListener( ParseListener* pl )
    {
        listeners_.push_back(pl);
    }

    void INIParser::removeParserListener( ParseListener* pl )
    {
        listeners_.remove(pl);
    }

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
        else if ( c == ';' )
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


    StringA INIParser::serialize(bool input_order /*= false*/) const
    {
        StringA s;
        serialize(s, input_order);
        return s;
    }

    void INIParser::serialize( StringA& output, bool input_order /*= false*/ ) const
    {
        MemoryDataStream stream;
        serialize(stream, input_order);
        output = StringA(stream.data(), stream.size());
    }

    void INIParser::serialize( MemoryDataStream& stream, bool input_order /*= false*/ ) const
    {
        stream.reserve(4096);
        _serialize(stream, input_order);
    }

    void INIParser::serialize( std::ostream& stream, bool input_order /*= false*/ ) const
    {
        _serialize(stream, input_order);
    }

    template< typename _stream_t >
    class SerializeVistor
    {
    public:
        SerializeVistor() : stream_(NULL) {}

    protected:
        void Visit(::osl::INIParser& parser, const ::osl::StringA& section, const ::osl::StringA& key, const ::osl::StringA& value)
        {
            assert(stream_);
            if (last_section_ != section)
            {
                last_section_ = section;
                stream_->write("[", 1);
                stream_->write(section.c_str(), section.length());
                stream_->write("]", 1);
                stream_->write(parser.line_separator().c_str(), parser.line_separator().size());
            }

            stream_->write(key.c_str(), key.length());
            stream_->write(parser.kv_separator().c_str(), parser.kv_separator().size());
            stream_->write(value.c_str(), value.length());
            stream_->write(parser.line_separator().c_str(), parser.line_separator().size());
        }

    protected:
        void set_stream(_stream_t * stream) { stream_ = stream; }

    protected:
        _stream_t * stream_;
        ::osl::StringA last_section_;
    };

    template< typename _stream_t >
    class SerializeFastVistor : public INIParser::FastVisitor, public SerializeVistor<_stream_t>
    {
    public:
        SerializeFastVistor(_stream_t * stream) { SerializeVistor<_stream_t>::set_stream(stream); }

        virtual void visit(::osl::INIParser& parser, const ::osl::StringA& section, const ::osl::StringA& key, const ::osl::StringA& value)
        {
            SerializeVistor<_stream_t>::Visit(parser, section, key, value);
        }
    };

    template< typename _stream_t >
    class SerializeSequenceVistor : public INIParser::SequenceVisitor, public SerializeVistor<_stream_t>
    {
    public:
        SerializeSequenceVistor(_stream_t * stream) { SerializeVistor<_stream_t>::set_stream(stream); }

        virtual void visit(::osl::INIParser& parser, const ::osl::StringA& section, const ::osl::StringA& key, const ::osl::StringA& value)
        {
            SerializeVistor<_stream_t>::Visit(parser, section, key, value);
        }
    };

    template<class _stream_t>
    void osl::INIParser::_serialize( _stream_t& stream, bool input_order /*= false*/ ) const
    {
        assert(line_separator_.length() > 0);
        assert(kv_separator_.length() > 0);
        if (line_separator_.empty() || kv_separator_.empty())
        {
            return;
        }

        if (input_order && section_list_.size() == section_map_.size())
        {
            SerializeSequenceVistor<_stream_t> visitor(&stream);
            visit(visitor);
        }
        else
        {

            SerializeFastVistor<_stream_t> visitor(&stream);
            visit(visitor);
        }
    }

    void INIParser::visit( FastVisitor& visitor ) const
    {
        SectionMap::const_iterator it_sectioin(section_map_.begin());
        SectionMap::const_iterator ite_sectioin(section_map_.end());
        for (; it_sectioin != ite_sectioin; ++it_sectioin)
        {
            StringAStringAMap::const_iterator it(it_sectioin->second.begin());
            StringAStringAMap::const_iterator ite(it_sectioin->second.end());
            for (; it != ite; ++it)
            {
                visitor.visit(const_cast<INIParser&>(*this), it_sectioin->first, it->first, it->second);
            }
        }
    }

    void INIParser::visit( SequenceVisitor& visitor ) const
    {
        SectionList::const_iterator it_section_list(section_list_.begin());
        SectionList::const_iterator ite_section_list(section_list_.end());
        for (; it_section_list != ite_section_list; ++it_section_list)
        {
            SectionMap::const_iterator it_section_map(section_map_.find(it_section_list->first));
            assert(it_section_map != section_map_.end());
            StringAList::const_iterator it_key(it_section_list->second.begin());
            StringAList::const_iterator ite_key(it_section_list->second.end());
            for (; it_key != ite_key; ++it_key)
            {
                StringAStringAMap::const_iterator it_map = it_section_map->second.find(*(it_key));
                assert(it_map != it_section_map->second.end());
                visitor.visit(const_cast<INIParser&>(*this), it_section_list->first, *it_key, it_map->second);
            }
        }
    }

}// end of namespace osl


#endif // end of #if H_PROVIDE_INI_PARSER


