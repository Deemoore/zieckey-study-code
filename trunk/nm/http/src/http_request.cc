
#include "stdafx.h"
#include "osl/include/string_util.h"

namespace nm
{
    HttpRequest::HttpRequest(bool nonblocking /*= true*/ ) : nonblocking_(nonblocking)
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
        Dictionary::const_iterator ite(dict.begin());
        for (; it != ite; ++it)
        {
            post_work_->addParameter(osl::StringUtil::mbsToUtf8(it->first), osl::StringUtil::mbsToUtf8(it->second));
        }
        post_work_->setBlockingDoHttpRequest(true);
        bool ret = post_work_->doHttpBlockingRequest();
        if (!ret)
        {
            return false;
        }

        osl::MemoryDataStream* rd = post_work_->getRecvDataStream();
        std::string utf8data(rd->data(),  rd->size());
        return GetModel().ParseFromJSON(osl::StringUtil::utf8ToMbs(utf8data));
    }
    
    const std::string HttpRequest::GetErrorMsg() const
    {
        return post_work_->getHttpErrorCodeStr();
    }
}

