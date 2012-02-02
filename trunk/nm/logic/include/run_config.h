#pragma once

#include "osl/include/singleton.h"

#include <string>

namespace nm
{
    #define s_pRunConfig   ( ::nm::RunConfig::getSingletonPtr() )
    class RunConfig : public osl::Singleton<RunConfig>
    {
    public:
        RunConfig();

        const std::string& GetConsumptionRootURL() const { return consumption_root_url_;}
        const std::string& GetWareHouseRootURL() const { return ware_house_url_;}

        const std::string& GetLoginURL() const { return login_url_;}
        const std::string& GetDeleteProducedInformationURL() const { return DeleteProducedInformation_url_;}
        const std::string& GetSelectConsumeByGoodsGUIDURL() const { return SelectConsumeByGoodsGUID_url_;}
        const std::string& GetSelectMemberInfoByDynamicCodeURL() const { return SelectMemberInfoByDynamicCode_url_;}
        const std::string& GetSelectStoreTicketInfoListURL() const { return SelectStoreTicketInfoList_url_;}
        const std::string& GetGetCardPwdByCardIDURL() const { return GetCardPwdByCardID_url_;}
        const std::string& GetSelectMemberInfoByCardIDURL() const { return SelectMemberInfoByCardID_url_;}const std::string& GetSelectMemberInfoByCardIDURL() { return SelectMemberInfoByCardID_url_;} 
        const std::string& GetInsertCardInfoURL() { return InsertCardInfo_url_;} 
        const std::string& GetSelectGroupMembershipURL() { return SelectGroupMembership_url_;} 
        const std::string& GetStoreMemberConsumptionURL() { return StoreMemberConsumption_url_;} 
        const std::string& GetConsumerMemberURL() { return ConsumerMember_url_;} 
        const std::string& GetUnitedMemberConsumptionURL() { return UnitedMemberConsumption_url_;} 
        const std::string& GetConsumerNonMemberURL() { return ConsumerNonMember_url_;} 
        const std::string& GetInsertCommunicationInfoURL() { return InsertCommunicationInfo_url_;} 
        const std::string& GetGetCommunicationTypeListURL() { return GetCommunicationTypeList_url_;} 
        const std::string& GetGetCommonCustomerInfoByPhoneURL() { return GetCommonCustomerInfoByPhone_url_;} 
        const std::string& GetInsertApproveInfoURL() { return InsertApproveInfo_url_;} 
        const std::string& GetGetApproveInfoListURL() { return GetApproveInfoList_url_;} 
        const std::string& GetGetMemberCommunicateInfoListURL() { return GetMemberCommunicateInfoList_url_;} 
        const std::string& GetGetCommunicateInfoListURL() { return GetCommunicateInfoList_url_;} 
        const std::string& GetGetAccordingMemberInfoURL() { return GetAccordingMemberInfo_url_;} 
        const std::string& GetSelectCommonCustomerInfoURL() { return SelectCommonCustomerInfo_url_;} 
        const std::string& GetSelectCommonCustomerConsumeInfoURL() { return SelectCommonCustomerConsumeInfo_url_;} 
        const std::string& GetGetProductCategoryListURL() { return GetProductCategoryList_url_;} 
        const std::string& GetGetProducedInfoListURL() { return GetProducedInfoList_url_;} 
        const std::string& GetGetRoomTypeListURL() { return GetRoomTypeList_url_;} 
        const std::string& GetGetAllHousingDepartmentInfoListURL() { return GetAllHousingDepartmentInfoList_url_;} 
        const std::string& GetGetMemberInfoListURL() { return GetMemberInfoList_url_;} 
        const std::string& GetGetShopMemberLevelListURL() { return GetShopMemberLevelList_url_;} 
        const std::string& GetGetTicketTypeListURL() { return GetTicketTypeList_url_;} 
        const std::string& GetGetShopTicketEntityURL() { return GetShopTicketEntity_url_;} 
        const std::string& GetInsertShopTicketURL() { return InsertShopTicket_url_;} 
        const std::string& GetUpdateShopTicketURL() { return UpdateShopTicket_url_;} 
        const std::string& GetGetCompanyCouponEntityURL() { return GetCompanyCouponEntity_url_;} 
        const std::string& GetGetMemeberLevelListURL() { return GetMemeberLevelList_url_;} 
        const std::string& GetInsertCompanyCouponURL() { return InsertCompanyCoupon_url_;} 
        const std::string& GetUpdateCompanyCouponURL() { return UpdateCompanyCoupon_url_;} 
        const std::string& GetSelectConsumerSingleDetailsURL() { return SelectConsumerSingleDetails_url_;} 
        const std::string& GetSelectMemberConsumerSingleDetailsURL() { return SelectMemberConsumerSingleDetails_url_;} 
        const std::string& GetQueryGroupMemberConsumptionInfoURL() { return QueryGroupMemberConsumptionInfo_url_;} 
        const std::string& GetSelectGroupMembershipByAccountURL() { return SelectGroupMembershipByAccount_url_;} 
        const std::string& GetGetMemberConsumptionRecordsURL() { return GetMemberConsumptionRecords_url_;} 
        const std::string& GetCplusLoginURL() { return CplusLogin_url_;} 
        const std::string& GetInsertMachineInfoURL() { return InsertMachineInfo_url_;} 
        const std::string& GetGetBookingInformationNormalStateURL() { return GetBookingInformationNormalState_url_;} 
        const std::string& GetInsertMachineRunStateURL() { return InsertMachineRunState_url_;} 
        const std::string& GetGetMemberInfoByPageURL() { return GetMemberInfoByPage_url_;} 
        const std::string& GetGetCommonCustomerInfoListURL() { return GetCommonCustomerInfoList_url_;} 
        const std::string& GetSelectStoreUnitedMembershipInfoURL() { return SelectStoreUnitedMembershipInfo_url_;} 
        const std::string& GetReportLossMembershipCardURL() { return ReportLossMembershipCard_url_;} 
        const std::string& GetGetMemberLevelEntityURL() { return GetMemberLevelEntity_url_;} 
        const std::string& GetInsertMemberLevelURL() { return InsertMemberLevel_url_;} 
        const std::string& GetUpdateMemberLevelURL() { return UpdateMemberLevel_url_;} 
        const std::string& GetDeleteMemberLevelURL() { return DeleteMemberLevel_url_;} 
        const std::string& GetMemberRechargeStoresURL() { return MemberRechargeStores_url_;} 
        const std::string& GetGetMemberInfoURL() { return GetMemberInfo_url_;} 
        const std::string& GetInsertMemberInfoURL() { return InsertMemberInfo_url_;} 
        const std::string& GetUpdateMemberInfoURL() { return UpdateMemberInfo_url_;} 
        const std::string& GetValidateICCardIsNormalURL() { return ValidateICCardIsNormal_url_;} 
        const std::string& GetSelectDictionarySearchURL() { return SelectDictionarySearch_url_;} 
        const std::string& GetGetContactMemberLevelGuidURL() { return GetContactMemberLevelGuid_url_;} 
        const std::string& GetPhonePreTreatmentURL() { return PhonePreTreatment_url_;} 
        const std::string& GetUpdateMemberScheduledURL() { return UpdateMemberScheduled_url_;} 
        const std::string& GetGetProducedInformationListURL() { return GetProducedInformationList_url_;} 
        const std::string& GetInsertProducedInformationURL() { return InsertProducedInformation_url_;} 
        const std::string& GetUpdateProducedInformationURL() { return UpdateProducedInformation_url_;} 
        const std::string& GetGetProducedInformationEntryURL() { return GetProducedInformationEntry_url_;} 
        const std::string& GetDeleteProductCategoryURL() { return DeleteProductCategory_url_;} 
        const std::string& GetSelectProductInfoByTypeURL() { return SelectProductInfoByType_url_;} 
        const std::string& GetInsertProductCategoryURL() { return InsertProductCategory_url_;} 
        const std::string& GetUpdateProductCategoryURL() { return UpdateProductCategory_url_;} 
        const std::string& GetGetProductCategoryEntryURL() { return GetProductCategoryEntry_url_;} 
        const std::string& GetMembershipCardReplacementURL() { return MembershipCardReplacement_url_;} 
        const std::string& GetUpdateScheduledStatusURL() { return UpdateScheduledStatus_url_;} 
        const std::string& GetDeleteRoomTypeURL() { return DeleteRoomType_url_;} 
        const std::string& GetDeleteHousingDepartmentInfoURL() { return DeleteHousingDepartmentInfo_url_;} 
        const std::string& GetSelectRoomInfoByTypeURL() { return SelectRoomInfoByType_url_;} 
        const std::string& GetSelectHousingDepartmentInfoURL() { return SelectHousingDepartmentInfo_url_;} 
        const std::string& GetInsertHousingDepartmentInfoURL() { return InsertHousingDepartmentInfo_url_;} 
        const std::string& GetUpdateHousingDepartmentInfoURL() { return UpdateHousingDepartmentInfo_url_;} 
        const std::string& GetGetHousingDepartmentInfoEntryURL() { return GetHousingDepartmentInfoEntry_url_;} 
        const std::string& GetInsertRoomTypeURL() { return InsertRoomType_url_;} 
        const std::string& GetUpdateRoomTypeURL() { return UpdateRoomType_url_;} 
        const std::string& GetGetViewShopTicketListURL() { return GetViewShopTicketList_url_;} 
        const std::string& GetDeleteShopTicketURL() { return DeleteShopTicket_url_;} 
        const std::string& GetDeleteCompanyCouponURL() { return DeleteCompanyCoupon_url_;} 
        const std::string& GetUpdateMemberPhoneAndAddressURL() { return UpdateMemberPhoneAndAddress_url_;} 
        const std::string& GetDeliveryServiceURL() { return DeliveryService_url_;} 
        const std::string& GetGetStoreUnitedMembershipInfoURL() { return GetStoreUnitedMembershipInfo_url_;} 
        const std::string& GetSelectStoreUnitedMembershipConsumeInfoURL() { return SelectStoreUnitedMembershipConsumeInfo_url_;}
        const std::string& GetDeliveryServiceDetailsURL() { return DeliveryServiceDetails_url_;}

