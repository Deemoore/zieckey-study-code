// Delog.cpp : implementation file
//

#include "stdafx.h"
#include "MyMp3sec.h"
#include "Delog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Delog dialog


Delog::Delog(CWnd* pParent /*=NULL*/)
	: CDialog(Delog::IDD, pParent)
{
	//{{AFX_DATA_INIT(Delog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Delog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Delog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Delog, CDialog)
	//{{AFX_MSG_MAP(Delog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Delog message handlers
