#pragma once

#include <string>

#include "osl/include/base64.h"
#include "net/include/exp.h"

#include "http/include/http_request.h"
#include "logic/include/run_config.h"
#include "logic/include/model_define.h"

namespace nm
{
    class UserCenter
    {
    public:
        typedef std::map<std::string, std::string> stringstringmap;

    public:
        UserCenter(net::CURLService* service);
        ~UserCenter();

        void SetUserNamePwd(const std::string& user_name, const std::string& pwd);

        //
        bool DoHttpPost(const std::string& url, const stringstringmap& kvmap, net::CURLWork::Listener* listener);

        //! \brief 
        //! \param[in] - const std::string & guid
        //! \param[in] - net::CURLWork::Listener * listener
        //! \return - bool
        bool DeleteProducedInformation(const std::string& guid, net::CURLWork::Listener* listener);

        //! \brief 
        //! \param[in] - const std::string & goodsGuid
        //! \param[in] - const std::string & begintime
        //! \param[in] - const std::string & endtime
        //! \param[in] - const std::string & firstRowNumber
        //! \param[in] - const std::string & lastRowNumber
        //! \param[in] - const std::string & sortField  - 原始值，不需要base64，该接口自己会处理好
        //! \param[in] - const std::string & sortType
        //! \param[in] - net::CURLWork::Listener * listener
        //! \return - bool
        bool SelectConsumeByGoodsGUID(
            const std::string& goodsGuid,
            const std::string& begintime,
            const std::string& endtime,
            const std::string& firstRowNumber,
            const std::string& lastRowNumber,
            const std::string& sortField,//the original value, no base64
            const std::string& sortType, 
            net::CURLWork::Listener* listener);

        bool SelectMemberInfoByDynamicCode(
            const std::string& dynamicCode,
            net::CURLWork::Listener* listener);


        bool SelectStoreTicketInfoList(
            const std::string& money,
            const std::string& shopGuid,
            const std::string& memberlevelGuid,
            const int flag,
            net::CURLWork::Listener* listener);


        bool GetCardPwdByCardID(
            const std::string& shopGuid,
            const std::string& physicalCard,
            net::CURLWork::Listener* listener);

        bool SelectMemberInfoByCardID(
            const std::string& shopGuid,
            const std::string& memberGUID,
            net::CURLWork::Listener* listener);

        //! \brief 
        //! \param[in] - const std::string & shopGuid
        //! \param[in] - const std::string & cardID
        //! \param[in] - const std::string & physicalCard
        //! \param[in] - const std::string & operatorName  - 原始值，不需要base64，该接口自己会处理好
        //! \param[in] - net::CURLWork::Listener * listener
        //! \return - bool
        bool InsertCardInfo(
            const std::string& shopGuid,
            const std::string& cardID,
            const std::string& physicalCard,
            const std::string& operatorName,
            net::CURLWork::Listener* listener);


        bool SelectGroupMembership(
            const int firstRowNumber,
            const int lastRowNumber,
            const std::string& sortField,
            const std::string& sortType,
            const std::string& shopGuid,
            net::CURLWork::Listener* listener);


        bool StoreMemberConsumption(
            const std::string& cardID,
            const std::string& memberGuid,
            const double       storedValue,
            const std::string& shopGuid,
            const double       cashmoney,
            const std::string& ticketGUID,
            const double       OfferAmount,
            const std::string& code,
            const int          HasDetails,
            const std::string& operaGuid,
            net::CURLWork::Listener* listener);

        //! \brief 
        //! \param[in] - const std::string & Json1 - 原始值，不需要base64，该接口自己会处理好
        //! \param[in] - const std::string & shopGuid
        //! \param[in] - const int HasDetails
        //! \param[in] - net::CURLWork::Listener * listener
        //! \return - bool
        bool ConsumerMember(
            const std::string& Json1,
            const std::string& shopGuid,
            const int HasDetails,
            net::CURLWork::Listener* listener);


        bool UnitedMemberConsumption(
            const std::string& cardID,
            const std::string& memberGuid,
            const double       storedValue,
            const std::string& shopGuid,
            const double       cashmoney,
            const std::string& ticketGUID,
            const double       OfferAmount,
            const std::string& code,
            const int          HasDetails,
            const std::string& operaGuid,
            net::CURLWork::Listener* listener);

        //! \brief 
        //! \param[in] - const std::string & Json1 - 原始值，不需要base64，该接口自己会处理好
        //! \param[in] - net::CURLWork::Listener * listener
        //! \return - bool
        bool ConsumerNonMember(
            const std::string& Json1,
            net::CURLWork::Listener* listener);

