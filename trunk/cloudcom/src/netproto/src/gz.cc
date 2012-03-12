#include "netproto/include/gz.h"

#ifdef H_NPP_PROVIDE_ZLIB

#include <zlib/zlib.h>
#include "zlib/zutil.h"

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

        void write_u32(uint32_t x, Bytef* dest)
        {
            for(int n = 0; n < 4; n++) {
                unsigned char c=(unsigned char)(x & 0xff);
                dest[n] = c;
                    x >>= 8;
            }
        }

        void read_u32(const Bytef* source, uint32_t& x)
        {

        }

        static int gz_magic[2] = {0x1f, 0x8b}; /* gzip magic header */
#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define HEAD_CRC     0x02 /* bit 1 set: header CRC present */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define RESERVED     0xE0 /* bits 5..7: reserved */
        bool check_header(const uint8_t* source, size_t source_len, uint32_t* have_read_count)
        {
#define get_byte() (source[readn++])
            int method; /* method byte */
            int flags;  /* flags byte */
            uInt len;
            int c;

            uint32_t readn = 0;

            if (source_len < 10)
            {
                return false;
            }

            /* Check the gzip magic header */
            for (len = 0; len < 2; len++) {
                c = source[readn++];
                if (c != gz_magic[len]) {
                    //                     if (len != 0) m_zstream.avail_in++, m_zstream.next_in--;
                    //                     if (c != EOF) {
                    //                         m_zstream.avail_in++, m_zstream.next_in--;
                    //                         m_transparent = 1;
                    //                     }
                    //                     m_z_err =m_zstream.avail_in != 0 ? Z_OK : Z_STREAM_END;
                    return false;
                }
            }

            method = source[readn++];
            flags = source[readn++];
            if (method != Z_DEFLATED || (flags & RESERVED) != 0) {
                return false;
            }

            /* Discard time, xflags and OS code: */
            //for (len = 0; len < 6; len++) ;
            readn += 6;
            assert(readn == 10);

            //TODO more check of the length

            if ((flags & EXTRA_FIELD) != 0) { /* skip the extra field */
                len  =  (uInt)get_byte();
                len += ((uInt)get_byte())<<8;
                /* len is garbage if EOF but the loop below will quit anyway */
                while (len-- != 0 && get_byte() != EOF) ;
            }
            if ((flags & ORIG_NAME) != 0) { /* skip the original file name */
                while ((c = get_byte()) != 0 && c != EOF) ;
            }
            if ((flags & COMMENT) != 0) {   /* skip the .gz file comment */
                while ((c = get_byte()) != 0 && c != EOF) ;
            }
            if ((flags & HEAD_CRC) != 0) {  /* skip the header crc */
                for (len = 0; len < 2; len++) (void)get_byte();
            }

            *have_read_count = readn;
            return true;
        }



    }

    int GZip::Compress( const void* source, size_t sourceLen, void* dest, size_t* destLen )
    {
        uint32_t dest_len_inner = *destLen;
        int r = gz_compress2((uint8_t*)dest, &dest_len_inner, (const uint8_t*)source, sourceLen);
        *destLen = dest_len_inner;
        return r;
    }

    int GZip::Uncompress( const void* source, size_t sourceLen, void* dest, size_t* destLen )
    {
        uint32_t dest_len_inner = *destLen;
        int r = gz_uncompress((uint8_t*)dest, &dest_len_inner, (const uint8_t*)source, sourceLen);
        *destLen = dest_len_inner;
        return r;
    }

    int GZip::gz_uncompress( uint8_t*dest, uint32_t *destLen, const uint8_t*source, uint32_t sourceLen )
    {
        z_stream stream;
        int err;

        uint32_t have_read_count = 0;
        if (!check_header(source, sourceLen, &have_read_count))
        {
            return Z_DATA_ERROR;
        }

        //4 for crc
        //4 for orginal length
        if (sourceLen < have_read_count + 4 + 4)
        {
            return Z_DATA_ERROR;
        }


        stream.next_in = (Bytef*)source + have_read_count;
        stream.avail_in = (uInt)sourceLen - have_read_count - 4 - 4;

        /* Check for source > 64K on 16-bit machine: */
        //if ((uLong)stream.avail_in != sourceLen) return Z_BUF_ERROR;

        stream.next_out = (Bytef*)dest;
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

        //TODO Check crc
        //TODO check orignal length

        err = inflateEnd(&stream);
        return err;
    }

    int GZip::gz_compress2( uint8_t*dest, uint32_t *destLen, const uint8_t*source, uint32_t sourceLen )
    {
        z_stream stream;
        int err;

        uint8_t header[10]={0x1f,0x8b,Z_DEFLATED, 0 /*flags*/, 0,0,0,0 /*time*/, 0 /*xflags*/, OS_CODE};
        memcpy(dest, header, sizeof(header));
        uint32_t writen = sizeof(header);

        stream.next_in = (Bytef*)source;
        stream.avail_in = (uInt)sourceLen;
#ifdef MAXSEG_64K
        /* Check for source > 64K on 16-bit machine: */
        if ((uLong)stream.avail_in != sourceLen) return Z_BUF_ERROR;
#endif
        stream.next_out = (Bytef*)dest + writen;
        stream.avail_out = (uInt)*destLen - writen;

        //if ((uLong)stream.avail_out != *destLen) return Z_BUF_ERROR;

        stream.zalloc = (alloc_func)0;
        stream.zfree = (free_func)0;
        stream.opaque = (voidpf)0;

        //---------------------------------------------------------
#define DEF_MEM_LEVEL 9
        int strategy = Z_HUFFMAN_ONLY;
        //---------------------------------------------------------
        //&d_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, DEFAULT_WINDOWSIZE, DEFAULT_MEMLEVEL,  Z_DEFAULT_STRATEGY
        uint32_t m_crc = crc32(0L, Z_NULL, 0);
        err = deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, -MAX_WBITS, DEF_MEM_LEVEL, strategy);
        if (err != Z_OK) return err;

        err = deflate(&stream, Z_FINISH);
        if (err != Z_STREAM_END) {
            deflateEnd(&stream);
            return err == Z_OK ? Z_BUF_ERROR : err;
        }

        writen += stream.total_out;
        m_crc = crc32(m_crc, (const Bytef *)source, sourceLen);
        write_u32(m_crc, (Bytef*)dest + writen);
        writen += 4;
        write_u32(stream.total_in, (Bytef*)dest + writen);
        writen += 4;

        *destLen = writen;

        err = deflateEnd(&stream);
        return err;
    }
}

#endif



