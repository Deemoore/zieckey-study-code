
#ifndef QOSLIB_STL_EX_
#define QOSLIB_STL_EX_

namespace osl
{



    // Use to compare the first element only of a pair
    // e.g. typedef std::set<std::pair<int, Data*>, compare_pair<int, Data*> > some_pair_set_t;
    template <typename T1, typename T2>
    struct compare_pair_first
    {
        bool operator()( const std::pair<T1, T2>& a, const std::pair<T1, T2>& b ) const
        {
            return a.first < b.first;
        }
    };

    template <typename T1, typename T2>
    struct compare_pair_greater
    {
        bool operator()( const std::pair<T1, T2>& a, const std::pair<T1, T2>& b ) const
        {
            if ( !( a.first < b.first ) )
            {
                return true;
            }
            else if ( !( b.first < a.first ) )
            {
                return false;
            }
            else
            {
                return !( a.second < b.second );
            }
        }
    };

    // Use to compare the contents of two pointers (e.g. std::string*)
    template <typename T>
    struct compare_pointer_contents
    {
        typedef const T* Tptr;
        bool operator()( const Tptr& a, const Tptr& b ) const
        {
            return *a < *b;
        }
    };

    // DeletePointer is a simple helper for deleting ah_ pointers in a container.
    // The general form is:
    //
    //  std::for_each(cont.begin(), cont.end(), DeletePointer());

    struct DeletePointer
    {
        template<typename T> void operator()( T* ptr ) const
        {
            delete ptr;
        }
    };
    struct DeletePointerArray
    {
        template<typename T> void operator()( T* ptr ) const
        {
            delete[] ptr;
        }
    };

    //! Unref paired pointer.
    //! 参数不接受智能指针类型 
    struct UnrefPointer
    {
        template<typename T> void operator()( T *ptr ) const
        {
            ptr->unref();
        }
    };


    //! Unref paired pointer.
    //! 不接second参数为智能指针类型
    struct UnrefPairedPointer
    {
        template<typename T,class U> void operator()( std::pair<T,U*> &ptr ) const
        {
            ptr.second->unref();
        }
    };

    //! Realease com interface
    //! 参数不接受智能指针类型 
    struct ReleaseCOMInterface
    {
        template<typename T> void operator()( T* pITF ) const
        {
            pITF->Release();
        }
    };

    // DeletePointer is a simple helper for deleting ah_ pointers in a map.
    // The general form is:
    //
    //  std::for_each(somemap.begin(), somemap.end(), DeletePairedPointer());

    struct DeletePairedPointer
    {
        template<typename T> void operator()( T &ptr ) const
        {
            delete ptr.second;
        }
    };
    struct DeletePairedPointerArray
    {
        template<typename T> void operator()( T &ptr ) const
        {
            delete[] ptr.second;
        }
    };


    // Alternate version of the above so that has a more cumbersome
    // syntax, but it can be used with compositional functors.
    // NOTE: The functor retuns a bool because msdev bombs during the
    // composition if you return void. Once we upgrade to a newer
    // compiler, the second unary_function template parameter can be set
    // to void.
    //
    // Here's a snippit showing how you use this object:
    //
    // typedef Map<int, widget*> map_type;
    // map_type widget_map;
    // ... // add elements
    // // delete them ah_
    // for_each(widget_map.begin(),
    //          widget_map.end(),
    //          h_compose1(DeletePointerFunctor<widget>(),
    //                     h_select2nd<map_type::value_type>()));

    template<typename T>
    struct DeletePointerFunctor : public std::unary_function<T*, bool>
    {
        bool operator()( T* ptr ) const
        {
            delete ptr;
            return true;
        }
    };

    // See notes about DeleteArray for why you should consider avoiding this.
    template<typename T>
    struct DeleteArrayFunctor : public std::unary_function<T*, bool>
    {
        bool operator()( T* ptr ) const
        {
            delete[] ptr;
            return true;
        }
    };

