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

namespace net
{
    class CURLService;
}

namespace nm
{
    struct TopModel
    {
        virtual bool ParseFromJSON(const std::string& json_str) = 0;
    };

    typedef std::map<std::string, std::string> Dictionary;
    typedef Dictionary stringstringmap;

    class HttpRequest : public net::CURLWork::Listener
    {
    public:
        class Listener : public osl::Object
        {
        public:
            //! \brief 异步请求的回调接口
            //! \note 已经同步到主线程
            //! \param[in] - HttpRequest * request
            //! \param[in] - bool success - true 表面请求成功，否则失败
            //!     如果失败，可以通过 HttpRequest::GetErrorMsg 来获取失败信息
            //! \return - void
            virtual void OnFinished(HttpRequest* request, bool success) = 0;
        };
        typedef osl::RefPtr<Listener> ListenerPtr;
        typedef std::list<ListenerPtr> ListenerPtrList;

    public:
        //! \brief 构造函数
        //! \param[] - bool sync
        //! \return - 
        HttpRequest(bool sync = true);

        //! \brief 设置是否为同步调用
        //! \param[in] - bool sync - true 同步调用 ; false 异步调用
        //! \return - void
        void SetSyncRequest(bool sync);

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
        const std::string& GetErrorMsg() const;

        //! \brief 得到参数列表
        //! \return - const Dictionary&
        const Dictionary& GetParameters() const;
        Dictionary& GetParameters();

        //! \brief 设置登录用户名和密码
        //! \warning 只需要在登录成功后设置一次
        //! \param[in] - const std::string & user_name
        //! \param[in] - const std::string & pwd
        //! \return - void
        static void SetUserNamePwd(const std::string& user_name, const std::string& pwd);
        
        //! 处理异步调用的线程池，全局调用一次
        static void SetCURLService(net::CURLService* service);

        //! 顶层主线程调用该函数派发完成的请求
        static void DispatchFinishedRequests();
    public:
        //////////////////////////////////////////////////////////////////////////
        // 异步接口

        //! \brief 当请求是异步请求是，需要添加一个监听器（回调接口）
        //!     当http请求完成时，接口<code>Listener::OnFinishedT</code>会被网络线程调用
        //! \warning 注意线程安全问题！！
        //! \param[in] - Listener * listener
        //! \return - void
        void AddListener(Listener* listener);

    public:
        
        //! \brief 得到请求URL
        //! \return - const std::string&
        virtual const std::string& GetURL() = 0;


        //! \brief 得到服务器返回的结构体model
        //! \return - TopModel&
        virtual TopModel& GetModel() = 0;

    private:
        virtual void onFinishOKT( net::CURLWork* pw );
        virtual void onFinishErrorT( net::HttpErrorCode hec, const osl::StringA& errmsg, net::CURLWork* pw );

    protected:
        nm::Dictionary  parameters_; //请求参数的 key-value 集合

    private:
        bool sync_request_;
        net::HttpPostWorkPtr post_work_;

        std::string error_msg_;
        bool request_ok;

        ListenerPtrList listeners_;

        static std::string  login_name_;
        static std::string  login_pwd_;
        static net::CURLService* curl_service_;

        typedef std::list<HttpRequest*> HttpRequestList;
        static HttpRequestList finished_requests_;
    };


    //////////////////////////////////////////////////////////////////////////
    inline const Dictionary& HttpRequest::GetParameters() const 
    {
        return parameters_;
    }

    //////////////////////////////////////////////////////////////////////////
    inline Dictionary& HttpRequest::GetParameters()
    {
        return parameters_;
    }

}

