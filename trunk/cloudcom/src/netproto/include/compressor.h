#ifndef _NETPROTO_COMPRESSOR_WRAPPER_H_
#define _NETPROTO_COMPRESSOR_WRAPPER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/auto_delete.h"

namespace npp
{
    class _EXPORT_NETPROTO Compressor
    {
    public:
        virtual ~Compressor() {}

        virtual bool Compress(const void* data, size_t data_len, std::string& uncompresed_data) = 0;
        virtual bool Uncompress(const void* data, size_t data_len, std::string& compresed_data) = 0;
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



