

#ifndef QOSLIB_STLALLOCATOR_
#define QOSLIB_STLALLOCATOR_

#include "osl/include/mem_alloc.h"

namespace osl
{


    //using namespace std;
    struct STLContainerName
    {
        static const char* NAME()
        {
            return "unknown_stl";
        }
    };

    //! The allocator conforms to Standard STL allocator.It use redesigned
    //! memory management mechanism.
    template < class _Ty, typename _ContainerName = STLContainerName >
    class HSTLAllocator
        : public std::allocator<_Ty>
    {
    public:
        typedef std::allocator<_Ty> _Mybase;
        typedef typename _Mybase::value_type value_type;


        typedef value_type* pointer;
        typedef value_type& reference;
        typedef const value_type* const_pointer;
        typedef const value_type& const_reference;

        typedef size_t size_type;
        //typedef uint32 size_type;
        typedef ptrdiff_t difference_type;

        template<class _Other>
        struct rebind
        {
            // convert an HSTLAllocator<_Ty> to an HSTLAllocator <_Other>
            typedef HSTLAllocator<_Other, _ContainerName> other;
        };

        pointer address( reference _Val ) const
        {
            // return address of mutable _Val
            return ( &_Val );
        }

        const_pointer address( const_reference _Val ) const
        {
            // return address of nonmutable _Val
            return ( &_Val );
        }

        HSTLAllocator()
            : _Mybase()
        {
            // construct default HSTLAllocator (do nothing)
        }

        HSTLAllocator( const HSTLAllocator<_Ty, _ContainerName>& )
            : _Mybase()
        {
            // construct by copying (do nothing)
        }

        template<class _Other, typename _OthContainerName>
        HSTLAllocator( const HSTLAllocator<_Other, _OthContainerName>& )
        {
            // construct from a related HSTLAllocator (do nothing)
        }

        template<class _Other, typename _OthContainerName>
        HSTLAllocator<_Ty, _ContainerName>& operator=( const HSTLAllocator<_Other, _OthContainerName>& )
        {
            // assign from a related HSTLAllocator (do nothing)
            return ( *this );
        }

        void deallocate( pointer _Ptr, size_type )
        {
#ifdef H_MEMORY_POOL        
            // deallocate object at _Ptr, ignore size
            MemAlloc::free( _Ptr );
#else
            _Mybase::deallocate( _Ptr, 0 );
#endif // #ifdef H_MEMORY_POOL
        }

        pointer allocate( size_type _Count )
        {
#ifdef H_MEMORY_POOL        
            // allocate array of _Count elements
            //return (_Allocate(_Count, (pointer)0));
            //return (pointer)malloc( _Count * sizeof(value_type) );
            return ( pointer )H_ALLOC_NAME( _Count * sizeof( value_type ), _ContainerName::NAME() );
#else
            return _Mybase::allocate( _Count );
#endif // #ifdef H_MEMORY_POOL
        }

        pointer allocate( size_type _Count, const void * )
        {
            // allocate array of _Count elements, ignore hint
            return ( allocate( _Count ) );
        }

        void construct( pointer _Ptr, const _Ty& _Val )
        {
            // construct object at _Ptr with value _Val
            std::_Construct( _Ptr, _Val );
        }

        void destroy( pointer _Ptr )
        {
            // destroy object at _Ptr
            std::_Destroy( _Ptr );
        }

        size_t max_size() const
        {
            // estimate maximum array size
            size_t _Count = ( size_t )( -1 ) / sizeof ( _Ty );
            return ( 0 < _Count ? _Count : 1 );
        }
    };

    // HSTLAllocator TEMPLATE OPERATORS
    template < class _Ty, typename _ContainerName,
             class _Other, typename _OthContainerName > inline
    bool operator==( const HSTLAllocator<_Ty, _ContainerName>&, const HSTLAllocator<_Other, _OthContainerName>& )
    {
        // test for HSTLAllocator equality (always true)
        return ( true );
    }

    template < class _Ty, typename _ContainerName,
             class _Other, typename _OthContainerName > inline
    bool operator!=( const HSTLAllocator<_Ty, _ContainerName>&, const HSTLAllocator<_Other, _OthContainerName>& )
    {
        // test for HSTLAllocator inequality (always false)
        return ( false );
    }



};// namespace

#endif//endoffile
