#ifndef _NETPROTO_ZLIB_WRAPPER_H_
#define _NETPROTO_ZLIB_WRAPPER_H_

#include "netproto/include/inner_pre.h"

#ifdef H_NPP_PROVIDE_ZLIB

#include "netproto/include/compressor.h"

namespace npp
{
    class _EXPORT_NETPROTO ZLib : public Compressor
    {
    public:
        ZLib() {}
        virtual ~ZLib() {}

        virtual bool Compress(const void* data, size_t data_len, std::string& compresed_data);
        virtual bool Uncompress(const void* data, size_t data_len, std::string& uncompresed_data);

        /*
        Compresses the source buffer into the destination buffer.  sourceLen is
        the byte length of the source buffer. Upon entry, destLen is the total
        size of the destination buffer, which must be at least the value returned
        by GetCompressBound(sourceLen). Upon exit, destLen is the actual size of the
        compressed buffer.
        This function can be used to compress a whole file at once if the
        input file is mmap'ed.
        compress returns Z_OK if success, Z_MEM_ERROR if there was not
        enough memory, Z_BUF_ERROR if there was not enough room in the output
        buffer.
        */
        static int Compress(const void* source, size_t sourceLen, void* dest, size_t* destLen, int level = ZZ_BEST_SPEED);

        /*
        GetCompressBound() returns an upper bound on the compressed size after
        Compress() on sourceLen bytes.  It would be used before
        a Compress() call to allocate the destination buffer.
        */
        static size_t GetCompressBound(size_t sourceLen);
        
        /*
        Decompresses the source buffer into the destination buffer.  sourceLen is
        the byte length of the source buffer. Upon entry, destLen is the total
        size of the destination buffer,which must be at least the value returned
        by GetUncompressBound(sourceLen)
        Upon exit, destLen is the actual size of the uncompressed buffer.
        This function can be used to decompress a whole file at once if the
        input file is mmap'ed.

        uncompress returns Z_OK if success, Z_MEM_ERROR if there was not
        enough memory, Z_BUF_ERROR if there was not enough room in the output
        buffer, or Z_DATA_ERROR if the input data was corrupted or incomplete.
        */
        static int Uncompress(const void* source, size_t sourceLen, void* dest, size_t* destLen);

        /*
        GetUncompressBound() returns an upper bound on the uncompressed size after
        Uncompress() on sourceLen bytes.  It would be used before
        a Uncompress() call to allocate the destination buffer.
        */
        static size_t GetUncompressBound(const void* compressed_data);
    };

}//end of namespace npp
#endif

#endif

