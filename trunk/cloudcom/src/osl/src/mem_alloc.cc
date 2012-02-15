#include "osl/include/inner_pre.h"


//! Include configuration memory pool.
#if (defined( H_MEMORY_POOL ))
//如果使用池，启用系统内存， 可以关闭它
//#	define H_USE_SYS_MEM
#	include "mem_alloc_pool.h"
#else
#	include "mem_alloc_sys_heap.h"
#endif

namespace osl
{

    //////////////////////////////////////////////////////////////////////////
    //                           ScopedMem
    //////////////////////////////////////////////////////////////////////////
    ScopedMem::ScopedMem( osl::u32 nSize )
    {
#ifdef H_MEMORY_DEBUG
        pRep = ( osl::u8* )osl::MemAlloc::alloc( nSize, "ScopedMem", __FILE__, __LINE__ );
#else
        pRep = ( osl::u8* )osl::MemAlloc::alloc( nSize );
#endif
    }
    //----------------------------------------------
    void ScopedMem::alloc( osl::u32 nSize )
    {
        if ( pRep )
        {
            osl::MemAlloc::free( pRep );
        }

#ifdef H_MEMORY_DEBUG
        pRep = ( osl::u8* )osl::MemAlloc::alloc( nSize, "ScopedMem" );
#else
        pRep = ( osl::u8* )osl::MemAlloc::alloc( nSize );
#endif
    }

};//namespace
