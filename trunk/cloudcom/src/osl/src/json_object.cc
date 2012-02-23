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


    //-------------------------------------------------------------------------
    //----------- JSONObject
    //-------------------------------------------------------------------------

    

	osl::StringA Object::toString( bool readable ) const
	{
		osl::StringA  retVal;
		if( this->toString( retVal , readable ) )
		{
			return retVal;
		}
		else
		{
			return osl::StringUtil::BLANKA;
		}
	}

// 	bool Object::toString( osl::MemoryDataStream& ___OUT sb, size_t indent /*= 0 */ ) const
// 	{
// 		osl::StringA str = toString( indent > 0 ? true : false );
// 		if( str.empty() )
// 		{
// 		}
// 		else
// 		{
// 			for ( size_t i = 1; i < indent; i++ )
// 			{
// 				sb.write( '\t' );
// 			}
// 			sb.write( str.c_str() , str.length() );
// 		}
// 		return true;
// 	}

    

    JSONObject::JSONObject( const osl::StringA& source )
        : Object( OT_OBJECT )
    {
        parse( source );
    }

    JSONObject::JSONObject( const char* source )
        : Object( OT_OBJECT )
    {
        parse( source );
    }

    JSONObject::JSONObject( JSONTokener* token )
        : Object( OT_OBJECT )
    {
        parse( token );
    }

    JSONObject::~JSONObject()
    {
    }

    osl::u32 JSONObject::parse( JSONTokener* x )
    {
        osl::StringA key( "" );
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
        if ( c != '{' )
        {
            //printf("A JSONObject text must begin with '{'\n");
            return 0;
        }

        //bool isOK = false;

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
            switch ( c )
            {
                case 0:
                    printf( "A JSONObject text must end with '}'" );
                    return 0;
                case '}':
                    return x->getCurPos();
                case '"':	// a key must be a string
                    if ( !x->nextString( '"', key ) )
                    {
                        return x->getCurPos();
                    }
                    break;
                default:
                    /*x->back();
                    po = x->nextValue();*/
                    return 0;
            }

            /*
            * The key is followed by ':'. We will also tolerate '=' or '=>'.
            */
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

            if ( c == '=' )
            {
                if ( x->next() != '>' )
                {
                    x->back();
                }
            }
            else if ( c != ':' )
            {
                return 0;
            }

            Object* po = x->nextValue();

            if ( po )
            {
                put( key, po );
            }
            else
            {
                return 0;
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

            /*
            * Pairs are separated by ','. We will also tolerate ';'.
            */
            switch ( c )
            {
                case ',':
                case ';':
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
                    if ( c == '}' )
                    {
                        return x->getCurPos();//ok, we have parsed done here
                    }

                    x->back();
                    break;
                case '}':
                    return x->getCurPos();
                default:
                    return 0;
            }
        } // end of for ( ;; )

        //return x->getCurPos();
    }

    osl::u32 JSONObject::parse( const char* source, const osl::s64 source_len )
    {
        if ( source_len == 0 )
        {
            return 0;
        }

        //assert( source && source_len );

        json::JSONTokener x( source, source_len );

        return parse( &x );
    }

    osl::u32 JSONObject::parse( const osl::StringA& source )
    {
        json::JSONTokener x( source );

        return parse( &x );
    }


    bool JSONObject::empty() const
    {
        return m_mapObjectPtr.empty();
    }

    size_t JSONObject::size() const
    {
        return m_mapObjectPtr.size();
    }

    bool JSONObject::put( const osl::StringA& key, Object* value )
    {
        if ( !value )
        {
            m_mapObjectPtr.erase( key );
            return true;
        }

// 		TCHAR sz[16]={0};
// 		_sntprintf( sz,15 , _T("%x\n") , GetCurrentThreadId() );
// 		OutputDebugString( sz );


//         ObjectPtr& pv = m_map[key];
//
//         if ( !pv )
//         {
//             pv = value;
//         }
//         else
//         {
//             pv = value;
//         }

        m_mapObjectPtr[key] = value;
        return true;

    }

    bool JSONObject::put( const osl::StringA& key, const osl::s64 value )
    {
        JSONInteger* jo = H_NEW JSONInteger( value );
        return put( key, jo );
    }

    bool JSONObject::put( const osl::StringA& key, const osl::f64 value )
    {
        JSONDouble* jo = H_NEW JSONDouble( value );
        return put( key, jo );
    }

    bool JSONObject::put( const osl::StringA& key, const bool value )
    {
        JSONBoolean* jo = H_NEW JSONBoolean( value );
        return put( key, jo );
    }

    bool JSONObject::put( const osl::StringA& key, const osl::StringA& value )
    {
        return put( key, value.c_str() );
    }

    bool JSONObject::put( const osl::StringA& key, const char* value )
    {
        JSONString* jo = H_NEW JSONString( value );
        return put( key, jo );
    }

    Object* JSONObject::stringToValue( osl::StringA& s )
    {
        osl::StringUtil::toLowerCase( s );

        if ( s == "" || s == "null" )
        {
            return H_NEW JSONNull();
        }
        else if ( s == "true" )
        {
            return H_NEW JSONBoolean( true );
        }
        else if ( s == "false" )
        {
            return H_NEW JSONBoolean( false );
        }

        /*
        * If it might be a number, try converting it. We support the 0- and 0x-
        * conventions. If a number cannot be produced, then the value will just
        * be a string. Note that the 0-, 0x-, plus, and implied string
        * conventions are non-standard. A JSON parser is free to accept
        * non-JSON forms as long as it accepts all correct JSON forms.
        */
        char b = s.at( 0 );

        if ( b != '.' && b != '-' && b != '+' && ( b < '0' || b > '9' ) )
        {
            return NULL;
        }

        //if ( ( b >= '0' && b <= '9' ) || b == '.' || b == '-' || b == '+' )

        /* a normal number string */
        if ( b != '0' )
        {
            if ( osl::StringUtil::isFloatNumber( s ) )
            {
                return H_NEW JSONDouble( atof( s.c_str() ) );
            }
            else
            {
                return H_NEW JSONInteger( atoll( s.c_str() ) );
            }
        }

        /* hexadecimal number */
        if ( s.length() > 2 && ( s.at( 1 ) == 'x' || s.at( 1 ) == 'X' ) )
        {
            osl::s64 result = 0;
            int curval = 0;

            for ( size_t i = 2; i < s.length(); i++ )
            {
                curval = JSONTokener::dehexchar( s[i] );

                if ( curval != -1 )
                {
                    result = result * 16 + curval;
                }
                else
                {
                    printf( "Not a valid hexadecimal character : %c\n", s[i] );
                    return NULL;
                }
            }

            return H_NEW JSONInteger( result );
        }
        else
        {
            /* it is a float string */
            if ( osl::StringUtil::isFloatNumber( s ) )
            {
                return H_NEW JSONDouble( atof( s.c_str() ) );
            }
            else
            {
                /* it is a octal number string */
                osl::s64 result = 0;
                int curval = 0;

                for ( size_t i = 1; i < s.length(); i++ )
                {
                    curval = JSONTokener::dehexchar( s[i] );

                    if ( curval != -1 )
                    {
                        result = result * 8 + curval;
                    }
                    else
                    {
                        printf( "Not a valid octal character : %c\n", s[i] );
                        return NULL;
                    }
                }

                return H_NEW JSONInteger( result );
            }
        }
    }

    bool JSONObject::quote( const osl::StringA& ___IN source, osl::StringA& ___OUT rs )
    {
        if ( source.length() == 0 )
        {
            rs = "\"\"";
            return true;
        }

        int len = source.length();
        osl::MemoryDataStream sb( len + 16 );//prepare data buffer, with more 16 bytes.
        bool ret = quote( source, sb );

        if ( ret )
        {
            rs = osl::StringA( ( char* )sb.getCache(), sb.getSize() );
            return true;
        }

        return false;
    }

    bool JSONObject::quote( const osl::StringA& ___IN source, osl::MemoryDataStream& ___OUT sb )
    {
        if ( source.length() == 0 )
        {
            sb.write( "\"\"", 2 );
            return true;
        }

        char         b;
        char         c = 0;
        int          i;
        int          len = source.length();
        //osl::StringA       t;

        sb.write( '"' );

        for ( i = 0; i < len; i += 1 )
        {
            b = c;
            c = source[i];

            switch ( c )
            {
                case '\\':
                case '"':
                    sb.write( '\\' );
                    sb.write( c );

                    break;
                case '/':

                    if ( b == '<' )
                    {
                        sb.write( '\\' );
                    }

                    sb.write( c );
                    break;
                case '\b':
                    sb.write( "\\b", 2 );
                    break;
                case '\t':
                    sb.write( "\\t", 2 );
                    break;
                case '\n':
                	sb.write( "\\n", 2 );
                	break;
                case '\r':
                	sb.write( "\\r", 2 );
                	break;
                case '\f':
                    sb.write( "\\f", 2 );
                    break;
                default:
                    //if (c < ' ' || (c >= '\u0080' && c < '\u00a0') ||
                    //	(c >= '\u2000' && c < '\u2100'))
                    //{
                    //		//TODO xxx
                    //		/*t = "000" + Integer.toHexString(c);
                    //		sb.write("\\u" + t.substring(t.length() - 4));*/
                    //} else {
                    //	sb.write(c);
                    //}
                    sb.write( c );
            }
        }

        sb.write( '"' );
        return true;
    }

    //osl::s64 JSONObject::stringToInteger( osl::StringA& s, unsigned int radix )
    //{
    //		return 0;
    //}

    Object*	JSONObject::get( const osl::StringA& key )const
    {
        MapConstIterator it = m_mapObjectPtr.find( key );

        if ( it != m_mapObjectPtr.end() )
        {
            return ( it->second );
        }

        return NULL;
    }

    JSONBoolean* JSONObject::getJSONBoolean( const osl::StringA& key )const
    {
        MapConstIterator it = m_mapObjectPtr.find( key );

        if ( it != m_mapObjectPtr.end() )
        {
            return dynamic_cast<JSONBoolean*>( ( it->second ).getPointer() );
            //return Json_Cast<JSONBoolean>(it->second);
        }

        return NULL;
    }

    JSONDouble*	JSONObject::getJSONDouble( const osl::StringA& key )const
    {
        MapConstIterator it = m_mapObjectPtr.find( key );

        if ( it != m_mapObjectPtr.end() )
        {
            return dynamic_cast<JSONDouble*>( ( it->second ).getPointer() );
            //return Json_Cast<JSONDouble>(it->second);
        }

        return NULL;
    }

    JSONInteger*	JSONObject::getJSONInteger( const osl::StringA& key )const
    {
        MapConstIterator it = m_mapObjectPtr.find( key );

        if ( it != m_mapObjectPtr.end() )
        {
            return dynamic_cast<JSONInteger*>( ( it->second ).getPointer() );
            //return Json_Cast<JSONInteger>(it->second);
        }

        return NULL;
    }

    JSONArray*		JSONObject::getJSONArray( const osl::StringA& key )const
    {
        MapConstIterator it = m_mapObjectPtr.find( key );

        if ( it != m_mapObjectPtr.end() )
        {
            return dynamic_cast<JSONArray*>( ( it->second ).getPointer() );
            //return Json_Cast<JSONArray>(it->second);
        }

        return NULL;
    }

    JSONObject*	JSONObject::getJSONObject( const osl::StringA& key )const
    {
        MapConstIterator it = m_mapObjectPtr.find( key );

        if ( it != m_mapObjectPtr.end() )
        {
            return dynamic_cast<JSONObject*>( ( it->second ).getPointer() );
            //return Json_Cast< JSONObject>(it->second);
        }

        return NULL;
    }

    JSONString*	JSONObject::getJSONString( const osl::StringA& key )const
    {
        MapConstIterator it = m_mapObjectPtr.find( key );

        if ( it != m_mapObjectPtr.end() )
        {
            return dynamic_cast<JSONString*>( ( it->second ).getPointer() );
            //return Json_Cast<JSONString>(it->second);
        }

        return NULL;
    }



    bool JSONObject::toString( osl::StringA& s, bool readable ) const
    {
        
        size_t indent = 0;

        if ( readable )
        {
            indent = 1;
        }

		osl::MemoryDataStream sb( DEFAULT_BUFFER_SIZE );
        bool ret = toStringBuf( sb, indent );

        if ( ret )
        {
            s = osl::StringA( ( char* )sb.getCache(), sb.getSize() );
            return true;
        }

        return false;
    }

    bool JSONObject::toStringBuf( osl::MemoryDataStream& sb, size_t indent ) const
    {
		//write begin
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

        sb.write( '{' );

        if ( indent > 0 )
        {
            sb.write( '\n' );
        }

        MapConstIterator it( m_mapObjectPtr.begin() ), ite( m_mapObjectPtr.end() );
        bool needComma = false;

        for ( ; it != ite; it++ )
        {
            if ( needComma )
            {
                sb.write( ',' );

                if ( indent > 0 )
                {
                    sb.write( '\n' );
                }
            }
            else
            {
                needComma = true;
            }

            //write key
            if ( indent > 0 )
            {
                sb.write( indentstr.c_str(), indentstr.length() );
                sb.write( '\t' ); //indent one more level
                JSONObject::quote( it->first, sb );
            }
            else
            {
                JSONObject::quote( it->first, sb );
            }

            //write value
            sb.write( ':' );

            if ( indent > 0 )
            {
                switch ( it->second->getType() )
                {
                    case OT_OBJECT:
                    case OT_ARRAY:
                        sb.write( '\n' );
                        it->second->toStringBuf( sb, indent + 1 );
                        break;
                    default:
                        it->second->toStringBuf( sb, 0 );
                }

            }
            else
            {
                it->second->toStringBuf( sb, 0 );
            }
        }

        //write end close }
        if ( indent > 0 )
        {
            sb.write( '\n' );
            sb.write( indentstr.c_str(), indentstr.length() );
        }

        sb.write( '}' );
        return true;
    }


    //---------------------------------------------------------------------------
    bool JSONObject::getBool( const osl::StringA& strKey, bool valDefault )const
    {
        JSONBoolean* pVal =	getJSONBoolean( strKey );

        if ( pVal )
        {
            return pVal->getRealValue();
        }

        return valDefault;
    }

    //---------------------------------------------------------------------------
    osl::f64 JSONObject::getDouble( const osl::StringA& strKey, osl::f64 valDefault )const
    {
        JSONDouble* pVal =	getJSONDouble( strKey );

        if ( pVal )
        {
            return pVal->getRealValue();
        }

        return valDefault;
    }


    //---------------------------------------------------------------------------
    osl::s64 JSONObject::getInteger( const osl::StringA& strKey, osl::s64 valDefault )const
    {
        JSONInteger* pVal =	getJSONInteger( strKey );

        if ( pVal )
        {
            return pVal->getRealValue();
        }

        return valDefault;
    }

    //---------------------------------------------------------------------------
    const osl::StringA&  JSONObject::getString( const osl::StringA& strKey, const osl::StringA& valDefault )const
    {
        JSONString* pVal =	getJSONString( strKey );

        if ( pVal )
        {
            return pVal->getRealValue();
        }

        return valDefault;
    }


