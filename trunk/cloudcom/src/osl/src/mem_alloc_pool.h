
#pragma once

#include "osl/include/mem_alloc.h"
#include "osl/include/string_ext.h"
#include "osl/include/process_ext.h"
#include "osl/include/lock.h"

#include "mem_alloc_pool.inl.h"
#include <fstream>

namespace osl
{
    // for debug purpose to kb, mb
    std::string outputMemSize( osl::u32 nSize )
    {

        std::ostringstream strTip;

        if( nSize < ( 1024 ) )
        {
            strTip << nSize << "B";
        }
        else if( nSize < ( 1048576 ) )
        {
            strTip << (double)( (double)nSize / 1024.0f ) << "KB";

        }
        else
        {
            strTip << (double)( (double)nSize / 1048576.0f ) << "MB";
        }

        return strTip.str().c_str();
    }


    //LargeMemManager* s_pLargeMemManager = NULL;

    static MemNodeList*     s_SmallMemList[c_nSmallMemListArraySize];
    static MemNodeList*     s_MiddleMemList[c_nMiddleMemListArraySize];
#ifdef H_USE_LARGE_MEM_LIST
    static LargeMemList*       s_LargeMemList[c_nLargeMemListArraySize];
#endif
    static SysHeapMemList*                   s_SysHeapMemList = NULL; 

    static bool c_bMemAllocInitialized = false;

    //----------------------------------------------
    void MemAlloc::initialize()
    {
        if ( c_bMemAllocInitialized )
        {
            return;
        }

        c_bMemAllocInitialized = true;

#ifdef H_MEMORY_STATS
        // clear stats
        memset( &s_MemStats, 0, sizeof( Stats ) );
        s_MemStats.nMemListSize = c_nSmallMemListArraySize + c_nMiddleMemListArraySize
#	ifdef H_USE_LARGE_MEM_LIST
            + c_nLargeMemListArraySize
#	endif
            ;

        s_MemStats.pMemListStatsArray = new Stats::MemListStats[ s_MemStats.nMemListSize ];

#ifdef H_MEMORY_DEBUG
        s_MemStats.pMemNodeCountArray = new Stats::MemCount[c_nMemBlockIncSize];

        for ( u32 i = 0; i < c_nMemBlockIncSize; ++i )
        {
            s_MemStats.pMemNodeCountArray[i].nMemSize = i * 8;
            s_MemStats.pMemNodeCountArray[i].nUsedCount = 0;
        }
#endif

        memset( s_MemStats.pMemListStatsArray, 0, sizeof( Stats::MemListStats ) * s_MemStats.nMemListSize  );
        memset( s_SmallMemList, 0, sizeof( s_SmallMemList ) );
#	ifdef H_USE_LARGE_MEM_LIST
        memset( s_LargeMemList, 0, sizeof( s_LargeMemList ) );
#	endif
        s_SysHeapMemList = NULL;
#endif

        // small list
        for ( size_t i = 0; i < c_nSmallMemListArraySize; ++i )
        {
            s_SmallMemList[i] = new MemNodeList(
                ( i + 1 ) * c_nSmallMemIncStepSize, c_nMemBlockIncSize, i  );
        }

        // large list
        for ( size_t i = 0; i < c_nMiddleMemListArraySize; ++i )
        {
            size_t nTimes = i / 2;

            size_t nNodeSize = 1 << ( nTimes + c_nMinMiddleMemListShift );

            if ( i % 2 == 1 )
            {
                nNodeSize += ( nNodeSize >> 1 );
            }

            s_MiddleMemList[i] = new MemNodeList(
                nNodeSize, c_nMemBlockIncSize, c_nSmallMemListArraySize + i  );
        }


        // huge manger.
        s_pLargeMemManager = new LargeMemManager();
        if( !s_pLargeMemManager->initialize() )
        {
            uninitialize();
            return;
        }

#ifdef H_USE_LARGE_MEM_LIST
        /// huge list
        for ( size_t i = 0; i < c_nLargeMemListArraySize; ++i )
        {
            size_t nNodeSize = ( i + 1 ) * c_nLargeMemIncStepSize + c_nMinLargeMemListSize;

            s_LargeMemList[i] = new LargeMemList(
                nNodeSize, c_nSmallMemListArraySize + c_nMiddleMemListArraySize + i  );
        }
#endif

        // sys heap
        s_SysHeapMemList = new SysHeapMemList();
    }

    //----------------------------------------------
    void MemAlloc::uninitialize()
    {
        if ( !c_bMemAllocInitialized )
        {
            return;
        }

        // small list
        for ( size_t i = 0; i < c_nSmallMemListArraySize; ++i )
        {
            if( s_SmallMemList[i] )
            {
                delete s_SmallMemList[i];
                s_SmallMemList[i] = NULL;
            }
        }

        // large list
        for ( size_t i = 0; i < c_nMiddleMemListArraySize; ++i )
        {
            if( s_MiddleMemList[i] )
            {
                delete s_MiddleMemList[i];
                s_MiddleMemList[i] = NULL;
            }
        }

#ifdef H_USE_LARGE_MEM_LIST
        // huge mem list.
        for ( size_t i = 0; i < c_nLargeMemListArraySize; ++i )
        {
            if( s_LargeMemList[i] )
            {
                delete s_LargeMemList[i];
                s_LargeMemList[i] = NULL;
            }
        }
#endif

        // sys heap
        if( s_SysHeapMemList )
        {
            delete s_SysHeapMemList;
            s_SysHeapMemList = NULL;
        }


#ifdef H_MEMORY_STATS

#ifdef H_MEMORY_DEBUG

        if( s_MemStats.pMemNodeCountArray )
        {
            delete[] s_MemStats.pMemNodeCountArray;
        }


#endif

        if( s_MemStats.pMemListStatsArray )
        {
            delete[] s_MemStats.pMemListStatsArray;
        }
#endif
    }

