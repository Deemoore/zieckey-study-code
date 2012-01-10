//! \file   HDataStream.inl
//!	\date   2010:5:31
//! \brief  MemoryDataStream的 inline函数
//!	\author Han Weiping

#pragma once

namespace osl
{
    inline void MemoryDataStream::swap( MemoryDataStream& r )
    {
        std::swap( m_pData , r.m_pData );
        std::swap( m_bSelfCreate , r.m_bSelfCreate );
        std::swap( m_nSizeBuffer , r.m_nSizeBuffer );
        std::swap( m_nPosWrite , r.m_nPosWrite );
        std::swap( m_nPosRead , r.m_nPosRead );
        std::swap( m_nSize , r.m_nSize );
        std::swap( m_nStates , r.m_nStates );
    }

    //!
#pragma pack(push,1)
    template<typename TE1, typename TE2 >
    struct Struct2Element
    {
        TE1    v1;
        TE2    v2;
    };

    template<typename TE1, typename TE2, typename TE3 >
    struct Struct3Element
    {
        TE1    v1;
        TE2    v2;
        TE3    v3;
    };

    template<typename TE1, typename TE2, typename TE3, typename TE4 >
    struct Struct4Element
    {
        TE1    v1;
        TE2    v2;
        TE3    v3;
        TE4    v4;
    };
#pragma pack(pop)

    //-------------------------------------------------------
    // Serialize Struct2Element
    template<typename TE1, typename TE2 >
    inline osl::MemoryDataStream& operator<< ( osl::MemoryDataStream& file, const Struct2Element<TE1, TE2 >& val )
    {
        file << ( const TE1& )val.v1
             << ( const TE2& )val.v2;

        return file;
    }

    // Serialize Struct2Element
    template<typename TE1, typename TE2 >
    inline osl::MemoryDataStream& operator>> ( osl::MemoryDataStream& file,  Struct2Element<TE1, TE2 >& val )
    {
        file >> ( TE1& )val.v1
             >> ( TE2& )val.v2;

        return file;
    }


    //-------------------------------------------------------
    // Serialize Struct2Element
    template<typename TE1, typename TE2, typename TE3 >
    inline osl::MemoryDataStream& operator<< ( osl::MemoryDataStream& file, const Struct3Element<TE1, TE2, TE3 >& val )
    {
        file << ( const TE1& )val.v1
             << ( const TE2& )val.v2
             << ( const TE3& )val.v3;
        return file;
    }

    // Serialize Struct2Element
    template<typename TE1, typename TE2, typename TE3 >
    inline osl::MemoryDataStream& operator>> ( osl::MemoryDataStream& file,  Struct3Element<TE1, TE2, TE3 >& val )
    {
        file >> ( TE1& )val.v1
             >> ( TE2& )val.v2
             >> ( TE3& )val.v3;
        return file;
    }

    //-------------------------------------------------------
    template<typename TE1, typename TE2, typename TE3, typename TE4 >
    inline osl::MemoryDataStream& operator<< ( osl::MemoryDataStream& file, const Struct4Element<TE1, TE2, TE3, TE4 >& val )
    {
        file << ( const TE1& )val.v1
             << ( const TE2& )val.v2
             << ( const TE3& )val.v3
             << ( const TE4& )val.v4;
        return file;
    }

    template<typename TE1, typename TE2, typename TE3, typename TE4 >
    inline osl::MemoryDataStream& operator>> ( osl::MemoryDataStream& file,  Struct4Element<TE1, TE2, TE3, TE4 >& val )
    {
        file >> ( TE1& )val.v1
             >> ( TE2& )val.v2
             >> ( TE3& )val.v3
             >> ( TE4& )val.v4;
        return file;
    }






    // MemoryDataStream Implementation

    inline MemoryDataStream::MemoryDataStream() : m_pData( NULL )
        , m_bSelfCreate( false )
        , m_nSizeBuffer( 0 )
        , m_nPosWrite( 0 )
        , m_nPosRead( 0 )
        , m_nSize( 0 )
        , m_nStates( 0 )
    {

    }

