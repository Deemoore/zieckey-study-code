#include "../socketcommon.h"

int main( int argc, char* argv[] )
{ 
    if ( argc != 4 )
    {
        std::cout << "error parameters. usage: " << argv[0] << " ip port packetinteval";
        return -1;
    }

    Log::init();

    float packetinteval = atof( argv[3] );
    if ( packetinteval <= 0.001 )
    {
        packetinteval = 0.5;
    }

    socketstartup();

    SOCKET serversockfd = tcp_server( argv[1], argv[2] );
    int myerrno = getLastSocketError();
    if ( ! isvalidsock( serversockfd ) )
    {
        std::cout << "create tcp server error. errno=" << myerrno << std::endl;
        msleep( packetinteval * 1000 );// 1/10 of packetinteval*1000
        return -1;
    }

    char recvbuf[MAX_BUF_SIZE];
    char msgbuf[MAX_BUF_SIZE];
    memset( msgbuf, 'A', sizeof( msgbuf ) );
    for ( ;; )
    {
        Log::trace( "OK, tcp server is running, and waiting for client connection." );
        struct sockaddr_in clientaddr;
        socklen_t addrlen = sizeof( clientaddr );
        memset( &clientaddr, 0, addrlen );
        SOCKET clientfd = accept( serversockfd, (struct sockaddr*)&clientaddr, &addrlen );
        int myerrno = getLastSocketError();
        if ( ! isvalidsock( clientfd ) )
        {
            std::cout << "accept error. errno=" << myerrno << std::endl;
            msleep( packetinteval * 1000 );// 1/10 of packetinteval*1000
            continue;
        }

        int sendcount = 0;
        int recvcount = 0;
        int recverrorcount = 0;
        for ( ;; )
        {
            int sendn = send( clientfd, msgbuf, sizeof( msgbuf ), 0 );
            int myerrno = getLastSocketError();
            if ( -1 == sendn )
            {
                static int errorcount = 0;
                if ( 10 == errorcount++ )
                {
                    break;
                }
                std::cout << "send error. errno=" << myerrno;
                msleep( packetinteval * 1000 );// 1/10 of packetinteval*1000
                continue;
            }

            Log::trace( "send a message to client." );
            sendcount++;
            int recvn = recv( clientfd, recvbuf, sizeof(msgbuf), 0 );
            if ( sizeof(msgbuf) == recvn )
            {
                bool brecvwrite = true;
                for ( int i = 0; i < sizeof(msgbuf); ++i )
                {
                    if ( recvbuf[i] != 'A' && recvbuf[i] != 'q' && recvbuf[i] != 'Q' )
                    {
                        brecvwrite = false;
                        break;
                    }
                }
                
                if ( brecvwrite )
                {
                    Log::trace( "recv a message from client." );
                    recvcount++;
                }
                else
                {
                    Log::trace( "recv message content is wrong." );
                    recverrorcount++;
                }
            }
            else
            {
                static int errorcount = 0;
                if ( 10 == errorcount++ )
                {
                    Log::trace( "recv message error." );
                    break;
                }
            }

            if ( recvbuf[0] == 'q' || recvbuf[0] == 'Q' )
            {
                std::ostringstream log;
                log << "===========================================================";
                log << "\n\tRecv count=" << recvcount
                    << "\n\tSend count=" << sendcount
                    << "\n\tRecv error count=" << recverrorcount;
                log << "\n===========================================================";
                Log::trace( log.str() );

                CLOSE_SOCKET( clientfd );
                break;
            }

            msleep( (unsigned int)(packetinteval * 1000) );
        } // end of send-recv for(;;)
    
    }//end of accept loop for(;;)



    CLOSE_SOCKET( serversockfd );

    return 0;
}