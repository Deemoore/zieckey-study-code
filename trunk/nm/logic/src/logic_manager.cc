#include "stdafx.h"

#include "logic/include/logic_manager.h"

template<> nm::LogicManager* osl::Singleton<nm::LogicManager>::ms_Singleton = NULL;

namespace nm
{

    LogicManager::LogicManager() 
        : initialized_(false)
        , user_center_(NULL)
        , run_config_(NULL)
    {
    }

    bool LogicManager::Initialize()
    {
        if (initialized_)
        {
            return true;
        }

        curl_service_ = new net::CURLService(1);
        bool start_ok = curl_service_->start();
        if (!start_ok)
        {
            fprintf(stderr, "curl start failed!\n");
            return false;
        }

        user_center_ = new UserCenter(curl_service_);

        run_config_  = new RunConfig();

        initialized_ = true;

        return true;
    }

    void LogicManager::Uninitialize()
    {
        H_SAFE_DELETE(user_center_);
        
        curl_service_->stop();
        curl_service_ = NULL;
    }
}

