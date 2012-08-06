#include <process.h>
#include "Http.h"
#include "HttpProxy.h"
#include "UtilString.h"
#include <assert.h>

#define  RESULTDATA_INCREASE_LEN		(10*1024)       ///<  ����http�����������ÿ�����ݿ�Ĵ�С
#define  MAX_RECVDATA_LEN				102400000     ///<  ����ÿ��http���������������ڴ�


HTTP_RESULTCODE GetErrorCode( CURLcode eUrlError )
{
	HTTP_RESULTCODE eErrorCode;
	switch(eUrlError)
	{
	case CURLE_OK:
		eErrorCode = HTTPRESULT_OK;
		break;
	case CURLE_COULDNT_CONNECT:
		eErrorCode = HTTPRESULT_CANTCONNECT;
		break;
	case CURLE_OPERATION_TIMEDOUT:
		eErrorCode = HTTPRESULT_TIMEOUT;
		break;
	case CURLE_HTTP_RETURNED_ERROR:
		eErrorCode = HTTPRESULT_ERROR;
		break;
	case CURLE_COULDNT_RESOLVE_HOST:
		eErrorCode = HTTPRESULT_CANTRESOLVE;
		break;
	default :
		eErrorCode = HTTPRESULT_FAIL;
		break;
	}

	return eErrorCode;
}

CHttp::CHttp()
{
	m_pchResultData		= NULL;
	m_uLength			= 0;
	m_uWritePos			= 0;
	m_bRunning			= false;		
}

CHttp::~CHttp()
{
	CHttpProxy::GetInstance()->RemoveCallback((unsigned long)this);
	Reset();
}

void CHttp::Reset()
{
	m_strUrl.empty();
	m_strData.empty();

	if( m_pchResultData)
	{
		delete []m_pchResultData;
		m_pchResultData = NULL;	
	}	
	m_uLength		= 0;
	m_uWritePos		= 0;
	m_mapPostData.clear();
	m_mapPostFile.clear();
}


/*****************************************************************
 *          ͬ �� GET          *
 *****************************************************************/
HTTP_RESULTCODE	CHttp::SyncDownload(const std::string &strUrl, std::string & strResult)
{
	if (strUrl.empty())
	{
		return HTTPRESULT_FAIL;
	}

	if( m_bRunning )
	{
		return HTTPRESULT_FAIL;
	}

	m_bRunning	= true;
	Reset();	
	m_strUrl = strUrl;

	CURLcode eErrorCode = DoHttpGet();
	bool  bResult = GetResultData(strResult);
	m_bRunning	= false;

	if (bResult && CURLE_OK == eErrorCode)
	{
		return HTTPRESULT_OK;
	}	

	return GetErrorCode(eErrorCode);
}

/********************************************************************
 *         ͬ �� POST  ����Ĭ��Content-type: application/x-www-form-urlencoded         *
 ********************************************************************/
HTTP_RESULTCODE	CHttp::SyncUpload(const std::string & strUrl, const std::string & strData, std::string & strResult)
{
	if (strUrl.empty())
	{
		return HTTPRESULT_FAIL;
	}

	if( m_bRunning )
	{
		return HTTPRESULT_FAIL;
	}

	m_bRunning  = true;
	Reset();
	m_strUrl = strUrl;
	m_strData = strData;

	CURLcode eErrorCode= DoHttpPost();
	std::string strTemp;
	bool  bResult = GetResultData(strResult);
	
	m_bRunning  = false;

	if(bResult  &&  CURLE_OK==eErrorCode )
	{
		return HTTPRESULT_OK;
	}

	return GetErrorCode(eErrorCode);
}

/********************************************************************
 *         ͬ �� POST  ��Content-type: multipart/form-data            *
 *********************************************************************/
HTTP_RESULTCODE	CHttp::SyncUploadFormData(const std::string & strUrl, const std::map<std::string,std::string> & mapData, const std::map<std::string,std::string> & mapFile, std::string & strResult)
{
	if (strUrl.empty())
	{
		return HTTPRESULT_FAIL;
	}

	if( m_bRunning )
	{
		return HTTPRESULT_FAIL;
	}

	m_bRunning  = true;
	Reset();

	m_strUrl			  = strUrl;
	m_mapPostData =  mapData;
	m_mapPostFile	  =  mapFile;

	CURLcode eErrorCode = DoHttpPostFormData();
	std::string strTemp;
	bool  bResult = GetResultData(strResult);
	
	m_bRunning  = false;

	if (bResult && eErrorCode == CURLE_OK)
	{
		return HTTPRESULT_OK;
	}

	return GetErrorCode(eErrorCode);
}


/********************************************************************
 *           Download  �߳����к���                    *
 ********************************************************************/
