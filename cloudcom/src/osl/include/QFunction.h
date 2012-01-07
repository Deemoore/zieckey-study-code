
#ifndef _QOSLIB_FUNCTION_
#define _QOSLIB_FUNCTION_


namespace osl
{


    //////////////////////////////////////////////////////////////////////////////////////////
    //                    void-return  Function Base
    //////////////////////////////////////////////////////////////////////////////////////////

    class FunctionBase0 : public Object
    {
    public:
        virtual void operator()() = 0;
    };


    template <typename Arg1>
    class FunctionBase1 : public Object
    {
    public:
        virtual void operator()( Arg1 v1 ) = 0;
    };


    template <typename Arg1, typename Arg2 >
    class FunctionBase2 : public Object
    {
    public:
        virtual void operator()( Arg1 v1, Arg2 v2 ) = 0;
    };

    template <typename Arg1, typename Arg2, typename Arg3 >
    class FunctionBase3 : public Object
    {
    public:
        virtual void operator()( Arg1 v1, Arg2 v2, Arg3 v3 ) = 0;
    };

    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    class FunctionBase4 : public Object
    {
    public:
        virtual void operator()( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 ) = 0;
    };


    //////////////////////////////////////////////////////////////////////////////////////////
    //                    typed-return  Function Base
    //////////////////////////////////////////////////////////////////////////////////////////
    template <typename Ret>
    class FunctionBaseR0 : public Object
    {
    public:
        virtual Ret operator()() = 0;
    };

    template <typename Ret, typename Arg1>
    class FunctionBaseR1 : public Object
    {
    public:
        virtual Ret operator()( Arg1 v1 ) = 0;
    };

    template <typename Ret, typename Arg1, typename Arg2 >
    class FunctionBaseR2 : public Object
    {
    public:
        virtual Ret operator()( Arg1 v1 , Arg2 v2 ) = 0;
    };

    template <typename Ret, typename Arg1, typename Arg2, typename Arg3 >
    class FunctionBaseR3 : public Object
    {
    public:
        virtual Ret operator()( Arg1 v1, Arg2 v2, Arg3 v3 ) = 0;
    };

    template <typename Ret, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    class FunctionBaseR4 : public Object
    {
    public:
        virtual Ret operator()( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 ) = 0;
    };


    //////////////////////////////////////////////////////////////////////////////////////////
    //                    void-return  Function implementations
    //////////////////////////////////////////////////////////////////////////////////////////

    // v0
    //template <>
    class FunctionImpl0 : public FunctionBase0
    {
    public:
        typedef void ( *SlotFunction )();

        FunctionImpl0( SlotFunction fun ):	m_Fun( fun ) {}

        virtual void operator()()
        {
            ( *m_Fun )();
        };
    protected:
        SlotFunction  m_Fun;
    };

    template <class Functor>
    class Functor0 : public FunctionBase0
    {
    public:
        Functor0( Functor fun ):	m_Fun( fun ) {}

        virtual void operator()()
        {
            m_Fun();
        };
    protected:
        Functor  m_Fun;
    };

    template <class T >
    class FunctionMember0 : public FunctionBase0
    {
    public:
        typedef void ( T::*Fun )();

        FunctionMember0( T* pHolder, Fun fun ): m_pHolder( pHolder ), m_Fun( fun ) {}

        virtual void operator()()
        {
            ( m_pHolder->*m_Fun )();
        };

    protected:
        T*   m_pHolder;
        Fun      m_Fun;
    };

    // v1
    template <typename Arg1>
    class FunctionImpl1 : public FunctionBase1<Arg1>
    {
    public:
        typedef void ( *SlotFunction )( Arg1 );

        FunctionImpl1( SlotFunction fun ):	m_Fun( fun ) {}

        virtual void operator()( Arg1 v1 )
        {
            ( *m_Fun )( v1 );
        };
    protected:
        SlotFunction  m_Fun;
    };

    template <class Functor, typename Arg1>
    class Functor1 : public FunctionBase1<Arg1>
    {
    public:
        Functor1( Functor fun ):	m_Fun( fun ) {}

        virtual void operator()( Arg1 v1 )
        {
            m_Fun( v1 );
        };
    protected:
        Functor  m_Fun;
    };

    template <class T, typename Arg1>
    class FunctionMember1 : public FunctionBase1<Arg1>
    {
    public:
        typedef void ( T::*Fun )( Arg1 v1 );

        FunctionMember1( T* pHolder, Fun fun ): m_pHolder( pHolder ), m_Fun( fun ) {}

        virtual void operator()( Arg1 v1 )
        {
            ( m_pHolder->*m_Fun )( v1 );
        };

    protected:
        T*   m_pHolder;
        Fun      m_Fun;
    };

