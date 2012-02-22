#ifndef _QOSLIB_MD5_H_
#define _QOSLIB_MD5_H_

#include "netproto/include/inner_pre.h"

#if H_PROVIDE_MD5

#include <fstream>
#include <iostream>

namespace npp
{



    // MD5.CC - source code for the C++/object oriented translation and 
    //          modification of MD5.

    // Translation and modification (c) 1995 by Mordechai T. Abzug 

    // This translation/ modification is provided "as is," without express or 
    // implied warranty of any kind.

    // The translator/ modifier does not claim (1) that MD5 will do what you think 
    // it does; (2) that this translation/ modification is accurate; or (3) that 
    // this software is "merchantible."  (Language for this disclaimer partially 
    // copied from the disclaimer below).

    /* based on:

    MD5.H - header file for MD5C.C
    MDDRIVER.C - test driver for MD2, MD4 and MD5

    Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
    rights reserved.

    License to copy and use this software is granted provided that it
    is identified as the "RSA Data Security, Inc. MD5 Message-Digest
    Algorithm" in all material mentioning or referencing this software
    or this function.

    License is also granted to make and use derivative works provided
    that such works are identified as "derived from the RSA Data
    Security, Inc. MD5 Message-Digest Algorithm" in all material
    mentioning or referencing the derived work.

    RSA Data Security, Inc. makes no representations concerning either
    the merchantability of this software or the suitability of this
    software for any particular purpose. It is provided "as is"
    without express or implied warranty of any kind.

    These notices must be retained in any copies of any part of this
    documentation and/or software.

    */


    class _EXPORT_OSLIB MD5 
    {
    public:
        enum
        {
            MD5_RAW_BIN_DIGEST_LEN = 16, // the length of digest as a 16-byte binary array
            MD5_HEX_DIGEST_LEN = 32, // the length of digest as a 32-byte ASCII-hex string, not include the terminating null-character
        };
    public:
        // methods for controlled operation:
        MD5();  // simple initializer

		// Constructors for special circumstances.  
		// All these constructors finalize the MD5 context.
		MD5(const void *str, size_t input_length); // digest string, finalize
		MD5(std::istream& stream);       // digest stream, finalize
		MD5(FILE *file);            // digest file, close, finalize
		MD5(std::ifstream& stream);      // digest stream, close, finalize

        void update(const void* input, size_t input_length);
        void update(std::istream& stream);
        void update(FILE *file);
        void update(std::ifstream& stream);
        void finalize();

        //! Method to acquire finalized result which is digest as a 16-byte binary array
        //! \param[out] unsigned char * binary16md5, the result stored here, it MUST BE at least 16 bytes long
		//! \return true if digest the input source data successfully and digest data is stored in output
        bool getRawDigest ( unsigned char binary16md5[/*16*/] ); // digest as a 16-byte binary array

		//! Method to acquire finalized result which is digest as a 33-byte ASCII-hex string
		//! \param[out] char* output, the result stored here, output MUST BE at least 33 bytes long
		//! \return true if digest the input source data successfully and digest data is stored in output
        bool getHexDigest( char hex33md5[/*33*/] ); //digest as a 33-byte ASCII-hex string, with the terminating null-character


        //! Get the hex 33 bytes md5 string from a 16 bytes long binary md5 string
        static void getHex33Str( const unsigned char rawmd5[/*16*/], char hex33[/*33*/] )
        {
            for ( int i = 0; i < 16; i++ )
            {
                sprintf( hex33 + i * 2, "%02x", rawmd5[i] );
            }

            hex33[32] = '\0';
        }


        //! Return a random hex md5, 33 bytes md5 string (including the terminating char \0)
        static std::string genHexMD5( const size_t random_data_len = 1024 );

        //! Return a random binary md5, 16 bytes md5 string 
        static std::string genRawMD5( const size_t random_data_len = 1024 );

        //! Return the md5 digest of <code>data</code> 
        static void getHexMD5( const void* data, size_t data_len, char hex33md5[/*33*/] );
        static std::string getHexMD5( const void* data, size_t data_len )
        {
            char hex33md5[33] = {};
            getHexMD5(data, data_len, hex33md5);
            return hex33md5;
        }

