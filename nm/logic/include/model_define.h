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
		UMS_Base_�û���Ϣ��ͼ
		*/
		/************************************************************************/
		struct UMSBaseUserinfo
		{
			std::string user_guid;	       //GUID		
			int         user_type;		   //�û�����
			std::string branch_guid;	   //�̻�GUID
			std::string user_name;         //�û�����
			std::string user_num;          //����
			std::string user_id_num;       //���֤����
			std::string user_postion;      //ְ��
			std::string user_postion_guid; //��λGUID
			int			user_sex;          //�Ա�
			std::string user_phone_num;    //�绰
			std::string user_login_name;   //��¼����
			std::string user_pwd;          //����
			std::string user_dept_guid;    //����GUID
			std::string branch_hotline;	   //���ߵ绰
			std::string branch_address;    //��ַ
			std::string branch_name;       //�ŵ�����
			std::string user_power;        //Ȩ��
			std::string user_role;	       //��ɫ
			int         branch_type;       //�̻�����
			int         branch_city_id;    //���ڳ���ID
			std::string branch_city_name;  //���ڳ���
			std::string user_dept_name;    //��������
			std::string branch_group_guid; //����GUID
			std::string branch_group_name; //��������
			time_t      opt_time;          //����ʱ��
		};
		typedef std::list<UMSBaseUserinfo> ListUMSBaseUserinfo; //�û���Ϣ��List����

		/************************************************************************/
		/*
		VIEW_OPR_��Ʒ������ϸ
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
		typedef std::list<ViewOPRProductConsumDetail> ListViewOPRProductConsumDetail; //VIEW_OPR_��Ʒ������ϸList����

		/************************************************************************/
		/* 
		VIEW_OPR_��Ʒ������ϸ��ҳ
		*/
		/************************************************************************/
		struct ViewOPRProductConsumDetailPagging
		{
			int							   page_count;                      //������
			ListViewOPRProductConsumDetail view_opr_pruduct_consum_detail;  //VIEW_OPR_��Ʒ������ϸ
		};

		/************************************************************************/
		/*
		VIEW_��Ա��ͼ
		*/
		/************************************************************************/
		struct ViewMember
		{
			std::string member_phone;				//�ֻ�
			std::string member_name;				//��Ա����
			std::string member_guid;				//GUID
			std::string member_level_guid;			//��Ա����
			std::string member_id_num;				//֤������
			int			member_type;				//��Ա����
			std::string member_cardnum;				//����
			double		member_card_balance;		//�����;
		};
		typedef std::list<ViewMember> ListViewMember;//VIEW_��Ա��ͼList����

		/************************************************************************/
		/*
		VIEW_Company_�Ż�ȯ
		*/
		/************************************************************************/
		struct VIEW_Company_Coupon
		{
			int			logo;				//��ʶ;        
			std::string coupon_guid;			//GUID
			int			coupon_id;				//�Ż�ȯID;        
			double		condition2;				//����2;        
			std::string merchant_guid;			//�̻�GUID;        
			std::string coupon_name;			//�Ż�ȯ����;        
			std::string coupon_name_type;		//�Ż�ȯ��������;        
			time_t		startdate;				//��ʼ����;        
			time_t		enddate;				//��ֹ����;        
			std::string starttime;				//��ʼʱ��;        
			std::string endtime;				//����ʱ��;        
			std::string useweek;				//ʹ������;        
			std::string member_lever;			//��Ա����;        
			std::string formula;				//��ʽ;        
			std::string instructions;				//ʹ��˵��;        
			std::string note;					//��ע;        
			double		discountmoney;				//�Żݺ���;
		};
		typedef std::list<VIEW_Company_Coupon> ListVIEW_Company_Coupon;//VIEW_Company_�Ż�ȯList����

		/************************************************************************/
		/*
		��Ա���������Ƿ���ȷ
		*/
		/************************************************************************/
		struct MemberInputpPwdiIsok
		{        
			std::string msg;			//��Ϣ;        
			bool		isok;			//�Ƿ���ȷ;        
			std::string pwd;			//��������;        
			std::string cardno;			//����;        
			std::string memberguid;		//F_MemberGUID
		};
		typedef std::list<MemberInputpPwdiIsok> ListMemberInputpPwdiIsok;//��Ա���������Ƿ���ȷList����


		/************************************************************************/
		/*
		VIEW_�̻��ʻ�������ϸ
		*/
		/************************************************************************/
		struct VIEW_MerchantAccountDetails
		{        
			double		allconsumption;	//�ۼ�����;        
			double		allrecharge;	//�ۼƳ�ֵ;        
			std::string accountnumber;	//�ʻ���;        
			double		money;			//���;        
			std::string bank;			//��������;        
			std::string accountname;	//����;        
			std::string bankaccount;	//�����ʻ�;
		};
		typedef std::list<VIEW_MerchantAccountDetails> ListVIEW_MerchantAccountDetails;//VIEW_�̻��ʻ�������ϸList����

		/************************************************************************/
		/*
		VIEW_��ҳ�̻��ʻ�������ϸ
		*/
		/************************************************************************/

		struct VIEW_MerchantAccountDetailsPagging
		{        
			ListVIEW_MerchantAccountDetails listview_merchant_account_details;	//VIEW_��ҳ�̻��ʻ�������ϸ����
			int								page_count;							//������
		};
		typedef std::list<VIEW_MerchantAccountDetailsPagging> ListVIEW_MerchantAccountDetailsPagging;//VIEW_��ҳ�̻��ʻ�������ϸList����

		/************************************************************************/
		/*
		Message
		*/
		/************************************************************************/     
		struct Message
		{        
			bool		isbool;		//�Ƿ���ȷ
			std::string message;	//��Ϣ
		};
		typedef std::list<Message> ListMessage;//MessageList����


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
			int			F_Property;//��ͨ����
			int			F_Type;//��ͨ����:1,�������̻� 2.�������Ա 3.�̻����Ա
			std::string	F_Content;
			std::string	F_Appraisal;
			double		F_PlanMoney;
			std::string	F_SpecialOffers;
			int			F_CommunicationType;//��ͨ��ʽ
			int			F_Stage;//��չ�׶�
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
		UMS_OPR_CommunicationTypeInfo(��ͨ����)
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
		typedef std::list<UMS_OPR_CommunicationTypeInfo> ListUMS_OPR_CommunicationTypeInfo;//UMS_OPR_CommunicationTypeInfo(��ͨ����)List����

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
		typedef std::list<VIEW_OPR_CommonCustomerInfo> ListVIEW_OPR_CommonCustomerInfo;//VIEW_OPR_CommonCustomerInfoList����


		/************************************************************************/
		/*
		UMS_OPR_ApproveInfo (��ͨ������)
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
		typedef std::list<UMS_OPR_ApproveInfo> ListUMS_OPR_ApproveInfo;//UMS_OPR_ApproveInfo (��ͨ������)List����

		/************************************************************************/
		/*
		VIEW_����ҵ��Ա��ѯ��ͨ��¼
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
			std::string BusinessManName;		//ҵ��Ա����;        
			std::string Communication_Nature;	//��ͨ����;        
			std::string Communication_Mode;		//��ͨ��ʽ;
		};
		typedef std::list<VIEW_GetCommunicationRecordByBusinessMan> ListVIEW_GetCommunicationRecordByBusinessMan;//VIEW_����ҵ��Ա��ѯ��ͨ��¼List����

		/************************************************************************/
		/*
		UMS_OPR��ҳ��ͨ��¼
		*/
		/************************************************************************/
		struct UMS_OPRCommunicationrecordPagging
		{
			ListVIEW_GetCommunicationRecordByBusinessMan	listview_getcommunicationrecordbybusinessman;	//VIEW_����ҵ��Ա��ѯ��ͨ��¼List����
			int												page_count;		
		};
		typedef std::list<UMS_OPRCommunicationrecordPagging> ListUMS_OPRCommunicationrecordPagging;//UMS_OPR��ҳ��ͨ��¼List����

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
		typedef std::list<VIEW_POS_ShopMemberInfo> ListVIEW_POS_ShopMemberInfo;//VIEW_POS_ShopMemberInfoList����

		/************************************************************************/
		/*
		UMS_��ͨ�˿���Ϣ
		*/
		/************************************************************************/    
		struct UMS_Customer_info
		{        
			double		allconsumptionmoney;	//�����ѽ��;        
			std::string name;					//����;        
			std::string phoneno;				//�ֻ�����;        
			std::string address;				//��ַ;
		};
		typedef std::list<UMS_Customer_info> ListUMS_Customer_info;//UMS_��ͨ�˿���ϢList����

		/************************************************************************/
		/*
		UMS_OPR_���ѵ�ҵ����ͼ
		*/
		/************************************************************************/    
		struct UMS_OPR_Consumption_Business_view
		{        
			std::string numbers;			//����;        
			time_t		operation_date;		//��������;        
			double		shouldmoney;		//Ӧ�ս��;        
			double		actualmoney;		//ʵ�ս��;        
			double		onsalemoney;		//�Żݽ��;        
			std::string operater;			//����Ա;        
			int			ishaveproduct;		//�Ƿ��в�Ʒ;
		};
		typedef std::list<UMS_OPR_Consumption_Business_view> ListUMS_OPR_Consumption_Business_view;//UMS_OPR_���ѵ�ҵ����ͼList����

		/************************************************************************/
		/*
		UMS_��ͨ�˿����Ѽ�¼
		*/
		/************************************************************************/ 
		struct UMS_Ordinary_Consumption_record
		{        
			ListUMS_OPR_Consumption_Business_view	listums_opr_consumption_business_view;	//UMS_OPR_���ѵ�ҵ����ͼList����
			int										page_count;	
		};
		typedef std::list<UMS_Ordinary_Consumption_record> ListUMS_Ordinary_Consumption_record;//UMS_��ͨ�˿����Ѽ�¼List����

		/************************************************************************/
		/*
		UMS_BASE_�������ͱ�
		*/
		/************************************************************************/
		struct UMS_BASE_RoomTypeInfo
		{        
			std::string guid;			
			std::string shopguid;		//�ŵ�GUID;        
			std::string type;			//����;        
			std::string remark;			//��ע;  
			int			remembertag;	//��¼״̬;  
			std::string creater;		//������;        
			std::string creattime;		//����ʱ��;        
			std::string updateter;		//����޸���;        
			std::string updatetime;		//����޸�ʱ��; 
		};
		typedef std::list<UMS_BASE_RoomTypeInfo> ListUMS_BASE_RoomTypeInfo;//UMS_BASE_�������ͱ�List����

		/************************************************************************/
		/*
		UMS_BASE_������Ϣ��
		*/
		/************************************************************************/
		struct UMS_BASE_RoomInfo
		{        
			std::string guid;			
			std::string shopguid;		//�ŵ�GUID;        
			std::string room_code;		//����;        
			std::string room_name;		//����;        
			std::string room_size;		//��С;        
			int			order;			//����;        
			std::string room_type;		//��������;        
			int			state;			//״̬;	//0���� 1 ʹ��
			std::string remark;			//��ע;        
			int			remembertag;	//��¼״̬;  
			std::string creater;		//������;        
			std::string creattime;		//����ʱ��;        
			std::string updateter;		//����޸���;        
			std::string updatetime;		//����޸�ʱ��; 
		};
		typedef std::list<UMS_BASE_RoomInfo> ListUMS_BASE_RoomInfo;//UMS_BASE_������Ϣ��List����

		/************************************************************************/
		/*
		VIEW_��Ա��ͨ�˿���Ϣ��ͼ
		*/
		/************************************************************************/    
		struct VIEW_MemberAndOrdinary_Info_View
		{        
			std::string membername;		//��Ա����;        
			std::string phone;			//�ֻ�;        
			std::string address;		//��ַ;         
			std::string guid;        
			int			membertype;		//��Ա����;//1��Ա 2��ͨ�˿�        
			std::string otherphone;		//�����绰;
		};
		typedef std::list<VIEW_MemberAndOrdinary_Info_View> ListVIEW_MemberAndOrdinary_Info_View;//VIEW_��Ա��ͨ�˿���Ϣ��ͼList����

		/************************************************************************/
		/*
		UMS_BASE_�ŵ��Ա����
		*/
		/************************************************************************/
		struct UMS_BASE_ShopMemberLeave
		{
			int			id;
			std::string guid;
			std::string	shop_guid;		//�ŵ�GUID;
			std::string member_type;	//��Ա����;   
			int			order;			//����; 
			std::string remark;			//��ע;        
			int			remembertag;	//��¼״̬;  
			std::string creater;		//������;        
			time_t		creattime;		//����ʱ��;        
			std::string updateter;		//����޸���;        
			time_t		updatetime;		//����޸�ʱ��

		};
		typedef std::list<UMS_BASE_ShopMemberLeave> ListUMS_BASE_ShopMemberLeave;//UMS_BASE_�ŵ��Ա����List����

		/************************************************************************/
		/*
		UMS_�Ż�ȯ
		*/
		/************************************************************************/
		struct UMS_Coupon
		{        
			int			id;			//�Ż�ȯID
			std::string couponname;	//�Ż�ȯ����;
		};
		typedef std::list<UMS_Coupon> ListUMS_Coupon;//UMS_�Ż�ȯList����

		/************************************************************************/
		/*
		UMS_Company_�ŵ��Ż�ȯ
		*/
		/************************************************************************/
		struct UMS_Company_ShopCoupon
		{        
			int			id;        
			std::string guid;        
			std::string contractguid;	//��ͬGUID;        
			int			couponid;		//�Ż�ȯID;        
			std::string merchantguid;	//�̻�GUID;        
			std::string shopguid;		//�ŵ�GUID;        
			std::string couponname;		//�Ż�ȯ����;        
			int			count;			//����;        
			double		condition1;		//����1;        
			double		condition2;		//����2;        
			std::string contractimg;	//�Ż�ȯͼƬ;        
			std::string startdate;		//��ʼ����;        
			std::string enddate;		//��ֹ����;        
			std::string starttime;		//��ʼʱ��;        
			std::string endtime;		//����ʱ��;        
			std::string usedweek;		//ʹ������;   
			std::string member_leave;	//��Ա����;        
			std::string formula;		//��ʽ;       
			int			usedalone;		//����ʹ��;          
			std::string explain;		//ʹ��˵��;   
			int			state;			//״̬;                 
			std::string remark;			//��ע; 
			int			remembertag;	//��¼״̬;  
			std::string creater;		//������;        
			time_t		creattime;		//����ʱ��;        
			std::string updateter;		//����޸���;        
			time_t		updatetime;		//����޸�ʱ��
			int			toexamine;		//���;//0:δ���  1���ͨ��        
			int			shopid;			//�ŵ�ID;
		};
		typedef std::list<UMS_Company_ShopCoupon> ListUMS_Company_ShopCoupon;//UMS_Company_�ŵ��Ż�ȯList����

		/************************************************************************/
		/*
		UMS_Company_�Ż�ȯ
		*/
		/************************************************************************/     
		struct UMS_Company_Coupon
		{
			int			id;        
			std::string guid;        
			std::string contractguid;	//��ͬGUID;        
			int			couponid;		//�Ż�ȯID;        
			std::string merchantguid;	//�̻�GUID;         
			std::string couponname;		//�Ż�ȯ����;        
			int			count;			//����;        
			double		condition1;		//����1;        
			double		condition2;		//����2;        
			std::string contractimg;	//�Ż�ȯͼƬ;        
			std::string startdate;		//��ʼ����;        
			std::string enddate;		//��ֹ����;        
			std::string starttime;		//��ʼʱ��;        
			std::string endtime;		//����ʱ��;        
			std::string usedweek;		//ʹ������;   
			std::string member_leave;	//��Ա����;        
			std::string formula;		//��ʽ;       
			int			usedalone;		//����ʹ��;          
			std::string explain;		//ʹ��˵��;   
			int			state;			//״̬;                 
			std::string remark;			//��ע; 
			int			remembertag;	//��¼״̬;  
			std::string creater;		//������;        
			time_t		creattime;		//����ʱ��;        
			std::string updateter;		//����޸���;        
			time_t		updatetime;		//����޸�ʱ��
			int			toexamine;		//���;//0:δ���  1���ͨ��        
			int			shopid;			//�ŵ�ID;
		};
		typedef std::list<UMS_Company_Coupon> ListUMS_Company_Coupon;//UMS_Company_�Ż�ȯList����

		/************************************************************************/
		/*
		UMS_OPR_��ԱԤ������
		*/
		/************************************************************************/
		struct UMS_OPR_MemberOrderInfo
		{
			int			id;
			std::string guid;
			std::string numbers;		//����;
			std::string shopguid;		//�ŵ�GUID;
			std::string memberguid;		//��ԱGUID;
			int			peoplecount;	//����;
			std::string ordertime;		//Ԥ��ʱ��;
			std::string source;			//��Դ;
			std::string roomtype;		//��������;
			std::string roomguid;		//����GUID;
			std::string identity;		//���;
			int			state;			//״̬;
			std::string reply;			//�ظ�;
			std::string remark;			//��ע;
			int			remembertag;	//��¼״̬;  
			std::string creater;		//������;        
			std::string creattime;		//����ʱ��;        
			std::string updateter;		//����޸���;        
			std::string updatetime;		//����޸�ʱ��
			int			orderpeopeltype;//Ԥ��������;
		};
		typedef std::list<UMS_OPR_MemberOrderInfo> ListUMS_OPR_MemberOrderInfo;//UMS_OPR_��ԱԤ������List����

		/************************************************************************/
		/*
		UMS_�����ֵ���ϸ��
		*/
		/************************************************************************/
		struct UMS_dictionaryDetails
		{        
			int			id;        
			std::string name;	//����;
		};
		typedef std::list<UMS_dictionaryDetails> ListUMS_dictionaryDetails;//UMS_�����ֵ���ϸ��List����

		/************************************************************************/
		/*
		������Ϣ
		*/
		/************************************************************************/
		struct Returnmessage
		{        
			std::string message;    //��Ϣ   
			bool		isok;		//�Ƿ�ɹ�;        
			std::string cardno;		//����;
		};
		typedef std::list<Returnmessage> ListReturnmessage;//������ϢList����

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
		typedef std::list<UMS_BASE_ShopMemberInfo> ListUMS_BASE_ShopMemberInfo;//UMS_BASE_ShopMemberInfoList����

		/************************************************************************/
		/*
		UMS_BASE_��Ա����Ϣ��
		*/
		/************************************************************************/
		struct UMS_BASE_MemberCardInfo
		{
			int			id;
			std::string guid;
			std::string userguid;			//�û�GUID;
			std::string cardno;				//����;
			std::string physicsno;			//������;
			std::string pwd;				//����;
			std::string storedleave;		//��ֵ������;
			std::string lokleave;			//���ֿ�����;
			std::string getcarddate;		//��������;
			std::string overduedate;		//��������;
			std::string getcardshopguid;	//�����ŵ�GUID;
			int			state;				//״̬;
			int			cardstate;			//��״̬;
			std::string remark;				//��ע;
			int			remembertag;		//��¼״̬;  
			std::string creater;			//������;        
			std::string creattime;			//����ʱ��;        
			std::string updateter;			//����޸���;        
			std::string updatetime;			//����޸�ʱ��;
		};
		typedef std::list<UMS_BASE_MemberCardInfo> ListUMS_BASE_MemberCardInfo;//UMS_BASE_MemberCardInfo List����

		/************************************************************************/
		/* 
		VIEW_POS_ShopMemberInfoPage
		*/
		/************************************************************************/
		struct VIEW_POS_ShopMemberInfoPage
		{        
			int							page_count;	       
			ListVIEW_POS_ShopMemberInfo view_pos_shopmemberinfo;//VIEW_POS_ShopMemberInfo List����
		};
		typedef std::list<VIEW_POS_ShopMemberInfoPage> ListVIEW_POS_ShopMemberInfoPage;//VIEW_POS_ShopMemberInfoPage List����

		/************************************************************************/
		/* 
		UMS_OPR_��Ա��״̬�����
		*/
		/************************************************************************/
		struct UMS_OPR_MemberCardStateUpdateInfo
		{
			int			id;
			std::string guid;
			std::string shopguid;			//�ŵ�GUID;
			std::string cardno;				//����;
			int			type;				//����;
			int			state;				//״̬;
			std::string operationexplain;	//����˵��;
			time_t		operationdate;		//��������;
			std::string operaterguid;		//������GUID;
			std::string remark;				//��ע;
			int			remembertag;		//��¼״̬;  
			std::string creater;			//������;        
			time_t		creattime;			//����ʱ��;        
			std::string updateter;			//����޸���;        
			time_t		updatetime;			//����޸�ʱ��;
		};
		typedef std::list<UMS_OPR_MemberCardStateUpdateInfo> ListUMS_OPR_MemberCardStateUpdateInfo;//UMS_OPR_��Ա��״̬����� List����

		/************************************************************************/
		/*
		UMS_Base_������Ϣ
		*/
		/************************************************************************/
		struct UMSBaseAreainfo
		{
			int			id;				//ID
			std::string guid;			//GUID
			int			father_id;		//��ID
			std::string area_name;		//��������
			double		longitude;		//����
			double		latitude;		//γ��
			int			marqueezoom;	//�Ŵ����
			int			sort_order;		//����
			int			deep_level;		//���
			std::string remark;			//��ע
			int			record_status;	//��¼״̬
			std::string creator;		//������
			time_t		create_time;	//����ʱ��
			std::string last_update_op;	//����޸���
			time_t      last_update_time;//����޸�ʱ��
		};
		typedef std::list<UMSBaseAreainfo> ListUMSBaseAreainfo;

		/************************************************************************/
		/*
		UMS_Base_��Ա����
		*/
		/************************************************************************/ 
		struct UMSMemberLevel
		{
			std::string member_level_guid;	  //GUID		
			std::string member_level_name;	  //��Ա����
		};
		typedef std::list<UMSMemberLevel> ListUMSMemberLevel; //��Ա�����List����


		/************************************************************************/
		/*
		VIEW_���ѵ���ϸ��ͼ
		*/
		/************************************************************************/ 
		struct UMSConsumeMenuSingleDetailView
		{
			int			menu_id;			//id
			std::string menu_guid;			//GUID
			std::string menu_single;		//����
			std::string menu_name;			//Ʒ��
			std::string menu_name_guid;		//Ʒ��GUID
			double		menu_num;			//����
			int			menu_status;	    //״̬
			std::string menu_remark;        //��ע
			int			menu_log_status;    //��¼״̬
			std::string menu_create_name;   //������
			time_t		menu_create_time;   //����ʱ��
			std::string menu_update_name;   //����޸���
			time_t		menu_update_time;   //����޸�ʱ��
			std::string menu_unit;          //��λ
			double		menu_price;         //����
		};
		typedef std::list<UMSConsumeMenuSingleDetailView> ListUMSConsumeMenuSingleDetailView; //���Ѳ�Ʒ��ϸ��List����

		/************************************************************************/
		/*
		UMS_���Ż�Ա������Ϣ
		*/
		/************************************************************************/ 
		struct UMSGroupMemberCashDetail
		{
			time_t group_opertion_time;	   //����ʱ��
			int			group_type;                //����
			std::string group_card_no;			   //����
			std::string group_member_name;		   //��Ա����
			double 		group_account_price;       //Ӧ�����
			double 		group_preferential_price;  //�Żݽ��
			double 		group_practice_price;      //ʵ�ս��
			double 		group_balance;             //���
			std::string group_single;   		   //ҵ�񵥺�
			int			group_is_bool;             //�Ƿ��в�Ʒ
			std::string group_member_guid;		   //��Աguid
			std::string group_phone;				//�ֻ�����

		};
		typedef std::list<UMSGroupMemberCashDetail> ListUMSGroupMemberCashDetail; //���Ż�Ա������ϸ��List����

		/************************************************************************/
		/*
		UMS_��ҳ���Ż�Ա������Ϣ
		*/
		/************************************************************************/ 
		struct UMSGroupMemberCashView
		{
			ListUMSGroupMemberCashDetail group_cash_info;  //���Ż�Ա������ϸ
			int group_count;  //������
		};
		typedef std::list<UMSGroupMemberCashView> ListUMSGroupMemberCashView; //���Ż�Ա���ѽṹ��List����

		/************************************************************************/
		/*
		VIEW_��ֵ��Ա������Ϣ
		*/
		/************************************************************************/ 
		struct UMSLocalMemberCashDetail
		{
			time_t		 local_operation_time;		//����ʱ��
			int			 local_marker;              //��ʶ
			std::string  local_card_no;				//����
			std::string  local_member_name;			//��Ա����
			double 		local_account_price;        //����Ӧ��
			double 		local_preferential_price;   //�Żݽ��
			double 		local_practice_price;       //��ֵ��ֿ�
			double 		local_balance;              //���
			std::string local_operation_name; 		 //����Ա
			std::string local_single;         		 //ҵ�񵥺�
			int			 local_is_bool;       		 //�Ƿ��в�Ʒ
		};
		typedef std::list<UMSLocalMemberCashDetail> ListUMSLocalMemberCashDetail; //��ֵ��Ա������ϸ��List����

		/************************************************************************/
		/*
		VIEW_��ҳ��ֵ��Ա������Ϣ
		*/
		/************************************************************************/ 
		struct UMSLocalMemberCashView
		{
			int local_count ;                     //������
			ListUMSLocalMemberCashDetail local_info;  //��ֵ��Ա������ϸ
		};
		typedef std::list<UMSLocalMemberCashView> ListUMSLocalMemberCashView; //��ֵ��Ա������ͼ��List����

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
		typedef std::list<UMS_OPR_MachineInfo> ListUMS_OPR_MachineInfo; //UMS_OPR_MachineInfo��List����

		/************************************************************************/
		/*
		UMS_������Ļ�ԱԤ����Ϣ
		*/
		/************************************************************************/ 
		struct UMSWaitMemberInfo
		{
			int			wait_id;              //ID
			std::string wait_guid;            //GUID
			std::string wait_single;          //����
			std::string wait_member_guid;     //��Աguid
			std::string wait_member_origin;   //��Դ
			std::string wait_room_type;       //��������
			std::string wait_order_time;      //Ԥ��ʱ��
			std::string wait_create_time;     //����ʱ��
			int			wait_status;          //״̬
			std::string wait_member_name;     //��Ա����
			std::string wait_phone;           //�ֻ�
			int			wait_preson_num;      //����
			std::string wait_roomtype_name;   //������������	
		};
		typedef std::list<UMSWaitMemberInfo> ListUMSWaitMemberInfo; //UMS_OPR_MachineInfo��List����

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
		typedef std::list<UMS_OPR_CommonCustomerInfo> ListUMS_OPR_CommonCustomerInfo; //VIEW_POS_ShopMemberInfo��List����

		/************************************************************************/
		/*
		VIEW_CommonCustomerInfo
		*/
		/************************************************************************/ 
		struct VIEW_CommonCustomerInfo
		{
			int								allcount;//������
			ListUMS_OPR_CommonCustomerInfo  listums_opr_commoncustomerinfo;
		};
		typedef std::list<VIEW_CommonCustomerInfo> ListVIEW_CommonCustomerInfo; //VIEW_POS_ShopMemberInfo��List����

		/************************************************************************/
		/*
		UMS_�ŵ����ֻ�Ա��Ϣ
		*/
		/************************************************************************/ 
		struct UMSUniteMemberInfo
		{
			std::string unite_member_guid;   //��ԱGUID 
			std::string unite_member_phone;  //�ֻ� 
			std::string unite_card_no;       //���� 
			std::string unite_member_name;   //��Ա����
			double		unite_total_cash;    //�ۼ����ѽ��
			std::string unite_acount_no;     //�˻���
		};
		typedef std::list<UMSUniteMemberInfo> ListUMSUniteMemberInfo; //VIEW_POS_ShopMemberInfo��List����

		/************************************************************************/
		/*
		UMS_��ҳ�ŵ����ֻ�Ա��Ϣ
		*/
		/************************************************************************/ 
		struct VIEW_UniteMemberInfoPage
		{
			int						allcount;//������
			ListUMSUniteMemberInfo listums_opr_commoncustomerinfo;
		};
		typedef std::list<VIEW_UniteMemberInfoPage> ListVIEW_UniteMemberInfoPage; //VIEW_POS_ShopMemberInfo��List����

		/************************************************************************/
		/*
		UMS_BASE_��Ʒ��Ϣ��
		*/
		/************************************************************************/
		struct productInfo
		{
			std::string product_guid ;									//GUID
			std::string shop_guid ;										//�ŵ�GUID ;
			std::string product_coding ;								//���� ;
			std::string product_name ;									//Ʒ�� ;
			std::string product_spec ;									//��� ;
			std::string product_type_guid ;								//��� ;
			double		product_unit_price;								//���� ; 
			double		product_purchase_price;							//������ ;
			std::string product_unit;								//��λ ; 
			int			product_sort;									//���� ; 
			std::string product_casing;									//��װ ; 
			std::string product_image;									//ͼƬ ; 
			std::string product_easy_know;								//������ ; 
			std::string remark;											//��ע ; 
			int			record_status;									//��¼״̬
			std::string creator;										//������
			std::string	create_time;									//����ʱ��
			std::string last_update_op;									//����޸���
			std::string last_update_time;								//����޸�ʱ��
		};
		typedef std::list<productInfo> ListproductInfo;
		/************************************************************************/
		/*
		UMS_BASE_��Ʒ��Ϣ��ͼ
		*/
		/************************************************************************/
		struct ViewProductInfo
		{
			std::string product_guid ;									//GUID
			std::string shop_guid ;										//�ŵ�GUID
			std::string product_coding ;								//����
			std::string product_name ;									//Ʒ��
			std::string product_spec ;									//���
			std::string product_type_guid ;								//���
			std::string product_type_name ;								//�������
			int			product_type_kind ;								//�������
			double		product_purchase_price;							//������ ; 
			double		product_unit_price;								//���� ;
			std::string product_unit;									//��λ ;
			int			product_sort;									//���� ;
			std::string product_casing;									//��װ ;
			std::string product_image;									//ͼƬ ;
			std::string product_easy_know;								//������ ;
			std::string remark;											//��ע ;
		};
		typedef std::list<ViewProductInfo> ListViewProductInfo;		//UMS_BASE_��Ʒ��Ϣ��ͼList����

		/************************************************************************/
		/*
		UMS_BASE_��ҳ��Ʒ��Ϣ��
		*/
		/************************************************************************/
		struct ViewProductInfoPagging
		{
			int					page_count ;							//������
			ListViewProductInfo list_view_pruductInfo ;					//UMS_BASE_��Ʒ��Ϣ��ͼ
		};
		typedef std::list<ViewProductInfoPagging> ListViewProductInfoPagging;
		/************************************************************************/
		/*
		UMS_BASE_��Ʒ����
		*/
		/************************************************************************/
		struct productTypeInfo
		{
			std::string type_guid;										//GUID ;
			std::string shop_guid;										//�ŵ�GUID ;
			std::string father_guid;									//��GUID ;
			std::string type_name;										//��� ;
			int			type_sort;										//���� ;
			std::string remark;											//��ע ; 
			int			record_status;									//��¼״̬
			std::string creator;										//������
			std::string create_time;									//����ʱ��
			std::string last_update_op;									//����޸���
			std::string last_update_time;								//����޸�ʱ��
			int			type_kind;										//������� ;
			int			relation_kind;									//�������� ;
		};
		typedef std::list<productTypeInfo> ListproductTypeInfo;		//UMS_BASE_��Ʒ���� List����

		/************************************************************************/
		/*
		UMS_BASE_����Ԥ����Ϣ��ͼ
		*/
		/************************************************************************/
		struct ViewRoomOrderInfo
		{

			std::string room_guid;										//GUID ;
			std::string easy_know;										//���� ;
			std::string room_name;										//���� ;
			std::string room_size;										//��С ;
			int			room_sort;										//���� ;
			std::string room_type_guid;									//�������� ;
			std::string room_type_name;									//������������ ;
			int			room_status;									//״̬ ;//0���� 1 ʹ��
			std::string remark;											//��ע ;
		};
		typedef std::list<ViewRoomOrderInfo> ListViewRoomOrderInfo;		//UMS_BASE_����Ԥ����Ϣ��ͼList����

		/************************************************************************/
		/*
		UMS_BASE_��ҳ����Ԥ����Ϣ��ͼ
		*/
		/************************************************************************/
		struct ViewRoomOrderInfoPagging
		{

			ListViewRoomOrderInfo list_view_roomOrderInfo ;			//ums_����Ԥ����Ϣ��ͼ ;
			int page_count;											//������ ;
		};
		typedef std::list<ViewRoomOrderInfoPagging> ListViewRoomOrderInfoPagging;
		/************************************************************************/
		/*
		UMS_BASE_������Ϣ��
		*/
		/************************************************************************/
		struct roomInfo
		{
			std::string room_guid;										//GUID ;
			std::string shop_guid;										//�ŵ�GUID ;
			std::string easy_know;										//���� ;
			std::string room_name;										//���� ;
			std::string room_size;										//��С ;
			int			room_sort;										//���� ;
			std::string room_type_guid;										//�������� ;
			int			room_status;									//״̬ ;//0���� 1 ʹ��
			std::string remark;											//��ע ; 
			int			record_status;									//��¼״̬
			std::string creator;										//������
			std::string create_time;									//����ʱ��
			std::string last_update_op;									//����޸���
			std::string last_update_time;								//����޸�ʱ��
		};
		typedef std::list<roomInfo> ListroomInfo;
		/************************************************************************/
		/*
		UMS_BASE_������Ϣ��ͼ
		*/
		/************************************************************************/
		struct ViewRoomInfo
		{

			std::string room_guid;										//GUID ;
			std::string easy_know;										//���� ;
			std::string room_name;										//���� ;
			std::string room_size;										//��С ;
			std::string room_type_guid;									//�������� ;
			std::string room_type_name;									//������������ ;
			int			room_status;									//״̬ ;//0���� 1 ʹ��
			std::string remark;											//��ע ;
		};
		typedef std::list<ViewRoomInfo> ListViewRoomInfo;
		/************************************************************************/
		/*
		VIEW_�ŵ��Ż�ȯ
		*/
		/************************************************************************/
		struct	ViewFavourableTicketInfo
		{

			int			ticket_id;										//��ʶ ;
			std::string ticket_guid;									//GUID ;
			std::string ticket_name;									//�Ż�ȯ���� ;
			std::string ticket_type;									//�Ż�ȯ�������� ;
			time_t		ticket_date_start;								//��ʼ���� ;
			time_t		ticket_date_end;								//��ֹ���� ;
			std::string ticket_hour_start;								//��ʼʱ�� ;
			std::string ticket_hour_end;								//����ʱ�� ;
			std::string ticket_explain;									//ʹ��˵�� ;
			int			ticket_approve;									//��� ;
		};
		typedef std::list<ViewFavourableTicketInfo> ListViewFavourableTicketInfo;		//VIEW_�ŵ��Ż�ȯList����

		/************************************************************************/
		/*
		ConsumerSingleDetails
		*/
		/************************************************************************/
		struct ConsumerSingleDetails  //���ѵ���ϸ
		{

			std::string GUID ;
			std::string ConsumeID ;										//ҵ�񵥺�
			std::string ProductGuid ;									//��Ʒguid
			double		Number ;										//����
		};
		typedef std::list<ConsumerSingleDetails> ListConsumerSingleDetails;
		/************************************************************************/
		/*
		ConsumptionSingleBusiness
		*/
		/************************************************************************/
		struct ConsumptionSingleBusiness  //���ѵ�ҵ���
		{

			std::string GUID ;											//GUID
			std::string ShopGuid ;										//�ŵ�GUID
			std::string MemberGuid ;									//��ԱGUID
			std::string MemberName ;									//��Ա����
			std::string MemberPhone ;									//��Ա�绰
			double		money ;											//���ѽ��
			std::string OperatorGuid ;									//����ԱGUID
			std::string Address ;										//��ַ
			int			ConsumeType ;									//��������
			std::string Mark ;											//��ʾ
			time_t		OrderTime ;										//����ʱ��
		};
		typedef std::list<ConsumptionSingleBusiness> ListConsumptionSingleBusiness;		//UMS_�ŵ����ֻ�Ա������ϢList����


		/************************************************************************/
		/*
		UMS_�ŵ����ֻ�Ա������Ϣ
		*/
		/************************************************************************/
		struct uniteMemberConsumeInfo
		{

			//time_t		operator_time;									//����ʱ�� ;
			std::string operator_time;									//����ʱ�� ;
			double		money_need;										//Ӧ����� ;
			double		money_forfree;									//�Żݽ�� ;
			double		money_pay;										//ʵ�ս�� ;
			double		balance;										//��� ;
			int			isExistProduct;									//�Ƿ��в�Ʒ ;
			std::string billno;											//���� ;
			std::string member_guid;									//��ԱGUID ;
			std::string accountNo;										//�ʻ��� ;
		};
		typedef std::list<uniteMemberConsumeInfo> ListUniteMemberConsumeInfo;		//UMS_�ŵ����ֻ�Ա������ϢList����

		/************************************************************************/
		/*
		UMS_��ҳ�ŵ����ֻ�Ա������Ϣ
		*/
		/************************************************************************/
		struct uniteMemberConsumeInfoPagging
		{
			int						page_count;						//������ ;
			ListUniteMemberConsumeInfo list_UniteMemberConsumeInfo;	//ums_�ŵ����ֻ�Ա������Ϣ ;
		};
	}
}