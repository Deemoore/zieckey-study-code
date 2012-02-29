#ifndef _OSLIB_JSON_H_
#define _OSLIB_JSON_H_

#include "osl/include/inner_pre.h"
#include "osl/include/malloc_micro.h"
#include "osl/include/string_ext.h"
#include "osl/include/object.h"
#include "osl/include/string_util.h"
#include "osl/include/data_stream.h"

#if H_PROVIDE_JSON

#if H_PROVIDE_UUID
#include "osl/include/uuid.h"
#endif 

#include "osl/include/no_copy.h"

namespace json
{
    enum ObjectType
    {
        OT_UNKNOWN,
        OT_OBJECT,	//! JSONObject
        OT_ARRAY,	//! JSONArray
        OT_STRING,	//! JSONString
        OT_INTEGER,	//! JSONInteger
        OT_DOUBLE,	//!	JSONDouble
        OT_BOOLEAN,	//! JSONBoolean
        OT_NULL		//! JSONNull
    };

	class JSONBoolean;
	class JSONInteger;
	class JSONDouble;
	class JSONString;
	class JSONArray;
	class JSONObject;

	template<typename _Type> struct TypeToJsonType;

	template<>
	struct TypeToJsonType<bool>
	{
		typedef JSONBoolean type ;
		enum { enum_type = OT_BOOLEAN } ;
	};

	template<>
	struct TypeToJsonType<osl::s64>
	{
		typedef JSONInteger type ;
		enum { enum_type = OT_INTEGER } ;
	};

    template<>
        struct TypeToJsonType<osl::f64>
        {
            typedef JSONDouble type ;
            enum { enum_type = OT_DOUBLE } ;
        };

    template<>
        struct TypeToJsonType<osl::StringA>
        {
            typedef JSONString type ;
            enum { enum_type = OT_STRING } ;
        };

    template<>
        struct TypeToJsonType<JSONArray>
        {
            typedef JSONArray type;
            enum { enum_type = OT_ARRAY } ;
        };

    template<>
        struct TypeToJsonType<JSONObject>
        {
            typedef JSONObject type;
            enum { enum_type = OT_OBJECT } ;
        };

    /**
     *	Abstract class of all json Objects :
     *	JSONObject, JSONArray, JSONString, JSONInteger, JSONDouble, JSONBoolean, JSONNull
     */
    class _EXPORT_OSLIB Object : public osl::Object
    {
        H_ALLOC_OBJECT( Object );
    public:
        enum{ OBJECT_TYPE = OT_UNKNOWN };
        Object( const ObjectType e )
            : m_type( e ) {}

        virtual ~Object() {}

        ObjectType getType() const
        {
            return m_type;
        }


        bool isTypeOf( ObjectType ot )
        {
            return ( ot == m_type );
        }

        /** Make a JSON text of an Object value. the result is stored in outs
         *	e.g. string "abc" => "\"abc\""
         *	e.g. string "ab\t" => "\"ab\\t\""
         *	e.g. int 324 =>  "324"
         * @param[out] outs, the json text string
         * @param[in] readable, true, to make a pretty printed JSON text of this object.
         *			false, to make a compact JSON text, no whitespace is added.
         * @return true, if success, or false
         */
        virtual bool toString( osl::StringA& ___OUT outs, bool readable = false ) const = 0;
        virtual bool toStringBuf( osl::MemoryDataStream& sb, size_t indent = 0 ) const = 0;

        /** 
         * @copybrief Object::toString(osl::StringA&,bool)
         * @param[in] readable, true, to make a pretty printed JSON text of this object.
         *			false, to make a compact JSON text, no whitespace is added.
         * @return the json text string
         */
        osl::StringA toString( bool readable = false ) const ;

        //         /** 
        // 		* @copybrief Object::toString(osl::StringA&,bool)
        //         * @param[out] sb, the string buffer, storing the json text
        //         * @param[in] indent, The indentation number of the top level.
        //         *			0, means no indent
        //         * @return true, if success, or false
        //         */
        //         bool toString( osl::MemoryDataStream& ___OUT sb, size_t indent = 0 ) const ;

        //! \warning This method is quite not effective, so make sure why you need call this method
        //! \note We mostly use this method to do some unit test
        //! \retrun true If rhs is the same type and the value is equal to each other
        virtual bool equals( const Object& rhs ) = 0;

    protected:
        /**
         * Deserialize the data stream to parse one json object.
         * First we deserialize a type and then deserialize an object according to the type.
         * @param file[in] the binary data stream
         * @param pObject[out] the parsed json object
         * @return true, if load a json object successfully, you need to take over the memory delete of pObject, or false.
         */
        static bool deserializeOneObject( osl::MemoryDataStream& ___IN file, Object*& ___OUT pObject );