    inline MemoryDataStream::MemoryDataStream( int nBufferSize ) : m_bSelfCreate( true )
        , m_nSizeBuffer( nBufferSize )
        , m_nPosWrite( 0 )
        , m_nPosRead( 0 )
        , m_nSize( 0 )
        , m_nStates( 0 )
    {
        m_pData = ( u8* )H_ALLOC_NAME( m_nSizeBuffer, "MemoryDataStream" );

        if ( !m_pData )
        {
            m_nSizeBuffer = 0;
        }
    }
    //! Construct with outside memory and size.
    inline MemoryDataStream::MemoryDataStream( osl::u8* pData, int nBufferSize, bool bDestroy )
        : m_pData( pData )
        , m_bSelfCreate( bDestroy )
        , m_nSizeBuffer( nBufferSize )
        , m_nPosWrite( 0 )
        , m_nPosRead( 0 )
        , m_nSize( nBufferSize )
        , m_nStates( 0 )
    {
    }

    inline MemoryDataStream::~MemoryDataStream()
    {
        if ( m_pData && m_bSelfCreate )
        {
            MemAlloc::free( m_pData );
        }
    }

    inline bool MemoryDataStream::isReadBad() const
    {
        return ( m_nStates & S_READ_BAD ) == 0  ? false : true;
    }

    inline bool MemoryDataStream::isWriteBad() const
    {
        return ( m_nStates & S_WRITE_BAD ) == 0 ? false : true;
    }

    inline void MemoryDataStream::setStates( unsigned int nBits )
    {
        m_nStates |= nBits;
    }

    inline bool MemoryDataStream::read( void* buf, u32 buf_len )
    {
        // check whether the file is bad.
        assert( buf && m_pData );

        if ( isReadBad() )
        {
            return false;
        }

        u32 nNewPos = m_nPosRead + buf_len;

        if ( nNewPos > ( u32 )m_nSize )
        {
            setStates( S_READ_BAD );
            return false;
        }

        memcpy( buf, m_pData + m_nPosRead, buf_len );

        m_nPosRead = nNewPos;

        return true;
    }

    inline bool MemoryDataStream::write( char ch )
    {
        return write( &ch, 1 );
    }
	
	inline bool MemoryDataStream::readle( u32* pu32 )
	{
		if ( this->getReadableSize() < 4 )
		  return false;

#ifdef H_LITTLE_ENDIAN
		*this >> *pu32;
#else
		u8* pc = (u8*)pu32;
		*this >> pc[3];
		*this >> pc[2];
		*this >> pc[1];
		*this >> pc[0];
#endif

		return true;
	}

	inline bool MemoryDataStream::writele( u32 i )
	{
#ifdef H_LITTLE_ENDIAN
		*this << i;
#else
		*this << (char)( ( i & 0xff000000 ) >> 24 );
		*this << (char)( ( i & 0x00ff0000 ) >> 16 );
		*this << (char)( ( i & 0x0000ff00 ) >> 8  );
		*this << (char)( ( i & 0x000000ff ) );
#endif
		return true;
	}

    inline bool MemoryDataStream::write( const void* buf, u32 buf_len )
    {
        assert( buf );

        if ( !appendSize( buf_len ) )
        {
            return false;
        }

        memcpy( m_pData + m_nPosWrite, buf, buf_len );

        m_nPosWrite += buf_len;

        // update size.
        m_nSize = m_nPosWrite > m_nSize ? m_nPosWrite : m_nSize; //std::max( m_nPosWrite, m_nSize );

        return true;
    }

    inline osl::u32 MemoryDataStream::seekg( s32 offset )
    {
        s32 nNewPos = m_nPosRead + offset;

        if ( nNewPos > ( s32 )m_nSize )
        {
            m_nPosRead = m_nSize;
            setStates( S_READ_BAD );

        }
        else if ( nNewPos < 0 )
        {

            m_nPosRead = 0;
            setStates( S_READ_BAD );
        }
        else
        {
            m_nPosRead = nNewPos;
        }

        return m_nPosRead;
    }

    inline osl::u32 MemoryDataStream::tellg() const
    {
        return m_nPosRead;
    }

    inline osl::u32 MemoryDataStream::seekp( s32 offset )
    {
		s32 nNewPos = (osl::s32)m_nPosWrite + offset;

        if ( nNewPos < 0 )
        {
            m_nPosWrite = 0;
        }
        else
        {
			// pre-allocate size.
			if ( nNewPos > (osl::s32)m_nSize )
			{
				if ( !appendSize( (u32)nNewPos - m_nSize  ) )
				{
					return 0;
				}
			}

			// finished check, set the new size.
			m_nPosWrite = nNewPos;
        }

        // update size.
        m_nSize = m_nPosWrite > m_nSize ? m_nPosWrite : m_nSize; //std::max( m_nPosWrite, m_nSize );

        return m_nPosWrite;
    }

