#include "Request.h"
#include "Url/RequestUrl.h"
#include <assert.h>

CRequest::CRequest()
{

}

CRequest::~CRequest()
{

}

CRequest* CRequest::GetInstance()
{
	static CRequest oWeibo;
	return &oWeibo;
}

HTTP_RESULTCODE CRequest::SyncRequest(std::string strUrl, EHttpMethod eHttpMethod,  CWeiboParam oParam, std::string & strData )
{
	HTTP_RESULTCODE eResultCode = HTTPRESULT_FAIL;	
	std::string strPost;
    
	std::string strRetData;
	 
	std::string strOauthUrl = CRequestUrl::GetInstance()->GetUrl(strUrl, eHttpMethod, oParam, strPost);
	CHttp oHttp;

	if (eHttpMethod == EHttpMethod_Get)
	{
		if (!strPost.empty())
		{
			strOauthUrl += "?";
			strOauthUrl += strPost;
		}
		eResultCode = oHttp.SyncDownload(strOauthUrl,  strRetData);
	}
	else if (eHttpMethod == EHttpMethod_Post)
	{
		if(oParam.GetPicParamMap().empty())
		{
			eResultCode = oHttp.SyncUpload(strOauthUrl, strPost, strRetData);
		}
		else
		{
			if (!strPost.empty())
			{
				strOauthUrl += "?";
				strOauthUrl += strPost;
			}
		    eResultCode = oHttp.SyncUploadFormData(strOauthUrl, oParam.GetParamMap(), oParam.GetPicParamMap(), strRetData);
		}
	}
	
	strData = strRetData;
	std::string c_strFormat = TXWeibo::Param::strFormat;
	char* pFormat = oParam.GetParam(c_strFormat.c_str()); 
	std::string strFormat;
	if(pFormat != NULL)
	{
		strFormat.append(pFormat);
	}
	ReleaseData(pFormat);
	if(strFormat == TXWeibo::Param::strJson || strFormat == TXWeibo::Param::strXml)//只decode指定格式
	{
		char* pUrlDecode;
		pUrlDecode = Util::String::FormUrlDecode(strRetData.c_str());
		strData = pUrlDecode;
		ReleaseData(pUrlDecode);
	}

	return eResultCode;
}

bool CRequest::AsyncRequest(std::string strUrl, EHttpMethod eHttpMethod,  CWeiboParam oParam, VWeiboCallback * pCallback )
{
	std::string strResult;
	HTTP_RESULTCODE eResultCode = HTTPRESULT_FAIL;
	std::string strPost;
	bool bResult = false;

	std::string strOauthUrl = CRequestUrl::GetInstance()->GetUrl(strUrl, eHttpMethod, oParam, strPost);

	CHttp* pHttp = new CHttp;
	if (eHttpMethod == EHttpMethod_Get)
	{
		if (!strPost.empty())
		{
			strOauthUrl += "?";
			strOauthUrl += strPost;
		}
		bResult = pHttp->AsyncDownload(strOauthUrl, this);
	}
	else if (eHttpMethod == EHttpMethod_Post)
	{
		if(oParam.GetPicParamMap().empty())
		{
			bResult = pHttp->AsyncUpload(strOauthUrl, strPost, this);
		}
		else
		{
			if (!strPost.empty())
			{
				strOauthUrl += "?";
				strOauthUrl += strPost;
			}

			bResult = pHttp->AsyncUploadFormData(strOauthUrl, oParam.GetParamMap(), oParam.GetPicParamMap(), this);

		}		
	}
	else
	{
		bResult = false;
	}

	if (bResult)
	{
		tagWeiboRequest oRequest;
		oRequest.strUrl = strUrl;
		oRequest.oParam = oParam;
		oRequest.pCallback = pCallback;

		m_mapHttp2Request[pHttp] = oRequest;
	}

	return bResult;
}

void CRequest::OnHttpComplete( CHttp *pHttp, HTTP_RESULTCODE eErrorCode, std::string& strData )
{
	if (pHttp == NULL)
	{
		assert(pHttp);
		return;
	}

	MapHttp2Request::iterator it = m_mapHttp2Request.find(pHttp);
	if (it == m_mapHttp2Request.end())
	{
		return;
	}

	tagWeiboRequest& oRequest = it->second;
	if (oRequest.pCallback == NULL)
	{
		assert(oRequest.pCallback);
		m_mapHttp2Request.erase(pHttp);
		delete pHttp;
		pHttp = NULL;
		return;
	}

	std::string strDecode	= strData;
	std::string c_strFormat = TXWeibo::Param::strFormat;
	char* pFormat = oRequest.oParam.GetParam(c_strFormat.c_str()); 
	std::string strFormat;
	if(pFormat != NULL)
	{
		strFormat.append(pFormat);
	}
	ReleaseData(pFormat);
	if(strFormat ==  TXWeibo::Param::strJson || strFormat ==  TXWeibo::Param::strXml)//只decode指定格式
	{
		char* pUrlDecode;
		pUrlDecode = Util::String::FormUrlDecode(strData.c_str());
		strDecode = pUrlDecode;
		ReleaseData(pUrlDecode);
	}
	oRequest.pCallback->OnRequestComplete(eErrorCode,oRequest.strUrl.c_str(), oRequest.oParam, strDecode.c_str(),strDecode.length());

	m_mapHttp2Request.erase(pHttp);
	delete pHttp;
	pHttp = NULL;
}