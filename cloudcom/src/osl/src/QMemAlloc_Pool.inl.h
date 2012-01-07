#pragma once



// enable memory stats
#define H_MEMORY_STATS


//! 是不是使用自己的虚拟内存管理
#define H_SMALL_MEM_USE_VIRT_MEM

//! 是不是开启大号内存池，Large. larger than 256KB
#define H_USE_LARGE_MEM_LIST

namespace osl
{
    //! allocate virtual memory.
    u8* allocVirtualBlock( osl::u32 nSize )
    {

#if defined(H_OS_WINDOWS) && defined(H_SMALL_MEM_USE_VIRT_MEM)
        return ( u8* )::VirtualAlloc( 0, nSize
            , MEM_COMMIT | MEM_RESERVE  //! 保留，提交内存， 两阶段工作一起做。
            | MEM_TOP_DOWN//| ,                                                           //!  使用大内存页，64KB， 使用高端地址。因为不释放。
            , //PAGE_READWRITE 
            PAGE_READWRITE
            //| PAGE_WRITECOMBINE             //! 开放任何访问权限。 打开写合并。
            );          

#else	
        return ( u8* )malloc( nSize );
#endif
    }

    //! Free a virtual memory block.
    void freeVirtualBlock( osl::u8* pMem )
    {
#if defined(H_OS_WINDOWS) && defined(H_SMALL_MEM_USE_VIRT_MEM)
        //VirtualAlloc
        ::VirtualFree( pMem, 0, MEM_RELEASE );
#else	
        free( pMem );
#endif
    }




    static MemAlloc::Stats s_MemStats;


    //----------------------------------------------
    static const unsigned short c_nSmallMemBlockSlotID = 1;
    static const unsigned short c_nLargeMemBlockSlotID  = 0;
    static const unsigned short c_nPadWordUsed         = 0xf40e;
    static const unsigned short c_nPadWordFree         = 0x54ea;
    //static const unsigned size_t   c_nSizeMemHeader       = 8;  // use 8 bytes as header.

#ifdef H_ARCH_32
#	pragma pack( push,8 )
#else
#	pragma pack( push,4 )
#endif

    struct MemNode
    {
        union
        {
            size_t nSize;
            MemNode* pNextNode;
        };
#ifdef H_MEMORY_DEBUG
        const char* pClassName;
        const char* pFileName;
        int nLine;
#endif
    };
    typedef std::set<MemNode*>  MemNodeSet;

#ifdef H_MEMORY_DEBUG
    struct MemPad
    {
        u16  nBlockSlot;   // Memory block slot index.
        u16    nPadWord;  // Pad word at word just before memory.
    };
#endif

#pragma pack(pop)


    //! Small memory unit manager.
    class MemNodeList
    {
    public:
        MemNodeList( size_t nNodeSize, size_t nBlockIncSize, size_t nIndexIHListArray )
            : m_nNodeSize( nNodeSize ), m_nRawMemBlockIncSize( nBlockIncSize )
            , m_nIndexIHListArray( nIndexIHListArray )
        {
            m_pFreeNodeHeader = NULL;
            m_pRawMemStart = NULL;
            m_nRawMemRemainSize = 0;
#ifdef H_MEMORY_DEBUG
            m_nMemPadOffset = m_nNodeSize - sizeof( MemPad );
            m_nUserMemUnitSize = m_nNodeSize - sizeof( MemPad ) - sizeof( MemNode );
#else
            m_nUserMemUnitSize = m_nNodeSize - sizeof( MemNode );
#endif

#ifdef H_MEMORY_STATS
            memset( &s_MemStats.pMemListStatsArray[m_nIndexIHListArray], 0,
                sizeof( MemAlloc::Stats::MemListStats ) );
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNodeSize = m_nNodeSize;
#endif
        }

        ~MemNodeList()
        {
            clear();
        }

