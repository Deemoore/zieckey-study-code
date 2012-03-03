#include "netproto/include/inner_pre.h"

#include "netproto/include/data_stream.h"
#include "netproto/include/idea.h"


#if H_NPP_PROVIDE_IDEA_ENCRYPT

namespace npp
{
#define CCWEB_ALIGN H_ALIGN

    IDEA::IDEA()
    {
    }

    bool IDEA::initialize( const unsigned char key[16] )
    {
        return initialize(std::string((const char*)key, 16));
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
        return IDEA::encrypt((const unsigned char*)szSource, (const size_t)nSourceLen, m_encrypt_key, dataEncrypted);
    }

    bool IDEA::encrypt( const void* szSource, const size_t nSourceLen, 
        Padding padding, 
        void* data_encrypted, size_t& data_encrypted_len )
    {
        return IDEA::encrypt(szSource, nSourceLen, m_encrypt_key, padding, data_encrypted, data_encrypted_len);
    }

    size_t IDEA::getEncryptDataLen( Padding padding, size_t nSourceLen )
    {
        //! output buffer length checking
        if (padding == PaddingZero)
        {
            return H_ALIGN(nSourceLen, 8);
        }
        else if (padding == PaddingPKCS7)
        {
            return H_ALIGN( nSourceLen + 1, kAlignUnitLength8 );
        }
        else
        {
            assert(false);
            return (size_t)-1;
        }
    }

    bool IDEA::decrypt( const void* szSource, const size_t nSourceLen, MemoryDataStream& dataDecrypted )
    {
        return IDEA::decrypt(szSource, (const size_t)nSourceLen, m_decrypt_key, dataDecrypted);
    }

    bool IDEA::decrypt( const void* szSource, const size_t nSourceLen, Padding padding, void* data_decrypted, size_t& data_decrypted_len )
    {
        return IDEA::decrypt(szSource, (const size_t)nSourceLen, m_decrypt_key, padding, data_decrypted, data_decrypted_len);
    }

    bool IDEA::encrypt( const void* szSource, const size_t nSourceLen, const std::string& strEncryptKey, npp::MemoryDataStream& dataEncrypted )
    {
        return IDEA::encrypt(szSource, nSourceLen, strEncryptKey, PaddingZero, dataEncrypted);
    }

    bool IDEA::encrypt( const void* szSource, const size_t nSourceLen, const ::IDEA_KEY_SCHEDULE& ideaEncryptKey, npp::MemoryDataStream& dataEncrypted )
    {
        return IDEA::encrypt(szSource, nSourceLen, ideaEncryptKey, PaddingZero, dataEncrypted);
    }

