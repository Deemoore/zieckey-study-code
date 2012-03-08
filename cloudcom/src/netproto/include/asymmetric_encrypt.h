#ifndef NETPROTO_ASYMMETRIC_ENCRYPT_H_
#define NETPROTO_ASYMMETRIC_ENCRYPT_H_

#include "netproto/include/config.h"
#include "netproto/include/platform_micros.h"
#include "netproto/include/auto_delete.h"

namespace npp
{
    class _EXPORT_NETPROTO AsymmetricEncryptor
    {
    public:
        //! \brief public encrypt method
        //! \param[in] - const void * m
        //! \param[in] - const size_t m_len
        //! \param[out] - unsigned char * sigret
        //! \param[in,out] - size_t * siglen
        //! \return - bool
        virtual bool PublicEncrypt(const void* m, const size_t m_len, void* sigret, size_t* siglen) = 0;

        virtual bool PrivateDecrypt(const void* sig, const size_t sig_len, void* plain_data, size_t* plain_data_len) = 0;

        virtual bool PrivateEncrypt(const void* m, const size_t m_len, void* sigret, size_t* siglen) = 0;

        virtual bool PublicDecrypt(const void* sig, const size_t sig_len, void* plain_data, size_t* plain_data_len) = 0;
        
        
        //! \brief Get the encrypt data length which will be allocated for storing the encrypted data
        //! \return - size_t
        virtual size_t GetEncryptDataLength() = 0;

        //! \brief Get the encrypt data length which will be allocated for storing the encrypted data
        //! \param[in] - Padding padding
        //! \param[in] - size_t nSourceLen
        //! \return - size_t
        virtual size_t GetDecryptDataLength() = 0;
    };


    class _EXPORT_NETPROTO AsymmetricEncryptorFactory
    {
    public:
        static AsymmetricEncryptor* GetAsymmetricEncryptor(int encrypt_method, int key_no);
    };

} // end of namespace ext


#endif 





