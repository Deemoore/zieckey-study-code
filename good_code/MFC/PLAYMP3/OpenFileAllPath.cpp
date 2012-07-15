// OpenFileAllPath.cpp : implementation file
//

#include "stdafx.h"
#include "PLAYMP3.h"
#include "OpenFileAllPath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenFileAllPath dialog


COpenFileAllPath::COpenFileAllPath(CWnd* pParent /*=NULL*/)
	: CDialog(COpenFileAllPath::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenFileAllPath)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COpenFileAllPath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenFileAllPath)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenFileAllPath, CDialog)
	//{{AFX_MSG_MAP(COpenFileAllPath)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenFileAllPath message handlers
