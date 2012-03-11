#include "osl/include/inner_pre.h"
#include "osl/include/ring_buffer.h"
#include "osl/include/atomic_op.h"

#ifdef H_OS_WINDOWS
#	include "emmintrin.h"
#endif

namespace osl
{
    RingBuffer::RingBuffer( int numPtrs ) : max_element_count_( numPtrs )
#ifdef H_USING_MY_COUNTINT
        , size_( 0 )
#endif
    {
        internal_ring_buffer_ = NULL;
        data_buffer_ = NULL;
        max_element_count_ = convert2pow( max_element_count_ );

        if ( init() != -1 )
        {
            initialized_ = true;
        }
        else
        {
            destroy();
            initialized_ = false;
        }
    }

    RingBuffer::~RingBuffer()
    {
        destroy();
    }

    long RingBuffer::init()
    {
        if ( ( ( max_element_count_ - 1 ) & max_element_count_ ) != 0 )
        {
            return -1;    //must power of 2
        }

        size_t nDataBufferSize = max_element_count_ * sizeof( void* );
        if ( !data_buffer_ )
        {
#ifdef H_USING_OSLIB_MEM_ALLOC
            data_buffer_ = ( char* )OSLib::MemAlloc::alloc( nDataBufferSize, "RingBuffer_databuf", __FILE__ , __LINE__ );
#else
            data_buffer_ = ( char* )malloc( nDataBufferSize );
#endif
        }

        if ( !internal_ring_buffer_ )
        {
#ifdef H_USING_OSLIB_MEM_ALLOC
            internal_ring_buffer_ = ( struct InternalRingBuffer* )OSLib::MemAlloc::alloc( sizeof( InternalRingBuffer ), "RingBuffer_Node", __FILE__ , __LINE__ );
#else
            internal_ring_buffer_ = ( struct InternalRingBuffer* )malloc( sizeof( InternalRingBuffer ) );
#endif
        }

        return initRingBuffer( internal_ring_buffer_, nDataBufferSize, data_buffer_ );
    }

    void RingBuffer::destroy()
    {
        if ( data_buffer_ )
        {
#ifdef H_USING_OSLIB_MEM_ALLOC
            OSLib::MemAlloc::free( data_buffer_ );
#else
            free( data_buffer_ );
#endif
            data_buffer_ = NULL;
        }

        if ( internal_ring_buffer_ )
        {
#ifdef H_USING_OSLIB_MEM_ALLOC
            OSLib::MemAlloc::free( internal_ring_buffer_ );
#else
            free( internal_ring_buffer_ );
#endif
            internal_ring_buffer_ = NULL;
        }
    }

    int RingBuffer::convert2pow( int nNum )
    {
        nNum = nNum > kMaxElementNum ? kMaxElementNum : nNum;
        nNum = nNum < kMinElementNum ? kMinElementNum : nNum;

        if ( ( ( nNum - 1 ) & nNum ) == 0 )
        {
            return nNum;
        }

        int n = kMinElementNum;

        while ( nNum > n )	//loop less than 16
        {
            n = n << 1;
        }

        return n;
    }

    //should thread 1 write,thread 2 read
    bool RingBuffer::push_back( void* pPtr )
    {
        //		long lPtr = ( long )pPtr;
        if ( writeRingBuffer( internal_ring_buffer_, &pPtr, sizeof( long ) ) > 0 )
        {
#ifdef H_USING_MY_COUNTINT
            InterlockedInc32( &size_ );
#endif
            return true;
        }

        return false;
    }

    //should thread 1 write,thread 2 read
    void* RingBuffer::pop_front()
    {
        long lPtr = 0;

        if ( readRingBuffer( internal_ring_buffer_, &lPtr, sizeof( long ) ) == sizeof( long ) )
        {
#ifdef H_USING_MY_COUNTINT
            InterlockedDec32( &size_ );
#endif
            return ( void * ) lPtr;
        }
        else
        {
            return NULL;
        }
    }

    /** Initialize Ring Buffer.
    *
    *  @param pBuf The ring buffer.
    *
    *  @param numBytes The number of pointers in the buffer and must be power of 2.
    *
    *  @param buffer A pointer to a previously allocated area where the pointers
    *     will be maintained.  It must be numBytes long.
    *
    *  @return -1 if numBytes is not a power of 2, otherwise 0.
    */
    long RingBuffer::initRingBuffer( struct InternalRingBuffer* pBuf, long numBytes, void* buffer )
    {
        if ( ( ( numBytes - 1 ) & numBytes ) != 0 )
        {
            return -1;    //not power of 2
        }

        pBuf->bufferSize = numBytes;
        pBuf->buffer = ( char* )buffer;
        flushRingBuffer( pBuf );
        pBuf->bigMask = ( numBytes * 2 ) - 1;
        pBuf->smallMask = ( numBytes ) - 1;
        return 0;
    }

