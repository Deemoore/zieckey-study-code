#include "Request.h"
#include "WeiboApi.h"


#define TXWB_BASE_URL  "http://open.t.qq.com"
//static Txwb_key_list g_weibo_keylist_t[TXWB_MAX];


HTTP_RESULTCODE  SyncRequest(const char* pReqUrl,  EHttpMethod eHttpMethod, CWeiboParam oQWBlogParam, char* &pResultData,int &nLen )
{
	std::string strData;
	HTTP_RESULTCODE eErrorCode = CRequest::GetInstance()->SyncRequest(pReqUrl, eHttpMethod, oQWBlogParam, strData);
	
	char* pszData = new char[strData.length()];
	memcpy(pszData,strData.c_str(),strData.length());
	pResultData = pszData;
	nLen = strData.length();
	return eErrorCode;
}

bool  AsyncRequest( const char* pReqUrl, EHttpMethod eHttpMethod,  CWeiboParam oQWBlogParam, VWeiboCallback * pCallback )
{
	return CRequest::GetInstance()->AsyncRequest(pReqUrl, eHttpMethod, oQWBlogParam, pCallback);
}

void  ReleaseData( void* p )
{
   if(p)
     delete []p;
}



//根据api的类型获取对应的uri
static const char* txwb_get_uri(Txwb_api_option option)
{

	static const char txwb_uri_t[TXWB_MAX][64] = {
		"base",

		
		//时间线
		"/api/statuses/home_timeline",
		"/api/statuses/public_timeline",
		"/api/statuses/user_timeline",
		"/api/statuses/mentions_timeline",
		"/api/statuses/ht_timeline",
		"/api/statuses/broadcast_timeline",
		"/api/statuses/special_timeline",
		"/api/statuses/area_timeline",
		"/api/statuses/home_timeline_ids",
		"/api/statuses/user_timeline_ids",
		"/api/statuses/broadcast_timeline_ids",
		"/api/statuses/mentions_timeline_ids",
		"/api/statuses/users_timeline",
		"/api/statuses/users_timeline_ids",
		//==14


		//微博相关
		"/api/t/show",
		"/api/t/add",
		"/api/t/del",
		"/api/t/re_add",
		"/api/t/reply",
		"/api/t/add_pic",
		"/api/t/re_count",
		"/api/t/re_list",
		"/api/t/comment",
		"/api/t/add_music",
		"/api/t/add_video",
		"/api/t/getvideoinfo",
		"/api/t/list",
		"/api/t/add_video_prev",
		//28


		//账户相关
		"/api/user/info",
		"/api/user/update",
		"/api/user/update_head",
		"/api/user/update_edu",
		"/api/user/other_info",
		"/api/user/infos",
		//33

		//关系链相关
		
		"/api/friends/fanslist",
		"/api/friends/idollist",
		"/api/friends/blacklist",


		"/api/friends/speciallist",
		"/api/friends/add",
		"/api/friends/del",


		"/api/friends/addspecial",
		"/api/friends/delspecial",
		"/api/friends/addblacklist",


		"/api/friends/delblacklist",
		"/api/friends/check",
		"/api/friends/user_fanslist",

		"/api/friends/user_idollist",
		"/api/friends/user_speciallist",
		"/api/friends/fanslist_s",
		"/api/friends/idollist_s",
		//49

		//私信相关
		"/api/private/add",
		"/api/private/del",
		"/api/private/recv",
		"/api/private/send",
		//53

		//搜索相关
		"/api/search/user",
		"/api/search/t",
		"/api/search/userbytag",
		//56

		//热度相关
		"/api/trends/ht",
		"/api/trends/t",
		//58

		//数据更新相关
		"/api/info/update",
		//59


		//数据收藏
		"/api/fav/addt",
		"/api/fav/delt",
		"/api/fav/list_t",
		"/api/fav/addht",
		"/api/fav/delht",
		"/api/fav/list_ht",
		//65

		//话题相关
		"/api/ht/ids",
		"/api/ht/info",
		//67


		//标签相关
		"/api/tag/add",
		"/api/tag/del",
		//69


		//其他other
		"/api/other/kownperson",
		"/api/other/shorturl",

		"/api/other/videokey"
		//72
		
		
	};

	if(option >=TXWB_MAX || option <=TXWB_BASE)
		return NULL;

	return txwb_uri_t[option];
	
}


//根据api的类型获取对应的url
std::string Weibo_get_url(Txwb_api_option option)
{
	std::string strret = "";
	const char* puri = txwb_get_uri(option);
	if(puri)
	{
		strret = TXWB_BASE_URL;
		strret += puri;
	}


	return strret;
}




EHttpMethod Weibo_get_httpmethd(Txwb_api_option option)
{
			static const EHttpMethod txwb_httpmethod_t[TXWB_MAX] = {
			EHttpMethod_Get,  // base , means nothing


			//时间线
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			// = 14


			//微博相关
			EHttpMethod_Get,
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Get,
			EHttpMethod_Post,

			//=28


			//账户相关
			EHttpMethod_Get,
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Get,
			EHttpMethod_Get,
			//=33


			//关系链相关

			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			


			EHttpMethod_Get,
			EHttpMethod_Post,
			EHttpMethod_Post,
			

			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Post,
			

			EHttpMethod_Post,
			EHttpMethod_Get,
			EHttpMethod_Get,

			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			//=49

			//私信相关
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Get,
			EHttpMethod_Get,
			//=54

			//搜索相关
			EHttpMethod_Get,
			EHttpMethod_Get,
			EHttpMethod_Get,
			//=57


			//热度相关
			EHttpMethod_Get,
			EHttpMethod_Get,
			//=59


			//数据更新相关
			EHttpMethod_Get,
			//=60

			//数据收藏
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Get,
			EHttpMethod_Post,
			EHttpMethod_Post,
			EHttpMethod_Get,
			//=65

			//话题相关
			EHttpMethod_Get,
			EHttpMethod_Get,
			// = 67

			//标签相关
			EHttpMethod_Post,
			EHttpMethod_Post,
			// = 69


			//其他other
			EHttpMethod_Get,
			EHttpMethod_Get,

			EHttpMethod_Get,
			// = 72

			

	};
	return txwb_httpmethod_t[option];
}

HTTP_RESULTCODE SyncRequestByOption(Txwb_api_option option,CWeiboParam oQWBlogParam,char * & pResultData,int & nLen)
{
	std::string requrl;

	//获取url
	requrl = Weibo_get_url(option);
	if(requrl == "" )
	{
		return HTTPRESULT_OPITON_ERR;
	}

	return SyncRequest(requrl.c_str(),Weibo_get_httpmethd(option),oQWBlogParam,pResultData,nLen);
}

bool  AsyncRequestByOption(Txwb_api_option option, CWeiboParam oQWBlogParam, VWeiboCallback * pCallback )
{
	std::string requrl;

	//获取url
	requrl = Weibo_get_url(option);
	if(requrl == "")
	{
		return HTTPRESULT_OPITON_ERR;
	}

	return AsyncRequest(requrl.c_str(),Weibo_get_httpmethd(option),oQWBlogParam,pCallback);
}


