#ifndef NETPROTO_ENCRYPT_UTILITY_H_
#define NETPROTO_ENCRYPT_UTILITY_H_

#include "netproto/include/config.h"
#include "netproto/include/platform_micros.h"
#include "netproto/include/data_stream.h"

#ifdef H_NPP_PROVIDE_IDEA_ENCRYPT

#include <idea/idea.h>
#include "netproto/include/symmetric_encrypt.h"

namespace npp
{


    class _EXPORT_NETPROTO IDEA : public SymmetricEncryptor
    {
    public:
        enum Padding
        {
            PaddingZero,
            PaddingPKCS7,
        };

        enum { kAlignUnitLength8 = 8 };

    public:
        IDEA();

        bool initialize(const unsigned char key[16]);
        bool initialize(const std::string& key);

        //! \brief IDEA encrypt
        //! \param const void*  szSource - the input source data
        //! \param const size_t nSourceLen - the source data length
        //! \param[out] npp::MemoryDataStream & encrypt_data - the encrypted data is stored here
        //! \param[out] void* encrypt_data - the encrypted data is stored here.
        //!     Make sure the buffer size of <code>encrypt_data</code> is at least H_ALIGN(nSourceLen, 8)
        //! \return bool - true if encrypts successfully
        bool encrypt( const void* szSource, const size_t nSourceLen, MemoryDataStream& data_encrypted );


        //! \brief 
        //! \param[in] - const void * szSource
        //! \param[in] - const size_t nSourceLen
        //! \param[in] - Padding padding
        //! \param[out] - void * data_encrypted
        //! \param[in, out] - size_t & data_encrypted_len
        //! \return - bool
        bool encrypt( const void* szSource, const size_t nSourceLen, Padding padding, void* data_encrypted, size_t& data_encrypted_len);
        
        
        //! \brief Get the encrypt data length which will be allocated for storing the encrypted data
        //! \param[in] - Padding padding
        //! \param[in] - size_t nSourceLen
        //! \return - size_t
        static size_t getEncryptDataLen(Padding padding, size_t nSourceLen);

        //! \brief IDEA decrypt
        //! \param const void*  szSource - the input source data
        //! \param const size_t nSourceLen - the source data length
        //! \param npp::MemoryDataStream & data_decrypted - the decrypted data is stored here
        //! \return bool - true if decrypts successfully
        bool decrypt( const void* szSource, const size_t nSourceLen, MemoryDataStream& data_decrypted );

        //! \brief 
        //! \param[in] - const void * szSource
        //! \param[in] - const size_t nSourceLen
        //! \param[in] - Padding padding
        //! \param[out] - void * data_decrypted
        //! \param[in,out] - size_t & data_decrypted_len
        //! \return - bool
        bool decrypt( const void* szSource, const size_t nSourceLen, Padding padding, void* data_decrypted, size_t& data_decrypted_len);
        bool decrypt( const void* szSource, const size_t nSourceLen, Padding padding, MemoryDataStream& data_decrypted );

        //Overridden from SymmetricEncryptor
    public:
        //! Initialize the encrypt
        virtual bool Initialize(const unsigned char* key, size_t key_len);

        //! Create a random key and stored the value to <code>key</code>
        //! \paran[out] key - 
        virtual std::string CreateRandomKey();

        //! \brief 
        //! \param[in] - const void * szSource
        //! \param[in] - const size_t nSourceLen
        //! \param[in] - Padding padding
        //! \param[out] - void * data_encrypted
        //! \param[in, out] - size_t & data_encrypted_len
        //! \return - bool
        virtual bool Encrypt( const void* szSource, const size_t nSourceLen, void* data_encrypted, size_t& data_encrypted_len);


        //! \brief Get the encrypt data length which will be allocated for storing the encrypted data
        //! \param[in] - Padding padding
        //! \param[in] - size_t nSourceLen
        //! \return - size_t
        virtual size_t GetEncryptDataLength(size_t nSourceLen);

        //! \brief 
        //! \param[in] - const void * szSource
        //! \param[in] - const size_t nSourceLen
        //! \param[in] - Padding padding
        //! \param[out] - void * data_decrypted
        //! \param[in,out] - size_t & data_decrypted_len
        //! \return - bool
        virtual bool Decrypt( const void* szSource, const size_t nSourceLen, void* data_decrypted, size_t& data_decrypted_len);

