#include "hp2pnegserver/include/HP2PNegServerPrerequisits.h"

P2PNS_NAMESPACE_BEGIN

static bool s_bInitialized = false;

bool initializeP2PNegServer()
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


void uninitializeP2PNegServer()
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



P2PNS_NAMESPACE_END