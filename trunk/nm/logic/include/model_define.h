#pragma  once
#include <list>
#include <string>


namespace nm
{
	//Encoding : UTF-8
	namespace model
	{
		/************************************************************************/
		/*
		UMS_Base_用户信息视图
		*/
		/************************************************************************/
		struct UMSBaseUserinfo
		{
			std::string user_guid;	       //GUID		
			int         user_type;		   //用户类型
			std::string branch_guid;	   //商户GUID
			std::string user_name;         //用户姓名
			std::string user_num;          //工号
			std::string user_id_num;       //身份证号码
			std::string user_postion;      //职务
			std::string user_postion_guid; //岗位GUID
			int			user_sex;          //性别
			std::string user_phone_num;    //电话
			std::string user_login_name;   //登录名称
			std::string user_pwd;          //密码
			std::string user_dept_guid;    //部门GUID
			std::string branch_hotline;	   //热线电话
			std::string branch_address;    //地址
			std::string branch_name;       //门店名称
			std::string user_power;        //权限
			std::string user_role;	       //角色
			int         branch_type;       //商户类型
			int         branch_city_id;    //所在城市ID
			std::string branch_city_name;  //所在城市
			std::string user_dept_name;    //部门名称
			std::string branch_group_guid; //集团GUID
			std::string branch_group_name; //集团名称
			time_t      opt_time;          //创建时间
		};
		typedef std::list<UMSBaseUserinfo> ListUMSBaseUserinfo; //用户信息的List对象

		/************************************************************************/
		/*
		VIEW_OPR_货品消费明细
		*/
		/************************************************************************/
		struct ViewOPRProductConsumDetail
		{
			double      quantity;             //F_Quantity
			double      unitprice;			  //F_UnitPrice
			double      subtotal;			  //F_Subtotal
			std::string consumetype;		  //F_ConsumeType
			std::string opertime;			  //F_OperTime
		};
		typedef std::list<ViewOPRProductConsumDetail> ListViewOPRProductConsumDetail; //VIEW_OPR_货品消费明细List对象

		/************************************************************************/
		/* 
		VIEW_OPR_货品消费明细分页
		*/
		/************************************************************************/
		struct ViewOPRProductConsumDetailPagging
		{
			int							   page_count;                      //总行数
			ListViewOPRProductConsumDetail view_opr_pruduct_consum_detail;  //VIEW_OPR_货品消费明细
		};

		/************************************************************************/
		/*
		VIEW_会员视图
		*/
		/************************************************************************/
		struct ViewMember
		{
			std::string member_phone;				//手机
			std::string member_name;				//会员名称
			std::string member_guid;				//GUID
			std::string member_level_guid;			//会员级别
			std::string member_id_num;				//证件号码
			int			member_type;				//会员类型
			std::string member_cardnum;				//卡号
			double		member_card_balance;		//卡余额;
		};
		typedef std::list<ViewMember> ListViewMember;//VIEW_会员视图List对象

		/************************************************************************/
		/*
		VIEW_Company_优惠券
		*/
		/************************************************************************/
		struct VIEW_Company_Coupon
		{
			int			logo;				//标识;        
			std::string coupon_guid;			//GUID
			int			coupon_id;				//优惠券ID;        
			double		condition2;				//条件2;        
			std::string merchant_guid;			//商户GUID;        
			std::string coupon_name;			//优惠券名称;        
			std::string coupon_name_type;		//优惠券名称种类;        
			time_t		startdate;				//开始日期;        
			time_t		enddate;				//截止日期;        
			std::string starttime;				//起始时段;        
			std::string endtime;				//截至时段;        
			std::string useweek;				//使用星期;        
			std::string member_lever;			//会员级别;        
			std::string formula;				//公式;        
			std::string instructions;				//使用说明;        
			std::string note;					//备注;        
			double		discountmoney;				//优惠后金额;
		};
		typedef std::list<VIEW_Company_Coupon> ListVIEW_Company_Coupon;//VIEW_Company_优惠券List对象

		/************************************************************************/
		/*
		会员输入密码是否正确
		*/
		/************************************************************************/
		struct MemberInputpPwdiIsok
		{        
			std::string msg;			//消息;        
			bool		isok;			//是否正确;        
			std::string pwd;			//返回密码;        
			std::string cardno;			//卡号;        
			std::string memberguid;		//F_MemberGUID
		};
		typedef std::list<MemberInputpPwdiIsok> ListMemberInputpPwdiIsok;//会员输入密码是否正确List对象


		/************************************************************************/
		/*
		VIEW_商户帐户往来明细
		*/
		/************************************************************************/
		struct VIEW_MerchantAccountDetails
		{        
			double		allconsumption;	//累计消费;        
			double		allrecharge;	//累计充值;        
			std::string accountnumber;	//帐户号;        
			double		money;			//金额;        
			std::string bank;			//开户银行;        
			std::string accountname;	//户名;        
			std::string bankaccount;	//银行帐户;
		};
		typedef std::list<VIEW_MerchantAccountDetails> ListVIEW_MerchantAccountDetails;//VIEW_商户帐户往来明细List对象

		/************************************************************************/
		/*
		VIEW_分页商户帐户往来明细
		*/
		/************************************************************************/

