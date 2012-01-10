#ifndef _QOSLIB_INI_PARSER_H_
#define _QOSLIB_INI_PARSER_H_

#if H_PROVIDE_INI_PARSER

#include "osl/include/string_ext.h"

namespace osl
{
    //! \brief The class for ini format file's parsing.
    //! The INI file can contains comments lines which start with '#' or '//' 
    class _EXPORT_OSLIB INIParser 
    {
    public:
        INIParser(){}

        //! \brief Parse the INI file
        //! \param const StringA & filename - The INI file name
        //! \return bool - return true if parse successfully
        bool parse( const StringA& filename );
        bool parse( const char* filename );

        //! \brief Parse the raw data.
        //!     We will parse the data every line.
        //!   Lines are separated by '\n'.
        //! \param const char * data - The source data
        //! \param size_t datalen - The length of the data
        //! \return bool - return true if parse successfully
        bool parse( const char* data, size_t datalen );

        //! \brief Parse the raw data
        //!     We will parse the data line by line.
        //!   Lines are separated by <code>linesep</code>
        //!   key-value is separated by <code>keyvaluesep</code>
        //! \param const char * data - 
        //! \param size_t datalen - 
        //! \param const char * linesep - the line separator
        //! \param const char * keyvaluesep - the key/value separator
        //! \return bool - 
        bool parse( const char* data, size_t datalen, const char* linesep, const char* keyvaluesep );

        //! \brief Get the value of specified key
        //! \param const StringA & key - 
        //! \return const char* - If find return the value, or return NULL
        const char* get( const StringA& key ) const;

        //! \brief 
        //! \return const StringAStringAMap& - 
        const StringAStringAMap& getKeyValueMap() const { return m_mapINIKeyValue; }

    private:

        //! \brief Skip the lines which start with '#' or '//' 
        //! \note Lines are separated by '\n' or '\r\n'
        //! \param const char * szsrc - The source string
        //! \return const char* - The pointer to the next line
        const char* skipCommit( const char* szsrc );

        //! \brief Skipping whitespace, such as '\n' '\r' ' '
        //! \param const char * szsrc - The source string
        //! \return const char* - The pointer to the next line
        const char* skipSpaces( const char* szsrc );

    private:
        StringAStringAMap m_mapINIKeyValue;
    };

};// end of namespace osl

#endif // end of #if H_PROVIDE_INI_PARSER
#endif // end of #define _QOSLIB_MD5_H_