    void RingBuffer::flushRingBuffer( struct InternalRingBuffer* pBuf )
    {
        pBuf->writeIndex = pBuf->readIndex = 0;
    }

    long RingBuffer::getRingBufferWriteAvailable( InternalRingBuffer* pBuf )
    {
        return ( pBuf->bufferSize - getRingBufferReadAvailable( pBuf ) );
    }

    long RingBuffer::getRingBufferReadAvailable( InternalRingBuffer* pBuf )
    {
        mb();
        return ( ( pBuf->writeIndex - pBuf->readIndex ) & pBuf->bigMask );
    }

    long RingBuffer::getRingBufferWriteRegions( InternalRingBuffer* pBuf, long numBytes,
        void **dataPtr1, long *sizePtr1,
        void **dataPtr2, long *sizePtr2 )
    {
        long   index;
        long   available = getRingBufferWriteAvailable( pBuf );

        if ( numBytes > available )
        {
            numBytes = available;
        }

        /* Check to see if write is not contiguous. */
        index = pBuf->writeIndex & pBuf->smallMask;

        if ( ( index + numBytes ) > pBuf->bufferSize )
        {
            /* Write data in two blocks that wrap the buffer. */
            long   firstHalf = pBuf->bufferSize - index;
            *dataPtr1 = &pBuf->buffer[index];
            *sizePtr1 = firstHalf;
            *dataPtr2 = &pBuf->buffer[0];
            *sizePtr2 = numBytes - firstHalf;
        }
        else
        {
            *dataPtr1 = &pBuf->buffer[index];
            *sizePtr1 = numBytes;
            *dataPtr2 = NULL;
            *sizePtr2 = 0;
        }

        return numBytes;
    }

    long RingBuffer::writeRingBuffer( InternalRingBuffer* pBuf, const void *data, long numBytes )
    {
        long size1, size2, numWritten;
        void *data1, *data2;
        numWritten = getRingBufferWriteRegions( pBuf, numBytes, &data1, &size1, &data2, &size2 );

        if ( size2 > 0 )
        {

            memcpy( data1, data, size1 );
            data = ( ( char * )data ) + size1;
            memcpy( data2, data, size2 );
        }
        else
        {
            memcpy( data1, data, size1 );
        }

        advanceRingBufferWriteIndex( pBuf, numWritten );
        return numWritten;
    }

    long RingBuffer::getRingBufferReadRegions( InternalRingBuffer* pBuf, long numBytes,
        void **dataPtr1, long *sizePtr1,
        void **dataPtr2, long *sizePtr2 )
    {
        long   index;
        long   available = getRingBufferReadAvailable( pBuf );

        if ( numBytes > available )
        {
            numBytes = available;
        }

        /* Check to see if read is not contiguous. */
        index = pBuf->readIndex & pBuf->smallMask;

        if ( ( index + numBytes ) > pBuf->bufferSize )
        {
            /* Write data in two blocks that wrap the buffer. */
            long firstHalf = pBuf->bufferSize - index;
            *dataPtr1 = &pBuf->buffer[index];
            *sizePtr1 = firstHalf;
            *dataPtr2 = &pBuf->buffer[0];
            *sizePtr2 = numBytes - firstHalf;
        }
        else
        {
            *dataPtr1 = &pBuf->buffer[index];
            *sizePtr1 = numBytes;
            *dataPtr2 = NULL;
            *sizePtr2 = 0;
        }

        return numBytes;
    }

    long RingBuffer::readRingBuffer( InternalRingBuffer* pBuf, void *data, long numBytes )
    {
        long size1, size2, numRead;
        void *data1, *data2;
        numRead = getRingBufferReadRegions( pBuf, numBytes, &data1, &size1, &data2, &size2 );

        if ( size2 > 0 )
        {
            memcpy( data, data1, size1 );
            data = ( ( char * )data ) + size1;
            memcpy( data, data2, size2 );
        }
        else
        {
            memcpy( data, data1, size1 );
        }

        advanceRingBufferReadIndex( pBuf, numRead );
        return numRead;
    }

    long RingBuffer::advanceRingBufferReadIndex( InternalRingBuffer* pBuf, long numBytes )
    {
        /* we need to ensure that previous writes are always seen before updating the index. */
        mb();
        return pBuf->readIndex = ( pBuf->readIndex + numBytes ) & pBuf->bigMask;
    }

    long RingBuffer::advanceRingBufferWriteIndex( InternalRingBuffer* pBuf, long numBytes )
    {
        /* we need to ensure that previous writes are seen before we update the write index */
        mb();
        return pBuf->writeIndex = ( pBuf->writeIndex + numBytes ) & pBuf->bigMask;
    }

};//namespace