#if H_PROVIDE_UUID
    //---------------------------------------------------------------------------
    osl::QUUID  JSONObject::getUUID( const osl::StringA& strKey, const osl::QUUID& valDefault )const
    {
        JSONString* pVal =	getJSONString( strKey );

        if ( pVal )
        {
            osl::QUUID idRet;
            idRet.generateFromStringA( pVal->getRealValue() );
            return idRet;
        }

        return valDefault;
    }
#endif // #if H_PROVIDE_UUID


    //---------------------------------------------------------------------------
    bool  JSONObject::getBoolArray( const osl::StringA& strKey, bool* pArray, osl::u32 nCount, bool valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            for ( osl::u32 i = 0; i < nCount; ++ i )
            {
                pArray[i] = pVal->getBool( i, valDefault );
            }

            return true;
        }

        return false;
    }


    //---------------------------------------------------------------------------
    bool  JSONObject::getByteArray( const osl::StringA& strKey, osl::u8* pArray, osl::u32 nCount, osl::u8 valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            for ( osl::u32 i = 0; i < nCount; ++ i )
            {
                pArray[i] = ( osl::u8 )pVal->getInteger( i, valDefault );
            }

            return true;
        }

        return false;
    }

    //---------------------------------------------------------------------------
    bool  JSONObject::getS32Array( const osl::StringA& strKey, osl::s32* pArray, osl::u32 nCount, osl::s32 valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            for ( osl::u32 i = 0; i < nCount; ++ i )
            {
                pArray[i] = ( osl::s32 )pVal->getInteger( i, valDefault );
            }

            return true;
        }

        return false;
    }

    //---------------------------------------------------------------------------
    bool  JSONObject::getS64Array( const osl::StringA& strKey, osl::s64* pArray, osl::u32 nCount, osl::s64 valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            for ( osl::u32 i = 0; i < nCount; ++ i )
            {
                pArray[i] = ( osl::s64 )pVal->getInteger( i, valDefault );
            }

            return true;
        }

        return false;
    }

    //---------------------------------------------------------------------------
    bool  JSONObject::getF32Array( const osl::StringA& strKey, osl::f32* pArray, osl::u32 nCount, osl::f32 valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            for ( osl::u32 i = 0; i < nCount; ++ i )
            {
                pArray[i] = ( osl::f32 )pVal->getDouble( i, valDefault );
            }

            return true;
        }

        return false;
    }

    //---------------------------------------------------------------------------
    bool  JSONObject::getF64Array( const osl::StringA& strKey, osl::f64* pArray, osl::u32 nCount, osl::f64 valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            for ( osl::u32 i = 0; i < nCount; ++ i )
            {
                pArray[i] = ( osl::f64 )pVal->getDouble( i, valDefault );
            }

            return true;
        }

        return false;
    }


