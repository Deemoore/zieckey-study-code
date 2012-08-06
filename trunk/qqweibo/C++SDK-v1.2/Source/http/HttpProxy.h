/** 
@file     CHttpProxy
@brief	  http消息处理的代理类.管理所有下载的回调指针. 
		  本类使用Singleton模式,当前只有一个实例

@version	2010-11-17	
*/

#pragma once
#include <windows.h>
#include <map>
class VHttpCallback;


#define MSG_HTTP_COMPLETE	WM_USER + 4000


class  CHttpProxy
{
public:
	static	CHttpProxy *	GetInstance();	

	
	HWND	GethWnd();
	void	HttpMsgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);


	void	AddCallback(unsigned long uKey, VHttpCallback *pCallback);
	VHttpCallback *	GetCallback(unsigned long	 uKey);
	void	RemoveCallback(unsigned long     uKey);
	void	RemoveCallback(VHttpCallback *pCallback);


	///消息处理函数
	void	OnHttpComplete(WPARAM wParam, LPARAM lParam);	
	

private:
	CHttpProxy();
	virtual	~CHttpProxy();

	bool	Init();


private:	
	typedef std::map<unsigned long, VHttpCallback*>   CMapKey2Callback;
	CMapKey2Callback		m_mapKey2Callback;  ///> 存储请求Key和回调指针的对应关系
	HWND					m_hWnd;
};
