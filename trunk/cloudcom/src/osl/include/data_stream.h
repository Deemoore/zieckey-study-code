#ifndef _OSLIB_DATASTREAM_H_
#define _OSLIB_DATASTREAM_H_

#include "osl/include/platform_micros.h"
#include "osl/include/object.h"
#include "osl/include/string_ext.h"

namespace osl
{

    //! The class encapsulates data stream in memory.
    class _EXPORT_OSLIB MemoryDataStream : public Object
    {
        H_ALLOC_OBJECT( MemoryDataStream )
    public:
        //!
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
        explicit MemoryDataStream( osl::u8* pData, int nBufferSize, bool bDestroy );

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
        //! \param nBits - S_WRITE_BAD or S_READ_BAD or 0 or S_WRITE_BAD|S_READ_BAD
        void setStates( unsigned int nBits );

        //! \warning deprecated interface, please use 
        //!     <code>readRawFile(const std::string& strFileName)</code> instead
        //! Open raw file and read all the file data to this memory data stream
        //! \note It is only a helper method. path splitter should be "/"
        bool openRawFile( const StringA& strFileName );

        //! Open the raw file and read all the file data to this memory data stream
        //! \note It is only a helper method. path splitter should be "/"
        bool readRawFile( const StringA& strFileName );

        //! \brief: Helper method to save data to a disk file. path splitter should be "/"
        //! \param[in]: const StringA & strFilePathName, the path name of the file, it can include dir path
        //! \return: bool
        bool saveToFile( const StringA& strFilePathName );


        /** read data form data stream, the result is in buf
        *  @remark The read count is in len,it may be lesser than the buf_len,
        *          the len will be zero if read nothing or there is an error occurred
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

        /** write a value to data stream
        *  @param  v: the value which will be written
        *  @note   the return value is true if write succeed, else false
        */
        bool write( int8_t  ch );
//         bool write( int16_t i );
//         bool write( int32_t i );
//         bool write( int64_t i );
//         bool write( uint8_t  ch );
//         bool write( uint16_t i );
//         bool write( uint32_t i );
//         bool write( uint64_t i );
//         bool write( f32 f );
//         bool write( f64 d );

//         template<typename _T>
//         bool append(const _T& v) { return write(v); }

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
        *  @param  buf: the buffer where stored the data to be written to the stream
        *  @param  buf_len: the buf length in byte
        *  @note   the return value is true if read succeed, else false
        */
        bool write( const void* buf, u32 buf_len );

        /**
         * Calling <code>write(v, strlen(v))</code>
         */
        bool append(const char* v) { return write(v, strlen(v)); }

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

        //! \warning 废弃的接口，请使用 <code>reset()</code>
        //! Close the data stream.
        void close();

        //! Reset the data stream
        void reset();

        void swap( MemoryDataStream& r );

    private:
        template< typename T>
        MemoryDataStream& InternalWriteType( const T& val , stdext::true_type );

        //! \brief 不要给这个函数增加实现
        template< typename T>
        MemoryDataStream& InternalWriteType( const T& val , stdext::false_type );

        template< typename T>
        MemoryDataStream& InternalReadType( T& val , stdext::true_type );

        //! \brief 不要给这个函数增加实现
        template< typename T>
        MemoryDataStream& InternalReadType( T& val , stdext::false_type );
    public:
        /** Store data to the stream.It can be generalized. */
        template< typename T>
        MemoryDataStream& operator<<( const T& val );

        /** Get data from the stream. */
        template< typename T>
        MemoryDataStream& operator>>( T& val );
        /** Get data from the stream. */
        template< typename T>
        MemoryDataStream& operator>>( osl::RefPtr<T>& val );

        template< typename T>
        MemoryDataStream& operator<<( const osl::RefPtr<T>& val );

		/** Get data from the stream. */
		MemoryDataStream& operator>>( osl::RefPtr<MemoryDataStream>& val );
		MemoryDataStream& operator<<( const osl::RefPtr<MemoryDataStream>& val );

        /** Write string to the stream */
        MemoryDataStream& operator<< ( const StringW& val );

        /** Write string to the stream */
#ifndef H_STD_STRING
        MemoryDataStream& operator << ( const StringW::_BaseType& val );
#endif

        /** Write string to the stream. */
        MemoryDataStream& operator << ( const wchar_t* szVal );

        /** Write string to the stream */
        MemoryDataStream& operator << ( const StringA& val );

