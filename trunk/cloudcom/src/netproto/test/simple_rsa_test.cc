
#include "netproto/include/test_common.h"
#include "netproto/include/slrsa_wrapper.h"

namespace
{
    void test1()
    {
        const size_t BUF_SIZE = 1024;
        const size_t KEY_LEN = 1024;
        unsigned char privatekey[BUF_SIZE] = {0x00, 0x04, 0xde, 0x44, 0x22, 0x5f, 0x95, 0x2d, 0x38, 0x67, 0x0c, 0xa1, 0xaf, 0xb4, 0xa2, 0x53, 0x29, 0xd4, 0xae, 0x75, 0xf8, 0x38, 0x8e, 0x4f, 0x54, 0x48, 0x54, 0x0b, 0x9e, 0xd5, 0x21, 0x6b, 0x51, 0xb1, 0x2c, 0x38, 0x82, 0xbd, 0x86, 0xed, 0x63, 0xbc, 0x5f, 0xe7, 0x29, 0x5f, 0xf0, 0xf2, 0x94, 0x7e, 0xf2, 0x60, 0xe9, 0xea, 0x0e, 0xbe, 0x75, 0xac, 0x57, 0x4a, 0x3b, 0xad, 0x63, 0x25, 0xe6, 0x2a, 0xee, 0x1b, 0xf2, 0x5f, 0xe1, 0x5c, 0xa2, 0x98, 0x78, 0xe3, 0xcd, 0x8a, 0x90, 0xbd, 0x5a, 0xfb, 0x83, 0x2e, 0xae, 0x0d, 0xbe, 0x69, 0xe8, 0xd4, 0xb6, 0x97, 0x94, 0x57, 0x2c, 0x3c, 0x5f, 0xd8, 0xf7, 0xa3, 0xf5, 0x79, 0x55, 0xfc, 0x43, 0x5c, 0xbe, 0x27, 0x86, 0x42, 0x2c, 0x72, 0xad, 0x23, 0x96, 0x43, 0xf1, 0x97, 0xb6, 0xa9, 0xcc, 0xa5, 0x10, 0x9f, 0x34, 0x57, 0x20, 0xbb, 0x26, 0xab, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x77, 0xc4, 0x1b, 0x09, 0x8a, 0x26, 0xad, 0xc7, 0xc9, 0x64, 0xae, 0x7b, 0x15, 0x24, 0xde, 0xdb, 0x7d, 0x8e, 0x8f, 0xcc, 0x59, 0xd2, 0xa1, 0x45, 0xc0, 0x13, 0xea, 0xe8, 0x49, 0x73, 0xbc, 0xb7, 0x4d, 0x6e, 0xbd, 0xf4, 0x46, 0x6a, 0x50, 0x5d, 0xc7, 0x07, 0x96, 0xa1, 0xde, 0x01, 0xb8, 0xc6, 0x96, 0xf0, 0x65, 0xda, 0xfb, 0x4a, 0xe1, 0xb9, 0x95, 0xe7, 0xa8, 0x34, 0x8b, 0xc2, 0x76, 0x3d, 0x16, 0x15, 0xcd, 0xe4, 0x7d, 0x4a, 0x68, 0xfa, 0x6b, 0x9c, 0x42, 0x76, 0xdd, 0x4e, 0xdc, 0x42, 0x21, 0xe7, 0x0b, 0xe5, 0xb3, 0x6f, 0x62, 0xa4, 0x8d, 0x0a, 0xb5, 0xd4, 0x5c, 0x0f, 0x46, 0xfd, 0x63, 0xd2, 0xe5, 0xa2, 0xd6, 0x02, 0x5f, 0xf0, 0x39, 0xd2, 0x22, 0x33, 0xc1, 0xcd, 0xd9, 0xf8, 0xde, 0xb7, 0xa0, 0xfc, 0xfe, 0x11, 0xe3, 0x04, 0x17, 0x30, 0xfa, 0x03, 0x49, 0xe3, 0xad, 0x01, 0xff, 0x96, 0x5e, 0xcd, 0x4d, 0x07, 0x30, 0xe3, 0x2f, 0x40, 0xef, 0xa9, 0xef, 0xd7, 0x70, 0xff, 0x91, 0xf4, 0xcf, 0xfa, 0x72, 0x53, 0x67, 0x95, 0x0e, 0x38, 0x67, 0xbd, 0x16, 0x3a, 0xdc, 0xa3, 0xcf, 0xd2, 0x8f, 0x62, 0x1f, 0xba, 0xe1, 0x26, 0x54, 0x23, 0x62, 0xd4, 0x8d, 0x84, 0xdb, 0x1f, 0x19, 0xbe, 0x5a, 0xff, 0xae, 0x6a, 0xf1, 0x03, 0x84, 0xf7, 0xdc, 0x3a, 0x38, 0xdf, 0xb8, 0x41, 0xde, 0x9f, 0xfe, 0x2d, 0x8b, 0x99, 0x61, 0xd7, 0x3d, 0x25, 0xe7, 0x52, 0x84, 0x10, 0x05, 0x52, 0x35, 0x0a, 0x9e, 0x4a, 0x83, 0x28, 0xea, 0xdb, 0x2f, 0x75, 0xab, 0x69, 0x9a, 0x91, 0x7d, 0x51, 0x00, 0x52, 0x6c, 0xc3, 0x0c, 0xfb, 0xe0, 0xd2, 0xd7, 0x15, 0xf4, 0xf6, 0x18, 0x5b, 0x54, 0x44, 0x4d, 0xc6, 0x69, 0xc6, 0x46, 0x56, 0x13, 0x9f, 0xd9, 0x02, 0x8b, 0xa7, 0x35, 0x24, 0x43, 0xeb, 0xfb, 0xe0, 0xea, 0xe8, 0x94, 0x42, 0xc3, 0xf1, 0x00, 0x3e, 0x94, 0x71, 0xfa, 0xc5, 0x6c, 0xbc, 0xd0, 0xd0, 0x5c, 0xae, 0x4a, 0x40, 0xdb, 0xd1, 0xcf, 0x43, 0xd3, 0x28, 0x4b, 0x62, 0x12, 0xd2, 0xf5, 0x1a, 0x62, 0xe7, 0xa6, 0xb1, 0x7a, 0xf5, 0x54, 0xf1, 0xd2, 0x91, 0xfa, 0x2d, 0xb5, 0xec, 0x3e, 0x68, 0x94, 0x31, 0x69, 0x68, 0x46, 0xc0, 0xdb, 0x27, 0x91, 0x47, 0x67, 0x89, 0x42, 0x81, 0xa6, 0x19, 0x97, 0x2a, 0x62, 0x2a, 0x99, 0x6e, 0x5f, 0x08, 0x25, 0xb4, 0x52, 0x26, 0x25, 0xe2, 0x35, 0x02, 0xec, 0x21, 0x4a, 0x04, 0xc0, 0x5d, 0xb2, 0xe6, 0x47, 0x73, 0x2e, 0x48, 0xf8, 0xc7, 0xf3, 0xc6, 0x8b, 0xb1, 0x67, 0xc1, 0x91, 0xf7, 0x9d, 0x54, 0x9b, 0x84, 0xf5, 0x9d, 0x46, 0x9d, 0x03, 0xae, 0x53, 0x03, 0x05, 0x3d, 0x79, 0xbc, 0xdc, 0xcb, 0xe2, 0x68, 0x69, 0xe4, 0xd9, 0xeb, 0xc4, 0xc2, 0xb6, 0x0a, 0x6c, 0xc9, 0xf2, 0x8f, 0xcc, 0x5f, 0x27, 0x55, 0x30, 0x69, 0x92, 0xbd, 0xbe, 0x70, 0x36, 0x95, 0xeb, 0xec, 0xf0, 0x12, 0x01, 0x9a, 0xa0, 0x3b, 0xa6, 0xa8, 0x47, 0x1f, 0xf8, 0xcc, 0x6a, 0x9f, 0xdf, 0x89, 0xac, 0xd9, 0xaf, 0x2f, 0x1a, 0x4d, 0xac, 0x44, 0x3e, 0x54, 0xa2, 0xc0, 0x9e, 0x91, 0xa9, 0x4b, 0x56, 0xf3, 0x0e, 0xa5, 0x54, 0xda, 0xe8, 0x2e, 0x01, 0xa7};
        unsigned char publickey[BUF_SIZE] = {0x00, 0x04, 0xde, 0x44, 0x22, 0x5f, 0x95, 0x2d, 0x38, 0x67, 0x0c, 0xa1, 0xaf, 0xb4, 0xa2, 0x53, 0x29, 0xd4, 0xae, 0x75, 0xf8, 0x38, 0x8e, 0x4f, 0x54, 0x48, 0x54, 0x0b, 0x9e, 0xd5, 0x21, 0x6b, 0x51, 0xb1, 0x2c, 0x38, 0x82, 0xbd, 0x86, 0xed, 0x63, 0xbc, 0x5f, 0xe7, 0x29, 0x5f, 0xf0, 0xf2, 0x94, 0x7e, 0xf2, 0x60, 0xe9, 0xea, 0x0e, 0xbe, 0x75, 0xac, 0x57, 0x4a, 0x3b, 0xad, 0x63, 0x25, 0xe6, 0x2a, 0xee, 0x1b, 0xf2, 0x5f, 0xe1, 0x5c, 0xa2, 0x98, 0x78, 0xe3, 0xcd, 0x8a, 0x90, 0xbd, 0x5a, 0xfb, 0x83, 0x2e, 0xae, 0x0d, 0xbe, 0x69, 0xe8, 0xd4, 0xb6, 0x97, 0x94, 0x57, 0x2c, 0x3c, 0x5f, 0xd8, 0xf7, 0xa3, 0xf5, 0x79, 0x55, 0xfc, 0x43, 0x5c, 0xbe, 0x27, 0x86, 0x42, 0x2c, 0x72, 0xad, 0x23, 0x96, 0x43, 0xf1, 0x97, 0xb6, 0xa9, 0xcc, 0xa5, 0x10, 0x9f, 0x34, 0x57, 0x20, 0xbb, 0x26, 0xab, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01};
        size_t publickey_len = 258;
        size_t privatekey_len = 706;

        npp::SimpleRSA rsa;
        H_TEST_ASSERT(rsa.initialize(privatekey, privatekey_len, publickey,  publickey_len));

        const char* data = "asdfjlasjflasjdflajsdlkfjasdlkfajsdlkfjas;dlkf";
        size_t data_len = strlen(data);

        unsigned char sigret[2048] = {0};
        size_t siglen  = 0;

        bool ret = rsa.sign((unsigned char*)data, data_len, sigret, &siglen );
        H_TEST_ASSERT(ret);
        ret = rsa.verify((unsigned char*)data, data_len, sigret, siglen );
        H_TEST_ASSERT(ret);

        std::string ss;
        H_TEST_ASSERT(rsa.sign((unsigned char*)data, data_len, ss ));
        H_TEST_ASSERT(rsa.verify((unsigned char*)data, data_len, ss.data(), ss.size() ));
    }
}

TEST_UNIT(simple_rsa_test_1)
{
    test1();
}


