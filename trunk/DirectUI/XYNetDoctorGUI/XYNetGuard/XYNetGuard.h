#pragma once

#include "resource.h"
#include <bkres/bkres.h>
#include <atlfile.h>
#include <bkwin/bkatldefine.h>
#include <miniutil/bkcmdline.h>

class CXYNetGuardModule
    : public CAppModule
{
public:
	CXYNetGuardModule()
		: m_hModRichEdit2(NULL)
    {
    }

    HRESULT			Init(HINSTANCE hInstance);
    UINT_PTR		RunMain();
    BOOL			CheckInstance();
    void			SetActiveWindow(HWND hWndActive);
	VOID			InitRichEdit2();
	BOOL			CheckIntegrityLevel();
	LPCTSTR			GetAppFilePath();
	LPCTSTR			GetAppDirPath();

protected:
    CString			m_strAppFileName;
    CString			m_strAppPath;
	HMODULE			m_hModRichEdit2;
    BkWinManager	m_BkWndMagnager;
    CBkCmdLine		_CmdLine;
	
	struct XYNetGuard_Instance_Data
	{
		HWND hActiveWnd;
	};

	CAtlFileMapping<XYNetGuard_Instance_Data> m_mapping;

	BOOL			_GetPEProductVersion(LPCWSTR lpszFileName, CString &strProductVersion);
    void			_GetFileInfo(BYTE *pbyInfo, LPCWSTR lpszFileInfoKey, LPWSTR lpszFileInfoRet);
    void			_InitUIResource();
	void			_RestartSelf();
	BOOL			_IsNeedAdministratorCall();
};

extern CXYNetGuardModule _Module;
