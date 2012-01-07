#ifndef _H_OSLIB_MEMALLOC_H
#define _H_OSLIB_MEMALLOC_H

#include "osl/include/platform_micros.h"

//! Whether use minimum memory.
//! Comment out H_MINI_MEM_USE if want to debug memroy
#ifdef H_DEBUG_MODE
#else
#	define H_MINI_MEM_USE
#endif

// use memory debug.
//#define H_MEMORY_DEBUG

//禁止调试内存，如果在调试模式，需要禁用内存池的话，打开这个宏.
//#define H_DISABLE_MEMORY_DEBUG

// Them macro may be defined by make file. 是不是打开内存调试诊断
#if defined(H_MEMORY_DEBUG) && defined( H_MINI_MEM_USE) 
#	undef H_MEMORY_DEBUG
#endif

#if defined(H_MEMORY_DEBUG) && defined( H_DISABLE_MEMORY_DEBUG )
#	undef H_MEMORY_DEBUG
#endif

/*
#ifdef H_MEMORY_DEBUG
#	define H_MEMORY_POOL
#else 
// 如果使用内存池，那么启用他。
#	define H_MEMORY_POOL
#endif
*/

namespace osl
{


    //! Pool memory management.
    //! \par Have three memory list group, the first group contains memory unit less than or equal 128 B, the second group contains
    //!      memory unit less than or equal 512KB. the third group contains memory unit larger than 512KB. we name them 'small group'
    //!      'large group' and  'huge group'.
    //! \par  'small group' has 128/8=16 memory lists, each of the memory list contains certain sized memory units. the memory unit size
    //!      grow at 8B step.
    //! \par 内存对象查询功能， 可以根据分配时指定的ClassName来查找特定类名的实例指针。
    //! \par 内存对象引用查询功能，可以遍历内存查找引用了某个值的所有的内存对象，可以看到这些内存大小，在引用对象中的偏移地址，内存对象
    //!      的类名，文件等等信息。
    class _EXPORT_OSLIB MemAlloc
    {
    public:

        //! Memory statistic.
        class Stats
        {
        public:
            struct MemListStats
            {
                size_t nNodeSize;			// memory size of each memory node.
                size_t nNumBlock;			// total block number in the list.
                size_t nNumAllocatedSize;   // total allocated size.
                size_t nNumUsedNode;		// used node number.
                size_t nNumFreeNode;		// free node number.
                size_t nNumAllocTime;		// times of allocate operation on the list.
            };
        public:
            volatile AtomicInt     nTotalAllocatedSize;	//! total allocated pool size.
            volatile AtomicInt          nTotalBusySize;	//! currently used size
            MemListStats*           pMemListStatsArray;	//! memory list array.
            volatile     AtomicInt        nMemListSize;	//! memory list array size.
            MemListStats                  sysHeapMemStats;	//! huge memory statistics.

        public:
            struct MemCount
            {
                u32    nMemSize; //! the size of the memory node
                u32  nUsedCount; //! the count, this memory node is used.
            };
            MemCount*              pMemNodeCountArray; //! used to statistic the every MemNode count
        };


        //! Object node in memory pool
        struct ObjectNode
        {
            int            nNodeSize;   //! Node size of reference target
            int              nOffset;   //! position the reference in the target.
            void*            pObject;   //! pointer to start of object memory.
            const char*      szClass;   //! Class name of reference target.
            const char*       szFile;   //! file that allocate the memory of reference target.
            int                nLine;
        };

    public:

        //! Alloc memory with size.
        static void* alloc( size_t nBytes );
        static void* alloc( size_t nBytes , const char*pClassName );
        static void* alloc( size_t nBytes , const char*pClassName, const char* pFileName, int nLine );
        static void free( void* ptr );

        //! Allocate aligned memory. MUST free with freeAligned
        static void* allocAligned( size_t nBytes, osl::u32 nAlign = 16 );
        static void* allocAligned( size_t nBytes , const char*pClassName, osl::u32 nAlign = 16 );
        static void* allocAligned( size_t nBytes , const char*pClassName, const char* pFileName, int nLine, osl::u32 nAlign = 16 );
        static void freeAligned( void* ptr );

        static Stats* getStats();

        //! Dump the memory usage statistics.
        //! \remark The method is specially used for debug purpose. The method may be very slow, since it will iterate all memory list.
        //! \param bOutputEachUnit Whether output each allocation unit to output file.
        static void dumpStats( std::ostream& file, bool bOutputEachUnit );

        //! Dump the memory usage statistics. between nMinSize and nMaxSize
        //! \remark The method is specially used for debug purpose. The method may be very slow, since it will iterate all memory list.
        //! \param nMinSize Start size of memory to stat.
        //! \param nMaxSize Max size of memory to stat.
        //! \param bOutputEachUnit Whether output each allocation unit to output file.
        static void dumpStats( std::ostream& file, osl::u32 nMinSize, osl::u32 nMaxSize, bool bOutputEachUnit );


