// libcurl-test-ce-1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "libcurl-test-ce-1.h"
#include "libcurl-test-ce-1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <sstream>
#include "curl/curl.h"
// 
// #pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "ws2.lib")
//#pragma comment(lib, "wcecompat.lib")


static size_t writeFunc( void* ptr, size_t size, size_t nmemb, void *usrptr )
{
    std::stringstream* ss = (std::stringstream*)usrptr;
    ss->write((const char*)ptr, size * nmemb);
    return (size*nmemb);
}

void test_curl()
{

    std::stringstream ss;
    CURL *curl = NULL;

    curl = curl_easy_init();

    curl_easy_setopt( curl, CURLOPT_URL, "http://www.baidu.com" );
    curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, &writeFunc );
    curl_easy_setopt( curl, CURLOPT_WRITEDATA, &ss );//this will be used in writeFunc as the usrptr

    CURLcode res = curl_easy_perform( curl );

    if (res == CURLE_OK)
    {
        int a;
        a = 1;
        CString temp;
        temp.Format(_T("%s"),ss.str().c_str());
        AfxMessageBox(temp);
    }
    else
    {
        int a;
        a = 1;
    }
}

// Clibcurltestce1Dlg 对话框

Clibcurltestce1Dlg::Clibcurltestce1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clibcurltestce1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clibcurltestce1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clibcurltestce1Dlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Clibcurltestce1Dlg 消息处理程序

BOOL Clibcurltestce1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
test_curl();
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void Clibcurltestce1Dlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_LIBCURLTESTCE1_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_LIBCURLTESTCE1_DIALOG));
	}
}
#endif