UINT __stdcall thread_run_download(LPVOID lpParam)
{
	CHttp * oHttp= (CHttp *) lpParam;
	CURLcode eErrorCode = oHttp->DoHttpGet();	

	HTTP_RESULTCODE eHttpError = GetErrorCode(eErrorCode);

	::PostMessage(CHttpProxy::GetInstance()->GethWnd(), MSG_HTTP_COMPLETE, (WPARAM)oHttp,(LPARAM)eHttpError);

	return 0;
}

/********************************************************************
 *          upload  �߳����к���              *
 ********************************************************************/
UINT __stdcall  thread_run_upload(LPVOID lpParam)
{
	CHttp * pHttp= (CHttp *) lpParam;
	CURLcode eErrorCode = pHttp->DoHttpPost();

     HTTP_RESULTCODE eHttpError = GetErrorCode(eErrorCode);	

	::PostMessage(CHttpProxy::GetInstance()->GethWnd(), MSG_HTTP_COMPLETE, (WPARAM)pHttp,(LPARAM)eHttpError);
	
	return 0;
}

/********************************************************************
 *           upload formdata �߳����к���         *
 ********************************************************************/
UINT __stdcall  thread_run_uploadformdata(LPVOID lpParam)
{
	CHttp * pHttp= (CHttp *) lpParam;
	CURLcode eErrorCode = pHttp->DoHttpPostFormData();

    HTTP_RESULTCODE eHttpError = GetErrorCode(eErrorCode);	

	::PostMessage(CHttpProxy::GetInstance()->GethWnd(), MSG_HTTP_COMPLETE, (WPARAM)pHttp,(LPARAM)eHttpError);

	return 0;
}

/********************************************************************
 *              �첽 GET             *
 ********************************************************************/
bool CHttp::AsyncDownload(const std::string &strUrl, VHttpCallback * pCallback)
{
	if (NULL == pCallback || strUrl.empty())
	{
		assert(0);
		return false;
	}

	if( m_bRunning )
	{
		return false;
	}

	m_bRunning = true;
	Reset();	
	m_strUrl = strUrl;	

	CHttpProxy * pHttproxy = CHttpProxy::GetInstance();
	if (pHttproxy)
	{
		pHttproxy->AddCallback((unsigned long)this,	pCallback);	
	}	

	UINT dwThreadID = 0;
	int nVal = _beginthreadex(NULL, 0, thread_run_download, (void *)this, 0, &dwThreadID);
	if (nVal <= 0)	
	{
		return false;
	}

	return true;
}

/********************************************************************
 *           �첽POST,  ��Ĭ��Content-type: application/x-www-form-urlencoded              *
 ********************************************************************/
bool CHttp::AsyncUpload(const std::string& strUrl, const std::string& strData, VHttpCallback * pCallback)
{
	if (NULL == pCallback || strUrl.empty())
	{
		assert(0);
		return false;
	}

	if( m_bRunning )
	{
		return false;
	}

	m_bRunning = true;
	Reset();	
	m_strUrl = strUrl;
	m_strData = strData;	
	CHttpProxy * pHttproxy = CHttpProxy::GetInstance();
	if (pHttproxy)
	{
		pHttproxy->AddCallback((unsigned long)this,	pCallback);	
	}	

	UINT dwThreadID = 0;
	int nVal = _beginthreadex(NULL, 0, thread_run_upload, (void *)this, 0, &dwThreadID);
	if (nVal <= 0)	
	{
		return false;
	}
	return true;
}

/********************************************************************
 *           �첽POST ��Content-type: multipart/form-data             *
 ********************************************************************/
bool CHttp::AsyncUploadFormData(const std::string &strUrl,const std::map<std::string,std::string> & mapData, 
																	const std::map<std::string,std::string> & mapFile, VHttpCallback * pCallback)
{
	if (NULL == pCallback || strUrl.empty())
	{
		assert(0);
		return false;
	}

	if( m_bRunning )
	{
		return false;
	}

	m_bRunning = true;
	Reset();	

	m_strUrl = strUrl;
	m_mapPostData = mapData;	
	m_mapPostFile = mapFile;
	CHttpProxy * pHttproxy = CHttpProxy::GetInstance();
	if (pHttproxy)
	{
		pHttproxy->AddCallback((unsigned long)this,	pCallback);	
	}	

	UINT dwThreadID = 0;
	int nVal = _beginthreadex(NULL, 0, thread_run_uploadformdata, (void *)this, 0, &dwThreadID);
	if (nVal <= 0)	
	{
		return false;
	}
	
	return true;
}


/********************************************************************
 *           Get     Run              *
 ********************************************************************/