        //! Gets  instance name
        //! \remark The method is specially used for debug purpose and do nothing in release mode
        //! \param nClassSize Size of the class. The value MUST be sizeof(ClassName), else will find 0. It used to accelerate
        //! searching.
        static u32 getNumInstancesByClassName( const char* pClassName, osl::u32 nClassSize );

        //! Gets instance name.
        //! \remark The method is specially used for debug purpose. The method may be very slow, since it will iterate all memory list.
        //! searching.
        static u32 getNumInstancesByClassName( const char* pClassName );

        //template<typename _ClassType >
        //static _ClassType* getObject()
        //{
        //	return (_ClassType*)getObject( sizeof(_ClassType), #_ClassType);
        //}

        //! Gets memory object by address.
        //! \note The method ONLY take effect in debug mode.The method may be very slow, since it will iterate all memory list.
        //! \param obj[out] Received found memory object.
        //! \param nAddr  address of memory which located in the object.
        //! \return false if find nothing.
        static bool findObjectByAddr( ObjectNode& obj, PointerInt nAddr );


        //! Gets memory object by class name and class type.
        //! \note The method ONLY take effect in debug mode.The method may be very slow, since it will iterate all memory list.
        //! \par   The method faster than findObjectByClassName( const char* szClassName, osl::u32 nIndex ) which have to search
        //!        all the pool memory.
        //! \param szClassName Class name to find.
        //! \param nClassSize Class size to find. If is 0, search all memory list.
        //! \param nIndex  i'th match object.
        //! \return NULL if find nothing.
        static void* findObjectByClassName( const char* szClassName, osl::u32 nClassSize = 0, osl::u32 nIndex = 0 );


        //! Finds object references .
        //! \note The method ONLY take effect in debug mode.The method may be very slow, since it will iterate all memory list.
        //! \param pReferences[out] Hold reference list. The last element is NULL, Use findObjectReferences to free it later.
        //! \param szClassName Class name of object to find.
        //! \param nIndex  i'th match object.
        static void findObjectReferences( ObjectNode**& pReferences, const char* szClassName, osl::u32 nClassSize = 0, osl::u32 nIndex = 0 );

        //! Finds object references.
        //! \note The method ONLY take effect in debug mode.The method may be very slow, since it will iterate all memory list.
        //! \param pReferences[out] Hold reference list. The last element is NULL, Use findObjectReferences to free it later.
        //! \param pTarget pSource object to find.
        static void findObjectReferences( ObjectNode**& pReferences, PointerInt val );

        // Free object reference list obtained from findObjectReferences.
        //! \note The method ONLY take effect in debug mode.The method may be very slow, since it will iterate all memory list.
        static void freeObjectReferenceList( ObjectNode** pReferences );

    private:
        friend bool osl::initializeOSLib();
        friend void osl::uninitializeOSLib();

        //! Hide constructor.
        MemAlloc();
        ~MemAlloc();
        MemAlloc( const MemAlloc& );

        //! Initialize the memory allocator.
        static void initialize();

        //! Uninitialize the memory allocator.
        static void uninitialize();
    };



    //! Scoped memory block. When lifetime out, memory in the object will be freed.
    //! \warning The object SHOULD ONLY be used on stack.
    struct _EXPORT_OSLIB ScopedMem
    {
        void*   pRep;
        ScopedMem( const ScopedMem& r );    //!< 勿加实现
    public:

        ScopedMem(): pRep( 0 ) {}

        ScopedMem( void* _rep )
            :pRep( _rep )
        {
        }

        //! Construct a sized memory.
        ScopedMem( osl::u32 nSize );

        ~ScopedMem()
        {
            if ( pRep )
            {
                osl::MemAlloc::free( pRep );
            }
        }

