
#include "stdafx.h"
#include "../include/tcp_pipe.h"

namespace nm
{
    HttpRequest::HttpRequest( const char* url, unsigned int timeout, bool nonblocking /*= true*/ ) : url_(url)
        , port_(0)
        , timeout_(timeout)
        , tcp_pipe_(NULL)
        , nonblocking_(nonblocking)
    {
        ParseIpAndURI(url_, ip_, port_, uri_);
    }

    HttpRequest::~HttpRequest()
    {
        listeners_.clear();
        if (tcp_pipe_)
        {
            delete tcp_pipe_;
            tcp_pipe_ = NULL;
        }
    }

    void HttpRequest::ParseIpAndURI(const std::string& url, std::string& ip, short& port, std::string& uri)
    {
        std::string http_pre = url.substr(0, 7);
        std::transform(http_pre.begin(), http_pre.end(), http_pre.begin(), tolower);
        size_t host_pos_begin = 0;
        if (0 == strcmp(http_pre.c_str(), "http://"))
        {
            host_pos_begin = 7;
        }

        //Get the URI
        char* first_sep = strchr(url.c_str() + host_pos_begin, '/');
        if (first_sep)
        {
            uri = first_sep;
            ip = url.substr(host_pos_begin, first_sep - url.c_str() - host_pos_begin);
        }
        else
        {
            uri = "";
            ip = url.substr(host_pos_begin);
        }

        //Get the PORT and IP
        size_t pos = ip.find(':');
        if (pos == std::string::npos)
        {
            port = 80;//the default value
        }
        else
        {
            port = atoi(ip.c_str() + pos + 1);
            ip = ip.substr(0, pos);
        }
    }

    bool HttpRequest::DoRequest()
    {
        if (!Init())
        {
            ListenerList::iterator it(listeners_.begin());
            ListenerList::iterator ite(listeners_.end());
            for (; it != ite; ++it)
            {
                (*it)->OnFinishErrorT(EC_FAILED_INIT, this);
            }
            return false;
        }
        return DoHttpRequest();
    }

    bool HttpRequest::Init()
    {
        tcp_pipe_ = new TcpPipe(nonblocking_);
        if (!tcp_pipe_->Connect(ip_.c_str(), port_))
        {
            fprintf(stderr, "connect failed!\n");
            return false;
        }

        return true;
    }
}

