#ifndef QOSLIB_HObject_H
#define QOSLIB_HObject_H

#include "osl/include/atomic_op.h"

#include "osl/include/malloc_micro.h"

namespace osl
{


    /** Interface provides referencing counted function. It can be generalized
    *  by Object derived object or general object.
    *  @note Derived classes are responsible for instance destroy.
    *  @note Derived classes are responsible for thread safe implementation.
    */
    class _EXPORT_OSLIB RefTarget
    {
    public:
        // Constructor & Destructor.
        RefTarget() {};
        virtual ~RefTarget() {};

        /** Increments the reference count and returns the new value.*/
        virtual void ref() const = 0;

        /** Decrements the reference count and returns the new value.*/
        virtual void unref() const = 0;

        /** Gets the reference count.*/
        virtual s32 getRef() const = 0;
    };

    template<class Base>
    class RefTargetImpl : public Base
    {
    public:
        RefTargetImpl(): m_nRefCount( 0 ) {}
        //! \copydoc RefTarget::ref
        virtual void ref()const;
        //! \copydoc RefTarget::unref
        virtual void unref()const;
        //! \copydoc RefTarget::getRef
        virtual s32 getRef() const
        {
            return m_nRefCount;
        }
    private:
#ifdef H_OS_WINDOWS
		mutable volatile long m_nRefCount;
#elif defined(H_OS_LINUX)
		mutable volatile s32    m_nRefCount;
#endif
    };