        //! Load, Deserialize. load from data stream to convert it to a json object
        //!     Before we call this function, we has deserialized the a osl::u8
        //! as the type, so we just deserialize the data in this function
        //! and don't care about the first osl::u8 type.
        virtual bool loadFrom( osl::MemoryDataStream& ___IN file ) = 0/*{ return true; }*/;

        //! Save, Serializer. save the json object in the data stream
        //! we first save the type as a osl::u8 in the file and then save the data.
        virtual void saveTo( osl::MemoryDataStream& ___OUT file ) const = 0/*{}*/;

    private:
        ObjectType	m_type;

    private:
        friend class JSONArray;
        friend class JSONObject;
        Object();
    };

    typedef osl::RefPtr<Object> ObjectPtr;


    template<class ValueType>
    class JSONValueObjectImpl : public Object
    {
    public:
        JSONValueObjectImpl()
            : Object( static_cast<ObjectType>( TypeToJsonType<ValueType>::enum_type ) )
            , m_value( ValueType() )
        {
        }
        JSONValueObjectImpl( const ValueType& value ) 
            : Object( static_cast<ObjectType>( TypeToJsonType<ValueType>::enum_type )  ) 
            , m_value( value )
        {
        }

        const ValueType& getRealValue() const
        {
            return m_value;
        }

        ValueType& getRealValue()
        {
            return m_value;
        }

        void setValue( const ValueType& newvalue )
        {
            m_value = newvalue;
        }

        operator ValueType()
        {
            return m_value;
        }

    protected:
        ValueType m_value;
    };


    //-------------------------------------------------------------------------
    //-------- JSONInteger
    //-------------------------------------------------------------------------
    /**
     *	The concrete object of JSON
     */
    class _EXPORT_OSLIB JSONInteger : public JSONValueObjectImpl<osl::s64>
    {
        typedef JSONValueObjectImpl<osl::s64> BaseClass;
        H_ALLOC_OBJECT( JSONInteger );
    public:
        enum{ OBJECT_TYPE = OT_INTEGER };
        JSONInteger( osl::s64 value = 0 );
        JSONInteger& operator=( osl::s64 value );

        bool operator==( const JSONInteger& value )
        {
            return m_value == value.m_value;
        }
        bool operator==( osl::s64 value )
        {
            return m_value == value;
        }

        using Object::toString;//osl::StringA Object::toString( bool readable = false ) const ;
        virtual bool toString( osl::StringA& ___OUT s, bool readable = false )const;	//!< @copydoc Object::toString(osl::StringA&,bool)
        virtual bool toStringBuf( osl::MemoryDataStream& sb, size_t indent = 0 )const;

        //! \warning This method is quite not effective, so make sure why you need call this method
        //! \note We mostly use this method to do some unit test
        //! \retrun true If rhs is the same type and the value is equal to each other
        virtual bool equals( const Object& rhs );

    private:
        //! override method from base class json::Object
        virtual bool loadFrom( osl::MemoryDataStream& ___IN file );
        virtual void saveTo( osl::MemoryDataStream& ___OUT file ) const;
    };

    //-------------------------------------------------------------------------
    //-------- JSONDouble
    //-------------------------------------------------------------------------
    /**
     *	The concrete object of JSON
     */
    class _EXPORT_OSLIB JSONDouble : public JSONValueObjectImpl< osl::f64>
    {
        typedef JSONValueObjectImpl<osl::f64> BaseClass;
        H_ALLOC_OBJECT( JSONDouble );
    public:
        enum{ OBJECT_TYPE = OT_DOUBLE };
        JSONDouble( osl::f64 value = 0 );
        JSONDouble& operator=( osl::f64 value );

        bool equals( const JSONDouble& other, osl::f64 tolarence = 0.00001 );
        bool equals( osl::f64 value, osl::f64 tolarence = 0.00001  );

        using Object::toString;//osl::StringA Object::toString( bool readable = false ) const ;
        virtual bool toString( osl::StringA& ___OUT s, bool readable = false )const;	//!< @copydoc Object::toString(osl::StringA&,bool)
        virtual bool toStringBuf( osl::MemoryDataStream& sb, size_t indent = 0 )const;

        //! \warning This method is quite not effective, so make sure why you need call this method
        //! \note We mostly use this method to do some unit test
        //! \retrun true If rhs is the same type and the value is equal to each other
        virtual bool equals( const Object& rhs );
    private:
        //! override method from base class json::Object
        virtual bool loadFrom( osl::MemoryDataStream& ___IN file );
        virtual void saveTo( osl::MemoryDataStream& ___OUT file ) const;
    };

