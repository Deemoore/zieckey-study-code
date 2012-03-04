#ifndef _QOSLIB_INI_PARSER_H_
#define _QOSLIB_INI_PARSER_H_

#include "osl/include/inner_pre.h"

#if H_PROVIDE_INI_PARSER

#include "osl/include/string_ext.h"

namespace osl
{
    class MemoryDataStream;

    //! \brief The class for INI format file's parsing.
    //! The INI file can contains comments lines which start with '#' or '//' 
    class _EXPORT_OSLIB INIParser 
    {
    public:
        typedef Map< StringA, StringA > StringAStringAMap;
        typedef Map< StringA, StringAStringAMap > SectionMap;

        typedef List< StringA > StringAList;
        typedef std::pair< StringA, StringAList> SectionPairEntry;
        typedef List< SectionPairEntry > SectionList;

        //! The listener will be called when parsing an INI file
        class _EXPORT_OSLIB ParseListener
        {
        public:
            virtual ~ParseListener() {}

            //! \brief When we parse the INI file, every found of the section/key-value,
            //!     this interface will be called!
            //! \param const StringA & section - 
            //! \param const StringA & key - 
            //! \param const StringA & value - 
            //! \return void - 
            virtual void onValue(::osl::INIParser& parser, const ::osl::StringA& section, const ::osl::StringA& key, const ::osl::StringA& value) = 0;
        };

        //! The listener will be called when visit the parsed INI file.
        //! The values may be not the order of the input INI file.
        //!     This order maybe not the same as the input file order, 
        //!  but it is much faster than SequenceVisitor
        class _EXPORT_OSLIB FastVisitor
        {
        public:
            virtual ~FastVisitor() {}

            virtual void visit(::osl::INIParser& parser, const ::osl::StringA& section, const ::osl::StringA& key, const ::osl::StringA& value) = 0;
        };

        //! The listener will be called when visit the parsed INI file
        //! The values' sequences is extremely as the order of the input INI file
        class _EXPORT_OSLIB SequenceVisitor
        {
        public:
            virtual ~SequenceVisitor() {}

            virtual void visit(::osl::INIParser& parser, const ::osl::StringA& section, const ::osl::StringA& key, const ::osl::StringA& value) = 0;
        };
    public:
        //! \brief 
        //! \param[in] - bool case_sensitive
        INIParser(bool case_sensitive = true);
        ~INIParser();

        //! \brief Clear the section/key-value map
        void reset();

        //! \brief Query whether it is case sensitive
        //! \return - bool
        bool isCaseSensitive() const { return case_sensitive_; }

        void setCaseSensitive(bool case_sensitive) { case_sensitive_ = case_sensitive; }

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

        //! \brief When parsing the INI file, you can call this function to stop the parsing
        //! \return void - 
        void stopParse(bool stop_parsing);

        //! \brief 
        //! \param ParseListener * pl - 
        //! \return void - 
        void addParseListener( ParseListener* pl );
        void removeParserListener( ParseListener* pl );

        //Query
    public:

        //! \brief Get the value of specified key from the default section
        //! \param const StringA & key - 
        //! \return const char* - If find return the value, or return NULL
        const char* get( const StringA& key ) const;

        //! \brief Get the value of specified key from a certain section
        //! \param const StringA & section - The section name
        //! \param const StringA & key - The key
        //! \return const char* - If find return the value, or return NULL
        const char* get( const StringA& section, const StringA& key ) const;

        //! \brief Set the value of specified key into a certain section
        //! \param const StringA & section - The section name
        //! \param const StringA & key - The key
        //! \param const StringA & key - The value
        void set( const StringA& section, const StringA& key, const StringA& value );

        //! \brief Get the default key/value Map
        //! \return const StringAStringAMap& - 
        const StringAStringAMap& getDefaultKeyValueMap();

        //! \brief Get the key/value Map of a certain section
        //! \param const StringA & section - The section name
        //! \return const StringAStringAMap& - 
        const StringAStringAMap& getKeyValueMap(const StringA& section);

        //! \brief Get the section full map
        //! \return - const SectionMap&
        const SectionMap& getSectionMap() const { return section_map_; }

        //Separator
    public:
        void setKVSeparator(const StringA& separator) { kv_separator_  = separator; }
        void setLineSeparator(const StringA& separator) { line_separator_  = separator; }

        const StringA& line_separator() const { return line_separator_; }
        const StringA& kv_separator() const { return kv_separator_; }

        //Visit
    public:

        //! \brief Visit all the section/key/value in the memory sorted order
        //!     This order maybe not the same as the input file order, 
        //!  but it is much faster than SequenceVisitor
        //! \param[in] - FastVisitor & visitor
        //! \return - void
        void visit(FastVisitor& visitor) const;

        //! \brief Visit all the section/key/value in the input file order
        //! \param[in] - SequenceVisitor & visitor
        //! \return - void
        void visit(SequenceVisitor& visitor) const;

        //Serialize
    public:

        //! \brief Serialize the INI to output string
        //! \param[in] - bool input_order - true if we want to 
        //!     serialize this INI object as the order of the input INI file
        //! \return - osl::StringA
        StringA serialize(bool input_order = false) const;

        //! \brief Serialize the INI to output string
        //! \param[in] - StringA & output
        //! \param[in] - MemoryDataStream & buf
        //! \param[in] - std::ostream & os
        //! \return - void
        void serialize(StringA& output, bool input_order = false) const;
        void serialize(MemoryDataStream& buf, bool input_order = false) const;
        void serialize(std::ostream& os, bool input_order = false) const;

    private:

        //! \brief Skip the lines which start with '#' or '//' or ";"
        //! \note Lines are separated by '\n' or '\r\n'
        //! \param const char * szsrc - The source string
        //! \return const char* - The pointer to the next line
        const char* skipCommit( const char* szsrc );

        //! \brief Skipping whitespace, such as '\n' '\r' ' '
        //! \param const char * szsrc - The source string
        //! \return const char* - The pointer to the next line
        const char* skipSpaces( const char* szsrc );

        template<class _stream_t>
        void _serialize(_stream_t& os, bool input_order = false) const;

    private:
        bool            case_sensitive_;//! case sensitive flag
        bool            stop_parsing_;  //! stop the parsing 
        SectionMap      section_map_; //! pair<section string, key/value map>
        osl::StringA    kv_separator_;//! The key/value separator
        osl::StringA    line_separator_;//! The key/value separator
        SectionList     section_list_; //! pair<section string, keys list>

        typedef std::list <ParseListener*> ListenerList;
        ListenerList    listeners_;

        class SequenceParseListener;
    };

    //---------------------------------------------------------
    inline void INIParser::reset()
    {
        section_map_.clear();
    }

    inline void INIParser::stopParse(bool stop_parsing)
    {
        stop_parsing_ = stop_parsing;
    }

};// end of namespace osl

#endif // end of #if H_PROVIDE_INI_PARSER
#endif // end of #define _QOSLIB_MD5_H_