    // v2
    template <typename Arg1, typename Arg2>
    class FunctionImpl2 : public FunctionBase2<Arg1, Arg2>
    {
    public:
        typedef void ( *SlotFunction )( Arg1, Arg2 );

        FunctionImpl2( SlotFunction fun ):	m_Fun( fun ) {}

        virtual void operator()( Arg1 v1, Arg2 v2 )
        {
            ( *m_Fun )( v1, v2 );
        };
    protected:
        SlotFunction  m_Fun;
    };

    template <class Functor, typename Arg1, typename Arg2 >
    class Functor2 : public FunctionBase2<Arg1, Arg2>
    {
    public:
        Functor2( Functor fun ):	m_Fun( fun ) {}

        virtual void operator()( Arg1 v1, Arg2 v2 )
        {
            m_Fun( v1, v2 );
        };
    protected:
        Functor  m_Fun;
    };

    template <class T, typename Arg1, typename Arg2 >
    class FunctionMember2 : public FunctionBase2<Arg1, Arg2>
    {
    public:
        typedef void ( T::*Fun )( Arg1 v1, Arg2 v2 );

        FunctionMember2( T* pHolder, Fun fun ): m_pHolder( pHolder ), m_Fun( fun ) {}

        virtual void operator()( Arg1 v1, Arg2 v2 )
        {
            ( m_pHolder->*m_Fun )( v1, v2 );
        };

    protected:
        T*   m_pHolder;
        Fun      m_Fun;
    };

    // v3
    template <typename Arg1, typename Arg2, typename Arg3>
    class FunctionImpl3 : public FunctionBase3<Arg1, Arg2, Arg3>
    {
    public:
        typedef void ( *SlotFunction )( Arg1, Arg2, Arg3 );

        FunctionImpl3( SlotFunction fun ):	m_Fun( fun ) {}

        virtual void operator()( Arg1 v1, Arg2 v2, Arg3 v3 )
        {
            ( *m_Fun )( v1, v2, v3 );
        };
    protected:
        SlotFunction  m_Fun;
    };

    template <class Functor, typename Arg1, typename Arg2, typename Arg3 >
    class Functor3 : public FunctionBase3<Arg1, Arg2, Arg3>
    {
    public:
        Functor3( Functor fun ):	m_Fun( fun ) {}

        virtual void operator()( Arg1 v1, Arg2 v2, Arg3 v3 )
        {
            m_Fun( v1, v2, v3 );
        };
    protected:
        Functor  m_Fun;
    };

    template <class T, typename Arg1, typename Arg2, typename Arg3>
    class FunctionMember3 : public FunctionBase3<Arg1, Arg2, Arg3>
    {
    public:
        typedef void ( T::*Fun )( Arg1 v1, Arg2 v2, Arg3 v3 );

        FunctionMember3( T* pHolder, Fun fun ): m_pHolder( pHolder ), m_Fun( fun ) {}

        virtual void operator()( Arg1 v1, Arg2 v2, Arg3 v3 )
        {
            ( m_pHolder->*m_Fun )( v1, v2, v3 );
        };

    protected:
        T*   m_pHolder;
        Fun      m_Fun;
    };

    // v4
    template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    class FunctionImpl4 : public FunctionBase4<Arg1, Arg2, Arg3, Arg4>
    {
    public:
        typedef void ( *SlotFunction )( Arg1, Arg2, Arg3, Arg4 );

        FunctionImpl4( SlotFunction fun ):	m_Fun( fun ) {}

        virtual void operator()( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 )
        {
            ( *m_Fun )( v1, v2, v3, v4 );
        };
    protected:
        SlotFunction  m_Fun;
    };

    template <class Functor, typename Arg1, typename Arg2, typename Arg3, typename Arg4 >
    class Functor4 : public FunctionBase4<Arg1, Arg2, Arg3, Arg4>
    {
    public:
        Functor4( Functor fun ):	m_Fun( fun ) {}

        virtual void operator()( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 )
        {
            m_Fun( v1, v2, v3, v4 );
        };
    protected:
        Functor  m_Fun;
    };

    template <class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    class FunctionMember4 : public FunctionBase4<Arg1, Arg2, Arg3, Arg4>
    {
    public:
        typedef void ( T::*Fun )( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 );

        FunctionMember4( T* pHolder, Fun fun ): m_pHolder( pHolder ), m_Fun( fun ) {}

        virtual void operator()( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 )
        {
            ( m_pHolder->*m_Fun )( v1, v2, v3, v4 );
        };

    protected:
        T*   m_pHolder;
        Fun      m_Fun;
    };


    //////////////////////////////////////////////////////////////////////////////////////////
    //                    Typed-return  Function implementations
    //////////////////////////////////////////////////////////////////////////////////////////

