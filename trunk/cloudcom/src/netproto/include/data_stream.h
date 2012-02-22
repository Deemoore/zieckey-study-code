#ifndef _NETPROTO_DATASTREAM_H_
#define _NETPROTO_DATASTREAM_H_

#include "netproto/include/inner_pre.h"

namespace npp
{
#define H_ALLOC( size )               ::malloc( (size) )
#define H_ALLOC_NAME( size, name )    ::malloc( (size) )
#define H_ALLOC_NAME_FILE( size, name, file_name, line_no )    ::malloc( (size) )
#define H_FREE( p )       if(p){ ::free( (p) ); p = 0;}

    //! The class encapsulates data stream in memory.
    class _EXPORT_NETPROTO MemoryDataStream
    {
    public:
        enum State
        {
            S_READ_BAD  = 1 << 5,
            S_WRITE_BAD = 1 << 6,
        };

    public:

        //! Default Constructor.
        MemoryDataStream();

        //! Construct with memory size.
        explicit MemoryDataStream( int nBufferSize );

        //! Construct with outside memory and size.
        //! \note if bDestroy is true, the memory will be released by call to MemAlloc::free(...),
        //!      so pData MUST be allocated by call to MemAlloc::alloc(...)
        explicit MemoryDataStream( u8* pData, int nBufferSize, bool bDestroy );

        //! Destructor.
        ~MemoryDataStream();


        //! Assure convert to text.
        //! \remark Add ending null to the stream.
        //! \note The method CAN ONLY be called once on a stream. Once the method is invoked, NO write method
        //!       should be followed.
        void toText();


        //! Query whether the read operation is bad.
        bool isReadBad()const;


        //! Query whether the write operation is bad.
        bool isWriteBad()const;


        //! Sets stats of the file.
        void setStates( unsigned int nBits );;

        //! \warning 废弃的接口，请调用 readRawFile(const std::string& strFileName)
        //! Open raw file and read all the file data to this memory data stream
        //! \note It is only a helper method. path splittor should be "/"
        bool openRawFile( const std::string& strFileName );

        //! Open the raw file and read all the file data to this memory data stream
        //! \note It is only a helper method. path splittor should be "/"
        bool readRawFile( const std::string& strFileName );

        //! \brief: Helper method to save data to a disk file. path splittor should be "/"
        //! \param[in]: const std::string & strFilePathName, the path name of the file, it can include dir path
        //! \return: bool
        bool saveToFile( const std::string& strFilePathName );


        /** read data form data stream, the result is in buf
        *  @remark The read count is in len,it may be lesser than the buf_len,
        *          the len will be zero if read nothing or there is an error occured
        *  @param  buf: the buffer which the result will be stored
        *  @param  buf_len: the buf length in byte
        *  @return the return value is true if read succeed, else false
        */
        bool read( void* buf, u32 buf_len );
		


        /** Read 4 bytes from this data stream, the data in this stream is Little Endian
		*   In little endian CPU system:
		*		char* pc = pU32;
		*		m_pData[0] -> pc[0]
		*		m_pData[1] -> pc[1]
		*		m_pData[2] -> pc[2]
		*		m_pData[3] -> pc[3]
		*   In big endian CPU system:
		*		char* pc = pint;
		*		m_pData[0] -> pc[3]
		*		m_pData[1] -> pc[2]
		*		m_pData[2] -> pc[1]
		*		m_pData[3] -> pc[0]
        *  @param  pint : the value will stored there 
        *  @return the return value is true if read succeed, else false
        */
		bool readle( u32* pU32 );

        /** write a char to data stream
        *  @param  ch: the char which will be written
        *  @note   the return value is true if write succeed, else false
        */
        bool write( char ch );


        /** Write 4 bytes int data to this data stream, the data in this stream is Little Endian
		*   In little endian CPU system:
		*		char* pc = &i;
		*		pc[0] -> m_pData[0]
		*		pc[1] -> m_pData[1]
		*		pc[2] -> m_pData[2]
		*		pc[3] -> m_pData[3]
		*   In big endian CPU system:
		*		char* pc = &i;
		*		pc[3] -> m_pData[0]
		*		pc[2] -> m_pData[1]
		*		pc[1] -> m_pData[2]
		*		pc[0] -> m_pData[3]
        *  @param  i : the int which will be written
        *  @return the return value is true if write succeed, else false
        */
		bool writele( u32 i );

        /** write data to data stream
        *  @param  buf: the buffer which the data will be written
        *  @param  buf_len: the buf length in byte
        *  @note   the return value is true if read succeed, else false
        */
        bool write( const void* buf, u32 buf_len );

