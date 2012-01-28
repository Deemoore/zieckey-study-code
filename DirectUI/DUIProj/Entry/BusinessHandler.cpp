#include "StdAfx.h"
#include "BusinessHandler.h"
#include "MainDlg.h"

CBusinessHandler::CBusinessHandler(CMainDlg* pMainDlg) : m_pMainDlg(pMainDlg)
{
}

CBusinessHandler::~CBusinessHandler(void)
{
}

void CBusinessHandler::Init()
{
	// To Do
	// Initialize business modal
}

void CBusinessHandler::OnLeftBtn04Click()
{
	::MessageBox(NULL, _T("Btn 04 Clicked."), _T("Btn Click"), MB_OK);
}