    // v0
    template < typename Ret >
    class FunctionImplR0 : public FunctionBaseR0<Ret>
    {
    public:
        typedef Ret ( *SlotFunction )();

        FunctionImplR0( SlotFunction fun ):	m_Fun( fun ) {}

        virtual Ret operator()()
        {
            return ( *m_Fun )();
        };
    protected:
        SlotFunction  m_Fun;
    };

    template <class Functor, typename Ret>
    class FunctorR0 : public FunctionBaseR0<Ret>
    {
    public:
        FunctorR0( Functor fun ):	m_Fun( fun ) {}

        virtual Ret operator()()
        {
            return m_Fun();
        };
    protected:
        Functor  m_Fun;
    };

    template <class T, typename Ret >
    class FunctionMemberR0 : public FunctionBaseR0<Ret>
    {
    public:
        typedef Ret ( T::*Fun )();

        FunctionMemberR0( T* pHolder, Fun fun ): m_pHolder( pHolder ), m_Fun( fun ) {}

        virtual Ret operator()()
        {
            return ( m_pHolder->*m_Fun )();
        };

    protected:
        T*   m_pHolder;
        Fun      m_Fun;
    };

    // v1
    template < typename Ret, typename Arg1>
    class FunctionImplR1 : public FunctionBaseR1<Ret, Arg1>
    {
    public:
        typedef Ret ( *SlotFunction )( Arg1 );