        MemNode* getMemNode()
        {
            H_AUTOLOCK( m_lkObject );

            MemNode* pRetNode = NULL;

            if ( m_pFreeNodeHeader )
            {
                pRetNode = m_pFreeNodeHeader;
                m_pFreeNodeHeader = m_pFreeNodeHeader->pNextNode;

#ifdef H_MEMORY_DEBUG
                MemPad*  pMemPad    =  ( MemPad* )( ( ( char* )pRetNode ) + m_nMemPadOffset );
                pMemPad->nBlockSlot = c_nSmallMemBlockSlotID;
                pMemPad->nPadWord   = c_nPadWordUsed;
#endif
            }
            else
            {
                if ( m_nRawMemRemainSize < m_nNodeSize )
                {
                    // allocate a block of memory.
                    m_pRawMemStart = ( u8* )allocVirtualBlock( m_nRawMemBlockIncSize );

                    if ( !m_pRawMemStart )
                    {
                        return NULL;
                    }

                    m_vRawMemBlock.push_back( m_pRawMemStart );
                    m_nRawMemRemainSize = m_nRawMemBlockIncSize;

#ifdef H_MEMORY_STATS
                    s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumAllocatedSize += m_nRawMemBlockIncSize;
                    s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumBlock++;
                    s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode +=
                        m_nRawMemBlockIncSize / m_nNodeSize;

                    InterlockedXAdd( &s_MemStats.nTotalAllocatedSize, ( long )m_nRawMemBlockIncSize );
#endif
                }

                pRetNode = ( MemNode* )m_pRawMemStart;
                m_pRawMemStart = ( ( u8* )pRetNode ) + m_nNodeSize;
                m_nRawMemRemainSize -= m_nNodeSize;

#ifdef H_MEMORY_DEBUG
                MemPad*  pMemPad    =  ( MemPad* )( ( ( char* )pRetNode ) + m_nMemPadOffset );
                pMemPad->nBlockSlot = c_nSmallMemBlockSlotID;
                pMemPad->nPadWord   = c_nPadWordUsed;
#endif
            }

#ifdef H_MEMORY_STATS
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumAllocTime++;
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumUsedNode++;
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode--;
            assert( s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode < 0x00ffffff );
            assert( pRetNode );
#endif
            pRetNode->nSize    = m_nNodeSize;
            return pRetNode;
        }

        void recycleMemNode( MemNode* pMemNode )
        {
            H_AUTOLOCK( m_lkObject );

            pMemNode->pNextNode = m_pFreeNodeHeader;
            m_pFreeNodeHeader = pMemNode;

            //
#ifdef H_MEMORY_DEBUG
            memset( ( ( u8* )( pMemNode ) ) + sizeof( MemNode ) , 0xcd, m_nNodeSize - ( sizeof( MemNode ) + sizeof( MemPad ) ) );
#endif

#ifdef H_MEMORY_STATS
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode++;
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumUsedNode--;
#endif
        }

        void clear()
        {
            std::vector<u8*>::iterator itrBlockE = m_vRawMemBlock.end();

            for ( std::vector<u8*>::iterator itrBlock = m_vRawMemBlock.begin();
                itrBlock != itrBlockE; ++itrBlock )
            {
                freeVirtualBlock( *itrBlock );
            }

            m_vRawMemBlock.clear();
            m_pFreeNodeHeader = NULL;
            m_pRawMemStart = NULL;
            m_nRawMemRemainSize = 0;
        }

        size_t getNodeSize()const
        {
            return m_nNodeSize;
        }

        size_t getBlockSize()const
        {
            return m_nRawMemBlockIncSize;
        }

        // Lock the memroy list.
        void lock()
        {
            m_lkObject.lock();
        }

        //! unlock the memory list.
        void unlock()
        {
            m_lkObject.unlock();
        }

        //! Ges memory block list.
        const std::vector<u8*>& getMemBlocks()const
        {
            return  m_vRawMemBlock;
        }

        //! Gets last memory address.
        u8* getCurRawMemStart()const
        {
            return m_pRawMemStart;
        }

        //! Gets memory stats
        MemAlloc::Stats::MemListStats* getStats()const
        {
#ifdef H_MEMORY_STATS
            return s_MemStats.pMemListStatsArray + m_nIndexIHListArray;
#else
            return NULL;
#endif
        }


