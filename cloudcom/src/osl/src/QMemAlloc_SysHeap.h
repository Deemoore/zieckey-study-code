
#pragma once

#include "osl/include/QMemAlloc.h"

namespace osl
{
    static bool c_bMemAllocInitialized = false;

#ifdef H_OS_WINDOWS
    static HANDLE   s_hMemHeap = NULL;
#endif
    //----------------------------------------------
    void MemAlloc::initialize()
    {
        if ( c_bMemAllocInitialized )
        {
            return;
        }

        c_bMemAllocInitialized = true;

#ifdef H_OS_WINDOWS

        ::SetEnvironmentVariableA( "_NO_DEBUG_HEAP", "1" );

        assert( s_hMemHeap == NULL );
        s_hMemHeap = ::HeapCreate( HEAP_CREATE_ENABLE_EXECUTE, 0, 0 );

        if( !s_hMemHeap )
        {
            uninitialize();
            //
            assert( false && "Failed to create heap" );
            return;
        }


        ULONG  HeapFragValue = 2;

        if( !HeapSetInformation( s_hMemHeap,
            HeapCompatibilityInformation,
            &HeapFragValue,
            sizeof(HeapFragValue))
            )
        {
            ::OutputDebugStringA( "Failed to use low-fragment flag on created heap. Add environment of _NO_DEBUG_HEAP=1 to enable system memory pool.");
        }
#endif

        return;
    }

    //----------------------------------------------
    void MemAlloc::uninitialize()
    {
        if ( !c_bMemAllocInitialized )
        {
            return;
        }

#ifdef H_OS_WINDOWS

        if( s_hMemHeap )
        {
            ::HeapDestroy( s_hMemHeap );
            s_hMemHeap = NULL;
        }
#endif

    }
    //----------------------------------------------
    void* MemAlloc::alloc( size_t nBytes )
    {
        //#ifdef H_OS_WINDOWS
        //		return ::HeapAlloc( s_hMemHeap, 0, nBytes );
        //#else
        return ::malloc( nBytes );
        //#endif

    }
    //----------------------------------------------------------
    void* MemAlloc::alloc( size_t nBytes , const char*pClassName )
    {
        return MemAlloc::alloc( nBytes );
    }
    //----------------------------------------------------------
    void* MemAlloc::alloc( size_t nBytes , const char*pClassName, const char* pFileName, int nLine )
    {
        return MemAlloc::alloc( nBytes );
    }
    //----------------------------------------------------------
    void MemAlloc::free( void* ptr )
    {
        //#ifdef H_OS_WINDOWS
        //		::HeapFree( s_hMemHeap, 0, ptr );
        //#else
        return ::free( ptr );
        //#endif
    }
    //----------------------------------------------------------
    void* MemAlloc::allocAligned( size_t nBytes, osl::u32 nAlign  )
    {
        return NULL;
    }
    //----------------------------------------------------------
    void* MemAlloc::allocAligned( size_t nBytes , const char*pClassName, osl::u32 nAlign )
    {
        return NULL;
    }
    //----------------------------------------------------------
    void* MemAlloc::allocAligned( size_t nBytes , const char*pClassName, const char* pFileName, int nLine, osl::u32 nAlign )
    {
        return NULL;
    }
    //----------------------------------------------------------
    void MemAlloc::freeAligned( void* ptr )
    {
    }
    //----------------------------------------------
    u32 MemAlloc::getNumInstancesByClassName( const char* pClassName, osl::u32 nClassSize )
    {
        return 0;
    }

    //----------------------------------------------
    //
    u32 MemAlloc::getNumInstancesByClassName( const char* pClassName )
    {
        return 0;
    }
    //------------------------------------------------------
    void* MemAlloc::findObjectByClassName( const char* szClassName, osl::u32 nClassSize, osl::u32 nIndex )
    {
        return 0;
    }
    //----------------------------------------------
    MemAlloc::Stats* MemAlloc::getStats()
    {
        return NULL;
    }
    //----------------------------------------------
    void MemAlloc::dumpStats( std::ostream& file, bool bOutputEachUnit )
    {
        file << "Statics not supported in system heap mode.";
    }
    //----------------------------------------------
    void MemAlloc::dumpStats( std::ostream& file, osl::u32 nMinSize, osl::u32 nMaxSize, bool bOutputEachUnit )
    {
        file << "Statics not supported in system heap mode.";
    }
    //------------------------------------------------------
    void MemAlloc::findObjectReferences( ObjectNode**& pReferences, PointerInt val )
    {
    }
    //------------------------------------------------------
    void MemAlloc::freeObjectReferenceList( ObjectNode** pReferences )
    {
    }
    //------------------------------------------------------
    void MemAlloc::findObjectReferences( ObjectNode**& pReferences, const char* szClassName, osl::u32 nClassSize, osl::u32 nIndex )
    {
    }
    //------------------------------------------------------
    bool MemAlloc::findObjectByAddr( MemAlloc::ObjectNode& obj, PointerInt nAddr )
    {
        return false;
    }

};