        FunctionImplR1( SlotFunction fun ):	m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1 )
        {
            return m_Fun( v1 );
        };
    protected:
        SlotFunction  m_Fun;
    };

    template <class Functor, typename Ret, typename Arg1>
    class FunctorR1 : public FunctionBaseR1<Ret, Arg1>
    {
    public:
        FunctorR1( Functor fun ):	m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1 )
        {
            return m_Fun( v1 );
        };
    protected:
        Functor  m_Fun;
    };

    template <class T, typename Ret, typename Arg1>
    class FunctionMemberR1 : public FunctionBaseR1<Ret, Arg1>
    {
    public:
        typedef Ret ( T::*Fun )( Arg1 v1 );

        FunctionMemberR1( T* pHolder, Fun fun ): m_pHolder( pHolder ), m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1 )
        {
            return ( m_pHolder->*m_Fun )( v1 );
        };

    protected:
        T*   m_pHolder;
        Fun      m_Fun;
    };

    // v2
    template < typename Ret, typename Arg1, typename Arg2>
    class FunctionImplR2 : public FunctionBaseR2<Ret, Arg1, Arg2>
    {
    public:
        typedef Ret ( *SlotFunction )( Arg1, Arg2 );

        FunctionImplR2( SlotFunction fun ):	m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1, Arg2 v2 )
        {
            return ( *m_Fun )( v1, v2 );
        };
    protected:
        SlotFunction  m_Fun;
    };

    template <class Functor, typename Ret, typename Arg1, typename Arg2 >
    class FunctorR2 : public FunctionBaseR2<Ret, Arg1, Arg2>
    {
    public:
        FunctorR2( Functor fun ):	m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1, Arg2 v2 )
        {
            return m_Fun( v1, v2 );
        };
    protected:
        Functor  m_Fun;
    };

    template <class T, typename Ret, typename Arg1, typename Arg2 >
    class FunctionMemberR2 : public FunctionBaseR2<Ret, Arg1, Arg2>
    {
    public:
        typedef Ret ( T::*Fun )( Arg1 v1, Arg2 v2 );

        FunctionMemberR2( T* pHolder, Fun fun ): m_pHolder( pHolder ), m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1, Arg2 v2 )
        {
            return ( m_pHolder->*m_Fun )( v1, v2 );
        };

    protected:
        T*   m_pHolder;
        Fun      m_Fun;
    };

    // v3
    template < typename Ret, typename Arg1, typename Arg2, typename Arg3>
    class FunctionImplR3 : public FunctionBaseR3<Ret, Arg1, Arg2, Arg3>
    {
    public:
        typedef Ret ( *SlotFunction )( Arg1, Arg2, Arg3 );

        FunctionImplR3( SlotFunction fun ):	m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1, Arg2 v2, Arg3 v3 )
        {
            return ( *m_Fun )( v1, v2, v3 );
        };
    protected:
        SlotFunction  m_Fun;
    };

    template <class Functor, typename Ret, typename Arg1, typename Arg2, typename Arg3 >
    class FunctorR3 : public FunctionBaseR3<Ret, Arg1, Arg2, Arg3>
    {
    public:
        FunctorR3( Functor fun ):	m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1, Arg2 v2, Arg3 v3 )
        {
            return m_Fun( v1, v2, v3 );
        };
    protected:
        Functor  m_Fun;
    };

    template <class T, typename Ret, typename Arg1, typename Arg2, typename Arg3>
    class FunctionMemberR3 : public FunctionBaseR3<Ret, Arg1, Arg2, Arg3>
    {
    public:
        typedef Ret ( T::*Fun )( Arg1 v1, Arg2 v2, Arg3 v3 );

        FunctionMemberR3( T* pHolder, Fun fun ): m_pHolder( pHolder ), m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1, Arg2 v2, Arg3 v3 )
        {
            return ( m_pHolder->*m_Fun )( v1, v2, v3 );
        };

    protected:
        T*   m_pHolder;
        Fun      m_Fun;
    };

    // v4
    template <typename Ret, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    class FunctionImplR4 : public FunctionBaseR4<Ret, Arg1, Arg2, Arg3, Arg4>
    {
    public:
        typedef Ret ( *SlotFunction )( Arg1, Arg2, Arg3, Arg4 );

        FunctionImplR4( SlotFunction fun ):	m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 )
        {
            return ( *m_Fun )( v1, v2, v3, v4 );
        };
    protected:
        SlotFunction  m_Fun;
    };

    template <class Functor, typename Ret, typename Arg1, typename Arg2, typename Arg3, typename Arg4 >
    class FunctorR4 : public FunctionBaseR4<Ret, Arg1, Arg2, Arg3, Arg4>
    {
    public:
        FunctorR4( Functor fun ):	m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 )
        {
            return m_Fun( v1, v2, v3, v4 );
        };
    protected:
        Functor  m_Fun;
    };

    template <class T, typename Ret, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    class FunctionMemberR4 : public FunctionBaseR4<Ret, Arg1, Arg2, Arg3, Arg4>
    {
    public:
        typedef Ret ( T::*Fun )( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 );

        FunctionMemberR4( T* pHolder, Fun fun ): m_pHolder( pHolder ), m_Fun( fun ) {}

        virtual Ret operator()( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 )
        {
            return ( m_pHolder->*m_Fun )( v1, v2, v3, v4 );
        };

    protected:
        T*   m_pHolder;
        Fun      m_Fun;
    };


    //////////////////////////////////////////////////////////////////////////////////////////
    //                    void-return  Function
    //////////////////////////////////////////////////////////////////////////////////////////

    class Function0
    {
    public:
        typedef Function0                     Function;
        typedef FunctionBase0             FunctionBase;
        typedef RefPtr< FunctionBase > FunctionBasePtr;

        // Function operator().
        void operator()() const
        {
            ( *m_pFunBase )();  // call the bound function
        }

        typedef void ( *SlotFunction )();

        // default constructor
        Function0() {}

        // construct from a free function
        Function0( SlotFunction f )
        {
            m_pFunBase = H_NEW FunctionImpl0( f );
        }

        // construct from a member function and a pointer to the target object.
        template <class T>
        Function0( T* pHolder, void ( T::*f )() )
        {
            m_pFunBase = H_NEW FunctionMember0<T>( pHolder, f );
        }

        // Functor constructor
        template <typename Functor>
        Function0( const Functor& f )
        {
            m_pFunBase = H_NEW Functor0<Functor>( f );
        }

        // copy functor
        Function0( const Function& src ) : m_pFunBase( src.m_pFunBase ) {}
        void operator=( const Function& src )
        {
            m_pFunBase = src.m_pFunBase;
        }

        // equal operator
        inline bool operator==( const Function& oth )const
        {
            return getFunctionBase() == oth.getFunctionBase();
        }
        inline bool operator!=( const Function& oth )const
        {
            return getFunctionBase() != oth.getFunctionBase();
        }

        // Gets pointer to function base created by the class.
        inline FunctionBase* getFunctionBase()const
        {
            return m_pFunBase.getPointer();
        }

    protected:
        FunctionBasePtr m_pFunBase;
    };

    template < typename Arg1>
    class Function1
    {
    public:
        typedef Arg1                          Arg1Type;
        typedef Function1< Arg1>              Function;
        typedef FunctionBase1<Arg1>       FunctionBase;
        typedef RefPtr< FunctionBase > FunctionBasePtr;

        void operator()( Arg1 v1 ) const
        {
            ( *m_pFunBase )( v1 );  // call the bound function
        }

        typedef void ( *SlotFunction )( Arg1 );

        // default constructor
        Function1() {}

        //! construct from a free function
        Function1( SlotFunction f )
        {
            m_pFunBase = H_NEW FunctionImpl1<Arg1>( f );
        }

        //! construct from a member function and a pointer to the target object.
        template <class T>
        Function1( T* pHolder, void ( T::*f )( Arg1 ) )
        {
            m_pFunBase = H_NEW FunctionMember1<T, Arg1>( pHolder, f );
        }

        // Functor constructor
        template <typename Functor>
        Function1( const Functor& f )
        {
            m_pFunBase = H_NEW Functor1<Functor, Arg1>( f );
        }

        // copy functor
        Function1( const Function1& src ) : m_pFunBase( src.m_pFunBase ) {}
        inline void operator=( const Function1& src )
        {
            m_pFunBase = src.m_pFunBase;
        }

        // equal operator
        inline bool operator==( const Function& oth )const
        {
            return getFunctionBase() == oth.getFunctionBase();
        }
        inline bool operator!=( const Function& oth )const
        {
            return getFunctionBase() != oth.getFunctionBase();
        }

        // Gets pointer to function base created by the class.
        inline FunctionBase* getFunctionBase()const
        {
            return m_pFunBase.getPointer();
        }

    protected:
        FunctionBasePtr m_pFunBase;
    };

    template < typename Arg1, typename Arg2>
    class Function2
    {
    public:
        typedef Arg1                           Arg1Type;
        typedef Arg2                           Arg2Type;
        typedef Function2< Arg1, Arg2>         Function;
        typedef FunctionBase2<Arg1, Arg2 >  FunctionBase;
        typedef RefPtr< FunctionBase > FunctionBasePtr;

        void operator()( Arg1 v1, Arg2 v2 ) const
        {
            ( *m_pFunBase )( v1, v2 );  // call the bound function
        }

        typedef void ( *SlotFunction )( Arg1, Arg2 );

        // default constructor
        Function2() {}

        //! construct from a free function
        Function2( SlotFunction f )
        {
            m_pFunBase = H_NEW FunctionImpl2<Arg1, Arg2 >( f );
        }

        //! construct from a member function and a pointer to the target object.
        template <class T>
        Function2( T* pHolder, void ( T::*f )( Arg1, Arg2 ) )
        {
            m_pFunBase = H_NEW FunctionMember2<T, Arg1, Arg2 >( pHolder, f );
        }

        // Functor constructor
        template <typename Functor>
        Function2( const Functor& f )
        {
            m_pFunBase = H_NEW Functor2<Functor, Arg1, Arg2 >( f );
        }

        // copy functor
        Function2( const Function2& src ) : m_pFunBase( src.m_pFunBase ) {}
        inline void operator=( const Function2& src )
        {
            m_pFunBase = src.m_pFunBase;
        }

        // equal operator
        inline bool operator==( const Function& oth )const
        {
            return getFunctionBase() == oth.getFunctionBase();
        }
        inline bool operator!=( const Function& oth )const
        {
            return getFunctionBase() != oth.getFunctionBase();
        }

        // Gets pointer to function base created by the class.
        inline FunctionBase* getFunctionBase()const
        {
            return m_pFunBase.getPointer();
        }

    protected:
        FunctionBasePtr m_pFunBase;
    };

    template < typename Arg1, typename Arg2, typename Arg3 >
    class Function3 : public Object
    {
    public:
        typedef Arg1                                 Arg1Type;
        typedef Arg2                                 Arg2Type;
        typedef Arg3                                 Arg3Type;
        typedef Function3< Arg1, Arg2, Arg3>         Function;
        typedef FunctionBase3<Arg1, Arg2, Arg3 >  FunctionBase;
        typedef RefPtr< FunctionBase >        FunctionBasePtr;

        void operator()( Arg1 v1, Arg2 v2, Arg3 v3 ) const
        {
            ( *m_pFunBase )( v1, v2, v3 );  // call the bound function
        }

        typedef void ( *SlotFunction )( Arg1, Arg2, Arg3 );

        // default constructor
        Function3() {}

        //! construct from a free function
        Function3( SlotFunction f )
        {
            m_pFunBase = H_NEW FunctionImpl3<Arg1, Arg2, Arg3 >( f );
        }

        //! construct from a member function and a pointer to the target object.
        template <class T>
        Function3( T* pHolder, void ( T::*f )( Arg1, Arg2, Arg3 ) )
        {
            m_pFunBase = H_NEW FunctionMember3<T, Arg1, Arg2, Arg3 >( pHolder, f );
        }

        // Functor constructor
        template <typename Functor>
        Function3( const Functor& f )
        {
            m_pFunBase = H_NEW Functor3<Functor, Arg1, Arg2, Arg3>( f );
        }

        // copy functor
        Function3( const Function3& src ) : m_pFunBase( src.m_pFunBase ) {}
        void operator=( const Function3& src )
        {
            m_pFunBase = src.m_pFunBase;
        }

        // equal operator
        inline bool operator==( const Function& oth )const
        {
            return getFunctionBase() == oth.getFunctionBase();
        }
        inline bool operator!=( const Function& oth )const
        {
            return getFunctionBase() != oth.getFunctionBase();
        }

        // Gets pointer to function base created by the class.
        inline FunctionBase* getFunctionBase()const
        {
            return m_pFunBase.getPointer();
        }

    protected:
        FunctionBasePtr m_pFunBase;
    };

    template < typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    class Function4 : public Object
    {
    public:
        typedef Arg1                                       Arg1Type;
        typedef Arg2                                       Arg2Type;
        typedef Arg3                                       Arg3Type;
        typedef Arg4                                       Arg4Type;
        typedef Function4< Arg1, Arg2, Arg3, Arg4>          Function;
        typedef FunctionBase4<Arg1, Arg2, Arg3, Arg4 >  FunctionBase;
        typedef RefPtr< FunctionBase >              FunctionBasePtr;

        void operator()( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 ) const
        {
            ( *m_pFunBase )( v1, v2, v3, v4 );  // call the bound function
        }

        typedef void ( *SlotFunction )( Arg1, Arg2, Arg3, Arg4 );

        // default constructor
        Function4() {}

        //! construct from a free function
        Function4( SlotFunction f )
        {
            m_pFunBase = H_NEW FunctionImpl4<Arg1, Arg2, Arg3, Arg4 >( f );
        }

        //! construct from a member function and a pointer to the target object.
        template <class T>
        Function4( T* pHolder, void ( T::*f )( Arg1, Arg2, Arg3, Arg4 ) )
        {
            m_pFunBase = H_NEW FunctionMember4<T, Arg1, Arg2, Arg3, Arg4 >( pHolder, f );
        }

        // Functor constructor
        template <typename Functor>
        Function4( const Functor& f )
        {
            m_pFunBase = H_NEW Functor4<Functor, Arg1, Arg2, Arg3, Arg4 >( f );
        }

        // copy functor
        Function4( const Function4& src ) : m_pFunBase( src.m_pFunBase ) {}
        void operator=( const Function4& src )
        {
            m_pFunBase = src.m_pFunBase;
        }

        // equal operator
        inline bool operator==( const Function& oth )const
        {
            return getFunctionBase() == oth.getFunctionBase();
        }
        inline bool operator!=( const Function& oth )const
        {
            return getFunctionBase() != oth.getFunctionBase();
        }

        // Gets pointer to function base created by the class.
        inline FunctionBase* getFunctionBase()const
        {
            return m_pFunBase.getPointer();
        }

    protected:
        FunctionBasePtr m_pFunBase;
    };







    //////////////////////////////////////////////////////////////////////////////////////////
    //                     Typed return  Function
    //////////////////////////////////////////////////////////////////////////////////////////
    template <typename Ret>
    class FunctionR0
    {
    public:
        typedef FunctionR0< Ret >             Function;
        typedef FunctionBaseR0< Ret >     FunctionBase;
        typedef RefPtr< FunctionBase > FunctionBasePtr;

        // Function operator().
        Ret operator()() const
        {
            return ( *m_pFunBase )();  // call the bound function
        }

        typedef Ret ( *SlotFunction )();

        // default constructor
        FunctionR0() {}

        // construct from a free function
        FunctionR0( SlotFunction f )
        {
            m_pFunBase = H_NEW FunctionImplR0<Ret>( f );
        }

        // construct from a member function and a pointer to the target object.
        template <class T>
        FunctionR0( T* pHolder, Ret ( T::*f )() )
        {
            m_pFunBase = H_NEW FunctionMemberR0<T, Ret>( pHolder, f );
        }

        // Functor constructor
        template <typename Functor>
        FunctionR0( const Functor& f )
        {
            m_pFunBase = H_NEW FunctorR0<Functor, Ret>( f );
        }

        // copy functor
        FunctionR0( const FunctionR0& src ) : m_pFunBase( src.m_pFunBase ) {}
        void operator=( const FunctionR0& src )
        {
            m_pFunBase = src.m_pFunBase;
        }

        // equal operator
        inline bool operator==( const Function& oth )const
        {
            return getFunctionBase() == oth.getFunctionBase();
        }
        inline bool operator!=( const Function& oth )const
        {
            return getFunctionBase() != oth.getFunctionBase();
        }

        // Gets pointer to function base created by the class.
        inline FunctionBase* getFunctionBase()const
        {
            return m_pFunBase.getPointer();
        }

    protected:
        FunctionBasePtr m_pFunBase;
    };

    template <typename Ret, typename Arg1>
    class FunctionR1
    {
    public:
        typedef FunctionR1< Ret, Arg1 >             Function;
        typedef FunctionBaseR1<Ret, Arg1 >      FunctionBase;
        typedef RefPtr< FunctionBase >       FunctionBasePtr;

        Ret operator()( Arg1 v1 ) const
        {
            return ( *m_pFunBase )( v1 );  // call the bound function
        }

        typedef Ret ( *SlotFunction )( Arg1 );

        // default constructor
        FunctionR1() {}

        //! construct from a free function
        FunctionR1( SlotFunction f )
        {
            m_pFunBase = H_NEW FunctionImplR1<Ret, Arg1>( f );
        }

        //! construct from a member function and a pointer to the target object.
        template <class T>
        FunctionR1( T* pHolder, Ret ( T::*f )( Arg1 ) )
        {
            m_pFunBase = H_NEW FunctionMemberR1<T, Ret, Arg1>( pHolder, f );
        }

        // Functor constructor
        template <typename Functor>
        FunctionR1( const Functor& f )
        {
            m_pFunBase = H_NEW FunctorR1<Functor, Ret, Arg1>( f );
        }

        // copy functor
        FunctionR1( const FunctionR1& src ) : m_pFunBase( src.m_pFunBase ) {}
        void operator=( const FunctionR1& src )
        {
            m_pFunBase = src.m_pFunBase;
        }

        // equal operator
        inline bool operator==( const Function& oth )const
        {
            return getFunctionBase() == oth.getFunctionBase();
        }
        inline bool operator!=( const Function& oth )const
        {
            return getFunctionBase() != oth.getFunctionBase();
        }

        // Gets pointer to function base created by the class.
        inline FunctionBase* getFunctionBase()const
        {
            return m_pFunBase.getPointer();
        }

    protected:
        FunctionBasePtr m_pFunBase;
    };

    template <typename Ret, typename Arg1, typename Arg2>
    class FunctionR2
    {
    public:
        typedef FunctionR2< Ret, Arg1, Arg2 >           Function;
        typedef FunctionBaseR2<Ret, Arg1, Arg2 >    FunctionBase;
        typedef RefPtr< FunctionBase >          FunctionBasePtr;

        Ret operator()( Arg1 v1, Arg2 v2 ) const
        {
            return ( *m_pFunBase )( v1, v2 );  // call the bound function
        }

        typedef Ret ( *SlotFunction )( Arg1, Arg2 );

        // default constructor
        FunctionR2() {}

        //! construct from a free function
        FunctionR2( SlotFunction f )
        {
            m_pFunBase = H_NEW FunctionImplR2<Ret, Arg1, Arg2 >( f );
        }

        //! construct from a member function and a pointer to the target object.
        template <class T>
        FunctionR2( T* pHolder, Ret ( T::*f )( Arg1, Arg2 ) )
        {
            m_pFunBase = H_NEW FunctionMemberR2<T, Ret, Arg1, Arg2 >( pHolder, f );
        }

        // Functor constructor
        template <typename Functor>
        FunctionR2( const Functor& f )
        {
            m_pFunBase = H_NEW FunctorR2<Functor, Ret, Arg1, Arg2 >( f );
        }

        // copy functor
        FunctionR2( const FunctionR2& src ) : m_pFunBase( src.m_pFunBase ) {}
        void operator=( const FunctionR2& src )
        {
            m_pFunBase = src.m_pFunBase;
        }

        // equal operator
        inline bool operator==( const Function& oth )const
        {
            return getFunctionBase() == oth.getFunctionBase();
        }
        inline bool operator!=( const Function& oth )const
        {
            return getFunctionBase() != oth.getFunctionBase();
        }

        // Gets pointer to function base created by the class.
        inline FunctionBase* getFunctionBase()const
        {
            return m_pFunBase.getPointer();
        }

    protected:
        FunctionBasePtr m_pFunBase;
    };

    template <typename Ret, typename Arg1, typename Arg2, typename Arg3 >
    class FunctionR3
    {
    public:
        typedef FunctionR3< Ret, Arg1, Arg2, Arg3 >           Function;
        typedef FunctionBaseR3<Ret, Arg1, Arg2, Arg3 >    FunctionBase;
        typedef RefPtr<FunctionBase >                 FunctionBasePtr;

        Ret operator()( Arg1 v1, Arg2 v2, Arg3 v3 ) const
        {
            return ( *m_pFunBase )( v1, v2, v3 );  // call the bound function
        }

        typedef Ret ( *SlotFunction )( Arg1, Arg2, Arg3 );

        // default constructor
        FunctionR3() {}

        //! construct from a free function
        FunctionR3( SlotFunction f )
        {
            m_pFunBase = H_NEW FunctionImplR3<Ret, Arg1, Arg2, Arg3 >( f );
        }

        //! construct from a member function and a pointer to the target object.
        template <class T>
        FunctionR3( T* pHolder, Ret ( T::*f )( Arg1, Arg2, Arg3 ) )
        {
            m_pFunBase = H_NEW FunctionMemberR3<T, Ret, Arg1, Arg2, Arg3 >( pHolder, f );
        }

        // Functor constructor
        template <typename Functor>
        FunctionR3( const Functor& f )
        {
            m_pFunBase = H_NEW FunctorR3<Functor, Ret, Arg1, Arg2, Arg3>( f );
        }

        // copy functor
        FunctionR3( const FunctionR3& src ) : m_pFunBase( src.m_pFunBase ) {}
        void operator=( const FunctionR3& src )
        {
            m_pFunBase = src.m_pFunBase;
        }

        // equal operator
        inline bool operator==( const Function& oth )const
        {
            return getFunctionBase() == oth.getFunctionBase();
        }
        inline bool operator!=( const Function& oth )const
        {
            return getFunctionBase() != oth.getFunctionBase();
        }

        // Gets pointer to function base created by the class.
        inline FunctionBase* getFunctionBase()const
        {
            return m_pFunBase.getPointer();
        }

    protected:
        FunctionBasePtr m_pFunBase;
    };

    template <typename Ret, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    class FunctionR4
    {
    public:
        typedef FunctionR4< Ret, Arg1, Arg2, Arg3, Arg4 >           Function;
        typedef FunctionBaseR4<Ret, Arg1, Arg2, Arg3, Arg4 >    FunctionBase;
        typedef RefPtr< FunctionBase >                      FunctionBasePtr;

        Ret operator()( Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4 ) const
        {
            return ( *m_pFunBase )( v1, v2, v3, v4 );  // call the bound function
        }

        typedef Ret ( *SlotFunction )( Arg1, Arg2, Arg3, Arg4 );

        // default constructor
        FunctionR4() {}

        //! construct from a free function
        FunctionR4( SlotFunction f )
        {
            m_pFunBase = H_NEW FunctionImplR4<Ret, Arg1, Arg2, Arg3, Arg4 >( f );
        }

        //! construct from a member function and a pointer to the target object.
        template <class T>
        FunctionR4( T* pHolder, Ret ( T::*f )( Arg1, Arg2, Arg3, Arg4 ) )
        {
            m_pFunBase = H_NEW FunctionMemberR4<T, Ret, Arg1, Arg2, Arg3, Arg4 >( pHolder, f );
        }

        // Functor constructor
        template <typename Functor>
        FunctionR4( const Functor& f )
        {
            m_pFunBase = H_NEW FunctorR4<Functor, Ret, Arg1, Arg2, Arg3, Arg4 >( f );
        }

        // copy functor
        FunctionR4( const FunctionR4& src ) : m_pFunBase( src.m_pFunBase ) {}
        void operator=( const FunctionR4& src )
        {
            m_pFunBase = src.m_pFunBase;
        }

        // equal operator
        inline bool operator==( const Function& oth )const
        {
            return getFunctionBase() == oth.getFunctionBase();
        }
        inline bool operator!=( const Function& oth )const
        {
            return getFunctionBase() != oth.getFunctionBase();
        }

        // Gets pointer to function base created by the class.
        inline FunctionBase* getFunctionBase()const
        {
            return m_pFunBase.getPointer();
        }

    protected:
        FunctionBasePtr m_pFunBase;
    };

    //////////////////////////////////////////////////////////////////////////////////
    //  Following macros provides simple way to add  set/remove/call methods on    //
    //  function to class.                                                         //
    //////////////////////////////////////////////////////////////////////////////////


    /** Macro that include eventlistenerlist in header file. */
