#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

namespace zl
{
        // TEMPLATE CLASS mem_fun_t
template< typename _Result, typename _Ty >
class mem_fun_t : public std::unary_function<_Ty *, _Result>
{	
    typedef _Result (_Ty::*_Pmemfun)();
public:
    explicit mem_fun_t( _Pmemfun& pfunc )
        : m_pfun( pfunc )
    {	// construct from pointer
    }

    _Result operator()(_Ty *_Pleft) const
    {	// call function
        return ( (_Pleft->*m_pfun)() );
    }

private:
    _Pmemfun m_pfun; // the member function pointer
};

}//end of namespace zl