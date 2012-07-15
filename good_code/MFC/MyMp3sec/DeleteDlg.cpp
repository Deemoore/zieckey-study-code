// DeleteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyMp3sec.h"
#include "DeleteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteDlg dialog


CDeleteDlg::CDeleteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	DELETEOK.LoadBitmaps(IDB_DELETEOK);
	DELETECANCEL.LoadBitmaps(IDB_DELETECANCEL);
}


void CDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteDlg, CDialog)
	//{{AFX_MSG_MAP(CDeleteDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteDlg message handlers

void CDeleteDlg::OnOK() 
{
	// TODO: Add extra validation here
	PTSTR pszFilename=sourcepath.GetBuffer(55);
	DeleteFile(pszFilename);
	CDialog::OnOK();
	mymp3dlg->SearchFile();
	mymp3dlg->On0();
}

void CDeleteDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
//MessageBox(TEXT("OnCancel()"),TEXT("conment"),MB_OK);
	CDialog::OnCancel();
}

BOOL CDeleteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	VERIFY(DELETEOK.SubclassDlgItem(IDOK,this));
	DELETEOK.SizeToContent();
	VERIFY(DELETECANCEL.SubclassDlgItem(IDCANCEL,this));
	DELETECANCEL.SizeToContent();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
