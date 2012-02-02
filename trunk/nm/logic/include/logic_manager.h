#pragma once

#include "osl/include/singleton.h"
#include "net/include/exp.h"
#include "logic/include/user_center.h"
#include "logic/include/run_config.h"

namespace nm
{
    #define s_pLogicManager   ( ::nm::LogicManager::getSingletonPtr() )
    class LogicManager : osl::Singleton<LogicManager>
    {
    public:
        LogicManager();

        bool Initialize();

        void Uninitialize();

        net::CURLService* GetCURLService() const { return curl_service_; }
        UserCenter*       GetUserCenter() const { return user_center_; }
        RunConfig*        GetRunConfig() const { return run_config_; }
        

    private:
        bool                initialized_;
        UserCenter*         user_center_;
        net::CURLServicePtr curl_service_;
        RunConfig*          run_config_;
    };
}