	//! The macro used to trace class allocation. Should place at header of Object derived class.
#define H_ALLOC_OBJECT( CLASSNAME )                                                      \
public:                                                                                 \
	void* operator new( size_t nSize)                                               \
	{                                                                               \
		return H_ALLOC_NAME( nSize , #CLASSNAME );						\
	}                                                                               \
	void* operator new(size_t nSize,const char* pFileName,int nLine)                \
	{                                                                               \
		return H_ALLOC_NAME_FILE( nSize , #CLASSNAME , pFileName , nLine );    \
	}

    //! The class provides memory manage and RTTI feature for derived class.
    //! \remark
    class _EXPORT_OSLIB Object : public RefTarget
    {
		H_ALLOC_OBJECT( Object );
    public:
        Object(): m_nRefCount( 0 ) {}

        // need to override from derived class.
        virtual ~Object() {}

        /** @copydoc RefTarget::ref the reference count and returns
        *  the new value.
        */
        virtual void ref() const;

        /** @copydoc RefTarget::unref
        *  @note If reference count arrive zero, the instance will be
        *     destroyed.
        */
        virtual void unref() const;

        /** @copydoc RefTarget::getRef. Gets the reference count */
        s32 getRef() const
        {
            return ( s32 )m_nRefCount;
        }

        //! Not Supported
        void* operator new( size_t /*s*/, void* /*p*/ ) throw( )
        {
            assert( "Not Supported." );
            return 0;
        }
        //! Not Supported
        void* operator new[]( size_t /*nSize*/ ) throw( )
        {
            assert( "Not Supported." );
            return 0;
        }
        //! Not Supported
        void* operator new[]( size_t /*s*/, void* /*p*/ ) throw( )
        {
            assert( "Not Supported." );
            return 0;
        }

        void operator delete( void *ptr )
        {
            H_FREE( ptr );
        }
        void operator delete( void *ptr, const char*, int )
        {
            H_FREE( ptr );
        }

        //! Not Supported
        void  operator delete[]( void* /*ptr*/ )
        {
            assert( "Not Supported." );
        }
        //! Not Supported
        void operator delete[]( void * /*p1*/, void * /*p2*/ ) throw( )
        {
            assert( "Not Supported." );
        }
        //! Not Supported
        void operator delete( void * /*p1*/, void * /*p2*/ ) throw( )
        {
            assert( "Not Supported." );
        }

    protected:
		mutable volatile AtomicInt32 m_nRefCount;
    };


    //! The macro used to typedef RefPtr for a class.
#define H_REF_PTR(classname)  class classname; typedef osl::RefPtr<classname>  classname##Ptr;


    /** Pointer class. */
    template<class T> class RefPtr
    {
    public:
        typedef T object_type;
    protected:
        T* pRep;
    public:
        RefPtr(): pRep( 0 ) {}

        RefPtr( object_type* rep )
        {
            pRep = dynamic_cast<object_type*>( rep );

            if ( pRep )
            {
                pRep->ref();
            }
        }

        // Get Pointer from other type
        template< class U >
        RefPtr( U* rep )
        {
            pRep = dynamic_cast<object_type*>( rep );

            if ( pRep )
            {
                pRep->ref();
            }
        }

        RefPtr( const RefPtr& r )
        {
            pRep = r.getPointer();

            if ( pRep )
            {
                pRep->ref();
            }
        }

        template< class U >
        RefPtr( const RefPtr<U>& r )
        {
            pRep = dynamic_cast<object_type*>( r.getPointer() );

            if ( pRep )
            {
                pRep->ref();
            }
        }

        // assigner
        RefPtr& operator=( const RefPtr& r )
        {

            bind( r.getPointer() );

            return *this;
        }

        // assigner
        RefPtr& operator=( object_type* rep )
        {

            bind( rep );

            return *this;
        }

        // assigner
        template< class U >
        RefPtr& operator=( const RefPtr<U>& r )
        {

            bind( dynamic_cast<object_type*>( r.getPointer() ) );

            return *this;
        }

        ~RefPtr()
        {
            setNull();
        }

        inline operator object_type*()const
        {
            return pRep;
        }
        inline object_type& operator*() const
        {
            assert( pRep );
            return *pRep;
        }
        inline object_type* operator->() const
        {
            assert( pRep );
            return pRep;
        }

        inline const object_type* get() const
        {
            return pRep;
        }
        inline object_type* getPointer() const
        {
            return pRep;
        }
        inline bool isNull( void ) const
        {
            return pRep == 0;
        }
        //bool operator!() const { return pRep == 0; }
        //inline bool operator<(const RefPtr& r )const{ return getPointer() < r.getPointer(); }
        //inline bool operator==(const object_type* rep )const{ return getPointer() == rep;}
        //inline bool operator!=(const object_type* rep )const{ return getPointer() != rep;}

        /** Binds rep to the RefPtr.*/
        void bind( object_type* rep )
        {
            // MUST before setNull to assure object is relatively deleted.
            if ( rep )
            {
                rep->ref();
            }

            setNull();

            // copy data.
            pRep = rep;
        }

        /** Clear reference */
        void setNull( void )
        {
            if ( pRep )
            {
				T* pThis = pRep;
                pRep = NULL;
                pThis->unref();
            }
        }

        void swap( osl::RefPtr<T>& r )
        {
            std::swap( this->pRep , r.pRep );
        }
    };

    template<class T, class U> inline bool operator==( RefPtr<T> const& a, RefPtr<U> const& b )
    {
        return a.get() == b.get();
    }

    template<class T, class U> inline bool operator!=( RefPtr<T> const& a, RefPtr<U> const& b )
    {
        return a.get() != b.get();
    }



    typedef RefPtr<RefTarget>   RefPointer;
    typedef RefPtr<Object>      ObjectPtr;

    //---------------------------------------------------------
    //---------------------------------------------------------
    //---------------------------------------------------------
    // inline method
    template<class Base>
    inline void osl::RefTargetImpl<Base>::ref() const
    {
        InterlockedInc32( &m_nRefCount );
    }

    template<class Base>
    inline void osl::RefTargetImpl<Base>::unref() const
    {
        if ( InterlockedDec32( &m_nRefCount ) <= 0 )
        {
            delete this;
        }
    }

    //----------------------------------------------
    inline void Object::ref()const
    {
        InterlockedInc32( &m_nRefCount );
    }

    //----------------------------------------------
    inline void Object::unref() const
    {
        if ( InterlockedDec32( &m_nRefCount ) <= 0 )
        {
            delete this;
        }
    }
   

//////////////////////////////////////////////////////////////////////////
//  Helper Macros for object derived from Object And RefTarget
//////////////////////////////////////////////////////////////////////////
#define H_REFERENCE_METHODS( ConcreteClass )                                 \
public:                                                                  \
    virtual void ref() const          { return ConcreteClass::ref(); }       \
    virtual void unref() const        { return ConcreteClass::unref(); }     \
    virtual osl::s32 getRef() const   { return ConcreteClass::getRef(); }

};//namespace



namespace std
{
    template<class T>
    void swap( osl::RefPtr<T>& l , osl::RefPtr<T>& r )
    {
        return l.swap( r );
    }
}


#endif	//_Object_H



