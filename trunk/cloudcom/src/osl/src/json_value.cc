#include "osl/include/inner_pre.h"

#if H_PROVIDE_JSON

#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"
#include "osl/include/data_stream.h"
#include "osl/include/utility.h"
#include "osl/include/json.h"
#include "json_tokener.h"

/**
This file is the implement code of classes :
    Object, JSONInteger, JSONDouble, JSONString, JSONNull
*/

namespace json
{

    enum
    {
        INTEGER64_BIT_COUNT = 64
    };

    //-------------------------------------------------------------------------
    //----------- Object
    //-------------------------------------------------------------------------

    bool Object::deserializeOneObject( osl::MemoryDataStream& ___IN file, Object*& ___OUT pObject )
    {
        osl::u8 type;

        file >> type;

        switch ( type )
        {
            case OT_OBJECT:
                pObject = H_NEW JSONObject;
                break;
            case OT_ARRAY:
                pObject = H_NEW JSONArray;
                break;
            case OT_STRING:
                pObject = H_NEW JSONString;
                break;
            case OT_INTEGER:
                pObject = H_NEW JSONInteger;
                break;
            case OT_DOUBLE:
                pObject = H_NEW JSONDouble;
                break;
            case OT_BOOLEAN:
                pObject = H_NEW JSONBoolean;
                break;
            case OT_NULL:
                pObject = H_NEW JSONNull;
                break;
            default:
                assert( 0 );
                return false;
        }

        if ( pObject )
        {
            //file >> *pObject;
            pObject->loadFrom( file );
            return true;
        }

        return false;
    }


    //-------------------------------------------------------------------------
    //----------- JSONInteger
    //-------------------------------------------------------------------------

    

    JSONInteger::JSONInteger( osl::s64 value )
        : BaseClass( value )
    {
    }

    JSONInteger& JSONInteger::operator=( osl::s64 value )
    {
        m_value = value;
        return *this;
    }

    bool JSONInteger::toString( osl::StringA& s, bool readable )const
    {
		s = osl::StringUtil::valueOf( m_value );
        return true;
    }

	bool JSONInteger::toStringBuf( osl::MemoryDataStream& ___OUT sb, size_t indent )const
	{
		for ( size_t i = 1; i < indent; i++ )
		{
			sb.write( '\t' );
		}

		osl::StringA s;
		toString( s );
		sb.write( s.c_str(), s.length() );
		return true;
	}

    bool JSONInteger::equals( const Object& rhs )
    {
        if ( rhs.getType() == getType() && dynamic_cast<const JSONInteger&>(rhs).m_value == m_value )
        {
            return true;
        }

        return false;
    }

    //------------------------------------------------------------
    bool JSONInteger::loadFrom( osl::MemoryDataStream& ___IN file )
    {
        file >> ( osl::s64& )m_value;
        return true;
    }
    //------------------------------------------------------------
    void JSONInteger::saveTo( osl::MemoryDataStream& ___OUT file ) const
    {
        file << ( osl::u8 )getType()
             << ( osl::s64 )m_value;
    }

    //-------------------------------------------------------------------------
    //----------- JSONDouble
    //-------------------------------------------------------------------------
    

    JSONDouble::JSONDouble( osl::f64 value )
        : BaseClass( value )
    {
    }

    JSONDouble& JSONDouble::operator=( osl::f64 value )
    {
        m_value = value;
        return *this;
    }

    bool JSONDouble::equals( const JSONDouble& other, osl::f64 tolarence )
    {
        return osl::Util::equals( m_value, other.m_value, tolarence );
    }

    bool JSONDouble::equals( osl::f64 value, osl::f64 tolarence )
    {
        return osl::Util::equals( m_value, value, tolarence );
    }


    bool JSONDouble::toString( osl::StringA& s, bool readable )const
    {
		s = osl::StringUtil::valueOf( m_value );
//		osl::StringUtil::trim( s, "0" );
		return true;

// 		char buf[INTEGER64_BIT_COUNT + 1] = {};
// 		snprintf( buf, INTEGER64_BIT_COUNT, "%lf", m_value );
// 		size_t len = strlen( buf );
// 
// 		for ( size_t i = len - 1; i >= 0; i-- )//trim '0' at the string ends, keep the last char if it is '.'
// 		{
// 			if ( buf[i] != '0' )
// 			{
// 				buf[i+1] = 0;
// 
// 				break;
// 			}
// 		}
// 
// 		s = buf;
// 		return true;
    }

	bool JSONDouble::toStringBuf( osl::MemoryDataStream& ___OUT sb, size_t indent )const
	{
		for ( size_t i = 1; i < indent; i++ )
		{
			sb.write( '\t' );
		}

		osl::StringA s;
		toString( s );
		sb.write( s.c_str(), s.length() );
		return true;
// 		for ( size_t i = 1; i < indent; i++ )
// 		{
// 			sb.write( '\t' );
// 		}
// 
// 		char buf[INTEGER64_BIT_COUNT] = {0};
// 		snprintf( buf, INTEGER64_BIT_COUNT - 1, "%f", m_value );
// 		size_t len = strlen( buf );
// 
// 		for ( size_t i = len - 1; i >= 0; i-- )//trim '0' at the string ends
// 		{
// 			if ( buf[i] != '0' )
// 			{
// 				if ( buf[i] == '.' )
// 				{
// 					buf[i] = 0;
// 				}
// 				else
// 				{
// 					buf[i+1] = 0;
// 				}
// 
// 				break;
// 			}
// 		}
// 
// 		sb.write( buf, strlen( buf ) );
// 		return true;
    }

