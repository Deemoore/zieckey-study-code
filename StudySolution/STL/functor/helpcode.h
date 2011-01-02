#include <functional>
#include <vector>
#include <iostream>
#include <algorithm>

struct State
{
    State( int state ) : m_state( state ){}
    ~State() { std::cout << "~State(), m_state=" << m_state << std::endl; }

    void setState( int state ){ m_state = state; }
    int getState() const{ return m_state; }

    void print() const { std::cout << "State::print:" << m_state << std::endl; }

private:
    int m_state;
};

template<typename T>
struct DeletePointer1 
{
    void operator()( T* ptr ) const { delete ptr; }
};

struct DeletePointer2
{
    template<typename T> void operator()( T* ptr ) const { delete ptr; }
};

void print( State* pstate )
{
    pstate->print();
}

struct Printer
{
    template<typename T> void operator()( T* t ) { t->print(); }
};

int main()
{
    std::vector<State*> vect;

    vect.push_back( new State(0) );
    vect.push_back( new State(1) );
    vect.push_back( new State(2) );
    vect.push_back( new State(3) );

    //for each of the element, we call the member function State::print
    std::for_each( vect.begin(), vect.end(), std::mem_fun( &State::print ) );

    //method 1: delete each of the element in the vector
    std::for_each( vect.begin(), vect.end(), DeletePointer1<State>() );
    vect.clear();

    vect.push_back( new State(10) );
    vect.push_back( new State(11) );
    vect.push_back( new State(12) );
    vect.push_back( new State(13) );


    //for each of the element, we call the member function State::print
    std::for_each( vect.begin(), vect.end(), std::mem_fun( &State::print ) );


    //method 2: delete each of the element in the vector
    std::for_each( vect.begin(), vect.end(), DeletePointer2() );
    vect.clear();



    system( "pause" );

    return 0;
}


// 
// template< typename InputIterator, typename Function >
// Function for_each( InputIterator beg, InputIterator end, Function f ) {
//     while ( beg != end )
//         f( *beg++ );
// }


