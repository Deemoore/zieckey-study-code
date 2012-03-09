
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

