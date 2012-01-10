#include "osl/include/QOSLibPrerequisits.h"

#if H_PROVIDE_BASE64

#include "osl/include/object.h"
#include "osl/include/QString.h"
#include "osl/include/QStringUtil.h"
#include "osl/include/QDataStream.h"
#include "osl/include/QLogManager.h"
#include "osl/include/QBase64.h"

namespace osl
{

    //------------------------------------------------------------
    void Base64::encodeblock( const unsigned char in[3], unsigned char out[4], int len )
    {
        static const char* cb64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        out[0] = cb64[ in[0] >> 2 ];
        out[1] = cb64[ ( ( in[0] & 0x03 ) << 4 ) | ( ( in[1] & 0xf0 ) >> 4 ) ];
        out[2] = ( u8 ) ( len > 1 ? cb64[ ( ( in[1] & 0x0f ) << 2 ) | ( ( in[2] & 0xc0 ) >> 6 ) ] : '=' );
        out[3] = ( u8 ) ( len > 2 ? cb64[ in[2] & 0x3f ] : '=' );
    }

	/*
	** decodeblock
	**
	** decode 4 '6-bit' characters into 3 '8-bit' binary bytes
	*/
	void Base64::decodeblock( const unsigned char in[4], unsigned char out[3] )
	{
		out[ 0 ] = ( unsigned char ) ( in[0] << 2 | in[1] >> 4 );
		out[ 1 ] = ( unsigned char ) ( in[1] << 4 | in[2] >> 2 );
		out[ 2 ] = ( unsigned char ) ( ( ( in[2] << 6 ) & 0xc0 ) | in[3] );
	}

    //------------------------------------------------------------
    bool Base64::encode( const char* pathname, MemoryDataStream& encodedData )
    {
        if ( !pathname )
        {
            printf( "Wrong parameters.\n" );
            return false;
        }

        u8 in[3], out[4];
        int i = 0, len = 0;
        FILE* infile = fopen( pathname, "rb" );

        while ( !feof( infile ) )
        {
            len = 0;

            for ( i = 0; i < 3; i++ )
            {
                in[i] = ( u8 ) getc( infile );

                if ( !feof( infile ) )
                {
                    len++;
                }
                else
                {
                    in[i] = 0;
                }
            }

            if ( len )
            {
                encodeblock( in, out, len );
                encodedData.write( out, sizeof( out ) );
            }
        }

        return true;
    }

    //------------------------------------------------------------
    bool Base64::encode( const MemoryDataStream& srcData, MemoryDataStream& encodedData )
    {
        return encode( ( const u8* )srcData.getCache(), srcData.getSize(), encodedData );
    }


    //------------------------------------------------------------
    bool Base64::encode( const StringA& srcData, MemoryDataStream& encodedData )
    {
        return encode( ( const u8* )srcData.c_str(), srcData.size(), encodedData );
    }

    //------------------------------------------------------------
    bool Base64::encode( const StringA& srcData, StringA& encodedData )
    {
        MemoryDataStream ds;

        if ( encode( ( const u8* )srcData.c_str(), srcData.size(), ds ) )
        {
            encodedData = StringA( ( const char* )ds.getCache(), ds.getSize() );
            return true;
        }

        return false;
    }

    //------------------------------------------------------------
    bool Base64::encode( const MemoryDataStream& srcData, StringA& encodedData )
    {
        MemoryDataStream ds;

        if ( encode( srcData, ds ) )
        {
            encodedData = StringA( ( const char* )ds.getCache(), ds.getSize() );
            return true;
        }

        return false;
    }

