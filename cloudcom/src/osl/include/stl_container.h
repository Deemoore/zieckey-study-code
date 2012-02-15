
#ifndef QOSLIB_STLCONTAINER_
#define QOSLIB_STLCONTAINER_


#include "osl/include/stl_allocator.h"


namespace osl
{

	struct null_pointer : std::exception
	{
	};

    struct Less_PChar
    {
        bool operator()( const char* l, const char* r )
        {
            return ( 0 < strcmp( l , r ) );
        }
    };

#if defined(H_DEBUG_STL_MEM_FOOTPRINT)
    struct _EXPORT_OSLIB STL_Helper
    {

        template<class T>
        static const char* format( const char* pContainer , T )
        {
            return internalFormat( pContainer , typeid( T ).name() );
        }
        static STL_Helper* spHelper;
        static void initializeClass();
        static void shutdownClass();
    private:
        static const char* internalFormat( const char* pContainer, const char* pTypeName );
        std::set<char* , Less_PChar > m_Strset;
    };


#else
    struct _EXPORT_OSLIB STL_Helper
    {
        template<class T>
        static const char* format( const char* pContainer , T )
        {
            return pContainer;
        }
        static void initializeClass() {}
        static void shutdownClass() {}
    };
#endif

    template<class T>
    struct STLHashMap: STL_Helper
    {
        static const char* NAME()
        {
            return format( "stl_hashmap" , T() );
        }
    };

    template<class T>
    struct STLMap: STL_Helper
    {
        static const char* NAME()
        {
            return format( "stl_map" , T() );
        }
    };

    template<class T>
    struct STLMultiMap: STL_Helper
    {
        static const char* NAME()
        {
            return format( "stl_multimap" , T() );
        }
    };

    template<class T>
    struct STLSet: STL_Helper
    {
        static const char* NAME()
        {
            return format( "stl_set" , T() );
        }
    };

    template<class T>
    struct STLVector: STL_Helper
    {
        static const char* NAME()
        {
            return format( "stl_vector" , T() );
        }
    };

    template<class T>
    struct STLList: STL_Helper
    {
        static const char* NAME()
        {
            return format( "stl_list" , T() );
        }
    };

};//namespace

//! type name struct.
#define H_TYPE_NAME( typename ) struct typename##_Type{ static const char* NAME(){ return #typename;}; } ;

// If we're using the GCC 3.1 C++ Std lib
#if (defined(H_COMPILER_GNUC) && H_COMP_VER >= 310)

#include <ext/hash_map>

namespace __gnu_cxx
{
    template<typename _TFirst, typename _TSecond >
    struct hash< std::pair<_TFirst, _TSecond> >
    {
        size_t operator()( const std::pair<_TFirst, _TSecond>& _Keyval ) const
        {
            __gnu_cxx::hash<_TFirst>   _T_First_Hash;
            __gnu_cxx::hash<_TSecond>  _T_Second_Hash;

            return _T_First_Hash( _Keyval.first ) | _TSecond_Hash( _Keyval.second );
            // hash _Keyval to size_t value one-to-one
            //return ( ( _Keyval.first << 16 | _Keyval.second ) );
        }
    };

    template <> struct hash< unsigned long long >
    {
        size_t operator()( const unsigned long long& _Keyval ) const
        {
            return _Keyval;
        }
    };
}


namespace osl
{

    using __gnu_cxx::hash_map;

    // Map
    template < typename _Kty
    , typename _Ty
    , typename _ContainerName = osl::STLHashMap<std::pair<const _Kty, _Ty> >
    , typename _HashFn = __gnu_cxx::hash<_Kty>
    , typename _EqualKey = std::equal_to<_Kty>  >
    class HashMap : public __gnu_cxx::hash_map<_Kty, _Ty, _HashFn, _EqualKey, osl::HSTLAllocator<std::pair<const _Kty, _Ty>, _ContainerName > >
    {
    };

};

//#VC
#else

_STDEXT_BEGIN

template<typename _TFirst, typename _TSecond >
inline size_t hash_value( const std::pair<_TFirst, _TSecond>& _Keyval )
{
    // hash _Keyval to size_t value one-to-one
    return ( hash_value( ( _Keyval.first << 16 | _Keyval.second ) )  ^ _HASH_SEED );
}

