#include "WeiboParam.h"
#include <assert.h>
#include "WeiboApi.h"
using namespace std;

CWeiboParam::CWeiboParam( void )
{
	m_pmapParam = new MapKey2Value;
	m_pmapParam->clear();
	m_pmapPicParam = new MapKey2Value;
	m_pmapPicParam->clear();
}

CWeiboParam::CWeiboParam( const CWeiboParam& v )
{
	m_pmapParam = new MapKey2Value;
	m_pmapPicParam = new MapKey2Value;
	MapKey2Value::const_iterator it = v.m_pmapParam->begin();
	for (;it != v.m_pmapParam->end();it++)
	{
		(*m_pmapParam)[it->first] = it->second;
	}
	it = v.m_pmapPicParam->begin();
	for (;it != v.m_pmapPicParam->end();it++)
	{
		(*m_pmapPicParam)[it->first] = it->second;
	}

}
CWeiboParam::~CWeiboParam( void )
{
	//Clear();

	if(m_pmapParam)
	{
		delete m_pmapParam;
		m_pmapParam = NULL;
	}

	if(m_pmapPicParam)
	{
		delete m_pmapPicParam;
		m_pmapPicParam = NULL;
	}

}

void CWeiboParam::AddParam( const char* pKey, const char* pValue )
{
	if(pKey == NULL || pValue == NULL|| m_pmapParam == NULL)
	{
		assert(0);
		return ;
    }

	char *pCode = Util::String::FormUrlEncode(pValue);		
	char* pUtf8	= Util::String::MbcsToUtf8(pCode);	
	string strKey;
	strKey.append(pKey);
	string strValue;
	strValue.append(pUtf8);
	m_pmapParam->insert(make_pair(strKey,strValue));
	ReleaseData(pUtf8);
	ReleaseData(pCode);
}



char* CWeiboParam::GetParam( const char* pKey )
{
	if( !m_pmapParam || !pKey)
	{
		assert(0);
	    return NULL;
	}

	MapKey2Value::iterator it = m_pmapParam->find(string(pKey));
	if (it == (*m_pmapParam).end())
	{
		return NULL;
	}

	char * pRetBuffer = new char[it->second.length()+1];
	strncpy_s(pRetBuffer,it->second.length()+1,it->second.c_str(),it->second.length());
	return pRetBuffer;
}

void CWeiboParam::AddPicNameParam( const char*pKey, const char* pValue )
{
	if(!m_pmapPicParam || !pKey || !pValue)
	{
		assert(0);
	    return ;
	}

	(*m_pmapPicParam)[string(pKey)] = string(pValue);
}

char* CWeiboParam::GetPicNameParam( const char* pKey )
{
	if(!m_pmapPicParam || !pKey)
	{
		assert(0);
	    return NULL;
	}

	MapKey2Value::iterator it = m_pmapPicParam->find(string(pKey));
	if (it == m_pmapPicParam->end())
	{
		return NULL;
	}

	char * pRetBuffer = new char[it->second.length() + 1];
	strncpy_s(pRetBuffer,it->second.length()+1,it->second.c_str(),it->second.length());
	return pRetBuffer;
}

void CWeiboParam::GetAndRemoveKey( string& strCustomKey, string& strCustomSecrect, string& strTokenKey, string& strTokenSecrect )
{
	if(!m_pmapParam)
	{
		assert(0);
	    return;
	}

	std::string c_strCustomKey		= TXWeibo::Param::strCustomKey;
	std::string c_strCustomSecrect	= TXWeibo::Param::strCustomSecrect;
	std::string c_strTokenKey		= TXWeibo::Param::strTokenKey;
	std::string c_strTokenSecrect	= TXWeibo::Param::strTokenSecrect;

	char *pCustomKey	 = GetParam(c_strCustomKey.c_str());
	char *pCustomSecrect = GetParam(c_strCustomSecrect.c_str());
	char *pTokenKey		 = GetParam(c_strTokenKey.c_str());
	char *pTokenSecrect  = GetParam(c_strTokenSecrect.c_str());

	if(pCustomKey)
	{
		strCustomKey = pCustomKey;
	}
	if(pCustomSecrect)
	{
		strCustomSecrect = pCustomSecrect;
	}
	if(pTokenKey)
	{
		strTokenKey = pTokenKey;
	}
	if(pTokenSecrect)
	{
		strTokenSecrect = pTokenSecrect;
	}

	ReleaseData(pCustomKey);
	ReleaseData(pCustomSecrect);
	ReleaseData(pTokenKey);
	ReleaseData(pTokenSecrect);

	m_pmapParam->erase(TXWeibo::Param::strCustomKey);
	m_pmapParam->erase(TXWeibo::Param::strCustomSecrect);
	m_pmapParam->erase(TXWeibo::Param::strTokenKey);
	m_pmapParam->erase(TXWeibo::Param::strTokenSecrect);
}

char* CWeiboParam::GetUrlParamString()
{
	if(!m_pmapParam)
	{
		assert(0);
        return NULL;
	}

	std::string strResult;
	for (MapKey2Value::iterator it = m_pmapParam->begin(); it != m_pmapParam->end(); ++it)
	{
		if (it != m_pmapParam->begin())
		{
			strResult += "&";
		}

		strResult += it->first;
		strResult += "=";
		strResult += it->second;
	}

	char * pRetBuffer = new char[strResult.length() + 1];
	strncpy_s(pRetBuffer,strResult.length()+1,strResult.c_str(),strResult.length());
	return pRetBuffer;
}

void CWeiboParam::Clear()
{
	if(!m_pmapParam || !m_pmapPicParam)
	{
		assert(0);
		return;
	}

	m_pmapParam->clear();
	m_pmapPicParam->clear();
}

CWeiboParam::MapKey2Value& CWeiboParam::GetParamMap()
{
	if(!m_pmapParam)
	{
		assert(0);
	}
	return *m_pmapParam;
}

CWeiboParam::MapKey2Value& CWeiboParam::GetPicParamMap()
{
	if(!m_pmapPicParam)
	{
		assert(0);
	}
	return *m_pmapPicParam;
}

CWeiboParam& CWeiboParam::operator=( const CWeiboParam& v )
{
	MapKey2Value::const_iterator it = v.m_pmapParam->begin();
	for (;it != v.m_pmapParam->end(); it++)
	{
		(*m_pmapParam)[it->first] = it->second;
	}
	it = v.m_pmapPicParam->begin();
	for (;it != v.m_pmapPicParam->end(); it++)
	{
		(*m_pmapPicParam)[it->first] = it->second;
	}

	return *this;
}