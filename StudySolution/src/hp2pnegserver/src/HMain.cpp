#include "hp2pnegserver/include/HP2PNegServerPrerequisits.h"
#include <iostream>

#include "hoslib/include/HAsyncCommand.h"

namespace 
{
    // shell command used to be queued in main thread queue.
    class ShellCmd : public OSLib::AsyncCommand
    {
    public:

        //! field
        OSLib::StringA  m_strCMD;

        //! Constructor.
        ShellCmd( const char* strCMD ): m_strCMD( strCMD ) {}

        virtual void doCommand()
        {
            //s_pSyncServer->getAppShell()->processCommand( m_strCMD );
        }
    };
}


//-------------------------------------------------------
int main( int argc, char* argv[] )
{
    // Initilize the module. It will initialize OSLib and Net
    P2PNS::initializeP2PNegServer();

    // system started.
    H_LOG_NAME_INFO( "ss", "Start P2PNegServer..." );


#ifdef H_DEBUG_MODE
    {
        OSLib::OStringStream strTip;
        strTip << " Current bin directory " << OSLib::OS::getBinDir() << std::endl ;
        strTip << " Current etc directory " << OSLib::OS::getConfDir() ;
        H_LOG_NAME_INFO( "SyncServer", strTip.str() );
    }
#endif

//     SS::SyncServer* pThisServer = H_NEW SS::SyncServer();
//     pThisServer->ref();
// 
//     if ( !pThisServer->start() )
//     {
//         std::cout << "Can Not Start the server. Press any key to quit..." << std::endl;
//         std::cin.get();
//         return 0;
//     }
// 
//     H_LOG_NAME_INFO( "cs", "Shell ready..." );
// 
//     // show command description.
//     pThisServer->getAppShell()->showCommandDescriptions();
// 
//     char szCommand[1024];
// 
//     for ( ;; )
//     {
//         // get line less than 256.
//         std::cin.getline( szCommand, 1024 );
// 
//         if ( std::cin.fail() )
//         {
//             std::cin.clear( std::ios_base::goodbit );
// 
// #ifdef H_OS_LINUX
//             static bool bFirst = true;
// 
//             if ( bFirst )
//             {
//                 bFirst = false;
//                 std::cout << "Error, Command string length CAN NOT larger than 255." << std::endl;
//             }
// 
//             OSLib::OS::msSleep( 20 );
// #else
//             std::cout << "Error, Command string length CAN NOT larger than 255." << std::endl;
// #endif
//             continue;
//         }
// 
//         {
//             // process command.
//             //pThisServer->getAppShell()->processCommand( strDD );
// 
//             // process command.
//             pThisServer->getCommandQueue()->pushCommand( H_NEW ShellCmd( szCommand ) );
// 
//             // quit
//             if ( strcmp( szCommand, "quit" ) == 0 || strcmp( szCommand, "q" ) == 0 )
//             {
//                 break;
// 
//                 // statistics
//             }
//             else if ( strcmp( szCommand, "stats" ) == 0 || strcmp( szCommand, "s" ) == 0 )
//             {
//                 // dump stats.
//                 pThisServer->dumpStats();
// 
//                 // command help.
//                 //printfCommandHelp();
// 
//             }
//             else
//             {
//                 // command help.
//                 //printfCommandHelp();
//             }
//         }
//     }
// 
// 
//     //
//     /// Stopping
//     //
//     {
//         std::cout << std::endl << std::endl << std::endl
//             << "SyncServer is quiting, please wait..." << std::endl
//             << "=================================" << std::endl;
// 
//         // wait for stop.
//         pThisServer->stop();
// 
//         pThisServer->unref();;
//     }



    H_LOG_NAME_INFO( "HMain", "Begin to uninitialize module..." );

    P2PNS::uninitializeP2PNegServer();


    // stop tip.
    {
        std::cout << std::endl << std::endl << std::endl
            << "Gateway server successfully quit." << std::endl
            << "=================================" << std::endl;

        //
        OSLib::OS::msSleep( 500 );
    }

    return 0;
}



//#pragma comment( lib,"HDBLib_d.lib")

