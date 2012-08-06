#include "HttpProxy.h"
#include "Http.h"
#include "UtilString.h"
#include "curl\curl.h"


CHttpProxy* g_pHttpProxy = NULL; ///> 全局变量，一旦创建就不释放了，进程退出时让操作系统释放

CHttpProxy *CHttpProxy::GetInstance()
{
	if (g_pHttpProxy == NULL)
	{
		g_pHttpProxy = new CHttpProxy;

		if (!g_pHttpProxy->Init())
		{
			delete g_pHttpProxy;
			g_pHttpProxy = NULL;
		}
	}

	return g_pHttpProxy;
}

LRESULT CALLBACK   HttpProxyWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{	
	if (g_pHttpProxy)
	{
		g_pHttpProxy->HttpMsgProc(hWnd, Msg, wParam, lParam);
	}

	LRESULT lRet = ::DefWindowProc(hWnd,Msg,wParam,lParam);

	return lRet;
}

CHttpProxy::CHttpProxy():
m_hWnd(0)
{	
	curl_global_init(CURL_GLOBAL_ALL);
}

CHttpProxy::~CHttpProxy()
{
	curl_global_cleanup();
}

bool	CHttpProxy::Init()
{
	WNDCLASSEX  wc	   =  {sizeof(wc)};
	wc.hInstance	   =  ::GetModuleHandle(0);
	wc.lpszClassName   =  L"TXWeiboHttpWindow";
	wc.lpfnWndProc	   =  &HttpProxyWndProc;
	wc.hbrBackground   =  NULL;
	wc.cbWndExtra      =  sizeof(void*);

	WNDCLASSEX			wc2;
	if (!GetClassInfoEx(wc.hInstance, wc.lpszClassName, &wc2))
	{
		RegisterClassEx(&wc);
	}

	CREATESTRUCT cs		= {0};
	cs.lpszClass		=  wc.lpszClassName;
	cs.lpszName			=  L"";
	cs.hInstance		=  wc.hInstance;
	cs.hwndParent		=  0;	
	cs.style			=  WS_POPUP;

	m_hWnd = CreateWindowEx(cs.dwExStyle,cs.lpszClass,cs.lpszName,cs.style,
		cs.x,cs.y,cs.cx,cs.cy,cs.hwndParent,cs.hMenu,cs.hInstance,cs.lpCreateParams);

	if(NULL == m_hWnd )
	{
		return false;
	}

	return true;
}

HWND  CHttpProxy::GethWnd()
{
	return m_hWnd;
}

void CHttpProxy::HttpMsgProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	switch(Msg)
	{
	case MSG_HTTP_COMPLETE:
		OnHttpComplete(wParam, lParam);
		break;		
	}
}


void CHttpProxy::OnHttpComplete(WPARAM wParam, LPARAM lParam)
{	
	VHttpCallback	*pCallback = NULL;
	pCallback    = GetCallback((unsigned int)wParam);

	if ( pCallback )
	{
		HTTP_RESULTCODE   eErrorCode = (HTTP_RESULTCODE)lParam;
		CHttp * pHttp = (CHttp *)wParam;

		std::string strResult;
		if(!pHttp->GetResultData(strResult))
		{
            eErrorCode = HTTPRESULT_TOOLAGRE;
		}
		
		if (NULL != pHttp)
		{
			pHttp-> m_bRunning = false;
		}
		pCallback->OnHttpComplete(pHttp,eErrorCode,strResult);
	}	
}



void CHttpProxy::AddCallback(unsigned long uKey, VHttpCallback *pCallback)
{
	if( 0 == uKey || NULL == pCallback )
	{
		return;
	}

	m_mapKey2Callback[uKey] = pCallback;
}

void CHttpProxy::RemoveCallback(unsigned long  uKey)
{
	m_mapKey2Callback.erase(uKey);
}

void CHttpProxy::RemoveCallback(VHttpCallback *pCallback)
{
	CMapKey2Callback::iterator it = m_mapKey2Callback.begin();

	while( it != m_mapKey2Callback.end() )
	{
		if(it->second == pCallback)
		{
			it = m_mapKey2Callback.erase(it);
		}
		else
		{
			it++;
		}
	}
}

VHttpCallback * CHttpProxy::GetCallback( unsigned long uKey )
{
	VHttpCallback *pCallback = NULL;
	CMapKey2Callback::const_iterator iter = m_mapKey2Callback.find(uKey);

	if (iter != m_mapKey2Callback.end())
	{
		pCallback = iter->second;
	}

	return pCallback;
}