#if H_PROVIDE_UUID
    //---------------------------------------------------------------------------
    bool  JSONObject::getUUIDArray( const osl::StringA& strKey, osl::QUUID* pArray, osl::u32 nCount, const osl::QUUID& valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            for ( osl::u32 i = 0; i < nCount; ++ i )
            {
                JSONString* pEleVal = pVal->getJSONString( i );

                if ( pEleVal )
                {
                    pArray[i].generateFromStringA( pEleVal->getRealValue() );
                }
                else
                {
                    pArray[i] = valDefault;
                }
            }

            return true;
        }

        return false;
    }
#endif // #if H_PROVIDE_UUID

    //---------------------------------------------------------------------------
    bool  JSONObject::getStringArray( const osl::StringA& strKey, osl::StringA* pArray, osl::u32 nCount, const osl::StringA& valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            for ( osl::u32 i = 0; i < nCount; ++ i )
            {
                pArray[i] = pVal->getString( i, osl::StringUtil::BLANKA );
            }

            return true;
        }

        return false;
    }
    //---------------------------------------------------------------------------
    void  JSONObject::getBoolArray( const osl::StringA& strKey, osl::Vector<bool>& vArray, bool valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            pVal->getBoolArray( vArray, valDefault );
        }
    }
    //---------------------------------------------------------------------------
    void  JSONObject::getByteArray( const osl::StringA& strKey, osl::Vector<osl::u8>& vArray, osl::u8 valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            pVal->getByteArray( vArray, valDefault );
        }
    }
    //---------------------------------------------------------------------------
    void  JSONObject::getS32Array(  const osl::StringA& strKey, osl::Vector<osl::s32>& vArray, osl::s32 valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            pVal->getS32Array( vArray, valDefault );
        }
    }
    //---------------------------------------------------------------------------
    void  JSONObject::getS64Array(  const osl::StringA& strKey, osl::Vector<osl::s64>& vArray, osl::s64 valDefault  )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            pVal->getS64Array( vArray, valDefault );
        }
    }
    //---------------------------------------------------------------------------
    void  JSONObject::getF32Array(  const osl::StringA& strKey, osl::Vector<osl::f32>& vArray, osl::f32 valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            pVal->getF32Array( vArray, valDefault );
        }
    }
    //---------------------------------------------------------------------------
    void  JSONObject::getF64Array(  const osl::StringA& strKey, osl::Vector<osl::f64>& vArray , osl::f64 valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            pVal->getF64Array( vArray, valDefault );
        }
    }

