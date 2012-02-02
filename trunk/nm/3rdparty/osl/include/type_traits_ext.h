#ifndef OSLIB_TYPE_TRAITS_EXT_H_
#define OSLIB_TYPE_TRAITS_EXT_H_

#include "osl/include/platform_micros.h"

#if defined(H_OS_WINDOWS ) || defined(H_OS_WINCE)
//
namespace stdext
{
    struct true_type
    {
        enum {value = true};
        typedef true_type type;
    };
    struct false_type
    {
        enum {value = false};
        typedef false_type type;
    };

    template<bool>
    struct _Cat_base;
    template<>
    struct _Cat_base<false>
            : false_type
    {
    };
    template<>
    struct _Cat_base<true>
            : true_type
    {
    };
    template<typename Type>
    struct _Is_Internal_Type
            : false_type
    {
    };

    template<>
    struct _Is_Internal_Type<bool>
            : true_type
    {
    };

    template<>
    struct _Is_Internal_Type<char>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<unsigned char>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<signed char>
            : true_type
    {
    };

    //template<>
    //struct _Is_Internal_Type<wchar_t>
    //	: true_type
    //{
    //};
    template<>
    struct _Is_Internal_Type<unsigned short>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<signed short>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<unsigned int>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<signed int>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<unsigned long>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<signed long>
            : true_type
    {
    };

    template<>
    struct _Is_Internal_Type<__int64>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<unsigned __int64>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<float>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<double>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<long double>
            : true_type
    {
    };

    // pointer is deprecated.
    template<>
    struct _Is_Internal_Type<void*>
            : false_type
    {
    };

    template<class _Ty>
    struct is_intetnal_type
            : _Is_Internal_Type<_Ty>
    {
    };

    template<class _Ty>
    struct _Is_pod : _Cat_base < is_intetnal_type<_Ty>::value || __has_trivial_constructor( _Ty ) && __is_pod( _Ty ) >
    {
    };

    //! \brief 同tr1中is_pod
    template<class _Ty>
    struct is_pod
            : _Is_pod<_Ty>
    {
    };

    template<bool>
    struct bool_type;

    template<>
    struct bool_type<false>
    {
        typedef false_type type;
    };

    template<>
    struct bool_type<true>
    {
        typedef true_type type;
    };



    //! \brief 同tr1中remove_pointer
    template<class _Ty>
    struct remove_pointer
    {
        typedef _Ty type;
    };

    template<class _Ty>
    struct remove_pointer<_Ty *>
    {
        typedef _Ty type;
    };

    template<class _Ty>
    struct remove_pointer<_Ty *const>
    {
        // remove pointer
        typedef _Ty type;
    };

    template<class _Ty>
    struct remove_pointer<_Ty *volatile>
    {
        // remove pointer
        typedef _Ty type;
    };

    template<class _Ty>
    struct remove_pointer<_Ty *const volatile>
    {
        // remove pointer
        typedef _Ty type;
    };


}

#define STD_EXT_BEGIN   namespace stdext{
#define STD_EXT_END     }

#define IS_POD_TYPE( type , booltype ) namespace stdext{    \
        template<>                                              \
        struct is_pod<type>: booltype##_type{};                     \
    }

#endif

#ifdef H_OS_LINUX

//must be enabled with the -std=c++0x or -std=gnu++0x compiler options.

#include<tr1/type_traits>
namespace stdext
{
    using std::tr1::is_pod;
    using std::tr1::remove_pointer;

    struct true_type
    {
        enum {value = true};
        typedef true_type type;
    };
    struct false_type
    {
        enum {value = false};
        typedef false_type type;
    };
    template<bool>
    struct bool_type;

    template<>
    struct bool_type<false>
    {
        typedef false_type type;
    };

    template<>
    struct bool_type<true>
    {
        typedef true_type type;
    };


    template<typename Type>
    struct _Is_Internal_Type
            : false_type
    {
    };

    template<>
    struct _Is_Internal_Type<bool>
            : true_type
    {
    };

    template<>
    struct _Is_Internal_Type<char>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<unsigned char>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<signed char>
            : true_type
    {
    };

    //template<>
    //struct _Is_Internal_Type<wchar_t>
    //  : true_type
    //{
    //};
    template<>
    struct _Is_Internal_Type<unsigned short>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<signed short>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<unsigned int>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<signed int>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<unsigned long>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<signed long>
            : true_type
    {
    };

    template<>
    struct _Is_Internal_Type<signed long long>
            : true_type
    {
    };

    template<>
    struct _Is_Internal_Type<unsigned long long>
            : true_type
    {
    };




    template<>
    struct _Is_Internal_Type<float>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<double>
            : true_type
    {
    };
    template<>
    struct _Is_Internal_Type<long double>
            : true_type
    {
    };

    // pointer is deprecated.
    template<>
    struct _Is_Internal_Type<void*>
            : false_type
    {
    };

    template<class _Ty>
    struct is_intetnal_type
            : _Is_Internal_Type<_Ty>
    {
    };

}

#define STD_EXT_BEGIN   namespace std{ namespace tr1{
#define STD_EXT_END     }}


#define IS_POD_TYPE( type , booltype ) namespace std{namespace tr1{ \
            template<>                                                  \
            struct is_pod<type>: booltype##_type{};                                \
        }}


#endif



//------------------------------------------------------
// Follow template used for compile time type checking
namespace stdext
{
    template<class T, class U>
    struct Test_Type
    {
        typedef false_type type;
    };
    template<typename tag>
    inline void test_bool_type_help( true_type , tag )
    {
    }


    template<typename tag>
    inline void test_bool_type_help( false_type , tag  );//!<不要给这个函输增加实现


    //! \brief  编译检测T为false_type则链接错误
    //! \tparam T true_type或者false_type
    template<class T>
    inline void test_bool_type( T )
    {
        test_bool_type_help( T() , int() );
    }

    //! \brief  编译检测T为false_type则链接错误
    //! \tparam T true_type或者false_type
    //! \tparam U 任意数据,占位符无意义
    template<class T, class U>
    inline void test_bool_type( T, U )
    {
        test_bool_type_help( T() , int() );
    }

    //! \brief  同tr1中is_same
    template<class T, class U>
    struct is_same
    {
        typedef false_type type;
        enum { value = 0 };
    };
    template<class T>
    struct is_same<T, T>
    {
        typedef true_type type;
        enum { value = 1 };
    };

    //! \brief  同tr1中remove_const
    template<class T>
    struct remove_const
    {
        typedef T type;
    };
    template<class T>
    struct remove_const<const T>
    {
        typedef T type;
    };
    //! \brief  同tr1中remove_reference
    template<class T>
    struct remove_reference
    {
        typedef T type;
    };
    template<class T>
    struct remove_reference<T&>
    {
        typedef T type;
    };

    //! \brief  同tr1中remove_cr
    template<class T>
    struct remove_cr
    {
        typedef typename remove_reference<typename remove_const<T>::type >::type type;
    };

    //! \brief 同tr1种的is_pointer 但判断不严谨
    template<class _Ty>
    struct is_pointer
        : false_type
    {
    };

    template<class _Ty>
    struct is_pointer<_Ty *>
        : true_type
    {
    };


};//stdext namespace


#endif //#ifndef OSLIB_TYPE_TRAITS_EXT_H_



