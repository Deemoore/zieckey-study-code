
#include "stdafx.h"
#include "osl/include/string_util.h"
#include "http/include/http_request.h"
#include "net/include/curl_service.h"

namespace nm
{
    std::string HttpRequest::login_name_;
    std::string HttpRequest::login_pwd_;

    net::CURLService* HttpRequest::curl_service_ = NULL;
    HttpRequest::HttpRequestList HttpRequest::finished_requests_;

    static osl::Lock finished_requests_lock;

    HttpRequest::HttpRequest(bool sync /*= true*/ ) 
        : sync_request_(sync)
        , request_ok(true)
    {
    }

    HttpRequest::~HttpRequest()
    {
    }

    void HttpRequest::AddParameter( const std::string& key, const std::string& value )
    {
        Dictionary& param = const_cast<Dictionary&>(GetParameters());
        param[key] = value;
    }

    bool HttpRequest::DoRequest()
    {
        post_work_ = new net::HttpPostWork(GetURL());
        const Dictionary& dict = GetParameters();
        Dictionary::const_iterator it(dict.begin());
        Dictionary::const_iterator ite(dict.end());
        for (; it != ite; ++it)
        {
            post_work_->addParameter(osl::StringUtil::mbsToUtf8(it->first), osl::StringUtil::mbsToUtf8(it->second));
        }

        if (HttpRequest::login_name_.size() > 0)
        {
            post_work_->addParameter("ApiKey", osl::StringUtil::mbsToUtf8(HttpRequest::login_name_));
            post_work_->addParameter("Sign", osl::StringUtil::mbsToUtf8(HttpRequest::login_pwd_));
        }
        
        if (sync_request_)
        {
            post_work_->setBlockingDoHttpRequest(sync_request_);
            bool ret = post_work_->doHttpBlockingRequest();
            if (!ret)
            {
                request_ok = false;
                error_msg_ = post_work_->getHttpErrorCodeStr();
                return false;
            }
            request_ok = true;
            osl::MemoryDataStream* rd = post_work_->getRecvDataStream();
            std::string utf8data(rd->data(),  rd->size());
            return GetModel().ParseFromJSON(osl::StringUtil::utf8ToMbs(utf8data));
        }
        else
        {
            assert(listeners_.size() > 0 && "async call MUST has listeners!");
            post_work_->addListener(this);
            curl_service_->addWorkT(post_work_);
            return false;
        }
    }
    
    const std::string& HttpRequest::GetErrorMsg() const
    {
        return error_msg_;//post_work_->getHttpErrorCodeStr();
    }

    void HttpRequest::SetUserNamePwd( const std::string& user_name, const std::string& pwd )
    {
        login_name_ = user_name;
        login_pwd_  = pwd;
    }

    void HttpRequest::AddListener( Listener* listener )
    {
        listeners_.push_back(listener);
    }

    void HttpRequest::SetCURLService( net::CURLService* service )
    {
        curl_service_ = service;
    }

    void HttpRequest::onFinishOKT( net::CURLWork* pw )
    {
        osl::MemoryDataStream* rd = post_work_->getRecvDataStream();
        std::string utf8data(rd->data(),  rd->size());
        std::string gbkdata = osl::StringUtil::utf8ToMbs(utf8data);
        bool parse = GetModel().ParseFromJSON(gbkdata);
        if (!parse)
        {
            error_msg_.reserve(64 + gbkdata.size());
            error_msg_.append("HTTP request OK. But JSON parse failed:\n");
            error_msg_.append(gbkdata);
            request_ok = false;
        }

        request_ok = true;

        ListenerPtrList::iterator it(listeners_.begin());
        ListenerPtrList::iterator ite(listeners_.end());
        for (; it != ite; ++it)
        {
            (*it)->OnFinishedT(this, this->request_ok);
        }
    }

    void HttpRequest::onFinishErrorT( net::HttpErrorCode hec, const osl::StringA& errmsg, net::CURLWork* pw )
    {
        error_msg_ = errmsg;
        request_ok = false;

        ListenerPtrList::iterator it(listeners_.begin());
        ListenerPtrList::iterator ite(listeners_.end());
        for (; it != ite; ++it)
        {
            (*it)->OnFinishedT(this, this->request_ok);
        }

//         {
//             H_AUTOLOCK(finished_requests_lock);
//             this->ref();
//             finished_requests_.push_back(this);
//         }
    }

    void HttpRequest::SetSyncRequest( bool sync )
    {
        sync_request_ = sync;
    }

    void HttpRequest::RemoveListener( Listener* listener )
    {
        listeners_.remove(listener);
    }
//     void HttpRequest::DispatchFinishedRequests()
//     {
//         HttpRequestList vect;
// 
//         {
//             H_AUTOLOCK(finished_requests_lock);
//             vect.swap(finished_requests_);
//         }
// 
//         for (HttpRequestList::iterator itvect(vect.begin()); itvect != vect.end(); ++itvect)
//         {
//             ListenerPtrList::iterator it((*itvect)->listeners_.begin());
//             ListenerPtrList::iterator ite((*itvect)->listeners_.end());
//             for (; it != ite; ++it)
//             {
//                 (*it)->OnFinished((*itvect), (*itvect)->request_ok);
//                 (*itvect)->unref();
//             }
//         }
//     }
}