    protected:
        size_t                m_nNodeSize;   //! Size of each memory unit of this list, including MemNode, user memory and MemPad
        size_t         m_nUserMemUnitSize;   //! size of the user request to allocate memory size, e.g: 8, 16, 24, 32
        //size_t           m_nMemUnitSize;   //! Size of each memory unit of this list, including MemNode, user memory and MemPad 

        size_t      m_nRawMemBlockIncSize;   //! Memory increment size when we request memory from os heap runtime of the list. 1MB in default.
        size_t        m_nIndexIHListArray;   //! Index in the nodelist array.It is for debug mode.

        MemNode*        m_pFreeNodeHeader;   //! header of memory node list.

        u8*                m_pRawMemStart;   //! a pointer to the unused raw memory block
        size_t        m_nRawMemRemainSize;   //! raw memory block size remaining in the raw block

        std::vector<u8*>   m_vRawMemBlock;   //! blocks allocated up to date.

#ifdef H_MEMORY_DEBUG
        size_t            m_nMemPadOffset;   //! position of memory pad structure from start of memory node.
#endif
        osl::Lock            m_lkObject;
    };



    //!!! 在三种不同大类内存的尺寸交叉的地方，采用重叠冗余方式，因为优先从小号池分配，所以大号的开始列表成为冗余的。!!!

    //! Small memory unit
    const size_t c_nMinUserMemUnitSize = 8;//! the minimum size of user memory allocating unit, in bytes
    const size_t c_nMinThresholdMemUnit = 128;//! we use this threshold value to make difference between small memory and large memory.
    const size_t c_nSmallMemListArraySize = c_nMinThresholdMemUnit / c_nMinUserMemUnitSize;  //! the size of s_SmallMemList
    const size_t c_nSmallMemIncStepSize = 8;		// size difference of memory node between adjacent list.


    //! Middle memory unit
    const size_t c_nMinMiddleMemListShift = 7;	// minimum number to shift left 1 for large node from 128B to ...
    const size_t c_nMaxMiddleMemListShift = 18;	// maximum number to shift left 1 for large node 20(1MB) 19(512KB) 18(256KB)
    const size_t c_nMinMiddleMemList = 1 << c_nMinMiddleMemListShift;	// minimum node size of large node
    const size_t c_nMaxMiddleMemList = 1 << c_nMaxMiddleMemListShift;	// maximum node size of large node
    const size_t c_nMiddleMemListArraySize = 2 * ( c_nMaxMiddleMemListShift - c_nMinMiddleMemListShift + 1 );

    // Memory block size.
    const size_t c_nMemBlockIncSize = 1 << ( c_nMaxMiddleMemListShift + 1 );	//! the memory block increment size


#ifdef H_USE_LARGE_MEM_LIST
    //! Large memory unit
    const size_t c_nMinLargeMemListSize = 1 << ( c_nMaxMiddleMemListShift ); //! minimum node size for huge memory from ( 1 << c_nMaxMiddleMemListShift ) to ...
    const size_t c_nMaxLargeMemListSize = 1 << 25;		// maximum node size for huge memory. ((1<<25)32MB) (1<<24)16MB (1<<23)8M (1 << 22)4MB;
    const size_t c_nLargeMemIncStepSize = 1 << 17;		// size difference of memory node between adjacent list. 17(128KB) 16(64KB)
    const size_t c_nLargeMemListArraySize = ( c_nMaxLargeMemListSize - c_nMinLargeMemListSize ) / c_nLargeMemIncStepSize + 1;
#endif







    //! Large memory mananger.
    //! 对于大内存，我们使用系统堆来做，因为系统堆会进行碎片合并等工作，应该比我们自己做要好。
    // 
    class LargeMemList;
    class LargeMemManager
    {
    public:	
        LargeMemManager()
        {
            m_nMaxHeapSize  = 1 << 29;   //! 512MB
            m_nCompactValve = m_nMaxHeapSize >> 3;// 64MB
            m_nCurHeapSize  = 0;
#if defined(H_OS_WINDOWS) && defined(H_SMALL_MEM_USE_VIRT_MEM)
            m_hHeap = NULL;
#endif
        }

