#include "UtilString.h"
#include <Windows.h>
#include <assert.h>
#include "WeiboApi.h"


wchar_t* Util::String::Utf8ToUnicode(const char* pUtf8)
{
	assert(pUtf8);
	int nChar = MultiByteToWideChar(CP_UTF8, 0, pUtf8, -1, NULL, 0);

	int nSize = nChar*sizeof(wchar_t) + 1;
	wchar_t* pwchBuffer = new wchar_t[nSize];

	nChar = MultiByteToWideChar(CP_UTF8, 0, pUtf8, -1, pwchBuffer, nSize);
	if(nChar == 0)
	{
		delete []pwchBuffer;
		return NULL;
	}

	pwchBuffer[nChar] = 0;
	return pwchBuffer;
}


char* Util::String::UnicodeToUtf8(const wchar_t* pUnicode)
{
	assert(pUnicode);
	int nChar = WideCharToMultiByte(CP_UTF8, 0, pUnicode, -1, 0, 0, 0, 0);

	int nSize = nChar*sizeof(char) + 1;
	char* pchBuffer = new char[nSize];
	
	nChar = WideCharToMultiByte(CP_UTF8, 0, pUnicode, -1, pchBuffer, nSize, 0, 0);
	if( nChar == 0 )
	{
		delete[] pchBuffer;
		return NULL;
	}

	pchBuffer[nChar]= 0;
	return pchBuffer;
}

wchar_t* Util::String::MbcsToUnicode(const char* pMbcs)
{
	int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
	int nChar = MultiByteToWideChar(codepage, 0, pMbcs, -1, NULL,0);

	int nSize = nChar * sizeof(wchar_t) + 1;
	wchar_t* pwchBuffer = new wchar_t[nSize];

	nChar = MultiByteToWideChar(codepage, 0, pMbcs, -1, pwchBuffer, nSize);
	if(nChar == 0)
	{
		delete[] pwchBuffer;
		return NULL;
	}

	pwchBuffer[nChar]=0;

	return pwchBuffer;
}

char*	Util::String::UnicodeToMbcs(const wchar_t* pUnicode)
{
	int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
	int nChar = WideCharToMultiByte(codepage, 0, pUnicode, -1, 0, 0, 0, 0);
	int nSize = nChar * sizeof(char) + 1;

	char* pchBuffer = new char[nSize];

	nChar = WideCharToMultiByte(codepage, 0, pUnicode, -1, pchBuffer, nSize, 0, 0);
	if( nChar == 0 )
	{
		delete[] pchBuffer;
		return NULL;
	}

	pchBuffer[nChar]= 0;
	return pchBuffer;
}

char* Util::String::MbcsToUtf8(const char* pMbcs)
{
   assert(pMbcs);
   wchar_t* pUnicode = MbcsToUnicode(pMbcs);
   char*pRet =  UnicodeToUtf8(pUnicode);
   ReleaseData(pUnicode);
   return pRet;
}

char* Util::String::Utf8ToMbcs(const char* pUtf8)
{
	assert(pUtf8);
	wchar_t* pUnicode = Utf8ToUnicode(pUtf8);
	char* pRet = UnicodeToMbcs(pUnicode);
	ReleaseData(pUnicode);
	return pRet;
}