		struct VIEW_MerchantAccountDetailsPagging
		{        
			ListVIEW_MerchantAccountDetails listview_merchant_account_details;	//VIEW_分页商户帐户往来明细集合
			int								page_count;							//总行数
		};
		typedef std::list<VIEW_MerchantAccountDetailsPagging> ListVIEW_MerchantAccountDetailsPagging;//VIEW_分页商户帐户往来明细List对象

		/************************************************************************/
		/*
		Message
		*/
		/************************************************************************/     
		struct Message
		{        
			bool		isbool;		//是否正确
			std::string message;	//消息
		};
		typedef std::list<Message> ListMessage;//MessageList对象


		/************************************************************************/
		/* 
		UMS_OPR_CommunicationInfo
		*/
		/************************************************************************/
		struct UMS_OPR_CommunicationInfo
		{
			int			F_ID;
			std::string F_GUID;
			std::string F_OperatorGUID;
			std::string F_ShopGUID;
			std::string F_ContactGUID;
			std::string	F_ContactName;
			std::string	F_Phone;
			int			F_Property;//沟通性质
			int			F_Type;//沟通类型:1,中心与商户 2.中心与会员 3.商户与会员
			std::string	F_Content;
			std::string	F_Appraisal;
			double		F_PlanMoney;
			std::string	F_SpecialOffers;
			int			F_CommunicationType;//沟通方式
			int			F_Stage;//进展阶段
			std::string	F_Result;
			time_t		 F_ContactTime;
			std::string	F_Remark;
			int			F_Tag;
			std::string	F_Creater;
			time_t		F_CreateTime;
			time_t		F_UpdateTime;
			std::string	F_Updater;
		};
		typedef std::list<UMS_OPR_CommunicationInfo> ListUMS_OPR_CommunicationInfo;
		/************************************************************************/
		/*
		UMS_OPR_CommunicationTypeInfo(沟通类型)
		*/
		/************************************************************************/
		struct UMS_OPR_CommunicationTypeInfo
		{        
			int			F_ID;        
			std::string F_GUID;        
			std::string F_TypeName;        
			std::string F_Remark;        
			int			F_Tag;        
			std::string F_Creater;        
			time_t		F_CreateTime;        
			time_t		F_UpdateTime;        
			std::string F_Updater;
		};
		typedef std::list<UMS_OPR_CommunicationTypeInfo> ListUMS_OPR_CommunicationTypeInfo;//UMS_OPR_CommunicationTypeInfo(沟通类型)List对象

		/************************************************************************/
		/*
		VIEW_OPR_CommonCustomerInfo
		*/
		/************************************************************************/    
		struct VIEW_OPR_CommonCustomerInfo
		{        
			std::string F_GUID;        
			std::string F_Name;        
			std::string F_FixPhone;        
			std::string F_Address;        
			std::string F_MemberLevel;        
			std::string F_Phone;
		};
		typedef std::list<VIEW_OPR_CommonCustomerInfo> ListVIEW_OPR_CommonCustomerInfo;//VIEW_OPR_CommonCustomerInfoList对象


		/************************************************************************/
		/*
		UMS_OPR_ApproveInfo (沟通批复表)
		*/
		/************************************************************************/
		struct UMS_OPR_ApproveInfo
		{        
			int			F_ID;        
			std::string F_GUID;        
			std::string F_CommunicationGUID;        
			std::string F_Content;        
			std::string F_ApprovedPerson;        
			std::string F_ApprovedPersonGUID;        
			time_t		F_ApprovedTime;        
			std::string F_Remark;        
			int			F_Tag;        
			std::string F_Creater;        
			time_t		F_CreateTime;        
			time_t		F_UpdateTime;        
			std::string F_Updater;
		};
		typedef std::list<UMS_OPR_ApproveInfo> ListUMS_OPR_ApproveInfo;//UMS_OPR_ApproveInfo (沟通批复表)List对象

		/************************************************************************/
		/*
		VIEW_根据业务员查询沟通记录
		*/
		/************************************************************************/
		struct VIEW_GetCommunicationRecordByBusinessMan
		{        
			std::string F_GUID;        
			time_t		F_CreateTime;        
			std::string F_ContactName;        
			std::string F_Phone;        
			std::string F_Content;        
			std::string F_Result;        
			std::string BusinessManName;		//业务员名称;        
			std::string Communication_Nature;	//沟通性质;        
			std::string Communication_Mode;		//沟通方式;
		};
		typedef std::list<VIEW_GetCommunicationRecordByBusinessMan> ListVIEW_GetCommunicationRecordByBusinessMan;//VIEW_根据业务员查询沟通记录List对象

		/************************************************************************/
		/*
		UMS_OPR分页沟通记录
		*/
		/************************************************************************/
		struct UMS_OPRCommunicationrecordPagging
		{
			ListVIEW_GetCommunicationRecordByBusinessMan	listview_getcommunicationrecordbybusinessman;	//VIEW_根据业务员查询沟通记录List对象
			int												page_count;		
		};
		typedef std::list<UMS_OPRCommunicationrecordPagging> ListUMS_OPRCommunicationrecordPagging;//UMS_OPR分页沟通记录List对象

