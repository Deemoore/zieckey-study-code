#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

struct Printer
{
    template< typename T >
    void operator()( T& _val )
    {
        std::cout << _val << ", ";
    }
};

int main()
{
    std::vector<int> ivec;
    const int MAX_COUNT = 10;
    for ( int i = 1; i < MAX_COUNT; ++i )
    {
        ivec.push_back( i );
        ivec.push_back( MAX_COUNT - i );
    }

    std::cout << "initialize :   ";
    std::for_each( ivec.begin(), ivec.end(), Printer() );
    transform( ivec.begin(), ivec.end(), ivec.begin(), std::negate<int>() );//将所有元素求反值
    std::cout << "\nafter negate :   ";
    std::for_each( ivec.begin(), ivec.end(), Printer() );
    transform( ivec.begin(), ivec.end(), ivec.begin(), std::negate<int>() );//将所有元素求反值
    std::cout << "\nafter negate twice :   ";
    std::for_each( ivec.begin(), ivec.end(), Printer() );

    //删除掉vector中小于5的所有元素，注意remove_if并不改变容器的大小，所以还需要调用erase来删除
    std::vector<int>::iterator iter = std::remove_if( ivec.begin(), ivec.end(), std::bind2nd( std::less<int>(), 5 ) );
    ivec.erase( iter, ivec.end() );
    std::cout << "\nafter remove_if[ < 5 ] :   ";
    std::for_each( ivec.begin(), ivec.end(), Printer() );


    //将集合中所有等于6的元素值改为60.
    std::replace_if( ivec.begin(), ivec.end(), std::bind2nd( std::equal_to<int>(), 6 ), 60 );
    std::cout << "\nafter replace_if[ 6 --> 60 ] :   ";
    for_each( ivec.begin(), ivec.end(), Printer() );

    std::cout << std::endl;
    system( "pause" );
    return 0;
}