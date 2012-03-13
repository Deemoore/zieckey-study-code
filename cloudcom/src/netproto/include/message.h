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

    class _EXPORT_NETPROTO Message
    {
    public:
        enum{ kMD5HexLen = 16 };

        enum ProtoVersion
        {
            kProtoVersion1 = 1,
            kProtoVersion2 = 2,
        };

        enum SymmetricEncryptMethod
        {
            kNoSymmetricEncrypt   = 0,
            kXorSymmetricEncrypt  = 1,//not use this
            kIDEASymmetricEncrypt = 2,
            kSymmetricEncryptMethodNum,
        };

        enum AsymmetricEncryptMethod
        {
            kOpenSSLRSA0 = 0, //! OpenSSL RSA
            kSimpleRSA   = 1, //! Simple RSA
            kOpenSSLRSA2 = 2, //! OpenSSL RSA, the same as kOpenSSLRSA0
            kAsymmetricEncryptMethodNum
        };

        enum AsymmetricPublicPrivateMethod
        {
            kAsymmetricPublicEncrypt   = 0,
            kAsymmetricPrivateEncrypt  = 1,
            kAsymmetricPublicPrivateMethodNum
        };

        enum CompressMethod
        {
            kNoComress   = 0,
            kZlibCompress  = 1,
            kCompressNum
        };

        enum ErrorCode
        {
            kNoError = 0,

            kParameterErrorNULLPointer,
            kParameterErrorDataLengthError,

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

            kIDEAEncryptFialed,
            kIDEADecryptFialed,

            kNotSupportSignMethod,
            kNotSupportSymmetricEncryptMethod,
            kNotSupportAsymmetricPublicPrivateMethod,
            kNotSuportCompressMethod,

            kNotSupportPlainData,
            kNotSupportXorEncrypt,

            kCompressError,
            kUncompressError,
            kSymmetricEncyptFailed,
            kAsymmetricPublicEncryptFailed,
            kAsymmetricPrivateDecryptFailed,
            kAsymmetricPrivateEncryptFailed,
            kAsymmetricPublicDecryptFailed,

            kServerResponseParameterError,

        };

        enum ResponseErrorCodeV2
        {
            kRequestSuccess = 0,
            kInvalidRequest = 1,
            kInvalidClientPublicKey = 2,
            kServerInternalError = 3,
        };
    public:
        //! The header information struct of the data packet 
#pragma pack(push,1)
        struct NetHeaderV1
        {
            uint8_t  header_len_;    //! in bytes 
            uint8_t  version_;       //! The protocol version
            uint16_t data_len_;      //! big-endian, the length of the data 
            uint16_t message_id_;    //! big-endian, client generate randomly
            uint8_t  packet_seq_;
            uint8_t  packet_count_;
            uint16_t reserve_;      //! big-endian, preserved, set to 0x0000


            void Init()
            {
                memset(this, 0, sizeof(*this));
                header_len_ = sizeof(*this);
                version_ = kProtoVersion1;
                packet_count_ = 1;
            }

//             void InitV2()
//             {
//                 memset(this, 0, sizeof(*this));
//                 header_len_ = sizeof(*this);
//                 version_ = kProtoVersion2;
//                 packet_count_ = 1;
//             }

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

            uint16_t reserve() const { return reserve_; }
            void     set_reserve(uint16_t val) { reserve_ = val; }
        };

        struct NppHeaderV1
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
                encrypt_method_  = kIDEASymmetricEncrypt;
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

        struct NetHeaderV2
        {
            uint8_t  header_len_;    //! in bytes 
            uint8_t  version_;       //! The protocol version
            uint32_t data_len_;      //! big-endian, the length of the data 
            uint16_t message_id_;    //! big-endian, client generate randomly
            uint8_t  packet_seq_;
            uint8_t  packet_count_;
            uint16_t reserve_;      //! big-endian, preserved, set to 0x0000

            void Init()
            {
                memset(this, 0, sizeof(*this));
                header_len_ = sizeof(*this);
                version_ = kProtoVersion2;
                packet_count_ = 1;
            }

            uint8_t  version() const { return version_; }
            void     set_version(uint8_t val) { version_ = val; }

            uint32_t data_len() const { return data_len_; }
            void     set_data_len(uint32_t val) { data_len_ = val; }

            uint16_t message_id() const { return message_id_; }
            void     set_message_id(uint16_t val) { message_id_ = val; }

            uint8_t  packet_seq() const { return packet_seq_; }
            void     set_packet_seq(uint8_t val) { packet_seq_ = val; }

            uint8_t  packet_count() const { return packet_count_; }
            void     set_packet_count(uint8_t val) { packet_count_ = val; }

            uint16_t reserve() const { return reserve_; }
            void     set_reserve(uint16_t val) { reserve_ = val; }
        };

        struct NppRequestHeaderV2
        {
            uint8_t  symmetric_encrypt_method_;  //! the symmetric encrypt method, 0:no encrypt_; 1:Reserved; 2:idea 
            union
            {
                struct 
                {
                    uint8_t asymmetric_encrypt_method_:6; //! the asymmetric encrypt method, 0:OpenSSL RSA; 1:Simple RSA; 2:Reserved 
                    uint8_t asymmetric_pub_priv_method_:2; //! 
                };
                uint8_t asymmetric_encrypt_;
            };
            uint8_t  asymmetric_encrypt_key_no_;   //! the asymmetric encrypt key number
            uint8_t  compress_method_;             //! The compress algorithm ; 0£ºno compress; 1£ºzlib
            uint16_t asymmetric_encrypt_data_len_; //! The length of asymmetric encrypted data of symmetric_encrypt_key

            NppRequestHeaderV2();

            size_t GetSymmetricEncryptDataLength(size_t data_len, ErrorCode& ec) const;

            size_t GetSignLength(ErrorCode& ec);

            uint8_t  symmetric_encrypt_method() const { return symmetric_encrypt_method_; }
            void     set_symmetric_encrypt_method(uint8_t val) { symmetric_encrypt_method_ = val; }

            uint8_t  asymmetric_encrypt_method() const { return asymmetric_encrypt_method_; }
            void     set_asymmetric_encrypt_method(uint8_t val) { asymmetric_encrypt_method_ = val; }

            uint8_t  asymmetric_pub_priv_method() const { return asymmetric_pub_priv_method_; }
            void     set_asymmetric_pub_priv_method(uint8_t val) { asymmetric_pub_priv_method_ = val; }

            uint8_t  asymmetric_encrypt_key_no() const { return asymmetric_encrypt_key_no_; }
            void     set_asymmetric_encrypt_key_no(uint8_t val) { asymmetric_encrypt_key_no_ = val; }

            uint8_t  compress_method() const { return compress_method_; }
            void     set_compress_method(uint8_t val) { compress_method_ = val; }

            uint16_t asymmetric_encrypt_data_len() const { return asymmetric_encrypt_data_len_; }
            void     set_asymmetric_encrypt_data_len(uint16_t val) { asymmetric_encrypt_data_len_ = val; }
        };

        struct NppResponseHeaderV2
        {
            uint8_t error_code_;                //! 0 success. 1 failed. 2 client asymmetric public key invalid  . enum ResponseErrorCodeV2
            uint8_t compress_method_;           //! The compress algorithm ; 0£ºno compress; 1£ºzlib
            uint8_t md5_[16];

            uint8_t compress_method() const { return compress_method_; }
            void    set_compress_method(uint8_t val) { compress_method_ = val; }
            uint8_t error_code() const { return error_code_; }
            void    set_error_code(uint8_t val) { error_code_ = val; }
            const uint8_t* md5() const { return md5_; }
            void    set_md5(uint8_t* val, size_t len = 16) { memcpy(md5_, val, len <= sizeof(md5_) ? len : sizeof(md5_)); }
        };
#pragma pack(pop)


    public:
        Message();
        virtual ~Message();

        //! Get the last ErrorCode
        ErrorCode last_error() const { return last_error_; }

        //! Get the error string
        const char* strerror() const;

    protected:
        //! Set the last ErrorCode
        void last_error(ErrorCode val) 
        { 
            last_error_ = val; 
        }

    protected:


//         bool _DecryptAndUncompressData( const char* encrypt_data, size_t encrypt_data_len, const std::string& symmetric_encrypt_key )
//         {
//             switch (npp_request_header_v2_.symmetric_encrypt_method())
//             {
//             case kNoSymmetricEncrypt:
//                 if (!s_pNppConfig->support_plain())
//                 {
//                     last_error(kNotSupportPlainData);
//                     return false;
//                 }
// 
//                 return _Uncompress(encrypt_data, encrypt_data_len);
//                 break;
//             case kXorSymmetricEncrypt:
//                 last_error(kNotSupportXorEncrypt);
//                 return false;
//                 break;
//             case kIDEASymmetricEncrypt:
//                 {
//                     symmetric_encryptor_ = SymmetricEncryptorFactory::CreateSymmetricEncryptor(npp_request_header_v2_.symmetric_encrypt_method());
//                     if (!symmetric_encryptor_)
//                     {
//                         last_error(kNotSupportIDEAKeyNumber);
//                         return false;
//                     }
//                     bool init_ok = symmetric_encryptor_->Initialize((const unsigned char*)symmetric_encrypt_key.data(), symmetric_encrypt_key.size());
//                     assert(init_ok);
//                     return _DecryptAndUncompressData(symmetric_encryptor_, encrypt_data, encrypt_data_len);
//                 }
//                 break;
//             default:
//                 last_error(kNotSupportSymmetricEncryptMethod);
//                 return false;
//                 break;
//             }
//         }
// 
//         bool _DecryptAndUncompressData( SymmetricEncryptor* e, const char* encrypt_data, size_t encrypt_data_len )
//         {
//             size_t decrypted_data_len = e->GetDecryptDataLength(encrypt_data, encrypt_data_len);
//             if (npp_request_header_v2_.compress_method() == kNoComress)
//             {
//                 unpacked_data_.resize(decrypted_data_len);
//                 if (!e->Decrypt(encrypt_data, decrypted_data_len, &unpacked_data_[0], decrypted_data_len))
//                 {
//                     last_error(kIDEADecryptFialed);
//                     return false;
//                 }
//                 assert(encrypt_data_len <= unpacked_data_.size());
//                 if (decrypted_data_len < unpacked_data_.size())
//                 {
//                     unpacked_data_.resize(decrypted_data_len);
//                 }
//                 return true;
//             }
// 
//             std::string decrypted_data; //the decrypted data which is compressed
//             decrypted_data.resize(decrypted_data_len);
//             if (!e->Decrypt(encrypt_data, decrypted_data_len, &decrypted_data[0], decrypted_data_len))
//             {
//                 last_error(kIDEADecryptFialed);
//                 return false;
//             }
//             assert(encrypt_data_len <= decrypted_data.size());
//             if (decrypted_data_len < decrypted_data.size())
//             {
//                 decrypted_data.resize(decrypted_data_len);
//             }
// 
//             return _Uncompress(decrypted_data.data(), decrypted_data_len);
//         }

        //! \brief 
        //! \param const void * data - The data to be calculate MD5
        //! \param size_t data_len - 
        //! \param uint8_t * write_pos - It MUST be large enough to hold 16 bytes
        //! \return void - 
        static void CalcMD5AndWrite( const void* data, size_t data_len, uint8_t* write_pos );

        //! \brief 
        //! \param const void * digest - The digest
        //! \param size_t digest_len - 
        //! \param const void * d - The source data to be verified
        //! \param size_t d_len - 
        //! \return bool - 
        bool VerifyDigest(const void* digest, size_t digest_len, const void* d, size_t d_len);

    private:
        ErrorCode last_error_;
    };

}

#endif

