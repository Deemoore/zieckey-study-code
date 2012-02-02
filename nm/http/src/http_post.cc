#include "stdafx.h"

#include "../include/http_post.h"

namespace nm
{
    bool HttpPost::DoHttpRequest()
    {
        //////////////////////////////////////////////////////////////////////////
        //step 1: fill the http body
        std::string body_data;
        {
            std::stringstream ss_body_data;
            StringStringMap::iterator it(parameters_.begin());
            StringStringMap::iterator ite(parameters_.end());
            bool first_parameter = true;
            for (; it != ite; ++it)
            {
                if (first_parameter)
                {
                    ss_body_data << '"' << it->first << '=' << it->second;
                    first_parameter = false;
                }
                else
                {
                    ss_body_data << '&' << it->first << '=' << it->second;
                }
            }
            ss_body_data << '"';
            body_data = ss_body_data.str();
        }

        //////////////////////////////////////////////////////////////////////////
        //step 2: construct the http request packet
        std::string send_data;
        {
            std::stringstream oss;
            oss << "POST " 
                << uri_.c_str() 
                << " HTTP/1.0\r\n"
                << "Content-Length: " << body_data.length() << "\r\n"
                << "Content-Type: application/json\r\n"
                << "Host: " << ip_ << "\r\n\r\n";

            if (http_raw_body_data_.length() > 0)
            {
                oss << http_raw_body_data_;
            }
            else
            {
                oss << body_data;
            }
            send_data = oss.str();
        }

        //////////////////////////////////////////////////////////////////////////
        //step 3: do the http request packet
        HttpErrorCode hec = EC_NO_ERROR;
        do 
        {
            //////////////////////////////////////////////////////////////////////////
            //step 3.1: send the http request packet
            if (!tcp_pipe_->Send(send_data.c_str(), send_data.length()))
            {
                fprintf(stderr, "send data error\n");
                hec = EC_SEND_ERROR;
                break;
            }

            //////////////////////////////////////////////////////////////////////////
            //step 3.2: recv the http request packet
            if (!tcp_pipe_->Recv(recv_data_))
            {
                fprintf(stderr, "recv data error\n");
                hec = EC_RECV_ERROR;
                break;
            }
        } while (false);

        //////////////////////////////////////////////////////////////////////////
        //step 4: notify the listeners
        ListenerList::iterator it(listeners_.begin());
        ListenerList::iterator ite(listeners_.end());
        for (; it != ite; ++it)
        {
            if (hec == EC_NO_ERROR)
            {
                (*it)->OnFinishOKT(this);
            }
            else
            {
                (*it)->OnFinishErrorT(hec, this);
            }
        }

        return true;
    }

    void HttpPost::SetRawHttpBodyContent( const char* data, size_t data_len )
    {
        http_raw_body_data_ = std::string(data, data_len);
    }


    void HttpPost::SetRawHttpBodyContent( const std::string& data)
    {
        SetRawHttpBodyContent(data.c_str(), data.length());
    }

}

