/** 
@file  
@brief		微博对外接口
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
	HTTPRESULT_OK   = 0,		///<  成功	
	HTTPRESULT_TIMEOUT,         ///<  请求超时
	HTTPRESULT_CANTRESOLVE,     ///<  不能解析地址
	HTTPRESULT_CANTCONNECT,     ///<  不能连接
	HTTPRESULT_ERROR,           ///<  HTTP请求的数据错误 
	HTTPRESULT_TOOLAGRE,        ///<  返回的数据量太大
	HTTPRESULT_FAIL,		    ///<  失败
	HTTPRESULT_OPITON_ERR		///类型错误，无法生成有效url
};

namespace  TXWeibo
{
	/// 参数名
	namespace   Param
	{
		///oauth相关的参数名
		const std::string strCustomKey			= "strCustomKey";     
		const std::string strCustomSecrect		= "strCustomSecrect";
		const std::string strTokenKey			= "strTokenKey";
		const std::string strTokenSecrect		= "strTokenSecrect";
		const std::string strVerifyCode			= "oauth_verifier";
		const std::string strCallbackUrl		= "oauth_callback";


		///数据格式的参数名和参数值
		const std::string strFormat				= "format";		 ///< 请求的文件的格式：strJson或strXml
		const std::string strJson				= "json";	
		const std::string strXml				= "xml";	
	}
}





// 微博api的类型，枚举变量的命名除了timeline简写为tl之外，其他都与
//http://open.t.qq.com/resource.php?i=1,1 api 说明中的一致。
// 例如： t/show 获取一条微博数据对应的枚举变量为
//   TXWB_T_SHOW
//
typedef enum{
	TXWB_BASE=0,

	//时间线TXWB_STATUSES_
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

	//微博相关  TXWB_T_
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

	//账户相关TXWB_USER_
	TXWB_USER_INFO,
	TXWB_USER__UPDATE,
	TXWB_USER_UPDATE_HEAD,
	TXWB_USER_UPDATE_EDU,
	TXWB_USER_OTHER_INFO,
	TXWB_USER_INFOS,
	//=34

	//关系链相关 TXWB_FRIENDS_
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

	//私信相关TXWB_PRIVATE_
	TXWB_PRIVATE_ADD,
	TXWB_PRIVATE_DEL,
	TXWB_PRIVATE_RECV,
	TXWB_PRIVATE_SEND,
	//54


	//搜索相关 TXWB_SEARCH_
	TXWB_SEARCH_USER,
	TXWB_SEARCH_T,
	TXWB_SEARCH_USERBYTAG,  //通过标签搜索用户
	//57


	//热度，趋势相关  TXWB_TRENDS_
	TXWB_TRENDS_HT,
	TXWB_TRENDS_T,
	//=59

	//数据更新相关TXWB_INFO_
	TXWB_INFO_UPDATE,
	//=60



	//数据收藏TXWB_FAV_
	TXWB_FAV_ADDT,
	TXWB_FAV_DELT,
	TXWB_FAV_LIST_T,
	TXWB_FAV_ADDHT,
	TXWB_FAV_DELHT,
	TXWB_FAV_LIST_HT,
	//=66


	//话题相关TXWB_HT_
	TXWB_HT_IDS,
	TXWB_HT_INFO,
	//=68

	

	//标签相关TXWB_TAG_
	TXWB_TAG_ADD,
	TXWB_TAG_DEL,
	//=70



	//其他TXWB_OTHER_
	TXWB_OTHER_KNOWNPERSON,
	TXWB_OTHER_SHORTURL,
	TXWB_OTHER_VIDEOKEY,
	//=73


	TXWB_MAX
}Txwb_api_option;



class CWeiboParam;

/// 异步微博请求回调接口
class  VWeiboCallback
{
public:
	/// 异步微博请求回调函数
	/** 
		@param  eHttpRetCode    in :    Http错误码
		@param  pReqUrl			in :	请求URL
		@param  oParam			in :	该请求所带的参数类对象
		@param  pData			in :    返回的数据
		@param  nLen            in :    返回的数据长度
	*/	
	virtual void OnRequestComplete(HTTP_RESULTCODE eHttpRetCode,const char* pReqUrl, CWeiboParam oParam, const char*pData,int nLen) = 0;
};


/// 同步请求数据
/**
    @param  pReqUrl				in :    请求URL
	@param	eHttpMethod			in :	HTTP请求的类型,取值枚举EHttpMethod
	@param  oQWBlogParam		in :	该请求所带的参数类对象
	@param  pResultData			out：	同步返回的数据，需调用ReleaseData释放
	@param  nLen				out:    同步返沪的数据长度

	@retval		HTTPRESULT_OK:成功	其它:失败
*/
HTTP_RESULTCODE TXWeibo_API  SyncRequest(const char* pReqUrl, EHttpMethod eHttpMethod, 
								CWeiboParam oQWBlogParam, char* &pResultData,int &nLen);

/// 异步请求数据
/** 
	@param	pReqUrl 			in :	请求URL
	@param	eHttpMethod 		in :	HTTP请求的类型，取值枚举EHttpMethod
	@param	oQWBlogParam		in :	该请求所带的参数类对象
	@param	pCallback			in ：	回调指针

	@retval 	true:成功	false:失败
*/

bool TXWeibo_API  AsyncRequest(const char* pReqUrl,  EHttpMethod eHttpMethod, 
								CWeiboParam oQWBlogParam, VWeiboCallback * pCallback );

///释放在SDK中申请的内存
void TXWeibo_API  ReleaseData(void* p);


/// 同步请求数据
/**
    @param  option				in :   接口的类型，取值自Txwb_api_option
	@param  oQWBlogParam		in :	该请求所带的参数类对象
	@param  pResultData			out：	同步返回的数据，需调用ReleaseData释放
	@param  nLen				out:    同步返沪的数据长度

	@retval		HTTPRESULT_OK:成功	其它:失败
*/

HTTP_RESULTCODE TXWeibo_API SyncRequestByOption(Txwb_api_option option,
								CWeiboParam oQWBlogParam,char * & pResultData ,int & nLen);


/// 异步请求数据
/** 
	@param  option				in :   接口的类型，取值自Txwb_api_option
	@param	oQWBlogParam		in :	该请求所带的参数类对象
	@param	pCallback			in ：	回调指针

	@retval 	true:成功	false:失败
*/

bool TXWeibo_API AsyncRequestByOption(Txwb_api_option option,
								CWeiboParam oQWBlogParam,VWeiboCallback * pCallback);




