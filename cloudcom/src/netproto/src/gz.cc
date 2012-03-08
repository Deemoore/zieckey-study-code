#include "netproto/include/gz.h"

#ifdef H_NPP_PROVIDE_ZLIB

#include <zlib/zlib.h>

namespace npp
{
    //---------------------------------------------------------
    //---------------------------------------------------------
    namespace
    {
        /* ===========================================================================
        Compresses the source buffer into the destination buffer. The level
        parameter has the same meaning as in deflateInit.  sourceLen is the byte
        length of the source buffer. Upon entry, destLen is the total size of the
        destination buffer, which must be at least 0.1% larger than sourceLen plus
        12 bytes. Upon exit, destLen is the actual size of the compressed buffer.

        compress2 returns Z_OK if success, Z_MEM_ERROR if there was not enough
        memory, Z_BUF_ERROR if there was not enough room in the output buffer,
        Z_STREAM_ERROR if the level parameter is invalid.
        */
        int gz_compress2 (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level)
        {
            z_stream stream;
            int err;

            stream.next_in = (Bytef*)source;
            stream.avail_in = (uInt)sourceLen;
#ifdef MAXSEG_64K
            /* Check for source > 64K on 16-bit machine: */
            if ((uLong)stream.avail_in != sourceLen) return Z_BUF_ERROR;
#endif
            stream.next_out = dest;
            stream.avail_out = (uInt)*destLen;
            if ((uLong)stream.avail_out != *destLen) return Z_BUF_ERROR;

            stream.zalloc = (alloc_func)0;
            stream.zfree = (free_func)0;
            stream.opaque = (voidpf)0;

            //---------------------------------------------------------
#define DEF_MEM_LEVEL 9
            int strategy = Z_HUFFMAN_ONLY;
            //---------------------------------------------------------
            //&d_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, DEFAULT_WINDOWSIZE, DEFAULT_MEMLEVEL,  Z_DEFAULT_STRATEGY
            err = deflateInit2(&stream, level, Z_DEFLATED, -MAX_WBITS, DEF_MEM_LEVEL, strategy);
            if (err != Z_OK) return err;

            err = deflate(&stream, Z_FINISH);
            if (err != Z_STREAM_END) {
                deflateEnd(&stream);
                return err == Z_OK ? Z_BUF_ERROR : err;
            }
            *destLen = stream.total_out;

            err = deflateEnd(&stream);
            return err;
        }


        int gz_uncompress (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
        {
            z_stream stream;
            int err;

            stream.next_in = (Bytef*)source;
            stream.avail_in = (uInt)sourceLen;
            /* Check for source > 64K on 16-bit machine: */
            if ((uLong)stream.avail_in != sourceLen) return Z_BUF_ERROR;

            stream.next_out = dest;
            stream.avail_out = (uInt)*destLen;
            if ((uLong)stream.avail_out != *destLen) return Z_BUF_ERROR;

            stream.zalloc = (alloc_func)0;
            stream.zfree = (free_func)0;

            err = inflateInit2(&stream, -MAX_WBITS);
            if (err != Z_OK) return err;

            err = inflate(&stream, Z_FINISH);
            if (err != Z_STREAM_END) {
                inflateEnd(&stream);
                if (err == Z_NEED_DICT || (err == Z_BUF_ERROR && stream.avail_in == 0))
                    return Z_DATA_ERROR;
                return err;
            }
            *destLen = stream.total_out;

            err = inflateEnd(&stream);
            return err;
        }

    }
#if 0
    int GZip::Compress( const void* source, size_t sourceLen, void* dest, size_t* destLen )
    {
        uLongf dest_len_inner = *destLen;
        int r = gz_compress2((Bytef*)dest, &dest_len_inner, (const Bytef*)source, sourceLen, ZZ_BEST_SPEED);
        *destLen = dest_len_inner;
        return r;
    }

    int GZip::Uncompress( const void* source, size_t sourceLen, void* dest, size_t* destLen )
    {
        uLongf dest_len_inner = *destLen;
        int r = gz_uncompress((Bytef*)dest, &dest_len_inner, (const Bytef*)source, sourceLen);
        *destLen = dest_len_inner;
        return r;
    }
#endif
}

#endif