        //! \brief 
        //! \param[in] - const std::string & Json - 原始值，不需要base64，该接口自己会处理好
        //! \param[in] - net::CURLWork::Listener * listener
        //! \return - bool
        bool InsertCommunicationInfo(
            const std::string& Json,
            net::CURLWork::Listener* listener);


        //! \brief 
        //! \param[in] - const std::string & username
        //! \param[in] - const std::string & pwd
        //! \param[in] - net::CURLWork::Listener * listener
        //! \return - bool
        bool Login(const std::string& username, 
                   const std::string& pwd, 
                   net::CURLWork::Listener* listener);

        //! \brief 
        //! \param[in] - const char * login_resp_msg
        //! \param[in] - size_t login_resp_msg_len
        //! \param[out] - UMSBaseUserinfo & user_info
        //! \return - bool return true when parse OK!
        static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMSBaseUserinfo& model);

		//! \brief 
		//! \param[in] - const char * resp_msg
		//! \param[in] - size_t resp_msg_len
		//! \param[in] - model::ListViewOPRProductConsumDetail & model
		//! \return - bool
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListViewOPRProductConsumDetail& model);

		//! \brief 
		//! \param[in] - const char * resp_msg
		//! \param[in] - size_t resp_msg_len
		//! \param[in] - model::ListUMSOPRMarkShopLevel & model
		//! \return - bool
        static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ViewOPRProductConsumDetailPagging& model_list);

        //! \brief 
        //! \param[in] - const char * resp_msg
        //! \param[in] - size_t resp_msg_len
        //! \param[in] - model::ViewMember & model
        //! \return - bool
        static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ViewMember& model);

		//! \brief 
		//! \param[in] - const char * resp_msg
		//! \param[in] - size_t resp_msg_len
		//! \param[in] - model::VIEW_Company_Coupon & model_list
		//! \return - bool
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListVIEW_Company_Coupon& model_list);



		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListMemberInputpPwdiIsok& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListVIEW_MerchantAccountDetails& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListVIEW_MerchantAccountDetailsPagging& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListMessage& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_OPR_CommunicationInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_OPR_CommunicationTypeInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListVIEW_OPR_CommonCustomerInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_OPR_ApproveInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListVIEW_GetCommunicationRecordByBusinessMan& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_OPRCommunicationrecordPagging& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListVIEW_POS_ShopMemberInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_Customer_info& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_OPR_Consumption_Business_view& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_Ordinary_Consumption_record& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_BASE_RoomTypeInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_BASE_RoomInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListVIEW_MemberAndOrdinary_Info_View& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_BASE_ShopMemberLeave& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_Coupon& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_Company_ShopCoupon& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_Company_Coupon& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_OPR_MemberOrderInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_dictionaryDetails& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListReturnmessage& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_BASE_ShopMemberInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_BASE_MemberCardInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListVIEW_POS_ShopMemberInfoPage& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_OPR_MemberCardStateUpdateInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMSBaseAreainfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMSMemberLevel& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMSConsumeMenuSingleDetailView& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMSGroupMemberCashDetail& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMSGroupMemberCashView& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMSLocalMemberCashDetail& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMSLocalMemberCashView& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_OPR_MachineInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMSWaitMemberInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMS_OPR_CommonCustomerInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListVIEW_CommonCustomerInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListUMSUniteMemberInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListVIEW_UniteMemberInfoPage& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListproductInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListViewProductInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListViewProductInfoPagging& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListproductTypeInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListViewRoomOrderInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListViewRoomOrderInfoPagging& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListroomInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListViewRoomInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListViewFavourableTicketInfo& model_list);
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::ListConsumerSingleDetails& model_list);
		//! \brief 
		//! \param[in] - const char * resp_msg
		//! \param[in] - size_t resp_msg_len
		//! \param[in] - model::UMSUniteMemberInfo & model_list
		//! \return - bool
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::UMSUniteMemberInfo& model_list);
		//! \brief 
		//! \param[in] - const char * resp_msg
		//! \param[in] - size_t resp_msg_len
		//! \param[in] - model::uniteMemberConsumeInfoPagging & model_list
		//! \return - bool
		static bool ParseRespMsg(const char* resp_msg, size_t resp_msg_len, model::uniteMemberConsumeInfoPagging& model_list);
    private:
        net::CURLServicePtr curl_service_;
        std::string         user_name_;
        std::string         user_pwd_;

    private:
        bool DoHttpPost(const std::string& url, const std::string& data, net::CURLWork::Listener* listener);
    };
}


