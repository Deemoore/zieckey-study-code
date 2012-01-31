// net-ce-testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "net-ce-test.h"
#include "net-ce-testDlg.h"

#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "ws2.lib")

#include "net/include/exp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CnetcetestDlg 对话框

CnetcetestDlg::CnetcetestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CnetcetestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CnetcetestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CnetcetestDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CnetcetestDlg 消息处理程序


void test_MemoryDataStream()
{
    osl::MemoryDataStreamPtr buf = new osl::MemoryDataStream();
    buf->write("abc,", 4);
    buf->write("abc,", 4);
    buf->write("abc,", 4);
    buf->write("abc,", 4);
    buf->write("abc,", 4);
    buf->reset();
    buf->write("abc,", 4);
    buf->write("abc,", 4);
    buf->write("abc,", 4);
    buf->write("abc,", 4);
    buf->write("abc,", 4);

    osl::MemoryDataStream* buf1 = buf.getPointer();
    osl::MemoryDataStream* buf2 = buf.getPointer();
    buf1->write("abc,", 4);
    buf2->write("abc,", 4);

    buf->write("abc,", 4);
    buf->write("abc,", 4);
    buf->write("abc,", 4);
    buf->write("abc,", 4);

    osl::MemoryDataStreamPtr buf3 = buf;
    osl::MemoryDataStreamPtr buf4 = buf;


    buf3->write("abc,", 4);
    buf3->write("abc,", 4);
    buf4->write("abc,", 4);
    buf4->write("abc,", 4);

}

BOOL CnetcetestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

    test_MemoryDataStream();

    {
        net::HttpGetWorkPtr work = new net::HttpGetWork("http://www.baidu.com");
        work->setBlockingDoHttpRequest(true);
        work->doHttpBlockingRequest();
        osl::MemoryDataStreamPtr recv_data = work->getRecvDataStream();
        size_t ss = recv_data->size();
        const char* data = recv_data->data();
        fprintf(stderr, "%lu %s\n", ss, data);
    }

    listener_ = new MyListener;
    curl_service_ = new net::CURLService(1);
    bool start_ok = curl_service_->start();
    if (!start_ok)
    {
        fprintf(stderr, "curl start failed!\n");
    }

    {
        net::HttpGetWorkPtr work = new net::HttpGetWork("http://www.baidu.com");
        work->addListener(listener_);
        curl_service_->addWorkT(work);
    }


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CnetcetestDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_NETCETEST_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_NETCETEST_DIALOG));
	}
}
#endif