        ~LargeMemManager()
        {
            uninitialize();
        }

        //! Initialize the huge memory manager.
        bool initialize();

        //! Uninitialize the manager.
        void uninitialize();

        //! allocate a heap memory.
        u8* allocHeapBlock( osl::u32 nSize );

        //! Free a heap memory block.
        //! \param nSize Size of pMem. It is reserved by LargeMemList when allocate the memory.
        void freeHeapBlock( osl::u8* pMem, osl::u32 nSize );

        //! Free a heap memory block.
        //! \param nSize Size of pMem. It is reserved by LargeMemList when allocate the memory.
        void freeSysHeapBlock( osl::u8* pMem, osl::u32 nSize );

        // Lock the memroy list.
        void lock()
        {
            m_lkObject.lock();
        }

        //! unlock the memory list.
        void unlock()
        {
            m_lkObject.unlock();
        }

    private:
#if defined(H_OS_WINDOWS) && defined(H_SMALL_MEM_USE_VIRT_MEM)
        HANDLE                        m_hHeap;   //! handle for heap.
#endif
        osl::u32             m_nMaxHeapSize;   //! max heap size 512MB in default

        osl::u32            m_nCompactValve;   //! size of heap over which should find and clean free nodes. m_nMaxHeapSize >> 1 in default.
        osl::u32             m_nCurHeapSize;   //! current heap size.

        osl::Lock              m_lkObject;
    private:

        //! Check heap state.
        void compactHeap();
    };

    LargeMemManager* s_pLargeMemManager = NULL;


#ifdef H_USE_LARGE_MEM_LIST
    //! Large memory unit manager.
    class LargeMemList
    {
    public:
        LargeMemList( size_t nNodeSize,  size_t nIndexIHListArray )
            : m_nNodeSize( nNodeSize )
            , m_nIndexIHListArray( nIndexIHListArray )
        {
            m_pFreeNodeHeader = NULL;

#ifdef H_MEMORY_DEBUG
            m_nMemPadOffset = m_nNodeSize - sizeof( MemPad );
            m_nUserMemUnitSize = m_nNodeSize - sizeof( MemPad ) - sizeof( MemNode );
#else
            m_nUserMemUnitSize = m_nNodeSize - sizeof( MemNode );
#endif

#ifdef H_MEMORY_STATS
            memset( &s_MemStats.pMemListStatsArray[m_nIndexIHListArray], 0,
                sizeof( MemAlloc::Stats::MemListStats ) );
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNodeSize = m_nNodeSize;
#endif
        }

        ~LargeMemList()
        {
            clear();
        }

        MemNode* getMemNode()
        {
            //H_AUTOLOCK( m_lkObject );

            MemNode* pRetNode = NULL;

            if ( m_pFreeNodeHeader )
            {
                pRetNode = m_pFreeNodeHeader;
                m_pFreeNodeHeader = m_pFreeNodeHeader->pNextNode;
            }
            else
            {
                //
                pRetNode = (MemNode*)s_pLargeMemManager->allocHeapBlock( m_nNodeSize );
                if( !pRetNode )
                {
                    return NULL;
                }

#ifdef H_MEMORY_STATS
                s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumAllocatedSize += m_nNodeSize;
                s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumBlock++;
                s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode += 1;

                InterlockedXAdd( &s_MemStats.nTotalAllocatedSize, ( long )m_nNodeSize );
#endif
            }

#ifdef H_MEMORY_DEBUG
            MemPad*  pMemPad    =  ( MemPad* )( ( ( char* )pRetNode ) + m_nMemPadOffset );
            pMemPad->nBlockSlot = c_nLargeMemBlockSlotID;
            pMemPad->nPadWord   = c_nPadWordUsed;
#endif

#ifdef H_MEMORY_STATS
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumAllocTime++;
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumUsedNode++;
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode--;
            assert( s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode < 0x00ffffff );
            assert( pRetNode );
#endif
            pRetNode->nSize    = m_nNodeSize;

#ifdef H_MEMORY_DEBUG
            m_setBusyNodes.insert( pRetNode );
#endif
            return pRetNode;
        }

