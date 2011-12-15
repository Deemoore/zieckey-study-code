#include <stdio.h>
#include <string>

int main()
{
    const char* a = "aaaaaaaa";
    std::string s(a, 2);
    printf("address a=%p\n", a);
    printf("address s.data()=%p\n", s.data());
    printf("address s.c_str()=%p\n", s.c_str());


    std::string s1;
    s1.resize(8);
    memset(&s1[0], 'a', 8);
    printf("address s1.c_str()=%p\n", s1.c_str());
    printf("contents s1.c_str()=|%s|\n", s1.c_str());
    printf("s1.length()=%lu\n", s1.length());


    s1.resize(6);
    memset(&s1[0], 'a', 6);
    printf("address s1.c_str()=%p\n", s1.c_str());
    printf("contents s1.c_str()=|%s|\n", s1.c_str());
    printf("s1.length()=%lu\n", s1.length());
    return 0;
}