    // CopyNewPointer is a simple helper which accepts a pointer, and
    // returns a new pointer built with the copy constructor. Example:
    //
    //  transform(in.begin(), in.end(), out.end(), CopyNewPointer());

    struct CopyNewPointer
    {
        template<typename T> T* operator()( const T* ptr ) const
        {
            return new T( *ptr );
        }
    };

    //! 从容器中移除指定值的对象
    //! \tparam _Container  容器类型 , 适合Vector和List
    //! \tparam _T  要移除的元素类型
    //! \param[in] c    容器
    //! \param[in] val  移除的数值
    //! \retval true    容器中有对应的元素,且移除成功.
    //! \retval false   容器中无此元素
    template <typename _Container, typename _T >
    inline bool erase_element( _Container& c, const _T& val )
    {
        typedef typename _Container::iterator iterator;
        iterator ite = std::find( c.begin() , c.end() , val );

        if ( ite != c.end() )
        {
            c.erase( ite );
            return true;
        }
        else
        {
            return false;
        }
    };

    //! 移除容器元素,移除前调用元素的unref成员函数
    //! \copydetails erase_element(_Container&,const _T&)
    template <typename _Container, typename _T >
    inline bool erase_unref_element( _Container& c, _T* val )
    {
        typedef typename _Container::iterator iterator;
        iterator ite = std::find( c.begin() , c.end() , val );

        if ( ite != c.end() )
        {
            val->unref();
            c.erase( ite );
            return true;
        }
        else
        {
            return false;
        }
    };

    //! 移除容器元素,移除前使用delete删除元素
    //! \copydetails erase_element(_Container&,const _T&)
    template <typename _Container, typename _T >
    inline bool erase_delete_element( _Container& c, const _T* val )
    {
        typedef typename _Container::iterator iterator;
        iterator ite = std::find( c.begin() , c.end() , val );

        if ( ite != c.end() )
        {
            delete val;
            c.erase( ite );
            return true;
        }
        else
        {
            return false;
        }
    };

    //! 移除容器元素,移除前调用second成员的unref成员函数
    //! \tparam _Container  容器类型 Map,Value对应的必须是指针类型,不得是智能指针.
    //! \tparam _T  要移除的元素类型 Map的Key值
    //! \param[in] c    容器
    //! \param[in] val  key值
    //! \retval true    容器中有对应的元素,且移除成功.
    //! \retval false   容器中无此元素
    template <typename _Container, typename _T >
    inline bool erase_unref_second_element( _Container& c, const _T& val )
    {
        typedef typename _Container::iterator iterator;
        iterator ite = c.find( val );

        if ( ite != c.end() )
        {
            ite->second->unref();
            c.erase( ite );
            return true;
        }
        else
        {
            return false;
        }
    };

    //! 移除容器元素,移除前使用delete 删除second成员
    //! \copydetails erase_unref_second_element(_Container&,const _T&)
    template <typename _Container, typename _T >
    inline bool erase_delete_second_element( _Container& c, const _T& val )
    {
        typedef typename _Container::iterator iterator;
        iterator ite = c.find( val );

        if ( ite != c.end() )
        {
            delete ite->second;
            c.erase( ite );
            return true;
        }
        else
        {
            return false;
        }

        //return false;
    };

    //! 对容器中所有元素调用unref方法,然后将容器清空
    template <typename _Container>
    inline void clear_unref_elements( _Container& c )
    {
        if( !c.empty() )
        {
            std::for_each( c.begin(), c.end(), UnrefPointer() );
            c.clear();
        }
    };

    /// Clear the container and do delete operation on each element.
    template <typename _Container>
    inline void clear_delete_elements( _Container& c )
    {
        if( !c.empty() )
        {
            std::for_each( c.begin(), c.end(), DeletePointer() );
            c.clear();
        }

    };

