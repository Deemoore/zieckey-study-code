/****************************** Module Header ********************************\
    Name: packet.h
 Created: 2012/02/24 24:2:2012 0:14
  Author: weizili

 Purpose: 
\*****************************************************************************/

#ifndef NETPROTO_PACKET_H_
#define NETPROTO_PACKET_H_

#include "netproto/include/inner_pre.h"

namespace npp
{

    /**
    * The header information struct of the data packet 
    */
    struct Header{
        uint8_t  header_len; /** in bytes */
        uint8_t  header_ver;
        uint16_t data_len;   /** big-endian, the length of the data */
        uint16_t message_id; /** big-endian */ 
        uint8_t  packet_seq;
        uint8_t  packet_count;
        uint16_t preserve;   /** big-endian, preserved, set to 0x0000 */
    };

    class _EXPORT_NETPROTO Pakcet
    {
    public:
        //! The header information struct of the data packet 
#pragma pack(push,1)
        struct NetHeader
        {
            uint8_t  header_len; /** in bytes */
            uint8_t  header_ver;
            uint16_t data_len;   /** big-endian, the length of the data */
            uint16_t message_id; /** big-endian */ 
            uint8_t  packet_seq;
            uint8_t  packet_count;
            uint16_t preserve;   /** big-endian, preserved, set to 0x0000 */
        };

        struct NppHeader
        {
            union
            {
                struct 
                {
                    uint8_t encrypt_key_no:4; /** the number of the encrypt key  */
                    uint8_t encrypt_method:4; /** the encrypt method, 0:no encrypt; 1:XOR; 2:idea */
                };
                uint8_t encrypt;
            };
            union
            {
                struct 
                {
                    uint8_t sign_method:4; /** the sign method */
                    uint8_t sign_key_no:4; /** The key number of the sign */
                };
                uint8_t sign;
            };
            uint8_t digest_sign_len;/** The length of the sign and digest */
        };
#pragma pack(pop)


    };
}

#endif

