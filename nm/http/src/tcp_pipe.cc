#include "stdafx.h"
#include "../include/tcp_pipe.h"
#include "../include/string_util.h"
#include "osl/include/data_stream.h"
#include <iostream>

namespace nm
{
    namespace
    {
        struct InitHelper
        {
            InitHelper()
            {
                WSADATA wsaData;
                int nError =  WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) ;
                if ( nError )
                {
                    WSACleanup();
                    std::cout << "WSAStartup() failed with error: %d" << nError;
                }
            }
        } g_init_helper_never_use_this;


        SOCKET createTcpSocket()
        {
            SOCKET skRet;
#ifdef _MSC_VER

            // Create a socket to accept a connection on
            //skRet = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED );
            skRet = socket( AF_INET, SOCK_STREAM, 0 );

#else
            skRet = socket( AF_INET, SOCK_STREAM, 0 );

#	ifdef SO_NOSIGPIPE
            // disable sigpipe
            int nOn = 1;

            if ( 0 != setsockopt( skRet, SOL_SOCKET, SO_NOSIGPIPE, ( char* )&nOn, sizeof( nOn ) ) )
            {
                fprintf( stderr, "Can not set SO_NOSIGPIPE on socket." );
            }

#	endif
#endif

            return skRet;

        }
        static bool setSocketReuse( SOCKET sock, bool bResuse )
        {
            int nReuse = bResuse ? 1 : 0;

            if ( 0 != setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, ( const char* )&nReuse, sizeof( nReuse ) ) )
            {
                return false;
            }

            return true;
        }

        bool setnonblocking( SOCKET sock )
        {
#ifdef _MSC_VER
            unsigned long nVal = 1;

            if ( 0 != ioctlsocket( sock, FIONBIO, &nVal ) )
            {
                return false;
            }

#else

            int opts;
            opts = fcntl( sock, F_GETFL );

            if ( opts < 0 )
            {
                //perror("fcntl(sock,GETFL)");
                //exit(1);
                return false;
            }

            opts = opts | O_NONBLOCK;

            if ( fcntl( sock, F_SETFL, opts ) < 0 )
            {
                //perror("fcntl(sock,SETFL,opts)");
                //exit(1);
                return false;
            }

#endif
            return true;
        }

        /* inet_aton - version of inet_aton for Windows */
        int inet_aton( const char* cp, struct in_addr *pin )
        {
            int rc;

            rc = inet_addr( cp );

            if ( rc == -1 && strcmp( cp, "255.255.255.255" ) )
            {
                return 0;
            }

            pin->s_addr = rc;

            return 1;
        }

        /**
        * @brief <b>Summary:</b>
        *        set sockaddr_in structure
        *
        * @param[in] hname
        *            host name,if hname value is NULL,address will be set to INADDR_ANY
        * @param[in] sname
        *            service name,
        * @param[in] protocol
        *            network protocol,udp or tcp
        * @param[out] sap
        *            sockaddr_in pointer to set
        * @return int
        ****************************************************************************************/
        int set_address( const char* hname, const char* sname,
                        struct sockaddr_in* sap, const char* protocol )
        {
            struct servent* sp;
            struct hostent* hp;
            char* endptr;
            short port;

            memset( sap, 0, sizeof( *sap ) );
            sap->sin_family = AF_INET;

            if ( hname != NULL && strlen( hname ) > 0 )
            {
               
                if ( !inet_aton( hname, &sap->sin_addr ) )
                {
                    hp = gethostbyname( hname );

                    if ( hp == NULL )
                    {
                        //OStringStream strTip;
                        //strTip <<  "unknown host:" << hname;
                        //error( 0, 0, "unknown host:%s\n", hname );
                        return -1;
                    }

                    sap->sin_addr = *( struct in_addr* )hp->h_addr;
                }
            }
            else
            {
                sap->sin_addr.s_addr = htonl( INADDR_ANY );
            }

            port = (short)strtol( sname, &endptr, 0 );

            if ( *endptr == '\0' )
            {
                sap->sin_port = htons( port );
            }
            else
            {
                sp = getservbyname( sname, protocol );

                if ( sp == NULL )
                {
                    //error( 0, 0, "unknown service %s\n", sname );
                    return -1;
                }

                sap->sin_port = sp->s_port;
            }

            return 0;
        }
    }
    

    TcpPipe::TcpPipe(bool nonblocking/* = true*/)
        : sock_(INVALID_SOCKET)
        , nonblocking_(nonblocking)
        , port_(0)
    {
        
    }

    TcpPipe::~TcpPipe()
    {
        if (sock_ != INVALID_SOCKET)
        {
            closesocket(sock_);
            sock_ = INVALID_SOCKET;
        }
    }

    bool TcpPipe::Connect(const char* ip, short port)
    {
        //sock_ = createTcpSocket();
        sock_ = socket( AF_INET, SOCK_STREAM, 0 );
        if (sock_ == INVALID_SOCKET)
        {
            return false;
        }

        if (nonblocking_)
        {
            setnonblocking(sock_);
        }

        struct sockaddr_in sap;
        set_address(ip, StringUtil::valueOf(port).c_str(), &sap, "tcp");
        //TODO
        
        int ret = connect(sock_, (struct sockaddr*)&sap, sizeof(struct sockaddr));
        if (ret != 0)
        {
            fprintf(stderr, "Connect failed!\n");
            return false;
        }
        return true;
    }


    void test_MemoryDataStream()
    {
        osl::MemoryDataStreamPtr buf = new osl::MemoryDataStream();
        buf->write("abc,", 4);
        buf->write("abc,", 4);
        buf->write("abc,", 4);
        buf->write("abc,", 4);
        buf->write("abc,", 4);
        buf->reset();
        buf->write("abc,", 4);
        buf->write("abc,", 4);
        buf->write("abc,", 4);
        buf->write("abc,", 4);
        buf->write("abc,", 4);

        osl::MemoryDataStream* buf1 = buf.getPointer();
        osl::MemoryDataStream* buf2 = buf.getPointer();
        buf1->write("abc,", 4);
        buf2->write("abc,", 4);

        buf->write("abc,", 4);
        buf->write("abc,", 4);
        buf->write("abc,", 4);
        buf->write("abc,", 4);

        osl::MemoryDataStreamPtr buf3 = buf;
        osl::MemoryDataStreamPtr buf4 = buf;


        buf3->write("abc,", 4);
        buf3->write("abc,", 4);
        buf4->write("abc,", 4);
        buf4->write("abc,", 4);

    }

    bool TcpPipe::Send(const void* data, size_t data_len)
    {
        //test_MemoryDataStream();

        //TODO 仅仅是简单实现
        int sendn = send(sock_, (const char*)data, data_len, 0);
        if (sendn == -1)
        {
            //TODO
            return false;
        }
        return true;
    }

    bool TcpPipe::Recv(std::string& recv_data)
    {
        //TODO 仅仅是简单实现
        std::stringstream ss;

        char buffer[512] = {'\0'};
        int	l = 0;
        do
        {
            l = recv(sock_,buffer,sizeof(buffer)-1,0);  
            if(l<0)
            {
                //TODO
                break;
            }
            ss.write(buffer, l);
        } while(l>0);

        recv_data = ss.str();
        return true;
    }
}