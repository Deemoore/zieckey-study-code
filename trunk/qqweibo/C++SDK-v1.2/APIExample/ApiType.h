#ifndef __TXWB_APITYPE__
	#define __TXWB_APITYPE__

#include <vector>
#include <string>


class CApiType{

public:
	CApiType();
	~CApiType();
	void InitApiTypeList();
	void InitDefaultParamList();

public:
	typedef std::pair<std::wstring,std::wstring>  paramKeyValuePair;
	typedef std::vector<paramKeyValuePair> paramKeyValuePairList;
	paramKeyValuePairList m_apiDefaultKeyValuePairList[TXWB_MAX];
	std::wstring m_apiTypeNameList[TXWB_MAX];
	
private:


};


#endif