        void recycleMemNode( MemNode* pMemNode )
        {
            //H_AUTOLOCK( m_lkObject );

            pMemNode->pNextNode = m_pFreeNodeHeader;
            m_pFreeNodeHeader = pMemNode;

#ifdef H_MEMORY_DEBUG
            m_setBusyNodes.erase( pMemNode );
#endif

            //
#ifdef H_MEMORY_DEBUG
            memset( ( ( u8* )( pMemNode ) ) + sizeof( MemNode ) , 0xcd, m_nNodeSize - ( sizeof( MemNode ) + sizeof( MemPad ) ) );
#endif

#ifdef H_MEMORY_STATS
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode++;
            s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumUsedNode--;
#endif
        }

        void clear()
        {
            //H_AUTOLOCK( m_lkObject );

            while( m_pFreeNodeHeader )
            {
                MemNode* pCurNode = m_pFreeNodeHeader;
                m_pFreeNodeHeader = m_pFreeNodeHeader->pNextNode;

                // free memory.
                s_pLargeMemManager->freeHeapBlock( (u8*)pCurNode, m_nNodeSize );
            }
        }

        size_t getNodeSize()const
        {
            return m_nNodeSize;
        }

        size_t getBlockSize()const
        {
            return m_nNodeSize;
        }

        // Lock the memroy list.
        void lock()
        {
            m_lkObject.lock();
        }

        //! unlock the memory list.
        void unlock()
        {
            m_lkObject.unlock();
        }

        //! Gets free node header.
        MemNode* getFreeNodeHeader()const
        {
            return m_pFreeNodeHeader;
        }

#ifdef H_MEMORY_DEBUG
        //! Gets memory block list.
        const MemNodeSet& getMemNodes()const
        {
            return  m_setBusyNodes;
        }
#endif

        //! Gets memory stats
        MemAlloc::Stats::MemListStats* getStats()const
        {
#ifdef H_MEMORY_STATS
            return s_MemStats.pMemListStatsArray + m_nIndexIHListArray;
#else
            return NULL;
#endif
        }

    protected:
        size_t                  m_nNodeSize;   //! Size of each memory unit of this list, including MemNode, user memory and MemPad
        size_t           m_nUserMemUnitSize;   //! size of the user request to allocate memory size, e.g: 8, 16, 24, 32
        //size_t             m_nMemUnitSize;   //! Size of each memory unit of this list, including MemNode, user memory and MemPad 

        size_t          m_nIndexIHListArray;   //! Index in the nodelist array.It is for debug mode.

        MemNode*          m_pFreeNodeHeader;   //! header of memory node list.



#ifdef H_MEMORY_DEBUG
        size_t              m_nMemPadOffset;   //! position of memory pad structure from start of memory node.
        MemNodeSet           m_setBusyNodes;
#endif
        osl::Lock              m_lkObject;
    };
#endif


    /// system heap mem list. 直接使用堆内存，不做自己的池，但是保留了内存追踪能力
    class SysHeapMemList
    {
    public:
#pragma pack(push,8)
        struct SysMemNode
        {
            SysMemNode*   pPreNode;
            SysMemNode*  pNextNode;
            MemNode          base;
        };
#pragma pack(pop)

        static const osl::u32   c_nMemNodeSizeDiff = sizeof(SysMemNode) - sizeof(MemNode);
    public:
        //!
        SysHeapMemList()
        {
#ifdef H_MEMORY_DEBUG
            m_pTailNode = NULL;
#endif
        };