        //! \brief Get the encrypt data length which will be allocated for storing the encrypted data
        //! \param[in] - Padding padding
        //! \param[in] - size_t nSourceLen
        //! \return - size_t
        virtual size_t GetDecryptDataLength(const void* encrypted_data, size_t encrypted_data_len);

        //! Return the encrypt key length
        virtual std::string GetEncryptKey() { return m_original_key;}

    public:
        //! \brief IDEA encrypt
        //! \param const unsigned char*  szSource - the input source data
        //! \param const size_t nSourceLen - the source data length
        //! \param const std::string & strEncryptKey - the 16 bytes long encrypting key
        //! \param npp::MemoryDataStream & dataEncrypted - the encrypted data is stored here
        //! \return bool - true if encrypts successfully
        static bool encrypt( const void* szSource, const size_t nSourceLen, const std::string& strEncryptKey, npp::MemoryDataStream& dataEncrypted );
        static bool encrypt( const void* szSource, const size_t nSourceLen, const ::IDEA_KEY_SCHEDULE& ideaEncryptKey, npp::MemoryDataStream& dataEncrypted );

        static bool encrypt( const void* szSource, const size_t nSourceLen, 
                             const std::string& strEncryptKey, Padding padding, 
                             npp::MemoryDataStream& dataEncrypted );

        static bool encrypt( const void* szSource, const size_t nSourceLen, 
                             const ::IDEA_KEY_SCHEDULE& ideaEncryptKey, Padding padding, 
                             npp::MemoryDataStream& dataEncrypted );

        static bool encrypt( const void* szSource, const size_t nSourceLen, 
                             const std::string& strEncryptKey, Padding padding, 
                             void* data_encrypted, size_t& data_rncrypted_len );
        static bool encrypt( const void* szSource, const size_t nSourceLen, 
                             const ::IDEA_KEY_SCHEDULE& ideaEncryptKey, Padding padding,
                             void* data_encrypted, size_t& data_encrypted_len );

        //! \brief IDEA decrypt
        //! \param const unsigned char*  szSource - the input source data
        //! \param const size_t nSourceLen - the source data length
        //! \param const std::string & strDecryptKey - the 16 bytes long decrypting key
        //! \param npp::MemoryDataStream & dataDecrypted - the decrypted data is stored here
        //! \return bool - true if decrypts successfully
        static bool decrypt( const void* szSource, const size_t nSourceLen, const std::string& strDecryptKey, npp::MemoryDataStream& dataDecrypted );
        static bool decrypt( const void* szSource, const size_t nSourceLen, const ::IDEA_KEY_SCHEDULE& ideaDecryptKey, npp::MemoryDataStream& dataDecrypted );

        static bool decrypt( const void* szSource, const size_t nSourceLen, const std::string& strDecryptKey, Padding padding, npp::MemoryDataStream& dataDecrypted);
        static bool decrypt( const void* szSource, const size_t nSourceLen, const ::IDEA_KEY_SCHEDULE& ideaDecryptKey, Padding padding, npp::MemoryDataStream& dataDecrypted);

        static bool decrypt( const void* szSource, const size_t nSourceLen, const std::string& strDecryptKey, Padding padding, void* data_decrypted, size_t& data_decrypted_len);
        static bool decrypt( const void* szSource, const size_t nSourceLen, const ::IDEA_KEY_SCHEDULE& ideaDecryptKey, Padding padding, void* data_decrypted, size_t& data_decrypted_len);

    public:
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //Only for test, don't use it
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        typedef struct {
            /*{{{*/
            u_char* data;   /** The memory data */
            size_t data_len;/** The length of data */
            /*}}}*/
        } mem_data_t;

        //Only for test, don't use it
        //! param[out] mem_data_t* out_data - The decrypted/encrypted data is stored here
        //!      The memory MUST BE allocated before you call this.
        static void encrypt( const unsigned char* in_buf, const size_t in_buf_len, const IDEA_KEY_SCHEDULE* key, mem_data_t* out_data );
        static void decrypt( const unsigned char* in_buf, const size_t in_buf_len, const IDEA_KEY_SCHEDULE* key, mem_data_t* out_data );
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------

    private:
        std::string       m_original_key;
        IDEA_KEY_SCHEDULE m_encrypt_key;
        IDEA_KEY_SCHEDULE m_decrypt_key;
    };
} // end of namespace ext

#endif // end of #ifdef H_NPP_PROVIDE_IDEA_ENCRYPT



#endif //end of #ifndef Q_APP_UTILITY_ENCRYPT_UTILITY_H_