#define H_FUNCTIOH_HEADER( FunctionName, FunctionType )						     \
    \
public:																			 \
    \
    void set##FunctionName(FunctionType func )									 \
    {																			 \
        m_v##FunctionName = func;								    		     \
    }																			 \
    \
protected:																		 \
    irr::FunctionType  m_##FunctionName;



    // Macro that onSocketEventT function with one parameter
#define H_NOTIFY_FUNCTIOH_0( FunctionName )		  		         \
    m_##FunctionName();

    // Macro that onSocketEventT function with 1 parameter
#define H_NOTIFY_FUNCTIOH_1( FunctionName, v1 )				     \
    m_##FunctionName( v1 );

    // Macro that onSocketEventT function with 1 parameter
#define H_NOTIFY_FUNCTIOH_2( FunctionName, v1, v2 )			     \
    m_##FunctionName( v1, v2 );

    // Macro that onSocketEventT function with 1 parameter
#define H_NOTIFY_FUNCTIOH_3( FunctionName, v1, v2, v3 )		     \
    m_##FunctionName( v1, v2, v3 );

    // Macro that onSocketEventT function with 1 parameter
#define H_NOTIFY_FUNCTIOH_4( FunctionName, v1, v2, v3, v4 )	     \
    m_##FunctionName( v1, v2, v3, v4 );

};//namespace

#endif//endoffile

