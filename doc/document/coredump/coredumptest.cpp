#include <string>
#include <stdio.h>

using namespace std;

int main()
{
	string* ps = new string("Hello world");
	delete ps;
	ps = NULL;
	printf("%s\n", ps->c_str());
	return 0;
}
