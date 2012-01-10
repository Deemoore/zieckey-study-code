#include "osl/include/inner_pre.h"

#if H_PROVIDE_JSON

#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"
#include "osl/include/data_stream.h"
#include "osl/include/json.h"
#include "json_tokener.h"


namespace json
{
    

    JSONArray::JSONArray( JSONTokener* token )
        : Object( OT_ARRAY )
    {
        parse( token );
    }

    JSONArray::JSONArray( const osl::StringA& source )
        : Object( OT_ARRAY )
    {
        parse( source );
    }

    JSONArray::JSONArray( const char* source )
        : Object( OT_ARRAY )
    {
        parse( source );
    }

    JSONArray::~JSONArray()
    {
    }

    osl::u32 JSONArray::parse( const osl::StringA& source )
    {
        JSONTokener x( source );
        return parse( &x );
    }

    osl::u32 JSONArray::parse( const char* source, const osl::s64 len )
    {
        JSONTokener x( source, len );
        return parse( &x );
    }

    osl::u32 JSONArray::parse( JSONTokener* x )
    {
		char c = x->nextClean();
		if ( '/' == c )
		{
			if ( !x->skipComment() )
			{
				printf("wrong format of comment");
				return 0;
			}
		}
		else
		{
			x->back();
		}

		c = x->nextClean();
        char q;

        if ( c == '[' )
        {
            q = ']';
        }
        else if ( c == '(' )
        {
            q = ')';
        }
        else
        {
            fprintf( stderr, "A JSONArray text must start with '['" );
            return 0;
        }

		c = x->nextClean();
		if ( '/' == c )
		{
			if ( !x->skipComment() )
			{
				fprintf( stderr, "wrong format of comment");
				return 0;
			}
		}
		else
		{
			x->back();
		}

		c = x->nextClean();
        if ( c == q )
        {
            return x->getCurPos();
        }

        x->back();
        Object* jo = NULL;

        for ( ;; )
        {
			c = x->nextClean();
			if ( '/' == c )
			{
				if ( !x->skipComment() )
				{
					printf("wrong format of comment");
					return 0;
				}
			}
			else
			{
				x->back();
			}

			c = x->nextClean();
            if ( c == ',' )
            {
                x->back();
                m_list.push_back( H_NEW JSONNull() );
            }
            else
            {
                x->back();
                jo = x->nextValue();

                if ( jo )
                {
                    m_list.push_back( jo );
                }
                else
                {
                    return 0;
                }
            }

			c = x->nextClean();
			if ( '/' == c )
			{
				if ( !x->skipComment() )
				{
					printf("wrong format of comment");
					return 0;
				}
			}
			else
			{
				x->back();
			}

			c = x->nextClean();

            switch ( c )
            {
                case ';':
                case ',':
					c = x->nextClean();
					if ( '/' == c )
					{
						if ( !x->skipComment() )
						{
							printf("wrong format of comment");
							return 0;
						}
					}
					else
					{
						x->back();
					}

					c = x->nextClean();
                    if ( c == q )
                    {
                        return x->getCurPos();
                    }

                    x->back();
                    break;
                case ']':
                case ')':

                    if ( q != c )
                    {
                        fprintf( stderr, "Expected a a ')' or ']'" );
                        return 0;
                    }

                    return x->getCurPos();
                default:
                    fprintf( stderr, "Expected a ',' or ']'" );
                    return 0;
            }
        }
    }

    bool JSONArray::toStringBuf( osl::MemoryDataStream& ___OUT sb, size_t indent )const
	{
		osl::StringA indentstr;
		if ( indent > 1 )
		{
			indentstr.assign( indent - 1, '\t' );
			//         for ( size_t i = 1; i < indent; i++ )
			//         {
			//             indentstr += "\t";
			//         }
			sb.write( indentstr.c_str(), indentstr.length() );
		}

        ObjectList::const_iterator it( m_list.begin() ), ite( m_list.end() );
		//sb << '[';
		sb.write( '[' );

        if ( indent > 0 )
        {
            //sb << '\n';
            sb.write( '\n' );
        }

        osl::StringA temp;
        bool needComma = false;

        for ( ; it != ite; it++ )
        {
            if ( needComma )
            {
                sb.write( ',' );
                //sb << ',';

                if ( indent > 0 )
                {
                    sb.write( '\n' );
                    //sb << '\n';
                }
            }
            else
            {
                needComma = true;
            }

            if ( indent > 0 )
            {
                ( *it )->toStringBuf( sb, indent + 1 );
            }
            else
            {
                ( *it )->toStringBuf( sb, 0 );
            }
        }

        //write end close ]
        if ( indent > 0 )
        {
            sb.write( '\n' );
            //sb << '\n';
            sb.write( indentstr.c_str(), indentstr.length() );
        }

        sb.write( ']' );
        //sb << ']';
        return true;
    }