    //-------------------------------------------------------------------------
    //-------- JSONBoolean
    //-------------------------------------------------------------------------
    /**
     *	The concrete object of JSON
     */
    class _EXPORT_OSLIB JSONBoolean : public JSONValueObjectImpl<bool>
    {
        typedef JSONValueObjectImpl<bool> BaseClass;
        H_ALLOC_OBJECT( JSONBoolean );
    public:
        enum{ OBJECT_TYPE = OT_BOOLEAN };
        JSONBoolean( bool value = false );
        JSONBoolean& operator=( bool value );
        bool operator==( const JSONBoolean& value )
        {
            return m_value == value.m_value;
        }
        bool operator==( bool value )
        {
            return m_value == value;
        }

        using Object::toString;//osl::StringA Object::toString( bool readable = false ) const ;
        virtual bool toString( osl::StringA& ___OUT s, bool readable = false )const;	//!< @copydoc Object::toString(osl::StringA&,bool)
        virtual bool toStringBuf( osl::MemoryDataStream& sb, size_t indent = 0 )const;

        //! \warning This method is quite not effective, so make sure why you need call this method
        //! \note We mostly use this method to do some unit test
        //! \retrun true If rhs is the same type and the value is equal to each other
        virtual bool equals( const Object& rhs );
    private:
        //! override method from base class json::Object
        virtual bool loadFrom( osl::MemoryDataStream& ___IN file );
        virtual void saveTo( osl::MemoryDataStream& ___OUT file ) const;
    };


    //-------------------------------------------------------------------------
    //-------- JSONString
    //-------------------------------------------------------------------------
    /**
     *	The concrete object of JSON
     */
    class _EXPORT_OSLIB JSONString : public JSONValueObjectImpl<osl::StringA>
    {
        typedef JSONValueObjectImpl<osl::StringA> BaseClass;
        H_ALLOC_OBJECT( JSONString );
    public:
        enum{ OBJECT_TYPE = OT_STRING };
        JSONString( const osl::StringA& value );
        JSONString( const char* value = "" );
        JSONString& operator=( const osl::StringA& value );
        bool operator==( const JSONString& value )
        {
            return m_value == value.m_value;
        }
        bool operator==( osl::StringA& value )
        {
            return m_value == value;
        }
        bool operator==( const char* value )
        {
            return m_value == value;
        }

        using JSONValueObjectImpl<osl::StringA>::setValue;
        void setValue( const char* newvalue )
        {
            m_value = newvalue;
        }

        using Object::toString;//osl::StringA Object::toString( bool readable = false ) const ;
        virtual bool toString( osl::StringA& ___OUT s, bool readable = false )const;	//!< @copydoc Object::toString(osl::StringA&,bool)
        virtual bool toStringBuf( osl::MemoryDataStream& sb, size_t indent = 0 )const;

        //! \warning This method is quite not effective, so make sure why you need call this method
        //! \note We mostly use this method to do some unit test
        //! \retrun true If rhs is the same type and the value is equal to each other
        virtual bool equals( const Object& rhs );
    private:
        //! override method from base class json::Object
        virtual bool loadFrom( osl::MemoryDataStream& ___IN file );
        virtual void saveTo( osl::MemoryDataStream& ___OUT file ) const;

    };



    struct _null
    {};
    //-------------------------------------------------------------------------
    //-------- JSONNull
    //-------------------------------------------------------------------------
    class _EXPORT_OSLIB JSONNull : public Object 
    {
        H_ALLOC_OBJECT( JSONNull );
    public:
        JSONNull() : Object( OT_NULL ) {}

        using Object::toString;//osl::StringA Object::toString( bool readable = false ) const ;
        virtual bool toString( osl::StringA& ___OUT s, bool readable = false )const;	//!< @copydoc Object::toString(osl::StringA&,bool)
        virtual bool toStringBuf( osl::MemoryDataStream& sb, size_t indent = 0 )const;

        //! \warning This method is quite not effective, so make sure why you need call this method
        //! \note We mostly use this method to do some unit test
        //! \retrun true If rhs is the same type and the value is equal to each other
        virtual bool equals( const Object& rhs );
    private:
        //! override method from base class json::Object
        virtual bool loadFrom( osl::MemoryDataStream& ___IN file );
        virtual void saveTo( osl::MemoryDataStream& ___OUT file ) const;

    };


    //-------------------------------------------------------------------------
    //-------- JSONArray
    //-------------------------------------------------------------------------
    /**
     * A JSONArray is an ordered sequence of values. Its external text form is a
     * string wrapped in square brackets with commas separating the values. The
     * internal form is an object.
     * @author
     * @version 2009-04-13
     */
    class JSONObject;
    class JSONTokener;
    class _EXPORT_OSLIB JSONArray : public Object , public osl::NoCopy
    {
        H_ALLOC_OBJECT( JSONArray );
    public:
        H_DEF_LIST( ObjectPtr, ObjectList );
        typedef ObjectList::iterator        ListIterator;
        typedef ObjectList::const_iterator  ListConstIterator;

