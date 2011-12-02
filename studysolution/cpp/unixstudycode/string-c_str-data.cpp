#include <stdio.h>
#include <string>

int main()
{
    const char* a = "aaaaaaaa";
    std::string s(a, 2);
    printf("address a=%p\n", a);
    printf("address s.data()=%p\n", s.data());
    printf("address s.c_str()=%p\n", s.c_str());
    return 0;
}
