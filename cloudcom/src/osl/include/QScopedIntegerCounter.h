#ifndef _H_OSLIB_SCOPEDINTEGERCOUNTER_
#define _H_OSLIB_SCOPEDINTEGERCOUNTER_


namespace osl
{

    //! Scoped u32 counter.
    template<typename T>
    struct ScopedIntegerCounter
    {
        explicit ScopedIntegerCounter( T& nInt )
            : m_nCounter( nInt )
        {
            ++m_nCounter;
        }

        ~ScopedIntegerCounter()
        {
            --m_nCounter;
        }

        T&  m_nCounter;
    private:
        ScopedIntegerCounter( const ScopedIntegerCounter& );
        ScopedIntegerCounter&operator=( const ScopedIntegerCounter& );
    };




    //! Scoped u32 counter.
    //! The type of <code>T<code> must be volatile
    template<typename T>
    struct ScopedIntegerCounterThreadsafe
    {
        explicit ScopedIntegerCounterThreadsafe( T& nInt )
            : m_nCounter( nInt )
        {
            InterlockedInc32( &m_nCounter );
        }

        ~ScopedIntegerCounterThreadsafe()
        {
            InterlockedDec32( &m_nCounter );
        }

        T&  m_nCounter;
    private:
        ScopedIntegerCounterThreadsafe( const ScopedIntegerCounterThreadsafe& );
        ScopedIntegerCounterThreadsafe&operator=( const ScopedIntegerCounterThreadsafe& );
    };

};

#endif//endoffile.
