/** 
@file  
@brief	http������
@version	2010-11-19	

*/


#pragma once
#include "HttpProxy.h"
#include <map>
#include "curl/curl.h"
#include "WeiboApi.h"


class  CHttp;

///���http���֪ͨ��Ҫ�̳еĻص�����
class   VHttpCallback
{
public:
	VHttpCallback(){}
	virtual ~VHttpCallback()
	{
		CHttpProxy *pUIProxy = CHttpProxy::GetInstance();
		if( pUIProxy )
		{
			pUIProxy->RemoveCallback(this);
		}
	}

public:
	/// ��ɺ���,  �̳������ʵ�ָú���������ϴ����ؽ����֪ͨ
	/** 
	@param pOhttp			in:  CHttp����
	@param eErrorCode		in:  ״̬���룬ȡֵHTTPRESULT_OK��HTTPRESULT_FAIL
	@param strData			out: �������
	*/	
	virtual  void OnHttpComplete(CHttp * pOhttp, HTTP_RESULTCODE eErrorCode, std::string& strData) = 0;

};




class  CHttp
{
public:
	CHttp();
	~CHttp();	

public:
	/// ͬ������
	/** 
	@param strUrl		in:   ���ص�url	
	@param strResult	out:  �������

	@retval  HTTPRESULT_OK:�ɹ�   HTTPRESULT_FAIL:ʧ�� 
	*/	
	HTTP_RESULTCODE	SyncDownload(const std::string &strUrl, std::string & strResult);

	/// �첽����
	/** 
	@param strUrl		in:  ���ص�url
	@param pCallback	in:  ��ȡ�ص���ָ��
	*/	
	bool	AsyncDownload(const std::string &strUrl, VHttpCallback * pCallback);

	/// ͬ���ϴ�
	/** 
	@param strUrl		in:   �ϴ���url
	@param strData		in:   �ϴ�������
	@param strResult	out:  �������

	@retval  HTTPRESULT_OK:�ɹ�   HTTPRESULT_FAIL:ʧ�� 
	*/	
	HTTP_RESULTCODE	SyncUpload(const std::string &strUrl, const std::string &strData, std::string & strResult);

	/// �첽�ϴ�
	/** 
	@param strUrl		in:	�ϴ���url
	@param strData		in:	�ϴ�������
	@param pCallback	in:	��ȡ�ص���ָ��
	*/	
	bool	AsyncUpload(const std::string &strUrl, const std::string &strData, VHttpCallback * pCallback);

	/// ͬ���ϴ�������enctype="multipart/form-data"
	/** 
	@param strUrl		in:	�ϴ���url
	@param mapData		in:	�ϴ����ֶ�����
	@param mapFile		in:	�ϴ����ļ���
	@param strResult	out: �������

	@retval  HTTPRESULT_OK: �ɹ�   HTTPRESULT_FAIL: ʧ�� 
	*/	
	HTTP_RESULTCODE	SyncUploadFormData(const std::string &strUrl,  const std::map<std::string,std::string> & mapData,
																		const std::map<std::string,std::string> & mapFile, std::string & strResult);

	/// �첽�ϴ�������enctype="multipart/form-data"
	/** 
	@param strUrl		in:	�ϴ���url
	@param strData		in:	�ϴ�������
	@param pCallback	in:	��ȡ�ص���ָ��
	*/	
	bool	  AsyncUploadFormData(const std::string & strUrl,const std::map<std::string,std::string> & mapData, 
												const std::map<std::string,std::string> & mapFile, VHttpCallback * pCallback);


public:
	static    size_t	ProcessResult( void* data, size_t size, size_t nmemb, void *pHttp );


public:
	void			Reset();

	CURLcode		DoHttpGet();
	CURLcode		DoHttpPost();	
	CURLcode		DoHttpPostFormData();	
	

	bool			WriteResultData(char* pchData, unsigned long uLength);
	bool			GetResultData(std::string & strData);


public:
	bool			m_bRunning;
	
private:
	std::string		m_strUrl;   
	std::string		m_strData;	 ///<  Post��������

	typedef	std::map<std::string, std::string>    CMapKeyValue;	
	CMapKeyValue	m_mapPostFile;   ///<  ��form-data��ʽ�ϴ����ļ���ͼƬ
	CMapKeyValue	m_mapPostData;   ///<  ��form-data��ʽ�ϴ���post����

	
	char *			m_pchResultData; ///<  �ϴ������صĽ�����
	unsigned long	m_uLength;		 ///<  �ϴ������صĽ����ŵ�BUF�ĳ���
	unsigned long	m_uWritePos;	 ///<  �ϴ������صĽ������buf�ĵ�ǰ��дλ��

};
