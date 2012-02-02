#pragma once

#include <string.h>

#include <string>
#include <sstream>
#include <list>
#include <map>
#include <algorithm>

#include "osl/include/object.h"

namespace nm
{
    class TcpPipe;

    class HttpRequest : public osl::Object
    {
    public:
        /*! @enum HTTP Error Code	 */
        enum HttpErrorCode
        {
            EC_NO_ERROR = 3000,	//! no error
            EC_HOST_UNREACHABLE,
            EC_COULDNT_CONNECT,
            EC_REMOTE_ACCESS_DENIED,
            EC_UPLOAD_FAILED,
            EC_HTTP_POST_ERROR,
            EC_SEND_ERROR,
            EC_RECV_ERROR,
            EC_REMOTE_DISK_FULL,
            EC_REMOTE_FILE_EXISTS,
            EC_REMOTE_FILE_NOT_FOUND,
            EC_FAILED_INIT,
            EC_UNKNOWN_ERROR
        };

        /*! @class HTTPWorkListener
        *  @brief
        *	This listener interface is used for notifying callers
        */
        class Listener/* : public osl::RefTarget*/
        {
        public:
            //! \brief <b>Summary:</b>
            //! 	This function is called by HTTPWork(observable) to notify
            //! Listeners that this HTTP work is done, and the received data 
            //! from server is preserved in m_ptrRecvMDStream
            //! \note This function is called in another thread, you <b>MUST</b>
            //!     be care about the multi thread-safe problem
            //! \param  pw, the HTTPWork which is listened by this listener.
            //! you can call HTTPWork::getRecvDataStream() to get the server response string.
            virtual void OnFinishOKT( HttpRequest* pw ) = 0;

            //! \brief <b>Summary:</b>
            //! 	This function is called by HTTPWork(observable) to notify
            //! Listeners that the work is no done because something error.
            //! \note This function is called in another thread, you <b>MUST</b>
            //!     be care about the multi thread-safe problem
            //! \param hec, error code
            //! \param pw, the HTTPWork which is listened by this listener
            virtual void OnFinishErrorT(HttpErrorCode hec, HttpRequest* pw ) = 0;

        };//end of class Listener

        typedef std::list < Listener* > ListenerList;
        typedef std::map<std::string, std::string> StringStringMap;

    public:
        //! \brief 
        //! \param[] - const char * url
        //! \param[] - unsigned int timeout
        //! \param[] - bool nonblocking
        //! \return - 
        HttpRequest(const char* url, unsigned int timeout, bool nonblocking = true);

        virtual ~HttpRequest();

        void AddListener( Listener* pl )
        {
            listeners_.push_back(pl);
        }
        
        //! \brief <b>Summary:</b>
        //!     Add parameter to this request.
        //!     like key="password" , value="123456"
        //! \note If add the same more than one time, 
        //!       the new key-value will override the old key-value.
        //! \param[in] key, the name of the parameter
        //! \param[in] value, the value
        //! \return true, if add successfully
        //!	    false, if add failed
        virtual bool AddParameter( const char* key, const char* value )
        {
            parameters_[key] = value;
            return true;
        }

        virtual bool AddParameter( const std::string& key, const std::string& value )
        {
            parameters_[key] = value;
            return true;
        }

        //! \brief Do the HTTP request
        //! \return - bool
        bool DoRequest();

        const std::string& GetRespData() const
        {
            return recv_data_;
        }

    public:
        //! \brief 
        //! \param[in] - const std::string & url
        //! \param[out] - std::string & ip
        //! \param[out] - short& port
        //! \param[out] - std::string & uri
        //! \return - void
        static void ParseIpAndURI(const std::string& url, std::string& ip, short& port, std::string& uri);

    protected:
        virtual bool DoHttpRequest() = 0;

        virtual bool Init();

    protected:
        std::string  url_;
        std::string  ip_;
        std::string  uri_;
        short        port_;
        unsigned int timeout_; //millisecond

        ListenerList        listeners_;
        StringStringMap     parameters_;
        std::string         recv_data_;

        TcpPipe*            tcp_pipe_;
        bool                nonblocking_;
    };


}

