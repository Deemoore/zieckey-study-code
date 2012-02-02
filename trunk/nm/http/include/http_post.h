#pragma once

#include "http_request.h"

namespace nm
{
    class HttpPost : public HttpRequest
    {
    public:
        HttpPost(const char* url, unsigned int timeout, bool nonblocking)
            : HttpRequest(url, timeout, nonblocking)
        {
        }

        //! \brief Set the Http body directly.
        //! \warning 如果这个方法被调用，那么在此之前或之后通过 AddParameter 添加的参数都将无效
        //! \param[] - const char * data
        //! \param[] - size_t data_len
        //! \return - void
        void SetRawHttpBodyContent(const char* data, size_t data_len);
        void SetRawHttpBodyContent(const std::string& data);

    protected:
        virtual bool DoHttpRequest();

    private:
        std::string http_raw_body_data_;

    };
}

