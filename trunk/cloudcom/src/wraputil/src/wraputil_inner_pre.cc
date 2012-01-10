#include "wraputil/include/wraputil_inner_pre.h"

namespace wu
{
    namespace
    {
        class AutoInitModule
        {
        public:
            AutoInitModule()
            {
                initializeWrapUtil();
            }

            ~AutoInitModule()
            {
                uninitializeWrapUtil();
            }
        };

        static AutoInitModule auto_init_module;
    }

    static bool s_bInitialized = false;

    //----------------------------------------------
    bool isWrapUtilInitialized()
    {
        return s_bInitialized;
    }
    //----------------------------------------------
    bool initializeWrapUtil()
    {
        // initialize.
        osl::initializeOSLib();

        s_bInitialized = true;

        return true;
    }
    //----------------------------------------------
    void uninitializeWrapUtil()
    {
        if ( !s_bInitialized )
        {
            return;
        }

        s_bInitialized = false;
    }
};

