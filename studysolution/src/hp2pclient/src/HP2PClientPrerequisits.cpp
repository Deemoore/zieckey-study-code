#include "hp2pclient/include/HP2PClientPrerequisits.h"

P2PC_NAMESPACE_BEGIN

static bool s_bInitialized = false;

bool initializeP2PClient()
{
    if ( s_bInitialized )
    {
        return true;
    }

    // initialize OSLib
    if ( !OSLib::initializeOSLib() )
    {
        return false;
    }

    // Initialize Network
    if ( !Net::initializeNet() )
    {
        return  false;
    }


    if ( !Common::initializeCommon() )
    {
        return false;
    }

    return true;
}


void uninitializeP2PClient()
{
    if ( !s_bInitialized )
    {
        return;
    }





    // self.
    Common::uninitializeCommon();

    // Initialize Network
    Net::uninitializeNet();

    // OSLib;
    OSLib::uninitializeOSLib();
}



P2PC_NAMESPACE_END