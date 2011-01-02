#include "../socketcommon.h"

int main( int argc, char* argv[] )
{
	if ( argc != 4 )
	{
		std::cout << "error parameters. usage: " << argv[0] << " ip port packetnum";
		return -1;
	}

    Log::init();

	int packetnum = atoi( argv[3] );

	if ( packetnum < 0 )
	{
		packetnum = 100;
	}

	socketstartup();
	SOCKET clientfd = tcp_client( argv[1], argv[2] );

	if ( !isvalidsock( clientfd ) )
	{
		Log::trace( "cannot connect server" );
		return -1;
	}

	char recvbuf[MAX_BUF_SIZE];

	int sendcount = 0;
	int recvcount = 0;
	int recverrorcount = 0;

	for ( ;; )
	{
		int recvn = recv( clientfd, recvbuf, sizeof( recvbuf ), 0 );

		if ( sizeof( recvbuf ) == recvn )
		{
			bool brecvwrite = true;
			for ( int i = 0; i < sizeof( recvbuf ); ++i )
			{
				if ( recvbuf[i] != 'A' )
				{
					brecvwrite = false;
					break;
				}
			}

			if ( brecvwrite )
			{
#ifdef H_OS_WINDOWS
                static DWORD tmLastRecvMsg = 0;
                DWORD tnow = GetTickCount();
                double fdiff = (double)( tnow - tmLastRecvMsg ) / 1000.0f;
                if ( fdiff > 2.0 )
                {
                    std::ostringstream log;
                    log << "recv a message from server, but it is too long, interval:" << fdiff << "s.";
                    Log::error( log.str() );
                }
                else
                {
                    Log::trace( "recv a message from server." );
                }
                tmLastRecvMsg = tnow;
#else
                Log::trace( "recv a message from server." );
#endif
				recvcount++;
			}
			else
			{
				Log::trace( "recv message, but the content is wrong." );
				recverrorcount++;
			}
		}
		else
		{
			static int errorcount = 0;

			if ( 10 == errorcount++ )
			{
				break;
			}
		}

        if ( recvcount == packetnum )
        {
            memset( recvbuf, 'q', sizeof(recvbuf) );
        }

		int sendn = 0;
		do
		{
			sendn = send( clientfd, recvbuf, sizeof( recvbuf ), 0 );

			if ( -1 == sendn )
			{
				static int errorcount = 0;

				if ( 10 == errorcount++ )
				{
					break;
				}

				std::cout << "send error. errno=" << getLastSocketError();
				msleep( 100 );
			}
			else
			{
				//Log::trace( "                      send a message to client." );
				sendcount++;
				break;
			}
		}
		while ( -1 == sendn );


        if ( recvcount == packetnum )
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
		
	} // end of send-recv for(;;)


	return 0;
}