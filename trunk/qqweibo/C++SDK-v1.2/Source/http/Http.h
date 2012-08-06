/** 
@file  
@brief	http下载类
@version	2010-11-19	

*/


#pragma once
#include "HttpProxy.h"
#include <map>
#include "curl/curl.h"
#include "WeiboApi.h"


class  CHttp;

///获得http完成通知需要继承的回调基类
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
	/// 完成函数,  继承类必须实现该函数来获得上传下载结果的通知
	/** 
	@param pOhttp			in:  CHttp对象
	@param eErrorCode		in:  状态代码，取值HTTPRESULT_OK或HTTPRESULT_FAIL
	@param strData			out: 结果数据
	*/	
	virtual  void OnHttpComplete(CHttp * pOhttp, HTTP_RESULTCODE eErrorCode, std::string& strData) = 0;

};




class  CHttp
{
public:
	CHttp();
	~CHttp();	

public:
	/// 同步下载
	/** 
	@param strUrl		in:   下载的url	
	@param strResult	out:  结果数据

	@retval  HTTPRESULT_OK:成功   HTTPRESULT_FAIL:失败 
	*/	
	HTTP_RESULTCODE	SyncDownload(const std::string &strUrl, std::string & strResult);

	/// 异步下载
	/** 
	@param strUrl		in:  下载的url
	@param pCallback	in:  获取回调的指针
	*/	
	bool	AsyncDownload(const std::string &strUrl, VHttpCallback * pCallback);

	/// 同步上传
	/** 
	@param strUrl		in:   上传的url
	@param strData		in:   上传的数据
	@param strResult	out:  结果数据

	@retval  HTTPRESULT_OK:成功   HTTPRESULT_FAIL:失败 
	*/	
	HTTP_RESULTCODE	SyncUpload(const std::string &strUrl, const std::string &strData, std::string & strResult);

	/// 异步上传
	/** 
	@param strUrl		in:	上传的url
	@param strData		in:	上传的数据
	@param pCallback	in:	获取回调的指针
	*/	
	bool	AsyncUpload(const std::string &strUrl, const std::string &strData, VHttpCallback * pCallback);

	/// 同步上传，采用enctype="multipart/form-data"
	/** 
	@param strUrl		in:	上传的url
	@param mapData		in:	上传的字段内容
	@param mapFile		in:	上传的文件名
	@param strResult	out: 结果数据

	@retval  HTTPRESULT_OK: 成功   HTTPRESULT_FAIL: 失败 
	*/	
	HTTP_RESULTCODE	SyncUploadFormData(const std::string &strUrl,  const std::map<std::string,std::string> & mapData,
																		const std::map<std::string,std::string> & mapFile, std::string & strResult);

	/// 异步上传，采用enctype="multipart/form-data"
	/** 
	@param strUrl		in:	上传的url
	@param strData		in:	上传的数据
	@param pCallback	in:	获取回调的指针
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
	std::string		m_strData;	 ///<  Post包体数据

	typedef	std::map<std::string, std::string>    CMapKeyValue;	
	CMapKeyValue	m_mapPostFile;   ///<  以form-data格式上传的文件或图片
	CMapKeyValue	m_mapPostData;   ///<  以form-data格式上传的post数据

	
	char *			m_pchResultData; ///<  上传或下载的结果存放
	unsigned long	m_uLength;		 ///<  上传或下载的结果存放的BUF的长度
	unsigned long	m_uWritePos;	 ///<  上传或下载的结果数据buf的当前书写位置

};
