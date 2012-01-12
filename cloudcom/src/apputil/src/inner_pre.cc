#include "apputil/include/inner_pre.h"


namespace aut
{

    static bool s_bInitialized = false;

    //----------------------------------------------
    bool isAppUtilInitialized()
    {
        return s_bInitialized;
    }
    //----------------------------------------------
    bool initializeAppUtil()
    {
        // initialize.
        if ( !osl::initializeOSLib() )
        {
            return false;
        }

        if ( !net::initializeNet() )
        {
            osl::uninitializeOSLib();
            return false;
        }
        
        if ( s_bInitialized )
        {
            return true;
        }

        s_bInitialized = true;

        return true;
    }
    //----------------------------------------------
    void uninitializeAppUtil()
    {
        if ( !s_bInitialized )
        {
            return;
        }

        s_bInitialized = false;

    }

};

