#pragma once

#include <bkwinctrls/ExtendCtrlFactory.h>

template<class TMainDlg>
class CMyModule : CAppModule
{
public:
	CMyModule(void)
	{
		// get application path information
		DWORD dwRet = ::GetModuleFileName(NULL, m_strAppFileName.GetBuffer(MAX_PATH+1), MAX_PATH);
		if (0 == dwRet)
		{
			m_strAppFileName.ReleaseBuffer(0);
		}
		else
		{
			m_strAppFileName.ReleaseBuffer();
			m_strAppPath = m_strAppFileName;
			m_strAppPath.Truncate(m_strAppPath.ReverseFind(L'\\') + 1);
		}
	}

	~CMyModule(void)
	{
	}

	UINT_PTR RunMain(void)
	{
		// Initialize Skin Resource
#ifdef USE_SKIN_DLL
		{
			CString strResDLL;
			::GetModuleFileName((HMODULE)&__ImageBase, strResDll.GetBuffer(MAX_PATH+10), MAX_PATH);
			strResDLL.ReleaseBuffer();
			strResDLL.Truncate(strResDLL.ReverseFind(_T('\\') + 1);
			strResDLL += _T("SkinsDefault.skin");
			BKResManager::SetResourceDLL(strResDLL);
		}

#else
		{
			CString strPath;
			::GetModuleFileName((HMODULE)&__ImageBase, strPath.GetBuffer(MAX_PATH+1), MAX_PATH);
			strPath.ReleaseBuffer();
			strPath.Truncate(strPath.ReverseFind(_T('\\')) + 1);
			strPath += _T("Skins\\Default");

			if (PathFileExists(strPath))
			{
				BkResManager::SetResourcePath(strPath);
			}

		}
#endif

		// Check Instance
		if (!CheckInstance())
		{
			return 0;
		}

		UINT_PTR uRet = 0;
		_InitUIResource();
		uRet = m_dlgMain.DoModal(NULL);

		return uRet;
	}

	// Initialize this Application Module
	HRESULT Init(HINSTANCE hInstance)
	{
		HRESULT hRet = __super::Init(NULL, hInstance);
		if (FAILED(hRet)) return hRet;

		// register install path
		CRegKey reg;
		reg.Create(HKEY_LOCAL_MACHINE, L"SOFTWARE\\ABC");
		reg.Create(HKEY_LOCAL_MACHINE, L"SOFTWARE\\ABC\\THClient");

		DWORD dwRet = 1;
		TCHAR szTemp[2];
		LONG lRet = reg.QueryStringValue(_T("Install Path"), szTemp, &dwRet);
		if (ERROR_FILE_NOT_FOUND == lRet)
		{
			reg.SetStringValue(_T("Install Path"), m_strAppPath);
		}

		return hRet;
	}


	#define ABC_THCLIENT_CLASS _T("{9205CA01-8A31-44d1-BF96-6D64B607A9F7}")

	struct Instance_Data
	{
		HWND hActiveWnd;
	};

	CAtlFileMapping<Instance_Data> m_mapping;

	BOOL CheckInstance()
	{
		BOOL bRet = FALSE;
		HRESULT hRet = E_FAIL;
		BOOL bAlreadyExisted = FALSE;

		if (NULL != m_mapping.GetHandle())
			return TRUE;

		hRet = m_mapping.MapSharedMem(sizeof(Instance_Data), ABC_THCLIENT_CLASS, &bAlreadyExisted);
		if (FAILED(hRet))
			return bRet;

		bRet = TRUE;
		if (bAlreadyExisted)
		{
			HWND hWndActive = ((Instance_Data *)m_mapping)->hActiveWnd;

			if (::IsIconic(hWndActive))
				::SendMessage(hWndActive, WM_SYSCOMMAND, SC_RESTORE | HTCAPTION, 0);

			::SetWindowPos(hWndActive, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE);
			::SetForegroundWindow(hWndActive);
			::SetFocus(hWndActive);

			bRet = FALSE;
		}

		return bRet;
	}

	void SetActiveWindow(HWND hWndActive)
	{
		Instance_Data *pInstance = (Instance_Data *)m_mapping;

		if (pInstance)
			pInstance->hActiveWnd = hWndActive;
	}

	BOOL CheckIntegrityLevel()
	{
		BOOL bRet = TRUE;
		if (FALSE == _IsNeedAdministratorCall())
			return bRet;

		bRet = _CmdLine.Execute(m_strAppFileName, TRUE, FALSE);

		if (!bRet)
		{
			::MessageBox(0, L"请使用管理员账户运行本软件", 0, 0);
		}

		return FALSE;
	}

	void _InitUIResource()
	{
		// 可以考虑用BkString来实现多语言
		BkString::Load(IDR_BK_STRING_DEF);
		BkFontPool::SetDefaultFont(BkString::Get(IDS_APP_FONT), -12);

		// 可以考虑用BkSkin来实现换肤
		BkSkin::LoadSkins(IDR_BK_SKIN_DEF);

		// 可以考虑用BkStyle来实现多风格变换
		BkStyle::LoadStyles(IDR_BK_STYLE_DEF);

		CBkPanel::RegistCtrlFactory(new CExtendCtrlFactory());		
	}

protected:
	typedef struct _MY_TOKEN_MANDATORY_LABEL {
		SID_AND_ATTRIBUTES Label;
	} MY_TOKEN_MANDATORY_LABEL, *PMY_TOKEN_MANDATORY_LABEL;

	typedef struct _MY_TOKEN_LINKED_TOKEN {
		HANDLE LinkedToken;
	} MY_TOKEN_LINKED_TOKEN, *PMY_TOKEN_LINKED_TOKEN;
	typedef enum _MY_TOKEN_INFORMATION_CLASS {
		/*
		TokenUser = 1,
		TokenGroups,
		TokenPrivileges,
		TokenOwner,
		TokenPrimaryGroup,
		TokenDefaultDacl,
		TokenSource,
		TokenType,
		TokenImpersonationLevel,
		TokenStatistics,

		TokenRestrictedSids,
		TokenSessionId,
		TokenGroupsAndPrivileges,
		TokenSessionReference,
		TokenSandBoxInert,
		TokenAuditPolicy,
		TokenOrigin,*/
		MYTokenElevationType  = 18, // MaxTokenInfoClass
		MYTokenLinkedToken,
		MYTokenElevation,

		MYTokenHasRestrictions,
		MYTokenAccessInformation,
		MYTokenVirtualizationAllowed,
		MYTokenVirtualizationEnabled,
		MYTokenIntegrityLevel,
		MYTokenUIAccess,
		MYTokenMandatoryPolicy,
		MYTokenLogonSid,
		//MaxTokenInfoClass  // MaxTokenInfoClass should always be the last enum
	} MY_TOKEN_INFORMATION_CLASS, *PMY_TOKEN_INFORMATION_CLASS;

	BOOL _IsNeedAdministratorCall()
	{
		BOOL bRet = FALSE, bNeedSvcCall = FALSE;
		HANDLE hToken = NULL;
		DWORD dwBytesNeeded = 0;
		MY_TOKEN_MANDATORY_LABEL *pTIL = NULL;

		if (!RunTimeHelper::IsVista())
			goto Exit0;

		bRet = ::OpenProcessToken(::GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
		if (NULL == hToken)
			return FALSE;

		bRet = ::GetTokenInformation(
			hToken,
			(TOKEN_INFORMATION_CLASS)MYTokenIntegrityLevel,
			NULL, 0, &dwBytesNeeded);

		pTIL = (MY_TOKEN_MANDATORY_LABEL *)new BYTE[dwBytesNeeded];
		if (!pTIL)
			goto Exit0;

		bRet = ::GetTokenInformation(
			hToken,
			(TOKEN_INFORMATION_CLASS)MYTokenIntegrityLevel,
			pTIL, dwBytesNeeded, &dwBytesNeeded);
		if (!bRet || !pTIL)
			goto Exit0;

		SID* pSid = static_cast<SID*>(pTIL->Label.Sid);
		if (!pSid)
			goto Exit0;

		if (SECURITY_MANDATORY_HIGH_RID > pSid->SubAuthority[0])
			bNeedSvcCall = TRUE;

Exit0:
		if (NULL != pTIL)
		{
			delete[] (LPBYTE)pTIL;
			pTIL = NULL;
		}

		if (hToken)
		{
			::CloseHandle(hToken);
			hToken = NULL;
		}

		return bNeedSvcCall;
	}
protected:
	CString			m_strAppFileName;
    CString			m_strAppPath;
	CBkCmdLine _CmdLine;
	TMainDlg   m_dlgMain;
};