#if H_PROVIDE_UUID
    //---------------------------------------------------------------------------
    void  JSONObject::getUUIDArray( const osl::StringA& strKey, osl::QUUIDVector& vArray, const osl::QUUID& valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            pVal->getUUIDArray( vArray, valDefault );
        }
    }
#endif // #if H_PROVIDE_UUID
    //---------------------------------------------------------------------------
    void  JSONObject::getStringArray( const osl::StringA& strKey, osl::StringAVector& vArray, const osl::StringA& valDefault )const
    {
        JSONArray* pVal = getJSONArray( strKey );

        if ( pVal )
        {
            pVal->getStringArray( vArray, valDefault );
        }
    }
#if H_PROVIDE_UUID
    //---------------------------------------------------------------------------
    bool JSONObject::put( const osl::StringA& key, const osl::QUUID& value )
    {
        JSONString* jo = H_NEW JSONString( value.toStringA() );
        return put( key, jo );
    }
#endif // #if H_PROVIDE_UUID


    template<class T>
    bool JSONObject::putIntegerArray( const osl::StringA& key, const T* value, osl::u32 nCount )
    {
        JSONArray* pArray = H_NEW JSONArray();

        for ( osl::u32 i = 0; i < nCount; ++i )
        {
            pArray->put( H_NEW JSONInteger( static_cast<osl::s64>( value[i] ) ) );
        }

        return put( key, pArray );
    }

    //////////////////////////////////////////////////////////////////////////
    //! Following methods put array objects.
    bool JSONObject::putByteArray( const osl::StringA& key, const osl::s8* value, osl::u32 nCount )
    {
        return putIntegerArray<osl::s8>( key, value, nCount );
    }

    //---------------------------------------------------------------------------
    bool JSONObject::putS32Array( const osl::StringA& key, const osl::s32* value, osl::u32 nCount )
    {
        return putIntegerArray<osl::s32>( key, value, nCount );
    }

    //---------------------------------------------------------------------------
    bool JSONObject::putS64Array( const osl::StringA& key, const osl::s64* value, osl::u32 nCount )
    {
        return putIntegerArray<osl::s64>( key, value, nCount );
    }

    bool JSONObject::putU32Array( const osl::StringA& key, const osl::u32* value, osl::u32 nCount )
    {
        return putIntegerArray<osl::u32>( key, value, nCount );
    }
    bool JSONObject::putU64Array( const osl::StringA& key, const osl::u64* value, osl::u32 nCount )
    {
        return putIntegerArray<osl::u64>( key, value, nCount );
    }







    //---------------------------------------------------------------------------
    bool JSONObject::putF32Array( const osl::StringA& key, const osl::f32* value, osl::u32 nCount )
    {
        JSONArray* pArray = H_NEW JSONArray();

        for ( osl::u32 i = 0; i < nCount; ++i )
        {
            pArray->put( H_NEW JSONDouble( osl::f64( value[i] ) ) );
        }

        return put( key, pArray );
    }

    //---------------------------------------------------------------------------
    bool JSONObject::putF64Array( const osl::StringA& key, const osl::f64* value, osl::u32 nCount )
    {
        JSONArray* pArray = H_NEW JSONArray();

        for ( osl::u32 i = 0; i < nCount; ++i )
        {
            pArray->put( H_NEW JSONDouble( osl::f64( value[i] ) ) );
        }

        return put( key, pArray );
    }

    //---------------------------------------------------------------------------
    bool JSONObject::putBoolArray( const osl::StringA& key, const bool* value, osl::u32 nCount )
    {
        JSONArray* pArray = H_NEW JSONArray();

        for ( osl::u32 i = 0; i < nCount; ++i )
        {
            pArray->put( H_NEW JSONBoolean( value[i] ) );
        }

        return put( key, pArray );
    }

    //---------------------------------------------------------------------------
    bool JSONObject::putStringArray( const osl::StringA& key, const osl::StringA* value, osl::u32 nCount )
    {
        JSONArray* pArray = H_NEW JSONArray();

        for ( osl::u32 i = 0; i < nCount; ++i )
        {
            pArray->put( H_NEW JSONString( value[i] ) );
        }

        return put( key, pArray );
    }

