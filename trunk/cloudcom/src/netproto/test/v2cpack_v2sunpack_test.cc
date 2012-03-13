#include "netproto/include/test_common.h"

#include "netproto/include/npp_config.h"
#include "netproto/include/v1_message_packer.h"
#include "netproto/include/v1_message_unpacker.h"
#include "netproto/include/idea.h"
#include "netproto/include/v2c_request_packer.h"
#include "netproto/include/v2s_request_unpacker.h"
#include "netproto/include/v2c_response_unpacker.h"
#include "netproto/include/v2s_response_packer.h"
#include "npp_config_creator.h"


#include <iostream>


namespace
{
    static void test_pack_unpack_1( bool support_plain, bool sign_pack, bool verify_sign, 
        npp::Message::CompressMethod cm, 
        npp::Message::SymmetricEncryptMethod sem, 
        npp::Message::AsymmetricEncryptMethod aem, 
        npp::Message::AsymmetricPublicPrivateMethod appm)
    {
#ifdef H_NPP_SUPPORT_PROTO_SERVER_V2
        npp::NppConfig* npp_config = CreateNppConfig(support_plain, sign_pack, verify_sign);
        npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
        const char * raw_data = "1234567890";
        size_t raw_data_len = strlen(raw_data);

        //v2
        {
            npp::v2c::RequestMessage v2c_request;
            v2c_request.SetCompressMethod(cm);
            v2c_request.SetAsymmetricEncryptMethod(aem);
            v2c_request.SetSymmetricEncryptMethod(sem);
            v2c_request.SetAsymmetricPublicPrivateMethod(appm);
            H_TEST_ASSERT(v2c_request.Pack(raw_data, raw_data_len));

            npp::v2s::RequestMessageUnpacker v2s_unpacker;
            bool unpack_ok = v2s_unpacker.Unpack(v2c_request.Data(), v2c_request.Size());
            assert  (unpack_ok);
            H_TEST_ASSERT(unpack_ok);
            H_TEST_ASSERT(raw_data_len == v2s_unpacker.Size());
            H_TEST_ASSERT(memcmp(raw_data, v2s_unpacker.Data(), raw_data_len) == 0);

            npp::v2s::ResponseMessagePacker v2s_response(&v2s_unpacker);
            const char* response_data = "0123sdfasd456asdfas789";
            size_t response_data_len = strlen(response_data);
            size_t buf_len = v2s_response.GetPackedTotalDataSize(response_data_len);
            char buf[1024] = {};//char* buf = new char[buf_len];
            H_TEST_ASSERT(buf_len <= sizeof(buf));
            H_TEST_ASSERT(v2s_response.Pack(response_data, response_data_len, buf, buf_len));

            npp::v2c::ResponseUnpacker v2c_response_unpacker(&v2c_request);
            H_TEST_ASSERT(v2c_response_unpacker.Unpack(buf, buf_len));
            H_TEST_ASSERT(response_data_len == v2c_response_unpacker.Size());
            H_TEST_ASSERT(memcmp(response_data, v2c_response_unpacker.Data(), response_data_len) == 0);

            H_TEST_ASSERT(npp::v2c::ResponseUnpacker::GetMessageID(buf) == v2c_request.GetMessageID());
        }

        //v1
        {
            npp::v1::MessagePacker v1_packer;
            size_t buf_len = v1_packer.GetPackedTotalDataSize(raw_data_len);
            char buf[1024] = {};//char* buf = new char[buf_len];
            H_TEST_ASSERT(v1_packer.Pack(raw_data, raw_data_len, buf, buf_len));

            npp::v2s::RequestMessageUnpacker v2s_unpacker;
            bool unpack_ok = v2s_unpacker.Unpack(buf, buf_len);
            assert(unpack_ok);
            H_TEST_ASSERT(unpack_ok);
            //H_TEST_ASSERT(raw_data_len == v2s_unpacker.Size());
            H_TEST_ASSERT(memcmp(raw_data, v2s_unpacker.Data(), raw_data_len) == 0);

            npp::v2s::ResponseMessagePacker v2s_response(&v2s_unpacker);
            const char* response_data = "01234asdfa56aafsdfasds78934234";
            size_t response_data_len = strlen(response_data);
            buf_len = v2s_response.GetPackedTotalDataSize(response_data_len);
            H_TEST_ASSERT(buf_len <= sizeof(buf));
            H_TEST_ASSERT(v2s_response.Pack(response_data, response_data_len, buf, buf_len));

            npp::v1::MessageUnpacker v1_unpacker;
            H_TEST_ASSERT(v1_unpacker.Unpack(buf, buf_len));
            //H_TEST_ASSERT(response_data_len == v1_unpacker.Size());
            H_TEST_ASSERT(memcmp(response_data, v1_unpacker.Data(), response_data_len) == 0);
        }
#endif
    }
}


TEST_UNIT(test_func_v2cpack_v2sunpack_0_encrypt)
{
    for (int cm = 0; cm < npp::Message::kCompressNum; cm++)
    {
        for (int sem = 0; sem < npp::Message::kSymmetricEncryptMethodNum; sem++)
        {
            if (sem == npp::Message::kXorSymmetricEncrypt)
            {
                continue;
            }
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
            for (int aem = npp::Message::kSimpleRSA; aem < npp::Message::kAsymmetricEncryptMethodNum; aem++)
#else
            for (int aem = npp::Message::kSimpleRSA; aem <= npp::Message::kSimpleRSA; aem++)
#endif
            {
                for (int appm = 0; appm < npp::Message::kAsymmetricPublicPrivateMethodNum; appm++)
                {
                    if (sem != npp::Message::kNoSymmetricEncrypt)
                    {
                        test_pack_unpack_1(false, true, true, (npp::Message::CompressMethod)cm, (npp::Message::SymmetricEncryptMethod)sem, (npp::Message::AsymmetricEncryptMethod)aem, (npp::Message::AsymmetricPublicPrivateMethod)appm);
                        test_pack_unpack_1(false, true, false, (npp::Message::CompressMethod)cm, (npp::Message::SymmetricEncryptMethod)sem, (npp::Message::AsymmetricEncryptMethod)aem, (npp::Message::AsymmetricPublicPrivateMethod)appm);
                        test_pack_unpack_1(false, false, false, (npp::Message::CompressMethod)cm, (npp::Message::SymmetricEncryptMethod)sem, (npp::Message::AsymmetricEncryptMethod)aem, (npp::Message::AsymmetricPublicPrivateMethod)appm);
                    }

                    test_pack_unpack_1(true, true, true, (npp::Message::CompressMethod)cm, (npp::Message::SymmetricEncryptMethod)sem, (npp::Message::AsymmetricEncryptMethod)aem, (npp::Message::AsymmetricPublicPrivateMethod)appm);
                    test_pack_unpack_1(true, true, false, (npp::Message::CompressMethod)cm, (npp::Message::SymmetricEncryptMethod)sem, (npp::Message::AsymmetricEncryptMethod)aem, (npp::Message::AsymmetricPublicPrivateMethod)appm);
                    test_pack_unpack_1(true, false, false, (npp::Message::CompressMethod)cm, (npp::Message::SymmetricEncryptMethod)sem, (npp::Message::AsymmetricEncryptMethod)aem, (npp::Message::AsymmetricPublicPrivateMethod)appm);
                }
            }
        }   
    }
}