bool Util::String::StringToInt(const char* strValue, int & iValue)
{
	iValue = 0;
	bool br = true;
	if (!strValue || !*strValue)
	{
		return false;
	}
	while (isspace((int)*strValue))
	{
		strValue ++;
	}
	if (*strValue == '+' || *strValue == '-')
	{
		br = (*strValue++ == '+');
	}
	bool bOK = true;
	if (strValue[0] == '0' && (strValue[1]|0x20)=='x')
	{
		strValue += 2;
		for (;;)
		{
			TCHAR ch = *strValue;
			int iValue2 = 0;
			if (ch >= '0' && ch <= '9')	iValue2 = iValue*16 + ch -'0';
			else if (ch>='a' && ch<='f') iValue2 = iValue*16 + ch -'a'+10;
			else if (ch>='A' && ch<='F') iValue2 = iValue*16 + ch -'A'+10;
			else break;
			if (iValue2 < 0 || iValue >= 134217728)	bOK = false;
			iValue = iValue2;
			++strValue;
		}
	}
	else
	{
		while (*strValue >= '0' && *strValue <= '9')
		{
			int iValue2 = iValue * 10 + *strValue++ -'0';
			if (iValue2 < 0 || iValue > 214748364) bOK = false;
			iValue = iValue2;
		}
	}
	if (!br) iValue = -iValue;
	while (*strValue && isspace((BYTE)*strValue)) ++strValue;
	return bOK && strValue[0] == 0;
}
bool Util::String::StringToDWord(const char* strValue, unsigned int & dwValue)
{
	dwValue = 0;
	if (!strValue || !*strValue)
	{
		return false;
	}
	while (isspace((int)*strValue))
	{
		strValue ++;
	}
	if (*strValue == '+')
	{
		strValue ++;
	}
	bool bOK = true;
	if (strValue[0] == '0' && (strValue[1]|0x20)=='x')
	{
		strValue += 2;
		for (;;)
		{
			TCHAR ch = *strValue;
			unsigned int dwValue2 = 0;
			if (ch >= '0' && ch <= '9')	dwValue2 = dwValue*16 + ch -'0';
			else if (ch>='a' && ch<='f') dwValue2 = dwValue*16 + ch -'a'+10;
			else if (ch>='A' && ch<='F') dwValue2 = dwValue*16 + ch -'A'+10;
			else break;
			if (dwValue2 < dwValue || dwValue >= 268435456) bOK = false;
			dwValue = dwValue2;
			++strValue;
		}
	}
	else
	{
		while (*strValue >= '0' && *strValue <= '9')
		{
			unsigned int dwValue2 = dwValue * 10 + *strValue++ -'0';
			if (dwValue2 < dwValue || dwValue > 429496729) bOK = false;
			dwValue = dwValue2;
		}
	}
	while (*strValue && isspace((BYTE)*strValue)) ++strValue;
	return bOK && strValue[0] == 0;
}
bool Util::String::StringToInt64(const char* strValue, long long & i64Value)
{
	i64Value = 0;
	bool br = true;
	if (!strValue || !*strValue)
	{
		return false;
	}
	while (isspace((int)*strValue))
	{
		strValue ++;
	}
	if (*strValue == '+' || *strValue == '-')
	{
		br = (*strValue++ == '+');
	}
	bool bOK = true;
	if (strValue[0] == '0' && (strValue[1]|0x20)=='x')
	{
		strValue += 2;
		for (;;)
		{
			TCHAR ch = *strValue;
			long long i64Value2 = 0;
			if (ch >= '0' && ch <= '9')	i64Value2 = i64Value*16 + ch -'0';
			else if (ch>='a' && ch<='f') i64Value2 = i64Value*16 + ch -'a'+10;
			else if (ch>='A' && ch<='F') i64Value2 = i64Value*16 + ch -'A'+10;
			else break;
			if (i64Value2 < 0 || i64Value >= 576460752303423488ULL) bOK = false;
			i64Value = i64Value2;
			++strValue;
		}
	}
	else
	{
		while (*strValue >= '0' && *strValue <= '9')
		{
			long long i64Value2 = i64Value * 10 + *strValue++ -'0';
			if (i64Value2 < 0 || i64Value > 922337203685477580ULL) bOK = false;

			i64Value = i64Value2;
		}
	}
	if (!br) i64Value = -i64Value;
	while (*strValue && isspace((BYTE)*strValue)) ++strValue;
	return bOK && strValue[0] == 0;
}
bool Util::String::StringToUnsignedInt64(const char* strValue, unsigned long long & ui64Value)
{
	ui64Value = 0;
	if (!strValue || !*strValue)
	{
		return false;
	}
	while (isspace((int)*strValue))
	{
		strValue ++;
	}
	if (*strValue == '+')
	{
		strValue ++;
	}
	bool bOK = true;
	if (strValue[0] == '0' && (strValue[1]|0x20)=='x')
	{
		strValue += 2;
		for (;;)
		{
			TCHAR ch = *strValue;
			unsigned long long ui64Value2 = 0;
			if (ch >= '0' && ch <= '9')	ui64Value2 = ui64Value*16 + ch -'0';
			else if (ch>='a' && ch<='f') ui64Value2 = ui64Value*16 + ch -'a'+10;
			else if (ch>='A' && ch<='F') ui64Value2 = ui64Value*16 + ch -'A'+10;
			else break;
			if (ui64Value2 < ui64Value || ui64Value >= 1152921504606846976ULL) bOK = false;
			ui64Value = ui64Value2;
			++strValue;
		}
	}
	else
	{
		while (*strValue >= '0' && *strValue <= '9')
		{
			unsigned long long ui64Value2 = ui64Value * 10 + *strValue++ -'0';
			if (ui64Value2 < ui64Value || ui64Value > 1844674407370955161ULL) bOK = false;
			ui64Value = ui64Value2;
		}
	}
	while (*strValue && isspace((BYTE)*strValue)) ++strValue;
	return bOK && strValue[0] == 0;
}


inline int Util::String::UrlEncode(const char *source, char *dest, unsigned max)
{
	static const char *digits = "0123456789ABCDEF";
	unsigned char ch;
	unsigned len = 0;
	char *start = dest;

	while (len < max - 4 && *source)
	{
		ch = (unsigned char)*source;
		if (*source == '&') {
			*dest++ = '%';
			*dest++ = digits[(ch >> 4) & 0x0F];
			*dest++ = digits[ch & 0x0F];
		}
		else
		{
			*dest++ = *source;
		}
		source++;
	}
	*dest = 0;
	return start - dest;
}

char* Util::String::FormUrlEncode(const char* pEncode)
{
	size_t needed_length = strlen(pEncode) * 3 + 3;
	char stackalloc[64];
	char * buf = needed_length > sizeof(stackalloc)/sizeof(*stackalloc) ?
		(char *)malloc(needed_length) : stackalloc;
	UrlEncode(pEncode, buf, needed_length);
	std::string result(buf);
	if (buf != stackalloc) {
		free(buf);
	}

	char * szBuffer = new char[result.length() + 1];
	strncpy_s(szBuffer,result.length()+1,result.c_str(),result.length());
	return szBuffer;
}

char* Util::String::FormUrlDecode(const char* pDecode)
{
	std::string buffer = "";
	int len = strlen(pDecode);

	for (int i = 0; i < len; i++)
	{
		int j = i ;
		char ch = pDecode[j];
		if(ch =='+')
		{
			buffer+=' ';
		}
		else if (ch == '%')
		{
			char tmpstr[] = "0x0__";
			int chnum;
			tmpstr[3] = pDecode[j+1];
			tmpstr[4] = pDecode[j+2];
			chnum = strtol(tmpstr, NULL, 16);
			buffer += chnum;
			i += 2;
		}
		else
		{
			buffer += ch;
		}
	}

	char * szBuffer = new char[buffer.length() + 1];
	strncpy_s(szBuffer,buffer.length()+1,buffer.c_str(),buffer.length());
	return szBuffer;

}