#include <stdio.h>

#include <sys/time.h>

#include <iomanip>
#include <iostream>
using namespace std;

class A
{
    public:
        A(){ std::cout << "A() called, this=" << this << std::endl;}
        ~A(){ std::cout << "~A() called, this=" << this << std::endl;}
        void print() { std::cout << "class A" << std::endl; }
};


int main()
{
    A* pa = new A();
    void* pv = pa;
    A* pb = reinterpret_cast<A*>( pv );
    pb->print();
    delete pb;
    return 0;
}


