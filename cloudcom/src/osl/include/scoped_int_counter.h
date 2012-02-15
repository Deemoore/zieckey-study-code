#ifndef _H_OSLIB_SCOPEDINTEGERCOUNTER_
#define _H_OSLIB_SCOPEDINTEGERCOUNTER_

#include "osl/include/atomic_op.h"

namespace osl
{

    //! Scoped u32 counter.
    template<typename T>
    struct ScopedIntCounter
    {
        explicit ScopedIntCounter( T& nInt )
            : m_nCounter( nInt )
        {
            ++m_nCounter;
        }

        ~ScopedIntCounter()
        {
            --m_nCounter;
        }

        T&  m_nCounter;
    private:
        ScopedIntCounter( const ScopedIntCounter& );
        ScopedIntCounter&operator=( const ScopedIntCounter& );
    };




    //! Scoped u32 counter.
    //! The type of <code>T<code> must be volatile
    template<typename T>
    struct ScopedIntCounterThreadsafe
    {
        explicit ScopedIntCounterThreadsafe( T& nInt )
            : m_nCounter( nInt )
        {
            InterlockedInc32( &m_nCounter );
        }

        ~ScopedIntCounterThreadsafe()
        {
            InterlockedDec32( &m_nCounter );
        }

        T&  m_nCounter;
    private:
        ScopedIntCounterThreadsafe( const ScopedIntCounterThreadsafe& );
        ScopedIntCounterThreadsafe&operator=( const ScopedIntCounterThreadsafe& );
    };

};

#endif//endoffile.
