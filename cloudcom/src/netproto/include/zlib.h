#ifndef _NETPROTO_ZLIB_WRAPPER_H_
#define _NETPROTO_ZLIB_WRAPPER_H_

#include "netproto/include/inner_pre.h"

#if H_NPP_PROVIDE_ZLIB

namespace npp
{
    class _EXPORT_NETPROTO ZLib
    {
    public:
        enum kErrorCode
        {
            kNoError = 0,
#define Z_OK            0
#define Z_STREAM_END    1
#define Z_NEED_DICT     2
#define Z_ERRNO        (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR   (-3)
#define Z_MEM_ERROR    (-4)
#define Z_BUF_ERROR    (-5)
#define Z_VERSION_ERROR (-6)
        };
    public:
        static bool Compress();
        static bool Uncompress();
    };
}//end of namespace npp
#endif

#endif

