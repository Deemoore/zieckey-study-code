#include "netproto/include/inner_pre.h"

#include "netproto/include/data_stream.h"
#include "netproto/include/idea_wrapper.h"



#if H_PROVIDE_IDEA_ENCRYPT


namespace npp
{
#define CCWEB_ALIGN H_ALIGN

    IDEA::IDEA()
    {
    }

    bool IDEA::initialize( unsigned char key[16] )
    {
        return initialize(std::string((char*)key, 16));
    }

    bool IDEA::initialize( const std::string& key )
    {
        ::idea_set_encrypt_key( (unsigned char*)key.data(), &m_encrypt_key );
        ::idea_set_decrypt_key( &m_encrypt_key, &m_decrypt_key);
        m_original_key = key;
        return true;
    }

    bool IDEA::encrypt( const void* szSource, const size_t nSourceLen, MemoryDataStream& dataEncrypted )
    {
        return IDEA::encrypt((const unsigned char*)szSource, (const unsigned int)nSourceLen, m_encrypt_key, dataEncrypted);
    }

    bool IDEA::decrypt( const void* szSource, const size_t nSourceLen, MemoryDataStream& dataDecrypted )
    {
        return IDEA::decrypt((const unsigned char*)szSource, (const unsigned int)nSourceLen, m_decrypt_key, dataDecrypted);
    }

    bool IDEA::encrypt( const unsigned char* szSource, const unsigned int nSourceLen, const std::string& strEncryptKey, npp::MemoryDataStream& dataEncrypted )
    {
        if ( strEncryptKey.length() != 16 )
        {
            assert( false && "The input parameter strEncryptKey MUST BE 16 bytes long." );
            return false;
        }

        if ( !szSource || 0 == nSourceLen )
        {
            return false;
        }

        ::IDEA_KEY_SCHEDULE ideakey;
        ::idea_set_encrypt_key( ( u_char * )strEncryptKey.c_str(), &ideakey );

        return encrypt( szSource, nSourceLen, ideakey, dataEncrypted );
    }

    bool IDEA::encrypt( const unsigned char* szSource, const unsigned int nSourceLen, const ::IDEA_KEY_SCHEDULE& ideaEncryptKey, npp::MemoryDataStream& dataEncrypted )
    {
        if ( !szSource || 0 == nSourceLen )
        {
            return false;
        }

        const unsigned int ALINE_LEN = 8;

        unsigned int nAlignSourceLen = H_ALIGN( nSourceLen, ALINE_LEN );

        if ( !dataEncrypted.setBufferSize( nAlignSourceLen + dataEncrypted.getSize() ) )
        {
            return false;
        }

        unsigned int nPos = 0;
        unsigned int nOctalCount = nSourceLen / 8;
        for ( unsigned int i = 0; i < nOctalCount; ++i )
        {
            nPos = i * ALINE_LEN;
            ::idea_ecb_encrypt( szSource + nPos, (unsigned char*)dataEncrypted.getCurWriteBuffer(), const_cast<IDEA_KEY_SCHEDULE*>( &ideaEncryptKey ) );
            dataEncrypted.seekp( ALINE_LEN );
        }

        bool b8BytesAlign = ( nAlignSourceLen == nSourceLen ); //whether the input is a multiple of 8
        if ( !b8BytesAlign )
        {
            unsigned char buf[ALINE_LEN] = { '\0' };
            if ( nOctalCount > 0 )
            {
                nPos += ALINE_LEN;
            }
            assert( nSourceLen > nPos );
            memcpy( buf, szSource + nPos, nSourceLen - nPos );
            ::idea_ecb_encrypt( buf, (unsigned char*)dataEncrypted.getCurWriteBuffer(), const_cast<IDEA_KEY_SCHEDULE*>( &ideaEncryptKey ) );
            dataEncrypted.seekp( ALINE_LEN );
        }

        return true;
    }


    void IDEA::encrypt( const unsigned char* in_buf, const unsigned int in_buf_len, const IDEA_KEY_SCHEDULE* key, mem_data_t* out_data )
    {
        if ( !in_buf || 0 == in_buf_len || !out_data->data )
        {
            out_data->data_len = 0;
            return;
        }

        const size_t ALINE_LEN = 8;
        size_t aligned_len = CCWEB_ALIGN( in_buf_len, ALINE_LEN );

        size_t pos = 0;
        size_t octal_count = in_buf_len / 8;
        size_t i = 0;
        for ( ; i < octal_count; ++i )
        {
            pos = i * ALINE_LEN;
            idea_ecb_encrypt( in_buf + pos, out_data->data + pos, const_cast<IDEA_KEY_SCHEDULE*>(key) );
        }

        //the input is not a multiple of 8
        if ( aligned_len != in_buf_len )
        {
            unsigned char buf[ALINE_LEN] = { '\0' };
            if ( octal_count > 0 )
            {
                pos += ALINE_LEN;
            }
            assert( in_buf_len > pos );
            memcpy( buf, in_buf + pos, in_buf_len - pos );
            ::idea_ecb_encrypt( buf, out_data->data + pos, const_cast<IDEA_KEY_SCHEDULE*>(key) );
        }

        out_data->data_len = aligned_len;
    }

