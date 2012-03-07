#ifndef _UTIL_H_INCLUDED
#define _UTIL_H_INCLUDED

#include "netproto/include/inner_pre.h"

#include <string>

/** 
 * @brief Compress the data using zlib.compress arigthim
 * @param[in] const void *in_data - The data to be compressed
 * @param[in] size_t in_data_len - 
 * @param[out] out_buf - stores the uncompressed data
 * @param[out] out_buf_len - indicates the length of out_buf
 * @return Z_OK if compress success others failed
 *         Z_OK defined in <zlib/zlib.h>
 * @description
 *    The zlib_compress_data() function allocates sufficient memory for a copy of the
 *    string out_buf, does the copy, and returns a pointer to it.  The pointer may
 *    subsequently be used as an argument to the function free(3).
 */
int zlib_compress_data(const void* in_data, size_t in_data_len, uint8_t** out_buf, size_t* out_buf_len);

bool zlib_compress_data(const void* in_data, size_t in_data_len, std::string& out_buf);

/** 
 * @brief Uncompress the data using zlib.uncompress arigthim
 * @param[in] const void *in_data - The data to be uncompressed
 *            The data is using qngx_zlib_compress_data function compressed
 * @param[in] size_t in_data_len - 
 * @param[out] out_buf - stores the uncompressed data
 * @param[out] out_buf_len - indicates the length of out_buf
 * @return Z_OK if uncompress success others failed
 *         Z_OK defined in <zlib/zlib.h>
 * @description
 *    The zlib_uncompress_data() function allocates sufficient memory for a copy of the
 *    string out_buf, does the copy, and returns a pointer to it.  The pointer may
 *    subsequently be used as an argument to the function free(3).
 */
int zlib_uncompress_data(const void* in_data, size_t in_data_len, uint8_t** out_buf, size_t* out_buf_len);

bool zlib_uncompress_data(const void* in_data, size_t in_data_len, std::string& out_buf);

#ifdef __FreeBSD__
#include <sys/endian.h>
#else
static __inline uint32_t
be32dec(const void *pp)
{
    unsigned char const *p = (unsigned char const *)pp;

    return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static __inline void
be32enc(void *pp, uint32_t u)
{
    unsigned char *p = (unsigned char *)pp;

    p[0] = (u >> 24) & 0xff;
    p[1] = (u >> 16) & 0xff;
    p[2] = (u >> 8) & 0xff;
    p[3] = u & 0xff;
}
#endif

#endif
