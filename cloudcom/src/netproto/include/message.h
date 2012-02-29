/****************************** Module Header ********************************\
    Name: packet.h
 Created: 2012/02/24 24:2:2012 0:14
  Author: weizili

 Purpose: 
\*****************************************************************************/

#ifndef NETPROTO_PACKET_H_
#define NETPROTO_PACKET_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/data_stream.h"

#define _DEBUG_TEST

#ifndef H_OS_WINDOWS
#include <arpa/inet.h>
#endif


namespace npp
{

    class _EXPORT_NETPROTO Message : public MemoryDataStream
    {
    public:
        enum EncryptMethod
        {
            kNoEncrypt   = 0,
            kXorEncrypt  = 1,//not use this
            kIDEAEncrypt = 2,
        };

        enum SignMethod
        {
            kOpenSSLRSA0 = 0, //! OpenSSL RSA
            kSimpleRSA   = 1, //! Simple RSA
            kOpenSSLRSA2 = 2, //! OpenSSL RSA, the same as kOpenSSLRSA0
        };

        enum ErrorCode
        {
            kNoError = 0,

            kParameterError,

            kVesionError,

            kMemoryNotEnough,

            kNotSupportOpenSSLRSA,          //! Not supported OpenSSL sign/verify method
            kNotSupportOpenSSLRSAKeyNumber, //! A Not Supported OpenSSL sign_ key number
            kNotSupportSimpleRSAKeyNumber,  //! A Not Supported Simple RSA sign_ key number
            kNotSupportIDEAKeyNumber,       //! A Not Supported IDEA key number

            kNppHeaderDataLengthError,
            kDigestVerifyFailed,
            kOpenSSLRSAVerifyFailed,
            kSimpleRSAVerifyFailed,

            kOpenSSLRSASignFailed,
            kSimpleRSASignFailed,

            kIDEADecryptFialed,

            kNotSupportSignMethod,
            kNotSupportEncryptMethod,

            kNotSupportPlainData,
            kNotSupportXorEncrypt,

        };
    public:
        //! The header information struct of the data packet 
#pragma pack(push,1)
        struct NetHeader
        {
            uint8_t  header_len_;    //! in bytes 
            uint8_t  version_;       //! The protocol version
            uint16_t data_len_;      //! big-endian, the length of the data 
            uint16_t message_id_;    //! big-endian, client generate randomly
            uint8_t  packet_seq_;
            uint8_t  packet_count_;
            uint16_t preserve_;      //! big-endian, preserved, set to 0x0000


            void Init()
            {
                memset(this, 0, sizeof(*this));
                header_len_ = sizeof(*this);
                version_ = 1;
                packet_count_ = 1;
            }

            uint8_t  version() const { return version_; }
            void     set_version(uint8_t val) { version_ = val; }

            uint16_t data_len() const { return data_len_; }
            void     set_data_len(uint16_t val) { data_len_ = val; }

            uint16_t message_id() const { return message_id_; }
            void     set_message_id(uint16_t val) { message_id_ = val; }

            uint8_t  packet_seq() const { return packet_seq_; }
            void     set_packet_seq(uint8_t val) { packet_seq_ = val; }

            uint8_t  packet_count() const { return packet_count_; }
            void     set_packet_count(uint8_t val) { packet_count_ = val; }

            uint16_t preserve() const { return preserve_; }
            void     set_preserve(uint16_t val) { preserve_ = val; }
        };

        struct NppHeader
        {
            union
            {
                struct 
                {
                    uint8_t encrypt_key_no_:4; /** the number of the encrypt_ key  */
                    uint8_t encrypt_method_:4; /** the encrypt_ method, 0:no encrypt_; 1:XOR; 2:idea */
                };
                uint8_t encrypt_;
            };
            union
            {
                struct 
                {
                    uint8_t sign_key_no_:4; /** The key number of the sign_ */
                    uint8_t sign_method_:4; /** the sign_ method */
                };
                uint8_t sign_;
            };
            uint8_t digest_sign_len_;/** The length of the sign_ and digest */

            void Init()
            {
#ifdef H_OS_WINDOWS
                encrypt_key_no_ = 2; //client program
#else
                encrypt_key_no_ = 1; //server program
#endif
                encrypt_method_  = kIDEAEncrypt;
                //sign_method_     = kSimpleRSA;
                sign_method_     = kOpenSSLRSA0;
                sign_key_no_     = 1;
                digest_sign_len_ = 128 + 16;
            }

            uint8_t encrypt_key_no() const { return encrypt_key_no_; }
            void    set_encrypt_key_no(uint8_t val) { encrypt_key_no_ = val; }
            uint8_t encrypt_method() const { return encrypt_method_; }
            void    set_encrypt_method(uint8_t val) { encrypt_method_ = val; }

            uint8_t sign_key_no() const { return sign_key_no_; }
            void    set_sign_key_no(uint8_t val) { sign_key_no_ = val; }
            uint8_t sign_method() const { return sign_method_; }
            void    set_sign_method(uint8_t val) { sign_method_ = val; }
        };
#pragma pack(pop)


    public:
        Message();
        virtual ~Message();

        //! Get the packet/unpacked data and size if packing/unpacking successfully
        const char* Data();
        size_t Size();

        //! Get the last ErrorCode
        ErrorCode last_error() const { return last_error_; }

        //! Get the error string
        const char* strerror() const;

    protected:
        //! Set the last ErrorCode
        void last_error(ErrorCode val) { last_error_ = val; }

    private:
        ErrorCode last_error_;
    };

}

#endif

