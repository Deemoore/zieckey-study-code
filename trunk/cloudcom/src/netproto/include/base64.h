#ifndef OSLIB_BASE64_H_
#define OSLIB_BASE64_H_

#include "netproto/include/config.h"
#include "netproto/include/platform_micros.h"
#include "netproto/include/data_stream.h"

#if H_PROVIDE_BASE64

namespace npp
{
    class _EXPORT_OSLIB Base64
    {
    public://encode

        //!	\brief encode a source data to Base64 encoded data
        //!	\param srcData - the source data
        //!	\param length - the length of the source data.
        //!	\param[out] encodedData - the encoded data stored here
        //!	\retval true, if success.
        static bool encode( const void* pSrcData, size_t length, MemoryDataStream& encodedData );
        static bool encode( const MemoryDataStream& srcData, MemoryDataStream& encodedData );
        static bool encode( const MemoryDataStream& srcData, std::string& encodedData );
        static bool encode( const std::string& srcData, MemoryDataStream& encodedData );
        static bool encode( const std::string& srcData, std::string& encodedData );

        static bool encode( const void* pSrcData, size_t length, std::string& encodedData )
        {//{{{
            npp::MemoryDataStream buf;
            if (npp::Base64::encode(pSrcData, length, buf))
            {
                encodedData = std::string((char*)buf.getCache(), buf.getSize());
                return true;
            }

            return false;
        }//}}}

        //! \brief encode a source data to Base64 encoded data
        //! \param const void * pSrcData - the source data
        //! \param size_t inlen - the length of the source data
        //! \param[out] void * outbuf - the encoded data stored here
		//! \param[in,out] size_t & outlen - pass in the max length of outbuf
		//!			if inlen%3 == 0, it MUST BE larger than inlen*4/3.
        //!			if inlen%3 != 0, it MUST BE larger than (inlen/3+1)*4.
        //!         You can call getEncodedBufLen( inlen ) to determine 
        //!         how much memory must be allocated for outbuf.
		//!			And pass out actually length of outbuf
        //! \return bool - true if success
        static bool encode( const void* pSrcData, size_t inlen, void* outbuf, size_t& outlen );

        static std::string encode(const void* data, size_t len)
        {//{{{
            npp::MemoryDataStream buf;
            if (npp::Base64::encode(data, len, buf))
            {
                return std::string((char*)buf.getCache(), buf.getSize());
            }
            else
            {
                return "";
            }
        }//}}}


    public://decode

        //!	\brief decode a source encoded data to plain data using Base64
        //!	\param pSrcData, the source encoded data,
        //!	\param length, the length of the source data.
		//!		It MUST BE a multiple of 4
        //!	\param[out] decodedData, the decoded data stored here
        //!	\retval true, if success.
        static bool decode( const void* pSrcData, size_t length, MemoryDataStream& decodedData );
        static bool decode( const MemoryDataStream& srcData, MemoryDataStream& decodedData );
        static bool decode( const MemoryDataStream& srcData, std::string& decodedData );
        static bool decode( const std::string& srcData, MemoryDataStream& decodedData );
        static bool decode( const std::string& srcData, std::string& decodedData );

        static bool decode( const void* pSrcData, size_t length, std::string& decodedData )
        {//{{{
            npp::MemoryDataStream buf;
            if (npp::Base64::decode((npp::u8*)pSrcData, length, buf))
            {
                decodedData = std::string((char*)buf.getCache(), buf.getSize());
                return true;
            }
            return false;
        }//}}}

        //! \brief decode a source encoded data to plain data using Base64
        //! \param const void * pSrcData - the source encoded data
        //! \param size_t inlen - the length of the source data
		//!		It MUST BE a multiple of 4
        //! \param[out] void * outbuf - the decoded data stored here
        //! \param[in,out] size_t & outlen - pass in the max length of outbuf
		//!			It MUST BE larger than or equal to inlen*3/4. 
        //!         You can call getDecodedBufLen( inlen ) to determine 
        //!         how much memory must be allocated for outbuf.
        //!			And pass out actually length of outbuf.
        //! \return bool - true if success
        static bool decode( const void* pSrcData, size_t inlen, void* outbuf, size_t& outlen );

        static std::string decode(const void* data, size_t len)
        {//{{{
            npp::MemoryDataStream buf;
            if (npp::Base64::decode((npp::u8*)data, len, buf))
            {
                return std::string((char*)buf.getCache(), buf.getSize());
            }
            else
            {
                return "";
            }
        }//}}}

    public:
        //! \brief This function returns the base64 encoded data size in bytes.
        //!     It can be used to determine how much memory must be allocated 
        //!     for an base64 encoded data.
        static size_t getEncodedBufLen( size_t plaindatalen );

        //! \brief This function returns the base64 decoded data size in bytes.
        //!     It can be used to determine how much memory must be allocated 
        //!     for an base64 decoded data.
        static size_t getDecodedBufLen( size_t encodeddatalen );

    public:
        //------------------------------------------------------------
        //------------------- file relative
        //------------------------------------------------------------

        //!	\brief  Base64 encode a local file to a DataStream
        //!	\param pathname, the file path name
        //!	\param[out] encodedData, the encoded data stored here
        //!	\retval true, if success.
        //!	\retval false, if failed.
        static bool encode( const char* pathname, MemoryDataStream& encodedData );

        //!	\brief  Base64 encode a file and output to another file.
        //! \param [in] inpath, the source input file path
        //! \param [in] outpath, the encoded output file path
        //!	\retval true, if success.
        //!	\retval false, if failed.
        static bool encode( const char *inpath, const char* outpath );


        //!	\brief  decode a source encoded data file to plain data file using Base64
        //! \param [in] inpath, the source input file path
        //! \param [in] outpath, the encoded output file path
        static bool decode( const char *inpath, const char* outpath );

    private:
        /**
        ** encode
        **
        ** base64 encode a stream adding padding and line breaks as per spec.
        */
        static void encode( FILE *infile, FILE *outfile, int linesize );

        //!	\brief decode a base64 encoded stream discarding padding, line breaks and noise
        //!	\param infile, infile pointer
        //!	\param[out] outfile, infile pointer
        //!	\return void,
        static bool decode( FILE *infile, FILE *outfile );
    private:
        /*
        ** encodeblock
        **
        ** encode 3 '8-bit' binary bytes as 4 '6-bit' characters
        */
        static void encodeblock( const unsigned char in[3], unsigned char out[4], int len );
        /*
        ** decodeblock
        **
        ** decode 4 '6-bit' characters into 3 '8-bit' binary bytes
        */
        static void decodeblock( const unsigned char in[4], unsigned char out[3] );

    private:
#pragma pack(push,1)
        union InBuf
        {
            u8 in[4];
            u32 l;
        };
#pragma pack(pop)

    };


    inline size_t Base64::getEncodedBufLen( size_t plaindatalen )
    {
        if ( plaindatalen % 3 == 0 )
        {
            return (plaindatalen / 3) * 4;
        }
        else
        {
            return ( (plaindatalen + 3) / 3 ) * 4;
        }
    }

    inline size_t Base64::getDecodedBufLen( size_t encodeddatalen )
    {
        assert( encodeddatalen % 4 == 0 );
        encodeddatalen = H_ALIGN(encodeddatalen, 4);
        return (encodeddatalen / 4) * 3;
    }
};

#endif //#if H_PROVIDE_BASE64

#endif // _BASE64_H_