_STDEXT_END

namespace osl
{

    using _STDEXT hash_map;

    // Map
    template < typename _Kty
    , typename _Ty
    , typename _ContainerName = osl::STLHashMap<std::pair<const _Kty, _Ty> >
    , typename _Tr = _STDEXT hash_compare<_Kty, std::less<_Kty> >
    >
    class HashMap : public _STDEXT hash_map<_Kty, _Ty, _Tr, osl::HSTLAllocator<std::pair<const _Kty, _Ty>, _ContainerName > >
    {
        H_ALLOCRAW_OPERATORS( HashMap );
    };
};


#endif


namespace osl
{

    //////////////////////////////////////////////////////////////////////////
    //  Containers.
    //////////////////////////////////////////////////////////////////////////

//     using std::list;
//     using std::vector;
//     using std::map;
//     using std::set;
//     using std::multimap;



#ifdef H_OS_WINDOWS
    // List
    template < typename T,
             typename _ContainerName = osl::STLList<T> >
    class List : public std::list<T, osl::HSTLAllocator<T, _ContainerName> >
    {
    };

#endif // H_OS_WINDOWS


    // Vector
    template < typename T,
             typename _ContainerName = osl::STLVector<T> >
    class Vector : public std::vector<T, osl::HSTLAllocator<T, _ContainerName > >
    {
    };


    // Map
    template < typename _Kty
    , typename _Ty
    , typename _ContainerName = osl::STLMap<std::pair<const _Kty, _Ty> >
    , typename _Pr = std::less<_Kty> >
    class Map : public std::map<_Kty, _Ty, _Pr, osl::HSTLAllocator<std::pair<const _Kty, _Ty>, _ContainerName > >
    {
    };


    // Set
    template < class _Kty
    , typename _ContainerName = osl::STLSet<_Kty>
    , class _Pr = std::less<_Kty>  >
    class Set : public std::set<_Kty, _Pr, osl::HSTLAllocator<_Kty, _ContainerName> >
    {
    };


    template < typename _Kty
    , typename _Ty
    , typename _ContainerName = osl::STLMultiMap<std::pair<const _Kty, _Ty> >
    , typename _Pr = std::less<_Kty> >
    class MultiMap : public std::multimap< _Kty, _Ty, std::less<_Kty>, osl::HSTLAllocator<std::pair<const _Kty, _Ty>, _ContainerName > >
    {};



//------------------------------------------------------
// Helper macros for container declaration.
#ifdef H_MINI_MEM_USE

    //! Helper macro to define container
#define H_DEF_LIST( _Ty, _Name )  \
    typedef osl::List< _Ty > _Name;


    //! Helper macro to define container
#define H_DEF_VECTOR( _Ty, _Name )  \
    typedef osl::Vector< _Ty > _Name;


    //! Helper macro to define container
#define H_DEF_MAP( _Kty, _Ty, _Name )  \
    typedef osl::Map< _Kty, _Ty > _Name;


    //! Helper macro to define container
#define H_DEF_SET( _Ty, _Name )  \
    typedef osl::Set< _Ty > _Name;

    //! Helper macro to define hashmap
#define H_DEF_HASHMAP( _Kty, _Ty, _Name )  \
    typedef osl::HashMap< _Kty, _Ty > _Name;


    //! Helper macro to define container
#define H_DEF_MULTIMAP( _Kty, _Ty, _Name )  \
    typedef osl::MultiMap< _Kty, _Ty > _Name;


#else

    //! Helper macro to define container
#define H_DEF_LIST( _Ty, _Name )  \
    struct _Name##_Type{ static const char* NAME(){ return "stl_list_"#_Name;}; } ; \
    typedef osl::List< _Ty, _Name##_Type > _Name;


    //! Helper macro to define container
#define H_DEF_VECTOR( _Ty, _Name )  \
    struct _Name##_Type{ static const char* NAME(){ return "stl_vector_"#_Name;}; } ; \
    typedef osl::Vector< _Ty, _Name##_Type > _Name;


