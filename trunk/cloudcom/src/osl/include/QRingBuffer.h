#ifndef OSLIB_RINGPTRBUFFER_H_
#define OSLIB_RINGPTRBUFFER_H_

#include "qoslib/include/QOSLibPrerequisits.h"
#include "qoslib/include/QString.h"
#include "qoslib/include/QMyOS.h"

namespace osl
{
    class _EXPORT_OSLIB RingBuffer
    {
    public:
        enum
        {
            kMinElementNum	   = 4,
            kDefaultElementNum = 8192,
            kMaxElementNum	   = 65536,
        };
    public:
        RingBuffer( int capacity = kDefaultElementNum );
        ~RingBuffer();

    public:
        //! push an element to end of the buffer
        bool push_back( void* pPtr );

        //! pop an element from the front of the buffer
        //! \return A pointer to the element or NULL if no element in the buffer
        void* pop_front();

        //! Gets element size in the queue.
        size_t size() const
        {
#ifdef H_USING_MY_COUNTINT
            return size_;
#   else
            return getRingBufferReadAvailable(internal_ring_buffer_) / sizeof( void* );
#endif
        }



    private:
        long init();
        void destroy();
        int convert2pow( int nNum );

    private:

        struct InternalRingBuffer
        {
            long   bufferSize; /* Number of bytes in FIFO. Power of 2. Set by PaUtil_InitRingBuffer. */
            long   writeIndex; /* Index of next writable byte. Set by PaUtil_AdvanceRingBufferWriteIndex. */
            long   readIndex;  /* Index of next readable byte. Set by PaUtil_AdvanceRingBufferReadIndex. */
            long   bigMask;    /* Used for wrapping indices with extra bit to distinguish full/empty. */
            long   smallMask;  /* Used for fitting indices to buffer. */
            char*  buffer;
        };

    private:
        int                        max_element_count_;
        char*                      data_buffer_;
        bool                       initialized_;
        struct InternalRingBuffer* internal_ring_buffer_;

#ifdef H_USING_MY_COUNTINT
        AtomicInt32 size_;
#endif


    private:

        /** Initialize Ring Buffer.
        @param pBuf The ring buffer.
        @param numBytes The number of bytes in the buffer and must be power of 2.
        @param dataPtr A pointer to a previously allocated area where the data
        will be maintained.  It must be numBytes long.
        @return -1 if numBytes is not a power of 2, otherwise 0.
        */
        static long initRingBuffer( struct InternalRingBuffer* pBuf, long numBytes, void* buffer );

        /** Clear buffer. Should only be called when buffer is NOT being read.
        @param pBuf The ring buffer.
        */
        static void flushRingBuffer( struct InternalRingBuffer* pBuf );

        /** Retrieve the number of bytes available in the ring buffer for writing.
        @param pBuf The ring buffer.
        @return The number of bytes available for writing.
        */
        static long getRingBufferWriteAvailable( InternalRingBuffer* pBuf );

        /** Retrieve the number of bytes available in the ring buffer for reading.
        @param pBuf The ring buffer.
        @return The number of bytes available for reading.
        */
        static long getRingBufferReadAvailable( InternalRingBuffer* pBuf );

        /** Write data to the ring buffer.
        @param pBuf The ring buffer.
        @param data The address of new data to write to the buffer.
        @param numBytes The number of bytes to be written.
        @return The number of bytes written.
        */
        static long writeRingBuffer( InternalRingBuffer* pBuf, const void *data, long numBytes );


        /** Get address of region(s) to which we can write data.
        @param pBuf The ring buffer.
        @param numBytes The number of bytes desired.
        @param dataPtr1 The address where the first (or only) region pointer will be
        stored.
        @param sizePtr1 The address where the first (or only) region length will be
        stored.
        @param dataPtr2 The address where the second region pointer will be stored if
        the first region is too small to satisfy numBytes.
        @param sizePtr2 The address where the second region length will be stored if
        the first region is too small to satisfy numBytes.
        @return The room available to be written or numBytes, whichever is smaller.
        */
        static long getRingBufferWriteRegions( InternalRingBuffer* pBuf, long numBytes,
            void **dataPtr1, long *sizePtr1,
            void **dataPtr2, long *sizePtr2 );

        /** Read data from the ring buffer.
        @param pBuf The ring buffer.
        @param data The address where the data should be stored.
        @param numBytes The number of bytes to be read.
        @return The number of bytes read.
        */
        static long readRingBuffer( InternalRingBuffer* pBuf, void *data, long numBytes );




        /** Get address of region(s) from which we can read data.
        @param pBuf The ring buffer.
        @param numBytes The number of bytes desired.
        @param dataPtr1 The address where the first (or only) region pointer will be
        stored.
        @param sizePtr1 The address where the first (or only) region length will be
        stored.
        @param dataPtr2 The address where the second region pointer will be stored if
        the first region is too small to satisfy numBytes.
        @param sizePtr2 The address where the second region length will be stored if
        the first region is too small to satisfy numBytes.
        @return The number of bytes available for reading.
        */
        static long getRingBufferReadRegions( InternalRingBuffer* pBuf, long numBytes,
            void **dataPtr1, long *sizePtr1,
            void **dataPtr2, long *sizePtr2 );

        /** Advance the write index to the next location to be written.
        @param pBuf The ring buffer.
        @param numBytes The number of bytes to advance.
        @return The new position.
        */
        static long advanceRingBufferReadIndex( InternalRingBuffer* pBuf, long numBytes );

        /** Advance the read index to the next location to be read.
        @param pBuf The ring buffer.
        @param numBytes The number of bytes to advance.
        @return The new position.
        */
        static long advanceRingBufferWriteIndex( InternalRingBuffer* pBuf, long numBytes );

    };
};


#endif	//_RINGPTRBUFFER_H
