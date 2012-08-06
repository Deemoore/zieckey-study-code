/** 
@file  
@brief		得到相应请求的URL
@version	2010-11-16	
*/

#pragma once
#include <map>
#include "WeiboParam.h"
#include "Request.h"



const std::string c_strHttpGet  = "GET";
const std::string c_strHttpPost = "POST";

class  CRequestUrl
{
public:
	 ~CRequestUrl(void);

	 /// 获取单例CRequestUrl对象
	 static CRequestUrl* GetInstance(); 

     ///得到对应请求的url
	/**
		@param eHttpMethod		in :	请求的类型
		@param eFileType		in :	请求返回的数据格式，json或xml
		@param  oQWBlogParam	in :	该请求所带的参数类对象

		@retval   url字符串
	*/
	 std::string GetUrl(std::string strUrl, EHttpMethod eHttpMethod, 
				                CWeiboParam& oParam, std::string& strPost);

	  ///从请求参数中获取post的内容
	 /**
	 @param oQWBlogParam		in :	该请求所带的参数类对象

	 @retval	post内容的字符串
	 */
	 std::string GetPostString(CWeiboParam oParam);

private:	
	/// 获取基本的url，这时url还没有ouath化
	std::string GetBaseUrl(std::string strUrl, CWeiboParam oParam);

	/// ouath化url
	std::string NormalrizeUrl(std::string strUrl, EHttpMethod eHttpMethod, 
										  std::string strCustomKey, std::string strCustomSecrect, 
								          std::string strTokenKey, std::string strTokenSecrect, 
								          std::string& strPost);
private:
	CRequestUrl();
	CRequestUrl(const CRequestUrl& other);
	CRequestUrl& operator=(const CRequestUrl& other);

private:	
	typedef std::map<int, std::string>		MapKey2Url;
	MapKey2Url							m_mapKeyUrl;  ///< 存储请求Key和URL的对应
};
