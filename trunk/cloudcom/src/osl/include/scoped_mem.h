#ifndef _SCOPED_MEMORY_H_
#define _SCOPED_MEMORY_H_

#include "osl/include/config.h"
#include "osl/include/malloc_micro.h"
#include "osl/include/inner_pre.h"

namespace osl
{
    //! Scoped memory block. When lifetime out, memory in the object will be freed.
    //! \warning The object SHOULD ONLY be used on stack.
    struct _EXPORT_OSLIB ScopedMem
    {
        void*   pRep;
        ScopedMem( const ScopedMem& r );    //!< Îð¼ÓÊµÏÖ
    public:

        ScopedMem(): pRep( 0 ) {}

        ScopedMem( void* _rep )
            :pRep( _rep )
        {
        }

        //! Construct a sized memory.
        ScopedMem( osl::u32 nSize )
        {
            pRep = H_ALLOC_NAME_FILE( nSize, "ScopedMem", __FILE__, __LINE__ );
        }

        ~ScopedMem()
        {
            if ( pRep )
            {
                H_FREE(pRep);
            }
        }

        inline ScopedMem& operator=( void*pBuf )
        {
            if ( pRep )
            {
                H_FREE(pRep);
            }

            pRep = pBuf;
            return *this;
        }

        operator osl::u8*()const
        {
            return static_cast<osl::u8*>(pRep);
        }
        osl::u8* get() const
        {
            return static_cast<osl::u8*>(pRep);
        }
        osl::u8* getPointer() const
        {
            return static_cast<osl::u8*>(pRep);
        }

        template<class T>
        T* getPointer()const
        {
            return static_cast<T*>(pRep);
        }

        inline bool isNull( void ) const
        {
            return pRep == 0;
        }

        //! Allocate sized memory.
        void alloc( osl::u32 nSize );
    };


    //////////////////////////////////////////////////////////////////////////
    //                           ScopedMem
    //////////////////////////////////////////////////////////////////////////
    //----------------------------------------------
    inline void ScopedMem::alloc( osl::u32 nSize )
    {
        if ( pRep )
        {
            H_FREE( pRep );
        }

        H_ALLOC_NAME(nSize, "ScopedMem" );
    }

}

#endif



