// MyMp3sec.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MyMp3sec.h"
#include "MyMp3secDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMp3secApp

BEGIN_MESSAGE_MAP(CMyMp3secApp, CWinApp)
	//{{AFX_MSG_MAP(CMyMp3secApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyMp3secApp construction

CMyMp3secApp::CMyMp3secApp()
	: CWinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyMp3secApp object

CMyMp3secApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMyMp3secApp initialization

BOOL CMyMp3secApp::InitInstance()
{
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CMyMp3secDlg dlg;
	m_pMainWnd = &dlg;
	SetDialogBkColor(RGB(255,255,255),RGB(0,0,0));
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