		/************************************************************************/
		/*
		VIEW_POS_ShopMemberInfo
		*/
		/************************************************************************/    
		struct VIEW_POS_ShopMemberInfo
		{        
			std::string F_MemberName;        
			std::string F_MobPhone;        
			std::string F_CardNumber;        
			std::string F_GUID;        
			double		F_CurrertMoney;        
			int			F_Marking;        
			std::string F_Grade;        
			std::string F_GradeName;        
			double		F_TotalCharge;        
			double		F_TotalConsume;        
			time_t		F_Birthday;        
			std::string F_CertificateNumber;        
			int			F_CertificateType;        
			std::string F_Remark;        
			std::string F_Address;
		};
		typedef std::list<VIEW_POS_ShopMemberInfo> ListVIEW_POS_ShopMemberInfo;//VIEW_POS_ShopMemberInfoList对象

		/************************************************************************/
		/*
		UMS_普通顾客信息
		*/
		/************************************************************************/    
		struct UMS_Customer_info
		{        
			double		allconsumptionmoney;	//总消费金额;        
			std::string name;					//姓名;        
			std::string phoneno;				//手机号码;        
			std::string address;				//地址;
		};
		typedef std::list<UMS_Customer_info> ListUMS_Customer_info;//UMS_普通顾客信息List对象

		/************************************************************************/
		/*
		UMS_OPR_消费单业务视图
		*/
		/************************************************************************/    
		struct UMS_OPR_Consumption_Business_view
		{        
			std::string numbers;			//单号;        
			time_t		operation_date;		//操作日期;        
			double		shouldmoney;		//应收金额;        
			double		actualmoney;		//实收金额;        
			double		onsalemoney;		//优惠金额;        
			std::string operater;			//操作员;        
			int			ishaveproduct;		//是否有产品;
		};
		typedef std::list<UMS_OPR_Consumption_Business_view> ListUMS_OPR_Consumption_Business_view;//UMS_OPR_消费单业务视图List对象

		/************************************************************************/
		/*
		UMS_普通顾客消费记录
		*/
		/************************************************************************/ 
		struct UMS_Ordinary_Consumption_record
		{        
			ListUMS_OPR_Consumption_Business_view	listums_opr_consumption_business_view;	//UMS_OPR_消费单业务视图List对象
			int										page_count;	
		};
		typedef std::list<UMS_Ordinary_Consumption_record> ListUMS_Ordinary_Consumption_record;//UMS_普通顾客消费记录List对象

		/************************************************************************/
		/*
		UMS_BASE_房厅类型表
		*/
		/************************************************************************/
		struct UMS_BASE_RoomTypeInfo
		{        
			std::string guid;			
			std::string shopguid;		//门店GUID;        
			std::string type;			//类型;        
			std::string remark;			//备注;  
			int			remembertag;	//记录状态;  
			std::string creater;		//创建人;        
			std::string creattime;		//创建时间;        
			std::string updateter;		//最后修改者;        
			std::string updatetime;		//最后修改时间; 
		};
		typedef std::list<UMS_BASE_RoomTypeInfo> ListUMS_BASE_RoomTypeInfo;//UMS_BASE_房厅类型表List对象

		/************************************************************************/
		/*
		UMS_BASE_房厅信息表
		*/
		/************************************************************************/
		struct UMS_BASE_RoomInfo
		{        
			std::string guid;			
			std::string shopguid;		//门店GUID;        
			std::string room_code;		//简码;        
			std::string room_name;		//名称;        
			std::string room_size;		//大小;        
			int			order;			//排序;        
			std::string room_type;		//房间类型;        
			int			state;			//状态;	//0禁用 1 使用
			std::string remark;			//备注;        
			int			remembertag;	//记录状态;  
			std::string creater;		//创建人;        
			std::string creattime;		//创建时间;        
			std::string updateter;		//最后修改者;        
			std::string updatetime;		//最后修改时间; 
		};
		typedef std::list<UMS_BASE_RoomInfo> ListUMS_BASE_RoomInfo;//UMS_BASE_房厅信息表List对象

		/************************************************************************/
		/*
		VIEW_会员普通顾客信息视图
		*/
		/************************************************************************/    
		struct VIEW_MemberAndOrdinary_Info_View
		{        
			std::string membername;		//会员名称;        
			std::string phone;			//手机;        
			std::string address;		//地址;         
			std::string guid;        
			int			membertype;		//会员类型;//1会员 2普通顾客        
			std::string otherphone;		//其他电话;
		};
		typedef std::list<VIEW_MemberAndOrdinary_Info_View> ListVIEW_MemberAndOrdinary_Info_View;//VIEW_会员普通顾客信息视图List对象

		/************************************************************************/
		/*
		UMS_BASE_门店会员级别
		*/
		/************************************************************************/
		struct UMS_BASE_ShopMemberLeave
		{
			int			id;
			std::string guid;
			std::string	shop_guid;		//门店GUID;
			std::string member_type;	//会员类型;   
			int			order;			//优先; 
			std::string remark;			//备注;        
			int			remembertag;	//记录状态;  
			std::string creater;		//创建人;        
			time_t		creattime;		//创建时间;        
			std::string updateter;		//最后修改者;        
			time_t		updatetime;		//最后修改时间

		};
		typedef std::list<UMS_BASE_ShopMemberLeave> ListUMS_BASE_ShopMemberLeave;//UMS_BASE_门店会员级别List对象

