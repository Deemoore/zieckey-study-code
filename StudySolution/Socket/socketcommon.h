//! Define Operation System.
#if ( defined(WIN32) || defined(WIN64) )
#	ifndef H_OS_WINDOWS
#		define H_OS_WINDOWS
#	endif
#else
#	ifndef H_OS_LINUX
#		define H_OS_LINUX
#	endif
#endif

#ifdef H_OS_WINDOWS
#   include <ws2tcpip.h>
#elif defined(H_OS_LINUX)
#	include <stdio.h>
#	include <stdlib.h>
#	include <unistd.h>
#	include <stdarg.h>
#	include <string.h>
#	include <errno.h>
#	include <netdb.h>
#	include <fcntl.h>
#	include <sys/time.h>
#	include <sys/socket.h>
#	include <netdb.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#	include <netinet/in.h>
#   include <poll.h>
#endif


#include <stdio.h>
#include <string.h>
#include <time.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>


#define MAX_BUF_SIZE 1024

#ifdef H_OS_WINDOWS
__pragma (comment( lib , "Ws2_32.lib" ))

#endif

#ifdef H_OS_LINUX
#   ifndef SOCKET
#	    define SOCKET int		    /**< SOCKET definition */
#   endif
#   ifndef INVALID_SOCKET
#	    define INVALID_SOCKET -1	/**< invalid socket definition */
#   endif
#endif

#define EXIT(s)			exit(s)
#define CLOSE(s)		if(close(s)) error( 1, errno, "closed failed")
#define set_errno(e)	errno = (e)
#define isvalidsock(s)	((s) != INVALID_SOCKET)


#ifdef H_OS_WINDOWS
#	define CLOSE_SOCKET(s)  ::closesocket(s); (s)=INVALID_SOCKET;
#elif defined(H_OS_LINUX)
#	define CLOSE_SOCKET(s)  ::close(s); (s)=INVALID_SOCKET;
#endif

#ifdef H_OS_WINDOWS

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
#endif





/**
* @brief <b>Summary:</b>
* @param[in]
* @param[in]
* @param[out]
* @return
****************************************************************************************/
bool setnonblocking( SOCKET sock )
{
#ifdef H_OS_WINDOWS
    unsigned long nVal = 1;

    if ( 0 != ioctlsocket( sock, FIONBIO, &nVal ) )
    {
        return false;
    }

#elif defined(H_OS_LINUX)

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
//----------------------------------------------
SOCKET createTcpSocket()
{
    SOCKET skRet;
#ifdef H_OS_WINDOWS

    // Create a socket to accept a connection on
    skRet = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED );

#elif defined(H_OS_LINUX)
    skRet = socket( AF_INET, SOCK_STREAM, 0 );

#	ifdef SO_NOSIGPIPE
    // disable sigpipe
    int nOn = 1;

    if ( 0 != setsockopt( skRet, SOL_SOCKET, SO_NOSIGPIPE, ( char* )&nOn, sizeof( nOn ) ) )
    {
        H_LOG_NAME_DEBUG( "", "Can not set SO_NOSIGPIPE on socket." );
    }

#	endif
#endif

    return skRet;

}
//------------------------------------------------
bool setSocketReuse( SOCKET sock, bool bResuse )
{
    int nReuse = bResuse ? 1 : 0;

    if ( 0 != setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, ( char* )&nReuse, sizeof( nReuse ) ) )
    {
        return false;
    }

    return true;
}
//------------------------------------------------
bool setSocketSendBuffer( SOCKET sock, int nSize )
{
    int nBufSize = nSize;

    if ( 0 != setsockopt( sock, SOL_SOCKET, SO_SNDBUF, ( char* )&nBufSize, sizeof( nBufSize ) ) )
    {
        return false;
    }

    return true;
}
//------------------------------------------------
bool setSocketRecvBuffer( SOCKET sock, int nSize )
{
    int nBufSize = nSize;

    if ( 0 != setsockopt( sock, SOL_SOCKET, SO_RCVBUF, ( char* )&nBufSize, sizeof( nBufSize ) ) )
    {
        return false;
    }

    return true;
}

/**
* @brief <b>Summary:</b>
*        print error to stdout
*
* @param[in] status
*            if status has a nonzero value, ther error calles
*            exit to terminate program
* @param[in] err
*            error number
* @param[in] fmt
*            Variable parameters
* @return void
****************************************************************************************/

void error( int status, int err, const char* fmt, ... )
{
    va_list ap;

    va_start( ap, fmt );
    fprintf( stderr, "%s: ", "your program" );
    vfprintf( stderr, fmt, ap );
    va_end( ap );

    if ( err )
    {
        fprintf( stderr, ": %s (%d)\n",  strerror( err ), err );
    }

    if ( status )
    {
        EXIT( status );
    }
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
        // #ifdef H_OS_WINDOWS
        //             sap->sin_addr.s_addr = inet_addr( hname ) ;
        // 
        //             if ( !sap->sin_addr.s_addr )
        //             {
        // 
        // #elif defined(H_OS_LINUX)
        // 
        //             if ( !inet_aton( hname, &sap->sin_addr ) )
        //             {
        // #endif
        if ( !inet_aton( hname, &sap->sin_addr ) )
        {
            hp = gethostbyname( hname );

            if ( hp == NULL )
            {
                //OStringStream strTip;
                //strTip <<  "unknown host:" << hname;
                error( 0, 0, "unknown host:%s\n", hname );
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
            error( 0, 0, "unknown service %s\n", sname );
            return -1;
        }

        sap->sin_port = sp->s_port;
    }

    return 0;
}

