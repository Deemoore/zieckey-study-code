// testMMTimerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testMMTimer.h"
#include "testMMTimerDlg.h"
#include ".\testmmtimerdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CtestMMTimerDlg dialog



CtestMMTimerDlg::CtestMMTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtestMMTimerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestMMTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestMMTimerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CtestMMTimerDlg message handlers

BOOL CtestMMTimerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//m_TimeAgent.StartTimer(1000,1);
	//m_TimeAgent.StartTimer(2000,2);
	m_nText = 0;
	m_nText2 = 0;
    StartTimer(50,1);
    StartTimer(100,2);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CtestMMTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtestMMTimerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtestMMTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtestMMTimerDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	StopTimer(2);
}

void CtestMMTimerDlg::OnMMTimer(int nTimerID)
{

	switch(nTimerID) {
	case 1:
		{

			CWnd *pWnd = GetDlgItem(IDC_STATIC_TIMER1);
			m_nText++;
			m_nText = m_nText % 100;
			CString strOutPut;
			strOutPut.Format("Count:%d",m_nText);
			if( pWnd != NULL)
			{
				::SendMessage(pWnd->GetSafeHwnd(),WM_SETTEXT,NULL,(LPARAM)strOutPut.GetBuffer());
			}

		}
		break;
	case 2:
		{
			CWnd *pWnd = GetDlgItem(IDC_STATIC_TIMER2);
			m_nText2++;
			m_nText2 = m_nText2 % 100 + 100;
			CString strOutPut;
			strOutPut.Format("Count:%d",m_nText2);
			if( pWnd != NULL)
			{
				::SendMessage(pWnd->GetSafeHwnd(),WM_SETTEXT,NULL,(LPARAM)strOutPut.GetBuffer());
			}


		}
		break;
	default:
		break;
	}
}