    private:
        std::string consumption_root_url_;
        std::string ware_house_url_;

        std::string login_url_;
        std::string DeleteProducedInformation_url_;
        std::string SelectConsumeByGoodsGUID_url_;
        std::string SelectMemberInfoByDynamicCode_url_;
        std::string SelectStoreTicketInfoList_url_;
        std::string GetCardPwdByCardID_url_;
        std::string SelectMemberInfoByCardID_url_;
        std::string InsertCardInfo_url_;
        std::string SelectGroupMembership_url_;
        std::string StoreMemberConsumption_url_;
        std::string ConsumerMember_url_;
        std::string UnitedMemberConsumption_url_;
        std::string ConsumerNonMember_url_;
        std::string InsertCommunicationInfo_url_;
        std::string GetCommunicationTypeList_url_;
        std::string GetCommonCustomerInfoByPhone_url_;
        std::string InsertApproveInfo_url_;
        std::string GetApproveInfoList_url_;
        std::string GetMemberCommunicateInfoList_url_;
        std::string GetCommunicateInfoList_url_;
        std::string GetAccordingMemberInfo_url_;
        std::string SelectCommonCustomerInfo_url_;
        std::string SelectCommonCustomerConsumeInfo_url_;
        std::string GetProductCategoryList_url_;
        std::string GetProducedInfoList_url_;
        std::string GetRoomTypeList_url_;
        std::string GetAllHousingDepartmentInfoList_url_;
        std::string GetMemberInfoList_url_;
        std::string GetShopMemberLevelList_url_;
        std::string GetTicketTypeList_url_;
        std::string GetShopTicketEntity_url_;
        std::string InsertShopTicket_url_;
        std::string UpdateShopTicket_url_;
        std::string GetCompanyCouponEntity_url_;
        std::string GetMemeberLevelList_url_;
        std::string InsertCompanyCoupon_url_;
        std::string UpdateCompanyCoupon_url_;
        std::string SelectConsumerSingleDetails_url_;
        std::string SelectMemberConsumerSingleDetails_url_;
        std::string QueryGroupMemberConsumptionInfo_url_;
        std::string SelectGroupMembershipByAccount_url_;
        std::string GetMemberConsumptionRecords_url_;
        std::string CplusLogin_url_;
        std::string InsertMachineInfo_url_;
        std::string GetBookingInformationNormalState_url_;
        std::string InsertMachineRunState_url_;
        std::string GetMemberInfoByPage_url_;
        std::string GetCommonCustomerInfoList_url_;
        std::string SelectStoreUnitedMembershipInfo_url_;
        std::string ReportLossMembershipCard_url_;
        std::string GetMemberLevelEntity_url_;
        std::string InsertMemberLevel_url_;
        std::string UpdateMemberLevel_url_;
        std::string DeleteMemberLevel_url_;
        std::string MemberRechargeStores_url_;
        std::string GetMemberInfo_url_;
        std::string InsertMemberInfo_url_;
        std::string UpdateMemberInfo_url_;
        std::string ValidateICCardIsNormal_url_;
        std::string SelectDictionarySearch_url_;
        std::string GetContactMemberLevelGuid_url_;
        std::string PhonePreTreatment_url_;
        std::string UpdateMemberScheduled_url_;
        std::string GetProducedInformationList_url_;
        std::string InsertProducedInformation_url_;
        std::string UpdateProducedInformation_url_;
        std::string GetProducedInformationEntry_url_;
        std::string DeleteProductCategory_url_;
        std::string SelectProductInfoByType_url_;
        std::string InsertProductCategory_url_;
        std::string UpdateProductCategory_url_;
        std::string GetProductCategoryEntry_url_;
        std::string MembershipCardReplacement_url_;
        std::string UpdateScheduledStatus_url_;
        std::string DeleteRoomType_url_;
        std::string DeleteHousingDepartmentInfo_url_;
        std::string SelectRoomInfoByType_url_;
        std::string SelectHousingDepartmentInfo_url_;
        std::string InsertHousingDepartmentInfo_url_;
        std::string UpdateHousingDepartmentInfo_url_;
        std::string GetHousingDepartmentInfoEntry_url_;
        std::string InsertRoomType_url_;
        std::string UpdateRoomType_url_;
        std::string GetViewShopTicketList_url_;
        std::string DeleteShopTicket_url_;
        std::string DeleteCompanyCoupon_url_;
        std::string UpdateMemberPhoneAndAddress_url_;
        std::string DeliveryService_url_;
        std::string GetStoreUnitedMembershipInfo_url_;
        std::string SelectStoreUnitedMembershipConsumeInfo_url_;
        std::string DeliveryServiceDetails_url_;
    };
}