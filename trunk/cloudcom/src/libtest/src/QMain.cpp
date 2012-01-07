#include "libtest/include/QLibTestPrerequisits.h"
// libtest.cpp :
//

/*#include "HStdHeader.h"*/
#include "libtest/include/QLibTest.h"

//#define H_PATCH_DATA_TRANSFER_TOOLS
//#define H_CURL_AUTO_TEST_TOOLS
//#define H_CURL_AUTO_TEST_SPEED
//#define H_TCP_NETWORK_TEST_TOOLS

//#define H_DECODED_IDEA_STORAGE_ENDINE_DATA_TOOLS

//----------------------------------------------
void testAll( osl::AppShell::Command* pCmd, osl::AppShell* pShell );

int main( int argc, char* argv[] )
{
    //H_LOG_NAME_DEBUG( "", "Shell ready...");
    osl::initializeOSLib();
    net::initializeNet();
    aut::initializeAppUtil();

    LibTest::TLibTest* pLibTest = H_NEW LibTest::TLibTest;
    pLibTest->ref();
    pLibTest->start();

#ifdef H_DECODED_IDEA_STORAGE_ENDINE_DATA_TOOLS
    if ( argc != 5 )
    {
        logTrace("", "Usage: %s --user=weizili --password=mypassword --in=/tmp/originaldata/ --out=/tmp/decode/", argv[0]);
        return -1;
    }

    osl::OStringStreamA tmp;
    tmp << "test_cacenter decodedumpfile ";
    for ( int i = 1; i < argc; ++i )
    {
        tmp << argv[i] << " ";
    }
    
    pLibTest->processCommand( tmp.str() );
    while ( pLibTest->isRunning() )
    {
        osl::OS::msSleep( 100 );
    }

    return 0;
#endif


// 
// #ifdef H_PATCH_DATA_TRANSFER_TOOLS
//     //osl::StringA strPatchDataTransferCmd = "test_patchdatatransfer --data_dir=E:/download/client-build078-r20091224-03/client --table_path=patch_id_transfer_table.txt";
//     osl::StringA strPatchDataTransferCmd = "test_patchdatatransfer";
//     pLibTest->processCommand( strPatchDataTransferCmd );
// #endif
// 
// #ifdef H_CURL_AUTO_TEST_TOOLS
//     osl::StringA strCurlCmd = "test_curl";
//     pLibTest->processCommand( strCurlCmd );
// #endif
// 
// #ifdef H_CURL_AUTO_TEST_SPEED
//     osl::StringA strCurlCmd = "test_curl --type=12";
//     pLibTest->processCommand( strCurlCmd );
// #endif
// 
// #ifdef H_TCP_NETWORK_TEST_TOOLS
//     osl::StringA strCurlCmd = "test_tcp --type=client start --tcpnum=300 --msglen=50000 --msgnum=1000000000 --host='192.168.0.42' --port=12345";
//     pLibTest->processCommand( strCurlCmd );
// #endif
	
	//Test json
	//pLibTest->processCommand( "test_json" );


    // show command description.
    pLibTest->showCommandDescriptions();

    char szCommand[1024];

    while ( 1 )
    {
        // get line less than 256.
        std::cin.getline( szCommand, 1024 );

        if ( std::cin.fail() )
        {
            std::cin.clear();
            std::cout << "Error, Command string length CAN NOT larger than 255." << std::endl;
            std::cin.clear( std::ios_base::goodbit );
            osl::OS::msSleep( 1000 );
            continue;
        }

        {
            // process command.
            //pThisServer->getAppShell()->processCommand( strDD );
            // process command.
            {
                osl::StringA strCmd = szCommand ;
                osl::StringUtil::toLowerCase( strCmd );
                pLibTest->processCommand( strCmd );
            }

            // quit
            if ( strcmp( szCommand, "quit" ) == 0 || strcmp( szCommand, "q" ) == 0 )
            {
                break;
                // statistics
            }
            else if ( strcmp( szCommand, "stats" ) == 0 || strcmp( szCommand, "s" ) == 0 )
            {
                // command help.
                //printfCommandHelp();
            }
            else
            {
                // command help.
                //printfCommandHelp();
            }
        }
    }

    pLibTest->join();

    for( ;; )
    {
        if ( pLibTest->isStopped() )
        {
            break;
        }
        else
        {
            osl::OS::msSleep( 5 );
        }
    }

    pLibTest->unref();
    pLibTest = NULL;
    net::uninitializeNet();
    osl::uninitializeOSLib();
    return 0;
}