	bool JSONArray::toString( osl::StringA& s, bool readable )const
	{
		osl::MemoryDataStream sb( DEFAULT_BUFFER_SIZE );
		size_t indent = 0;

		if ( readable )
		{
			indent = 1;
		}

		bool ret = toStringBuf( sb, indent );

		if ( ret )
		{
			s = osl::StringA( ( char* )sb.getCache(), sb.getSize() );
			return true;
		}

		return false;
	}


    bool JSONArray::equals( const Object& rhs )
    {
        if ( rhs.getType() != getType() )
        {
            return false;
        }

        const JSONArray& rhsArray = dynamic_cast<const JSONArray&>(rhs);
        if ( rhsArray.size() != size() )
        {
            return false;
        }

        const size_t sz = size();
        bool bAllElementEquals = true;
        for ( size_t i = 0; i < sz; ++i )
        {
            bool bFindEqualOne = false;
            Object* jthis = get( i );
            for ( size_t j = 0; j < sz; ++j )
            {
                //TODO 这里可以优化，上一次比较过的就不需要再次比较了
                if ( jthis->equals( *rhsArray.get(j) ) )
                {
                    bFindEqualOne = true;
                    break;
                }
            }

            if ( bFindEqualOne )
            {
                continue;
            }
            else
            {
                bAllElementEquals = false;
                break;
            }
        } // end of for

        return bAllElementEquals;
    }


    bool JSONArray::remove( int index )
    {
        ListIterator it = getIterator( index );

        if ( it == m_list.end() )
        {
            return false;
        }

        m_list.erase( it );
        return true;
    }

    Object* JSONArray::get( int index ) const
    {
        ListConstIterator it = getIterator( index );

        if ( it != m_list.end() )
        {
            return ( *it );
        }

        return NULL;
    }

    template<class T>
    T* JSONArray::getTypeObject( int index ) const
    {
        Object* pObject = get( index );

        if( pObject )
        {
            return dynamic_cast<T*>( pObject );
        }
        else
        {
            return NULL;
        }
    }


    JSONBoolean* JSONArray::getJSONBoolean( int index ) const
    {
        return getTypeObject<JSONBoolean>( index );
    }

    JSONDouble*  JSONArray::getJSONDouble( int index ) const
    {
        return getTypeObject<JSONDouble>( index );
    }

    JSONInteger* JSONArray::getJSONInteger( int index ) const
    {
        return getTypeObject<JSONInteger>( index );
    }

    JSONArray*   JSONArray::getJSONArray( int index ) const
    {
        return getTypeObject<JSONArray>( index );
    }

    JSONObject*  JSONArray::getJSONObject( int index ) const
    {
        return getTypeObject<JSONObject>( index );
    }

    JSONString*  JSONArray::getJSONString( int index ) const
    {
        return getTypeObject<JSONString>( index );
    }


    bool JSONArray::isNull( int index ) const
    {
        ListConstIterator it = getIterator( index );

        if ( it == m_list.end() )
        {
            return true;
        }

        return dynamic_cast<JSONNull*>( ( *it ).getPointer() ) ? true : false;
    }


    JSONArray* JSONArray::put( const bool value )
    {
        m_list.push_back( H_NEW JSONBoolean( value ) );
        return this;
    }

    JSONArray* JSONArray::put( const osl::f64 value )
    {
        m_list.push_back( H_NEW JSONDouble( value ) );
        return this;
    }

    JSONArray* JSONArray::put( const osl::s64 value )
    {
        m_list.push_back( H_NEW JSONInteger( value ) );
        return this;
    }

    JSONArray* JSONArray::put( const char* value )
    {
        m_list.push_back( H_NEW JSONString( value ) );
        return this;
    }