		/************************************************************************/
		/*
		UMS_优惠券
		*/
		/************************************************************************/
		struct UMS_Coupon
		{        
			int			id;			//优惠券ID
			std::string couponname;	//优惠券名称;
		};
		typedef std::list<UMS_Coupon> ListUMS_Coupon;//UMS_优惠券List对象

		/************************************************************************/
		/*
		UMS_Company_门店优惠券
		*/
		/************************************************************************/
		struct UMS_Company_ShopCoupon
		{        
			int			id;        
			std::string guid;        
			std::string contractguid;	//合同GUID;        
			int			couponid;		//优惠券ID;        
			std::string merchantguid;	//商户GUID;        
			std::string shopguid;		//门店GUID;        
			std::string couponname;		//优惠券名称;        
			int			count;			//数量;        
			double		condition1;		//条件1;        
			double		condition2;		//条件2;        
			std::string contractimg;	//优惠券图片;        
			std::string startdate;		//开始日期;        
			std::string enddate;		//截止日期;        
			std::string starttime;		//起始时段;        
			std::string endtime;		//截至时段;        
			std::string usedweek;		//使用星期;   
			std::string member_leave;	//会员级别;        
			std::string formula;		//公式;       
			int			usedalone;		//单独使用;          
			std::string explain;		//使用说明;   
			int			state;			//状态;                 
			std::string remark;			//备注; 
			int			remembertag;	//记录状态;  
			std::string creater;		//创建人;        
			time_t		creattime;		//创建时间;        
			std::string updateter;		//最后修改者;        
			time_t		updatetime;		//最后修改时间
			int			toexamine;		//审核;//0:未审核  1审核通过        
			int			shopid;			//门店ID;
		};
		typedef std::list<UMS_Company_ShopCoupon> ListUMS_Company_ShopCoupon;//UMS_Company_门店优惠券List对象

		/************************************************************************/
		/*
		UMS_Company_优惠券
		*/
		/************************************************************************/     
		struct UMS_Company_Coupon
		{
			int			id;        
			std::string guid;        
			std::string contractguid;	//合同GUID;        
			int			couponid;		//优惠券ID;        
			std::string merchantguid;	//商户GUID;         
			std::string couponname;		//优惠券名称;        
			int			count;			//数量;        
			double		condition1;		//条件1;        
			double		condition2;		//条件2;        
			std::string contractimg;	//优惠券图片;        
			std::string startdate;		//开始日期;        
			std::string enddate;		//截止日期;        
			std::string starttime;		//起始时段;        
			std::string endtime;		//截至时段;        
			std::string usedweek;		//使用星期;   
			std::string member_leave;	//会员级别;        
			std::string formula;		//公式;       
			int			usedalone;		//单独使用;          
			std::string explain;		//使用说明;   
			int			state;			//状态;                 
			std::string remark;			//备注; 
			int			remembertag;	//记录状态;  
			std::string creater;		//创建人;        
			time_t		creattime;		//创建时间;        
			std::string updateter;		//最后修改者;        
			time_t		updatetime;		//最后修改时间
			int			toexamine;		//审核;//0:未审核  1审核通过        
			int			shopid;			//门店ID;
		};
		typedef std::list<UMS_Company_Coupon> ListUMS_Company_Coupon;//UMS_Company_优惠券List对象

		/************************************************************************/
		/*
		UMS_OPR_会员预定主表
		*/
		/************************************************************************/
		struct UMS_OPR_MemberOrderInfo
		{
			int			id;
			std::string guid;
			std::string numbers;		//单号;
			std::string shopguid;		//门店GUID;
			std::string memberguid;		//会员GUID;
			int			peoplecount;	//人数;
			std::string ordertime;		//预定时间;
			std::string source;			//来源;
			std::string roomtype;		//房间类型;
			std::string roomguid;		//房间GUID;
			std::string identity;		//身份;
			int			state;			//状态;
			std::string reply;			//回复;
			std::string remark;			//备注;
			int			remembertag;	//记录状态;  
			std::string creater;		//创建人;        
			std::string creattime;		//创建时间;        
			std::string updateter;		//最后修改者;        
			std::string updatetime;		//最后修改时间
			int			orderpeopeltype;//预订人类型;
		};
		typedef std::list<UMS_OPR_MemberOrderInfo> ListUMS_OPR_MemberOrderInfo;//UMS_OPR_会员预定主表List对象

		/************************************************************************/
		/*
		UMS_数据字典明细表
		*/
		/************************************************************************/
		struct UMS_dictionaryDetails
		{        
			int			id;        
			std::string name;	//名称;
		};
		typedef std::list<UMS_dictionaryDetails> ListUMS_dictionaryDetails;//UMS_数据字典明细表List对象

		/************************************************************************/
		/*
		返回消息
		*/
		/************************************************************************/
		struct Returnmessage
		{        
			std::string message;    //消息   
			bool		isok;		//是否成功;        
			std::string cardno;		//卡号;
		};
		typedef std::list<Returnmessage> ListReturnmessage;//返回消息List对象

