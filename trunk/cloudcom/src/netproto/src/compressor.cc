#include "netproto/include/compressor.h"


#ifdef H_NPP_PROVIDE_ZLIB

#include "netproto/include/zlib.h"

#include "netproto/include/message.h"

#include <zlib/zlib.h>

namespace npp
{
    Compressor* CompressorFactory::CreateCompressor( int compress_method )
    {
        switch(compress_method)
        {
        case Message::kZlibCompress:
#ifdef H_NPP_PROVIDE_ZLIB
            return new ZLib();
#else
            return NULL;
#endif
        default:
            return NULL;
        }
    }

    void CompressorFactory::DesstoryCompressor( Compressor* c )
    {
        if (c)
        {
            delete c;
            c = NULL;
        }
    }
}

#endif