    void IDEA::decrypt( const unsigned char* in_buf, const unsigned int in_buf_len, const IDEA_KEY_SCHEDULE* key, mem_data_t* out_data )
    {
        if ( !in_buf || 0 == in_buf_len || !out_data->data )
        {
            out_data->data_len = 0;
            return;
        }

        const size_t ALINE_LEN = 8;
        if ( in_buf_len % ALINE_LEN != 0 )
        {
            printf( "The input source data length is wrong, it SHOULD be a multiple of 8" );
            return;
        }

        size_t pos = 0;
        size_t octal_count = in_buf_len / 8;
        size_t i = 0;
        for ( ; i < octal_count; ++i )
        {
            pos = i * ALINE_LEN;
            idea_ecb_encrypt( in_buf + pos, out_data->data + pos, const_cast<IDEA_KEY_SCHEDULE*>(key) );
        }

        assert( pos == in_buf_len - ALINE_LEN );
        /* we cannot determine the orginal data length, 
         * we just know it is a multiple of 8
         */
        out_data->data_len = in_buf_len;
    }


    bool IDEA::decrypt( const unsigned char* szSource, const unsigned int nSourceLen, const std::string& strDecryptKey, npp::MemoryDataStream& dataDecrypted )
    {
        if ( strDecryptKey.length() != 16 )
        {
            assert( false && "The input parameter strDecryptKey MUST BE 16 bytes long." );
            return false;
        }

        if ( !szSource || 0 == nSourceLen )
        {
            return false;
        }

        const unsigned int ALINE_LEN = 8;

        if ( nSourceLen % ALINE_LEN != 0 )
        {
            assert( false && "The input source data length is wrong, it SHOULD be a multiple of 8" );
            return false;
        }

        ::IDEA_KEY_SCHEDULE keyIdeaEncrypt;
        ::IDEA_KEY_SCHEDULE keyIdeaDecrypt;
        ::idea_set_encrypt_key( ( u_char * )strDecryptKey.c_str(), &keyIdeaEncrypt );
        ::idea_set_decrypt_key( &keyIdeaEncrypt, &keyIdeaDecrypt);

        return decrypt( szSource, nSourceLen, keyIdeaDecrypt, dataDecrypted );
    }

    bool IDEA::decrypt( const unsigned char* szSource, const unsigned int nSourceLen, const ::IDEA_KEY_SCHEDULE& ideaDecryptKey, npp::MemoryDataStream& dataDecrypted )
    {
        if ( !szSource || 0 == nSourceLen )
        {
            return false;
        }

        const unsigned int ALINE_LEN = 8;

        if ( nSourceLen % ALINE_LEN != 0 )
        {
            assert( false && "The input source data length is wrong, it SHOULD be a multiple of 8" );
            return false;
        }


        if ( !dataDecrypted.setBufferSize( nSourceLen + dataDecrypted.getSize() ) )
        {
            return false;
        }

        unsigned int nDecryptBufOriginalLen = dataDecrypted.getSize();
        const unsigned char* pos = szSource;
        unsigned int nOctalCount = nSourceLen / 8;
        for ( unsigned int i = 0; i < nOctalCount; ++i )
        {
            ::idea_ecb_encrypt( pos + i * ALINE_LEN, (unsigned char*)dataDecrypted.getCurWriteBuffer(), const_cast<IDEA_KEY_SCHEDULE*>( &ideaDecryptKey ) );
            dataDecrypted.seekp( ALINE_LEN );
        }

        unsigned int nDecryptedDataLen = dataDecrypted.getSize() - nDecryptBufOriginalLen;
        if ( nDecryptedDataLen != nSourceLen )
        {
            assert( false && "Decrypt failed." );
            dataDecrypted.setSize( nDecryptBufOriginalLen );// discards the decrypted data and reset to original state
            return false;
        }

        return true;
    }



} // end of namespace ext

#endif // end of #if H_PROVIDE_IDEA_ENCRYPT