        /** move the stream pointer for read
        *  @remark   after seek, the read pointer' position is at the stream buffer' base address + start + offset,
        *  or at the stream buffer' base address if the result is lesser than the base address
        *  or at the end of stream buffer if the result exceeded the end
        *
        *  @param  start: the position where the pointer will moving
        *  @param  offset: the offset to move
        */
        u32 seekg( s32 offset );

        /** get current read position   */
        u32 tellg()const;

        /** move the stream pointer for write
        *  @remark   after seek, the write pointer' position is at the stream buffer' base address + start + offset,
        *  or at the stream buffer' base address if the result is lesser than the base address
        *  or at the end of stream buffer if the result exceeded the end
        *
        *  @param  offset: the offset to move
        *		if offset < 0, this function doesn't case about m_nSize
        */
        u32 seekp( s32 offset );

        /** get current write position   */
        u32 tellp()const;


        /** Sets the capacity of the stream to at least size,
        * performing the same role as the <code>reserve(u32 size)</code>  function.  
        * the stream's data buffer maybe extend. 
        * \warning The old interface, the same as <code>reserve(u32 size)</code> 
        *  @return false if failed to allocate enough memory 
        *    and set the reading and writing flag as S_READ_BAD and S_WRITE_BAD
        */
        bool setBufferSize( u32 size );

        /** Sets the capacity of the stream to at least size,
        *   the stream's data buffer maybe extend.
        *  @note It will not change any flag of the stream if successfully
        *        
        *  @return false if failed to allocate enough memory 
        *    and set the reading and writing flag as S_READ_BAD and S_WRITE_BAD
        */
        bool reserve( u32 size );

        /**
        *	Sets new size for the file.
        * @param nSize, the new size
        * @return false if failed to allocate enough memory.
        */
        bool setSize( u32 nSize );

        /** get the length of data in byte   */
        u32 getSize() const;
        u32 size() const { return getSize(); }

        /** get the buffer base address pointer,  don't delete the returned pointer	*/
        void* getCache() const;
        const char* data() const { return reinterpret_cast<const char*>(getCache()); }

        //! return the char at the index of the data stream
        u8 charAt( u32 index ) const;

        /// Helper methods used to accelerate read/write

        /** Gets size of data that can read from the current read position. */
        u32 getReadableSize() const;

        /** Gets buffer pointer to the current read position. */
        void* getCurReadBuffer() const;
        void* getCurWriteBuffer() const;

        //! Reset the data stream
        void reset();

        void swap( MemoryDataStream& r );

    public:
        /** Store data to the stream.It can be generalized. */
        template< typename T>
        MemoryDataStream& operator<<( const T& val );

        /** Get data from the stream. */
        template< typename T>
        MemoryDataStream& operator>>( T& val );

        /** Write string to the stream */
        MemoryDataStream& operator << ( const std::string& val );

        /** Write string to the stream. */
        MemoryDataStream& operator << ( const char* szVal );

        /** Write string from the stream.
        *  @warning The source stream MUST be a write type, so put operation is expected
        *           before call the method.
        *  @param val  Source stream to read data from. It MUST be a input type of stream.
        */
        MemoryDataStream& operator << ( const MemoryDataStream& val );

        //! Write simple vector. which is consecutive memory.
        template<typename _Kt >
        void writeSimpleVector( const std::vector<_Kt>& val );

        //! Write sequence to the stream
        template< typename _Kt >
        MemoryDataStream& operator << ( const std::vector< _Kt >& val );

        //! Write sequence to the stream
        template< typename _Kt>
        MemoryDataStream& operator << ( const std::list< _Kt >& val );
        template<  typename _Kt, typename _Val >
        MemoryDataStream& operator << ( const std::pair<_Kt, _Val>& val );
        template<  typename _Kt, typename _Val >
        MemoryDataStream& operator >> ( std::pair<_Kt, _Val>& val );

        //! Write map to the stream
        template<  typename _Kt, typename _Val >
        MemoryDataStream& operator << ( const std::map< _Kt, _Val >& val );

        //! Write map to the stream
        template<  typename _Kt >
        MemoryDataStream& operator << ( const std::set< _Kt >& val );



        /** Read string from the stream */
        MemoryDataStream& operator >> ( std::wstring& val );

        /** Read string from the stream */
        MemoryDataStream& operator >> ( std::string& val );

        /** Read string from the stream */
        MemoryDataStream& operator >> ( MemoryDataStream& val );