    //------------------------------------------------------------
    bool Base64::encode( const void* pSrcData_void, size_t inlen, MemoryDataStream& encodedData )
    {
        const u8* pSrcData = (const u8*)pSrcData_void;
        if( NULL == pSrcData )
		{
			return false;
		}

        enum { IN_LEN = 3, OUT_LEN = 4 };

        u8 out[OUT_LEN];
        InBuf inbuf;

        u32 readFullCircle = inlen / IN_LEN;      //以3字节为单位，总共有多少个这样的3字节单位
        u32 readn = 0;      //已经读取的字节数
        encodedData.setBufferSize( ( readFullCircle + 2 ) * OUT_LEN );//预先分配好内存

        for( u32 k = 0; k < readFullCircle; k++ )
        {
            for ( u32 i = 0; i < IN_LEN; i++ )
            {
                inbuf.in[i] = pSrcData[readn++];
            }

            encodeblock( inbuf.in, out, IN_LEN );
            encodedData.write( out, OUT_LEN );
        }

        u32 remainChars = inlen % IN_LEN;  //最后剩余的字节数

        if ( remainChars > 0 )
        {
            inbuf.l = 0;

            for ( u32 i = 0; i < remainChars; i++ )
            {
                inbuf.in[i] = pSrcData[readn++];
            }

            encodeblock( inbuf.in, out, remainChars );
            encodedData.write( out, OUT_LEN );
        }

        return true;
    }


    bool Base64::encode( const void* pSrcData, size_t inlen, void* outbuf, size_t& outlen )
    {
        if ( NULL == pSrcData || 0 == inlen || NULL == outbuf )
        {
            return false;
        }

        enum { IN_LEN = 3, OUT_LEN = 4 };

        u32 readFullCircle = inlen / IN_LEN;      //以3字节为单位，总共有多少个这样的3字节单位
        u32 remainChars = inlen % IN_LEN;         //最后剩余的字节数

        u32 minbufsize = 0;
        if ( remainChars > 0 )
        {
            minbufsize = (readFullCircle + 1) * OUT_LEN;
        }
        else
        {
            minbufsize = (readFullCircle + 0) * OUT_LEN;
        }

        if ( minbufsize > outlen )
        {
            return false; //the outbuf is not large enough to hold the encoded data
        }
        
        u32 readn  = 0; //从 pSrcData 中已经读取的字节数
        u32 writen = 0; //已经写入 outbuf 的字节数

        for( u32 k = 0; k < readFullCircle; k++ )
        {
            encodeblock( (u8*)pSrcData + readn, (u8*)outbuf + writen, IN_LEN );
            readn  += IN_LEN;
            writen += OUT_LEN;
        }

        if ( remainChars > 0 )
        {
			InBuf inbuf;
			inbuf.l = 0;
			memcpy( inbuf.in, (u8*)pSrcData + readn, remainChars );
            encodeblock( inbuf.in, (u8*)outbuf + writen, remainChars );

            readn  += remainChars;
            writen += OUT_LEN;
        }

        assert( readn == inlen );
        assert( writen % OUT_LEN == 0 );
        outlen = writen;
        return true;
    }


    bool Base64::decode( const void* enc_void, size_t inlen, MemoryDataStream& decodedData )
    {
        const u8* enc = (const u8*)enc_void;

        // this decode table is copied from :
        // http://discussion.forum.nokia.com/forum/showthread.php?t=100464
        // Decode Table gives the index of any valid base64 character in the Base64 table
        // 65 == A, 97 == a, 48 == 0, 43 == +, 47 == /
        static const u8 dectable[256] =
        {
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 62, 255, 255, 255, 63,
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 255, 255,
            255, 254, 255, 255, 255, 0, 1, 2, 3, 4, 5, 6,
            7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
            19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255, 255,
            255, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
            37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
            49, 50, 51, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255
        };

        enum { IN_LEN = 4, OUT_LEN = 3 };
        InBuf inbuf;
        u8 out[OUT_LEN];
        u32 readFullCircle = inlen / IN_LEN;      //以4字节为单位，总共有多少个这样的4字节单位
        u32 readn = 0;      //已经读取的字节数
        decodedData.setBufferSize( ( readFullCircle + 2 ) * OUT_LEN );//预先分配好内存

        for( u32 k = 0; k < readFullCircle - 1; k++ )
        {
            inbuf.l = 0;

            for ( u32 i = 0; i < IN_LEN; i++ )
            {
                inbuf.in[i] = dectable[ enc[readn++] ];
                assert( inbuf.in[i] != 255 && "255 means the encoded input data is not base64 encoded data." );
            }

            decodeblock( inbuf.in, out );
            decodedData.write( out, sizeof( out ) );
        }

        inbuf.l = 0;

        for ( u32 i = 0; i < IN_LEN; i++ )
        {
            u8 b = enc[readn++];

            if ( b == '=' )
            {
                decodeblock( inbuf.in, out );
                decodedData.write( out, i - 1 );
                break;
            }

            inbuf.in[i] = dectable[ b ];
            assert( inbuf.in[i] != 255 && "255 means the encoded input data is not base64 encoded data." );

            if ( i == IN_LEN - 1  )
            {
                decodeblock( inbuf.in, out );
                decodedData.write( out, i );
            }
        }

        return true;
    }


