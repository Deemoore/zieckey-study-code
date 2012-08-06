/** 
@file  
@brief	QWBlogAPI的请求获取数据的接口
@version	2010-11-15	

*/

#pragma once
#include <string>
#include "WeiboApi.h"
#include "WeiboParam.h"
#include "Http/Http.h"
#include <map>

struct tagWeiboRequest
{
	std::string					strUrl;
	CWeiboParam					oParam;
	VWeiboCallback*				pCallback;
};


class  CRequest : public VHttpCallback
{
public:	
	~CRequest();
	static CRequest* GetInstance(); 

	
	/** 同步请求数据
	    @param  strUrl              in :  请求url
		@param	eHttpMethod			in :  请求的类型
		@param  oQWBlogParam		in :  该请求所带的参数类对象
		@param  strData				out ：同步返回的数据

		@retval		HTTPRESULT_OK:成功	其它:失败
	*/
	HTTP_RESULTCODE SyncRequest(std::string strUrl,  EHttpMethod eHttpMethod,  
							CWeiboParam  oQWBlogParam, std::string & strData);
	


	/** 同步请求数据
	    @param strUrl           in : 请求url
		@param eRequest			in : 请求的类型
		@param oQWBlogParam		in : 该请求所带的参数类对象
		@param pCallback		in ：回调指针

		@retval		true:成功	false:失败
	*/
	bool      AsyncRequest(std::string strUrl, EHttpMethod eHttpMethod,  
							CWeiboParam  oQWBlogParam, VWeiboCallback * pCallback);



	/// http完成回调函数,  继承类必须实现该函数来获得上传下载结果的通知
	/** 
		@param pHttp			in： CHttp对象
		@param eErrorCode		in： 状态代码，取值HTTP_RESULTCODE
		@param strData			out：结果数据
	*/	
	virtual void OnHttpComplete(CHttp *pHttp, 
								HTTP_RESULTCODE eErrorCode, std::string& strData);


private:
	CRequest();
	CRequest(const CRequest& other);
	CRequest& operator=(const CRequest& other);

private:
	typedef std::map<CHttp*, tagWeiboRequest>	MapHttp2Request;
	MapHttp2Request									m_mapHttp2Request;
};