    //----------------------------------------------
    /** Get large memory list index, 按照2n方增长，2级之间插入一个中间大小的节点。
    * 	*  @param nBytes memory size
    * 		*  @return memory list index in s_MiddleMemList[];
    * 			*/
    size_t getMiddleMemListIndex( size_t nBytes )
    {
        size_t iTimeBase = c_nMinMiddleMemListShift;

        register size_t iTime = 0;

        while ( ( ( size_t )1 << ( iTime + iTimeBase ) ) < nBytes )
        {
            ++iTime;
        }

        iTime = iTime << 1;

        if ( iTime > 0 &&
            ( s_MiddleMemList[ iTime - 1 ]->getNodeSize() >= nBytes )
            )
        {
            return iTime - 1;
        }

        return iTime;
    }
    //----------------------------------------------
    void* MemAlloc::alloc( size_t nBytes )
    {
#ifdef H_USE_SYS_MEM
        return ::malloc( nBytes );
#else
        //return malloc( nBytes );
        assert( c_bMemAllocInitialized );

#	ifdef H_MEMORY_DEBUG
        size_t nsize = H_ALIGN( nBytes, 8 );

        if ( nsize / 8 < c_nMemBlockIncSize )
        {
            s_MemStats.pMemNodeCountArray[nsize/8].nUsedCount++;
        }

#	endif

        //!=================================
        // Lock has been moved to node list.
        //=================================

        u8* pRet = NULL;

        // check valid size.
        if ( nBytes == 0 || nBytes >= ( size_t )( -1 ) )
        {
            return pRet;
        }

#	ifdef H_MEMORY_DEBUG
        // get actual node size.
        nBytes += sizeof( MemNode ) + sizeof( MemPad );
#	else
        nBytes += sizeof( MemNode );
#	endif

        MemNode* pMemNode = NULL;

        // small node
        if ( nBytes <= c_nMinThresholdMemUnit )
        {
            size_t HListIndex = ( ( size_t )nBytes - 1 ) / c_nSmallMemIncStepSize;
            // adjust location of returned raw memory.
            pMemNode = s_SmallMemList[HListIndex]->getMemNode();

        }
        else if ( nBytes <= c_nMaxMiddleMemList )
        {
            size_t HListIndex = getMiddleMemListIndex( ( size_t )nBytes );
            pMemNode = s_MiddleMemList[HListIndex]->getMemNode();
        }
#	ifdef H_USE_LARGE_MEM_LIST
        else if ( nBytes <= c_nMaxLargeMemListSize )
        {
            s_pLargeMemManager->lock();

            size_t HListIndex = ( ( size_t )nBytes - 1 - c_nMinLargeMemListSize) / c_nLargeMemIncStepSize;
            pMemNode = s_LargeMemList[HListIndex]->getMemNode();

            s_pLargeMemManager->unlock();
        }
#	endif
        else // beyond management.
        {
            s_pLargeMemManager->lock();

            pMemNode = s_SysHeapMemList->getMemNode( nBytes );

            s_pLargeMemManager->unlock();
        }

        // check node
        if ( !pMemNode )
        {
            // no memory available.
            return NULL;
        }


        pRet = ( ( u8* )pMemNode ) + sizeof( MemNode );

#	ifdef H_MEMORY_STATS

        if ( pMemNode )
        {
            InterlockedXAdd( &s_MemStats.nTotalBusySize, pMemNode->nSize );
        }

#	endif

#	ifdef H_MEMORY_DEBUG

        if( pMemNode )
        {
            //assert( !pClassName || strlen( pClassName ) );
            pMemNode->pClassName = "unknown";
            pMemNode->pFileName = "no file";
            pMemNode->nLine = 0;
        }

#		ifdef H_ARCH_32

        bool bStatMem = false;
        // 		{
        // 			if( s_MemStats.nTotalAllocatedSize > ( 400 * 1 << 20 ) )
        // 			{
        // 				if( s_MemStats.nTotalAllocatedSize > ( 800 * 1 << 20 ) )
        // 				{
        // 					bStatMem = true;
        // 				}
        // 				else
        // 				{
        // 					osl::u32 nTotalMB = 0; osl::u32 nCurAvilMB = 0;
        // 					OS::getSystemMemoryMB( &nTotalMB, &nCurAvilMB );
        // 
        // 					if( nCurAvilMB < 50 )
        // 					{
        // 						bStatMem = true;
        // 					}
        // 				}
        // 			}
        // 		}

        if( bStatMem )
        {
            std::ofstream strTip;
            strTip.open( "memstat.txt", std::ios_base::ate );

            dumpStats( strTip, false );

            strTip.flush();
            assert( false && "memory used out" );
        }
#		endif

#	endif
        return pRet;

#endif

    }
    //----------------------------------------------------------
    void* MemAlloc::alloc( size_t nBytes , const char*pClassName )
    {
#ifdef H_USE_SYS_MEM
        return ::malloc( nBytes );
#else

#	ifdef H_MEMORY_DEBUG
        void* pMem = MemAlloc::alloc( nBytes );

        if( pMem )
        {
            MemNode* pMemNode = ( MemNode* )( ( osl::u8* )pMem - sizeof( MemNode ) );

            //assert( !pClassName || strlen( pClassName ) );
            pMemNode->pClassName = ( pClassName ) ? pClassName : "unknown";
        }

        return pMem;
#	else
        return MemAlloc::alloc( nBytes );
#	endif

#endif //H_USE_SYS_MEM
    }
    void* MemAlloc::alloc( size_t nBytes , const char*pClassName, const char* pFileName, int nLine )
    {
#ifdef H_USE_SYS_MEM
        return ::malloc( nBytes );
#else

#	ifdef H_MEMORY_DEBUG
        void* pMem = MemAlloc::alloc( nBytes );

        if( pMem )
        {
            MemNode* pMemNode = ( MemNode* )( ( osl::u8* )pMem - sizeof( MemNode ) );

            //assert( !pClassName || strlen( pClassName ) );
            pMemNode->pClassName = ( pClassName ) ? pClassName : "unknown";
            pMemNode->pFileName = ( pFileName ) ? pFileName : "no file";
            pMemNode->nLine = nLine;
        }

        return pMem;
#	else
        return MemAlloc::alloc( nBytes );
#	endif

#endif //!H_USE_SYS_MEM
    }

