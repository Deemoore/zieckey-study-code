
#include "netproto/include/test_common.h"

#include "netproto/include/exp.h"

#include "netproto/include/zlib.h"
#include "netproto/include/auto_delete.h"
#include "netproto/include/gz.h"

#ifdef H_NPP_PROVIDE_ZLIB

namespace
{
    bool test_zlib_1(const char* data)
    {
        size_t data_len = strlen(data);
        size_t compressed_data_len = npp::ZLib::GetCompressBound(data_len);
        char* compressed_data = new char[compressed_data_len];
        npp::ext::auto_delete<char> compressed_data_auto_delete(compressed_data);
        H_TEST_ASSERT(ZZ_OK == npp::ZLib::Compress(data, data_len, compressed_data, &compressed_data_len));

        size_t decompressed_data_len = npp::ZLib::GetUncompressBound(compressed_data);
        H_TEST_ASSERT(decompressed_data_len == data_len);
        char* decompressed_data = new char[decompressed_data_len];
        npp::ext::auto_delete<char> decompressed_data_auto_delete(decompressed_data);
        H_TEST_ASSERT(ZZ_OK == npp::ZLib::Uncompress(compressed_data, compressed_data_len, decompressed_data, &decompressed_data_len));

        H_TEST_ASSERT(decompressed_data_len == data_len);
        H_TEST_ASSERT(strncmp(decompressed_data, data, data_len) == 0);

#if 1
        std::string scomprs;
        npp::ZLib zlib;
        H_TEST_ASSERT(zlib.Compress(data, data_len, scomprs));
        H_TEST_ASSERT(scomprs.length() == compressed_data_len);
        H_TEST_ASSERT(memcmp(compressed_data, scomprs.data(), scomprs.size()) == 0);

        std::string sdecomprs;
        H_TEST_ASSERT(zlib.Uncompress(compressed_data, compressed_data_len, sdecomprs));
        H_TEST_ASSERT(sdecomprs.length() == decompressed_data_len);
        H_TEST_ASSERT(memcmp(decompressed_data, sdecomprs.data(), sdecomprs.size()) == 0);
#endif
        return true;
    }

    bool test_gzip_1(const char* data)
    {
        size_t data_len = strlen(data);
        size_t compressed_data_len = 4096;
        char* compressed_data = new char[compressed_data_len];
        npp::ext::auto_delete<char> compressed_data_auto_delete(compressed_data);
        H_TEST_ASSERT(ZZ_OK == npp::GZip::Compress(data, data_len, compressed_data, &compressed_data_len));

        if (data_len < 32)
        {
            std::string path(data);
            path.append(".gz");
            FILE* fp = fopen(path.c_str(), "wb+");
            fwrite(compressed_data, compressed_data_len, 1, fp);
            fflush(fp);
            fclose(fp);
        }

        #if 1
        size_t decompressed_data_len = 4096;
        char* decompressed_data = new char[decompressed_data_len];
        npp::ext::auto_delete<char> decompressed_data_auto_delete(decompressed_data);
        H_TEST_ASSERT(ZZ_OK == npp::GZip::Uncompress(compressed_data, compressed_data_len, decompressed_data, &decompressed_data_len));

        H_TEST_ASSERT(decompressed_data_len == data_len);
        H_TEST_ASSERT(strncmp(decompressed_data, data, data_len) == 0);

        
#endif
        return true;
    }
}

TEST_UNIT(zlib_test)
{
    
    std::string test_datas[] = {
        "0",
        "01",
        "012",
        "0123",
        "01234",
        "012345",
        "0123456",
        "01234567",
        "012345678",
        "0123456789",
        "0123456789a",
        "0123456789ab",
        "0123456789abc",
        "0123456789abcd",
        "0123456789abcdf0",
        "0123456789abcdf12",
        "0123456789abcdf1231",
        "0123456789abcdf1231412412",
        "0123456789arqwerbcd",
        "0123456789aqwerqwerbcdf0",
        "asdfasdfasdfasdfasdfqwerwqefasdfasdf",
        "asdfasdfasdfasdfasdfqwerwqefasdfasasdfasdfdf",
        "asdfasdfasdfasdfasdfqwerwqefasdfasdasdfasdfasdff",
        "asdfasdfasdfasdfasdfqwerwqefasdfaasdfasdfasdsdf",
        "0123456789aqwerqwerbcdqwehr21j341j23;ln;fasdnfa214234123*_)(&(*^&%R(TYOIHKJLHBV%*)(*&^%&*()*&^%&*()*&^*()f0",
        "asdfasdfasdfasdfasdfqwerwqefa^&*()&&@#$!#W$@!Q#$U*(I)*&^$#@!~!@#$%^&*(PL:>:<LP:LP{++}|?><MNBGVFRTYUIKJHNBGVDCERFTYUYTR$#W@!@#$%^&*()_+_)(*&^%$#@!~sdfasdf",
        "asdfasdfasdfasdfasdfqwerwqefasdfasa  BVVVVVVVVVVFGFGFGFGFGFGRRRRRRRRRRRRRRRRRRRRRRRRRRRR^&TYDR%$R#$@!~@#!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~QWERFFFFFFEW$QQQWEQ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@RRRTYGHVFFRTFDER$FDRDXRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRFGVBBBBBBBBBBBBBBBBBBBBBBBBBBBBBUHEW$#EsdfasdfdJHGFDSFGHGFDSWQERTYTR%$#@!@#$%$#@!~!@#$%^&*()_(*&^%&IOP:OLURFDFGHJKLKJHGFDSXCVBNM<NBVCXf",
        "asdfasdfasdfasdfasdfqwerwqefasdfasdasdfasdfasdffJHGFYUHJTYR%$W#%^&*()_+)(*&^%$#@!~@#$%67890-=0987654321@#R%TUJHIKHGVFDU*R%$r5t6y7uiujhgyftrEW$R%^U*YDXR$%^&*GFDR%T^YHGFVCT^GFDR%TFDRTFDRFCDGVF",
        "UJHGJUJGTYJHGHGFYT^&YT$E%RE#$%RE$asdfasdfasdfasdfasdfqwerwqefasdfaasdfasdfasdsdJGFR^T&GHFT^&YG^&*f"
    };

    for (size_t i = 0; i < H_ARRAYSIZE(test_datas); ++i)
    {
        H_TEST_ASSERT(test_zlib_1(test_datas[i].data()));
        H_TEST_ASSERT(test_gzip_1(test_datas[i].data()));
    }
}

#endif

