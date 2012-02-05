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
        //! \param[] - bool sync
        //! \return - 
        HttpRequest(bool sync = true);

        virtual ~HttpRequest();

        //! \brief 添加参数
        //! \param[in] - const std::string & key
        //! \param[in] - const std::string & value
        //! \return - void
        void AddParameter(const std::string& key, const std::string& value);

        //! \brief Do the HTTP request
        //! \return - bool
        bool DoRequest();

        //! \brief 如果 DoRequest() 调用失败，上层调用这个接口得到错误信息
        //! \return - const std::string
        const std::string GetErrorMsg() const;

        //! \brief 得到参数列表
        //! \return - const Dictionary&
        const Dictionary& GetParameters() const;

        //! \brief 设置登录用户名和密码
        //! \warning 只需要在登录成功后设置一次
        //! \param[in] - const std::string & user_name
        //! \param[in] - const std::string & pwd
        //! \return - void
        static void SetUserNamePwd(const std::string& user_name, const std::string& pwd);

    protected:
        virtual const std::string& GetURL() = 0;
        virtual TopModel& GetModel() = 0;

    protected:
        nm::Dictionary  parameters_; //请求参数的 key-value 集合

    private:
        bool sync_request_;
        net::HttpPostWorkPtr post_work_;

        static std::string login_name_;
        static std::string login_pwd_;
    };


    //////////////////////////////////////////////////////////////////////////
    inline const Dictionary& HttpRequest::GetParameters() const 
    {
        return parameters_;
    }

}

