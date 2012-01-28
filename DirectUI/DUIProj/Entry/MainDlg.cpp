#include "StdAfx.h"
#include "MainDlg.h"
#include "BusinessHandler.h"

BEGIN_MSG_MAP_EX_IMP(CMainDlg)
	// 这段代码用于接收来自内部的通知消息
	MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
	CHAIN_MSG_MAP(CBkDialogImpl<CMainDlg>)
	CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CMainDlg>)
	MSG_WM_INITDIALOG(OnInitDialog)	

	// 将消息分发给成员
	CHAIN_MSG_MAP_MEMBER((*m_pBusinessHandler))
END_MSG_MAP_IMP()

CMainDlg::CMainDlg(void) : CBkDialogImpl<CMainDlg>(IDR_BK_MAIN_DIALOG)
{
	m_pBusinessHandler = new CBusinessHandler(this);
}

CMainDlg::~CMainDlg(void)
{
}

BOOL CMainDlg::OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/)
{
	m_pBusinessHandler->Init();
	return TRUE;
}
void CMainDlg::OnBkBtnClose()
{
	EndDialog(0);
}
void CMainDlg::OnBkBtnMin()
{
	ShowWindow(SW_MINIMIZE);
}
