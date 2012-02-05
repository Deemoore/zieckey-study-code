
#include "stdafx.h"
#include "osl/include/string_util.h"
#include "http/include/http_request.h"

namespace nm
{
    std::string HttpRequest::login_name_;
    std::string HttpRequest::login_pwd_;

    HttpRequest::HttpRequest(bool sync /*= true*/ ) : sync_request_(sync)
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
                return false;
            }
            osl::MemoryDataStream* rd = post_work_->getRecvDataStream();
            std::string utf8data(rd->data(),  rd->size());
            return GetModel().ParseFromJSON(osl::StringUtil::utf8ToMbs(utf8data));
        }
        else
        {
            assert(false);
            //TODO 等待实现异步调用
            return false;
        }
    }
    
    const std::string HttpRequest::GetErrorMsg() const
    {
        return post_work_->getHttpErrorCodeStr();
    }

    void HttpRequest::SetUserNamePwd( const std::string& user_name, const std::string& pwd )
    {
        login_name_ = user_name;
        login_pwd_  = pwd;
    }
}