        inline ScopedMem& operator=( void*pBuf )
        {
            if ( pRep )
            {
                osl::MemAlloc::free( pRep );
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

};



//! Gets instance name by class name. It will iterator all the memory node and count instances.
#define H_GET_CLASS_INSTANCE_NUM( myClass )     osl::MemAlloc::getNumInstancesByClassName( #myClass, sizeof(myClass) );




/** Helper macro to override new and delete operators for classes that
* *  dont need reference counting and may be frequent to be created and
* *  destoryed.
* *  @warning For referece counted object, MUST NOT use the macro.
* */
#ifndef H_ALLOCRAW_OPERATORS

#ifdef H_MINI_MEM_USE
#	define H_ALLOCRAW_OPERATORS( typename )								  	\
    public:																    \
    void* operator new( size_t nSize ) {								  	\
    return osl::MemAlloc::alloc( nSize );				                	\
}																	 	\
    void  operator delete( void* ptr ) {								  	\
    if(ptr) osl::MemAlloc::free( ptr );							 	    \
}																	 	\
    void* operator new( size_t nSize ,const char*pFile,int nLine) {	   		\
    return osl::MemAlloc::alloc( nSize );                              	\
}																		\
    void  operator delete( void* ptr ,const char*,int ) {					\
    if(ptr) osl::MemAlloc::free( ptr );								    \
}																		\
    void* operator new(size_t, void* location) {		 					\
    return location;								 					    \
}																		\
    void operator delete(void* , void*) {}			   						\
    void* operator new[]( size_t nSize ) {			   						\
    return osl::MemAlloc::alloc( nSize );		  						    \
}																		\
    void  operator delete[]( void* ptr ) {			   						\
    if(ptr) osl::MemAlloc::free( ptr );								    \
}


#else

#	define H_ALLOCRAW_OPERATORS( typename )								  	\
    public:																    \
    void* operator new( size_t nSize ) {								  	\
    return osl::MemAlloc::alloc( nSize, #typename );					\
}																	 	\
    void  operator delete( void* ptr ) {								  	\
    if(ptr) osl::MemAlloc::free( ptr );							 	\
}																	 	\
    void* operator new( size_t nSize ,const char*pFile,int nLine) {	   		\
    return osl::MemAlloc::alloc( nSize, #typename , pFile , nLine );	\
}																		\
    void  operator delete( void* ptr ,const char*,int ) {					\
    if(ptr) osl::MemAlloc::free( ptr );								\
}																		\
    void* operator new(size_t, void* location) {		 					\
    return location;								 					\
}																		\
    void operator delete(void* , void*) {}			   						\
    void* operator new[]( size_t nSize ) {			   						\
    return osl::MemAlloc::alloc( nSize );		  						\
}																		\
    void  operator delete[]( void* ptr ) {			   						\
    if(ptr) osl::MemAlloc::free( ptr );								\
}

#endif // H_MINI_MEM_USE
#endif // H_ALLOCRAW_OPERATORS




/**
* Alignment macros
*/

/* H_ALIGN() is only to be used to align on a power of 2 boundary */
#define H_ALIGN(size, boundary) (((size) + ((boundary) - 1)) & ~((boundary) - 1))

/** Default alignment */
#define H_ALIGN_DEFAULT(size) H_ALIGN(size, 16)




//---------------------------------------------------
//! 定义new 操作符的宏
#ifdef H_NEW
#	undef H_NEW
#endif

//! 定义new 操作符的宏
#ifdef H_DEBUG_MODE
#	define H_NEW                         new( __FILE__ , __LINE__ )
#else
#	define H_NEW                         new
#endif

//---------------------------------------------------
//! 定义malloc的宏

#ifdef H_ALLOC
#	undef H_ALLOC
#endif

#ifdef H_ALLOC_NAME
#	undef H_ALLOC_NAME
#endif

#ifdef H_MINI_MEM_USE
#	define H_ALLOC( size )               osl::MemAlloc::alloc( (size) )
#	define H_ALLOC_NAME( size, name )    osl::MemAlloc::alloc( (size) )
#else
#	define H_ALLOC( size )               osl::MemAlloc::alloc( (size), __FILE__, __FILE__, __LINE__ )
#	define H_ALLOC_NAME( size, name )    osl::MemAlloc::alloc( (size), (name), __FILE__, __LINE__ )
#endif


#ifdef H_FREE
#	undef H_FREE
#endif

#define H_FREE( p )            osl::MemAlloc::free( (p) )
#define H_SAFE_FREE( p )       if(p){ osl::MemAlloc::free( (p) ); p = 0;}



//! Aligned memory allocate macros.
#ifdef H_MINI_MEM_USE
#	define H_ALLOC_ALIGNED( size, aligned )               osl::MemAlloc::allocAligned( (size), (aligned) )
#	define H_ALLOC_ALIGNED_NAME( size, name, aligned )    osl::MemAlloc::allocAligned( (size), (aligned) )
#else
#	define H_ALLOC_ALIGNED( size, aligned )               osl::MemAlloc::allocAligned( (size), __FILE__, __FILE__, __LINE__, (aligned) )
#	define H_ALLOC_ALIGNED_NAME( size, name, aligned )    osl::MemAlloc::allocAligned( (size), (name), __FILE__, __LINE__, (aligned) )
#endif


#ifdef H_FREE_ALIGNED
#	undef H_FREE_ALIGNED
#endif

#define H_FREE_ALIGNED( p )            osl::MemAlloc::freeAligned( (p) )
#define H_SAFE_FREE_ALIGNED( p )       if(p){ osl::MemAlloc::freeAligned( (p) ); p = 0;}

#endif	//_NMEMALLOC_H



