#ifndef _NETPROTO_GZIP_WRAPPER_H_
#define _NETPROTO_GZIP_WRAPPER_H_

#include "netproto/include/inner_pre.h"

#ifdef H_NPP_PROVIDE_ZLIB

#include "netproto/include/compressor.h"

namespace npp
{
    /*
    Well that's nice, but how do I make a gzip file in memory?
        You can request that deflate write the gzip format instead of the zlib format using deflateInit2(). You can also request that inflate decode the gzip format using inflateInit2(). Read zlib.h for more details.
        Note that you cannot specify special gzip header contents (e.g. a file name or modification date), nor will inflate tell you what was in the gzip header. If you need to customize the header or see what's in it, you can use the raw deflate and inflate operations and the crc32() function and roll your own gzip encoding and decoding. Read the gzip RFC 1952 for details of the header and trailer format. 
        */
    class _EXPORT_NETPROTO GZip : public Compressor
    {
        //TODO need Add 4byte length of leading
        //TODO more comments
    public:
        virtual ~GZip() {}

        virtual bool Compress(const void* data, size_t data_len, std::string& compresed_data)
        {
            size_t dest_len_inner = GetCompressBound(data_len);
            compresed_data.resize(dest_len_inner);
            bool r = Compress(data, data_len, &compresed_data[0], &dest_len_inner);
            if (!r)
            {
                return false;
            }
            assert(dest_len_inner <= compresed_data.size());
            compresed_data.resize(dest_len_inner);
            return true;
        }

        virtual bool Uncompress(const void* data, size_t data_len, std::string& uncompresed_data)
        {
            size_t dest_len_inner = GetUncompressBound(data, data_len);
            uncompresed_data.resize(dest_len_inner);
            bool r = Uncompress(data, data_len, &uncompresed_data[0], &dest_len_inner);
            if (!r)
            {
                return false;
            }
            assert(dest_len_inner <= uncompresed_data.size());
            uncompresed_data.resize(dest_len_inner);
            return true;
        }

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
        static bool Compress(const void* source, size_t sourceLen, void* dest, size_t* destLen);
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
        static bool Uncompress(const void* source, size_t sourceLen, void* dest, size_t* destLen);
        //static int Uncompress(const void* source, size_t sourceLen, std::string& dest);

        static size_t GetUncompressBound( const void* compressed_data, size_t compressed_data_len );
    }; 

}//end of namespace npp

#ifdef __cplusplus
extern "C"{
#endif

//! \brief 
//! \param const uint8_t * source - 
//! \param uint32_t source_len - 
//! \param uint8_t * dest - 
//! \param size_t * dest_len - 
//! \return int - ZZ_OK if successfully
_EXPORT_NETPROTO int gz_compress  (const uint8_t *source, uint32_t source_len, uint8_t *dest, size_t *dest_len);
_EXPORT_NETPROTO int gz_uncompress(const uint8_t *source, uint32_t source_len, uint8_t *dest, size_t *dest_len);

//! \brief Get the compressed data length which you can use to allocate memory to store the data
//! \warning I am not much sure whether it is OK! If you came across any problem of this function, 
//!     please contact me <weizili>
//! \param size_t source_len - 
//! \return _EXPORT_NETPROTO size_t - 
_EXPORT_NETPROTO size_t gz_compress_bound(  size_t source_len);

//! \brief Get the uncompressed data length which you can use to allocate memory to store the data
//! \param const uint8_t * compressed_data - 
//! \param size_t compressed_source_len - 
//! \return _EXPORT_NETPROTO size_t - 
_EXPORT_NETPROTO size_t gz_uncompress_bound(const uint8_t *compressed_data, size_t compressed_source_len);

#ifdef __cplusplus
}; // end of extern "C"{
#endif

#endif

#endif

