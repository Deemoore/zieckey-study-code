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
            //! \brief �첽����Ļص��ӿ�
            //! \note �Ѿ�ͬ�������߳�
            //! \param[in] - HttpRequest * request
            //! \param[in] - bool success - true ��������ɹ�������ʧ��
            //!     ���ʧ�ܣ�����ͨ�� HttpRequest::GetErrorMsg ����ȡʧ����Ϣ
            //! \return - void
            virtual void OnFinished(HttpRequest* request, bool success) = 0;
        };
        typedef osl::RefPtr<Listener> ListenerPtr;
        typedef std::list<ListenerPtr> ListenerPtrList;

    public:
        //! \brief ���캯��
        //! \param[] - bool sync
        //! \return - 
        HttpRequest(bool sync = true);

        //! \brief �����Ƿ�Ϊͬ������
        //! \param[in] - bool sync - true ͬ������ ; false �첽����
        //! \return - void
        void SetSyncRequest(bool sync);

        virtual ~HttpRequest();

        //! \brief ��Ӳ���
        //! \param[in] - const std::string & key
        //! \param[in] - const std::string & value
        //! \return - void
        void AddParameter(const std::string& key, const std::string& value);

        //! \brief Do the HTTP request
        //! \return - bool
        bool DoRequest();

        //! \brief ��� DoRequest() ����ʧ�ܣ��ϲ��������ӿڵõ�������Ϣ
        //! \return - const std::string
        const std::string& GetErrorMsg() const;

        //! \brief �õ������б�
        //! \return - const Dictionary&
        const Dictionary& GetParameters() const;
        Dictionary& GetParameters();

        //! \brief ���õ�¼�û���������
        //! \warning ֻ��Ҫ�ڵ�¼�ɹ�������һ��
        //! \param[in] - const std::string & user_name
        //! \param[in] - const std::string & pwd
        //! \return - void
        static void SetUserNamePwd(const std::string& user_name, const std::string& pwd);
        
        //! �����첽���õ��̳߳أ�ȫ�ֵ���һ��
        static void SetCURLService(net::CURLService* service);

        //! �������̵߳��øú����ɷ���ɵ�����
        static void DispatchFinishedRequests();
    public:
        //////////////////////////////////////////////////////////////////////////
        // �첽�ӿ�

        //! \brief ���������첽�����ǣ���Ҫ���һ�����������ص��ӿڣ�
        //!     ��http�������ʱ���ӿ�<code>Listener::OnFinishedT</code>�ᱻ�����̵߳���
        //! \warning ע���̰߳�ȫ���⣡��
        //! \param[in] - Listener * listener
        //! \return - void
        void AddListener(Listener* listener);

    public:
        
        //! \brief �õ�����URL
        //! \return - const std::string&
        virtual const std::string& GetURL() = 0;


        //! \brief �õ����������صĽṹ��model
        //! \return - TopModel&
        virtual TopModel& GetModel() = 0;

    private:
        virtual void onFinishOKT( net::CURLWork* pw );
        virtual void onFinishErrorT( net::HttpErrorCode hec, const osl::StringA& errmsg, net::CURLWork* pw );

    protected:
        nm::Dictionary  parameters_; //��������� key-value ����

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

