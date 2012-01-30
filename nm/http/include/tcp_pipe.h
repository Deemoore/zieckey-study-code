#pragma once

namespace um
{
    class TcpPipe
    {
    public:
        TcpPipe(bool nonblocking = true);
        bool Connect(const char* ip, short port);
        bool Send(const char* data, size_t data_len);
        bool Recv(std::string& recv_data);
    };
}

