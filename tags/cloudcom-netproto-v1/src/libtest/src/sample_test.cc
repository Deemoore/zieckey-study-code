#include "libtest/include/inner_pre.h"
#include "libtest/include/lib_test.h"

TEST( test_a )
{
    std::cout << "cmd='test_a', desc='aaaaaaaaaaa'" << std::endl;
}


TEST( test_b )
{
    std::cout << "cmd='test_b', desc='bbbbbbbbbbb'" << std::endl;
}

//std::string& operator = (std::string& a, const osl::StringA& b)
//{
//    a = std::string(b.c_str(), b.length());
//    return a;
//}

TEST( test_c )
{
#ifdef H_STD_STRING
    std::string stds1 = "stdstring";
    osl::StringA osls1 = "oslstring";

    std::string stds2 = osls1;
    osl::StringA osls2 = stds1;

    std::cout << osls1 << std::endl;
    std::cout << osls2 << std::endl;
#endif 
}

TEST_INVOKE(test_invoke_a, "test_invoke_a the desc")
{
    std::cout << "test_invoke_a sample";
}



namespace
{
    template< class _Ty >
    struct visitor : public std::unary_function<_Ty, void>
    {
        void operator()( const _Ty& x )
        {
            std::cout << x << "\t";
        }
    };

    void test_for_each()
    {    

        typedef std::list<int> intlist;
        intlist il;
        for ( int i = 0; i < 10; i++ )
        {
            il.push_back(i);
        }
        std::for_each( il.begin(), il.end(), visitor<int>() );
    }
}

namespace
{
    /**
     *  select the second parameter from a std::pair 
     */
    template< class _Pair >
    struct select2nd_t
        : public std::unary_function< _Pair, typename _Pair::second_type >
    {
        const typename _Pair::second_type& operator()( const _Pair& _x )
        {
            return _x.second;
        }
    };
    

    /**
     *  compose _Func1 and _Func2 
     *  use the return value of _Func2 as the parameter of the _Func1 and return the return value of _Func1
     */
    template< class _Func1, class _Func2 >
    struct compose_t : public std::unary_function< typename _Func2::argument_type, typename _Func1::result_type >
    {
        _Func1 __func1;
        _Func2 __func2;

        compose_t( const _Func1& f1, const _Func2& f2 ) : __func1(f1), __func2(f2) {}

        typename _Func1::result_type operator()( const typename _Func2::argument_type& _x )
        {
            return __func1( __func2( _x ) );
        }
    };

    template< class _Map, class _Func >
    void for_each_2nd1( const _Map& _map, const _Func& func )
    {
        std::for_each( _map.begin(), _map.end(), compose_t<_Func, select2nd_t<typename _Map::value_type> >( func, select2nd_t<typename _Map::value_type>() ) );
    };

    template< class _Func1, class _Func2 >
    inline compose_t< _Func1, _Func2 > compose( const _Func1& func1, const _Func2& func2 )
    {
        return compose_t< _Func1, _Func2 >( func1, func2 );
    }

    template< class _Map, class _Func >
    void for_each_2nd2( const _Map& _map, const _Func& func )
    {
        std::for_each( _map.begin(), _map.end(), compose( func, select2nd_t<typename _Map::value_type>() ) );
    };
    

    void tset_for_each_2nd()
    {
        typedef std::map<int, int> intmap;
        intmap im;
        for ( int i = 0; i < 10; ++i )
        {
            im.insert( intmap::value_type(i, i * 100) );
        }
     
        for_each_2nd1( im, visitor<int>() );
        for_each_2nd2( im, visitor<int>() );
    }
}

TEST( test_functor )
{
    test_for_each();
    tset_for_each_2nd();

    std::cout << "a";
}

