
#include "osl/include/test_common.h"

#include "osl/include/json.h"

#include <iostream>

namespace
{
    void test_json_1()
    {
        const char* json_test_str = "{\"type\":\"AE,AE\\u6a21\\u677f,AE\\u63d2\\u4ef6,AE\\u6559\\u7a0b,\\u4f1a\\u58f0\\u4f1a\\u5f71,\\u5a5a\\u5e86,\\u680f\\u5305\"}";
        json::JSONObject jo;
        H_TEST_ASSERT(jo.parse(json_test_str));
        osl::StringA serialize = jo.toString();
        json::JSONObject jo1;
        H_TEST_ASSERT(jo1.parse(serialize.data(), serialize.size()));
        osl::StringA serialize1 = jo1.toString();
        H_TEST_ASSERT(jo1.equals(jo));
        H_TEST_ASSERT(serialize1 == serialize);
    }

    void test_json_2()
    {
        const char* json_test_str = "{\"key\":\"657d9bc79cf47f406c018eb0c5abf7cd\",\"table\":\"1\",\"url\":\"http:\\/\\/www.qiyi.com\\/dianshiju\\/20100417\\/n3283.html\",\"value\":[{\"cmd\":\"merge\",\"type\":\"2\",\"attrs\":{\"bthumb\":\"\",\"title\":\"\\u5bb6\\u6709\\u513f\\u5973 \\u7b2c\\u4e00\\u90e8\",\"length\":\"1512\",\"src\":\"qiyi\",\"star\":null,\"type\":\"\\u90fd\\u5e02\\u5267,\\u60c5\\u666f\\u5267,\\u513f\\u7ae5\\u5267,\\u751f\\u6d3b\\u5267,\\u9752\\u5c11\\u5267\",\"class\":\"0\"}}]}";
        json::JSONObject jo;
        H_TEST_ASSERT(jo.parse(json_test_str));
        json::JSONString* type = jo.getJSONString("type");
        (void)type;
        osl::StringA serialize = jo.toString();
        //(void)serialize;
        //std::cout << serialize.c_str();
        json::JSONObject jo1;
        H_TEST_ASSERT(jo1.parse(serialize.data(), serialize.size()));
        osl::StringA serialize1 = jo1.toString();
        //std::cout << serialize.c_str();
        H_TEST_ASSERT(serialize1 == serialize);
        H_TEST_ASSERT(jo1.equals(jo));
    }

    void test_json_3(const char* json_test_str)
    {
        json::JSONObject jo0;
        H_TEST_ASSERT(jo0.parse(json_test_str));
        osl::StringA serialize0 = jo0.toString();
        json::JSONObject jo1;
        H_TEST_ASSERT(jo1.parse(serialize0.data(), serialize0.size()));
        osl::StringA serialize1 = jo1.toString();
        H_TEST_ASSERT(jo1.equals(jo0));
        H_TEST_ASSERT(serialize1 == serialize0);
        json::JSONObject jo2;
        H_TEST_ASSERT(jo2.parse(serialize1.data(), serialize1.size()));
        osl::StringA serialize2 = jo2.toString();
        H_TEST_ASSERT(jo2.equals(jo1));
        H_TEST_ASSERT(jo2.equals(jo0));
        H_TEST_ASSERT(serialize1 == serialize2);
        H_TEST_ASSERT(serialize1 == serialize0);
    }

}

TEST_UNIT(json_unicode_test_1)
{
    test_json_1();
    test_json_2();
}


TEST_UNIT(json_unicode_and_binary_test_2)
{
    const char* path = "test_data/json/unicode.json.txt";
    std::fstream fs(path);
    H_TEST_ASSERT(fs.good());
    H_TEST_ASSERT(!fs.fail());
    std::string line;
    size_t text_length = 0;
    size_t binary_length = 0;
    while (std::getline(fs, line).good())
    {
        json::JSONObject jo0;
        H_TEST_ASSERT(jo0.parse(line.data(), line.size()));
        osl::StringA serialize0 = jo0.toString();
        json::JSONObject jo1;
        H_TEST_ASSERT(jo1.parse(serialize0.data(), serialize0.size()));
        osl::StringA serialize1 = jo1.toString();
        H_TEST_ASSERT(serialize1 == serialize0);
        H_TEST_ASSERT(jo1.equals(jo0));
        json::JSONObject jo2;
        H_TEST_ASSERT(jo2.parse(serialize1.data(), serialize1.size()));
        osl::StringA serialize2 = jo2.toString();
        H_TEST_ASSERT(jo2.equals(jo1));
        H_TEST_ASSERT(jo2.equals(jo0));
        H_TEST_ASSERT(serialize1 == serialize2);
        H_TEST_ASSERT(serialize1 == serialize0);
        
        text_length += serialize0.length();

        osl::MemoryDataStream buf;
        buf << jo2;
        binary_length += buf.size();
        json::JSONObject jo3;
        buf >> jo3;
        H_TEST_ASSERT(jo3.equals(jo2));
    }

    //std::cout << "\nbinary_length/text_length=" << double(binary_length)/double(text_length) << std::endl; //0.889
}

