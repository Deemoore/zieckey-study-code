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

        class _EXPORT_OSLIB Listener
        {
        public:
            //! \brief When we parse the INI file, every found of the section/key-value,
            //!     this interface will be called!
            //! \param const StringA & section - 
            //! \param const StringA & key - 
            //! \param const StringA & value - 
            //! \return void - 
            virtual void onValue(::osl::INIParser& parser, const ::osl::StringA& section, const ::osl::StringA& key, const ::osl::StringA& value) = 0;
        };

        class _EXPORT_OSLIB Iterator
        {
        public:
            StringA* section;
            StringA* key;
            StringA* value;

        public:
            Iterator() : parser_(NULL)
            {
                init();
            }

            explicit Iterator(INIParser* parser)
                : parser_(parser)
            {
            }

            Iterator(const Iterator& rhs)
            {
                parser_ = rhs.parser_;
                section = rhs.section;
                key     = rhs.key;
                value   = rhs.value;

                section_map_iterator_ = rhs.section_map_iterator_;
                kv_iterator_          = rhs.kv_iterator_;
            }
        private:
            INIParser* parser_;
            SectionMap::iterator section_map_iterator_;
            StringAStringAMap::iterator kv_iterator_;

            void init()
            {
                section = NULL;
                key     = NULL;
                value   = NULL;
                if (parser_)
                {
                    section_map_iterator_ = parser_->section_map_.begin();
                    if (section_map_iterator_ != parser_->section_map_.end())
                    {
                        section = &(section_map_iterator_->first);

                        kv_iterator_ = section_map_iterator_->second.begin();

                        if (kv_iterator_ != section_map_iterator_->second.end())
                        {
                            key   = &(kv_iterator_->first);
                            value = &(kv_iterator_->second);
                        }

                    }
                }
            }
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
        //! \param Listener * pl - 
        //! \return void - 
        void addListener( Listener* pl );
        void removeListener( Listener* pl );

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

        //! \brief Serialize the INI to output string
        //! \return - osl::StringA
        StringA serialize() const;

        //! \brief Serialize the INI to output string
        //! \param[in] - StringA & output
        //! \param[in] - MemoryDataStream & buf
        //! \param[in] - std::ostream & os
        //! \return - void
        void serialize(StringA& output) const;
        void serialize(MemoryDataStream& buf) const;
        void serialize(std::ostream& os) const;

        void setKVSeparator(const StringA& separator) { kv_separator_  = separator; }
        void setLineSeparator(const StringA& separator) { line_separator_  = separator; }
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
        void _serialize(_stream_t& os) const;

    private:
        bool            case_sensitive_;//! case sensitive flag
        bool            stop_parsing_;  //! stop the parsing 
        SectionMap      section_map_; //! pair<section string, key/value map>
        osl::StringA    kv_separator_;//! The key/value separator
        osl::StringA    line_separator_;//! The key/value separator

        typedef std::list <Listener*> ListenerList;
        ListenerList    listeners_;

        //For the serialize output
        typedef List<StringA> StringAList;
        typedef Map<StringA, StringAList> StringAListMap;

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