        typedef ObjectList::iterator        Iterator;
        typedef ObjectList::const_iterator  ConstIterator;
    public:
        enum{ OBJECT_TYPE = OT_ARRAY };
        /**
         * Construct an empty JSONArray.
         */
        JSONArray() : Object( OT_ARRAY ) {}
        virtual ~JSONArray();

        /**
         * Construct a JSONArray from a source JSON text.
         * @param source     A string that begins with
         * <code>[</code>&nbsp;<small>(left bracket)</small>
         *  and ends with <code>]</code>&nbsp;<small>(right bracket)</small>.
         * @return number of characters parsed. Return 0 if failed to parse.
         ***********************************************************************/
        osl::u32 parse( const osl::StringA& source );

        /**
         * Construct a JSONArray from a source JSON text.
         * @param source     A string that begins with
         * <code>[</code>&nbsp;<small>(left bracket)</small>
         *  and ends with <code>]</code>&nbsp;<small>(right bracket)</small>.
         * @param source_len, the length of the source string.
         *	if you use the default value(-1), we will use strlen(source) to
         *	calculate the length.
         * @return number of characters parsed. Return 0 if failed to parse.
         ***********************************************************************/
        osl::u32 parse( const char* source, const osl::s64 source_len = -1 );

        /**
         * Get the object value associated with an index.
         * @param index
         *  The index must be between 0 and length() - 1.
         * @return An object value.
         *	NULL, If there is no value for the index.
         */
        Object*		 get( int index ) const;
        JSONBoolean* getJSONBoolean( int index ) const;
        JSONDouble*  getJSONDouble( int index ) const;
        JSONInteger* getJSONInteger( int index ) const;
        JSONArray*   getJSONArray( int index ) const;
        JSONObject*  getJSONObject( int index ) const;
        JSONString*  getJSONString( int index ) const;

        bool isNull( int index ) const;


        /**
         * Gets a value
         * @param strKey, the key
         * @param valDefault, the default value.
         * @return the bool value.
         *	or valDefault, If there is no value for the key strKey
         */
        bool getBool( int index, bool valDefault = false )const;
        osl::f64 getDouble( int index, osl::f64 valDefault = 0 )const;
        osl::s64 getInteger( int index, osl::s64 valDefault = 0  )const;
        const osl::StringA getString( int index, const osl::StringA& valDefault = osl::StringUtil::BLANKA )const;

#if H_PROVIDE_UUID
        osl::QUUID  getUUID( int index, const osl::QUUID& valDefault = osl::QUUID::NULL_ID )const;
#endif

        /**
         * Gets an array.
         * @param strKey, the key
         * @param pArray[out] the result is stored
         * @param nCount Size of pArray
         * @param valDefault, the default value of the array element
         * @return true, if found the key strKey
         *	or false, If there is no value for the key strKey
         */
        void  getBoolArray( bool * pArray,     osl::u32 nCount, bool valDefault = false )const;
        void  getByteArray( osl::u8* pArray, osl::u32 nCount, osl::u8 valDefault = 0 )const;
        void  getS32Array( osl::s32* pArray, osl::u32 nCount, osl::s32 valDefault = 0 )const;
        void  getS64Array( osl::s64* pArray, osl::u32 nCount, osl::s64 valDefault = 0 )const;
        void  getF32Array( osl::f32* pArray, osl::u32 nCount, osl::f32 valDefault = 0.0f )const;
        void  getF64Array( osl::f64* pArray, osl::u32 nCount, osl::f64 valDefault = 0.0 )const;
        void  getStringArray( osl::StringA* pArray, osl::u32 nCount, const osl::StringA& valDefault = osl::StringUtil::BLANKA )const;

#if H_PROVIDE_UUID
        void  getUUIDArray( osl::QUUID* pArray, osl::u32 nCount, const osl::QUUID& valDefault = osl::QUUID::NULL_ID )const;
#endif		
        //!
        //! Gets an array.
        //! \remark  Try to find typed value, of can not find,set default value.
        //! \param strKey, the key
        //! \param vArray[out] the result is stored
        void  getBoolArray( osl::Vector<bool>& vArray, bool valDefault = false )const;
        void  getByteArray( osl::Vector<osl::u8>& vArray, osl::u8 valDefault = 0 )const;
        void  getS32Array(  osl::Vector<osl::s32>& vArray, osl::s32 valDefault = 0 )const;
        void  getS64Array(  osl::Vector<osl::s64>& vArray, osl::s64 valDefault = 0 )const;
        void  getF32Array(  osl::Vector<osl::f32>& vArray, osl::f32 valDefault = 0.0f )const;
        void  getF64Array(  osl::Vector<osl::f64>& vArray, osl::f64 valDefault = 0.0 )const;
#if H_PROVIDE_UUID
        void  getUUIDArray( osl::HUUIDVector& vArray, const osl::QUUID& valDefault = osl::QUUID::NULL_ID )const;
#endif
        void  getStringArray( osl::StringAVector& vArray, const osl::StringA& valDefault = osl::StringUtil::BLANKA )const;


