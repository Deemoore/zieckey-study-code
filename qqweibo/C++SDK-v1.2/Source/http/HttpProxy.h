/** 
@file     CHttpProxy
@brief	  http��Ϣ����Ĵ�����.�����������صĻص�ָ��. 
		  ����ʹ��Singletonģʽ,��ǰֻ��һ��ʵ��

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


	///��Ϣ������
	void	OnHttpComplete(WPARAM wParam, LPARAM lParam);	
	

private:
	CHttpProxy();
	virtual	~CHttpProxy();

	bool	Init();


private:	
	typedef std::map<unsigned long, VHttpCallback*>   CMapKey2Callback;
	CMapKey2Callback		m_mapKey2Callback;  ///> �洢����Key�ͻص�ָ��Ķ�Ӧ��ϵ
	HWND					m_hWnd;
};