    bool Base64::decode( const void* enc, size_t inlen, void* outbuf, size_t& outlen )
    {
		if ( NULL == enc || 0 == inlen || NULL == outbuf )
		{
			return false;
		}

        // this decode table is copied from :
        // http://discussion.forum.nokia.com/forum/showthread.php?t=100464
        // Decode Table gives the index of any valid base64 character in the Base64 table
        // 65 == A, 97 == a, 48 == 0, 43 == +, 47 == /
        static const u8 dectable[256] =
        {
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 62, 255, 255, 255, 63,
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 255, 255,
            255, 254, 255, 255, 255, 0, 1, 2, 3, 4, 5, 6,
            7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
            19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255, 255,
            255, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
            37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
            49, 50, 51, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255
        };

        enum { IN_LEN = 4, OUT_LEN = 3 };
        u32 readFullCircle = inlen / IN_LEN;   //以4字节为单位，总共有多少个这样的4字节单位

        if ( readFullCircle * OUT_LEN > outlen )
        {
            return false; //the outbuf is not large enough to hold the decoded data
        }

        u32 readn  = 0; //从 pSrcData 中已经读取的字节数
        u32 writen = 0; //已经写入 outbuf 的字节数
       
        InBuf inbuf;

        for( u32 k = 0; k < readFullCircle - 1; k++ )
        {
            inbuf.l = 0;
            for ( u32 i = 0; i < IN_LEN; i++ )
            {
                inbuf.in[i] = dectable[ ((const unsigned char*)enc)[readn++] ];
                assert( inbuf.in[i] != 255 && "255 means the encoded input data is not base64 encoded data." );
            }

            decodeblock( inbuf.in, ((u8*)outbuf) + writen );
            
            writen += OUT_LEN;
        }

        inbuf.l = 0;
		u8 b = 0;
        for ( u32 i = 0; i < IN_LEN; i++ )
        {
            b = ((const unsigned char*)enc)[readn++];

            if ( b == '=' )
            {
                decodeblock( inbuf.in, ((u8*)outbuf) + writen );
                writen += i - 1;
                break;
            }

            inbuf.in[i] = dectable[ b ];
            assert( inbuf.in[i] != 255 && "255 means the encoded input data is not base64 encoded data." );

            if ( i == IN_LEN - 1  )
            {
                decodeblock( inbuf.in, ((u8*)outbuf) + writen );
				writen += i;
				break;
            }
        }

        outlen = writen;

        return true;
    }


    //------------------------------------------------------------
    bool Base64::decode( const MemoryDataStream& srcData, MemoryDataStream& decodedData )
    {
        return decode( ( const u8* )srcData.getCache(), srcData.getSize(), decodedData );
    }

    //------------------------------------------------------------
    bool Base64::decode( const MemoryDataStream& srcData, StringA& decodedData )
    {
        MemoryDataStream ds;

        if ( !decode( srcData, ds ) )
        {
            return false;
        }

        decodedData = StringA( ( const char* )ds.getCache(), ds.getSize() );
        return true;
    }

    //------------------------------------------------------------
    bool Base64::decode( const StringA& srcData, MemoryDataStream& decodedData )
    {
        return decode( ( const u8* )srcData.c_str(), srcData.size(), decodedData );
    }

