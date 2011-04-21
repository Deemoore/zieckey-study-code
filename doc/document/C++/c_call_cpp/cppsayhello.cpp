//implematation file cppsayhello.cpp

#include "cppsayhello.h"

#include <iostream>


/**
  * compile : g++ -c cppsayhello.cpp -o cppsayhello.o
  */

void Say::hello()
{
	std::cout << "hello, from " << __PRETTY_FUNCTION__ << std::endl;
}



void sayhello( Say* say )
{
	say->hello();
}


void* create_say()
{
	Say* say = new Say();
	return (void*)say;
}

void  destroy_say( void* say )
{
	Say* s = (Say*)say;
	delete s;
    s = NULL;
}