    void MemAlloc::free( void* ptr )
    {
#ifdef H_USE_SYS_MEM
        return ::free( ptr );
#else

        assert( c_bMemAllocInitialized );

        if ( ptr == NULL )
        {
            return;
        }

        MemNode* pMemNode = ( MemNode* ) ( ( u8* )ptr - sizeof( MemNode ) );

#	ifdef H_MEMORY_STATS
        InterlockedXAdd( &s_MemStats.nTotalBusySize, -( AtomicInt )pMemNode->nSize );
#	endif


#	ifdef H_MEMORY_DEBUG

        MemPad* pMemPad = ( MemPad* )( ( ( char* )pMemNode ) + pMemNode->nSize - sizeof( MemPad ) );

        if ( pMemPad->nPadWord != c_nPadWordUsed )
        {
            assert( false && "Wrong memory operation" );
        }

        // clear free word.
        pMemPad->nPadWord = c_nPadWordFree;
#	endif

        //if( pMemNode->nSize <= c_nSizeMemHeader )
        //{
        //	::free( (void*)pMemNode );
        //
        //}else
        if ( pMemNode->nSize <= c_nMinThresholdMemUnit )
        {
#	ifdef H_MEMORY_DEBUG

            if ( pMemPad->nBlockSlot != c_nSmallMemBlockSlotID )
            {
                assert( false && "Wrong memory operation" );
            }

#	endif
            size_t HListIndex = ( ( size_t )pMemNode->nSize - 1 ) / c_nSmallMemIncStepSize;
            s_SmallMemList[HListIndex]->recycleMemNode( pMemNode );

        }
        else if ( pMemNode->nSize <= c_nMaxMiddleMemList )
        {
            size_t HListIndex = getMiddleMemListIndex( ( size_t )pMemNode->nSize );
            s_MiddleMemList[HListIndex]->recycleMemNode( pMemNode );

        }
#	ifdef H_USE_LARGE_MEM_LIST
        else if ( pMemNode->nSize <= c_nMaxLargeMemListSize )
        {
            // 临时这样加的。
            s_pLargeMemManager->lock();

            size_t HListIndex = ( ( size_t )pMemNode->nSize - 1 - c_nMinLargeMemListSize) / c_nLargeMemIncStepSize;
            s_LargeMemList[HListIndex]->recycleMemNode( pMemNode );

            s_pLargeMemManager->unlock();
        }
#	endif
        else
        {
            // 临时这样加的。
            s_pLargeMemManager->lock();

            s_SysHeapMemList->recycleMemNode( pMemNode );

            s_pLargeMemManager->unlock();
        }
#endif // if system memory
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

#ifdef H_MEMORY_DEBUG
    //! count number of class in the list.
    osl::u32 getNumInstancesInMemListByClassName( const char* pClassName, MemNodeList* pMemNodeList )
    {
        osl::u32 nNumInsts = 0;

        /// lock the list.
        pMemNodeList->lock();

        std::vector<osl::u8*>::const_iterator it( pMemNodeList->getMemBlocks().begin() ), ite( pMemNodeList->getMemBlocks().end() );

        for ( ; it != ite; ++it )
        {
            osl::u8* pBuf = *it;
            int nNumNodes = pMemNodeList->getBlockSize() / pMemNodeList->getNodeSize();

            for ( int iN = 0; iN < nNumNodes; ++iN )
            {
                // check memroy
                osl::MemPad* pPad = ( osl::MemPad* )( pBuf + pMemNodeList->getNodeSize() - sizeof( osl::MemPad ) );

                osl::MemNode* pMemNode = ( osl::MemNode* )pBuf;

                if ( pPad->nPadWord == osl::c_nPadWordUsed && pMemNode->pClassName )
                {
                    if ( strcmp( pMemNode->pClassName, pClassName ) == 0 )
                    {
                        ++nNumInsts;
                    }
                }

                // next node.
                pBuf += pMemNodeList->getNodeSize();
            }

        }// for each memory block in a size level

        pMemNodeList->unlock();

        return nNumInsts;
    }

#endif
    //----------------------------------------------
    u32 MemAlloc::getNumInstancesByClassName( const char* pClassName, osl::u32 nClassSize )
    {

#ifdef H_MEMORY_DEBUG

        // get actuall node size.
        osl::u32 nNodeSize = sizeof( MemNode ) + sizeof( MemPad ) + nClassSize;

        MemNodeList* pMemNodeList = NULL;

        // small node
        if ( nNodeSize <= c_nMinThresholdMemUnit )
        {
            size_t nIndex = ( ( size_t )nNodeSize - 1 ) / c_nSmallMemIncStepSize;

            // adjust location of returned raw memory.
            pMemNodeList = s_SmallMemList[nIndex];

        }
        else if ( nNodeSize <= c_nMaxMiddleMemList )
        {
            size_t nIndex = getMiddleMemListIndex( ( size_t )nNodeSize );
            pMemNodeList = s_MiddleMemList[nIndex];

        }
        else
        {
            assert( false );
        }

        return getNumInstancesInMemListByClassName( pClassName, pMemNodeList );


#else
        return 0;
#endif
    }

    //----------------------------------------------
    //
    u32 MemAlloc::getNumInstancesByClassName( const char* pClassName )
    {
        osl::u32 nNumInsts = 0;

#ifdef H_MEMORY_DEBUG

        /// small list
        {
            for ( size_t i = 0; i < c_nSmallMemListArraySize; ++i )
            {
                if ( s_SmallMemList[i] )
                {
                    nNumInsts += getNumInstancesInMemListByClassName( pClassName, s_SmallMemList[i] );
                }
            }
        }

        /// large list
        {
            for ( size_t i = 0; i < c_nMiddleMemListArraySize; ++i )
            {
                if ( s_MiddleMemList[i] )
                {
                    nNumInsts += getNumInstancesInMemListByClassName( pClassName, s_MiddleMemList[i] );
                }
            }
        }

#endif
        return nNumInsts;
    }



    //////////////////////////////////////////////////////////////////////////
    //						LargeMemManager
    ////////////////////////////////////////////////////////////////////////////-
    //----------------------------------------------------------
    bool LargeMemManager::initialize()
    {
#if defined(H_OS_WINDOWS) && defined(H_SMALL_MEM_USE_VIRT_MEM)
        assert( m_hHeap == NULL );
        m_hHeap = ::HeapCreate( HEAP_CREATE_ENABLE_EXECUTE, 0, 0 );
        if( !m_hHeap )
        {
            return false;
        }
#endif




        return true;
    }
    //----------------------------------------------------------
    void LargeMemManager::uninitialize()
    {
#if defined(H_OS_WINDOWS) && defined(H_SMALL_MEM_USE_VIRT_MEM)
        ::HeapDestroy( m_hHeap );
        m_hHeap = NULL;
#endif
    }
    //----------------------------------------------------------
    u8* LargeMemManager::allocHeapBlock( osl::u32 nSize )
    {
        //H_AUTOLOCK( m_lkObject );

        if( m_nCurHeapSize > m_nCompactValve )
        {
            compactHeap();

            if( m_nCurHeapSize > m_nMaxHeapSize )
            {
                return NULL;
            }
        }

#if defined(H_OS_WINDOWS) && defined(H_SMALL_MEM_USE_VIRT_MEM)
        u8* pRet = ( u8* )::HeapAlloc( m_hHeap, 0, nSize );
#else	
        u8* pRet = ( u8* )malloc( nSize );
#endif
        if( pRet )
        {
            m_nCurHeapSize += nSize;
        }

        return pRet;
    }
    //----------------------------------------------------------
    void LargeMemManager::freeHeapBlock( osl::u8* pMem, osl::u32 nSize )
    {
#if defined(H_OS_WINDOWS) && defined(H_SMALL_MEM_USE_VIRT_MEM)
        ::HeapFree( m_hHeap, 0, pMem );
#else	
        free( pMem );
#endif

        m_nCurHeapSize -= nSize;
    }
    //----------------------------------------------------------
    void LargeMemManager::compactHeap()
    {
#ifdef H_USE_LARGE_MEM_LIST
        for( osl::u32 i = 0; i < c_nLargeMemListArraySize; ++i )
        {
            s_LargeMemList[i]->clear();
        }
#endif
    }

    //------------------------------------------------------
#ifdef H_MEMORY_DEBUG
    //! count number of class in the list.
    //! \param nNumMatch[out] 匹配的个数
    void* findObjectInMemListByClassName( const char* szClassName, osl::u32 nIndex, osl::u32& nNumMatch, MemNodeList* pMemNodeList )
    {
        //osl::u32 nNumInsts = 0;

        /// lock the list.
        pMemNodeList->lock();

        nNumMatch = 0;

        std::vector<osl::u8*>::const_iterator it( pMemNodeList->getMemBlocks().begin() ), ite( pMemNodeList->getMemBlocks().end() );


        for ( ; it != ite; ++it )
        {
            osl::u8* pBuf = *it;
            int nNumNodes = pMemNodeList->getBlockSize() / pMemNodeList->getNodeSize();

            for ( int iN = 0; iN < nNumNodes; ++iN )
            {
                // check memroy
                osl::MemPad* pPad = ( osl::MemPad* )( pBuf + pMemNodeList->getNodeSize() - sizeof( osl::MemPad ) );

                osl::MemNode* pMemNode = ( osl::MemNode* )pBuf;

                if ( pPad->nPadWord == osl::c_nPadWordUsed && pMemNode->pClassName )
                {
                    if ( strcmp( pMemNode->pClassName, szClassName ) == 0 )
                    {
                        if( nIndex == nNumMatch++ )
                        {
                            pMemNodeList->unlock();
                            return pBuf + sizeof( osl::MemNode );
                        }
                    }
                }

                // next node.
                pBuf += pMemNodeList->getNodeSize();
            }

        }// for each memory block in a size level

        pMemNodeList->unlock();

        return 0;
    }

#endif
    //------------------------------------------------------
    void* MemAlloc::findObjectByClassName( const char* szClassName, osl::u32 nClassSize, osl::u32 nIndex )
    {

#ifdef H_MEMORY_DEBUG

        if( nClassSize != 0 )
        {
            // get actuall node size.
            osl::u32 nNodeSize = sizeof( MemNode ) + sizeof( MemPad ) + nClassSize;

            MemNodeList* pMemNodeList = NULL;

            // small node
            if ( nNodeSize <= c_nMinThresholdMemUnit )
            {
                size_t ni = ( ( size_t )nNodeSize - 1 ) / c_nSmallMemIncStepSize;

                // adjust location of returned raw memory.
                pMemNodeList = s_SmallMemList[ni];

            }
            else if ( nNodeSize <= c_nMaxMiddleMemList )
            {
                size_t ni = getMiddleMemListIndex( ( size_t )nNodeSize );
                pMemNodeList = s_MiddleMemList[ni];

            }
            else
            {
                assert( false );
            }

            osl::u32 nNumMatch = 0;
            return findObjectInMemListByClassName( szClassName, nIndex, nNumMatch, pMemNodeList );
        }
        else
        {
            void* pRet = NULL;
            osl::u32 nNumTotalMatch = 0;

            /// small list
            {
                for ( size_t i = 0; i < c_nSmallMemListArraySize; ++i )
                {
                    if ( s_SmallMemList[i]  )
                    {
                        osl::u32 nNumMatch = 0;
                        osl::u32 nCurIndex = nIndex - nNumTotalMatch;
                        pRet = findObjectInMemListByClassName( szClassName, nCurIndex, nNumMatch, s_SmallMemList[i] );

                        if( pRet )
                        {
                            return pRet;
                        }

                        nNumTotalMatch += nNumMatch;
                    }
                }
            }

            /// large list
            {
                for ( size_t i = 0; i < c_nMiddleMemListArraySize; ++i )
                {
                    if ( s_MiddleMemList[i] )
                    {
                        osl::u32 nNumMatch = 0;
                        osl::u32 nCurIndex = nIndex - nNumTotalMatch;
                        pRet = findObjectInMemListByClassName( szClassName, nCurIndex, nNumMatch, s_MiddleMemList[i] );

                        if( pRet )
                        {
                            return pRet;
                        }

                        nNumTotalMatch += nNumMatch;
                    }
                }
            }
        }

#endif
        return 0;

    }
    // Deump memory list.
    void dumpMemNodeList( std::ostream& file , osl::MemNodeList* lpNodeList, bool bOutputEachUnit )
    {

#ifdef H_COMPILER_MSVC
        typedef stdext::hash_map<const char*, int>  ClassInstanceMap;
#elif defined(H_COMPILER_GNUC)
        typedef __gnu_cxx::hash_map<const char*, int>  ClassInstanceMap;
#endif

        // for each memory size level
        /// lock the list.
        lpNodeList->lock();

        // Node Size
        file << "=========================";
        file << "Pool Size:" <<  outputMemSize( lpNodeList->getMemBlocks().size() * lpNodeList->getBlockSize() ) << "  NodeSize=" << outputMemSize( lpNodeList->getNodeSize() ) << std::endl;

        osl::u32 nNumTotalNodes = 0;
        osl::u32 nNumUsedNodes = 0;
        // collect class name instance count.
        ClassInstanceMap  mapClassInstance;

        std::vector<osl::u8*>::const_iterator it( lpNodeList->getMemBlocks().begin() ), ite( lpNodeList->getMemBlocks().end() );

        for ( ; it != ite; ++it )
        {
            osl::u8* pBuf = *it;
            int nNumNodes = lpNodeList->getBlockSize() / lpNodeList->getNodeSize();

            nNumTotalNodes += nNumNodes;

#ifdef H_MEMORY_DEBUG

            for ( int iN = 0; iN < nNumNodes; ++iN )
            {
                // check memroy
                osl::MemPad* pPad = ( osl::MemPad* )( pBuf + lpNodeList->getNodeSize() - sizeof( osl::MemPad ) );

                if ( pPad->nPadWord == osl::c_nPadWordUsed )
                {
                    ++nNumUsedNodes;

                    osl::MemNode* pMemNode = ( osl::MemNode* )pBuf;

                    mapClassInstance[ pMemNode->pClassName ] += 1;

                    if( bOutputEachUnit && pMemNode->nLine )
                    {
                        const char* pFile1 = strrchr( pMemNode->pFileName, '/' );
                        const char* pFile2 = strrchr( pMemNode->pFileName, '\\' );

                        if( !pFile1 || pFile2 > pFile1 )
                        {
                            pFile1 = pFile2;
                        }

                        file << "ClassName=" << pMemNode->pClassName << "\tFile=" << pFile1 << "\tLine=" << pMemNode->nLine << std::endl;
                    }
                }

                // next node.
                pBuf += lpNodeList->getNodeSize();
            }

#endif

        }// for each memory block in a size level



        /// output
        if ( mapClassInstance.begin() != mapClassInstance.end() )
        {
            // Node Size
            file << "NodeSize=" << outputMemSize( lpNodeList->getNodeSize() ) << "     ===Count:" << nNumTotalNodes;
#ifdef H_MEMORY_DEBUG

            file << "         ===UsedMemSize: " << outputMemSize( lpNodeList->getNodeSize() * nNumUsedNodes  );
#endif

            file << std::endl;

            // Class instances
            ClassInstanceMap::iterator itCI( mapClassInstance.begin() ), itCIE( mapClassInstance.end() );

            for ( ; itCI != itCIE; ++itCI )
            {
                file << "\tClass Name=" <<  itCI->first << "==========count: " << itCI->second << "            ========MemSize: " << outputMemSize( lpNodeList->getNodeSize() * itCI->second  ) << std::endl;
            }
        }

        file << std::endl;


        // unlock
        lpNodeList->unlock();

    }
#ifdef H_USE_LARGE_MEM_LIST
    // Deump huge memory list.
    void dumpLargeMemNodeList( std::ostream& file , osl::LargeMemList* lpNodeList, bool bOutputEachUnit )
    {

#ifdef H_COMPILER_MSVC
        typedef stdext::hash_map<const char*, int>  ClassInstanceMap;
#elif defined(H_COMPILER_GNUC)
        typedef __gnu_cxx::hash_map<const char*, int>  ClassInstanceMap;
#endif

        // for each memory size level
        /// lock the list.
        lpNodeList->lock();

        // Node Size
        file << "=========================";
        //file << "Pool Size:" <<  outputMemSize( lpNodeList->getMemBlocks().size() * lpNodeList->getBlockSize() ) << "  NodeSize=" << outputMemSize( lpNodeList->getNodeSize() ) << std::endl;

        osl::u32 nNumTotalNodes = 0;
        osl::u32 nNumUsedNodes = 0;
        // collect class name instance count.
        ClassInstanceMap  mapClassInstance;

#ifdef H_MEMORY_DEBUG
        MemNodeSet::const_iterator it( lpNodeList->getMemNodes().begin() ), ite( lpNodeList->getMemNodes().end() );
        for(; it != ite; ++it )
        {
            MemNode* pMemNode = *it;

            mapClassInstance[ pMemNode->pClassName ] += 1;

            file << "ClassName=" << pMemNode->pClassName 
                << "\tSize:" << outputMemSize(pMemNode->nSize)
                << "\tFile=" << ( pMemNode->pFileName? pMemNode->pFileName : "unknow file" ) 
                << "\tLine=" << pMemNode->nLine << std::endl;

        }
#endif

        /// output
        if ( mapClassInstance.begin() != mapClassInstance.end() )
        {
            // Node Size
            file << "NodeSize=" << outputMemSize( lpNodeList->getNodeSize() ) << "     ===Count:" << nNumTotalNodes;
#ifdef H_MEMORY_DEBUG

            file << "         ===UsedMemSize: " << outputMemSize( lpNodeList->getNodeSize() * nNumUsedNodes  );
#endif

            file << std::endl;

            // Class instances
            ClassInstanceMap::iterator itCI( mapClassInstance.begin() ), itCIE( mapClassInstance.end() );

            for ( ; itCI != itCIE; ++itCI )
            {
                file << "\tClass Name=" <<  itCI->first << "==========count: " << itCI->second << "            ========MemSize: " << outputMemSize( lpNodeList->getNodeSize() * itCI->second  ) << std::endl;
            }
        }

        file << std::endl;


        // unlock
        lpNodeList->unlock();

    }
#endif


    //----------------------------------------------
    MemAlloc::Stats* MemAlloc::getStats()
    {
        return &s_MemStats;
    }

    namespace
    {
        bool greaterThan( const MemAlloc::Stats::MemCount& a, const MemAlloc::Stats::MemCount& b )
        {
            return a.nUsedCount > b.nUsedCount;
        }
    }

    //----------------------------------------------
    void MemAlloc::dumpStats( std::ostream& file, bool bOutputEachUnit )
    {
        dumpStats( file, 0, 0xffffffff, bOutputEachUnit );
    }


    //----------------------------------------------
    void MemAlloc::dumpStats( std::ostream& file, osl::u32 nMinSize, osl::u32 nMaxSize, bool bOutputEachUnit )
    {

        file << "============================================================" << std::endl
            << "Memory Stats:" << std::endl;


        /// small list
        {
            file << "=======================" << std::endl
                << "Small Memory Stats:" << std::endl;

            for ( size_t i = 0; i < c_nSmallMemListArraySize; ++i )
            {
                if ( s_SmallMemList[i]  )
                {
                    if ( s_SmallMemList[i]->getNodeSize() > nMaxSize )
                    {
                        break;
                    }

                    if ( s_SmallMemList[i]->getNodeSize() >= nMinSize )
                    {
                        dumpMemNodeList( file, s_SmallMemList[i], bOutputEachUnit );
                    }
                }
            }
        }

        /// large list
        {
            file << "=======================" << std::endl
                << "Middle Memory Stats:" << std::endl;

            for ( size_t i = 0; i < c_nMiddleMemListArraySize; ++i )
            {
                if ( s_MiddleMemList[i] )
                {
                    if ( s_MiddleMemList[i]->getNodeSize() > nMaxSize )
                    {
                        break;
                    }

                    if ( s_MiddleMemList[i]->getNodeSize() >= nMinSize )
                    {
                        dumpMemNodeList( file, s_MiddleMemList[i], bOutputEachUnit );
                    }
                }
            }
        }

#ifdef H_USE_LARGE_MEM_LIST
        /// huge list
        {
            file << "=======================" << std::endl
                << "Large Memory Stats:" << std::endl;

            for ( size_t i = 0; i < c_nLargeMemListArraySize; ++i )
            {
                if ( s_LargeMemList[i] )
                {
                    if ( s_LargeMemList[i]->getNodeSize() > nMaxSize )
                    {
                        break;
                    }

                    if ( s_LargeMemList[i]->getNodeSize() >= nMinSize )
                    {
                        dumpLargeMemNodeList( file, s_LargeMemList[i], bOutputEachUnit );
                    }
                }
            }
        }
#endif


        /// 
        // system heap memory
        {
            file << "=======================" << std::endl
                << "System heap Memory Stats:" << std::endl;

            s_SysHeapMemList->lock();

#ifdef H_MEMORY_DEBUG
            SysHeapMemList::SysMemNode* pTailNode = s_SysHeapMemList->getTailNode();
            while( pTailNode )
            {
                MemNode* pNode = &pTailNode->base;

                file << "ClassName=" << pNode->pClassName 
                    << "\tSize:" << outputMemSize(pNode->nSize)
                    << "\tFile=" << ( pNode->pFileName? pNode->pFileName : "unknow file" ) 
                    << "\tLine=" << pNode->nLine << std::endl;

                // next node.
                pTailNode = pTailNode->pPreNode;
            }
#endif

            s_SysHeapMemList->unlock();
        }

#ifdef H_MEMORY_DEBUG
        // Node use count rank
        {
            //
            if( bOutputEachUnit )
            {
                file << "\n\n\n\n\n============================================================\n"
                    << "============================================================\n"
                    << "============================================================\n"
                    << "Memory node used count:\n"
                    << "size\t\tused times:\n";

                //descending sort
                std::sort( s_MemStats.pMemNodeCountArray, s_MemStats.pMemNodeCountArray + c_nMemBlockIncSize, &greaterThan );

                for ( u32 i = 0; i < c_nMemBlockIncSize; ++i )
                {
                    if ( !s_MemStats.pMemNodeCountArray[i].nUsedCount )
                    {
                        break;
                    }

                    file << outputMemSize( s_MemStats.pMemNodeCountArray[i].nMemSize ) << "\t\t" << s_MemStats.pMemNodeCountArray[i].nUsedCount << "\n";
                }

                file << "============================================================\n";
                file << "============================================================\n";
                file << "============================================================\n";
            }
        }
#endif

        file << "=======================" << std::endl
            << "Summary:" << std::endl;


        // small, large, huge list
        for ( size_t i = 0; i < ( size_t )s_MemStats.nMemListSize; ++i )
        {
            MemAlloc::Stats::MemListStats* pStats = s_MemStats.pMemListStatsArray + i;

            if ( pStats->nNumAllocatedSize != 0 )
            {
                file << "==memory unit size of: " << outputMemSize( pStats->nNodeSize ) << std::endl
                    << "used node number   : " << pStats->nNumUsedNode << std::endl
                    << "used size          : " << outputMemSize( pStats->nNumUsedNode * pStats->nNodeSize ) << std::endl
                    << "all size           : " << outputMemSize( pStats->nNumAllocatedSize ) << std::endl
                    << "alloc times        : " << pStats->nNumAllocTime << std::endl;
            }
        }

        // system heap memory
        {
            file << "=======================" << std::endl
                << "System Heap Memory:" << std::endl;

            //if ( s_MemStats.sysHeapMemStats.nNumUsedNode != 0 )
            {
                file << "==system heap memory unfree node number: " << s_MemStats.sysHeapMemStats.nNumUsedNode << std::endl
                    << "used size                       : " << outputMemSize( s_MemStats.sysHeapMemStats.nNumAllocatedSize ) << std::endl
                    << "alloc times                     : " << s_MemStats.sysHeapMemStats.nNumAllocTime << std::endl;
            }
        }


        file << "===================================" << std::endl;

        file //<< "total pool(KB): " << ( s_MemStats.nTotalAllocatedSize >> 10 ) << std::endl
            << "total pool : " << outputMemSize( s_MemStats.nTotalAllocatedSize ) << std::endl
            //<< "total busy(KB):"  << ( s_MemStats.nTotalBusySize >> 10 ) << std::endl
            << "total busy : "  << outputMemSize( s_MemStats.nTotalBusySize  ) << std::endl;

        file << "============================================================\n";




        return;
    }






    //------------------------------------------------------

    //------------------------------------------------------
#ifdef H_MEMORY_DEBUG
    typedef std::list< MemAlloc::ObjectNode*>  ObjectNodeList;

    void findObjectReferencesInMemList( ObjectNodeList& vList,  PointerInt val, MemNodeList* lpNodeList )
    {
        // for each memory size level
        /// lock the list.
        lpNodeList->lock();

        std::vector<osl::u8*>::const_iterator it( lpNodeList->getMemBlocks().begin() ), ite( lpNodeList->getMemBlocks().end() );

        osl::u8* pLastBuf = NULL;

        if(	it != ite )
        {
            pLastBuf = *( lpNodeList->getMemBlocks().rbegin() );
        }

        for ( ; it != ite; ++it )
        {
            osl::u8* pBufStart = *it;
            osl::u8* pBuf = pBufStart;

            int nNumNodes = lpNodeList->getBlockSize() / lpNodeList->getNodeSize();

            for ( int iN = 0; iN < nNumNodes; ++iN )
            {
                // check memroy
                osl::MemPad* pPad = ( osl::MemPad* )( pBuf + lpNodeList->getNodeSize() - sizeof( osl::MemPad ) );

                // if last unused block, just stop find.
                if( pLastBuf == pBufStart &&  ( u8* )pPad > lpNodeList->getCurRawMemStart() )
                {
                    break;
                }

                if ( pPad->nPadWord == osl::c_nPadWordUsed )
                {
                    osl::u8* pStart = pBuf + sizeof( osl::MemNode );
                    osl::u8*   pEnd = ( osl::u8* )pPad;

                    while( pStart != pEnd )
                    {
                        if( *( PointerInt* )pStart == val )
                        {
                            osl::MemNode* pNode = ( osl::MemNode* )( pBuf );

                            MemAlloc::ObjectNode* pRefNode = ( MemAlloc::ObjectNode* )::malloc( sizeof( MemAlloc::ObjectNode ) );

                            pRefNode->nNodeSize = lpNodeList->getNodeSize();

                            pRefNode->pObject = pBuf + sizeof( osl::MemNode );
                            pRefNode->nOffset = pStart - ( osl::u8* )pRefNode->pObject;

                            pRefNode->szClass = pNode->pClassName;
                            pRefNode->szFile  = pNode->pFileName;
                            pRefNode->nLine   = pNode->nLine;

                            vList.push_back( pRefNode );
                        }

                        ++pStart;
                    }
                }

                // next node.
                pBuf += lpNodeList->getNodeSize();
            }

        }// for each memory block in a size level

        lpNodeList->unlock();
    }
#endif

    //------------------------------------------------------
    void MemAlloc::findObjectReferences( ObjectNode**& pReferences, PointerInt val )
    {
#ifdef H_MEMORY_DEBUG

        ObjectNodeList vList;
        /// small list
        {
            for ( size_t i = 0; i < c_nSmallMemListArraySize; ++i )
            {
                if ( s_SmallMemList[i]  )
                {
                    findObjectReferencesInMemList( vList, val, s_SmallMemList[i] );
                }
            }
        }

        /// large list
        {
            for ( size_t i = 0; i < c_nMiddleMemListArraySize; ++i )
            {
                if ( s_MiddleMemList[i] )
                {
                    findObjectReferencesInMemList( vList, val, s_MiddleMemList[i] );
                }
            }
        }

        // allocate list.
        pReferences = ( ObjectNode** )::malloc( ( vList.size() + 1 ) * sizeof( ObjectNode* ) );

        osl::u32 i = 0;
        ObjectNodeList::iterator it( vList.begin() ), ite( vList.end() );

        for( ; it != ite; ++it )
        {
            pReferences[i++] = *it;
        }

        pReferences[i] = NULL;
#endif
    }
    //------------------------------------------------------
    void MemAlloc::freeObjectReferenceList( ObjectNode** pReferences )
    {
#ifdef H_MEMORY_DEBUG
        if( !pReferences )
        {
            return;
        }

        ObjectNode** pReferencesT = pReferences;

        while( *pReferencesT )
        {
            ::free( *pReferencesT );

            ++pReferencesT;
        }

        ::free( pReferences );
#endif
    }
    //------------------------------------------------------
    void MemAlloc::findObjectReferences( ObjectNode**& pReferences, const char* szClassName, osl::u32 nClassSize, osl::u32 nIndex )
    {
#ifdef H_MEMORY_DEBUG
        void* pObject = findObjectByClassName( szClassName, nClassSize, nIndex );

        if( !pObject )
        {
            return;
        }

        findObjectReferences( pReferences, ( PointerInt )pObject );
#endif
    }


    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////
#ifdef H_MEMORY_DEBUG
    bool findObjectByAddrInMemList( MemAlloc::ObjectNode& obj, PointerInt nAddr, MemNodeList* lpNodeList )
    {
        // for each memory size level
        /// lock the list.
        lpNodeList->lock();

        std::vector<osl::u8*>::const_iterator it( lpNodeList->getMemBlocks().begin() ), ite( lpNodeList->getMemBlocks().end() );

        for ( ; it != ite; ++it )
        {
            PointerInt nOffset = nAddr - ( PointerInt ) * it;

            if( nOffset <= ( PointerInt )( lpNodeList->getBlockSize() ) )
            {
                osl::u8* pBuf = *it + nOffset / lpNodeList->getNodeSize() * lpNodeList->getNodeSize();

                osl::MemNode* pNode = ( osl::MemNode* )( pBuf );

                obj.nNodeSize = lpNodeList->getNodeSize();

                obj.pObject = pBuf + sizeof( osl::MemNode );
                obj.nOffset = nAddr - ( PointerInt )pBuf;

                obj.szClass = pNode->pClassName;
                obj.szFile  = pNode->pFileName;
                obj.nLine   = pNode->nLine;
                lpNodeList->unlock();
                return true;
            }
        }// for each memory block in a size level

        lpNodeList->unlock();

        return false;
    }
#endif
    //------------------------------------------------------
    bool MemAlloc::findObjectByAddr( MemAlloc::ObjectNode& obj, PointerInt nAddr )
    {
#ifdef H_MEMORY_DEBUG

        /// small list
        {
            for ( size_t i = 0; i < c_nSmallMemListArraySize; ++i )
            {
                if ( s_SmallMemList[i]  )
                {
                    if( findObjectByAddrInMemList( obj, nAddr, s_SmallMemList[i] ) )
                    {
                        return true;
                    }
                }
            }
        }

        /// large list
        {
            for ( size_t i = 0; i < c_nMiddleMemListArraySize; ++i )
            {
                if ( s_MiddleMemList[i] )
                {
                    if( findObjectByAddrInMemList( obj, nAddr, s_MiddleMemList[i] ) )
                    {
                        return true;
                    }
                }
            }
        }
#endif
        return false;
    }




};
