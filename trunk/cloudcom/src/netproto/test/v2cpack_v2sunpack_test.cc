#include "netproto/include/test_common.h"

#include "netproto/include/npp_config.h"
#include "netproto/include/v1_message_packer.h"
#include "netproto/include/v1_message_unpacker.h"
#include "netproto/include/idea.h"
#include "netproto/include/v2c_request_packer.h"
#include "netproto/include/v2s_request_unpacker.h"
#include "npp_config_creator.h"


#include <iostream>


namespace
{
    static void test_pack_unpack_1( bool sign_pack, bool verify_sign )
    {
        npp::NppConfig* npp_config = CreateNppConfig(false, sign_pack, verify_sign);
        npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
        const char * raw_data = "1234567890";
        size_t raw_data_len = strlen(raw_data);

        npp::v2c::RequestMessage packer;
        H_TEST_ASSERT(packer.Pack(raw_data, raw_data_len));

        npp::v2s::RequestMessageUnpacker unpacker;
        H_TEST_ASSERT(unpacker.Unpack(packer.Data(), packer.Size()));
        H_TEST_ASSERT(raw_data_len == unpacker.Size());
        H_TEST_ASSERT(memcmp(raw_data, unpacker.Data(), raw_data_len) == 0);
    }

    static void test_pack_unpack_2( bool support_plain, bool sign_pack, bool verify_sign )
    {
        npp::NppConfig* npp_config = CreateNppConfig(support_plain, sign_pack, verify_sign);
        npp::ext::auto_delete<npp::NppConfig> npp_config_auto_deleted(npp_config);
        const char * raw_data = "1234567890";
        size_t raw_data_len = strlen(raw_data);

        char packed_data[1024] = {};
        size_t packed_data_len = sizeof(packed_data);
        npp::v1::MessagePacker packer;
        H_TEST_ASSERT(packer.Pack(raw_data, raw_data_len, packed_data, packed_data_len));

        npp::v1::MessageUnpacker unpacker;
        H_TEST_ASSERT(unpacker.Unpack(packed_data, packed_data_len));
        npp::Message::NetHeader& net_header = const_cast<npp::Message::NetHeader&>(unpacker.net_header());
        npp::Message::NppHeaderV1& npp_header = const_cast<npp::Message::NppHeaderV1&>(unpacker.npp_header());
        net_header.InitV1();
        npp_header.Init();

        if (support_plain)
        {
            npp_header.encrypt_method_ = npp::Message::kNoSymmetricEncrypt;
        }
        else
        {
            npp_header.encrypt_method_ = npp::Message::kIDEASymmetricEncrypt;
        }

        for (int encrypt_key_no = 1; encrypt_key_no <= 4; ++encrypt_key_no)
        {
            for (int sign_key_no = 1; sign_key_no <= 4; sign_key_no++)
            {
#ifdef H_NPP_PROVIDE_OPENSSL_RSA
                for (int sign_method = 0; sign_method <= npp::Message::kOpenSSLRSA2; ++sign_method)
#else
                for (int sign_method = npp::Message::kSimpleRSA; sign_method <= npp::Message::kSimpleRSA; ++sign_method)
#endif
                {
                    npp_header.encrypt_key_no_ = encrypt_key_no;
                    npp_header.sign_key_no_    = sign_key_no;
                    npp_header.sign_method_    = sign_method;
                    net_header.message_id_     = rand() % 65536;

                    packed_data_len = sizeof(packed_data);
                    npp::v1::MessagePacker packer1(&unpacker);
                    H_TEST_ASSERT(packer1.Pack(raw_data, raw_data_len, packed_data, packed_data_len));

                    H_TEST_ASSERT(npp::v1::MessagePacker::GetMessageID(packed_data) == net_header.message_id());

                    npp::v1::MessageUnpacker unpacker1;
                    H_TEST_ASSERT(unpacker1.Unpack(packed_data, packed_data_len));
                    H_TEST_ASSERT(unpacker1.last_error() == npp::Message::kNoError);
                    if (npp_header.encrypt_method_ == npp::Message::kIDEASymmetricEncrypt)
                    {
                        H_TEST_ASSERT(H_ALIGN(raw_data_len, 8) == unpacker1.Size());
                    }
                    H_TEST_ASSERT(memcmp(raw_data, unpacker1.Data(), raw_data_len) == 0);
                    H_TEST_ASSERT(unpacker1.net_header().message_id_ == net_header.message_id_);
                    H_TEST_ASSERT(unpacker1.npp_header().encrypt_key_no() + 1 == npp_header.encrypt_key_no() || unpacker1.npp_header().encrypt_key_no() == npp_header.encrypt_key_no() + 1);
                    H_TEST_ASSERT(unpacker1.npp_header().sign_key_no() + 1 == npp_header.sign_key_no() || unpacker1.npp_header().sign_key_no() == npp_header.sign_key_no() + 1);
                }
            }
        }
    }

}


TEST_UNIT(test_func_v2cpack_v2sunpack_0_encrypt)
{
     test_pack_unpack_1(true, true);
     test_pack_unpack_1(true, false);
     test_pack_unpack_1(false, false);
}

// TEST_UNIT(test_func_v2cpack_v2sunpack_0_all)
// {
//     test_pack_unpack_2(false, true, true);
//     test_pack_unpack_2(false, true, false);
//     test_pack_unpack_2(false, false, false);
// 
//     test_pack_unpack_2(true, true, true);
//     test_pack_unpack_2(true, true, false);
//     test_pack_unpack_2(true, false, false);
// }