    //------------------------------------------------------------
    bool Base64::decode( const StringA& srcData, StringA& decodedData )
    {
        MemoryDataStream ds;

        if ( !decode( srcData, ds ) )
        {
            return false;
        }

        decodedData = StringA( ( const char* )ds.getCache(), ds.getSize() );
        return true;
    }

    //------------------------------------------------------------
    bool Base64::decode( const char *inpath, const char* outpath )
    {
        if ( !inpath || !outpath )
        {
            printf( "Wrong parameters.\n" );
            return false;
        }

        FILE* infile = fopen( inpath, "rb" );

        if ( !infile )
        {
            return false;
        }

        FILE* outfile = fopen( outpath, "wb" );

        if ( !outfile )
        {
            fclose( infile );
            return false;
        }

        decode( infile, outfile );

        fclose( infile );
        fclose( outfile );
        return true;
    }

    //------------------------------------------------------------
    bool Base64::encode( const char *inpath, const char* outpath )
    {
        if ( !inpath || !outpath )
        {
            printf( "Wrong parameters.\n" );
            return false;
        }

        FILE* infile = fopen( inpath, "rb" );

        if ( !infile )
        {
            return false;
        }

        FILE* outfile = fopen( outpath, "wb" );

        if ( !outfile )
        {
            fclose( infile );
            return false;
        }

        u8 in[3], out[4];
        int i = 0, len = 0;

        while ( !feof( infile ) )
        {
            len = 0;

            for ( i = 0; i < 3; i++ )
            {
                in[i] = ( u8 ) getc( infile );

                if ( !feof( infile ) )
                {
                    len++;
                }
                else
                {
                    in[i] = 0;
                }
            }

            if ( len )
            {
                encodeblock( in, out, len );

                for ( i = 0; i < 4; i++ )
                {
                    putc( out[i], outfile );
                }
            }
        }

        if ( infile )
        {
            fclose( infile ) ;
        }

        if ( outfile )
        {
            fclose( outfile ) ;
        }

        return true;
    }

    //------------------------------------------------------------
    void Base64::encode( FILE *infile, FILE *outfile, int linesize )
    {
        u8 in[3], out[4];
        int i, len, blocksout = 0;

        while ( !feof( infile ) )
        {
            len = 0;

            for ( i = 0; i < 3; i++ )
            {
                in[i] = ( u8 ) getc( infile );

                if ( !feof( infile ) )
                {
                    len++;
                }
                else
                {
                    in[i] = 0;
                }
            }

            if ( len )
            {
                encodeblock( in, out, len );

                for ( i = 0; i < 4; i++ )
                {
                    putc( out[i], outfile );
                }

                blocksout++;
            }

            if ( blocksout >= ( linesize / 4 ) || feof( infile ) )
            {
                if ( blocksout )
                {
                    fprintf( outfile, "\r\n" );
                }

                blocksout = 0;
            }
        }
    }


    /*
    ** decode
    **
    ** decode a base64 encoded stream discarding padding, line breaks and noise
    */
    bool Base64::decode( FILE *infile, FILE *outfile )
    {
        static const char* cd64 = "|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";
        u8 in[4], out[3], v;
        int i, len;

        while ( !feof( infile ) )
        {
            for ( len = 0, i = 0; i < 4 && !feof( infile ); i++ )
            {
                v = 0;

                while ( !feof( infile ) && v == 0 )
                {
                    v = ( u8 ) getc( infile );
                    v = ( u8 ) ( ( v < 43 || v > 122 ) ? 0 : cd64[ v - 43 ] );

                    if ( v )
                    {
                        v = ( u8 ) ( ( v == '$' ) ? 0 : v - 61 );
                    }
                }

                if ( !feof( infile ) )
                {
                    len++;

                    if ( v )
                    {
                        in[ i ] = ( u8 ) ( v - 1 );
                    }
                }
                else
                {
                    in[i] = 0;
                }
            }

            if ( len )
            {
                decodeblock( in, out );

                for ( i = 0; i < len - 1; i++ )
                {
                    putc( out[i], outfile );
                }
            }
        }

        return true;
    }

    
};

#endif// #if H_PROVIDE_BASE64