		/************************************************************************/
		/*
		UMS_BASE_ShopMemberInfo
		*/
		/************************************************************************/
		struct UMS_BASE_ShopMemberInfo
		{
			int			F_ID;
			std::string F_GUID;
			std::string F_MemberCode;
			std::string F_MemberName;
			int			F_CertificateType;
			std::string F_CertificateNumber;
			int			F_Sex;
			int			F_Area;
			std::string F_MobPhone;
			std::string F_Address;
			std::string F_Birthday;
			std::string F_Phone;
			std::string F_EMail;
			std::string F_Grade;
			std::string F_Source;
			std::string F_Fix;
			std::string F_Post;
			std::string F_OperateTime;
			std::string F_ShopGUID;
			std::string F_Remark;
			int			F_Tag;
			std::string F_Creater;
			std::string F_CreateTime;
			std::string F_UpdateTime;
			std::string F_Updater;
		};
		typedef std::list<UMS_BASE_ShopMemberInfo> ListUMS_BASE_ShopMemberInfo;//UMS_BASE_ShopMemberInfoList对象

		/************************************************************************/
		/*
		UMS_BASE_会员卡信息表
		*/
		/************************************************************************/
		struct UMS_BASE_MemberCardInfo
		{
			int			id;
			std::string guid;
			std::string userguid;			//用户GUID;
			std::string cardno;				//卡号;
			std::string physicsno;			//物理卡号;
			std::string pwd;				//密码;
			std::string storedleave;		//储值卡级别;
			std::string lokleave;			//联乐卡级别;
			std::string getcarddate;		//发卡日期;
			std::string overduedate;		//截至日期;
			std::string getcardshopguid;	//发卡门店GUID;
			int			state;				//状态;
			int			cardstate;			//卡状态;
			std::string remark;				//备注;
			int			remembertag;		//记录状态;  
			std::string creater;			//创建人;        
			std::string creattime;			//创建时间;        
			std::string updateter;			//最后修改者;        
			std::string updatetime;			//最后修改时间;
		};
		typedef std::list<UMS_BASE_MemberCardInfo> ListUMS_BASE_MemberCardInfo;//UMS_BASE_MemberCardInfo List对象

		/************************************************************************/
		/* 
		VIEW_POS_ShopMemberInfoPage
		*/
		/************************************************************************/
		struct VIEW_POS_ShopMemberInfoPage
		{        
			int							page_count;	       
			ListVIEW_POS_ShopMemberInfo view_pos_shopmemberinfo;//VIEW_POS_ShopMemberInfo List对象
		};
		typedef std::list<VIEW_POS_ShopMemberInfoPage> ListVIEW_POS_ShopMemberInfoPage;//VIEW_POS_ShopMemberInfoPage List对象

		/************************************************************************/
		/* 
		UMS_OPR_会员卡状态变更表
		*/
		/************************************************************************/
		struct UMS_OPR_MemberCardStateUpdateInfo
		{
			int			id;
			std::string guid;
			std::string shopguid;			//门店GUID;
			std::string cardno;				//卡号;
			int			type;				//类型;
			int			state;				//状态;
			std::string operationexplain;	//操作说明;
			time_t		operationdate;		//操作日期;
			std::string operaterguid;		//操作人GUID;
			std::string remark;				//备注;
			int			remembertag;		//记录状态;  
			std::string creater;			//创建人;        
			time_t		creattime;			//创建时间;        
			std::string updateter;			//最后修改者;        
			time_t		updatetime;			//最后修改时间;
		};
		typedef std::list<UMS_OPR_MemberCardStateUpdateInfo> ListUMS_OPR_MemberCardStateUpdateInfo;//UMS_OPR_会员卡状态变更表 List对象

		/************************************************************************/
		/*
		UMS_Base_区域信息
		*/
		/************************************************************************/
		struct UMSBaseAreainfo
		{
			int			id;				//ID
			std::string guid;			//GUID
			int			father_id;		//父ID
			std::string area_name;		//区域名称
			double		longitude;		//经度
			double		latitude;		//纬度
			int			marqueezoom;	//放大比例
			int			sort_order;		//排序
			int			deep_level;		//深度
			std::string remark;			//备注
			int			record_status;	//记录状态
			std::string creator;		//创建人
			time_t		create_time;	//创建时间
			std::string last_update_op;	//最后修改者
			time_t      last_update_time;//最后修改时间
		};
		typedef std::list<UMSBaseAreainfo> ListUMSBaseAreainfo;

		/************************************************************************/
		/*
		UMS_Base_会员级别
		*/
		/************************************************************************/ 
		struct UMSMemberLevel
		{
			std::string member_level_guid;	  //GUID		
			std::string member_level_name;	  //会员级别
		};
		typedef std::list<UMSMemberLevel> ListUMSMemberLevel; //会员级别的List对象


