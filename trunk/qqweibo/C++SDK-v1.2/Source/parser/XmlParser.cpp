#include "XmlParser.h"
#include "UtilString.h"
#include "WeiboApi.h"


XmlParser::XmlParser()
{
	m_pRoot = NULL;
	m_bReadOnly = false;
	m_bDeleteSelf = false;
}

XmlParser::~XmlParser()
{
	if(m_bDeleteSelf)
	{
		delete m_pRoot;
	}
}

bool XmlParser::IsReadyOnly()
{
	return m_bReadOnly;
}

bool XmlParser::Parse(const char* pName)
{
	if(!pName || m_bReadOnly)
	{
		return false;
	}

	TiXmlDocument  oDoc;
	oDoc.Parse(pName, NULL, TIXML_ENCODING_UTF8);
	if( oDoc.Error())
	{
		return false;
	}

	m_pRoot = new TiXmlElement(*oDoc.RootElement());
	m_bReadOnly = true;
	m_bDeleteSelf = true;
	return true;
}

XmlParser XmlParser::GetChild(const char* pName)
{
	if(!pName || (m_pRoot == NULL))
	{
		return XmlParser();
	}

	TiXmlElement *pChild = GetChildByName(pName);
	return GetReadOnlyReader(pChild);
}

XmlParser XmlParser::GetChild(const int nIndex)
{
	if ((nIndex < 0) || (m_pRoot == NULL))
	{
		return XmlParser();
	}

	TiXmlElement *pChild = GetChildByIndex(nIndex);
	return GetReadOnlyReader(pChild);
}

char* XmlParser::GetString(const char* pName)
{
	if(!pName || (m_pRoot == NULL))
	{
		return NULL;
	}

	TiXmlElement *pChild = GetChildByName(pName);
	if( pChild && pChild->GetText())
	{
		return Util::String::Utf8ToMbcs(pChild->GetText());
	}

	return NULL;
}

char* XmlParser::GetString(const int nIndex)
{
	if((nIndex < 0) || (m_pRoot == NULL))
	{
		return NULL;
	}

	TiXmlElement *pChild = GetChildByIndex(nIndex);
	if( pChild && pChild->GetText())
	{
		return Util::String::Utf8ToMbcs(pChild->GetText());
	}

	return NULL;
}

bool XmlParser::GetBool(const char* pName)
{
	if(!pName || (m_pRoot == NULL))
	{
		return false;
	}

	int nValue = 0;

	TiXmlElement *pChild = GetChildByName(pName);
	if( pChild && pChild->GetText())
	{
		std::string strText;
		strText = Util::String::Utf8ToMbcs(pChild->GetText());
		Util::String::StringToInt(strText.c_str(), nValue);
	}

	return static_cast<bool>(nValue);
}

bool XmlParser::GetBool(const int nIndex)
{
	if((nIndex < 0) || (m_pRoot == NULL))
	{
		return false;
	}

	int nValue = 0;

	TiXmlElement *pChild = GetChildByIndex(nIndex);
	if( pChild && pChild->GetText())
	{
		char*pText;
		pText = Util::String::Utf8ToMbcs(pChild->GetText());
		Util::String::StringToInt(pText, nValue);
		ReleaseData(pText);
	}

	return static_cast<bool>(nValue);
}

int XmlParser::GetInt(const char*pName)
{
	if(!pName || (m_pRoot == NULL))
	{
		return 0;
	}

	int nValue = 0;

	TiXmlElement *pChild = GetChildByName(pName);
	if( pChild && pChild->GetText())
	{
		char* pText;
		pText = Util::String::Utf8ToMbcs(pChild->GetText());
		Util::String::StringToInt(pText, nValue);
		ReleaseData(pText);
	}

	return nValue;
}

int XmlParser::GetInt(const int nIndex)
{
	if((nIndex < 0) || (m_pRoot == NULL))
	{
		return 0;
	}

	int nValue = 0;

	TiXmlElement *pChild = GetChildByIndex(nIndex);
	if( pChild && pChild->GetText())
	{
		char* pText;
		pText = Util::String::Utf8ToMbcs(pChild->GetText());
		Util::String::StringToInt(pText, nValue);
		ReleaseData(pText);
	}

	return nValue;
}

unsigned int XmlParser::GetUint(const char* pName)
{
	if(!pName || (m_pRoot == NULL))
	{
		return 0;
	}

	unsigned int unValue = 0;

	TiXmlElement *pChild = GetChildByName(pName);
	if( pChild && pChild->GetText())
	{
		char* pText;
		pText = Util::String::Utf8ToMbcs(pChild->GetText());
		Util::String::StringToDWord(pText, unValue);
		ReleaseData(pText);
	}

	return unValue;
}

unsigned int XmlParser::GetUint(const int nIndex)
{
	if((nIndex < 0) || (m_pRoot == NULL))
	{
		return 0;
	}

	unsigned int unValue = 0;

	TiXmlElement *pChild = GetChildByIndex(nIndex);
	if( pChild && pChild->GetText())
	{
		char* pText;
		pText = Util::String::Utf8ToMbcs(pChild->GetText());
		Util::String::StringToDWord(pText, unValue);
		ReleaseData(pText);
	}

	return unValue;
}

long long XmlParser::GetUint64(const char* pName)
{
	if(!pName || (m_pRoot == NULL))
	{
		return 0;
	}

	unsigned long long un64Value = 0;

	TiXmlElement *pChild = GetChildByName(pName);
	if( pChild && pChild->GetText())
	{
		char* pText;
		pText = Util::String::Utf8ToMbcs(pChild->GetText());
		Util::String::StringToUnsignedInt64(pText, un64Value);
		ReleaseData(pText);
	}

	return un64Value;
}

long long XmlParser::GetUint64(const int nIndex)
{
	if((nIndex < 0) || (m_pRoot == NULL))
	{
		return 0;
	}

	unsigned long long un64Value = 0;

	TiXmlElement *pChild = GetChildByIndex(nIndex);
	if( pChild && pChild->GetText())
	{
		std::string strText;
		strText = Util::String::Utf8ToMbcs(pChild->GetText());
		Util::String::StringToUnsignedInt64(strText.c_str(), un64Value);
	}

	return un64Value;
}

XmlParser XmlParser::GetReadOnlyReader(TiXmlElement* pRoot)
{
	if (pRoot == NULL)
	{
		return XmlParser();
	}

	XmlParser oReader;
	oReader.m_pRoot = pRoot;
	oReader.m_bReadOnly = true;
	oReader.m_bDeleteSelf = false;

	return oReader;
}

TiXmlElement* XmlParser::GetChildByName(const char* pName)
{
	return m_pRoot->FirstChildElement(pName);
}

TiXmlElement* XmlParser::GetChildByIndex( const int nIndex )
{
	TiXmlElement *pChild = m_pRoot->FirstChildElement();
	int i = 0;
	while((pChild != NULL) && (i < nIndex))
	{
		pChild = pChild->NextSiblingElement();
		++i;
	}

	return pChild;
}