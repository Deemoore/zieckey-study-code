// Entry.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Entry.h"
#include "MyModule.h"
#include "MainDlg.h"

CMyModule<CMainDlg> _module;


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	HRESULT hRet = E_FAIL;

	if (FALSE == _module.CheckIntegrityLevel())
		return -2;

	hRet = _module.Init(hInstance);
	if (FAILED(hRet))
		return -1;

	::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	// _Module.InitRichEdit2();
	_module.RunMain();

	::CoUninitialize();

	return 0;
}