        //! Returns whether the JSON object is empty, i.e. whether its size is 0.
        bool empty() const
        {
            return m_list.empty();
        }

        /**
         * Get the number of elements in the JSONArray, included nulls.
         * @return The length (or size).
         */
        size_t size() const
        {
            return m_list.size();
        }

        /**
         * Get the number of elements in the JSONArray, included nulls.
         * @return The length (or size).
         */
        size_t getSize() const
        {
            return size();
        }

        /**
         * Append a boolean value. This increases the array's length by one.
         *
         * @param value A boolean value.
         * @return this.
         */
        JSONArray* put( const bool value );
        JSONArray* put( const osl::f64 value );
        JSONArray* put( const osl::s64 value );
        JSONArray* put( const osl::StringA& s );
        JSONArray* put( const char* s );
        JSONArray* put( Object* value );



        /**
         * Remove a index and close the hole.
         * @param index The index of the element to be removed.
         * @return true if remove the element success
         */
        bool remove( int index ) ;

        /**
         * Make a JSON text of this JSONArray. For compactness, no
         * unnecessary whitespace is added. If it is not possible to produce a
         * syntactically correct JSON text then null will be returned instead. This
         * could occur if the array contains an invalid number.
         * <p>
         * @warning This method assumes that the data structure is acyclical.
         * @override override method from base class json::Object
         * @return a printable, displayable, transmittable
         *  representation of the array.
         */
        using Object::toString;//osl::StringA Object::toString( bool readable = false ) const ;
        virtual bool toString( osl::StringA& ___OUT  s, bool readable = false )const;
        virtual bool toStringBuf( osl::MemoryDataStream& sb, size_t indent = 0 )const;

        //! \warning This method is quite not effective, so make sure why you need call this method
        //! \note We mostly use this method to do some unit test
        //! \retrun true If rhs is the same type and the value is equal to each other
        virtual bool equals( const Object& rhs );


        //!iterator
    public:      

        //! Gets objects in the array.
        //! \remark Caller is responsible for identify the concrete type of object element.
        const ObjectList&  getObjects()const
        {
            return m_list;
        }

        ConstIterator getIterator() const
        {
            return m_list.begin();
        }

        Iterator getIterator()
        {
            return m_list.begin();
        }

        ConstIterator begin() const
        {
            return m_list.begin();
        }

        Iterator begin()
        {
            return m_list.begin();
        }

        ConstIterator end() const
        {
            return m_list.end();
        }

        Iterator end()
        {
            return m_list.end();
        }

    protected:
        friend class JSONTokener;
        friend class JSONObject;

        //!\return number of characters parsed. Return 0 if failed to parse.
        osl::u32 parse( JSONTokener* token );
        JSONArray( JSONTokener* token );

        /**
         * Construct a JSONArray from a source JSON text string.
         * @note Don't use this tow constructors, unless you can make sure
         *	the json text string is valid format. You can you JSONArray()
         *	instead, and use parse(...) method to build a JSON object
         *	from a json text string.
         * @param source    A source json text string
         */
        JSONArray( const osl::StringA& source );
        JSONArray( const char* source );

        template<class T>
            T internal_get_element( int index , const T& valDefault )const;

#if H_PROVIDE_UUID
        osl::QUUID internal_get_element( int index , const osl::QUUID& valDefault )const;
#endif
        template<class T,class U>
            void internal_get( T* , osl::u32 nCount , const U& valDefault )const;

        template<class T,class _ContainerName,class U>
            void internal_get_vector( osl::Vector<T,_ContainerName>& vArray, const U& valDefault )const;

    private:
        //! override method from base class json::Object
        virtual bool loadFrom( osl::MemoryDataStream& ___IN file );
        virtual void saveTo( osl::MemoryDataStream& ___OUT file ) const;

    private:

        ObjectList m_list; //!The list where the JSONArray's properties are kept.
        enum { DEFAULT_BUFFER_SIZE = 512 };

        template<class T>
            T* getTypeObject( int index ) const;
    private:
        ConstIterator getIterator( size_t index ) const;
        Iterator getIterator( size_t index );
    };//end of class


    typedef osl::RefPtr<JSONArray>  JSONArrayPtr;


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    //-------- JSONObject
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    class JSONArray;
    class JSONTokener;
    class _EXPORT_OSLIB JSONObject : public Object , public osl::NoCopy
    {
        H_ALLOC_OBJECT( JSONObject );
    public:
        //typedef osl::HMap< osl::StringA, ObjectPtr > ObjectPtrMap;
        H_DEF_MAP( osl::StringA, ObjectPtr, ObjectPtrMap );
        typedef ObjectPtrMap Map;
        typedef ObjectPtrMap::iterator Iterator;
        typedef ObjectPtrMap::const_iterator ConstIterator;