		/************************************************************************/
		/*
		VIEW_消费单明细视图
		*/
		/************************************************************************/ 
		struct UMSConsumeMenuSingleDetailView
		{
			int			menu_id;			//id
			std::string menu_guid;			//GUID
			std::string menu_single;		//单号
			std::string menu_name;			//品名
			std::string menu_name_guid;		//品名GUID
			double		menu_num;			//数量
			int			menu_status;	    //状态
			std::string menu_remark;        //备注
			int			menu_log_status;    //记录状态
			std::string menu_create_name;   //创建人
			time_t		menu_create_time;   //创建时间
			std::string menu_update_name;   //最后修改者
			time_t		menu_update_time;   //最后修改时间
			std::string menu_unit;          //单位
			double		menu_price;         //单价
		};
		typedef std::list<UMSConsumeMenuSingleDetailView> ListUMSConsumeMenuSingleDetailView; //消费菜品明细的List对象

		/************************************************************************/
		/*
		UMS_集团会员消费信息
		*/
		/************************************************************************/ 
		struct UMSGroupMemberCashDetail
		{
			time_t group_opertion_time;	   //操作时间
			int			group_type;                //类型
			std::string group_card_no;			   //卡号
			std::string group_member_name;		   //会员名称
			double 		group_account_price;       //应付金额
			double 		group_preferential_price;  //优惠金额
			double 		group_practice_price;      //实收金额
			double 		group_balance;             //余额
			std::string group_single;   		   //业务单号
			int			group_is_bool;             //是否有产品
			std::string group_member_guid;		   //会员guid
			std::string group_phone;				//手机号码

		};
		typedef std::list<UMSGroupMemberCashDetail> ListUMSGroupMemberCashDetail; //集团会员消费明细的List对象

		/************************************************************************/
		/*
		UMS_分页集团会员消费信息
		*/
		/************************************************************************/ 
		struct UMSGroupMemberCashView
		{
			ListUMSGroupMemberCashDetail group_cash_info;  //集团会员消费明细
			int group_count;  //总行数
		};
		typedef std::list<UMSGroupMemberCashView> ListUMSGroupMemberCashView; //集团会员消费结构的List对象

		/************************************************************************/
		/*
		VIEW_储值会员消费信息
		*/
		/************************************************************************/ 
		struct UMSLocalMemberCashDetail
		{
			time_t		 local_operation_time;		//操作时间
			int			 local_marker;              //标识
			std::string  local_card_no;				//卡号
			std::string  local_member_name;			//会员名称
			double 		local_account_price;        //消费应收
			double 		local_preferential_price;   //优惠金额
			double 		local_practice_price;       //储值金抵扣
			double 		local_balance;              //余额
			std::string local_operation_name; 		 //操作员
			std::string local_single;         		 //业务单号
			int			 local_is_bool;       		 //是否有产品
		};
		typedef std::list<UMSLocalMemberCashDetail> ListUMSLocalMemberCashDetail; //储值会员消费明细的List对象

		/************************************************************************/
		/*
		VIEW_分页储值会员消费信息
		*/
		/************************************************************************/ 
		struct UMSLocalMemberCashView
		{
			int local_count ;                     //总行数
			ListUMSLocalMemberCashDetail local_info;  //储值会员消费明细
		};
		typedef std::list<UMSLocalMemberCashView> ListUMSLocalMemberCashView; //储值会员消费视图的List对象

		/************************************************************************/
		/*
		UMS_OPR_MachineInfo
		*/
		/************************************************************************/ 
		struct UMS_OPR_MachineInfo
		{
			int			F_ID ;
			std::string GUID ;
			std::string F_ShopGUID; 
			std::string F_ShopName; 
			std::string F_MachineName; 
			std::string F_MachineCode;
			std::string F_IpAddress;
			int			F_IpPort;
			time_t		F_OperateTime;
		};
		typedef std::list<UMS_OPR_MachineInfo> ListUMS_OPR_MachineInfo; //UMS_OPR_MachineInfo的List对象

		/************************************************************************/
		/*
		UMS_待处理的会员预定信息
		*/
		/************************************************************************/ 
		struct UMSWaitMemberInfo
		{
			int			wait_id;              //ID
			std::string wait_guid;            //GUID
			std::string wait_single;          //单号
			std::string wait_member_guid;     //会员guid
			std::string wait_member_origin;   //来源
			std::string wait_room_type;       //房间类型
			std::string wait_order_time;      //预订时间
			std::string wait_create_time;     //创建时间
			int			wait_status;          //状态
			std::string wait_member_name;     //会员名称
			std::string wait_phone;           //手机
			int			wait_preson_num;      //人数
			std::string wait_roomtype_name;   //房间类型名称	
		};
		typedef std::list<UMSWaitMemberInfo> ListUMSWaitMemberInfo; //UMS_OPR_MachineInfo的List对象

		/************************************************************************/
		/*
		UMS_OPR_CommonCustomerInfo
		*/
		/************************************************************************/ 
		struct UMS_OPR_CommonCustomerInfo
		{
			std::string F_GUID ;
			std::string F_Name ;
			std::string F_MobilePhone ;
		};
		typedef std::list<UMS_OPR_CommonCustomerInfo> ListUMS_OPR_CommonCustomerInfo; //VIEW_POS_ShopMemberInfo的List对象

