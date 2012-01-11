#ifndef QOSLIB_CRC32_H
#define QOSLIB_CRC32_H

#include "osl/include/inner_pre.h"

#if H_PROVIDE_CRC32

namespace osl
{


    /** 这个类封装了基于CRC32的校验码生成算法。
    *  @remark 这个算法利用固定的校验码冗余表来生成校验码，校验双方需要用相同的冗余表，
    *          冗余表在程序启动的时候初始化一次，表的内容不能动态变化或者加载。
    *  @par    这个类只包含一个公有的静态方法，并且不能创建他的任何时候实例。
    *  @note   如果需要用它来进行加密/解密服务，需要对冗余表进行特殊的动态设置服务，所以
    *          这个类暂时不适合此类应用。
    *
    */
    class _EXPORT_OSLIB CRC32
    {
    public:

        /** 采用固定的冗余表来生成校验码。
        *  @remark 校验码不能<b>保证无重复</b>，但是对于单纯的校验目的来说，他的重复概率被实践
        *          证明可以被多数应用接受。
        *  @warning
        *  @param chData   Source data buffer, If length is length than dwLength, result is unkown.
        *  @param dwLength Size of chData.
        *  @return crc value.
        *  <code>
        u16 nCrc = CRC32::getCRC32( pBuf, nLen );
        *  <\code>
        */
        static u32 getCRC32( const u8* chData, u32 dwLength );

    private:
        CRC32();
        CRC32( const CRC32& );

        // Initialize  table with 256 elements.
        static void Init_CRC32_Table( u32* table );
        static u32 Reflect( u32 ref, char ch );
    };
}

#endif // end of #if H_PROVIDE_CRC32

#endif // end of #ifndef QOSLIB_CRC32_H




