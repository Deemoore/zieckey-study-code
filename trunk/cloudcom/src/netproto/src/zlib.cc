#include "netproto/include/zlib.h"

#ifdef H_NPP_PROVIDE_ZLIB

#include <zlib/zlib.h>

#ifdef H_OS_WINDOWS
#	ifdef H_DEBUG_MODE
#       pragma comment(lib, "zlib_d.lib")
#	else
#       pragma comment(lib, "zlib.lib")
#	endif
#endif


namespace npp
{
    int ZLib::Compress( const void* source, size_t sourceLen, void* dest, size_t* destLen, int level/* = ZZ_BEST_SPEED*/ )
    {
        if (NULL == destLen || 
            NULL == dest || 
            *destLen < (GetCompressBound(sourceLen)) || 
            NULL == source)
        {
            return Z_MEM_ERROR;
        }

        *(uint32_t*)(dest) = htonl(sourceLen);

        uLongf dest_len_inner = *destLen - sizeof(uint32_t);

        int r = compress2((Bytef*)dest + sizeof(uint32_t), &dest_len_inner, (const Bytef*)source, sourceLen, level);

        //add the leading 4 bytes of original data length
        *destLen = dest_len_inner + sizeof(uint32_t);
        return r;
    }

    int ZLib::Compress( const void* source, size_t sourceLen, std::string& dest )
    {
        size_t dest_len_inner = GetCompressBound(sourceLen);
        dest.resize(dest_len_inner);
        int r = Compress(source, sourceLen, &dest[0], &dest_len_inner);
        if (r != Z_OK)
        {
            return r;
        }
        assert(dest_len_inner <= dest.size());
        dest.resize(dest_len_inner);
        return r;
    }

    bool ZLib::Compress( const void* data, size_t data_len )
    {
        int r = Compress(data, data_len, data_);
        return r == Z_OK;
    }

    size_t ZLib::GetCompressBound( size_t sourceLen )
    {
        return 4 + compressBound(sourceLen);
    }

    int ZLib::Uncompress( const void* source, size_t sourceLen, void* dest, size_t* destLen )
    {
        if (NULL == destLen || 
            NULL == dest || 
            *destLen < (GetUncompressBound(source)) || 
            NULL == source)
        {
            return Z_MEM_ERROR;
        }

        uLongf dest_len_inner = *destLen;
        int r = uncompress((Bytef*)dest, &dest_len_inner, (const Bytef *)source + sizeof(uint32_t), sourceLen - sizeof(uint32_t));
        *destLen = dest_len_inner;
        return r;
    }

    int ZLib::Uncompress( const void* source, size_t sourceLen, std::string& dest )
    {
        size_t dest_len_inner = GetUncompressBound(source);
        dest.resize(dest_len_inner);
        int r = Uncompress(source, sourceLen, &dest[0], &dest_len_inner);
        if (r != Z_OK)
        {
            return r;
        }
        assert(dest_len_inner <= dest.size());
        dest.resize(dest_len_inner);
        return r;
    }

    bool ZLib::Uncompress( const void* data, size_t data_len )
    {
        int r = Uncompress(data, data_len, this->data_);
        return r == Z_OK;
    }


    size_t ZLib::GetUncompressBound( const void* compressed_data )
    {
        return ntohl(*(uint32_t*)compressed_data);
    }

    const uint8_t* ZLib::Data() const
    {
        if (Size() == 0)
        {
            return NULL;
        }
        else
        {
            return (const uint8_t*)this->data_.data();
        }
    }

    size_t ZLib::Size() const
    {
        return this->data_.size();
    }
}

#endif