    //! Helper macro to define container
#define H_DEF_MAP( _Kty, _Ty, _Name )  \
    struct _Name##_Type{ static const char* NAME(){ return "stl_map_"#_Name;}; } ; \
    typedef osl::Map< _Kty, _Ty, _Name##_Type > _Name;


    //! Helper macro to define container
#define H_DEF_SET( _Ty, _Name )  \
    struct _Name##_Type{ static const char* NAME(){ return "stl_set_"#_Name;}; } ; \
    typedef osl::Set< _Ty, _Name##_Type > _Name;

    //! Helper macro to define hashmap
#define H_DEF_HASHMAP( _Kty, _Ty, _Name )  \
    struct _Name##_Type{ static const char* NAME(){ return "stl_hashmap_"#_Name;}; } ; \
    typedef osl::HashMap< _Kty, _Ty, _Name##_Type > _Name;


    //! Helper macro to define container
#define H_DEF_MULTIMAP( _Kty, _Ty, _Name )  \
    struct _Name##_Type{ static const char* NAME(){ return "stl_multimap_"#_Name;}; } ; \
    typedef osl::MultiMap< _Kty, _Ty, _Name##_Type > _Name;


#endif


    /** Wraps iteration over a vector.
    @remarks
    This class is here just to allow clients to iterate over an internal
    vector of a class without having to have access to the vector itself
    (typically to iterate you need both the iterator and the end() iterator
    to test for the end condition, which is messy).
    No updates are allowed through this interface, it is purely for
    iterating and reading.
    @par
    Note that like STL iterators, these iterators are only valid whilst no
    updates are made to the underlying collection. You should not attempt to
    use this iterator if a change is made to the collection. In fact, treat this
    iterator as a transient object, do NOT store it and try to use it repeatedly.
    */
    template <class T>
    class VectorIterator
    {
    private:
        typename T::iterator mCurrent;
        typename T::iterator mEnd;
        /// Private constructor since only the parameterised constructor should be used
        VectorIterator() {};
    public:
        typedef typename T::value_type ValueType;

        /** Constructor.
        @remarks
        Provide a start and end iterator to initialise.
        */
        VectorIterator( typename T::iterator start, typename T::iterator end )
            : mCurrent( start ), mEnd( end )
        {
        }

        /** Returns true if there are more items in the collection. */
        bool hasMoreElements( void ) const
        {
            return mCurrent != mEnd;
        }

        /** Returns the next element in the collection, and advances to the next. */
        typename T::value_type getNext( void )
        {
            return *mCurrent++;
        }
        /** Returns the next element in the collection, without advancing to the next. */
        typename T::value_type peekNext( void )
        {
            return *mCurrent;
        }
        /** Returns a pointer to the next element in the collection, without advancing to the next afterwards. */
        typename T::pointer peekNextPtr( void )
        {
            return &( *mCurrent );
        }
        /** Moves the iterator on one element. */
        void moveNext( void )
        {
            ++mCurrent;
        }



    };

    /** Wraps iteration over a map.
    @remarks
    This class is here just to allow clients to iterate over an internal
    map of a class without having to have access to the map itself
    (typically to iterate you need both the iterator and the end() iterator
    to test for the end condition, which is messy).
    No updates are allowed through this interface, it is purely for
    iterating and reading.
    @par
    Note that like STL iterators, these iterators are only valid whilst no
    updates are made to the underlying collection. You should not attempt to
    use this iterator if a change is made to the collection. In fact, treat this
    iterator as a transient object, do NOT store it and try to use it repeatedly.
    */
    template <class T>
    class MapIterator
    {
    private:
        typename T::iterator mCurrent;
        typename T::iterator mEnd;
        /// Private constructor since only the parameterised constructor should be used
        MapIterator() {};
    public:
        typedef typename T::mapped_type MappedType;
        typedef typename T::key_type KeyType;

        /** Constructor.
        @remarks
        Provide a start and end iterator to initialise.
        */
        MapIterator( typename T::iterator start, typename T::iterator end )
            : mCurrent( start ), mEnd( end )
        {
        }

        /** Returns true if there are more items in the collection. */
        bool hasMoreElements( void ) const
        {
            return mCurrent != mEnd;
        }