        MemNode* getMemNode( osl::u32 nBytes )
        {
            //H_AUTOLOCK( m_lkObject );

            // 对齐到64KB,便于内存管理
            nBytes = ( nBytes + c_nMemNodeSizeDiff + 0xffff ) & ~0xffff; //为什么减1？ 我不知道0xff和256在内部怎么表示的，害怕多分配内存。

            SysMemNode* pRetNode = ( SysMemNode* )s_pLargeMemManager->allocHeapBlock( nBytes );

            if ( !pRetNode )
            {
                return NULL;
            }

            // set  node size without our header..
            pRetNode->base.nSize     = nBytes - c_nMemNodeSizeDiff;

#ifdef H_MEMORY_DEBUG

            // add to tail of bi-directional list.
            {
                // modify current tail.
                if( m_pTailNode )
                {
                    m_pTailNode->pNextNode = pRetNode;
                }

                // process node
                pRetNode->pPreNode = m_pTailNode;
                pRetNode->pNextNode = NULL;
                m_pTailNode = pRetNode;
            }


            MemPad*  pMemPad    =  ( MemPad* )( ( ( char* )pRetNode ) + nBytes - sizeof( MemPad ) );
            pMemPad->nBlockSlot = c_nLargeMemBlockSlotID;
            pMemPad->nPadWord   = c_nPadWordUsed;
#endif

#ifdef H_MEMORY_STATS
            s_MemStats.sysHeapMemStats.nNumAllocTime++;
            s_MemStats.sysHeapMemStats.nNumAllocatedSize += nBytes;
            s_MemStats.sysHeapMemStats.nNumUsedNode++;

            InterlockedXAdd( &s_MemStats.nTotalAllocatedSize, nBytes );

#endif
            return (MemNode*)((osl::u8*)pRetNode + c_nMemNodeSizeDiff );
        }

        void recycleMemNode( MemNode* pMemNode )
        {
            //H_AUTOLOCK( m_lkObject );

            SysMemNode* pMyNode = (SysMemNode*)(((osl::u8*)pMemNode) - c_nMemNodeSizeDiff);

#ifdef H_MEMORY_DEBUG

            // erase from bi-directional list.
            {
                if( pMyNode->pPreNode )
                {
                    pMyNode->pPreNode->pNextNode = pMyNode->pNextNode;
                }

                if( pMyNode->pNextNode )
                {
                    pMyNode->pNextNode->pPreNode = pMyNode->pPreNode;
                }
            }

            if( pMyNode == m_pTailNode )
            {
                //H_ASSERT( !pMyNode->pNextNode );
                m_pTailNode = pMyNode->pPreNode;
            }

#endif

#ifdef H_MEMORY_STATS
            s_MemStats.sysHeapMemStats.nNumAllocatedSize -= ( pMemNode->nSize + c_nMemNodeSizeDiff );
            s_MemStats.sysHeapMemStats.nNumUsedNode--;
            //s_MemStats.nTotalAllocatedSize -= pMemNode->nSize;

            InterlockedXAdd( &s_MemStats.nTotalAllocatedSize, -( long )pMemNode->nSize );
#endif
            //::free( ( void* )pMemNode );
            s_pLargeMemManager->freeHeapBlock( (osl::u8*)pMyNode, pMemNode->nSize + c_nMemNodeSizeDiff );
        }



        // Lock the memroy list.
        void lock()
        {
            m_lkObject.lock();
        }

        //! unlock the memory list.
        void unlock()
        {
            m_lkObject.unlock();
        }

#ifdef H_MEMORY_DEBUG
        //! Gets memory block list.
        SysMemNode* getTailNode()const
        {
            return  m_pTailNode;
        }
#endif


    private:

#ifdef H_MEMORY_DEBUG
        SysMemNode*              m_pTailNode;
#endif
        osl::Lock               m_lkObject;
    };












