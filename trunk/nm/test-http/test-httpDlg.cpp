// test-httpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test-http.h"
#include "test-httpDlg.h"

#include "../http/include/exp.h"
#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CtesthttpDlg 对话框

CtesthttpDlg::CtesthttpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtesthttpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtesthttpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtesthttpDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON1, &CtesthttpDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CtesthttpDlg 消息处理程序

BOOL CtesthttpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CtesthttpDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_TESTHTTP_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_TESTHTTP_DIALOG));
	}
}
#endif


void CtesthttpDlg::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    Test_ParseIpAndURI();
}

void CtesthttpDlg::Test_ParseIpAndURI()
{
    nm::HttpPost post("", 0);
    std::string url = "http://192.168.0.11:8088/abc";
    std::string uri, ip;
    short port;
    nm::HttpPost::ParseIpAndURI(url, ip, port, uri);
    assert((uri == "/abc") && (port == 8088) && (ip == "192.168.0.11"));

    url = "HTTP://192.168.0.11:8088/abc";
    nm::HttpPost::ParseIpAndURI(url, ip, port, uri);
    assert((uri == "/abc") && (port == 8088) && (ip == "192.168.0.11"));

    url = "HTTP://192.168.0.11/abc";
    nm::HttpPost::ParseIpAndURI(url, ip, port, uri);
    assert((uri == "/abc") && (port == 80) && (ip == "192.168.0.11"));
}