        //! Return the md5 digest of <code>data</code> 
        //! \param[out] unsigned char * binary16md5, the result stored here, it MUST BE at least 16 bytes long
        static void getRawMD5( const void* data, size_t data_len, unsigned char binary16md5[/*16*/] );
        static std::string getRawMD5( const void* data, size_t data_len )
        {
            unsigned char binary16md5[16] = {};
            getRawMD5(data, data_len, binary16md5);
            return std::string((char*)binary16md5, sizeof(binary16md5));
        }

        static bool isValidMD5(const std::string& hexmd5)
        {
            return isValidMD5(hexmd5.c_str(), hexmd5.length());
        }


        static void convertBinary16ToHex32(const uint8_t binary16[/* 16 */], char hex33[/*33*/])
        {
            int m = 0;
            for (size_t i = 0; i < 16; ++i)
            {
                m = (binary16[i] & 0xF0) >> 4;
                if (m <= 9)
                {
                    hex33[i << 1] = m + '0';
                }
                else
                {
                    hex33[i << 1] = m + 'a' - 10;
                }

                m = (binary16[i]) & 0x0F;
                if (m <= 9)
                {
                    hex33[(i << 1) + 1] = m + '0';
                }
                else
                {
                    hex33[(i << 1) + 1] = m + 'a' - 10;
                }
            }
            hex33[32] = '\0';
        }

        static std::string convertBinary16ToHex32(const uint8_t binary16[/* 16 */])
        {
            char hex33[33] = {};
            convertBinary16ToHex32(binary16, hex33);
            return std::string(hex33, 32);
        }

        static int dehexchar( char c )
        {
            if ( c >= '0' && c <= '9' )
            {
                return c - '0';
            }

            if ( c >= 'A' && c <= 'F' )
            {
                return c - ( 'A' - 10 );
            }

            if ( c >= 'a' && c <= 'f' )
            {
                return c - ( 'a' - 10 );
            }

            return -1;
        }

        static std::string convertHex32ToBinary16(const char hex33[/*32*/], const size_t hex33_len = MD5_HEX_DIGEST_LEN)
        {
            uint8_t binary16[16] = {};
            convertHex32ToBinary16(hex33, hex33_len, binary16);
            return std::string((char*)binary16, sizeof(binary16));
        }

        static void convertHex32ToBinary16(const char hex33[/*32*/], const size_t hex33_len, uint8_t binary16[/* 16 */])
        {
            int m = 0;
            size_t i = 0;
            while (i < hex33_len)
            {
                m = dehexchar(hex33[i]);
                if (m < 0)
                {
                    break;
                }
                binary16[i >> 1] = m << 4;

                if (i + 1 >= hex33_len)
                {
                    break;
                }

                m = dehexchar(hex33[i+1]);
                if (m < 0)
                {
                    break;
                }
                binary16[i >> 1] |= m;

                i += 2;
            }
        }