        /** Returns the next value element in the collection, and advances to the next. */
        typename T::mapped_type getNext( void )
        {
            return ( mCurrent++ )->second;
        }
        /** Returns the next value element in the collection, without advancing to the next. */
        typename T::mapped_type peekNextValue( void )
        {
            return mCurrent->second;
        }
        /** Returns the next key element in the collection, without advancing to the next. */
        typename T::key_type peekNextKey( void )
        {
            return mCurrent->first;
        }
        /** Required to overcome intermittent bug */
        MapIterator<T> & operator=( MapIterator<T> &rhs )
        {
            mCurrent = rhs.mCurrent;
            mEnd = rhs.mEnd;
            return *this;
        }
        /** Returns a pointer to the next value element in the collection, without
        advancing to the next afterwards. */
        typename T::mapped_type* peekNextValuePtr( void )
        {
            return &( mCurrent->second );
        }
        /** Moves the iterator on one element. */
        void moveNext( void )
        {
            ++mCurrent;
        }



    };
    /** Wraps iteration over a const vector.
    @remarks
    This class is here just to allow clients to iterate over an internal
    vector of a class without having to have access to the vector itself
    (typically to iterate you need both the iterator and the end() iterator
    to test for the end condition, which is messy).
    No updates are allowed through this interface, it is purely for
    iterating and reading.
    @par
    Note that like STL iterators, these iterators are only valid whilst no
    updates are made to the underlying collection. You should not attempt to
    use this iterator if a change is made to the collection. In fact, treat this
    iterator as a transient object, do NOT store it and try to use it repeatedly.
    */
    template <class T>
    class ConstVectorIterator
    {
    private:
        mutable typename T::const_iterator mCurrent;
        typename T::const_iterator mEnd;
        /// Private constructor since only the parameterised constructor should be used
        ConstVectorIterator() {};
    public:
        typedef typename T::value_type ValueType;

        /** Constructor.
        @remarks
        Provide a start and end iterator to initialise.
        */
        ConstVectorIterator( typename T::const_iterator start, typename T::const_iterator end )
            : mCurrent( start ), mEnd( end )
        {
        }

        /** Returns true if there are more items in the collection. */
        bool hasMoreElements( void ) const
        {
            return mCurrent != mEnd;
        }

        /** Returns the next element in the collection, and advances to the next. */
        typename T::value_type getNext( void )
        {
            return *mCurrent++;
        }
        /** Returns the next element in the collection, without advancing to the next. */
        typename T::value_type peekNext( void ) const
        {
            return *mCurrent;
        }
        /** Returns a pointer to the next element in the collection, without advancing to the next afterwards. */
        typename T::const_pointer peekNextPtr( void ) const
        {
            return &( *mCurrent );
        }
        /** Moves the iterator on one element. */
        void moveNext( void ) const
        {
            ++mCurrent;
        }



    };

    /** Wraps iteration over a const map.
    @remarks
    This class is here just to allow clients to iterate over an internal
    map of a class without having to have access to the map itself
    (typically to iterate you need both the iterator and the end() iterator
    to test for the end condition, which is messy).
    No updates are allowed through this interface, it is purely for
    iterating and reading.
    @par
    Note that like STL iterators, these iterators are only valid whilst no
    updates are made to the underlying collection. You should not attempt to
    use this iterator if a change is made to the collection. In fact, treat this
    iterator as a transient object, do NOT store it and try to use it repeatedly.
    */
    template <class T>
    class ConstMapIterator
    {
    private:
        mutable typename T::const_iterator mCurrent;
        typename T::const_iterator mEnd;
        /// Private constructor since only the parameterised constructor should be used
        ConstMapIterator() {};
    public:
        typedef typename T::mapped_type MappedType;
        typedef typename T::key_type KeyType;

        /** Constructor.
        @remarks
        Provide a start and end iterator to initialise.
        */
        ConstMapIterator( typename T::const_iterator start, typename T::const_iterator end )
            : mCurrent( start ), mEnd( end )
        {
        }

        /** Returns true if there are more items in the collection. */
        bool hasMoreElements( void ) const
        {
            return mCurrent != mEnd;
        }

