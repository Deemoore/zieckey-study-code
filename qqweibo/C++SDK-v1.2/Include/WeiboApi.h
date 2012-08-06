/** 
@file  
@brief		΢������ӿ�
@version	2010-11-18		
*/

#pragma once
#include <string>

#ifndef TXWeibo_API 
#define TXWeibo_API  __declspec(dllimport)
#endif

enum  EHttpMethod
{
	EHttpMethod_Get,
	EHttpMethod_Post,
};

enum HTTP_RESULTCODE
{
	HTTPRESULT_OK   = 0,		///<  �ɹ�	
	HTTPRESULT_TIMEOUT,         ///<  ����ʱ
	HTTPRESULT_CANTRESOLVE,     ///<  ���ܽ�����ַ
	HTTPRESULT_CANTCONNECT,     ///<  ��������
	HTTPRESULT_ERROR,           ///<  HTTP��������ݴ��� 
	HTTPRESULT_TOOLAGRE,        ///<  ���ص�������̫��
	HTTPRESULT_FAIL,		    ///<  ʧ��
	HTTPRESULT_OPITON_ERR		///���ʹ����޷�������Чurl
};

namespace  TXWeibo
{
	/// ������
	namespace   Param
	{
		///oauth��صĲ�����
		const std::string strCustomKey			= "strCustomKey";     
		const std::string strCustomSecrect		= "strCustomSecrect";
		const std::string strTokenKey			= "strTokenKey";
		const std::string strTokenSecrect		= "strTokenSecrect";
		const std::string strVerifyCode			= "oauth_verifier";
		const std::string strCallbackUrl		= "oauth_callback";


		///���ݸ�ʽ�Ĳ������Ͳ���ֵ
		const std::string strFormat				= "format";		 ///< ������ļ��ĸ�ʽ��strJson��strXml
		const std::string strJson				= "json";	
		const std::string strXml				= "xml";	
	}
}





// ΢��api�����ͣ�ö�ٱ�������������timeline��дΪtl֮�⣬��������
//http://open.t.qq.com/resource.php?i=1,1 api ˵���е�һ�¡�
// ���磺 t/show ��ȡһ��΢�����ݶ�Ӧ��ö�ٱ���Ϊ
//   TXWB_T_SHOW
//
typedef enum{
	TXWB_BASE=0,

	//ʱ����TXWB_STATUSES_
	TXWB_STATUSES_HOME_TL,
	TXWB_STATUSES_PUBLIC_TL,
	TXWB_STATUSES_USER_TL,
	TXWB_STATUSES_MENTIONS_TL,
	TXWB_STATUSES_HT_TL,
	TXWB_STATUSES_BROADCASET_TL,
	TXWB_STATUSES_SPECIAL_TL,
	TXWB_STATUSES_AREA_TL,
	TXWB_STATUSES_HOME_TL_IDS,
	TXWB_STATUSES_USER_TL_IDS,
	TXWB_STATUSES_BROADCASET_TL_IDS,
	TXWB_STATUSES_MENTIONS_TL_IDS,
	TXWB_STATUSES_USERS_TL,
	TXWB_STATUSES_USERS_TL_IDS,
	//=14

	//΢�����  TXWB_T_
	TXWB_T_SHOW,
	TXWB_T_ADD,
	TXWB_T_DEL,
	TXWB_T_RE_ADD,
	TXWB_T_REPLY,
	TXWB_T_ADD_PIC,
	TXWB_T_RE_COUNT,
	TXWB_T_RE_LIST,
	TXWB_T_COMMENT,
	TXWB_T_ADD_MUSIC,
	TXWB_T_ADD_VIDEO,
	TXWB_T_GETVIDEOINFO,
	TXWB_T_LIST,
	TXWB_T_ADD_VIDEO_PREV,
	//=28

	//�˻����TXWB_USER_
	TXWB_USER_INFO,
	TXWB_USER__UPDATE,
	TXWB_USER_UPDATE_HEAD,
	TXWB_USER_UPDATE_EDU,
	TXWB_USER_OTHER_INFO,
	TXWB_USER_INFOS,
	//=34

	//��ϵ����� TXWB_FRIENDS_
	TXWB_FRIENDS_FANSLIST,
	TXWB_FRIENDS_IDOLLIST,
	TXWB_FRIENDS_BLACKLIST,
	TXWB_FRIENDS_SPECIALLIST,
	TXWB_FRIENDS_ADD,
	TXWB_FRIENDS_DEL,
	TXWB_FRIENDS_ADDSPECIAL,
	TXWB_FRIENDS_DELSPECIAL,
	TXWB_FRIENDS_ADD_BLACKLIST,
	TXWB_FRIENDS_DELBLACKLIST,
	TXWB_FRIENDS_CHECK,
	TXWB_FRIENDS_USER_FANSLIST,
	TXWB_FRIENDS_USER_IDOLLIST,
	TXWB_FRIENDS_USER_SPECIALLIST,
	TXWB_FRIENDS_USER_FANSLIST_S,
	TXWB_FRIENDS_USER_IDOLIST_S,
	//50

	//˽�����TXWB_PRIVATE_
	TXWB_PRIVATE_ADD,
	TXWB_PRIVATE_DEL,
	TXWB_PRIVATE_RECV,
	TXWB_PRIVATE_SEND,
	//54


	//������� TXWB_SEARCH_
	TXWB_SEARCH_USER,
	TXWB_SEARCH_T,
	TXWB_SEARCH_USERBYTAG,  //ͨ����ǩ�����û�
	//57


	//�ȶȣ��������  TXWB_TRENDS_
	TXWB_TRENDS_HT,
	TXWB_TRENDS_T,
	//=59

	//���ݸ������TXWB_INFO_
	TXWB_INFO_UPDATE,
	//=60



	//�����ղ�TXWB_FAV_
	TXWB_FAV_ADDT,
	TXWB_FAV_DELT,
	TXWB_FAV_LIST_T,
	TXWB_FAV_ADDHT,
	TXWB_FAV_DELHT,
	TXWB_FAV_LIST_HT,
	//=66


	//�������TXWB_HT_
	TXWB_HT_IDS,
	TXWB_HT_INFO,
	//=68

	

	//��ǩ���TXWB_TAG_
	TXWB_TAG_ADD,
	TXWB_TAG_DEL,
	//=70



	//����TXWB_OTHER_
	TXWB_OTHER_KNOWNPERSON,
	TXWB_OTHER_SHORTURL,
	TXWB_OTHER_VIDEOKEY,
	//=73


	TXWB_MAX
}Txwb_api_option;