        static bool isValidMD5(const char* hexmd5, size_t hexmd5_length)
        {
            if (hexmd5_length > 32 || hexmd5_length == 0)
            {
                return false;
            }

            static const char validmd5chs[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

            for (size_t i = 0; i < hexmd5_length; ++i)
            {
                if (validmd5chs[(int)hexmd5[i]] == 0)
                {
                    return false;
                }
            }

            return true;
        }
        //friend std::ostream& operator<< (std::ostream&, const MD5& context);

    private:

        // first, some types:
        typedef u32 uint4; // assumes integer is 4 words long
        typedef u16 uint2; // assumes short integer is 2 words long
        typedef u8 uint1; // assumes char is 1 word long

        // next, the private data:
        uint4 state[4];
        uint4 count[2];     // number of *bits*, mod 2^64
        uint1 buffer[64];   // input buffer
        uint1 digest[16];
        uint1 finalized;

        // last, the private methods, mostly static:
        void init             ();               // called by all constructors
        void transform        (uint1 *buffer);  // does the real update work.  Note 
        // that length is implied to be 64.

        static void encode    (uint1 *dest, uint4 *src, uint4 length);
        static void decode    (uint4 *dest, uint1 *src, uint4 length);
        static void memcpy    (uint1 *dest, uint1 *src, uint4 length);
        static void memset    (uint1 *start, uint1 val, uint4 length);

        static inline uint4  rotate_left (uint4 x, uint4 n);
        static inline uint4  F           (uint4 x, uint4 y, uint4 z);
        static inline uint4  G           (uint4 x, uint4 y, uint4 z);
        static inline uint4  H           (uint4 x, uint4 y, uint4 z);
        static inline uint4  I           (uint4 x, uint4 y, uint4 z);
        static inline void   FF  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
            uint4 s, uint4 ac);
        static inline void   GG  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
            uint4 s, uint4 ac);
        static inline void   HH  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
            uint4 s, uint4 ac);
        static inline void   II  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
            uint4 s, uint4 ac);

    };








    // ROTATE_LEFT rotates x left n bits.

    inline unsigned int MD5::rotate_left  (uint4 x, uint4 n){
        return (x << n) | (x >> (32-n))  ;
    }




    // F, G, H and I are basic MD5 functions.

    inline unsigned int MD5::F            (uint4 x, uint4 y, uint4 z){
        return (x & y) | (~x & z);
    }

    inline unsigned int MD5::G            (uint4 x, uint4 y, uint4 z){
        return (x & z) | (y & ~z);
    }

    inline unsigned int MD5::H            (uint4 x, uint4 y, uint4 z){
        return x ^ y ^ z;
    }

    inline unsigned int MD5::I            (uint4 x, uint4 y, uint4 z){
        return y ^ (x | ~z);
    }



    // FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
    // Rotation is separate from addition to prevent recomputation.


    inline void MD5::FF(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
        uint4  s, uint4 ac){
            a += F(b, c, d) + x + ac;
            a = rotate_left (a, s) +b;
    }

    inline void MD5::GG(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
        uint4 s, uint4 ac){
            a += G(b, c, d) + x + ac;
            a = rotate_left (a, s) +b;
    }

    inline void MD5::HH(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
        uint4 s, uint4 ac){
            a += H(b, c, d) + x + ac;
            a = rotate_left (a, s) +b;
    }

    inline void MD5::II(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, 
        uint4 s, uint4 ac){
            a += I(b, c, d) + x + ac;
            a = rotate_left (a, s) +b;
    }

//     class _EXPORT_OSLIB HMD5
//     {
//     public:
//         HMD5( void );
//         /** Constructor that encode plain data directly. */
//         HMD5( const u8* pData, u32 nSize );
//         ~HMD5( void );
// 
//         /** Sets plain data. The input data will be encoded here without extra buffer.. */
//         void setPlainData( const u8* pData, u32 nSize );
// 
//         //! Gets encoded digest.
//         //! \remark Gets md5 result as 16 bytes.
//         //! \param pResult buffer at least 16 char.
//         void getDigest( u8* pResult );
// 
//         void getRawDigest( u8* pResult /*16 bytes*/ )// digest as a 16-byte binary array
//         {
//             getDigest( pResult );
//         }
// 
//         void getHexDigest( u8* pResult /*33 bytes*/ );// digest as a 33-byte ascii-hex string, with the terminating null-character
// 
//     private:
//         u32            m_States[4];      // encrypted message
//         u32            m_Counts[2];      // bits of plain text
//         u8            m_Buffer[64];      //
//         bool          m_bFinalized;      // Whether digest data has been updated.
// 
//     private:
// 
//         /** Initialize the md5 object */
//         void initialize();
// 
//         /** Do transform for a 64 byte data.
//          *  @param pBlock Source data with 64 length.
//          */
//         void transform( const u8* pBlock );
// 
//     };


};//namespace

#endif // end of #if H_PROVIDE_MD5
#endif // end of #define _QOSLIB_MD5_H_


