/****************************** Module Header ********************************\
    Name: byte_swap.h
 Created: 2012/01/08 8:1:2012 1:43
  Author: weizili

 Purpose: 
\*****************************************************************************/
#ifndef OSLIB_BYTE_SWAP_H_
#define OSLIB_BYTE_SWAP_H_

#include "osl/include/platform_micros.h"
namespace osl
{
    class _EXPORT_OSLIB ByteSwap
    {
    public:
        static u16 bswap( u16 num );
        static s16 bswap( s16 num );
        static u32 bswap( u32 num );
        static s32 bswap( s32 num );
        static f32 bswap( f32 num );
    };

    /////////////////////////////////////////////////////////////
    //                   bswap_16
    /////////////////////////////////////////////////////////////
#if defined(_IRR_USE_SDL_DEVICE_)
#	include <SDL/SDL_endian.h>
#	define bswap_16(X) SDL_Swap16(X)
#	define bswap_32(X) SDL_Swap32(X)
#elif defined(H_OS_WINDOWS)
    //#	if (defined(_MSC_VER) && (_MSC_VER > 1298))
    //#		define bswap_16(X) _byteswap_ushort(X)
    //#		define bswap_32(X) _byteswap_ulong(X)
    //#	else
#		define bswap_16(X) ((((X)&0xFF) << 8) | (((X)&=0xFF00) >> 8))
#		define bswap_32(X) ( (((X)&0x000000FF)<<24) | (((X)&0xFF000000) >> 24) | (((X)&0x0000FF00) << 8) | (((X) &0x00FF0000) >> 8))
    //#	endif
#else
#	ifdef H_OS_MACOSX
#		define bswap_16(X) OSReadSwapInt16(&X,0)
#		define bswap_32(X) OSReadSwapInt32(&X,0)
#	elif defined(__FreeBSD__)
#		include <sys/endian.h>
#		define bswap_16(X) bswap16(X)
#		define bswap_32(X) bswap32(X)
#	elif !defined(H_OS_SOLARIS) && !defined(__PPC__)
#		include <byteswap.h>
#	else
#		define bswap_16(X) ((((X)&0xFF) << 8) | (((X)&=0xFF00) >> 8))
#		define bswap_32(X) ( (((X)&0x000000FF)<<24) | (((X)&0xFF000000) >> 24) | (((X)&0x0000FF00) << 8) | (((X) &0x00FF0000) >> 8))
#	endif
#endif


    inline u16 ByteSwap::bswap( u16 num )
    {
        return bswap_16( num );
    }
    inline s16 ByteSwap::bswap( s16 num )
    {
        return bswap_16( num );
    }
    inline u32 ByteSwap::bswap( u32 num )
    {
        return bswap_32( num );
    }
    inline s32 ByteSwap::bswap( s32 num )
    {
        return bswap_32( num );
    }
    inline f32 ByteSwap::bswap( f32 num )
    {
        void* vp = reinterpret_cast<void*>(&num);
        u32 tmp = bswap_32( *(reinterpret_cast<u32*>(vp) ) );
        vp = reinterpret_cast<void*>(&tmp);
        return *(reinterpret_cast<f32*>(vp));
    }
}
#endif //OSLIB_BYTE_SWAP_H_