        typedef std::pair<osl::StringA, Object*>            MapEntry;
        typedef ObjectPtrMap::const_iterator        MapConstIterator;
        typedef ObjectPtrMap::iterator                   MapIterator;

    public:
        enum{ OBJECT_TYPE = OT_OBJECT };
        JSONObject() : Object( OT_OBJECT ) {}

        virtual ~JSONObject();

    public:
        /**
         * Construct a JSONArray from a source JSON text.
         * @param source     A string that begins with
         * <code>[</code>&nbsp;<small>(left bracket)</small>
         *  and ends with <code>]</code>&nbsp;<small>(right bracket)</small>.
         * @return number of characters parsed. Return 0 if failed to parse.
         ***********************************************************************/
        osl::u32 parse( const osl::StringA& source );

        /**
         * Construct a JSONArray from a source JSON text.
         * @param source     A string that begins with
         * <code>[</code>&nbsp;<small>(left bracket)</small>
         *  and ends with <code>]</code>&nbsp;<small>(right bracket)</small>.
         * @param source_len, the length of the source string.
         *	if you use the default value(-1), we will use strlen(source) to
         *	calculate the length.
         * @return number of characters parsed. Return 0 if failed to parse.
         ***********************************************************************/
        osl::u32 parse( const char* source, const osl::s64 source_len = -1 );

        using Object::toString;//osl::StringA Object::toString( bool readable = false ) const ;
        virtual bool toString( osl::StringA& ___OUT s, bool readable = false )const;	//!< @copydoc Object::toString(osl::StringA&,bool)
        virtual bool toStringBuf( osl::MemoryDataStream& sb, size_t indent = 0 )const;

        //! \warning This method is quite not effective, so make sure why you need call this method
        //! \note We mostly use this method to do some unit test
        //! \retrun true If rhs is the same type and the value is equal to each other
        virtual bool equals( const Object& rhs );

        //! Load, Deserialize. load from data stream to convert it to a json object
        _EXPORT_OSLIB friend osl::MemoryDataStream& operator >> ( osl::MemoryDataStream& file, JSONObject& val );

        //! Save, Serialize. save the json object in the data stream
        _EXPORT_OSLIB friend osl::MemoryDataStream& operator << ( osl::MemoryDataStream& ___OUT file, const JSONObject& val );


    public:
        
        //! Returns whether the JSON object is empty, i.e. whether its size is 0.
        bool empty() const;

        //! Returns the number of elements in the this JSON object
        size_t size() const;

        /**
         * Get the object value associated with key value.
         * @param key  the key value
         * @return An object value.
         *	NULL, If there is no value for the index.
         */
        Object*			get(            const osl::StringA& key ) const;
        JSONBoolean*	getJSONBoolean( const osl::StringA& key ) const;
        JSONDouble*		getJSONDouble(  const osl::StringA& key ) const;
        JSONInteger*	getJSONInteger( const osl::StringA& key ) const;
        JSONArray*		getJSONArray(   const osl::StringA& key ) const;
        JSONObject*		getJSONObject(  const osl::StringA& key ) const;
        JSONString*		getJSONString(  const osl::StringA& key ) const;


        /**
         * Gets a value
         * @param strKey, the key
         * @param valDefault, the default value.
         * @return the bool value.
         *	or valDefault, If there is no value for the key strKey
         */
        bool                 getBool(    const osl::StringA& strKey, bool     valDefault = false ) const;
        osl::f64             getDouble(  const osl::StringA& strKey, osl::f64 valDefault = 0.0 )const;
        osl::s64             getInteger( const osl::StringA& strKey, osl::s64 valDefault = 0 )const;
        const osl::StringA&  getString(  const osl::StringA& strKey, const osl::StringA& valDefault = osl::StringUtil::BLANKA )const;

#if H_PROVIDE_UUID
        osl::QUUID  getUUID( const osl::StringA& strKey, const osl::QUUID& valDefault = osl::QUUID::NULL_ID )const;
#endif

