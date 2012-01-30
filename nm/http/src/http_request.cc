
#include "stdafx.h"

namespace nm
{
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
}