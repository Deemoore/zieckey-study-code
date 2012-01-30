#pragma once

#include "http_request.h"

namespace nm
{
    class HttpPost : public HttpRequest
    {
    public:
        HttpPost(const char* url, unsigned int timeout)
            : HttpRequest(url, timeout)
        {
        }

    protected:
        virtual void DoHttpRequest();
    };
}