        /** Write string to the stream */
#ifndef H_STD_STRING
        MemoryDataStream& operator << ( const StringA::_BaseType& val );
#endif

        /** Write string to the stream. */
        MemoryDataStream& operator << ( const char* szVal );

        /** Write string from the stream.
        *  @warning The source stream MUST be a write type, so put operation is expected
        *           before call the method.
        *  @param val  Source stream to read data from. It MUST be a input type of stream.
        */
        MemoryDataStream& operator << ( const MemoryDataStream& val );

        //! Write simple vector. which is consecutive memory.
        template<typename _Kt, typename _ContainerName >
        void writeSimpleVector( const Vector<_Kt, _ContainerName>& val );

        template< typename _Kt, typename _ContainerName  >
        MemoryDataStream& InternalWrite( const Vector< _Kt, _ContainerName >& val, stdext::true_type );
        template< typename _Kt, typename _ContainerName >
        MemoryDataStream& InternalWrite( const Vector< _Kt, _ContainerName >& val, stdext::false_type );

        //! Write sequence to the stream
        template< typename _Kt, typename _ContainerName >
        MemoryDataStream& operator << ( const Vector< _Kt, _ContainerName >& val );

        //! Write sequence to the stream
        template< typename _Kt, typename _ContainerName>
        MemoryDataStream& operator << ( const List< _Kt, _ContainerName >& val );
        template<  typename _Kt, typename _Val >
        MemoryDataStream& operator << ( const std::pair<_Kt, _Val>& val );
        template<  typename _Kt, typename _Val >
        MemoryDataStream& operator >> ( std::pair<_Kt, _Val>& val );

        //! Write map to the stream
        template<  typename _Kt, typename _Val, typename _ContainerName >
        MemoryDataStream& operator << ( const Map< _Kt, _Val, _ContainerName >& val );

        //! Write map to the stream
        template<  typename _Kt, typename _Val, typename _ContainerName >
        MemoryDataStream& operator << ( const HashMap< _Kt, _Val, _ContainerName >& val );

        //! Write map to the stream
        template<  typename _Kt, typename _ContainerName >
        MemoryDataStream& operator << ( const Set< _Kt, _ContainerName >& val );





        /** Read string from the stream */
        MemoryDataStream& operator >> ( StringW& val );

        /** Read string from the stream */
        MemoryDataStream& operator >> ( StringA& val );

        /** Read string from the stream */
        MemoryDataStream& operator >> ( MemoryDataStream& val );


        //! Read simple vector. which is consecutive memory.
        template< typename _Kt, typename _ContainerName >
        void readSimpleVector( Vector< _Kt, _ContainerName >& val );

        template< typename _Kt, typename _ContainerName >
        MemoryDataStream&  InternalReadVector( Vector< _Kt, _ContainerName >& val , stdext::true_type );

        template< typename _Kt, typename _ContainerName >
        MemoryDataStream&  InternalReadVector( Vector< _Kt, _ContainerName >& val , stdext::false_type );

        //! Read sequence from the stream
        template< typename _Kt, typename _ContainerName >
        MemoryDataStream& operator >> ( Vector< _Kt, _ContainerName >& val );


        //! Read sequence from the stream
        template< typename _Kt, typename _ContainerName >
        MemoryDataStream& operator >> ( List< _Kt, _ContainerName >& val );

        //! Read map from the stream
        template< typename _Kt, typename _Val, typename _ContainerName >
        MemoryDataStream& operator >> ( Map<_Kt, _Val, _ContainerName >& val );

        //! Read map from the stream
        template< typename _Kt, typename _Val, typename _ContainerName >
        MemoryDataStream& operator >> ( HashMap<_Kt, _Val, _ContainerName >& val );


        //! Read set from the stream
        template< typename _Kt, typename _ContainerName >
        MemoryDataStream& operator >> ( Set<_Kt, _ContainerName >& val );


        //! Append size of memory to the current stack.
        //! \return false if failed to allocate new memory.
        bool appendSize( u32 nSizeToAdd );

		//friend bool isContentEquals( const MemoryDataStream& first, const MemoryDataStream& first );

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

	typedef osl::RefPtr<MemoryDataStream> MemoryDataStreamPtr;

    //
    H_DEF_VECTOR( MemoryDataStreamPtr, MemoryDataStreamPtrVector );
};


#include "osl/include/data_stream.inl.h"

#endif	//_NDATASTREAM_H
