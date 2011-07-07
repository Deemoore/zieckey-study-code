#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

struct State
{
    State( int state ) : m_state( state ){}
    ~State() { std::cout << "~State(), m_state=" << m_state << std::endl; }
    void setState( int state ){ m_state = state; }
    int getState() const{ return m_state; }
    void print() const { std::cout << "State::print: " << m_state << std::endl; }
private:
    int m_state;
};

void print( State* pstate )
{
    pstate->print();
}

struct Printer
{
    template<typename T> void operator()( T* t ) { t->print(); }
};

struct DeletePointer1
{
    template<typename T> void operator()( T* ptr ) const { delete ptr; }
};

template<typename T>
struct DeletePointer2
{
    void operator()( T* ptr ) const { delete ptr; }
};

int main()
{
    std::vector<State*> vect;

    vect.push_back( new State(0) );
    vect.push_back( new State(1) );
    vect.push_back( new State(2) );
    vect.push_back( new State(3) );

    std::vector<State*>::iterator it( vect.begin() );
    std::vector<State*>::iterator ite( vect.end() );
    for ( ; it != ite; ++it )
    {
        (*it)->print();
    }

    std::for_each( vect.begin(), vect.end(), &print );
    std::for_each( vect.begin(), vect.end(), Printer() );
    std::for_each( vect.begin(), vect.end(), std::mem_fun( &State::print ) );
    std::for_each( vect.begin(), vect.end(), DeletePointer1() );
    vect.clear();

    system( "pause" );
    return 0;
}
// bind2nd
// replace_if( vect.begin(), vect.end(), bind2nd( equal_to<int>(), 70 ))
// equal_to<int>


// 
// template<class _Ty>
// struct equal_to
//     : public binary_function<_Ty, _Ty, bool>
// {	// functor for operator==
//     bool operator()(const _Ty& _Left, const _Ty& _Right) const
//     {	// apply operator== to operands
//         return (_Left == _Right);
//     }
// };
// 
// 
// template<class _Fn2,
// class _Ty> inline
//     binder2nd<_Fn2> bind2nd(const _Fn2& _Func, const _Ty& _Right)
// {	// return a binder2nd functor adapter
//     typename _Fn2::second_argument_type _Val(_Right);
//     return (std::binder2nd<_Fn2>(_Func, _Val));
// }
// 
// 
// 
// 
// template<class _Fn2>
// class binder2nd
//     : public unary_function<typename _Fn2::first_argument_type,
//     typename _Fn2::result_type>
// {	// functor adapter _Func(left, stored)
// public:
//     typedef unary_function<typename _Fn2::first_argument_type,
//         typename _Fn2::result_type> _Base;
//     typedef typename _Base::argument_type argument_type;
//     typedef typename _Base::result_type result_type;
// 
//     binder2nd(const _Fn2& _Func,
//         const typename _Fn2::second_argument_type& _Right)
//         : op(_Func), value(_Right)
//     {	// construct from functor and right operand
//     }
// 
//     result_type operator()(const argument_type& _Left) const
//     {	// apply functor to operands
//         return (op(_Left, value));
//     }
// 
//     result_type operator()(argument_type& _Left) const
//     {	// apply functor to operands
//         return (op(_Left, value));
//     }
// 
// protected:
//     _Fn2 op;	// the functor to apply
//     typename _Fn2::second_argument_type value;	// the right operand
// };
