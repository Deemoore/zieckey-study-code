#ifndef _QNETWORKLIB_HTTP_HEADER_PARSER_H__
#define _QNETWORKLIB_HTTP_HEADER_PARSER_H__




#if H_USING_CURL



namespace net
{

    class _EXPORT_NET HttpHeaderParser : public osl::Object, osl::NoCopy
    {
    public:
        HttpHeaderParser();

        bool parse( const osl::StringA& strHeader );
        bool parse( const char* pheader, const osl::u32 nlen );

    public:
        const osl::StringA& getHttpRespCodeLine() const; //! return the HTTP response first line, like "HTTP/1.1 200 OK"
        const osl::StringA& getHttpProtocolVersion() const; //! return HTTP protocol version, like "HTTP/1.1"
        osl::s32 getHttpRespCode() const; //! return the HTTP response code, like 200, 304, 404 ...

        //! \brief According to the key, return the value. 
        //!     e.g. key="Content-Type", will return "text/html; charset=UTF-8" something like it.
        //! \note If we cannot find the key we will return "".
        osl::StringA getMetaData( const osl::StringA& key ); 

        const osl::StringAStringAMap& getMetaDataMap() const;

    private:
        osl::StringA               m_strHttpRespCodeLine; //!< the HTTP response first line, like "HTTP/1.1 200 OK"
        osl::s32                         m_nHttpRespCode; //!< the HTTP response code, like 200, 304, 404 ...
        osl::StringA            m_strHttpProtocolVersion; //!< like "HTTP/1.1"

        osl::StringAStringAMap       m_mapHeaderMetaData; //!< the HTTP header meta data
    };
    typedef osl::RefPtr<HttpHeaderParser>  HttpHeaderParserPtr;



    //-----------------------------------------------------------
    //-----------------------------------------------------------
    //-----------------------------------------------------------
    inline HttpHeaderParser::HttpHeaderParser()
        : m_nHttpRespCode( -1 )
    {
    }
    inline bool HttpHeaderParser::parse( const osl::StringA& strHeader )
    {
		return parse( strHeader.c_str(), (osl::u32)strHeader.size() );
    }
    inline osl::s32 HttpHeaderParser::getHttpRespCode() const
    {
        return m_nHttpRespCode;
    }
//     inline osl::StringA HttpHeaderParser::getHttpRespCodeLine() const
//     {
//         return m_strHttpRespCodeLine;
//     }
//     inline osl::StringA HttpHeaderParser::getHttpProtocolVersion() const
//     {
//         return m_strHttpProtocolVersion;
//     }
    inline const osl::StringA& HttpHeaderParser::getHttpRespCodeLine() const
    {
        return m_strHttpRespCodeLine;
    }
    inline const osl::StringA& HttpHeaderParser::getHttpProtocolVersion() const
    {
        return m_strHttpProtocolVersion;
    }
    inline osl::StringA HttpHeaderParser::getMetaData( const osl::StringA& key )
    {
        osl::StringAStringAMap::iterator it = m_mapHeaderMetaData.find( key );
        if ( it != m_mapHeaderMetaData.end() )
        {
            return it->second;
        }

        return "";
    }
    inline const osl::StringAStringAMap& HttpHeaderParser::getMetaDataMap() const
    {
        return m_mapHeaderMetaData;
    }

};//namespace




#endif // end of #if H_USING_CURL


#endif // end of #ifdef _QNETWORKLIB_HTTP_HEADER_PARSER_H__