		/************************************************************************/
		/*
		VIEW_CommonCustomerInfo
		*/
		/************************************************************************/ 
		struct VIEW_CommonCustomerInfo
		{
			int								allcount;//总行数
			ListUMS_OPR_CommonCustomerInfo  listums_opr_commoncustomerinfo;
		};
		typedef std::list<VIEW_CommonCustomerInfo> ListVIEW_CommonCustomerInfo; //VIEW_POS_ShopMemberInfo的List对象

		/************************************************************************/
		/*
		UMS_门店联乐会员信息
		*/
		/************************************************************************/ 
		struct UMSUniteMemberInfo
		{
			std::string unite_member_guid;   //会员GUID 
			std::string unite_member_phone;  //手机 
			std::string unite_card_no;       //卡号 
			std::string unite_member_name;   //会员名称
			double		unite_total_cash;    //累计消费金额
			std::string unite_acount_no;     //账户号
		};
		typedef std::list<UMSUniteMemberInfo> ListUMSUniteMemberInfo; //VIEW_POS_ShopMemberInfo的List对象

		/************************************************************************/
		/*
		UMS_分页门店联乐会员信息
		*/
		/************************************************************************/ 
		struct VIEW_UniteMemberInfoPage
		{
			int						allcount;//总行数
			ListUMSUniteMemberInfo listums_opr_commoncustomerinfo;
		};
		typedef std::list<VIEW_UniteMemberInfoPage> ListVIEW_UniteMemberInfoPage; //VIEW_POS_ShopMemberInfo的List对象

		/************************************************************************/
		/*
		UMS_BASE_出品信息表
		*/
		/************************************************************************/
		struct productInfo
		{
			std::string product_guid ;									//GUID
			std::string shop_guid ;										//门店GUID ;
			std::string product_coding ;								//编码 ;
			std::string product_name ;									//品名 ;
			std::string product_spec ;									//规格 ;
			std::string product_type_guid ;								//类别 ;
			double		product_unit_price;								//单价 ; 
			double		product_purchase_price;							//进货价 ;
			std::string product_unit;								//单位 ; 
			int			product_sort;									//排序 ; 
			std::string product_casing;									//包装 ; 
			std::string product_image;									//图片 ; 
			std::string product_easy_know;								//助记码 ; 
			std::string remark;											//备注 ; 
			int			record_status;									//记录状态
			std::string creator;										//创建人
			std::string	create_time;									//创建时间
			std::string last_update_op;									//最后修改者
			std::string last_update_time;								//最后修改时间
		};
		typedef std::list<productInfo> ListproductInfo;
		/************************************************************************/
		/*
		UMS_BASE_出品信息视图
		*/
		/************************************************************************/
		struct ViewProductInfo
		{
			std::string product_guid ;									//GUID
			std::string shop_guid ;										//门店GUID
			std::string product_coding ;								//编码
			std::string product_name ;									//品名
			std::string product_spec ;									//规格
			std::string product_type_guid ;								//类别
			std::string product_type_name ;								//类别名称
			int			product_type_kind ;								//类别性质
			double		product_purchase_price;							//进货价 ; 
			double		product_unit_price;								//单价 ;
			std::string product_unit;									//单位 ;
			int			product_sort;									//排序 ;
			std::string product_casing;									//包装 ;
			std::string product_image;									//图片 ;
			std::string product_easy_know;								//助记码 ;
			std::string remark;											//备注 ;
		};
		typedef std::list<ViewProductInfo> ListViewProductInfo;		//UMS_BASE_出品信息视图List对象

		/************************************************************************/
		/*
		UMS_BASE_分页出品信息表
		*/
		/************************************************************************/
		struct ViewProductInfoPagging
		{
			int					page_count ;							//总行数
			ListViewProductInfo list_view_pruductInfo ;					//UMS_BASE_出品信息视图
		};
		typedef std::list<ViewProductInfoPagging> ListViewProductInfoPagging;
		/************************************************************************/
		/*
		UMS_BASE_出品类别表
		*/
		/************************************************************************/
		struct productTypeInfo
		{
			std::string type_guid;										//GUID ;
			std::string shop_guid;										//门店GUID ;
			std::string father_guid;									//父GUID ;
			std::string type_name;										//类别 ;
			int			type_sort;										//排序 ;
			std::string remark;											//备注 ; 
			int			record_status;									//记录状态
			std::string creator;										//创建人
			std::string create_time;									//创建时间
			std::string last_update_op;									//最后修改者
			std::string last_update_time;								//最后修改时间
			int			type_kind;										//类别性质 ;
			int			relation_kind;									//关联类型 ;
		};
		typedef std::list<productTypeInfo> ListproductTypeInfo;		//UMS_BASE_出品类别表 List对象

		/************************************************************************/
		/*
		UMS_BASE_房厅预定信息视图
		*/
		/************************************************************************/
		struct ViewRoomOrderInfo
		{

			std::string room_guid;										//GUID ;
			std::string easy_know;										//简码 ;
			std::string room_name;										//名称 ;
			std::string room_size;										//大小 ;
			int			room_sort;										//排序 ;
			std::string room_type_guid;									//房间类型 ;
			std::string room_type_name;									//房间类型名称 ;
			int			room_status;									//状态 ;//0禁用 1 使用
			std::string remark;											//备注 ;
		};
		typedef std::list<ViewRoomOrderInfo> ListViewRoomOrderInfo;		//UMS_BASE_房厅预定信息视图List对象