    /// Clear the container and do unref operation on each element.
    template <typename _Container>
    inline void clear_unref_second_elements( _Container& c )
    {
        if( !c.empty() )
        {
            std::for_each( c.begin(), c.end(), UnrefPairedPointer() );
            c.clear();
        }
    };

    /// Clear the container and do unref operation on each element.
    template <typename _Container>
    inline void clear_delete_second_elements( _Container& c )
    {
        if( !c.empty() )
        {
            std::for_each( c.begin(), c.end(), DeletePairedPointer() );
            c.clear();
        }
    };

    //! 容器是否包含指定元素,适合Vector和HList
    //! \param[in] c    容器
    //! \param[in] val  元素
    //! \retval true 找到对应的元素
    //! \retval true 未找到对应的元素
    template <typename Container, typename T >
    inline bool is_contain( const Container& c, const T& val )
    {
        return ( c.end() != find( c.begin(), c.end() , val ) );
    };



    // Simple function to help with finding pointers in maps.
    // For example:
    // 	typedef  map_t;
    //  Map<int, const char*> foo;
    //	foo[18] = "there";
    //	foo[2] = "heh_o";
    // 	const char* bar = get_ptr_in_map(foo, 2); // bar -> "heh_o"
    //  const char* baz = get_ptr_in_map(foo, 3); // baz == NULL
    template <typename K, typename T, typename N>
    inline T* get_ptr_in_map( const osl::Map<K, T*, N>& iHMap, const K& key )
    {
        // Typedef here avoids warnings because of new c++ naming rules.
        typedef typename osl::Map<K, T*, N>::const_iterator map_iter;
        map_iter iter = iHMap.find( key );

        if ( iter == iHMap.end() )
        {
            return NULL;
        }
        else
        {
            return iter->second;
        }
    };

