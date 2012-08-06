#include "RequestUrl.h"
#include "Request.h"
#include "url/Oauth/oauth.h"
#include "url/Oauth/oauth.c"
#include "url/Oauth/hash.c"
#include "url/Oauth/xmalloc.c"

CRequestUrl::CRequestUrl(void)
{
}

CRequestUrl::~CRequestUrl(void)
{
}

CRequestUrl* CRequestUrl::GetInstance()
{
	static CRequestUrl oUrlMgr;
	return &oUrlMgr;
}

std::string CRequestUrl::GetUrl(std::string strUrl, EHttpMethod eHttpMethod, CWeiboParam& oParam, std::string& strPost)
{
	std::string strCustomKey;
	std::string strCustomSecrect;
	std::string strTokenKey;
	std::string strTokenSecrect;

	oParam.GetAndRemoveKey(strCustomKey, strCustomSecrect, strTokenKey, strTokenSecrect);

	std::string strBaseUrl = GetBaseUrl(strUrl, oParam);

	std::string strNormalize =  NormalrizeUrl(strBaseUrl, eHttpMethod, strCustomKey, strCustomSecrect, strTokenKey, strTokenSecrect, strPost);

	return strNormalize;
}

std::string CRequestUrl::GetPostString(CWeiboParam oParam)
{
	std::string strParam; 
	char* pUrlParam = oParam.GetUrlParamString();
	if(pUrlParam)
	{
		strParam = pUrlParam;
		ReleaseData(pUrlParam);
	}
	return strParam;
}

std::string CRequestUrl::GetBaseUrl(std::string strUrl, CWeiboParam oParam)
{
	std::string strBaseUrl = strUrl;

	char* pUrlParam = oParam.GetUrlParamString();
	if (pUrlParam)
	{
		strBaseUrl += "?";
		strBaseUrl += pUrlParam;
		ReleaseData(pUrlParam);
	}

	return strBaseUrl;
}

std::string CRequestUrl::NormalrizeUrl( std::string strUrl, EHttpMethod eHttpMethod, std::string strCustomKey,
										std::string strCustomSecrect, std::string strTokenKey, std::string strTokenSecrect, std::string& strPost )
{
	//char* pcBuf = new char[1024*10];
	char *pcBuf = NULL;
	char* pCustomKey = NULL;
	char* pCustomSecrect = NULL;
	char* pTokenKey = NULL;
	char* pTokenSecrect = NULL;

	if (!strCustomKey.empty())
	{
		pCustomKey = (char*)strCustomKey.c_str();
	}

	if (!strCustomSecrect.empty())
	{
		pCustomSecrect = (char*)strCustomSecrect.c_str();
	}

	if (!strTokenKey.empty())
	{
		pTokenKey = (char*)strTokenKey.c_str();
	}

	if (!strTokenSecrect.empty())
	{
		pTokenSecrect = (char*)strTokenSecrect.c_str();
	}	

	std::string strHttpMethod;

	if(eHttpMethod == EHttpMethod_Get)
	{
		strHttpMethod = c_strHttpGet;
	}
	else
	{
		strHttpMethod = c_strHttpPost;
	}

 	std::string strNormarizeUrl = oauth_sign_url2(strUrl.c_str(), (char**)&pcBuf, OA_HMAC, strHttpMethod.c_str(), 
		pCustomKey, pCustomSecrect, pTokenKey, pTokenSecrect);

	strPost = pcBuf;
	delete[] pcBuf;

	return strNormarizeUrl;
}