/**
* @brief <b>Summary:</b>
*        new a tcp server with designated host name and service name
*
* @param[in] hname
*            host name,if hname value is NULL,address will be set to INADDR_ANY
* @param[in] sname
*            service name,
* @return SOCKET if success,return listen socket,else return INVALID_SOCKET
****************************************************************************************/
SOCKET tcp_server( const char * hname, const char * sname )
{
    struct sockaddr_in local;
    SOCKET s;
    const int on = 1;

    if ( set_address( hname, sname, &local, "tcp" ) )
    {
        return INVALID_SOCKET;
    }

    s = socket( AF_INET, SOCK_STREAM, 0 );

    if ( !isvalidsock( s ) )
    {
        error( 0, errno, "socket call failed" );
        return INVALID_SOCKET;
    }

    if ( setsockopt( s, SOL_SOCKET, SO_REUSEADDR,
        ( char* )&on, sizeof( on ) ) )
    {
        error( 0, errno, "setsockopt failed" );
        CLOSE_SOCKET( s );
        return INVALID_SOCKET;
    }

    //setnonblocking( s );	//if not set non-block here, port will not reuse

    if ( bind( s, ( struct sockaddr* )&local,
        sizeof( local ) ) )
    {
        error( 0, errno, "bind failed" );
        CLOSE_SOCKET( s );
        return INVALID_SOCKET;
    }

    if ( listen( s, 5 ) )
    {
        error( 0, errno, "listen failed" );
        CLOSE_SOCKET( s );
        return INVALID_SOCKET;
    }

    return s;
}

/**
* @brief <b>Summary:</b>
*        new a udp server with designated host name and service name
*
* @param[in] hname
*            host name,if hname value is NULL,address will be set to INADDR_ANY
* @param[in] sname
*            service name,
* @return SOCKET if success,return bind socket,else return INVALID_SOCKET
****************************************************************************************/

SOCKET udp_server( const char * hname, const char * sname )
{
    SOCKET s;
    struct sockaddr_in local;

    set_address( hname, sname, &local, "udp" );
    s = socket( AF_INET, SOCK_DGRAM, 0 );

    if ( !isvalidsock( s ) )
    {
        error( 0, errno, "sock call failed" );
        return INVALID_SOCKET;
    }

    if ( bind( s, ( struct sockaddr* )&local, sizeof( local ) ) )
    {
        error( 0, errno, "bind failed" );
        return INVALID_SOCKET;
    }

    return s;
}

/**
* @brief <b>Summary:</b>
*        connect tcp client to designated host name and service name
*
* @param[in] hname
*            server host name
* @param[in] sname
*            server service name,
* @return SOCKET if success,return connected socket,else return INVALID_SOCKET
****************************************************************************************/

SOCKET tcp_client( const char * hname, const char * sname )
{
    struct sockaddr_in peer;
    SOCKET s;

    set_address( hname, sname, &peer, "tcp" );
    s = socket( AF_INET, SOCK_STREAM, 0 );

    if ( !isvalidsock( s ) )
    {
        error( 0, errno, "socket call failed" );
        return INVALID_SOCKET;
    }

    if ( connect( s, ( struct sockaddr * )&peer,
        sizeof( peer ) ) )
    {
        error( 0, errno, "connect failed" );
        CLOSE_SOCKET( s );
        return INVALID_SOCKET;
    }

    return s;
}

/**
* @brief <b>Summary:</b>
*        set udp client to designated host name and service name
*
* @param[in] hname
*            server host name
* @param[in] sname
*            server service name,
* @return SOCKET if success,return valid socket,else return INVALID_SOCKET
****************************************************************************************/

SOCKET udp_client( const char * hname, const char * sname,
struct sockaddr_in * sap )
{
    SOCKET s;

    set_address( hname, sname, sap, "udp" );
    s = socket( AF_INET, SOCK_DGRAM, 0 );

    if ( !isvalidsock( s ) )
    {
        error( 0, errno, "socket call failed" );
        return INVALID_SOCKET;
    }