        /**
         * Gets an array.
         * @param strKey, the key
         * @param pArray[out] the result is stored
         * @param nCount Size of pArray
         * @param valDefault, the default value of the array element
         * @return true, if found the key strKey
         *	or false, If there is no value for the key strKey
         */
        bool  getBoolArray( const osl::StringA& strKey, bool* ___OUT     pArray, osl::u32 nCount, bool     valDefault = false )const;
        bool  getByteArray( const osl::StringA& strKey, osl::u8* ___OUT  pArray, osl::u32 nCount, osl::u8  valDefault = 0 )const;
        bool  getS32Array(  const osl::StringA& strKey, osl::s32* ___OUT pArray, osl::u32 nCount, osl::s32 valDefault = 0 )const;
        bool  getS64Array(  const osl::StringA& strKey, osl::s64* ___OUT pArray, osl::u32 nCount, osl::s64 valDefault = 0 )const;
        bool  getF32Array(  const osl::StringA& strKey, osl::f32* ___OUT pArray, osl::u32 nCount, osl::f32 valDefault = 0.0f )const;
        bool  getF64Array(  const osl::StringA& strKey, osl::f64* ___OUT pArray, osl::u32 nCount, osl::f64 valDefault = 0.0 )const;
#if H_PROVIDE_UUID
        bool  getUUIDArray( const osl::StringA& strKey, osl::QUUID* ___OUT pArray, osl::u32 nCount, const osl::QUUID& valDefault = osl::QUUID::NULL_ID )const;
#endif
        bool  getStringArray( const osl::StringA& strKey, osl::StringA* ___OUT pArray, osl::u32 nCount, const osl::StringA& valDefault = osl::StringUtil::BLANKA )const;

        /**
         * Gets an array.
         * @param strKey, the key
         * @param vArray[out] the result is stored
         */
        void  getBoolArray( const osl::StringA& strKey, osl::Vector<bool>&     vArray, bool     valDefault = false )const;
        void  getByteArray( const osl::StringA& strKey, osl::Vector<osl::u8 >& vArray, osl::u8  valDefault = 0 )const;
        void  getS32Array(  const osl::StringA& strKey, osl::Vector<osl::s32>& vArray, osl::s32 valDefault = 0 )const;
        void  getS64Array(  const osl::StringA& strKey, osl::Vector<osl::s64>& vArray, osl::s64 valDefault = 0 )const;
        void  getF32Array(  const osl::StringA& strKey, osl::Vector<osl::f32>& vArray, osl::f32 valDefault = 0.0f )const;
        void  getF64Array(  const osl::StringA& strKey, osl::Vector<osl::f64>& vArray, osl::f64 valDefault = 0.0 )const;
#if H_PROVIDE_UUID
        void  getUUIDArray( const osl::StringA& strKey, osl::HUUIDVector& vArray, const osl::QUUID& valDefault = osl::QUUID::NULL_ID )const;
#endif
        void  getStringArray( const osl::StringA& strKey, osl::StringAVector& vArray, const osl::StringA& valDefault = osl::StringUtil::BLANKA )const;

        /**
         *	Put a key/value pair into the JSONObject.
         *	If a item which is associated with key is exist,
         * the old value is deleted, and the new value is inserted.
         *	If the value is null, then the key will be removed
         * from the JSONObject if it is present.
         * @param key   A key string.
         * @param value An object which is the value.
         * @return true, if successfully.
         *		false, if failed.
         */
        bool put( const osl::StringA& key, Object*             value );
        bool put( const osl::StringA& key, const osl::s64      value );
        bool put( const osl::StringA& key, const osl::f64      value );
        bool put( const osl::StringA& key, const bool          value );
        bool put( const osl::StringA& key, const osl::StringA& value );
        bool put( const osl::StringA& key, const char*         value );
#if H_PROVIDE_UUID
        bool put( const osl::StringA& key, const osl::QUUID&   value );
#endif
        /**
         * Put an array to this JSONObject
         * @param key, the key
         * @param value the value array
         * @param nCount Size of pArray
         * @return true, if successfully
         *	or false, if failed
         */
        bool putByteArray(   const osl::StringA& key, const osl::s8* value,      osl::u32 nCount );
        bool putS32Array(    const osl::StringA& key, const osl::s32* value,     osl::u32 nCount );
        bool putS64Array(    const osl::StringA& key, const osl::s64* value,     osl::u32 nCount );
        bool putU32Array(    const osl::StringA& key, const osl::u32* value,     osl::u32 nCount );
        bool putU64Array(    const osl::StringA& key, const osl::u64* value,     osl::u32 nCount );
        bool putF32Array(    const osl::StringA& key, const osl::f32* value,     osl::u32 nCount );
        bool putF64Array(    const osl::StringA& key, const osl::f64* value,     osl::u32 nCount );
        bool putBoolArray(   const osl::StringA& key, const bool* value,         osl::u32 nCount );
        bool putStringArray( const osl::StringA& key, const osl::StringA* value, osl::u32 nCount );
#if H_PROVIDE_UUID
        bool putUUIDArray(   const osl::StringA& key, const osl::QUUID* value,   osl::u32 nCount );
#endif
        /**
         * Remove a key/value pair from this JSONObject.
         * @return true if remove the element success
         */
        bool remove( const osl::StringA& key );
        bool remove( const Object* pobj );

