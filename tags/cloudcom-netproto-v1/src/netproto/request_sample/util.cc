#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zlib/zlib.h>

#include "util.h"

int zlib_compress_data(const void *in_data, size_t in_data_len, uint8_t** out_buf, size_t* out_buf_len)
{/*{{{*/
    *out_buf_len = 0;
    uLongf outbufsize = compressBound(in_data_len) + 4; 
    *out_buf = (uint8_t*)malloc((size_t)outbufsize);

    be32enc(*out_buf, (uint32_t)in_data_len);

    //compress data
    {    
        //zlib : int compress2 (Bytef *dest, uLongf *destLen,  const Bytef *source, uLong sourceLen, int level);
        uLongf destlen = outbufsize - 4; 
        Bytef* dest_buf = (Bytef*)(*out_buf + 4); 
        int retv = compress2(dest_buf, &destlen,
                (const Bytef*)in_data, (uLongf)in_data_len, Z_BEST_SPEED);
        if (retv != Z_OK) {    
            fprintf(stderr, "compress failed. retv=%d\n", retv);
            return retv;
        }

        //add the leading 4 bytes of original data length
        *out_buf_len = (size_t)(destlen + 4);

        return Z_OK;
    }
}/*}}}*/

bool zlib_compress_data( const void* in_data, size_t in_data_len, std::string& output )
{
    uint8_t* out_buf = NULL;
    size_t  out_buf_len = 0;
    int r = zlib_compress_data(in_data, in_data_len, &out_buf, &out_buf_len);
    if (r == Z_OK)
    {
        output = std::string((char*)out_buf, out_buf_len);
    }

    free(out_buf);

    return r == Z_OK;
}

int zlib_uncompress_data(const void *in_data, size_t in_data_len, uint8_t** out_buf, size_t* out_buf_len)
{/*{{{*/
    *out_buf_len = 0;
    size_t origlen = 0;

    origlen = be32dec(in_data);

    //malloc data buffer
    *out_buf = (uint8_t*)malloc((size_t)origlen + 1);

    //uncompress
    {
        //int uncompress (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
        uLongf destlen = origlen;
        int retv = uncompress((Bytef*)(*out_buf), &destlen,
                (Bytef*)in_data + 4, (uLong)in_data_len - 4);
        if (retv != Z_OK) {
            fprintf(stderr, "%s uncompress failed, orginal len=%lu, compressed data len=%lu, retv=%d\n", __FUNCTION__, origlen, in_data_len - 4, retv);
            return retv;
        }

        if (destlen != origlen) {
            fprintf(stderr, "uncompress failed, data wrong\n");
            return -1000;
        }

        *out_buf_len = destlen;
        (*out_buf)[destlen] = '\0';

        return Z_OK;
    }
}/*}}}*/

bool zlib_uncompress_data( const void* in_data, size_t in_data_len, std::string& output )
{
    uint8_t* out_buf = NULL;
    size_t  out_buf_len = 0;
    int r = zlib_uncompress_data(in_data, in_data_len, &out_buf, &out_buf_len);
    if (r == Z_OK)
    {
        output = std::string((char*)out_buf, out_buf_len);
    }

    free(out_buf);

    return r == Z_OK;
}

