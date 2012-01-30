#pragma once


#include <WinSock2.h>

#include <string>

namespace nm
{
    class TcpPipe
    {
    public:
        TcpPipe(bool nonblocking = true);
        bool Connect(const char* ip, short port);
        bool Send(const void* data, size_t data_len);
        bool Recv(std::string& recv_data);

    private:
        SOCKET  sock_;
        bool    nonblocking_;
        std::string ip_;
        short port_;
    };
}