        /**
         * Merge another JSONObject to this JSONObject
         * For example:
         * A : { "keyA1" : "valueA1", "keyA2" : "valueA2", "same key" : "old value" }
         * B : { "keyB1" : "valueB", "same key" : "new value from B" }
         * A.merge(B) ==> A will change to : { "keyA1" : "valueA1", "keyA2" : "valueA2", "keyB1" : "valueB", "same key" : "new value from B" }, 
         *                and B don't change anything.
         * @note If <code>pOtherObject</code> has some same key as this JSONObject, 
         *   this new value from <code>pOtherObject</code> will override the old value 
         *   when <code>override</code> is true; or the value of the key in this 
         *   JSONObject will has no change.
         * @param pOtherObject
         * @param override -  
         * @return true, if successfully
         *	or false, if failed
         */
        bool merge( const JSONObject* pOtherObject, bool override );

        //!iterator
    public:      
        //! Gets object map container.
        const ObjectPtrMap& getObjects() const
        {
            return m_mapObjectPtr;
        }

        //! Gets object map container.
        ObjectPtrMap& getObjects() 
        {
            return m_mapObjectPtr;
        }

        ConstIterator getIterator() const
        {
            return m_mapObjectPtr.begin();
        }

        Iterator getIterator()
        {
            return m_mapObjectPtr.begin();
        }

        ConstIterator begin() const
        {
            return m_mapObjectPtr.begin();
        }

        Iterator begin()
        {
            return m_mapObjectPtr.begin();
        }

        ConstIterator end() const
        {
            return m_mapObjectPtr.end();
        }

        Iterator end()
        {
            return m_mapObjectPtr.end();
        }


    protected:
        /**
         * Construct a JSONObject from a source JSON text string.
         * @note Don't use this tow constructors, unless you can make sure
         *	the json text string is valid format. You can you JSONObject()
         *	instead, and use parse(...) method to build a JSON object
         *	from a json text string.
         * @param source    A string beginning
         *  with <code>{</code>&nbsp;<small>(left brace)</small> and ending
         *  with <code>}</code>&nbsp;<small>(right brace)</small>.
         */
        JSONObject( const osl::StringA& source );
        JSONObject( const char* source );


    protected:
        /**
         * Try to convert a string into a number, boolean, or null. If the string
         * can't be converted, return NULL
         * @note remember to delete the point , which is returned by this function
         * @param s A String.
         * @return A simple JSON value.
         */
        static Object* stringToValue( osl::StringA& s );

        /**
         *	Parses the string argument as a signed integer in the radix specified by the second argument.
         */
        //static osl::s64 stringToInteger( osl::StringA& s, unsigned radix );

        /**
         * Produce a string in osl::f64 quotes with backslash sequences in all the
         * right places. A backslash will be inserted within </, allowing JSON
         * text to be delivered in HTML. In JSON text, a string cannot contain a
         * control character or an unescaped quote or backslash.
         * @param source  A the source String
         * @param rs the produced string by this function
         * @return  true, if success, or false
         */
        static bool quote( const osl::StringA& ___IN source, osl::StringA& ___OUT rs ) ;
        static bool quote( const osl::StringA& ___IN source, osl::MemoryDataStream& ___OUT sb ) ;

        template<class T>
            bool putIntegerArray( const osl::StringA& key, const T* value,     osl::u32 nCount );

        friend class JSONTokener;
        friend class JSONArray;
        friend class JSONString;
        friend class JSONDouble;
        friend class JSONInteger;
        friend class JSONBoolean;
        friend class JSONNull;


        //! Return number of characters parsed.
        osl::u32 parse( JSONTokener* token );

        JSONObject( JSONTokener* token );

    private:

        //! override method from base class json::Object
        virtual bool loadFrom( osl::MemoryDataStream& ___IN file );
        virtual void saveTo( osl::MemoryDataStream& ___OUT file ) const;

    private:
        ObjectPtrMap                                  m_mapObjectPtr;
        enum { DEFAULT_BUFFER_SIZE = 2048 }; //! the default size of the buffer
    };

    typedef osl::RefPtr<JSONObject>	JSONObjectPtr;
    typedef osl::RefPtr<JSONInteger>	JSONIntegerPtr;
    typedef osl::RefPtr<JSONDouble>	JSONDoublePtr;
    typedef osl::RefPtr<JSONArray>	JSONArrayPtr;
    typedef osl::RefPtr<JSONString>	JSONStringPtr;
    typedef osl::RefPtr<JSONBoolean>	JSONBooleanPtr;
    typedef osl::RefPtr<JSONNull>		JSONNullPtr;
    typedef osl::RefPtr<Object>		ObjectPtr;



    //! type cast.
    template<typename _T >
        _T* Json_Cast( json::Object* pObj )
        {
            if ( pObj )
            {
                if ( static_cast<ObjectType>(_T::OBJECT_TYPE ) == pObj->getType() )
                {
                    return static_cast<_T*>( pObj );
                }
            }
            return NULL;
        }

}//end of namespace json


#endif //#if H_PROVIDE_JSON


#endif //#ifndef _OSLIB_JSON_H_