    bool JSONDouble::equals( const Object& rhs )
    {
        if ( rhs.getType() == getType() && osl::Util::equals( dynamic_cast<const JSONDouble&>(rhs).m_value, m_value )  )
        {
            return true;
        }

        return false;
    }

    //------------------------------------------------------------
    void JSONDouble::saveTo( osl::MemoryDataStream& ___OUT file ) const
    {
        file << ( osl::u8 )getType()
             << ( osl::f64 )m_value;
    }
    //------------------------------------------------------------
    bool JSONDouble::loadFrom( osl::MemoryDataStream& ___IN file )
    {
        file >> ( osl::f64& )m_value;
        return true;
    }


    //-------------------------------------------------------------------------
    //----------- JSONBoolean
    //-------------------------------------------------------------------------
    

    JSONBoolean::JSONBoolean( bool value )
        : BaseClass( value )
    {
    }

    JSONBoolean& JSONBoolean::operator=( bool value )
    {
        m_value = value;
        return *this;
    }


    bool JSONBoolean::toString( osl::StringA& s, bool v )const
    {
		s = m_value?"true":"false";
        return true;
    }

	bool JSONBoolean::toStringBuf( osl::MemoryDataStream& ___OUT sb, size_t indent )const
	{
		for ( size_t i = 1; i < indent; i++ )
		{
			sb.write( '\t' );
		}

		enum{ E_TRUE_STR_LEN = 4, E_FALSE_STR_LEN = 5 };
		if ( m_value )
		{
			sb.write( "true", E_TRUE_STR_LEN );
		}
		else
		{
			sb.write( "false", E_FALSE_STR_LEN );
		}
		return true;
	}

    bool JSONBoolean::equals( const Object& rhs )
    {
        if ( rhs.getType() == getType() && dynamic_cast<const JSONBoolean&>(rhs).m_value == m_value )
        {
            return true;
        }

        return false;
    }

    //------------------------------------------------------------
    void JSONBoolean::saveTo( osl::MemoryDataStream& ___OUT file ) const
    {
        file << ( osl::u8 )getType()
             << ( bool )m_value;
    }
    //------------------------------------------------------------
    bool JSONBoolean::loadFrom( osl::MemoryDataStream& ___IN file )
    {
        file >> ( bool& )m_value;
        return true;
    }



    //-------------------------------------------------------------------------
    //----------- JSONString
    //-------------------------------------------------------------------------

    

    JSONString::JSONString( const osl::StringA& value )
        : BaseClass( value )
    {
    }

    JSONString::JSONString( const char* value )
        : BaseClass( value )
    {
    }

    JSONString& JSONString::operator=( const osl::StringA& value )
    {
        m_value = value;
        return *this;
    }


    bool JSONString::toString( osl::StringA& s, bool readable )const
    {
        return JSONObject::quote( m_value, s );
    }

	bool JSONString::toStringBuf( osl::MemoryDataStream& ___OUT sb, size_t indent )const
	{
		for ( size_t i = 1; i < indent; i++ )
		{
			sb.write( '\t' );
		}

		return JSONObject::quote( m_value, sb );
	}

    bool JSONString::equals( const Object& rhs )
    {
        if ( rhs.getType() == getType() && dynamic_cast<const JSONString&>(rhs).m_value == m_value )
        {
            return true;
        }

        return false;
    }

    //------------------------------------------------------------
    void JSONString::saveTo( osl::MemoryDataStream& ___OUT file ) const
    {
        file << ( osl::u8 )getType()
             << ( osl::StringA )m_value;
    }
    //------------------------------------------------------------
    bool JSONString::loadFrom( osl::MemoryDataStream& ___IN file )
    {
        file >> ( osl::StringA& )m_value;
        return true;
    }



    //-------------------------------------------------------------------------
    //----------- JSONNull
    //-------------------------------------------------------------------------
    

    bool JSONNull::toString( osl::StringA& s, bool readable )const
    {
        s = "null";
        return true;
    }

	bool JSONNull::toStringBuf( osl::MemoryDataStream& ___OUT sb, size_t indent )const
	{
		for ( size_t i = 1; i < indent; i++ )
		{
			sb.write( '\t' );
		}

		enum{ E_NULL_STR_LEN = 4 };
		sb.write( "null", E_NULL_STR_LEN );
		return true;
	}



    bool JSONNull::equals( const Object& rhs )
    {
        if ( rhs.getType() == getType() )
        {
            return true;
        }

        return false;
    }

    //------------------------------------------------------------
    void JSONNull::saveTo( osl::MemoryDataStream& ___OUT file ) const
    {
        file << ( osl::u8 )getType();
    }
    //------------------------------------------------------------
    bool JSONNull::loadFrom( osl::MemoryDataStream& ___IN file )
    {
        return true;
    }

}//end of namespace json



#endif //#if H_PROVIDE_JSON


