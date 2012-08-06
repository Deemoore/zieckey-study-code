/** 
@file  
@brief	QWBlogAPI�������ȡ���ݵĽӿ�
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

	
	/** ͬ����������
	    @param  strUrl              in :  ����url
		@param	eHttpMethod			in :  ���������
		@param  oQWBlogParam		in :  �����������Ĳ��������
		@param  strData				out ��ͬ�����ص�����

		@retval		HTTPRESULT_OK:�ɹ�	����:ʧ��
	*/
	HTTP_RESULTCODE SyncRequest(std::string strUrl,  EHttpMethod eHttpMethod,  
							CWeiboParam  oQWBlogParam, std::string & strData);
	


	/** ͬ����������
	    @param strUrl           in : ����url
		@param eRequest			in : ���������
		@param oQWBlogParam		in : �����������Ĳ��������
		@param pCallback		in ���ص�ָ��

		@retval		true:�ɹ�	false:ʧ��
	*/
	bool      AsyncRequest(std::string strUrl, EHttpMethod eHttpMethod,  
							CWeiboParam  oQWBlogParam, VWeiboCallback * pCallback);



	/// http��ɻص�����,  �̳������ʵ�ָú���������ϴ����ؽ����֪ͨ
	/** 
		@param pHttp			in�� CHttp����
		@param eErrorCode		in�� ״̬���룬ȡֵHTTP_RESULTCODE
		@param strData			out���������
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