    inline u32 MemoryDataStream::tellp() const
    {
        return m_nPosWrite;
    }

    inline bool MemoryDataStream::setSize( u32 nSize )
    {
        // check size and assure enough buffer.
        if ( nSize > m_nSize )
        {
            if ( !appendSize( nSize - m_nSize ) )
            {
                return false;
            }
        }
        else if ( nSize == 0 )
        {
            /*
            这里添加 ‘nSize == 0’ 是为了确保分配内存给 m_pData 。
            */
            if ( !appendSize( sizeof(long) ) )
            {
                return false;
            }
        }

        // assure current file write position is winthin the file extend.
        if ( nSize < m_nPosWrite )
        {
            m_nPosWrite = nSize;
        }

        //!
        m_nSize = nSize;

        return true;
    }

    inline osl::u32 MemoryDataStream::getSize() const
    {
        return m_nSize;
    }

    inline void* MemoryDataStream::getCache() const
    {
        assert( m_pData );
        return m_pData;
    }

    inline u8 MemoryDataStream::charAt( u32 index ) const
    {
        assert( index < getSize() );
        return *( ( s8* )getCache() + index );
    }

    inline osl::u32 MemoryDataStream::getReadableSize() const
    {
        return getSize() - ( u32 )tellg();
    }

    inline void* MemoryDataStream::getCurReadBuffer() const
    {
        return ( ( char* )getCache() ) + tellg();
    }
    inline void* MemoryDataStream::getCurWriteBuffer() const
    {
        return ( ( char* )getCache() ) + tellp();
    }

    inline void MemoryDataStream::close()
    {
        reset();
    }

    inline void MemoryDataStream::reset()
    {
        m_nPosWrite = m_nPosRead = m_nSize = m_nStates = 0;
    }

    inline MemoryDataStream& MemoryDataStream::operator<<( const StringA& val )
    {
        u32 nStrLen = ( u32 )val.length() ;

        // 1. write string length
        *this << ( u32& )nStrLen;

        // 2. write string
        write( val.c_str(), ( u32 )nStrLen );

        return *this;
    }

#ifndef H_STD_STRING
    inline MemoryDataStream& MemoryDataStream::operator<<( const StringA::_BaseType& val )
    {
        u32 nStrLen = ( u32 )val.length() ;

        // 1. write string length
        *this << ( u32& )nStrLen;

        // 2. write string
        write( val.c_str(), ( u32 )nStrLen );

        return *this;
    }
#endif

    inline MemoryDataStream& MemoryDataStream::operator<<( const char* szVal )
    {
		if ( NULL == szVal )
		{
			return *this;
		}

        u32 nStrLen = ( u32 )strlen( szVal ) ;

        // 1. write string length
        *this << ( u32& )nStrLen;

        // 2. write string
        write( szVal, nStrLen  );

        return *this;
    }





    inline MemoryDataStream& MemoryDataStream::operator>>( StringA& val )
    {
        // check whether the file is bad.
        if ( isReadBad() )
        {
            return *this;
        }

        // 1. get length
        u32 nSize = 0;
        *this >> ( u32& )nSize;

        // 2. get file
        if ( nSize <= ( u32 )getReadableSize() )
        {
            val.resize( nSize );

            if ( nSize )
            {
                read( &val[0], nSize );

                // assure last character is null
                val[nSize] = ( char )0;
            }

        }
        else
        {
            setStates( S_READ_BAD );
        }

        return *this;
    }

    inline MemoryDataStream& MemoryDataStream::operator<<( const MemoryDataStream& val )
    {
        // 1. write string length
        *this << ( u32 )val.getSize();

        // 2. write string
        if( val.getSize() > 0 )
        {
            write( ( char* )val.getCache(), val.getSize() );
        }

        return *this;
    }

    inline MemoryDataStream& MemoryDataStream::operator>>( MemoryDataStream& val )
    {
        // check whether the file is bad.
        if ( isReadBad() )
        {
            return *this;
        }

        // 1. read length
        u32 nSize = 0;
        *this >> nSize;

        //
        val.reset();

        if( nSize == 0 )
        {
            return *this;
        }

        if ( nSize <= ( u32 )getReadableSize() )
        {
            // 2. read string
            val.write( ( ( char* )getCache() + tellg() ), nSize );

            // skip
            seekg( nSize );
        }
        else
        {
            setStates( S_READ_BAD );
        }

        return *this;
    }