    //     class EnhanceMemNodeList
    //     {
    //         struct  MemBlockItem
    //         {
    //             MemNode*      pNodeHeader;
    //             size_t      nNumFreeNodes;
    //             u8*             pMemBlock;
    //         };
    //     protected:
    //         size_t             m_nNodeSize;	 // Size of each memory node of the list,including node
    //         size_t         m_nBlockIncSize;  // Memory increment size by which apply memory from heap of the list
    //         size_t     m_nIndexIHListArray;  // Index in the nodelist array.It is for debug mode.
    //
    //         size_t    m_nMaxNodeNumInBlock;  // max node num in one block
    //
    //         u8*                m_pRawBlock;  // unused raw memory block
    //         u8*           m_pRawBlockStart;  // Start of current raw block.
    //         size_t              m_nRawSize;  // raw memory block size.
    //
    //         std::vector<MemBlockItem>  m_vMemBlocks;// blocks allocated up to date.
    //
    //         size_t            m_nPosMemPad;  // position of memory pad structor from start of memory node.
    //
    //         osl::Lock        m_lkObject;
    //
    //     public:
    //         EnhanceMemNodeList( size_t nNodeSize, size_t nBlockIncSize, size_t nIndexIHListArray )
    //             : m_nNodeSize( nNodeSize ), m_nBlockIncSize( nBlockIncSize )
    //             , m_nIndexIHListArray( nIndexIHListArray )
    //             , m_pRawBlock( NULL )
    //             , m_nRawSize( 0 )
    //         {
    //             m_nMaxNodeNumInBlock = size_t( m_nBlockIncSize / m_nNodeSize );
    //
    //             m_nPosMemPad = m_nNodeSize - sizeof( MemPad );
    //
    // #ifdef H_MEMORY_STATS
    //             memset( &s_MemStats.pMemListStatsArray[m_nIndexIHListArray], 0,
    //                 sizeof( MemAlloc::Stats::MemListStats ) );
    //             s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNodeSize = m_nNodeSize;
    // #endif
    //         }
    //
    //         ~EnhanceMemNodeList()
    //         {
    //             clear();
    //         }
    //
    //         MemNode* getMemNode()
    //         {
    //             H_AUTOLOCK( m_lkObject );
    //
    //             MemNode* pRetNode = NULL;
    //
    //             if ( m_pRawBlock && m_nRawSize >= m_nNodeSize )
    //             {
    //                 pRetNode    = ( MemNode* )m_pRawBlock;
    //                 m_pRawBlock = m_pRawBlock + m_nNodeSize;
    //                 m_nRawSize -= m_nNodeSize;
    //
    //                 pRetNode->nSize      = m_nNodeSize;
    //
    //                 MemPad*  pMemPad    =  ( MemPad* )( ( ( char* )pRetNode ) + m_nPosMemPad );
    //                 pMemPad->nBlockSlot = HIWORD( long( m_pRawBlockStart ) );
    //                 pMemPad->nPadWord   = c_nPadWordUsed;
    //
    //             }
    //             else
    //             {
    //                 size_t l_nFullBlockID = 0xffffffff;
    //                 size_t l_nFreeNodeNum = ( size_t )l_nFullBlockID;
    //                 size_t l_nBlockNum = m_vMemBlocks.size();
    //
    //                 for ( size_t i = 0 ; i < l_nBlockNum ; ++i )
    //                 {
    //                     size_t l_nFreeNodeNumThis = m_vMemBlocks[i].nNumFreeNodes;
    //
    //                     if ( l_nFreeNodeNumThis <= l_nFreeNodeNum )
    //                         if ( l_nFreeNodeNumThis > 0 )
    //                         {
    //                             l_nFreeNodeNum = l_nFreeNodeNumThis;
    //                             l_nFullBlockID = i;
    //                         }
    //                 }
    //
    //                 if ( l_nFullBlockID != 0xffffffff )
    //                 {
    //                     MemBlockItem& mbi = m_vMemBlocks[ l_nFullBlockID ];
    //
    //                     assert( mbi.pNodeHeader && "Wrong in mem getMemNode" );
    //
    //                     pRetNode        = mbi.pNodeHeader;
    //                     mbi.pNodeHeader = pRetNode->pNextNode;
    //                     --mbi.nNumFreeNodes;
    //
    //                     pRetNode->nSize      = m_nNodeSize;
    //
    //                 }
    //                 else
    //                 {
    //                     MemBlockItem mbi;
    //
    //                     m_pRawBlockStart = ( u8* )malloc( m_nBlockIncSize );
    //
    //                     if ( !m_pRawBlockStart )
    //                     {
    //                         return NULL;
    //                     }
    //
    //                     m_pRawBlock      = m_pRawBlockStart + m_nNodeSize;
    //
    //                     pRetNode = ( MemNode* )m_pRawBlockStart;
    //                     m_nRawSize = m_nBlockIncSize - m_nNodeSize;
    //
    //                     mbi.pMemBlock     = m_pRawBlockStart;
    //                     mbi.pNodeHeader   = NULL;
    //                     mbi.nNumFreeNodes = 0;
    //
    //                     m_vMemBlocks.push_back( mbi );
    //
    //                     pRetNode->nSize      = m_nNodeSize;
    //
    //                     MemPad*  pMemPad    =  ( MemPad* )( ( ( char* )pRetNode ) + m_nPosMemPad );
    //                     pMemPad->nBlockSlot = HIWORD( long( m_pRawBlockStart ) );
    //                     pMemPad->nPadWord   = c_nPadWordUsed;
    //
    //
    // #ifdef H_MEMORY_STATS
    //                     s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumAllocatedSize += m_nBlockIncSize;
    //                     s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumBlock++;
    //                     s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode +=
    //                         m_nBlockIncSize / m_nNodeSize;
    //
    //                     InterlockedXAdd( &s_MemStats.nTotalAllocatedSize, ( long )m_nBlockIncSize );
    // #endif
    //                 }
    //             }
    //
    // #ifdef H_MEMORY_STATS
    //             s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumAllocTime++;
    //             s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumUsedNode++;
    //             s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode--;
    //             assert( s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode < 0x00ffffff );
    //             assert( pRetNode );
    // #endif
    //
    //             return pRetNode;
    //         }
    //
    //         void recycleMemNode( MemNode* pMemNode )
    //         {
    //             H_AUTOLOCK( m_lkObject );
    //
    //             size_t l_nBlockNum = m_vMemBlocks.size();
    //
    //             for ( size_t i = 0 ; i < l_nBlockNum ; ++i )
    //             {
    //                 MemBlockItem& mbi = m_vMemBlocks[ i ];
    //
    //                 MemPad*  pMemPad    =  ( MemPad* )( ( ( char* )pMemNode ) + m_nNodeSize - sizeof( MemPad ) );
    //
    //                 if ( HIWORD( long( mbi.pMemBlock ) ) != pMemPad->nBlockSlot )continue;
    //
    //                 pMemNode->pNextNode = mbi.pNodeHeader;
    //                 mbi.pNodeHeader     = pMemNode;
    //
    //                 if ( ++mbi.nNumFreeNodes == m_nMaxNodeNumInBlock )
    //                 {
    //                     free( mbi.pMemBlock );
    //
    //                     m_vMemBlocks.erase( ( m_vMemBlocks.begin() + i ) );
    //
    // #ifdef H_MEMORY_STATS
    //                     s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumAllocatedSize -= m_nBlockIncSize;
    //                     s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumBlock--;
    //                     s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode -=
    //                         m_nBlockIncSize / m_nNodeSize;
    //
    //                     //s_MemStats.nTotalAllocatedSize -= m_nBlockIncSize;
    //
    //                     InterlockedXAdd( &s_MemStats.nTotalAllocatedSize, -( long )m_nBlockIncSize );
    // #endif
    //
    //                 }
    //
    // #ifdef H_MEMORY_STATS
    //                 s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumFreeNode++;
    //                 s_MemStats.pMemListStatsArray[m_nIndexIHListArray].nNumUsedNode--;
    // #endif
    //
    //                 return;
    //
    //             }// for each block slot.
    //
    //             assert( false && "Wrong in recycleMemNode." );
    //
    //             return;
    //         }
    //
    //         void clear()
    //         {
    //             std::vector<MemBlockItem>::iterator itrBlockE = m_vMemBlocks.end();
    //
    //             for ( std::vector<MemBlockItem>::iterator itrBlock = m_vMemBlocks.begin();
    //                 itrBlock != itrBlockE; ++itrBlock )
    //             {
    //                 free( ( void* )itrBlock->pMemBlock );
    //             }
    //
    //             m_vMemBlocks.clear();
    //             m_pRawBlock = NULL;
    //             m_nRawSize = 0;
    //         }
    //
    //         /** Gets node size and half node size. */
    //         size_t getNodeSize()const
    //         {
    //             return m_nNodeSize;
    //         }
    //
    //     };


}//namespace osl