        //! Read simple vector. which is consecutive memory.
        template< typename _Kt >
        void readSimpleVector( std::vector< _Kt >& val );

        //! Read sequence from the stream
        template< typename _Kt >
        MemoryDataStream& operator >> ( std::vector< _Kt >& val );


        //! Read sequence from the stream
        template< typename _Kt >
        MemoryDataStream& operator >> ( std::list< _Kt >& val );

        //! Read map from the stream
        template< typename _Kt, typename _Val >
        MemoryDataStream& operator >> ( std::map<_Kt, _Val >& val );

        //! Read set from the stream
        template< typename _Kt >
        MemoryDataStream& operator >> ( std::set<_Kt >& val );


        //! Append size of memory to the current stack.
        //! \return false if failed to allocate new memory.
        bool appendSize( u32 nSizeToAdd );

    private:

        template< typename T>
        MemoryDataStream& InternalWriteType( const T& val )
        {
            write( &val, sizeof( T ) );
            return ( *this );
        }

        template< typename T>
        MemoryDataStream& InternalReadType( T& val )
        {
            read( &val, sizeof( T ) );
            return ( *this );
        }

        template< typename _Kt >
        MemoryDataStream& InternalReadVector( std::vector< _Kt >& val )
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

        template< typename _Kt >
        inline MemoryDataStream& InternalWrite( const std::vector< _Kt >& val )
        {
            writeSimpleVector( val );
            return *this;
        }

    private:

        u8*                      m_pData;   //! Buffer to hold all the data.It can
        //! expand when it is wrote and is not
        //! long enough to hold more data.
        bool               m_bSelfCreate;	//! Whether the instance create buffer itself.

        u32                m_nSizeBuffer;   //! Size of m_pData.

        u32                  m_nPosWrite;	//! Current write data cursor in the buffer.

        u32                   m_nPosRead;   //! Current read data cursor in the buffer.

        u32                      m_nSize;   //! Get end position of write, it will not be affected
        //! by seekp(...)
        //! If open a new file, it will be m_nSize
        u32                    m_nStates;   //! status of the file.

    private:
        //! Hide copy constructor
        MemoryDataStream( const MemoryDataStream& );
        MemoryDataStream& operator= ( const MemoryDataStream& );
    };


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
    inline npp::MemoryDataStream& operator<< ( npp::MemoryDataStream& file, const Struct2Element<TE1, TE2 >& val )
    {
        file << ( const TE1& )val.v1
            << ( const TE2& )val.v2;

        return file;
    }

    // Serialize Struct2Element
    template<typename TE1, typename TE2 >
    inline npp::MemoryDataStream& operator>> ( npp::MemoryDataStream& file,  Struct2Element<TE1, TE2 >& val )
    {
        file >> ( TE1& )val.v1
            >> ( TE2& )val.v2;

        return file;
    }


    //-------------------------------------------------------
    // Serialize Struct2Element
    template<typename TE1, typename TE2, typename TE3 >
    inline npp::MemoryDataStream& operator<< ( npp::MemoryDataStream& file, const Struct3Element<TE1, TE2, TE3 >& val )
    {
        file << ( const TE1& )val.v1
            << ( const TE2& )val.v2
            << ( const TE3& )val.v3;
        return file;
    }

    // Serialize Struct2Element
    template<typename TE1, typename TE2, typename TE3 >
    inline npp::MemoryDataStream& operator>> ( npp::MemoryDataStream& file,  Struct3Element<TE1, TE2, TE3 >& val )
    {
        file >> ( TE1& )val.v1
            >> ( TE2& )val.v2
            >> ( TE3& )val.v3;
        return file;
    }

    //-------------------------------------------------------
    template<typename TE1, typename TE2, typename TE3, typename TE4 >
    inline npp::MemoryDataStream& operator<< ( npp::MemoryDataStream& file, const Struct4Element<TE1, TE2, TE3, TE4 >& val )
    {
        file << ( const TE1& )val.v1
            << ( const TE2& )val.v2
            << ( const TE3& )val.v3
            << ( const TE4& )val.v4;
        return file;
    }

    template<typename TE1, typename TE2, typename TE3, typename TE4 >
    inline npp::MemoryDataStream& operator>> ( npp::MemoryDataStream& file,  Struct4Element<TE1, TE2, TE3, TE4 >& val )
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
    inline MemoryDataStream::MemoryDataStream( npp::u8* pData, int nBufferSize, bool bDestroy )
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
            H_FREE(m_pData);
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

