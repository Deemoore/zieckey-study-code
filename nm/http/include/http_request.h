#pragma once

#include <string.h>

#include <string>
#include <sstream>
#include <list>
#include <map>
#include <algorithm>

#include "osl/include/object.h"
#include "net/include/exp.h"
#include "net/include/curl_work.h"
#include "net/include/http_post_work.h"

namespace nm
{
    struct TopModel
    {
        virtual bool ParseFromJSON(const std::string& json_str) = 0;
    };

    typedef std::map<std::string, std::string> Dictionary;
    typedef Dictionary stringstringmap;

    class HttpRequest : public osl::Object
    {
    public:
        //! \brief 构造函数
        //! \param[] - bool nonblocking
        //! \return - 
        HttpRequest(bool nonblocking = true);

        virtual ~HttpRequest();

        //! \brief 添加参数
        //! \param[in] - const std::string & key
        //! \param[in] - const std::string & value
        //! \return - void
        void AddParameter(const std::string& key, const std::string& value);

        //! \brief Do the HTTP request
        //! \return - bool
        bool DoRequest();

        //如果DoRequest失败，调用这个接口得到错误信息
        const std::string GetErrorMsg() const;

    protected:
        virtual const Dictionary& GetParameters() = 0;
        virtual const std::string& GetURL() = 0;
        virtual TopModel& GetModel() = 0;

    private:
        bool nonblocking_;
        net::HttpPostWorkPtr post_work_;
    };

}