    return s;
}
// 
// //----------------------------------------------
// HostInfoList getLocalHost()
// {
//     HostInfoList vHosts;
// 
// #ifdef H_OS_LINUX
// 
//     {
//         // add 0.0.0.0
//         HostInfo hostInfo;
//         hostInfo.strHostName = "localhost";
//         hostInfo.strIP = "0.0.0.0";
//         hostInfo.addrHost.s_addr = inet_addr( hostInfo.strIP.c_str() );
//         // add host.
//         vHosts.push_back ( hostInfo );
//     }
// #endif
// 
//     char szHostName[256];
//     memset( szHostName, 0, sizeof( szHostName ) );
// 
//     if ( 0 != gethostname( szHostName, 256 ) )
//     {
//         return vHosts;
//     }
// 
//     struct addrinfo* pAddrList;
// 
//     int nErr = getaddrinfo( szHostName, 0, 0, &pAddrList ) ;
// 
//     if ( nErr != 0 )
//     {
//         std::ostringstream strTip ;
//         strTip << "Can not get host " << szHostName << "'s address:" << gai_strerror( nErr );
// 
//         std::cout << strTip.str();
//         return vHosts;
//     }
// 
// 
//     {
//         struct addrinfo* pAddr = pAddrList;
// 
//         while ( pAddr )
//         {
//             HostInfo hostInfo;
//             hostInfo.strHostName = szHostName;
//             hostInfo.addrHost = ( ( struct sockaddr_in* ) pAddr->ai_addr )->sin_addr;
//             hostInfo.strIP = inet_ntoa ( hostInfo.addrHost );
// #ifdef H_OS_WINDOWS
// 
//             if ( hostInfo.addrHost.s_addr == 0 )
//             {
//                 pAddr = pAddr->ai_next;
//                 continue;
//             }
// 
// #endif
//             // add host.
//             vHosts.push_back ( hostInfo );
// 
//             pAddr = pAddr->ai_next;
//         }
//     }
// 
//     if ( pAddrList )
//     {
//         freeaddrinfo( pAddrList );
//     }
// 
//     return vHosts;
// }


int getLastSocketError()
{
#ifdef H_OS_WINDOWS
    return WSAGetLastError();
#else
    return errno;
#endif 
}

//! Sleep for a while in milliseconds. It will sleep the calling thread.
void msleep( unsigned int nMilliseconds )
{
#ifdef H_OS_WINDOWS
    ::Sleep( nMilliseconds );
#else
    usleep( nMilliseconds * 1000 );
#endif 
}


bool socketstartup()
{
#ifdef H_OS_WINDOWS
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 2, 2 );
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        return false;
    }
    /* Confirm that the WinSock DLL supports 2.2.*/
    /* Note that if the DLL supports versions greater    */
    /* than 2.2 in addition to 2.2, it will still return */
    /* 2.2 in wVersion since that is the version we      */
    /* requested.                                        */
    if ( LOBYTE( wsaData.wVersion ) != 2 ||
        HIBYTE( wsaData.wVersion ) != 2 ) {
            /* Tell the user that we could not find a usable */
            /* WinSock DLL.                                  */
            WSACleanup( );
            return false; 
    }
#endif
    return true;
}

bool socketshutdown()
{
#ifdef H_OS_WINDOWS
    WSACleanup( );
#endif
    return true;
}

#define MST (-7)
#define UTC (0)
#define CCT (+8)
class Log
{
public:
    static void init( const char* szLogFile = "log.txt" )
    {
        m_fstream.open( szLogFile, std::fstream::in | std::fstream::out | std::fstream::app );
        m_errorfstream.open( "error.log.txt", std::fstream::in | std::fstream::out | std::fstream::app );
    }
    static void close()
    {
        m_fstream.close();
        m_errorfstream.close();
    }

    static void trace( const char* msg )
    {
        std::ostringstream log;
        log << getDateString().c_str() << msg << std::endl;
        std::cout << log.str();
        m_fstream << log.str().c_str();
        m_fstream.flush();
    }

    static void error( const char* msg )
    {
        
        std::ostringstream log;
        log << getDateString().c_str() << msg << std::endl;
        std::cout << log.str();
        m_fstream << log.str().c_str();
        m_fstream.flush();
        m_errorfstream << log.str().c_str();
        m_errorfstream.flush();
    }

    static void trace( const std::string& msg )
    {
        trace( msg.c_str() );
    }

    static void error( const std::string& msg )
    {
        error( msg.c_str() );
    }

private:
    static std::string getDateString()
    {
        time_t rawtime;
        time( &rawtime );
        struct tm * timeinfo;
        timeinfo = localtime( &rawtime );
        std::ostringstream log;
        log << std::setfill('0') << std::setw(4) << timeinfo->tm_year << "-" 
            << std::setw(2) << timeinfo->tm_mon << "-" 
            << std::setw(2) << timeinfo->tm_mday << " "
            << std::setw(2) << (timeinfo->tm_hour) << ":" 
            << std::setw(2) << timeinfo->tm_min << ":" 
            << std::setw(2) << timeinfo->tm_sec << "," 
#ifdef H_OS_WINDOWS
            << std::setprecision(3) << (double)(GetTickCount() % 10000) / 1000.0f
#endif
            << " ";
        return log.str();
    }
private:
    static std::fstream m_fstream;
    static std::fstream m_errorfstream;
};


std::fstream Log::m_fstream;
std::fstream Log::m_errorfstream;
