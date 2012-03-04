

#ifndef NETPROTO_MESSAGE_UNPACKER_H_
#define NETPROTO_MESSAGE_UNPACKER_H_

#include "netproto/include/inner_pre.h"
#include "netproto/include/message.h"

namespace npp
{
    class MessagePacker;
    class _EXPORT_NETPROTO MessageUnpacker : public Message
    {
    public:
        bool Unpack(const void* data, size_t data_len);
        
        //! Get the unpacked data and size if packing successfully
        const char* Data() const;
        size_t Size() const;

    private:
        //! \brief 
        //! \param const void * digest - The digest
        //! \param size_t digest_len - 
        //! \param const void * d - The source data to be verified
        //! \param size_t d_len - 
        //! \return bool - 
        bool VerifyDigest(const void* digest, size_t digest_len, const void* d, size_t d_len);

        //! \brief 
        //! \param const char * digest - A pointer to the digest data
        //! \return bool - 
        bool VerifyOpenSSLRSASign(const char* digest);

        //! \brief 
        //! \param const char * digest - A pointer to the digest data
        //! \return bool - 
        bool VerifySimpleRSASign(const char* digest);

        //! Verify sign
        bool VerifySign(const char* digest, size_t data_len);

        //! Decrypt data
        bool DecryptData(const char* encrypt_data, size_t encrypt_data_len);


    public:
        //! The interface for MessagePacker, don't use it
        const NetHeader& net_header(const MessagePacker& caller) const { return net_header_; }
        const NppHeader& npp_header(const MessagePacker& caller) const { return npp_header_; }
        bool IsUnpackedOK(const MessagePacker& caller) const { return last_error() == kNoError && Data() != NULL;}

    private:
        bool unpack_v1(const void* d, size_t d_len);
    private:
        NetHeader net_header_;  //! The network data header
        NppHeader npp_header_;  //! The protocol relative header

        std::string unpacked_data_;
    };
}

#endif