    inline bool MemoryDataStream::appendSize( u32 nSizeToAdd )
    {
        u32 nNewSize = m_nSize + nSizeToAdd + 1;

        // only if buffer is no sufficient, we reallocate it.
        if ( nNewSize > ( u32 )m_nSizeBuffer )
        {
            u32 nNewBufferSize = nNewSize + ( nNewSize >> 1 );

            u8* pNewBuf = ( u8* )H_ALLOC_NAME( nNewBufferSize, "MemoryDataStream" );

            if ( !pNewBuf )
            {
                setStates( S_READ_BAD | S_WRITE_BAD );
                return false;
            }

            if ( m_pData )
            {
                memcpy( pNewBuf, m_pData, m_nSizeBuffer );
            }


            if ( m_bSelfCreate )
            {
                MemAlloc::free( m_pData );
            }

            m_pData       = pNewBuf;
            m_nSizeBuffer = nNewBufferSize;
            m_bSelfCreate = true;
        }

        return true;
    }

    inline bool MemoryDataStream::setBufferSize( u32 new_size )
    {
        return reserve( new_size );
    }
    

    inline bool MemoryDataStream::reserve( u32 new_size )
    {
        if ( new_size > m_nSizeBuffer )
        {
            u8* pNewBuf = ( u8* )H_ALLOC_NAME( new_size, "MemoryDataStream" );

            if ( !pNewBuf )
            {
                setStates( S_READ_BAD | S_WRITE_BAD );
                return false;
            }

            m_nSizeBuffer = new_size;

            if ( m_pData )
            {
                memcpy( pNewBuf, m_pData, m_nSize );
            }

            
            if ( m_bSelfCreate )
            {
                //means the old buffer is created by myself, we need free it
                MemAlloc::free( m_pData );
            }


            m_pData = pNewBuf;
            m_bSelfCreate = true;
        }

        return true;
    }


    template< typename T>
    inline MemoryDataStream& MemoryDataStream::InternalWriteType( const T& val , stdext::true_type )
    {
        write( &val, sizeof( T ) );
        return ( *this );
    }



    template< typename T>
    inline MemoryDataStream& MemoryDataStream::InternalReadType( T& val , stdext::true_type )
    {
        read( &val, sizeof( T ) );
        return ( *this );
    }

    template< typename T>
    inline MemoryDataStream& MemoryDataStream::operator<<( const T& val )
    {
        typedef  typename stdext::bool_type<stdext::is_pod<T>::value>::type T_type;
        return InternalWriteType( val , T_type() );
    }

    template<typename _Kt, typename _ContainerName>
    inline void MemoryDataStream::writeSimpleVector( const Vector<_Kt, _ContainerName>& val )
    {
        // 1. write length
        *this << ( u32 )val.size();

        // 2. memory
        if ( !val.empty() )
        {
            this->write( &( val[0] ), ( osl::u32 )sizeof( _Kt ) * val.size()  );
        }
    }


    template< typename T>
    inline MemoryDataStream& MemoryDataStream::operator>>( T& val )
    {
        typedef  typename stdext::bool_type<stdext::is_pod<T>::value>::type T_type;
        return InternalReadType( val , T_type() );
    }

    template<  typename _Kt, typename _Val >
    inline MemoryDataStream& MemoryDataStream::operator>>( std::pair<_Kt, _Val>& val )
    {
        ( *this ) >> val.first >> val.second;
        return *this;
    }

    template< typename _Kt, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::operator<<( const Vector< _Kt, _ContainerName >& val )
    {
        // 1. write length
        typedef  typename stdext::bool_type<stdext::is_pod<_Kt>::value>::type _Kt_type;
        return InternalWrite( val , _Kt_type() );
    }

    template< typename _Kt, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::operator<<( const List< _Kt, _ContainerName >& val )
    {
        // 1. write length
        *this << ( u32 )val.size();

        typedef typename List<_Kt, _ContainerName>::const_iterator ConstIterator;
        ConstIterator it( val.begin() ), ite( val.end() );

        for ( ; it != ite; ++it )
        {
            *this << ( const _Kt& )*it;
        }

        return *this;
    }

    template<  typename _Kt, typename _Val >
    inline MemoryDataStream& MemoryDataStream::operator<<( const std::pair<_Kt, _Val>& val )
    {
        ( *this ) << val.first << val.second;
        return *this;
    }

