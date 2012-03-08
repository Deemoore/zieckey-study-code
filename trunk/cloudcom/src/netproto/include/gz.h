#ifndef _NETPROTO_GZIP_WRAPPER_H_
#define _NETPROTO_GZIP_WRAPPER_H_

#include "netproto/include/inner_pre.h"

#ifdef H_NPP_PROVIDE_ZLIB

#include "netproto/include/compressor.h"

namespace npp
{
#if 0
    /*
    Well that's nice, but how do I make a gzip file in memory?
        You can request that deflate write the gzip format instead of the zlib format using deflateInit2(). You can also request that inflate decode the gzip format using inflateInit2(). Read zlib.h for more details.
        Note that you cannot specify special gzip header contents (e.g. a file name or modification date), nor will inflate tell you what was in the gzip header. If you need to customize the header or see what's in it, you can use the raw deflate and inflate operations and the crc32() function and roll your own gzip encoding and decoding. Read the gzip RFC 1952 for details of the header and trailer format. 
        */
    class _EXPORT_NETPROTO GZip : public Compressor
    {//TODO need Add 4byte length of leading
    public:
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
        static int Compress(const void* source, size_t sourceLen, void* dest, size_t* destLen);
        //static int Compress(const void* source, size_t sourceLen, std::string& dest);

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
        //static int Uncompress(const void* source, size_t sourceLen, std::string& dest);

        /*
        GetUncompressBound() returns an upper bound on the uncompressed size after
        Uncompress() on sourceLen bytes.  It would be used before
        a Uncompress() call to allocate the destination buffer.
        */
        static size_t GetUncompressBound(const void* compressed_data);
    }; 

#endif

}//end of namespace npp
#endif

#endif

