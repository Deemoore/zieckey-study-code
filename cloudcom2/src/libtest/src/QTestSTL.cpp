#include "libtest/include/QLibTestPrerequisits.h"
#include "libtest/include/QTestObject.h"
using namespace osl;

namespace
{
    class TestStl : public LibTest::ITestObject
    {

        void testAll();
        const char* getCommand();
        const char* getDesc();
        void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );


        void test_stl_swap();
        void test_ex_function_object();
        void test_ex_algorithm();
        void test_ex_algorithm_ex();
        void test_vector_operator();
        void test_stl_sgi_ex();
    };

    const char* TestStl::getCommand()
    {
        return "test_stl";
    }

    const char* TestStl::getDesc()
    {
        return "test_stl";
    }

    void TestStl::testAll()
    {
        test_stl_swap();
        test_ex_function_object();
        test_ex_algorithm();
        test_ex_algorithm_ex();
        test_vector_operator();
        test_stl_sgi_ex();
    }

    void TestStl::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        //osl::Object* p = H_NEW osl::Object;

        testAll();
    }

    void TestStl::test_stl_swap()
    {
        Vector<int> vecInt;
        U32Vector   vecU32;
        List<int>  lstInt;
        U64List     lstU64;
        Set<int>   setInt;
        F32Set      setF32;

        Map<int, int>   mapInt;
        HashMap<int, int> hashMapInt;
        MultiMap<int, int> multiMapInt;


        for ( int i = 0; i < 10; i++ )
        {
            vecInt.push_back( i );
            vecU32.push_back( i );
            lstInt.push_back( i );
            lstU64.push_back( i );
            setInt.insert( i );
            setF32.insert( i );

            mapInt.insert( std::make_pair( i, i + 1000 ) );
            hashMapInt.insert( std::make_pair( i, i + 1000 ) );
            multiMapInt.insert( std::make_pair( i, i + 1000 ) );

        }

        Vector<int> vecInt2;
        U32Vector   vecU322;
        List<int>  lstInt2;
        U64List     lstU642;
        Set<int>   setInt2;
        F32Set      setF322;
        Map<int, int>   mapInt2;
        HashMap<int, int> hashMapInt2;
        MultiMap<int, int> multiMapInt2;

        swap( vecInt , vecInt2 );
        swap( vecU32 , vecU322 );
        swap( lstInt , lstInt2 );
        swap( lstU64 , lstU642 );
        swap( setInt , setInt2 );
        swap( setF32 , setF322 );

        swap( mapInt , mapInt2 );
        swap( hashMapInt , hashMapInt2 );
        swap( multiMapInt , multiMapInt2 );

    }


    class CountClass : public osl::Object
    {
        static int s_nCount;
    public:
        static const int& nCount;
        CountClass()
        {
            s_nCount++;
        }
        CountClass( const CountClass& )
        {
            s_nCount++;
        }
        ~CountClass()
        {
            s_nCount--;
        }
    };
    typedef osl::RefPtr<CountClass> CountClassPtr;
    int CountClass::s_nCount = 0;
    const int& CountClass::nCount = CountClass::s_nCount;

    void TestStl::test_ex_function_object()
    {

        using namespace std;
        DeletePointer()( H_NEW CountClass );
        H_ASSERT( 0 == CountClass::nCount );

        DeletePointerArray()( new CountClass[3] );
        H_ASSERT( 0 == CountClass::nCount );

        {
            CountClass* p1 = H_NEW CountClass;
            p1->ref();
            UnrefPointer()( p1 );
            H_ASSERT( 0 == CountClass::nCount );

//             CountClassPtr ptr = H_NEW CountClass;
//             UnrefPointer()( ptr );
//             H_ASSERT( 0 == CountClass::nCount );
        }

        {
            std::pair<int, CountClass*> p;
            p.second = H_NEW CountClass;
            p.second->ref();

            UnrefPairedPointer()( p );
            H_ASSERT( 0 == CountClass::nCount );

//             std::pair<int,CountClassPtr> p2;
//             p2.second = H_NEW CountClass;
//             UnrefPairedPointer()( p2 );
//             H_ASSERT( 0 == CountClass::nCount );
        }

        {
            std::pair<int, CountClass*> p;
            p.second = H_NEW CountClass;
            DeletePairedPointer()( p );
            H_ASSERT( 0 == CountClass::nCount );

            std::pair<int, CountClass*> p2;
            p2.second = new CountClass[4];
            DeletePairedPointerArray()( p2 );
            H_ASSERT( 0 == CountClass::nCount );
        }


        {
            DeletePointerFunctor<CountClass>()( H_NEW CountClass );
            H_ASSERT( 0 == CountClass::nCount );
            DeleteArrayFunctor<CountClass>()( new CountClass[7] );
            H_ASSERT( 0 == CountClass::nCount );
        }

        {
            int X = 98765432;
            int *pX = CopyNewPointer()( &X );
            H_ASSERT( *pX == X );

            DeletePointer()( pX );
        }



    }


    template<class C , class D, size_t Num, class T>
    void test_erase_element( D ( &arg )[Num] , const T& val )
    {
        C c;
        c.assign( arg , arg + Num );

        H_ASSERT( is_contain( c , val ) );
        H_ASSERT( erase_element( c , val ) );
        H_ASSERT( 9 == c.size() );
        H_ASSERT( !is_contain( c , val ) );
        H_ASSERT( !erase_element( c , val ) );
    }


    template<class C>
    void test_erase_delete_element()
    {
        {
            C vec;

            for ( int i = 0 ; i < 10 ; i++ )
            {
                vec.push_back( H_NEW CountClass );
            }

            H_ASSERT( 10 == CountClass::nCount );

            typename C::iterator iter = vec.begin();
            advance( iter , 5 );
            CountClass* pFindValue =  *iter;
            (void)pFindValue;

            H_ASSERT( erase_delete_element( vec , pFindValue ) );
            H_ASSERT( 9 == vec.size() );
            H_ASSERT( 9 == CountClass::nCount );
            H_ASSERT( !erase_element( vec , pFindValue ) );

            clear_delete_elements( vec );

            H_ASSERT( 0 == vec.size() );
            H_ASSERT( 0 == CountClass::nCount );
            H_ASSERT( !erase_element( vec , pFindValue ) );

            H_ASSERT( vec.empty() );
        }
        {
            C vec;

            for ( int i = 0 ; i < 10 ; i++ )
            {
                CountClass* pTemp = H_NEW CountClass;

                pTemp->ref();
                vec.push_back( pTemp );
            }

            H_ASSERT( 10 == CountClass::nCount );

            typename C::iterator iter = vec.begin();
            advance( iter , 5 );
            CountClass* pFindValue =  *iter;
            (void)pFindValue;

            H_ASSERT( erase_unref_element( vec , pFindValue ) );
            H_ASSERT( 9 == vec.size() );
            H_ASSERT( 9 == CountClass::nCount );
            H_ASSERT( !erase_element( vec , pFindValue ) );

            clear_unref_elements( vec );

            H_ASSERT( 0 == vec.size() );
            H_ASSERT( 0 == CountClass::nCount );
            H_ASSERT( !erase_element( vec , pFindValue ) );

            H_ASSERT( vec.empty() );
        }
    }


    void TestStl::test_ex_algorithm()
    {
        {
            //is_contain
            //erase_element
            int nTempArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            test_erase_element< Vector<int> >( nTempArray , 6 );
            test_erase_element< List<int> >( nTempArray , 6 );
        }
        // erase_delete_element
        // erase_unref_element
        // clear_delete_elements
        // clear_unref_elements
        // erase_element
        test_erase_delete_element< Vector<CountClass*> >( );
        test_erase_delete_element< List<CountClass*> >( );

        {
            Map<int , CountClass* > m;

            for ( int i = 0 ; i < 10; i++ )
            {
                CountClass* pTmp = H_NEW CountClass;
                pTmp->ref();
                m[i] = pTmp;
            }

            H_ASSERT( NULL != get_if_there( m , 4 , static_cast<CountClass*>( 0 ) ) );
            H_ASSERT( NULL == get_if_there( m , 14 , static_cast<CountClass*>( 0 )  ) );

            H_ASSERT( is_in_map( m , 5 ) );
            H_ASSERT( !is_in_map( m , 15 ) );

            H_ASSERT( NULL != get_ptr_in_map( m , 4 ) );
            H_ASSERT( NULL == get_ptr_in_map( m , 14 ) );

            H_ASSERT( 10 == CountClass::nCount );
            H_ASSERT( erase_unref_second_element( m , 6 ) );
            H_ASSERT( 9 == m.size() );
            H_ASSERT( 9 == CountClass::nCount );
            H_ASSERT( !erase_unref_second_element( m , 6 ) );

            clear_unref_second_elements( m );
            H_ASSERT( 0 == CountClass::nCount );
            H_ASSERT( m.empty() );

        }

        {
            Map<int , CountClass* > m;

            for ( int i = 0 ; i < 10; i++ )
            {
                m[i] = H_NEW CountClass;
            }

            H_ASSERT( 10 == CountClass::nCount );
            H_ASSERT( erase_delete_second_element( m , 6 ) );
            H_ASSERT( 9 == m.size() );
            H_ASSERT( 9 == CountClass::nCount );
            H_ASSERT( !erase_delete_second_element( m , 6 ) );

            clear_delete_second_elements( m );
            H_ASSERT( 0 == CountClass::nCount );
            H_ASSERT( m.empty() );

        }



    }

    void TestStl::test_vector_operator()
    {
        //vector_replace_with_last;
        //vector_append

    }


    struct TempOpt
	{
		int& nSum;
		TempOpt( int& arg ): nSum( arg )
		{
		}
		int operator()( int n )
		{
			nSum += n;
			return 2 * n;
		}
	};



    // h_for_n
    // h_copy_n
    // h_transform_n
    // for_each_process2nd
    // for_each_process1st
    void TestStl::test_ex_algorithm_ex()
    {
        int nTemp[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        int nSum = 0;
        osl::h_for_n( nTemp , 7 , TempOpt( nSum ) );
        H_ASSERT( 28 == nSum );

        nSum = 0;

        int nResult[10] = {};
        h_transform_n( nTemp , 9 , nResult , TempOpt( nSum ) );
        H_ASSERT( 45 == nSum );

        const int nDest[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18 , 0 };
        H_ASSERT( 0 == memcmp( nResult , nDest , sizeof( nDest ) ) );
        (void)nDest;

        h_copy_n( nTemp , 10 , nResult );
        H_ASSERT( 0 == memcmp( nTemp , nResult , sizeof( nResult ) ) );













    }

    // h_select1st
    // h_select2nd
    // h_compose1
    // h_compose2
    // h_bind1st
    // h_bind2nd
    void TestStl::test_stl_sgi_ex()
    {






    }



}





CREATE_FUNCTION( TestStl );