    template<  typename _Kt, typename _Val, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::operator<<( const Map< _Kt, _Val, _ContainerName >& val )
    {
        // 1. write length
        *this << ( u32 )val.size();

        // 2. elements.
        typedef typename Map<_Kt, _Val, _ContainerName >::const_iterator ConstIterator;
        ConstIterator it( val.begin() ), ite( val.end() );

        for ( ; it != ite; ++it )
        {
            // get key
            *this << static_cast<const _Kt&>( it->first );

            // get value
            *this << static_cast<const _Val&> ( it->second );
        }

        return *this;
    }

    template<  typename _Kt, typename _Val, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::operator<<( const HashMap< _Kt, _Val, _ContainerName >& val )
    {
        // 1. write length
        *this << ( u32 )val.size();

        // 2. elements.
        typedef typename HashMap<_Kt, _Val, _ContainerName >::const_iterator ConstIterator;
        ConstIterator it( val.begin() ), ite( val.end() );

        for ( ; it != ite; ++it )
        {
            // get key
            *this << ( const _Kt& )it->first;

            // get value
            *this << ( const _Val& )it->second;
        }

        return *this;
    }

    template< typename _Kt, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::InternalWrite( const Vector< _Kt, _ContainerName >& val, stdext::false_type )
    {
        *this << ( u32 )val.size();

        typedef typename Vector<_Kt, _ContainerName>::const_iterator ConstIterator;
        ConstIterator it( val.begin() ), ite( val.end() );

        for ( ; it != ite; ++it )
        {
            *this << ( const _Kt& )*it;
        }

        return *this;
        //write
    }

    template< typename _Kt, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::InternalWrite( const Vector< _Kt, _ContainerName >& val, stdext::true_type )
    {
        writeSimpleVector( val );
        return *this;
    }
    template< typename _Kt, typename _Val, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::operator>>( HashMap<_Kt, _Val, _ContainerName >& val )
    {
        // check whether the file is bad.
        if ( isReadBad() )
        {
            return *this;
        }

        // 1. read length
        u32 nSize = 0;
        *this >> ( u32& )nSize;

        if ( getReadableSize() < nSize )
        {
            setStates( S_READ_BAD );
            return *this;
        }

        val.clear();

        for ( u32 i = 0; i < nSize; ++i )
        {
            if ( getReadableSize() == 0 )
            {
                setStates( S_READ_BAD );
                break;
            }

            // key,  value,
            _Kt key = _Kt();

            // get key
            *this >> ( _Kt& )key;

            // get value
            *this >> ( _Val& )val[key];
        }

        return *this;
    }

    template< typename _Kt, typename _Val, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::operator>>( Map<_Kt, _Val, _ContainerName >& val )
    {
        // check whether the file is bad.
        if ( isReadBad() )
        {
            return *this;
        }

        // 1. read length
        u32 nSize = 0;
        *this >> ( u32& )nSize;

        if ( getReadableSize() < nSize )
        {
            setStates( S_READ_BAD );
            return *this;
        }

        val.clear();

        for ( u32 i = 0; i < nSize; ++i )
        {
            if ( getReadableSize() == 0 )
            {
                setStates( S_READ_BAD );
                break;
            }

            // key,  value,
            _Kt key = _Kt();

            // get key
            *this >> ( _Kt& )key;

            // get value
            *this >> ( _Val& )val[key];
        }

        return *this;
    }

    template< typename _Kt, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::operator>>( List< _Kt, _ContainerName >& val )
    {
        // check whether the file is bad.
        if ( isReadBad() )
        {
            return *this;
        }

        // 1. read length
        u32 nSize = 0;
        *this >> ( u32& )nSize;

        if ( getReadableSize() < nSize )
        {
            setStates( S_READ_BAD );
            return *this;
        }

        val.clear();

        for ( u32 i = 0; i < nSize; ++i )
        {
            if ( getReadableSize() == 0 )
            {
                setStates( S_READ_BAD );
                break;
            }

            val.push_back( _Kt() );
            *this >> ( _Kt& )val.back();
        }

        return *this;
    }