    JSONArray* JSONArray::put( const osl::StringA& value )
    {
        return put( value.c_str() );
    }

    JSONArray* JSONArray::put( Object* value )
    {
        if ( value )
        {
            m_list.push_back( value );
        }

        return this;
    }


	template<class T>
	T JSONArray::internal_get_element( int index , const T& valDefault )const
	{
		typedef typename TypeToJsonType<T>::type JsonType;

		Object* pObject = get( index );
		if (  pObject )
		{
			JsonType* pJsonObject = Json_Cast<JsonType>( pObject );
		
			if ( pJsonObject  )
			{
				return pJsonObject->getRealValue();
			}
		}

		return valDefault;
	}

#if H_PROVIDE_UUID
	osl::QUUID JSONArray::internal_get_element( int index , const osl::QUUID& valDefault )const
	{
		const osl::StringA& strVal = getString( index );
		if ( ! strVal.empty() )
		{
			osl::QUUID idRet;
			idRet.generateFromStringA( strVal );
			return idRet;
		}

		return valDefault;
	}
#endif // #if H_PROVIDE_UUID

    //------------------------------------------------------
    bool JSONArray::getBool( int index, bool valDefault )const
    {
		return internal_get_element( index , valDefault );
    }


    //------------------------------------------------------
    osl::f64 JSONArray::getDouble( int index, osl::f64 valDefault )const
    {
		return internal_get_element( index , valDefault );
    }


    //------------------------------------------------------
    osl::s64 JSONArray::getInteger( int index, osl::s64 valDefault )const
    {
		return internal_get_element( index , valDefault );
    }


    //------------------------------------------------------
    const osl::StringA JSONArray::getString( int index, const osl::StringA& valDefault )const
    {
		return internal_get_element( index , valDefault );
    }


#if H_PROVIDE_UUID
    //------------------------------------------------------
    osl::QUUID  JSONArray::getUUID( int index, const osl::QUUID& valDefault )const
    {
        return internal_get_element( index , valDefault );
    }
#endif // #if H_PROVIDE_UUID

	template<class T,class U>
	void JSONArray::internal_get( T* pArray , osl::u32 nCount , const U& valDefault )const
	{
		for ( osl::u32 i = 0; i < nCount; ++ i )
		{
			pArray[i] = static_cast<T>( internal_get_element( static_cast<int>(i), valDefault ) );
		}
	}

    //------------------------------------------------------
    void  JSONArray::getBoolArray( bool* pArray, osl::u32 nCount, bool valDefault )const
    {
		internal_get( pArray , nCount , valDefault );
    }
    //------------------------------------------------------
    void  JSONArray::getByteArray( osl::u8* pArray, osl::u32 nCount, osl::u8 valDefault )const
    {
        internal_get( pArray , nCount , static_cast<osl::s64>( valDefault ) );
    }


    //------------------------------------------------------
    void  JSONArray::getS32Array( osl::s32* pArray, osl::u32 nCount, osl::s32 valDefault )const
    {
		internal_get( pArray , nCount , static_cast<osl::s64>( valDefault ) );
    }


    //------------------------------------------------------
    void  JSONArray::getS64Array( osl::s64* pArray, osl::u32 nCount, osl::s64 valDefault )const
    {
		internal_get( pArray , nCount , static_cast<osl::s64>( valDefault ) );
    }


    //------------------------------------------------------
    void  JSONArray::getF32Array( osl::f32* pArray, osl::u32 nCount, osl::f32 valDefault )const
    {
		internal_get( pArray , nCount , static_cast<osl::f64>( valDefault ) );
    }

    //------------------------------------------------------
    void  JSONArray::getF64Array( osl::f64* pArray, osl::u32 nCount, osl::f64 valDefault )const
    {
		internal_get( pArray , nCount , static_cast<osl::f64>( valDefault ) );
    }

#if H_PROVIDE_UUID
    //------------------------------------------------------
    void  JSONArray::getUUIDArray( osl::QUUID* pArray, osl::u32 nCount, const osl::QUUID& valDefault )const
    {
		internal_get( pArray , nCount , valDefault );
    }
#endif // #if H_PROVIDE_UUID

    //------------------------------------------------------
    void  JSONArray::getStringArray( osl::StringA* pArray, osl::u32 nCount, const osl::StringA& valDefault )const
    {
        internal_get( pArray , nCount , valDefault );
    }