        /** Returns the next value element in the collection, and advances to the next. */
        typename T::mapped_type getNext( void )
        {
            return ( mCurrent++ )->second;
        }
        /** Returns the next value element in the collection, without advancing to the next. */
        typename T::mapped_type peekNextValue( void ) const
        {
            return mCurrent->second;
        }
        /** Returns the next key element in the collection, without advancing to the next. */
        typename T::key_type peekNextKey( void ) const
        {
            return mCurrent->first;
        }
        /** Required to overcome intermittent bug */
        MapIterator<T> & operator=( MapIterator<T> &rhs )
        {
            mCurrent = rhs.mCurrent;
            mEnd = rhs.mEnd;
            return *this;
        }
        /** Returns a pointer to the next value element in the collection, without
        advancing to the next afterwards. */
        typename T::mapped_type* peekNextValuePtr( void ) const
        {
            return &( mCurrent->second );
        }
        /** Moves the iterator on one element. */
        void moveNext( void ) const
        {
            ++mCurrent;
        }
    };



    // vectors.
    H_DEF_VECTOR( osl::s8,  S8Vector );
    H_DEF_VECTOR( osl::u8,  U8Vector );
    H_DEF_VECTOR( osl::s16, S16Vector );
    H_DEF_VECTOR( osl::u16, U16Vector );
    H_DEF_VECTOR( osl::s32, S32Vector );
    H_DEF_VECTOR( osl::u32, U32Vector );
    H_DEF_VECTOR( osl::s64, S64Vector );
    H_DEF_VECTOR( osl::u64, U64Vector );
	H_DEF_VECTOR( osl::f32, F32Vector );
	H_DEF_VECTOR( osl::f64, F64Vector );

    H_DEF_VECTOR( void*, VoidVector );


    // sets
    H_DEF_SET( osl::s8,  S8Set );
    H_DEF_SET( osl::u8,  U8Set );
    H_DEF_SET( osl::s16, S16Set );
    H_DEF_SET( osl::u16, U16Set );
    H_DEF_SET( osl::s32, S32Set );
    H_DEF_SET( osl::u32, U32Set );
    H_DEF_SET( osl::s64, S64Set );
    H_DEF_SET( osl::u64, U64Set );
	H_DEF_SET( osl::f32, F32Set );
	H_DEF_SET( osl::f64, F64Set );

    H_DEF_SET( void*, VoidSet );

};//namespace osl;


#include "osl/include/list_impl_linux.h"
#include "osl/include/stl_ext.h"



template<class _Ty,class _Alloc>
inline void swap( osl::Vector<_Ty, _Alloc>& _Left, osl::Vector<_Ty, _Alloc>& _Right)
{	// swap _Left and _Right vectors
    _Left.swap(_Right);
}

template<class _Ty,class _Alloc>
inline void swap( osl::List<_Ty, _Alloc>& _Left, osl::List<_Ty, _Alloc>& _Right)
{	// swap _Left and _Right vectors
    _Left.swap(_Right);
}

template<class _Ty,class _Alloc,class _ContainerName,class _Pr>
inline void swap( osl::Map<_Ty, _Alloc,_ContainerName,_Pr>& _Left, osl::Map<_Ty, _Alloc,_ContainerName,_Pr>& _Right)
{	// swap _Left and _Right vectors
    _Left.swap(_Right);
}

template < class _Kty , typename _ContainerName , class _Pr >
inline void swap( osl::Set<_Kty, _ContainerName, _Pr>& _Left , osl::Set<_Kty, _ContainerName, _Pr>& _Right )
{
    _Left.swap( _Right );
};

template<class _Ty,class _Alloc,class _ContainerName,class _Pr>
inline void swap( osl::MultiMap<_Ty, _Alloc,_ContainerName,_Pr>& _Left, osl::MultiMap<_Ty, _Alloc,_ContainerName,_Pr>& _Right)
{	// swap _Left and _Right vectors
    _Left.swap(_Right);
}
template<class _Ty,class _Alloc,class _ContainerName,class _Pr>
inline void swap( osl::HashMap<_Ty, _Alloc,_ContainerName,_Pr>& _Left, osl::HashMap<_Ty, _Alloc,_ContainerName,_Pr>& _Right)
{	// swap _Left and _Right vectors
    _Left.swap(_Right);
}


#endif//endoffile

