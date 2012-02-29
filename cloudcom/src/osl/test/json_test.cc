
#include "osl/include/test_common.h"

#include "osl/include/json.h"

#include <iostream>

TEST_UNIT(json_unicode_test)
{
    //const char* json_test_str = "{\"key\":\"e7f5e684b979236597dc8cde1d7827c1\",\"table\":\"1\",\"url\":\"http:\/\/v.youku.com\/v_show\/id_XMzMxMjU3MzA4.html\",\"value\":[{\"cmd\":\"merge\",\"type\":\"2\",\"attrs\":{\"bthumb\":\"\",\"title\":\"\u90a2\u5e05\u7f51\u7edc\u5b66\u9662\u8bd5\u5b66\u6559\u7a0b\u7b2c\u4e09\u8bfe\",\"length\":\"1039\",\"src\":\"youku\",\"star\":\"\",\"type\":\"AE,AE\u6a21\u677f,AE\u63d2\u4ef6,AE\u6559\u7a0b,\u4f1a\u58f0\u4f1a\u5f71,\u5a5a\u5e86,\u680f\u5305\",\"class\":\"0\"}}]}";
    //const char* json_test_str = "{\"type\":\"AE,AE\u6a21\u677f,AE\u63d2\u4ef6,AE\u6559\u7a0b,\u4f1a\u58f0\u4f1a\u5f71,\u5a5a\u5e86,\u680f\u5305\"}";
    const char* json_test_str = "{\"type\":\"AE,AE\\u6a21\\u677f,AE\\u63d2\\u4ef6,AE\\u6559\\u7a0b,\\u4f1a\\u58f0\\u4f1a\\u5f71,\\u5a5a\\u5e86,\\u680f\\u5305\"}";
    json::JSONObject jo;
    H_TEST_ASSERT(jo.parse(json_test_str));
    json::JSONString* type = jo.getJSONString("type");
    (void)type;
}
