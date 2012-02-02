#include "stdafx.h"

#include "logic/include/run_config.h"

template<> nm::RunConfig* osl::Singleton<nm::RunConfig>::ms_Singleton = NULL;

namespace nm
{
    RunConfig::RunConfig()
    {
        consumption_root_url_ = "http://119.254.69.18/CplusConsumptionService/";
        ware_house_url_       = "http://119.254.69.18/CplusWarehouseService/";

        login_url_                          = consumption_root_url_ + "CplusLogin";
        DeleteProducedInformation_url_      = consumption_root_url_ + "DeleteProducedInformation";
        SelectConsumeByGoodsGUID_url_       = consumption_root_url_ + "SelectConsumeByGoodsGUID";
        SelectMemberInfoByDynamicCode_url_  = consumption_root_url_ + "SelectMemberInfoByDynamicCode";
        SelectStoreTicketInfoList_url_      = consumption_root_url_ + "SelectStoreTicketInfoList";
        GetCardPwdByCardID_url_             = consumption_root_url_ + "GetCardPwdByCardID";
        SelectMemberInfoByCardID_url_ = consumption_root_url_ + "SelectMemberInfoByCardID"; 
        InsertCardInfo_url_ = consumption_root_url_ + "InsertCardInfo"; 
        SelectGroupMembership_url_ = consumption_root_url_ + "SelectGroupMembership"; 
        StoreMemberConsumption_url_ = consumption_root_url_ + "StoreMemberConsumption"; 
        ConsumerMember_url_ = consumption_root_url_ + "ConsumerMember"; 
        UnitedMemberConsumption_url_ = consumption_root_url_ + "UnitedMemberConsumption"; 
        ConsumerNonMember_url_ = consumption_root_url_ + "ConsumerNonMember"; 
        InsertCommunicationInfo_url_ = consumption_root_url_ + "InsertCommunicationInfo"; 
        GetCommunicationTypeList_url_ = consumption_root_url_ + "GetCommunicationTypeList"; 
        GetCommonCustomerInfoByPhone_url_ = consumption_root_url_ + "GetCommonCustomerInfoByPhone"; 
        InsertApproveInfo_url_ = consumption_root_url_ + "InsertApproveInfo"; 
        GetApproveInfoList_url_ = consumption_root_url_ + "GetApproveInfoList"; 
        GetMemberCommunicateInfoList_url_ = consumption_root_url_ + "GetMemberCommunicateInfoList"; 
        GetCommunicateInfoList_url_ = consumption_root_url_ + "GetCommunicateInfoList"; 
        GetAccordingMemberInfo_url_ = consumption_root_url_ + "GetAccordingMemberInfo"; 
        SelectCommonCustomerInfo_url_ = consumption_root_url_ + "SelectCommonCustomerInfo"; 
        SelectCommonCustomerConsumeInfo_url_ = consumption_root_url_ + "SelectCommonCustomerConsumeInfo"; 
        GetProductCategoryList_url_ = consumption_root_url_ + "GetProductCategoryList"; 
        GetProducedInfoList_url_ = consumption_root_url_ + "GetProducedInfoList"; 
        GetRoomTypeList_url_ = consumption_root_url_ + "GetRoomTypeList"; 
        GetAllHousingDepartmentInfoList_url_ = consumption_root_url_ + "GetAllHousingDepartmentInfoList"; 
        GetMemberInfoList_url_ = consumption_root_url_ + "GetMemberInfoList"; 
        GetShopMemberLevelList_url_ = consumption_root_url_ + "GetShopMemberLevelList"; 
        GetTicketTypeList_url_ = consumption_root_url_ + "GetTicketTypeList"; 
        GetShopTicketEntity_url_ = consumption_root_url_ + "GetShopTicketEntity"; 
        InsertShopTicket_url_ = consumption_root_url_ + "InsertShopTicket"; 
        UpdateShopTicket_url_ = consumption_root_url_ + "UpdateShopTicket"; 
        GetCompanyCouponEntity_url_ = consumption_root_url_ + "GetCompanyCouponEntity"; 
        GetMemeberLevelList_url_ = consumption_root_url_ + "GetMemeberLevelList"; 
        InsertCompanyCoupon_url_ = consumption_root_url_ + "InsertCompanyCoupon"; 
        UpdateCompanyCoupon_url_ = consumption_root_url_ + "UpdateCompanyCoupon"; 
        SelectConsumerSingleDetails_url_ = consumption_root_url_ + "SelectConsumerSingleDetails"; 
        SelectMemberConsumerSingleDetails_url_ = consumption_root_url_ + "SelectMemberConsumerSingleDetails"; 
        QueryGroupMemberConsumptionInfo_url_ = consumption_root_url_ + "QueryGroupMemberConsumptionInfo"; 
        SelectGroupMembershipByAccount_url_ = consumption_root_url_ + "SelectGroupMembershipByAccount"; 
        GetMemberConsumptionRecords_url_ = consumption_root_url_ + "GetMemberConsumptionRecords"; 
        CplusLogin_url_ = consumption_root_url_ + "CplusLogin"; 
        InsertMachineInfo_url_ = consumption_root_url_ + "InsertMachineInfo"; 
        GetBookingInformationNormalState_url_ = consumption_root_url_ + "GetBookingInformationNormalState"; 
        InsertMachineRunState_url_ = consumption_root_url_ + "InsertMachineRunState"; 
        GetMemberInfoByPage_url_ = consumption_root_url_ + "GetMemberInfoByPage"; 
        GetCommonCustomerInfoList_url_ = consumption_root_url_ + "GetCommonCustomerInfoList"; 
        SelectStoreUnitedMembershipInfo_url_ = consumption_root_url_ + "SelectStoreUnitedMembershipInfo"; 
        ReportLossMembershipCard_url_ = consumption_root_url_ + "ReportLossMembershipCard"; 
        GetMemberLevelEntity_url_ = consumption_root_url_ + "GetMemberLevelEntity"; 
        InsertMemberLevel_url_ = consumption_root_url_ + "InsertMemberLevel"; 
        UpdateMemberLevel_url_ = consumption_root_url_ + "UpdateMemberLevel"; 
        DeleteMemberLevel_url_ = consumption_root_url_ + "DeleteMemberLevel"; 
        MemberRechargeStores_url_ = consumption_root_url_ + "MemberRechargeStores"; 
        GetMemberInfo_url_ = consumption_root_url_ + "GetMemberInfo"; 
        InsertMemberInfo_url_ = consumption_root_url_ + "InsertMemberInfo"; 
        UpdateMemberInfo_url_ = consumption_root_url_ + "UpdateMemberInfo"; 
        ValidateICCardIsNormal_url_ = consumption_root_url_ + "ValidateICCardIsNormal"; 
        SelectDictionarySearch_url_ = consumption_root_url_ + "SelectDictionarySearch"; 
        GetContactMemberLevelGuid_url_ = consumption_root_url_ + "GetContactMemberLevelGuid"; 
        PhonePreTreatment_url_ = consumption_root_url_ + "PhonePreTreatment"; 
        UpdateMemberScheduled_url_ = consumption_root_url_ + "UpdateMemberScheduled"; 
        GetProducedInformationList_url_ = consumption_root_url_ + "GetProducedInformationList"; 
        InsertProducedInformation_url_ = consumption_root_url_ + "InsertProducedInformation"; 
        UpdateProducedInformation_url_ = consumption_root_url_ + "UpdateProducedInformation"; 
        GetProducedInformationEntry_url_ = consumption_root_url_ + "GetProducedInformationEntry"; 
        DeleteProductCategory_url_ = consumption_root_url_ + "DeleteProductCategory"; 
        SelectProductInfoByType_url_ = consumption_root_url_ + "SelectProductInfoByType"; 
        InsertProductCategory_url_ = consumption_root_url_ + "InsertProductCategory"; 
        UpdateProductCategory_url_ = consumption_root_url_ + "UpdateProductCategory"; 
        GetProductCategoryEntry_url_ = consumption_root_url_ + "GetProductCategoryEntry"; 
        MembershipCardReplacement_url_ = consumption_root_url_ + "MembershipCardReplacement"; 
        UpdateScheduledStatus_url_ = consumption_root_url_ + "UpdateScheduledStatus"; 
        DeleteRoomType_url_ = consumption_root_url_ + "DeleteRoomType"; 
        DeleteHousingDepartmentInfo_url_ = consumption_root_url_ + "DeleteHousingDepartmentInfo"; 
        SelectRoomInfoByType_url_ = consumption_root_url_ + "SelectRoomInfoByType"; 
        SelectHousingDepartmentInfo_url_ = consumption_root_url_ + "SelectHousingDepartmentInfo"; 
        InsertHousingDepartmentInfo_url_ = consumption_root_url_ + "InsertHousingDepartmentInfo"; 
        UpdateHousingDepartmentInfo_url_ = consumption_root_url_ + "UpdateHousingDepartmentInfo"; 
        GetHousingDepartmentInfoEntry_url_ = consumption_root_url_ + "GetHousingDepartmentInfoEntry"; 
        InsertRoomType_url_ = consumption_root_url_ + "InsertRoomType"; 
        UpdateRoomType_url_ = consumption_root_url_ + "UpdateRoomType"; 
        GetViewShopTicketList_url_ = consumption_root_url_ + "GetViewShopTicketList"; 
        DeleteShopTicket_url_ = consumption_root_url_ + "DeleteShopTicket"; 
        DeleteCompanyCoupon_url_ = consumption_root_url_ + "DeleteCompanyCoupon"; 
        UpdateMemberPhoneAndAddress_url_ = consumption_root_url_ + "UpdateMemberPhoneAndAddress"; 
        DeliveryService_url_ = consumption_root_url_ + "DeliveryService"; 
        GetStoreUnitedMembershipInfo_url_ = consumption_root_url_ + "GetStoreUnitedMembershipInfo"; 
        SelectStoreUnitedMembershipConsumeInfo_url_ = consumption_root_url_ + "SelectStoreUnitedMembershipConsumeInfo";
        DeliveryServiceDetails_url_ = consumption_root_url_ + "DeliveryServiceDetails";

    }
}