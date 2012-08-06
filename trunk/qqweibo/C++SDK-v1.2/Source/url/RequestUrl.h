/** 
@file  
@brief		�õ���Ӧ�����URL
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

	 /// ��ȡ����CRequestUrl����
	 static CRequestUrl* GetInstance(); 

     ///�õ���Ӧ�����url
	/**
		@param eHttpMethod		in :	���������
		@param eFileType		in :	���󷵻ص����ݸ�ʽ��json��xml
		@param  oQWBlogParam	in :	�����������Ĳ��������

		@retval   url�ַ���
	*/
	 std::string GetUrl(std::string strUrl, EHttpMethod eHttpMethod, 
				                CWeiboParam& oParam, std::string& strPost);

	  ///����������л�ȡpost������
	 /**
	 @param oQWBlogParam		in :	�����������Ĳ��������

	 @retval	post���ݵ��ַ���
	 */
	 std::string GetPostString(CWeiboParam oParam);

private:	
	/// ��ȡ������url����ʱurl��û��ouath��
	std::string GetBaseUrl(std::string strUrl, CWeiboParam oParam);

	/// ouath��url
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
	MapKey2Url							m_mapKeyUrl;  ///< �洢����Key��URL�Ķ�Ӧ
};
