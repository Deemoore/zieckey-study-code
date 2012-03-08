#ifndef NETPROTO_SYMMETRIC_ENCRYPT_H_
#define NETPROTO_SYMMETRIC_ENCRYPT_H_

#include "netproto/include/config.h"
#include "netproto/include/platform_micros.h"
#include "netproto/include/auto_delete.h"

namespace npp
{
    class _EXPORT_NETPROTO SymmetricEncryptor
    {
    public:
        virtual ~SymmetricEncryptor() {}

        //! Initialize the encrypt
        virtual bool Initialize(const unsigned char* key, size_t key_len) = 0;

        //! Create a random key and stored the value to <code>key</code>
        //! \paran[out] key - 
        virtual std::string CreateRandomKey() = 0;

        //! \brief 
        //! \param[in] - const void * szSource
        //! \param[in] - const size_t nSourceLen
        //! \param[in] - Padding padding
        //! \param[out] - void * data_encrypted
        //! \param[in, out] - size_t & data_encrypted_len
        //! \return - bool
        virtual bool Encrypt( const void* szSource, const size_t nSourceLen, void* data_encrypted, size_t& data_encrypted_len) = 0;
        
        
        //! \brief Get the encrypt data length which will be allocated for storing the encrypted data
        //! \param[in] - Padding padding
        //! \param[in] - size_t nSourceLen
        //! \return - size_t
        virtual size_t GetEncryptDataLength(size_t nSourceLen) = 0;

        //! \brief 
        //! \param[in] - const void * szSource
        //! \param[in] - const size_t nSourceLen
        //! \param[in] - Padding padding
        //! \param[out] - void * data_decrypted
        //! \param[in,out] - size_t & data_decrypted_len
        //! \return - bool
        virtual bool Decrypt( const void* szSource, const size_t nSourceLen, void* data_decrypted, size_t& data_decrypted_len) = 0;

        //! \brief Get the encrypt data length which will be allocated for storing the encrypted data
        //! \param[in] - Padding padding
        //! \param[in] - size_t nSourceLen
        //! \return - size_t
        virtual size_t GetDecryptDataLength(const void* encrypted_data, size_t encrypted_data_len) = 0;

        //! Get the encrypt key
        virtual std::string GetEncryptKey() = 0;
    };


    class _EXPORT_NETPROTO SymmetricEncryptorFactory
    {
    public:
        static SymmetricEncryptor* CreateSymmetricEncryptor(int encrypt_method);
        static void DesstorySymmetricEncryptor(SymmetricEncryptor* c);
    };

} // end of namespace ext


namespace npp { 
    namespace ext {
        template<> inline
            auto_delete< npp::SymmetricEncryptor >::~auto_delete()
        {
            if ( ptr_ref_to_be_deleted_ )
            {
                npp::SymmetricEncryptorFactory::DesstorySymmetricEncryptor(ptr_ref_to_be_deleted_);
                ptr_ref_to_be_deleted_ = NULL;
            }
        }
    }
}


#endif 





