
#include "netproto/include/test_common.h"

#include "netproto/include/exp.h"

#include "netproto/include/zlib.h"
#include "netproto/include/auto_delete.h"

namespace
{
    bool test_compress_1(npp::Compressor* c, const char* data)
    {
        size_t data_len = strlen(data);
        std::string compressed_data;
        H_TEST_ASSERT(c->Compress(data, data_len, compressed_data));

        std::string decompressed_data;
        H_TEST_ASSERT(c->Uncompress(compressed_data.data(), compressed_data.size(), decompressed_data));

        H_TEST_ASSERT(decompressed_data.size() == data_len);
        H_TEST_ASSERT(strncmp(decompressed_data.data(), data, data_len) == 0);
        return true;
    }

    bool test_compress_2(npp::Compressor* c)
    {
        const char* data = NULL;
        std::string compressed_data;
        H_TEST_ASSERT(!c->Compress(data, 1, compressed_data));
        return true;
    }
}

TEST_UNIT(test_Compressor)
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
        for (int j = 1; j < npp::Message::kCompressNum; ++j )
        {
            npp::Compressor* c = npp::CompressorFactory::CreateCompressor(j);
            if (c)
            {
                npp::ext::auto_delete<npp::Compressor> c_auto_delete(c);
                H_TEST_ASSERT(c);
                H_TEST_ASSERT(test_compress_1(c, test_datas[i].data()));
                H_TEST_ASSERT(test_compress_2(c));
            }
        }
    }
}