CURLcode CHttp::DoHttpGet()
{	
	CURL *curl;
	curl = curl_easy_init();	

	curl_version_info_data * vinfo = curl_version_info( CURLVERSION_NOW ); 

	if(curl) 
	{
		curl_easy_setopt( curl, CURLOPT_HTTPGET, 1 );
		curl_easy_setopt(curl, CURLOPT_URL, m_strUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

		/// ����ssl���������ò��ܳɹ�
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);

		/// ֧���ض���
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, TRUE);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CHttp::ProcessResult);
		//curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20);
	}

	CURLcode eErrorCode = curl_easy_perform(curl);
	curl_easy_cleanup(curl);	

	return eErrorCode;	
}

/********************************************************************
 *       Post      Run                *
 ********************************************************************/
CURLcode CHttp::DoHttpPost()
{
	CURL *curl;
	curl = curl_easy_init();

	if(curl) 
	{
		curl_easy_setopt(curl, CURLOPT_POST, 1 );
		curl_easy_setopt(curl, CURLOPT_URL, m_strUrl.c_str());
	
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, m_strData.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, m_strData.length());

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CHttp::ProcessResult);
		//curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60);
	}

	CURLcode urlCode = curl_easy_perform(curl);
	curl_easy_cleanup(curl);	

	return urlCode;
}

/********************************************************************
 *           Post Formdata  Run                 *
 ********************************************************************/
CURLcode CHttp::DoHttpPostFormData()
{
	CURL *curl = curl_easy_init();

	/// ʹ��multi-parts form post	
	curl_httppost *post = NULL;
	curl_httppost *last = NULL;	

	/// �ı�����
	CMapKeyValue::iterator it1 = m_mapPostData.begin();	
	while (it1 != m_mapPostData.end())
	{		
		curl_formadd(&post, &last, CURLFORM_COPYNAME, (it1->first).c_str(), CURLFORM_COPYCONTENTS,(it1->second).c_str(), CURLFORM_END);
		it1++;
	}

	///  �ļ�����
	CMapKeyValue::iterator it2 = m_mapPostFile.begin();
	while (it2 != m_mapPostFile.end())
	{
		curl_formadd(&post, &last, CURLFORM_COPYNAME,  (it2->first).c_str(), CURLFORM_FILE, (it2->second).c_str(), CURLFORM_END);
		it2++;
	}

	curl_easy_setopt(curl, CURLOPT_URL, m_strUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CHttp::ProcessResult);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

	CURLcode eErrorCode = curl_easy_perform(curl);

	curl_formfree(post);
	curl_easy_cleanup(curl);	
	return eErrorCode;
}




/********************************************************************
 *              http ���лذ�����         *
 ********************************************************************/
size_t CHttp::ProcessResult( void* data, size_t size, size_t nmemb, void *pHttp )
{
	if (NULL == pHttp)
	{
		return 0;
	}

	CHttp * oHttp = (CHttp *)pHttp;
	oHttp->WriteResultData((char *)data,   size * nmemb);	
	return  size * nmemb;
}

/********************************************************************
 *             ����ذ�����     *
 ********************************************************************/
bool CHttp::WriteResultData(char* pchData, unsigned long  uLength)
{
	if( NULL == pchData || 0 == uLength )
	{
		return false;
	}

	if( NULL == m_pchResultData )
	{
		m_uLength	 = RESULTDATA_INCREASE_LEN;
		m_uWritePos = 0;
		m_pchResultData = new char[RESULTDATA_INCREASE_LEN];
	}

	/// �����ţ����ƶ�һ�£�����һ�½�����
	if( m_uWritePos + uLength > m_uLength )
	{
		if( m_uLength + RESULTDATA_INCREASE_LEN > MAX_RECVDATA_LEN )
		{
			return false;
		}

		char* pTmpData = new char[m_uLength+RESULTDATA_INCREASE_LEN];

		if( NULL == pTmpData )
		{
			return false;
		}

		memcpy(pTmpData,m_pchResultData,m_uLength);
		delete []m_pchResultData;
		m_pchResultData = pTmpData;
		m_uLength = m_uLength+RESULTDATA_INCREASE_LEN;
	}

	if( m_uWritePos + uLength > m_uLength )
	{
		/// ������,������һ����ô��
		return false;
	}

	/// Copy���µ�����
	memcpy( m_pchResultData + m_uWritePos ,pchData,uLength);
	m_uWritePos += uLength;

	return true;
}

/********************************************************************
 *           ȡ����ǰhttp�����б���Ļذ�����        *
 ********************************************************************/
bool CHttp::GetResultData(std::string & strData)
{	
	if( m_pchResultData && m_uWritePos )
	{
		strData.clear();
		strData.append(m_pchResultData,m_uWritePos);

		return true;
	}

	return false;
}