#if H_PROVIDE_UUID
    //---------------------------------------------------------------------------
    bool JSONObject::putUUIDArray( const osl::StringA& key, const osl::QUUID* value, osl::u32 nCount )
    {
        JSONArray* pArray = H_NEW JSONArray();

        for ( osl::u32 i = 0; i < nCount; ++i )
        {
            pArray->put( H_NEW JSONString( value[i].toStringA() ) );
        }

        return put( key, pArray );
    }
#endif // #if H_PROVIDE_UUID

    //! Upper methods put array objects.
    //////////////////////////////////////////////////////////////////////////

    //-----------------------------------------------------------
    bool JSONObject::merge( const JSONObject* pOtherObject, bool override  )
    {
        if ( !pOtherObject )
        {
            return false;
        }

        //override
        if ( override )
        {
            MapConstIterator it( pOtherObject->m_mapObjectPtr.begin() ), ite( pOtherObject->m_mapObjectPtr.end() );
            for ( ; it != ite; ++it )
            {
                m_mapObjectPtr[it->first] = it->second;
            }
            return true;
        }


        //no override
        MapConstIterator it( pOtherObject->m_mapObjectPtr.begin() ), ite( pOtherObject->m_mapObjectPtr.end() );
        for ( ; it != ite; ++it )
        {
            MapIterator iterthis = m_mapObjectPtr.find( it->first );
            if ( iterthis == m_mapObjectPtr.end() )
            {
                m_mapObjectPtr[it->first] = it->second;
            }
        }
        return true;
    }

    //------------------------------------------------------------
    bool JSONObject::loadFrom( osl::MemoryDataStream& ___IN file )
    {
        osl::u32 size = 0;
        file >> size;
        Object* pObject = NULL;
        osl::StringA key;

        for ( osl::u32 i = 0; i < size; i++ )
        {
            file >> ( osl::StringA& )key; //key

            Object::deserializeOneObject( file, pObject );

            if ( pObject )
            {
                put( key, pObject );
                pObject = NULL;
            }
            else
            {
                fprintf( stderr, "Deserialize binary data error!" );
                return false;
            }

        }

        return true;
    }
    //------------------------------------------------------------
    void JSONObject::saveTo( osl::MemoryDataStream& ___OUT file ) const
    {
        file << ( osl::u8 )getType()
            << ( osl::u32 )m_mapObjectPtr.size();
        JSONObject::ObjectPtrMap::const_iterator it( m_mapObjectPtr.begin() ), ite( m_mapObjectPtr.end() );

        for ( ; it != ite; it++ )
        {
            file << it->first;
            it->second->saveTo( file );
        }
    }


    bool JSONObject::equals( const Object& rhs )
    {
        if ( rhs.getType() != getType() )
        {
            return false;
        }

        const JSONObject& rhsJSONOBject = dynamic_cast<const JSONObject&>(rhs);
        if ( rhsJSONOBject.m_mapObjectPtr.size() != m_mapObjectPtr.size() )
        {
            return false;
        }

        //const size_t sz = m_mapObjectPtr.size();
        bool bAllElementEquals = true;
        ObjectPtrMap::const_iterator itthis( m_mapObjectPtr.begin() );
        ObjectPtrMap::const_iterator itethis( m_mapObjectPtr.end() );
        for ( ; itthis != itethis; ++itthis )
        {
            bool bFindEqualOne = false;
            Object* jthis = itthis->second;
            ObjectPtrMap::const_iterator itrhs( m_mapObjectPtr.begin() );
            ObjectPtrMap::const_iterator iterhs( m_mapObjectPtr.end() );
            for ( ; itrhs != iterhs; ++itrhs )
            {
                //TODO ��������Ż�����һ�αȽϹ�ľͲ���Ҫ�ٴαȽ���
                if ( jthis->equals( *(itrhs->second) ) )
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

    bool JSONObject::remove( const osl::StringA& key )
    {
        m_mapObjectPtr.erase( key );
        return true;
    }

    bool JSONObject::remove( const Object* pobj )
    {
        MapIterator it( m_mapObjectPtr.begin() );
        MapIterator ite( m_mapObjectPtr.end() );
        for ( ; it != ite; ++it )
        {
            if ( it->second == pobj )
            {
                m_mapObjectPtr.erase( it );
                return true;
            }
        }

        return false;
    }


    //! Save, Serializer. Save the object into a memory data stream
    osl::MemoryDataStream& operator << ( osl::MemoryDataStream& file, const JSONObject& val )
    {
        val.saveTo( file );
        return file;
    }

    //! Load, Deserialize. Load data from memory data stream and convert it to an object
    osl::MemoryDataStream& operator >> ( osl::MemoryDataStream& file, JSONObject& val )
    {
        osl::u8 type = 0xff;
        file >> type;
        assert( type == OT_OBJECT );
        val.loadFrom( file );
        return file;
    }







// 	template<typename _Type, typename _JsonType>
// 	_JsonType* JSONObject::json_cast(Object* pObj )
// 	{
// 		if( pObj && pObj->getType() == _my_type<_Type>::enum_type )
// 		{
// 			return (_JsonType*)pObj;
// 		}
// 		return NULL;
// 	};
//
// 	template<typename _Type>
// 	_Type& JSONObject::getValue( const osl::StringA& key )
// 	{
// 		Object*& pObj = m_mapObjectPtr[key];
// 		if( pObj )
// 		{
// 			//! add this typedef is used to help compiler to know the real object type
// 			typedef _my_type<_Type> TmpType;
// 			_my_type<_Type>::type* pVal = json_cast<_Type, TmpType::type>( pObj );
// 			if( pVal )
// 			{
// 				return pVal->getRealValue();
// 			}
//
// 			delete pObj;
// 		}
//
// 		pObj = new _my_type<_Type>::type;
// 		return ((_my_type<_Type>::type*)pObj)->getRealValue();
// 	}


};//end of namespace json


#endif //#if H_PROVIDE_JSON