    inline npp::u32 MemoryDataStream::seekg( s32 offset )
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

    inline npp::u32 MemoryDataStream::tellg() const
    {
        return m_nPosRead;
    }

    inline npp::u32 MemoryDataStream::seekp( s32 offset )
    {
        s32 nNewPos = (npp::s32)m_nPosWrite + offset;

        if ( nNewPos < 0 )
        {
            m_nPosWrite = 0;
        }
        else
        {
            // pre-allocate size.
            if ( nNewPos > (npp::s32)m_nSize )
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

    inline npp::u32 MemoryDataStream::getSize() const
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

    inline npp::u32 MemoryDataStream::getReadableSize() const
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

    inline void MemoryDataStream::reset()
    {
        m_nPosWrite = m_nPosRead = m_nSize = m_nStates = 0;
    }

    inline MemoryDataStream& MemoryDataStream::operator<<( const std::string& val )
    {
        u32 nStrLen = ( u32 )val.length() ;

        // 1. write string length
        *this << ( u32& )nStrLen;

        // 2. write string
        write( val.c_str(), ( u32 )nStrLen );

        return *this;
    }

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


    inline MemoryDataStream& MemoryDataStream::operator>>( std::string& val )
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
                H_FREE(m_pData);
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
                H_FREE(m_pData);
            }


            m_pData = pNewBuf;
            m_bSelfCreate = true;
        }

        return true;
    }

    template< typename T>
    inline MemoryDataStream& MemoryDataStream::operator<<( const T& val )
    {
        return InternalWriteType( val );
    }

    template<typename _Kt>
    inline void MemoryDataStream::writeSimpleVector( const std::vector<_Kt>& val )
    {
        // 1. write length
        *this << ( u32 )val.size();

        // 2. memory
        if ( !val.empty() )
        {
            this->write( &( val[0] ), ( npp::u32 )sizeof( _Kt ) * val.size()  );
        }
    }


    template< typename T>
    inline MemoryDataStream& MemoryDataStream::operator>>( T& val )
    {
        return InternalReadType( val );
    }

    template<  typename _Kt, typename _Val >
    inline MemoryDataStream& MemoryDataStream::operator>>( std::pair<_Kt, _Val>& val )
    {
        ( *this ) >> val.first >> val.second;
        return *this;
    }

    template< typename _Kt >
    inline MemoryDataStream& MemoryDataStream::operator<<( const std::vector< _Kt >& val )
    {
        // 1. write length
        //typedef  typename stdext::bool_type<stdext::is_pod<_Kt>::value>::type _Kt_type;
        return InternalWrite( val );
    }

    template< typename _Kt >
    inline MemoryDataStream& MemoryDataStream::operator<<( const std::list< _Kt >& val )
    {
        // 1. write length
        *this << ( u32 )val.size();

        typedef typename std::list<_Kt>::const_iterator ConstIterator;
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

    template<  typename _Kt, typename _Val >
    inline MemoryDataStream& MemoryDataStream::operator<<( const std::map< _Kt, _Val >& val )
    {
        // 1. write length
        *this << ( u32 )val.size();

        // 2. elements.
        typedef typename std::map<_Kt, _Val >::const_iterator ConstIterator;
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


    template< typename _Kt, typename _Val >
    inline MemoryDataStream& MemoryDataStream::operator>>( std::map<_Kt, _Val >& val )
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

    template< typename _Kt >
    inline MemoryDataStream& MemoryDataStream::operator>>( std::list< _Kt >& val )
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

    template< typename _Kt >
    inline void MemoryDataStream::readSimpleVector( std::vector< _Kt >& val )
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

    template< typename _Kt >
    inline MemoryDataStream& MemoryDataStream::operator>>( std::vector< _Kt >& val )
    {
        return InternalReadVector( val );
    }

    template<class T>
    inline MemoryDataStream& MemoryDataStream::operator<<( const std::set<T>& val )
    {
        ( *this ) << ( npp::u32 )val.size();

        typedef typename std::set<T>::const_iterator Iterator;
        Iterator end = val.end();

        for ( Iterator i = val.begin() ; i != end ; ++i )
        {
            ( *this ) << ( *i );
        }

        return  ( *this );
    }

    template<class T>
    inline MemoryDataStream& MemoryDataStream::operator>>( std::set<T>& val )
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

}//end of namespace npp


namespace std
{
    inline void swap( npp::MemoryDataStream& l , npp::MemoryDataStream& r )
    {
        l.swap( r );
    }
}


#endif	//_NDATASTREAM_H