    template< typename _Kt, typename _ContainerName >
    inline void MemoryDataStream::readSimpleVector( Vector< _Kt, _ContainerName >& val )
    {
        // check whether the file is bad.
        if ( isReadBad() )
        {
            return;
        }

        // 1. write length
        u32 nSize = 0;
        *this >> ( u32& )nSize;

        if ( getReadableSize() < nSize )
        {
            setStates( S_READ_BAD );
            return ;
        }

        val.resize( nSize );

        // 2. memory
        if ( nSize )
        {
            read( &( val[0] ), sizeof( _Kt ) * nSize );
        }
    }
    template< typename _Kt, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::InternalReadVector( Vector< _Kt, _ContainerName >& val , stdext::true_type )
    {
        readSimpleVector( val );
        return *this;
    }
    template< typename _Kt, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::InternalReadVector( Vector< _Kt, _ContainerName >& val , stdext::false_type )
    {
        // check whether the file is bad.
        if ( isReadBad() )
        {
            return *this;
        }

        // 1. read length
        u32 nSize = 0;
        *this >> ( u32& )nSize;

        if ( getReadableSize() < nSize )
        {
            setStates( S_READ_BAD );
            return *this;
        }

        val.resize( nSize );

        for ( u32 i = 0; i < nSize; ++i )
        {
            if ( getReadableSize() == 0 )
            {
                // set bad flag.
                setStates( S_READ_BAD );

                //
                val.clear();
                break;
            }

            *this >> ( _Kt& )val[i];
        }

        return *this;
    }
    template< typename _Kt, typename _ContainerName >
    inline MemoryDataStream& MemoryDataStream::operator>>( Vector< _Kt, _ContainerName >& val )
    {
        typedef  typename stdext::bool_type<stdext::is_pod<_Kt>::value>::type _Kt_type;
        return InternalReadVector( val , _Kt_type() );
    }


    template< typename T>
    inline MemoryDataStream& MemoryDataStream::operator>>( osl::RefPtr<T>& val )
    {
        if ( NULL == val.get() )
        {
            val = H_NEW T;
        }

        ( *this ) >> ( *val.getPointer() );


        return ( *this );
    }
    template< typename T>
    inline MemoryDataStream& MemoryDataStream::operator<<( const osl::RefPtr<T>& val )
    {
        if ( NULL == val.get() )
        {
			setStates( S_WRITE_BAD );
			assert( false && "null pointer can not be serialized!");
            return ( *this );
        }

        ( *this ) << ( *val.getPointer() );
        return ( *this );
    }

	inline MemoryDataStream& MemoryDataStream::operator>>( osl::RefPtr<MemoryDataStream>& val )
	{
		if ( NULL == val.get() )
		{
			val = H_NEW MemoryDataStream();
		}

		( *this ) >> ( *val.getPointer() );


		return ( *this );
	}
	inline MemoryDataStream& MemoryDataStream::operator<<( const osl::RefPtr<MemoryDataStream>& val )
	{
		if ( NULL == val.get() )
		{
			(*this) << osl::u32(0);
			return ( *this );
		}

		( *this ) << ( *val.getPointer() );
		return ( *this );
	}

    template<class T, typename _ContainerName>
    inline MemoryDataStream& MemoryDataStream::operator<<( const osl::Set<T, _ContainerName>& val )
    {
        ( *this ) << ( osl::u32 )val.size();

        typedef typename osl::Set<T, _ContainerName>::const_iterator Iterator;
        Iterator end = val.end();

        for ( Iterator i = val.begin() ; i != end ; ++i )
        {
            ( *this ) << ( *i );
        }

        return  ( *this );
    }

    template<class T, typename _ContainerName>
    inline MemoryDataStream& MemoryDataStream::operator>>( osl::Set<T, _ContainerName>& val )
    {
        u32 nSize;
        ( *this ) >> nSize;

        if (  ( *this ).getReadableSize() < nSize )
        {
            ( *this ).setStates( MemoryDataStream::S_READ_BAD );
            return  ( *this );
        }

        for ( size_t i = 0 ; i < nSize ; ++i )
        {
            if (  ( *this ).getReadableSize() == 0 )
            {
                ( *this ).setStates( MemoryDataStream::S_READ_BAD );
                val.clear();
                break;
            }

            T element = T();
            ( *this ) >> element;
            val.insert( element );
        }

        return  ( *this );
    }


// 	friend bool isContentEquals( const MemoryDataStream& first, const MemoryDataStream& second )
// 	{
// 		bool bequals = true;
// 		if ( first.getSize() == second.getSize() )
// 		{
// 			u32 sz = first.getSize();
// 			for ( u32 i = 0; i < sz; i++ )
// 			{
// 				if ( first.charAt( i ) != second.charAt( i ) )
// 				{
// 					bequals = false;
// 					break;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			bequals = false;
// 		}
// 
// 		return bequals;
// 	}

}//end of namespace osl


namespace std
{
    inline void swap( osl::MemoryDataStream& l , osl::MemoryDataStream& r )
    {
        l.swap( r );
    }
}