    // helper function which returns true if key is in iHMap.
    template <typename K, typename T, typename N>
    inline bool is_in_map( const osl::Map<K, T, N>& iHMap, const K& key )
    {
        typedef typename osl::Map<K, T, N>::const_iterator map_iter;

        if ( iHMap.find( key ) == iHMap.end() )
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    // Similar to get_ptr_in_map, but for any type with a valid T(0) constructor.
    // To replace LLSkipMap getIfThere, use:
    //   get_if_there(map, key, 0)
    // WARNING: Make sure default_value (generah_y 0) is not a valid map entry!
    template <typename K, typename T, typename N>
    inline T get_if_there( const osl::Map<K, T, N>& iHMap, const K& key, T default_value )
    {
        // Typedef here avoids warnings because of new c++ naming rules.
        typedef typename osl::Map<K, T, N>::const_iterator map_iter;
        map_iter iter = iHMap.find( key );

        if ( iter == iHMap.end() )
        {
            return default_value;
        }
        else
        {
            return iter->second;
        }
    };

    // Useful for replacing the removeObj() functionality of LLDynamicArray
    // Example:
    //  for (osl::Vector<T>::iterator iter = mList.begin(); iter != mList.end(); )
    //  {
    //    if ((*iter)->isMarkedForRemoval())
    //      iter = vector_replace_with_last(mList, iter);
    //    else
    //      ++iter;
    //  }
    template <typename T, typename Iter, typename N>
    inline Iter vector_replace_with_last( osl::Vector<T, N>& invec, Iter iter )
    {
        typename osl::Vector<T, N>::iterator last = invec.end();
        --last;

        if ( iter == invec.end() )
        {
            return iter;
        }
        else if ( iter == last )
        {
            invec.pop_back();
            return invec.end();
        }
        else
        {
            *iter = *last;
            invec.pop_back();
            return iter;
        }
    };

    // Useful for replacing the removeObj() functionality of LLDynamicArray
    // Example:
    //   vector_replace_with_last(mList, x);
    template <typename T, typename N>
    inline bool vector_replace_with_last( osl::Vector<T, N>& invec, const T& val )
    {
        typename osl::Vector<T, N>::iterator iter = std::find( invec.begin(), invec.end(), val );

        if ( iter != invec.end() )
        {
            typename osl::Vector<T, N>::iterator last = invec.end();
            --last;
            *iter = *last;
            invec.pop_back();
            return true;
        }

        return false;
    }


    // Append N elements to the vector and return a pointer to the first new element.
    template <typename T, typename N>
    inline T* vector_append( osl::Vector<T, N>& invec, int nSize )
    {
        unsigned int sz = ( unsigned int )invec.size();
        invec.resize( sz + nSize );
        return &( invec[sz] );
    }

    // cah_ function f to n members starting at first. similar to std::for_each
    template <class InputIter, class Size, class Function>
    Function h_for_n( InputIter first, Size n, Function f )
    {
        for ( ; n > 0; --n, ++first )
        {
            f( *first );
        }

        return f;
    }

    // copy first to result n times, incrementing each as we go
    template <class InputIter, class Size, class OutputIter>
    OutputIter h_copy_n( InputIter first, Size n, OutputIter result )
    {
        for ( ; n > 0; --n, ++result, ++first )
        {
            *result = *first;
        }

        return result;
    }

    // set  *result = op(*f) for n elements of f
    template <class InputIter, class OutputIter, class Size, class UnaryOp>
    OutputIter h_transform_n(
        InputIter first,
        Size n,
        OutputIter result,
        UnaryOp op )
    {
        for ( ; n > 0; --n, ++result, ++first )
        {
            *result = op( *first );
        }

        return result;
    }



    /*
    *
    * Copyright (c) 1994
    * Hewlett-Packard Company
    *
    * Permission to use, copy, modify, distribute and seh_ this software
    * and its documentation for any purpose is hereby granted without fee,
    * provided that the above copyright notice appear in ah_ copies and
    * that both that copyright notice and this permission notice appear
    * in supporting documentation.  Hewlett-Packard Company makes no
    * representations about the suitability of this software for any
    * purpose.  It is provided "as is" without express or implied warranty.
    *
    *
    * Copyright (c) 1996-1998
    * Silicon Graphics Computer Systems, Inc.
    *
    * Permission to use, copy, modify, distribute and seh_ this software
    * and its documentation for any purpose is hereby granted without fee,
    * provided that the above copyright notice appear in ah_ copies and
    * that both that copyright notice and this permission notice appear
    * in supporting documentation.  Silicon Graphics makes no
    * representations about the suitability of this software for any
    * purpose.  It is provided "as is" without express or implied warranty.
    */


    // helper to deal with the fact that MSDev does not package
    // select... with the stl. Look up usage on the sgi website.

    template <class _Pair>
    struct _h_Select1st : public std::unary_function<_Pair, typename _Pair::first_type>
    {
        const typename _Pair::first_type& operator()( const _Pair& __x ) const
        {
            return __x.first;
        }
    };

    template <class _Pair>
    struct _h_Select2nd : public std::unary_function<_Pair, typename _Pair::second_type>
    {
        const typename _Pair::second_type& operator()( const _Pair& __x ) const
        {
            return __x.second;
        }
    };

    template <class _Pair> struct h_select1st : public _h_Select1st<_Pair> {};
    template <class _Pair> struct h_select2nd : public _h_Select2nd<_Pair> {};

    // helper to deal with the fact that MSDev does not package
    // compose... with the stl. Look up usage on the sgi website.

    template <class _Operation1, class _Operation2>
    class h_unary_compose :
        public std::unary_function < typename _Operation2::argument_type,
        typename _Operation1::result_type >
    {
    protected:
        _Operation1 __op1;
        _Operation2 __op2;
    public:
        h_unary_compose( const _Operation1& __x, const _Operation2& __y )
            : __op1( __x ), __op2( __y ) {}
        typename _Operation1::result_type
            operator()( const typename _Operation2::argument_type& __x ) const
        {
            return __op1( __op2( __x ) );
        }
    };

    template <class _Operation1, class _Operation2>
    inline h_unary_compose<_Operation1, _Operation2>
        h_compose1( const _Operation1& __op1, const _Operation2& __op2 )
    {
        return h_unary_compose<_Operation1, _Operation2>( __op1, __op2 );
    }

    template <class _Operation1, class _Operation2, class _Operation3>
    class h_binary_compose
        : public std::unary_function < typename _Operation2::argument_type,
        typename _Operation1::result_type >
    {
    protected:
        _Operation1 _M_op1;
        _Operation2 _M_op2;
        _Operation3 _M_op3;
    public:
        h_binary_compose( const _Operation1& __x, const _Operation2& __y,
            const _Operation3& __z )
            : _M_op1( __x ), _M_op2( __y ), _M_op3( __z ) { }
        typename _Operation1::result_type
            operator()( const typename _Operation2::argument_type& __x ) const
        {
            return _M_op1( _M_op2( __x ), _M_op3( __x ) );
        }
    };

    template <class _Operation1, class _Operation2, class _Operation3>
    inline h_binary_compose<_Operation1, _Operation2, _Operation3>
        h_compose2( const _Operation1& __op1, const _Operation2& __op2,
        const _Operation3& __op3 )
    {
        return h_binary_compose<_Operation1, _Operation2, _Operation3>
            ( __op1, __op2, __op3 );
    }

    // helpers to deal with the fact that MSDev does not package
    // bind... with the stl. Again, this is from sgi.
    template <class _Operation>
    class h_binder1st :
        public std::unary_function < typename _Operation::second_argument_type,
        typename _Operation::result_type >
    {
    protected:
        _Operation op;
        typename _Operation::first_argument_type value;
    public:
        h_binder1st( const _Operation& __x,
            const typename _Operation::first_argument_type& __y )
            : op( __x ), value( __y ) {}
        typename _Operation::result_type
            operator()( const typename _Operation::second_argument_type& __x ) const
        {
            return op( value, __x );
        }
    };

    template <class _Operation, class _Tp>
    inline h_binder1st<_Operation>
        h_bind1st( const _Operation& __oper, const _Tp& __x )
    {
        typedef typename _Operation::first_argument_type _Arg1_type;
        return h_binder1st<_Operation>( __oper, _Arg1_type( __x ) );
    }

    template <class _Operation>
    class h_binder2nd
        : public std::unary_function < typename _Operation::first_argument_type,
        typename _Operation::result_type >
    {
    protected:
        _Operation op;
        typename _Operation::second_argument_type value;
    public:
        h_binder2nd( const _Operation& __x,
            const typename _Operation::second_argument_type& __y )
            : op( __x ), value( __y ) {}
        typename _Operation::result_type
            operator()( const typename _Operation::first_argument_type& __x ) const
        {
            return op( __x, value );
        }
    };

    template <class _Operation, class _Tp>
    inline h_binder2nd<_Operation>
        h_bind2nd( const _Operation& __oper, const _Tp& __x )
    {
        typedef typename _Operation::second_argument_type _Arg2_type;
        return h_binder2nd<_Operation>( __oper, _Arg2_type( __x ) );
    }



    //! \brief  增强版的 binder1st
    template<class _Fn2>
    class binder1st
        : public std::unary_function < typename _Fn2::second_argument_type,
        typename _Fn2::result_type >
    {
        // functor adapter _Func(stored, right)
    public:
        typedef std::unary_function < typename _Fn2::second_argument_type,
            typename _Fn2::result_type > _Base;
        typedef typename stdext::remove_cr<typename _Base::argument_type>::type argument_type;
        typedef typename _Base::result_type result_type;

        binder1st( const _Fn2& _Func,
            const typename stdext::remove_reference<typename _Fn2::first_argument_type>::type & _Left )
            : op( _Func ), value( _Left )
        {
            // construct from functor and left operand
        }

        result_type operator()( const argument_type& _Right ) const
        {
            // apply functor to operands
            return ( op( value, _Right ) );
        }

        result_type operator()( argument_type& _Right ) const
        {
            // apply functor to operands
            return ( op( value, _Right ) );
        }
        result_type operator()( const argument_type& _Right )
        {
            // apply functor to operands
            return ( op( value, _Right ) );
        }

        result_type operator()( argument_type& _Right )
        {
            // apply functor to operands
            return ( op( value, _Right ) );
        }
    protected:
        _Fn2 op;  // the functor to apply
        typename _Fn2::first_argument_type value;  // the left operand
    };

    //! \brief  增强版的 bind1st 可以bind参数因为&的 函数.
    template<class _Fn2, class _Ty>
    inline binder1st<_Fn2> bind1st( const _Fn2& _Func, const _Ty& _Left )
    {
        // return a binder1st functor adapter
        typename _Fn2::first_argument_type _Val( _Left );
        return ( binder1st<_Fn2>( _Func, _Val ) );
    }


    template<class _Fn2>
    class binder2nd
        : public std::unary_function < typename _Fn2::first_argument_type,
        typename _Fn2::result_type >
    {
        // functor adapter _Func(left, stored)
    public:
        typedef std::unary_function < typename _Fn2::first_argument_type,
            typename _Fn2::result_type > _Base;
        typedef typename stdext::remove_cr<typename _Base::argument_type>::type argument_type;
        typedef typename _Base::result_type result_type;

        binder2nd( const _Fn2& _Func,
            const typename stdext::remove_reference<typename _Fn2::second_argument_type>::type& _Right )
            : op( _Func ), value( _Right )
        {
            // construct from functor and right operand
        }

        result_type operator()( const argument_type& _Left ) const
        {
            // apply functor to operands
            return ( op( _Left, value ) );
        }

        result_type operator()( argument_type& _Left ) const
        {
            // apply functor to operands
            return ( op( _Left, value ) );
        }
        result_type operator()( const argument_type& _Left )
        {
            // apply functor to operands
            return ( op( _Left, value ) );
        }

        result_type operator()( argument_type& _Left )
        {
            // apply functor to operands
            return ( op( _Left, value ) );
        }
    protected:
        _Fn2 op;  // the functor to apply
        typename _Fn2::second_argument_type value;  // the right operand
    };

    //! \brief  增强版的 bind2nd 可以bind参数因为&的 函数.
    template < class _Fn2,
    class _Ty > inline
        binder2nd<_Fn2> bind2nd( const _Fn2& _Func, const _Ty& _Right )
    {
        // return a binder2nd functor adapter
        typename _Fn2::second_argument_type _Val( _Right );
        return ( binder2nd<_Fn2>( _Func, _Val ) );
    }


    template<class MAP , class Functor>
    void for_each_process2nd( const MAP & realActorMap , const Functor& funWork )
    {
        //         typename MAP::const_iterator beg = realActorMap.begin() ;
        //         typename MAP::const_iterator end = realActorMap.end();
        //         for( ; beg != end ; ++beg)
        //         {
        //             funWork( beg->second );
        //         }
        for_each( realActorMap.begin() , realActorMap.end()
            , osl::h_compose1( funWork , osl::h_select2nd<typename MAP::value_type>() )
            );
    }
#define forEachMapProcess2nd for_each_process2nd //for compatible old code

    template<class MAP , class Functor>
    void for_each_process1st( const MAP & realActorMap , const Functor& funWork )
    {
        //         typename MAP::const_iterator beg = realActorMap.begin() ;
        //         typename MAP::const_iterator end = realActorMap.end();
        //         for( ; beg != end ; ++beg)
        //         {
        //             funWork( beg->second );
        //         }
        for_each( realActorMap.begin() , realActorMap.end()
            , osl::h_compose1( funWork , osl::h_select1st<typename MAP::value_type>() )
            );
    }
#define forEachMapProcess1st for_each_process1st









    namespace detail
    {
        template<class SET , class F>
        F detail_remove_if( SET& s, F f )
        {
            typedef typename SET::iterator Iterator ;
            Iterator end = s.end() ;

            for ( Iterator iter = s.begin() ; iter != end ; )
            {
                if ( f( *iter ) )
                {
                    s.erase( iter++ );
                }
                else
                {
                    ++iter;
                }
            }

            return f;
        }
    }

    //! 移除容器中的指定的元素。
    template<class KEY, class VALUE , class F>
    F container_remove_if( std::map<KEY, VALUE>& m, F f )
    {
        return detail::detail_remove_if( m , f );
    }
    //! 移除容器中的指定的元素。
    template<class TYPE , class F>
    F container_remove_if( std::set<TYPE>& s, F f )
    {
        return detail::detail_remove_if( s , f );
    }
    //! 移除容器中的指定的元素。
    template<class KEY, class VALUE , class F>
    F container_remove_if( std::multimap<KEY, VALUE>& m, F f )
    {
        return detail::detail_remove_if( m , f );
    }
    //! 移除容器中的指定的元素。
    template<class TYPE , class F>
    F container_remove_if( std::multiset<TYPE>& s, F f )
    {
        return detail::detail_remove_if( s , f );
    }



    //! 移除容器中的指定的元素。
    template<class KEY, class VALUE , class F>
    F container_remove_if( HashMap<KEY, VALUE>& m, F f )
    {
        return detail::detail_remove_if( m , f );
    }

    //! 移除容器中的指定的元素。
    template<class KEY, class VALUE , class F>
    F container_remove_if( Map<KEY, VALUE>& m, F f )
    {
        return detail::detail_remove_if( m , f );
    }
    //! Remove a certain element from the container
    template<class TYPE , typename _ContainerName, class F>
    F container_remove_if( Set<TYPE, _ContainerName>& s, F f )
    {
        return detail::detail_remove_if( s , f );
    }
    //! Remove a certain element from the container
    template<class KEY, class VALUE ,  typename _ContainerName, class F>
    F container_remove_if( MultiMap<KEY, VALUE, _ContainerName>& m, F f )
    {
        return detail::detail_remove_if( m , f );
    }
    //! Remove a certain element from the container
    template<class TYPE , class F>
    F container_remove_if( std::list<TYPE>& lst , F f )
    {
        lst.remove_if( f );
        return f;
    }
    //! Remove a certain element from the container
    template<class TYPE ,  typename _ContainerName, class F>
    F container_remove_if( List<TYPE, _ContainerName>& lst , F f )
    {
        lst.remove_if( f );
        return f;
    }
    //! Remove a certain element from the container
    template<class TYPE , class F>
    F container_remove_if( std::vector<TYPE>& vec, F f )
    {
        vec.erase(
            std::remove_if ( vec.begin() , vec.end() , f )
            , vec.end() );
        return f;
    }
    //! Remove a certain element from the container
    template<class TYPE ,  typename _ContainerName, class F>
    F container_remove_if( Vector<TYPE, _ContainerName>& vec, F f )
    {
        vec.erase(
            std::remove_if ( vec.begin() , vec.end() , f )
            , vec.end() );
        return f;
    }

    namespace detail
    {
        template<class MAP , class F , class F2>
        F map_remove_if( MAP& s, F f , F2 f2 )
        {
            typedef typename MAP::iterator Iterator ;
            Iterator end = s.end() ;

            for ( Iterator iter = s.begin() ; iter != end ; )
            {
                if ( f( f2( *iter ) ) )
                {
                    s.erase( iter++ );
                }
                else
                {
                    ++iter;
                }
            }

            return f;
        }
    }
    template<class MAP , class F>
    F map_remove_if_second( MAP& s, F f )
    {
        return detail::map_remove_if( s , f , h_select2nd<typename MAP::value_type>() );
    }
    template<class MAP , class F>
    F map_remove_if_first( MAP& s, F f )
    {
        return detail::map_remove_if( s , f , h_select1st<typename MAP::value_type>() );
    }

}






#endif