		/************************************************************************/
		/*
		UMS_BASE_分页房厅预定信息视图
		*/
		/************************************************************************/
		struct ViewRoomOrderInfoPagging
		{

			ListViewRoomOrderInfo list_view_roomOrderInfo ;			//ums_房厅预定信息视图 ;
			int page_count;											//总行数 ;
		};
		typedef std::list<ViewRoomOrderInfoPagging> ListViewRoomOrderInfoPagging;
		/************************************************************************/
		/*
		UMS_BASE_房厅信息表
		*/
		/************************************************************************/
		struct roomInfo
		{
			std::string room_guid;										//GUID ;
			std::string shop_guid;										//门店GUID ;
			std::string easy_know;										//简码 ;
			std::string room_name;										//名称 ;
			std::string room_size;										//大小 ;
			int			room_sort;										//排序 ;
			std::string room_type_guid;										//房间类型 ;
			int			room_status;									//状态 ;//0禁用 1 使用
			std::string remark;											//备注 ; 
			int			record_status;									//记录状态
			std::string creator;										//创建人
			std::string create_time;									//创建时间
			std::string last_update_op;									//最后修改者
			std::string last_update_time;								//最后修改时间
		};
		typedef std::list<roomInfo> ListroomInfo;
		/************************************************************************/
		/*
		UMS_BASE_房厅信息视图
		*/
		/************************************************************************/
		struct ViewRoomInfo
		{

			std::string room_guid;										//GUID ;
			std::string easy_know;										//简码 ;
			std::string room_name;										//名称 ;
			std::string room_size;										//大小 ;
			std::string room_type_guid;									//房间类型 ;
			std::string room_type_name;									//房间类型名称 ;
			int			room_status;									//状态 ;//0禁用 1 使用
			std::string remark;											//备注 ;
		};
		typedef std::list<ViewRoomInfo> ListViewRoomInfo;
		/************************************************************************/
		/*
		VIEW_门店优惠券
		*/
		/************************************************************************/
		struct	ViewFavourableTicketInfo
		{

			int			ticket_id;										//标识 ;
			std::string ticket_guid;									//GUID ;
			std::string ticket_name;									//优惠券名称 ;
			std::string ticket_type;									//优惠券名称种类 ;
			time_t		ticket_date_start;								//开始日期 ;
			time_t		ticket_date_end;								//截止日期 ;
			std::string ticket_hour_start;								//起始时段 ;
			std::string ticket_hour_end;								//截至时段 ;
			std::string ticket_explain;									//使用说明 ;
			int			ticket_approve;									//审核 ;
		};
		typedef std::list<ViewFavourableTicketInfo> ListViewFavourableTicketInfo;		//VIEW_门店优惠券List对象

		/************************************************************************/
		/*
		ConsumerSingleDetails
		*/
		/************************************************************************/
		struct ConsumerSingleDetails  //消费单明细
		{

			std::string GUID ;
			std::string ConsumeID ;										//业务单号
			std::string ProductGuid ;									//产品guid
			double		Number ;										//数量
		};
		typedef std::list<ConsumerSingleDetails> ListConsumerSingleDetails;
		/************************************************************************/
		/*
		ConsumptionSingleBusiness
		*/
		/************************************************************************/
		struct ConsumptionSingleBusiness  //消费单业务表
		{

			std::string GUID ;											//GUID
			std::string ShopGuid ;										//门店GUID
			std::string MemberGuid ;									//会员GUID
			std::string MemberName ;									//会员姓名
			std::string MemberPhone ;									//会员电话
			double		money ;											//消费金额
			std::string OperatorGuid ;									//操作员GUID
			std::string Address ;										//地址
			int			ConsumeType ;									//消费类型
			std::string Mark ;											//标示
			time_t		OrderTime ;										//操作时间
		};
		typedef std::list<ConsumptionSingleBusiness> ListConsumptionSingleBusiness;		//UMS_门店联乐会员消费信息List对象


		/************************************************************************/
		/*
		UMS_门店联乐会员消费信息
		*/
		/************************************************************************/
		struct uniteMemberConsumeInfo
		{

			//time_t		operator_time;									//操作时间 ;
			std::string operator_time;									//操作时间 ;
			double		money_need;										//应付金额 ;
			double		money_forfree;									//优惠金额 ;
			double		money_pay;										//实收金额 ;
			double		balance;										//余额 ;
			int			isExistProduct;									//是否有产品 ;
			std::string billno;											//单号 ;
			std::string member_guid;									//会员GUID ;
			std::string accountNo;										//帐户号 ;
		};
		typedef std::list<uniteMemberConsumeInfo> ListUniteMemberConsumeInfo;		//UMS_门店联乐会员消费信息List对象

		/************************************************************************/
		/*
		UMS_分页门店联乐会员消费信息
		*/
		/************************************************************************/
		struct uniteMemberConsumeInfoPagging
		{
			int						page_count;						//总行数 ;
			ListUniteMemberConsumeInfo list_UniteMemberConsumeInfo;	//ums_门店联乐会员消费信息 ;
		};
	}
}