    bool IDEA::encrypt( const void* szSource, const size_t nSourceLen, const std::string& strEncryptKey, Padding padding, npp::MemoryDataStream& dataEncrypted )
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
        return IDEA::encrypt(szSource, nSourceLen, ideakey, padding, dataEncrypted);
    }

    bool IDEA::encrypt( const void* szSource, const size_t nSourceLen, const ::IDEA_KEY_SCHEDULE& ideaEncryptKey, Padding padding, npp::MemoryDataStream& dataEncrypted )
    {
        size_t data_encrypted_len = getEncryptDataLen(padding, nSourceLen);
        dataEncrypted.reserve(data_encrypted_len);
        bool ok = IDEA::encrypt(szSource, nSourceLen, ideaEncryptKey, padding, dataEncrypted.getCache(), data_encrypted_len);
        if (ok)
        {
            dataEncrypted.seekp(data_encrypted_len);
            return true;
        }
        else
        {
            dataEncrypted.reset();
            return false;
        }
    }

    bool IDEA::encrypt( const void* szSource, const size_t nSourceLen, const std::string& strEncryptKey, Padding padding, void* data_encrypted, size_t& data_encrypted_len )
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
        return IDEA::encrypt(szSource, nSourceLen, ideakey, padding, data_encrypted, data_encrypted_len);
    }

    bool IDEA::encrypt( const void* szSource, const size_t nSourceLen, 
        const ::IDEA_KEY_SCHEDULE& ideaEncryptKey, Padding padding, 
        void* data_encrypted, size_t& data_encrypted_len )
    {
        if (!data_encrypted)
        {
            data_encrypted_len = 0;
            return false;
        }

        size_t aligned_len = getEncryptDataLen(padding, nSourceLen);

        if (data_encrypted_len < H_ALIGN(nSourceLen, 8))
        {
            data_encrypted_len = 0;
            return false;
        }

        unsigned char* in_buf  = (unsigned char*)szSource;
        unsigned char* out_buf = (unsigned char*)data_encrypted;

        size_t pos = 0;
        size_t octal_count = nSourceLen / 8;
        size_t i = 0;
        for ( ; i < octal_count; ++i )
        {
            idea_ecb_encrypt( in_buf + pos, out_buf + pos, const_cast<IDEA_KEY_SCHEDULE*>(&ideaEncryptKey) );
            pos += kAlignUnitLength8;
        }

        if (PaddingPKCS7 == padding)
        {
            unsigned char buf[kAlignUnitLength8] = {};
            assert( nSourceLen >= pos );
            size_t remain = nSourceLen - pos;
            assert( kAlignUnitLength8 > remain );
            if (remain > 0)
            {
                memcpy( buf, in_buf + pos, remain );
            }
            memset( buf + remain, kAlignUnitLength8 - remain, kAlignUnitLength8 - remain );
            ::idea_ecb_encrypt( buf, out_buf + pos, const_cast<IDEA_KEY_SCHEDULE*>(&ideaEncryptKey) );
            pos += kAlignUnitLength8;
        }
        else if (PaddingZero == padding)
        {
            if (0 != nSourceLen % 8)
            {
                //the input is not a multiple of 8
                unsigned char buf[kAlignUnitLength8] = {};
                assert( nSourceLen > pos );
                memcpy( buf, in_buf + pos, nSourceLen - pos );
                ::idea_ecb_encrypt( buf, out_buf + pos, const_cast<IDEA_KEY_SCHEDULE*>(&ideaEncryptKey) );
                pos += kAlignUnitLength8;
            }
        }
        else
        {
            assert(false);
            return false;
        }

        assert(pos == aligned_len);
        data_encrypted_len = aligned_len;
        return true;
    }

    bool IDEA::decrypt( const void* szSource, const size_t nSourceLen, const std::string& strDecryptKey, npp::MemoryDataStream& dataDecrypted )
    {
        return IDEA::decrypt(szSource, nSourceLen, strDecryptKey, PaddingZero, dataDecrypted);
    }
    
    bool IDEA::decrypt( const void* szSource, const size_t nSourceLen, const std::string& strDecryptKey, Padding padding, npp::MemoryDataStream& dataDecrypted )
    {
        if (strDecryptKey.length() != 16)
        {
            return false;
        }

        ::IDEA_KEY_SCHEDULE keyIdeaEncrypt;
        ::IDEA_KEY_SCHEDULE keyIdeaDecrypt;
        ::idea_set_encrypt_key( ( u_char * )strDecryptKey.c_str(), &keyIdeaEncrypt );
        ::idea_set_decrypt_key( &keyIdeaEncrypt, &keyIdeaDecrypt);
        
        size_t data_decrypted_len = nSourceLen;
        dataDecrypted.reserve(data_decrypted_len);
        bool ok = IDEA::decrypt(szSource, nSourceLen, keyIdeaDecrypt, PaddingZero, dataDecrypted.getCache(), data_decrypted_len);
        if (ok)
        {
            dataDecrypted.seekp(data_decrypted_len);
            return true;
        }
        else
        {
            dataDecrypted.reset();
            return false;
        }
    }

    bool IDEA::decrypt( const void* szSource, const size_t nSourceLen, const ::IDEA_KEY_SCHEDULE& ideaDecryptKey, Padding padding, npp::MemoryDataStream& dataDecrypted )
    {
        size_t data_decrypted_len = nSourceLen;
        dataDecrypted.reserve(data_decrypted_len);
        bool ok = IDEA::decrypt(szSource, nSourceLen, ideaDecryptKey, PaddingZero, dataDecrypted.getCache(), data_decrypted_len);
        if (ok)
        {
            dataDecrypted.seekp(data_decrypted_len);
            return true;
        }
        else
        {
            dataDecrypted.reset();
            return false;
        }
    }

    bool IDEA::decrypt( const void* szSource, const size_t nSourceLen, const ::IDEA_KEY_SCHEDULE& ideaDecryptKey, npp::MemoryDataStream& dataDecrypted )
    {
        return IDEA::decrypt(szSource, nSourceLen, ideaDecryptKey, PaddingZero, dataDecrypted);
    }

    bool IDEA::decrypt( const void* szSource, const size_t nSourceLen, const std::string& strDecryptKey, Padding padding, void* data_decrypted, size_t& data_decrypted_len )
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

        const size_t kAlignUnitLength8 = 8;

        if ( nSourceLen % kAlignUnitLength8 != 0 )
        {
            assert( false && "The input source data length is wrong, it SHOULD be a multiple of 8" );
            return false;
        }

        ::IDEA_KEY_SCHEDULE keyIdeaEncrypt;
        ::IDEA_KEY_SCHEDULE keyIdeaDecrypt;
        ::idea_set_encrypt_key( ( u_char * )strDecryptKey.c_str(), &keyIdeaEncrypt );
        ::idea_set_decrypt_key( &keyIdeaEncrypt, &keyIdeaDecrypt);

        return decrypt( szSource, nSourceLen, keyIdeaDecrypt, padding, data_decrypted, data_decrypted_len );
    }

    bool IDEA::decrypt( const void* szSource, const size_t in_buf_len, const ::IDEA_KEY_SCHEDULE& ideaDecryptKey, Padding padding, void* data_decrypted, size_t& data_decrypted_len )
    {
        if ( !szSource || 0 == in_buf_len || !data_decrypted || data_decrypted_len < in_buf_len )
        {
            data_decrypted_len = 0;
            return false;
        }

        if ( in_buf_len % kAlignUnitLength8 != 0 )
        {
            fprintf( stderr, "The input source data length is wrong, it SHOULD be a multiple of 8" );
            return false;
        }

        const unsigned char* in_buf = static_cast<const unsigned char*>(szSource);
        unsigned char* out_data = static_cast<unsigned char*>(data_decrypted);
        size_t pos = 0;
        size_t octal_count = in_buf_len / 8;
        size_t i = 0;
        for ( ; i < octal_count; ++i )
        {
            idea_ecb_encrypt( in_buf + pos, out_data + pos, const_cast<::IDEA_KEY_SCHEDULE*>(&ideaDecryptKey) );
            pos += kAlignUnitLength8;
        }

        assert(pos == in_buf_len);

        if (padding == PaddingZero)
        {
            /* we cannot determine the original data length, 
            * we just know it is a multiple of 8
            */
            data_decrypted_len = in_buf_len;
        }
        else if (padding == PaddingPKCS7)
        {
            assert(out_data[pos - 1] <= 8);
            assert(out_data[pos - 1] > 0);
            data_decrypted_len -= out_data[pos - 1];
        }
        else
        {
            assert(false && "Not supported!");
            data_decrypted_len = 0;
            return false;
        }

        return true;
    }

    void IDEA::encrypt( const unsigned char* in_buf, const size_t in_buf_len, const IDEA_KEY_SCHEDULE* key, mem_data_t* out_data )
    {
        if ( !in_buf || 0 == in_buf_len || !out_data->data )
        {
            out_data->data_len = 0;
            return;
        }

        const size_t kAlignUnitLength8 = 8;
        size_t aligned_len = CCWEB_ALIGN( in_buf_len, kAlignUnitLength8 );

        size_t pos = 0;
        size_t octal_count = in_buf_len / 8;
        size_t i = 0;
        for ( ; i < octal_count; ++i )
        {
            pos = i * kAlignUnitLength8;
            idea_ecb_encrypt( in_buf + pos, out_data->data + pos, const_cast<IDEA_KEY_SCHEDULE*>(key) );
        }

        //the input is not a multiple of 8
        if ( aligned_len != in_buf_len )
        {
            unsigned char buf[kAlignUnitLength8] = { '\0' };
            if ( octal_count > 0 )
            {
                pos += kAlignUnitLength8;
            }
            assert( in_buf_len > pos );
            memcpy( buf, in_buf + pos, in_buf_len - pos );
            ::idea_ecb_encrypt( buf, out_data->data + pos, const_cast<IDEA_KEY_SCHEDULE*>(key) );
        }

        out_data->data_len = aligned_len;
    }


    void IDEA::decrypt( const unsigned char* in_buf, const size_t in_buf_len, const IDEA_KEY_SCHEDULE* key, mem_data_t* out_data )
    {
        if ( !in_buf || 0 == in_buf_len || !out_data->data )
        {
            out_data->data_len = 0;
            return;
        }

        const size_t kAlignUnitLength8 = 8;
        if ( in_buf_len % kAlignUnitLength8 != 0 )
        {
            printf( "The input source data length is wrong, it SHOULD be a multiple of 8" );
            return;
        }

        size_t pos = 0;
        size_t octal_count = in_buf_len / 8;
        size_t i = 0;
        for ( ; i < octal_count; ++i )
        {
            pos = i * kAlignUnitLength8;
            idea_ecb_encrypt( in_buf + pos, out_data->data + pos, const_cast<IDEA_KEY_SCHEDULE*>(key) );
        }

        assert( pos == in_buf_len - kAlignUnitLength8 );
        /* we cannot determine the original data length, 
        * we just know it is a multiple of 8
        */
        out_data->data_len = in_buf_len;
    }

} // end of namespace ext

#endif // end of #if H_NPP_PROVIDE_IDEA_ENCRYPT



