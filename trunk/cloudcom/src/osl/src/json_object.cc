#include "osl/include/inner_pre.h"

#if H_PROVIDE_JSON

#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"
#include "osl/include/data_stream.h"
#include "osl/include/json.h"
#include "json_tokener.h"
#include "json_utf8_inl.h"

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
        if ( source_len == 0 || !source )
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

    bool JSONObject::put( const osl::StringA& key, Object* value )
    {
        if ( !value )
        {
            m_object_map.erase( key );
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

        m_object_map[key] = value;
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
                        fprintf( stderr, "Not a valid octal character : %c\n", s[i] );
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

    
//     bool JSONObject::quote( const osl::StringA& ___IN source, osl::MemoryDataStream& ___OUT sb )
//     {
//         if ( source.seq_len() == 0 )
//         {
//             sb.write( "\"\"", 2 );
//             return true;
//         }
// 
//         const char *pos, *end;
//         int32_t codepoint;
// 
//         sb.write( '"' );
// 
//         end = pos = source.c_str();
//         while(1)
//         {
//             const char *text;
//             char seq[13];
//             int seq_len;
// 
//             while(*end)
//             {
//                 end = utf8_iterate(pos, &codepoint);
//                 if(!end)
//                     return -1;
// 
//                 /* mandatory escape or control char */
//                 if(codepoint == '\\' || codepoint == '"' || codepoint < 0x20)
//                     break;
// 
//                 /* non-ASCII */
//                 if(ascii && codepoint > 0x7F)
//                     break;
// 
//                 pos = end;
//             }
// 
//             if(pos != str) {
//                 if(dump(str, pos - str, data))
//                     return -1;
//             }
// 
//             if(end == pos)
//                 break;
// 
//             /* handle \, ", and control codes */
//             length = 2;
//             switch(codepoint)
//             {
//             case '\\': text = "\\\\"; break;
//             case '\"': text = "\\\""; break;
//             case '\b': text = "\\b"; break;
//             case '\f': text = "\\f"; break;
//             case '\n': text = "\\n"; break;
//             case '\r': text = "\\r"; break;
//             case '\t': text = "\\t"; break;
//             default:
//                 {
//                     /* codepoint is in BMP */
//                     if(codepoint < 0x10000)
//                     {
//                         sprintf(seq, "\\u%04x", codepoint);
//                         length = 6;
//                     }
// 
//                     /* not in BMP -> construct a UTF-16 surrogate pair */
//                     else
//                     {
//                         int32_t first, last;
// 
//                         codepoint -= 0x10000;
//                         first = 0xD800 | ((codepoint & 0xffc00) >> 10);
//                         last = 0xDC00 | (codepoint & 0x003ff);
// 
//                         sprintf(seq, "\\u%04x\\u%04x", first, last);
//                         length = 12;
//                     }
// 
//                     text = seq;
//                     break;
//                 }
//             }
// 
//             if(dump(text, length, data))
//                 return -1;
// 
//             str = pos = end;
//         }
// 
//         return dump("\"", 1, data);
//         return true;
//     }

    
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
                    {
                        //Reference of jansson-2.0.1 http://www.digip.org/jansson/
                        int32_t codepoint = 0;
                        const char* end = utf8_iterate(source.c_str() + i, &codepoint);
                        if (!end)
                        {
                            //This is not a ASCII code and also NOT an UTF8 code, 
                            //Maybe it is GBK Chinese code, so we just write it
                            sb.write(c);
                            break;
                        }

                        if (codepoint <= 0x7F)
                        {
                            sb.write(static_cast<char>(codepoint));
                        }
                        else
                        {
                            char seq[13] = {};
                            int  seq_len = 0; //The length of data written into seq
                            /* codepoint is in BMP */
                            if(codepoint < 0x10000)
                            {
                                snprintf(seq, sizeof(seq), "\\u%04x", codepoint);
                                seq_len = 6;
                            }
                            else/* not in BMP -> construct a UTF-16 surrogate pair */
                            {
                                int32_t first, last;

                                codepoint -= 0x10000;
                                first = 0xD800 | ((codepoint & 0xffc00) >> 10);
                                last = 0xDC00 | (codepoint & 0x003ff);

                                snprintf(seq, sizeof(seq), "\\u%04x\\u%04x", first, last);
                                seq_len = 12;
                            }

                            sb.write(seq, seq_len);
                            i = end - source.data() - 1; // -1 means for loop's third expression has a inc : i += 1
                        }
                        break;
                    }//end of default
                    
                    //---------------------------------------------------------
                    //---------------------------------------------------------
                    // --- OR --- old code , No process of UTF-8 
                    //sb.write( c ); 
                    //---------------------------------------------------------
                    //---------------------------------------------------------
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
        ConstIterator it = m_object_map.find( key );

        if ( it != m_object_map.end() )
        {
            return ( it->second );
        }

        return NULL;
    }

    JSONBoolean* JSONObject::getJSONBoolean( const osl::StringA& key )const
    {
        ConstIterator it = m_object_map.find( key );

        if ( it != m_object_map.end() )
        {
            return dynamic_cast<JSONBoolean*>( ( it->second ).getPointer() );
            //return Json_Cast<JSONBoolean>(it->second);
        }

        return NULL;
    }

    JSONDouble*	JSONObject::getJSONDouble( const osl::StringA& key )const
    {
        ConstIterator it = m_object_map.find( key );

        if ( it != m_object_map.end() )
        {
            return dynamic_cast<JSONDouble*>( ( it->second ).getPointer() );
            //return Json_Cast<JSONDouble>(it->second);
        }

        return NULL;
    }

    JSONInteger*	JSONObject::getJSONInteger( const osl::StringA& key )const
    {
        ConstIterator it = m_object_map.find( key );

        if ( it != m_object_map.end() )
        {
            return dynamic_cast<JSONInteger*>( ( it->second ).getPointer() );
            //return Json_Cast<JSONInteger>(it->second);
        }

        return NULL;
    }

    JSONArray*		JSONObject::getJSONArray( const osl::StringA& key )const
    {
        ConstIterator it = m_object_map.find( key );

        if ( it != m_object_map.end() )
        {
            return dynamic_cast<JSONArray*>( ( it->second ).getPointer() );
            //return Json_Cast<JSONArray>(it->second);
        }

        return NULL;
    }

    JSONObject*	JSONObject::getJSONObject( const osl::StringA& key )const
    {
        ConstIterator it = m_object_map.find( key );

        if ( it != m_object_map.end() )
        {
            return dynamic_cast<JSONObject*>( ( it->second ).getPointer() );
            //return Json_Cast< JSONObject>(it->second);
        }

        return NULL;
    }

    JSONString*	JSONObject::getJSONString( const osl::StringA& key )const
    {
        ConstIterator it = m_object_map.find( key );

        if ( it != m_object_map.end() )
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

        ConstIterator it( m_object_map.begin() ), ite( m_object_map.end() );
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
            ConstIterator it( pOtherObject->m_object_map.begin() ), ite( pOtherObject->m_object_map.end() );
            for ( ; it != ite; ++it )
            {
                m_object_map[it->first] = it->second;
            }
            return true;
        }

        //no override
        ConstIterator it( pOtherObject->m_object_map.begin() ), ite( pOtherObject->m_object_map.end() );
        for ( ; it != ite; ++it )
        {
            Iterator iterthis = m_object_map.find( it->first );
            if ( iterthis == m_object_map.end() )
            {
                m_object_map[it->first] = it->second;
            }
        }
        return true;
    }

    //------------------------------------------------------------
    bool JSONObject::loadFrom( osl::MemoryDataStream& ___IN file )
    {
        osl::u32 sz = 0;
        file >> sz;
        Object* pObject = NULL;
        osl::StringA key;

        for ( osl::u32 i = 0; i < sz; i++ )
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
            << ( osl::u32 )m_object_map.size();
        JSONObject::ObjectPtrMap::const_iterator it( m_object_map.begin() ), ite( m_object_map.end() );

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
        if ( rhsJSONOBject.m_object_map.size() != m_object_map.size() )
        {
            return false;
        }

        ObjectPtrMap::const_iterator itthis( m_object_map.begin() );
        ObjectPtrMap::const_iterator itethis( m_object_map.end() );
        ObjectPtrMap::const_iterator itrhs( rhsJSONOBject.begin() );
        ObjectPtrMap::const_iterator iterhs( rhsJSONOBject.end() );
        for ( ; itthis != itethis && itrhs != iterhs; ++itthis, ++itrhs )
        {
            if (itthis->first != itrhs->first)
            {
                return false;
            }

            if (!itthis->second->equals(*(itrhs->second)))
            {
                return false;
            }
        } // end of for

        return true;
    }

    bool JSONObject::remove( const osl::StringA& key )
    {
        m_object_map.erase( key );
        return true;
    }

    bool JSONObject::remove( const Object* pobj )
    {
        Iterator it( m_object_map.begin() );
        Iterator ite( m_object_map.end() );
        for ( ; it != ite; ++it )
        {
            if ( it->second == pobj )
            {
                m_object_map.erase( it );
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
        if (!val.loadFrom( file ))
        {
            fprintf(stderr, "load data failed from memory data stream!\n");
        }
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
// 		Object*& pObj = m_object_map[key];
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