TEST_UNIT(json_gbk_chinese_test_3)
{
    const char* path = "test_data/json/gbk-chinese.json.txt";
    std::fstream fs(path);
    H_TEST_ASSERT(fs.good());
    H_TEST_ASSERT(!fs.fail());
    std::string line;
    while (std::getline(fs, line).good())
    {
        json::JSONObject jo0;
        H_TEST_ASSERT(jo0.parse(line.data(), line.size()));
        osl::StringA serialize0 = jo0.toString();
        json::JSONObject jo1;
        H_TEST_ASSERT(jo1.parse(serialize0.data(), serialize0.size()));
        osl::StringA serialize1 = jo1.toString();
        H_TEST_ASSERT(serialize1 == serialize0);
        H_TEST_ASSERT(jo1.equals(jo0));
        json::JSONObject jo2;
        H_TEST_ASSERT(jo2.parse(serialize1.data(), serialize1.size()));
        osl::StringA serialize2 = jo2.toString();
        H_TEST_ASSERT(jo2.equals(jo1));
        H_TEST_ASSERT(jo2.equals(jo0));
        H_TEST_ASSERT(serialize1 == serialize2);
        H_TEST_ASSERT(serialize1 == serialize0);
    }
}

TEST_UNIT(json_error_test_4)
{
    osl::StringA line = "{\"list\":[{\"attrs\":{\"content\":\"\u606d\u559c\u3010\u674e\u5c0f\u59d0\u25c6\u25c6\u25c6\u3011\u7b2c\u4e00\u8f6e24\u780110\u4e2d8\u8fbe\u5230\u52a0\u5a01\u671b\u6807\u51c6\uff0c\u52a0\u5a01\u671b1000\u5e76\u664b\u5347\u4e3a\u4f18\u79c0\u9ad8\u624b\uff0c\u611f\u8c22\u4f60\u5bf9\u5409\u5229\u7684\u652f\u6301\uff0c\u5409\u5229\u6709\u4f60\u66f4\u7cbe\u5f69\uff01\u3010\u7c89\u58a8\u3011\u606d\u559c\u3010\u674e\u5c0f\u59d0\u25c6\u25c6\u25c6\u3011\u5728\u7b2c\u4e00\u8f6e\u4e8c\u56db\u7801\u4e2d\u5341\u671f\u4e2d\u516b\uff0c\u8fbe\u5230\u52a0\u5a01\u671b\u6807\u51c6\uff0c\u52a0\u5a01\u671b1000\u5e76\u664b\u5347\u4e3a\u91d1\u6e2f\u4f18\u79c0\u53d1\u8868\u9ad8\u624b\uff0c\u91d1\u6e2f\u6709\u4f60\u66f4\u7cbe\u5f69\uff01\u3010\u7ba1\u7406\u5458\u3011\u606d\u559c\u3010\u674e\u5c0f\u59d0\u25c6\u25c6\u25c6\u3011\u7b2c\u4e00\u8f6e\u4e00\u6ce2\u8fde\u4e2d\u4e94\u671f\u8fbe\u5230\u52a0\u5a01\u671b\u6807\u51c6\uff0c\u52a0\u5a01\u671b1000\u5e76\u664b\u5347\u4e3a\u8363\u8a89\u9ad8\u624b\uff0c\u611f\u8c22\u4f60\u5bf9\u5409\u5229\u7684\u652f\u6301\uff0c\u5409\u5229\u6709\u4f60\u66f4\u7cbe\u5f69\uff01 \u3010\u7c89\u58a8\u3011\u606d\u559c\u3010\u674e\",\"title\":\"026\u671f:\u4e00\u6ce220\u7801\u5927\u4e2d\u5df2\u7ecf\u66f4\u65b0\u4e86\uff01\u2588\u2588\u3010\u674e\u5c0f\u59d0\u4eba\u7f8e\u6599\u66f4\u9753\uff01\u5168\u80fd\u51a0\u519b\uff01\u3011\u2588\"},\"type\":\"99\"}],\"url\":\"http://ji2010.com/bbs/htm_data/2/1203/672810.html\"}";
    json::JSONObject jo0;
    H_TEST_ASSERT(jo0.parse(line.data(), line.size()));
    osl::StringA serialize0 = jo0.toString();
    //H_TEST_ASSERT(serialize0 == line);
    json::JSONObject jo1;
    H_TEST_ASSERT(jo1.parse(serialize0.data(), serialize0.size()));
    osl::StringA serialize1 = jo1.toString();
    H_TEST_ASSERT(serialize1 == serialize0);
    H_TEST_ASSERT(jo1.equals(jo0));
    json::JSONObject jo2;
    H_TEST_ASSERT(jo2.parse(serialize1.data(), serialize1.size()));
    osl::StringA serialize2 = jo2.toString();
    H_TEST_ASSERT(jo2.equals(jo1));
    H_TEST_ASSERT(jo2.equals(jo0));
    H_TEST_ASSERT(serialize1 == serialize2);
    H_TEST_ASSERT(serialize1 == serialize0);
}