class CWeiboParam;

/// �첽΢������ص��ӿ�
class  VWeiboCallback
{
public:
	/// �첽΢������ص�����
	/** 
		@param  eHttpRetCode    in :    Http������
		@param  pReqUrl			in :	����URL
		@param  oParam			in :	�����������Ĳ��������
		@param  pData			in :    ���ص�����
		@param  nLen            in :    ���ص����ݳ���
	*/	
	virtual void OnRequestComplete(HTTP_RESULTCODE eHttpRetCode,const char* pReqUrl, CWeiboParam oParam, const char*pData,int nLen) = 0;
};


/// ͬ����������
/**
    @param  pReqUrl				in :    ����URL
	@param	eHttpMethod			in :	HTTP���������,ȡֵö��EHttpMethod
	@param  oQWBlogParam		in :	�����������Ĳ��������
	@param  pResultData			out��	ͬ�����ص����ݣ������ReleaseData�ͷ�
	@param  nLen				out:    ͬ�����������ݳ���

	@retval		HTTPRESULT_OK:�ɹ�	����:ʧ��
*/
HTTP_RESULTCODE TXWeibo_API  SyncRequest(const char* pReqUrl, EHttpMethod eHttpMethod, 
								CWeiboParam oQWBlogParam, char* &pResultData,int &nLen);

/// �첽��������
/** 
	@param	pReqUrl 			in :	����URL
	@param	eHttpMethod 		in :	HTTP��������ͣ�ȡֵö��EHttpMethod
	@param	oQWBlogParam		in :	�����������Ĳ��������
	@param	pCallback			in ��	�ص�ָ��

	@retval 	true:�ɹ�	false:ʧ��
*/

bool TXWeibo_API  AsyncRequest(const char* pReqUrl,  EHttpMethod eHttpMethod, 
								CWeiboParam oQWBlogParam, VWeiboCallback * pCallback );

///�ͷ���SDK��������ڴ�
void TXWeibo_API  ReleaseData(void* p);


/// ͬ����������
/**
    @param  option				in :   �ӿڵ����ͣ�ȡֵ��Txwb_api_option
	@param  oQWBlogParam		in :	�����������Ĳ��������
	@param  pResultData			out��	ͬ�����ص����ݣ������ReleaseData�ͷ�
	@param  nLen				out:    ͬ�����������ݳ���

	@retval		HTTPRESULT_OK:�ɹ�	����:ʧ��
*/

HTTP_RESULTCODE TXWeibo_API SyncRequestByOption(Txwb_api_option option,
								CWeiboParam oQWBlogParam,char * & pResultData ,int & nLen);


/// �첽��������
/** 
	@param  option				in :   �ӿڵ����ͣ�ȡֵ��Txwb_api_option
	@param	oQWBlogParam		in :	�����������Ĳ��������
	@param	pCallback			in ��	�ص�ָ��

	@retval 	true:�ɹ�	false:ʧ��
*/

bool TXWeibo_API AsyncRequestByOption(Txwb_api_option option,
								CWeiboParam oQWBlogParam,VWeiboCallback * pCallback);




