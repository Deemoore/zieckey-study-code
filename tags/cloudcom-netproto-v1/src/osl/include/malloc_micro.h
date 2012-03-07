#ifndef _OSLIB_MALLOC_MIRCRO_H_
#define _OSLIB_MALLOC_MIRCRO_H_

#include "osl/include/config.h"

#if H_PROVIDE_MEMORY_POOL
#include "osl/include/mem_alloc.h"
#else // #if H_PROVIDE_MEMORY_POOL

#ifdef H_DEBUG_MODE
#	define H_NEW                         new( __FILE__ , __LINE__ )
#else
#	define H_NEW                         new
#endif

#ifdef H_ALLOC
#	undef H_ALLOC
#endif

#ifdef H_ALLOC_NAME
#	undef H_ALLOC_NAME
#endif

#define H_ALLOC( size )               ::malloc( (size) )
#define H_ALLOC_NAME( size, name )    ::malloc( (size) )
#define H_ALLOC_NAME_FILE( size, name, file_name, line_no )    ::malloc( (size) )

#ifdef H_FREE
#	undef H_FREE
#endif

#define H_SAFE_FREE( p )       if(p){ ::free( (p) ); p = 0;}
#define H_FREE( p )            H_SAFE_FREE(p)


#define H_ALLOCRAW_OPERATORS( typename )								  	\
    public:																    \
    void* operator new( size_t nSize ) {								  	\
        return H_ALLOC_NAME( nSize, #typename );					        \
    }																	 	\
    void  operator delete( void* ptr ) {								  	\
        if(ptr) H_FREE( ptr );							 	                \
    }																	 	\
    void* operator new( size_t nSize ,const char*pFile,int nLine) {	   		\
        return H_ALLOC_NAME_FILE( nSize, #typename , pFile , nLine );	    \
    }																		\
    void  operator delete( void* ptr ,const char*,int ) {					\
        if(ptr) H_FREE( ptr );								                \
    }																		\
    void* operator new(size_t, void* location) {		 					\
        return location;								 					\
    }																		\
    void operator delete(void* , void*) {}			   						\
    void* operator new[]( size_t nSize ) {			   						\
        return H_ALLOC( nSize );		  						            \
    }																		\
    void  operator delete[]( void* ptr ) {			   						\
        H_SAFE_FREE( ptr );								                    \
    }
    
#endif //endif #if H_PROVIDE_MEMORY_POOL


/**
* Alignment macros
*/

/* H_ALIGN() is only to be used to align on a power of 2 boundary */
#define H_ALIGN(size, boundary) (((size) + ((boundary) - 1)) & ~((boundary) - 1))

/** Default alignment */
#define H_ALIGN_DEFAULT(size) H_ALIGN(size, 8)


#endif //endif #ifndef _MALLOC_MIRCRO_H_

