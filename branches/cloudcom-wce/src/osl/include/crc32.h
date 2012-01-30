#ifndef QOSLIB_CRC32_H
#define QOSLIB_CRC32_H

#include "osl/include/inner_pre.h"

#if H_PROVIDE_CRC32

namespace osl
{


    /** ������װ�˻���CRC32��У���������㷨��
    *  @remark ����㷨���ù̶���У���������������У���룬У��˫����Ҫ����ͬ�������
    *          ������ڳ���������ʱ���ʼ��һ�Σ�������ݲ��ܶ�̬�仯���߼��ء�
    *  @par    �����ֻ����һ�����еľ�̬���������Ҳ��ܴ��������κ�ʱ��ʵ����
    *  @note   �����Ҫ���������м���/���ܷ�����Ҫ��������������Ķ�̬���÷�������
    *          �������ʱ���ʺϴ���Ӧ�á�
    *
    */
    class _EXPORT_OSLIB CRC32
    {
    public:

        /** ���ù̶��������������У���롣
        *  @remark У���벻��<b>��֤���ظ�</b>�����Ƕ��ڵ�����У��Ŀ����˵�������ظ����ʱ�ʵ��
        *          ֤�����Ա�����Ӧ�ý��ܡ�
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