	template<class T,class _ContainerName,class U>
	void JSONArray::internal_get_vector( osl::Vector<T,_ContainerName>& vArray, const U& valDefault )const
	{
		size_t nCount = m_list.size();
		vArray.resize( nCount );
		T* pArray = &vArray[0];
		internal_get( pArray , nCount , valDefault );
	}

    //---------------------------------------------------------------------------
    void  JSONArray::getBoolArray( osl::Vector<bool>& vArray, bool valDefault )const
    {
		//由于vector<bool>是个特化版本,所以要特别处理一下.
		size_t nCount = m_list.size();
		vArray.resize( nCount );

		osl::ScopedMem scopeMem( new bool[nCount] );
		bool* pArray = scopeMem.getPointer<bool>();

		internal_get( pArray , nCount , valDefault  );
		std::copy( pArray , pArray + nCount , vArray.begin() );
    }
    //---------------------------------------------------------------------------
    void  JSONArray::getByteArray( osl::Vector<osl::u8>& vArray, osl::u8 valDefault )const
    {
		internal_get_vector( vArray , static_cast<osl::s64>( valDefault ) );
    }
    //---------------------------------------------------------------------------
    void  JSONArray::getS32Array( osl::Vector<osl::s32>& vArray, osl::s32 valDefault )const
    {
		internal_get_vector( vArray , static_cast<osl::s64>( valDefault ) );
    }
    //---------------------------------------------------------------------------
    void  JSONArray::getS64Array(  osl::Vector<osl::s64>& vArray, osl::s64 valDefault )const
    {
		internal_get_vector( vArray , static_cast<osl::s64>( valDefault ) );
    }
    //---------------------------------------------------------------------------
    void  JSONArray::getF32Array(  osl::Vector<osl::f32>& vArray, osl::f32 valDefault )const
    {
        internal_get_vector( vArray , static_cast<osl::f64>( valDefault ) );
    }
    //---------------------------------------------------------------------------
    void  JSONArray::getF64Array( osl::Vector<osl::f64>& vArray, osl::f64 valDefault )const
    {
        internal_get_vector( vArray , static_cast<osl::f64>( valDefault ) );
    }
#if H_PROVIDE_UUID
    //---------------------------------------------------------------------------
    void  JSONArray::getUUIDArray( osl::HUUIDVector& vArray, const osl::QUUID& valDefault )const
    {
        internal_get_vector( vArray , valDefault );
    }
#endif // #if H_PROVIDE_UUID

    //---------------------------------------------------------------------------
    void  JSONArray::getStringArray( osl::StringAVector& vArray, const osl::StringA& valDefault )const
    {
        internal_get_vector( vArray , valDefault );
    }


    JSONArray::ListConstIterator JSONArray::getIterator( size_t index ) const
    {
        if ( index > m_list.size() )
        {
            return m_list.end();
        }

        ListConstIterator it = m_list.begin();

        advance( it , index );//        for ( size_t i = 0; i < index; i++ ) it++;

        return it;
    }

    JSONArray::ListIterator JSONArray::getIterator( size_t index )
    {
        if ( index > m_list.size() )
        {
            return m_list.end();
        }

        ListIterator it = m_list.begin();

        advance( it , index );//        for ( size_t i = 0; i < index; i++ ) it++;

        return it;
    }

    //------------------------------------------------------------
    void JSONArray::saveTo( osl::MemoryDataStream& ___OUT file ) const
    {
        osl::u32 nSize = ( osl::u32 )this->size();
        file << ( osl::u8 )getType()      //type
             << ( osl::u32 )nSize;              //size

        for ( osl::u32 i = 0; i < nSize; i++ )
        {
            get( i )->saveTo( file );
        }
    }
    //------------------------------------------------------------
    bool JSONArray::loadFrom( osl::MemoryDataStream& ___IN file )
    {
        osl::u32 nSize = 0;
        file >> nSize;
        Object* pObject = NULL;

        for ( osl::u32 i = 0; i < nSize; i++ )
        {
            Object::deserializeOneObject( file, pObject );

            if ( pObject )
            {
                //file >> *pObject;
                //pObject->loadFrom( file );
                put( pObject );
                pObject = NULL;
            }
        }

        return true;
    }

}//end of namespace json


#endif //#if H_PROVIDE_JSON


