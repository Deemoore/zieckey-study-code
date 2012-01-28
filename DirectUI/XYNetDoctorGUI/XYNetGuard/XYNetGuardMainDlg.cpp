#include "stdafx.h"
#include "XYNetGuard.h"
#include "XYNetGuardmaindlg.h"
#include "XYNetGuarduihandler.h"


BOOL	g_bkMsgBox = FALSE;

BEGIN_MSG_MAP_EX_IMP(CXYNetGuardMainDlg)
	MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
	CHAIN_MSG_MAP(CBkDialogImpl<CXYNetGuardMainDlg>)
	CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CXYNetGuardMainDlg>)
	CHAIN_MSG_MAP_MEMBER((*m_pNetGuardUIHandler))
	CHAIN_MSG_MAP_MEMBER((*m_pHomeViewUIHandler))
	CHAIN_MSG_MAP_MEMBER((*m_pNetConfigUIHandler))

	MSG_WM_INITDIALOG(OnInitDialog)
	MSG_WM_SYSCOMMAND(OnSysCommand)
	REFLECT_NOTIFICATIONS_EX()
END_MSG_MAP_IMP()


CXYNetGuardMainDlg::CXYNetGuardMainDlg()
	: CBkDialogImpl<CXYNetGuardMainDlg>(IDR_BK_MAIN_DIALOG)
{
	m_pNetGuardUIHandler		= new CXYNetGuardUIHandler(this);
	m_pHomeViewUIHandler		= new CHomeViewUIHandler(this);
	m_pNetConfigUIHandler		= new CNetConfigUIHandler(this);

	ZeroMemory(&m_NotifyIconData, sizeof m_NotifyIconData);
}

CXYNetGuardMainDlg::~CXYNetGuardMainDlg()
{
	delete m_pNetGuardUIHandler;
	delete m_pHomeViewUIHandler;
	delete m_pNetConfigUIHandler;
}

BOOL CXYNetGuardMainDlg::OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/)
{
	SetIcon(::LoadIcon((HMODULE)&__ImageBase, MAKEINTRESOURCE(IDI_BEIKESAFE)));
	SetIcon(::LoadIcon((HMODULE)&__ImageBase, MAKEINTRESOURCE(IDI_SMALL)), FALSE);
	_Module.SetActiveWindow(m_hWnd);
	
	ZeroMemory(&m_NotifyIconData, sizeof m_NotifyIconData);

	m_pNetGuardUIHandler->Init();
	m_pNetGuardUIHandler->FirstShow();

	m_pHomeViewUIHandler->Init();
	m_pHomeViewUIHandler->FirstShow();

	m_pNetConfigUIHandler->Init();
	m_pNetConfigUIHandler->FirstShow();


	InitTray();

	return TRUE;
}

void CXYNetGuardMainDlg::OnBkBtnClose()
{
	ShowWindow(SW_HIDE);
}

void CXYNetGuardMainDlg::OnBkBtnMenu()
{
	CPoint	pos;
	CRect	rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);

	pos.x = rc.right - 108;
	pos.y = rc.top + 22;

	CMenu menuPopup;
	menuPopup.LoadMenu(IDR_MAINMENU);

	CMenuHandle Menu = menuPopup.GetSubMenu(0);;
	
	//ATLVERIFY(GetCursorPos(&pos));
	Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN, pos.x, pos.y, m_hWnd);
}

void CXYNetGuardMainDlg::InitTray()
{
	if(!m_NotifyIconData.cbSize)
	{
		m_NotifyIconData.cbSize = NOTIFYICONDATAA_V1_SIZE;
		m_NotifyIconData.hWnd = m_hWnd;
		m_NotifyIconData.uID = 1;
		m_NotifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		m_NotifyIconData.uCallbackMessage = WM_SYSTEMTRAYICON;
		m_NotifyIconData.hIcon = AtlLoadIconImage(IDI_BEIKESAFE, LR_DEFAULTCOLOR, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON));
		CString sWindowText;
		GetWindowText(sWindowText);
		_tcscpy_s(m_NotifyIconData.szTip, sWindowText);
		if(!Shell_NotifyIcon(NIM_ADD, &m_NotifyIconData))
		{
			SetMsgHandled(FALSE);
		}
	}
}

void CXYNetGuardMainDlg::DelTray()
{
	if(m_NotifyIconData.cbSize)
	{
		Shell_NotifyIcon(NIM_DELETE, &m_NotifyIconData);
		ZeroMemory(&m_NotifyIconData, sizeof m_NotifyIconData);
	}
}

void CXYNetGuardMainDlg::OnBkBtnMin()
{	
	ShowWindow(SW_HIDE);
}

LRESULT CXYNetGuardMainDlg::OnSystemTrayIcon(UINT, WPARAM wParam, LPARAM lParam)
{
	ATLASSERT(wParam == 1);
	switch(lParam)
	{
	case WM_LBUTTONDBLCLK:
		//SendMessage(WM_COMMAND, SC_RESTORE);
		SetForegroundWindow(m_hWnd);
		ShowWindow(SW_SHOW);
		BringWindowToTop();
		break;
	case WM_RBUTTONUP:
		{
			SetForegroundWindow(m_hWnd);
			CMenu menuPopup;
			menuPopup.LoadMenu(IDR_TRAYMENU);

			CMenuHandle Menu = menuPopup.GetSubMenu(0);;
			CPoint Position;
			ATLVERIFY(GetCursorPos(&Position));
			Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_BOTTOMALIGN, Position.x, Position.y, m_hWnd);
		}
		break;
	}
	return 0;
}

LRESULT CXYNetGuardMainDlg::OnScRestore(UINT, INT, HWND)
{
	ShowWindow(SW_SHOW);
	BringWindowToTop();
	return 0;
}

LRESULT CXYNetGuardMainDlg::OnScClose(UINT, INT, HWND)
{
	DelTray();

	EndDialog(IDCANCEL);

	return 0;
}

void CXYNetGuardMainDlg::EndDialog(UINT uRetCode)
{
	__super::EndDialog(uRetCode);
}

void CXYNetGuardMainDlg::OnSysCommand(UINT nID, CPoint point)
{
	SetMsgHandled(FALSE);

	switch (nID & 0xFFF0)
	{
	case SC_CLOSE:
		SetMsgHandled(TRUE);
		if( !g_bkMsgBox )		//已经弹出msgbox，不关闭窗口
		{
			EndDialog(IDCANCEL);
		}
		break;
	}
}

void	CXYNetGuardMainDlg::OnBkBtnFeedBack()
{
	::ShellExecute(NULL, _T("open"), _T("http://bbs.code.ijinshan.com/forumdisplay.php?fid=11"), NULL, NULL, SW_SHOWNORMAL);
}

