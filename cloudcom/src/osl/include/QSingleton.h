#pragma  once



namespace osl
{

    // End SJS additions
    /** Template class for creating single-instance global classes.
    */
    template <typename T> class Singleton
    {

    public:
        static T& getSingleton( void )
        {
            //assert( ms_Singleton );
            return ( *ms_Singleton );
        }
        static T* getSingletonPtr( void )
        {
            return ms_Singleton;
        }

    protected:
        Singleton( void )
        {
            assert( NULL == ms_Singleton );

            ms_Singleton = static_cast< T* >( this );

        }
        ~Singleton( void )
        {
            //assert( ms_Singleton );
            ms_Singleton = 0;
        }

    protected:
        static T* ms_Singleton;
    };


};//namespace

