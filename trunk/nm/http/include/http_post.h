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
        //! \warning ���������������ã���ô�ڴ�֮ǰ��֮��ͨ�� AddParameter ��ӵĲ���������Ч
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

