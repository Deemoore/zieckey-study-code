#ifndef _NETPROTO_COMPRESSOR_WRAPPER_H_
#define _NETPROTO_COMPRESSOR_WRAPPER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/auto_delete.h"

namespace npp
{

#define ZZ_OK            0
#define ZZ_STREAM_END    1
#define ZZ_NEED_DICT     2
#define ZZ_ERRNO        (-1)
#define ZZ_STREAM_ERROR (-2)
#define ZZ_DATA_ERROR   (-3)
#define ZZ_MEM_ERROR    (-4)
#define ZZ_BUF_ERROR    (-5)
#define ZZ_VERSION_ERROR (-6)

#define ZZ_BEST_SPEED             1
#define ZZ_BEST_COMPRESSION       9

    class _EXPORT_NETPROTO Compressor
    {
    public:
        virtual ~Compressor() {}

        virtual bool Compress(const void* data, size_t data_len, std::string& compresed_data) = 0;
        virtual bool Uncompress(const void* data, size_t data_len, std::string& uncompresed_data) = 0;
    };

    class _EXPORT_NETPROTO CompressorFactory
    {
    public:
        static Compressor* CreateCompressor(int compress_method);
        static void DesstoryCompressor(Compressor* c);
    };


}//end of namespace npp

namespace npp { 
    namespace ext {
        template<> inline
            auto_delete< npp::Compressor >::~auto_delete()
        {
            if ( ptr_ref_to_be_deleted_ )
            {
                npp::CompressorFactory::DesstoryCompressor(ptr_ref_to_be_deleted_);
                ptr_ref_to_be_deleted_ = NULL;
            }
        }
    }
}

#endif



