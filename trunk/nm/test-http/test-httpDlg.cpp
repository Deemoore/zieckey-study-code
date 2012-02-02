// test-httpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test-http.h"
#include "test-httpDlg.h"

#include "../http/include/exp.h"
#include <assert.h>

#include "../logic/include/exp.h"

#include <sstream>
#include "curl/curl.h"
// 
// #pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "ws2.lib")
//#pragma comment(lib, "wcecompat.lib")

#pragma comment(lib, "libcurl.lib")

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


    listener_ = new MyListener(this);
    logic_manager_ = new nm::LogicManager();
    if (!logic_manager_->Initialize())
    {
        //TODO 
        fprintf(stderr, "init failed!");
        return FALSE;
    }
    Test_All();
	
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
    
}

void CtesthttpDlg::Test_ParseIpAndURI()
{
    nm::HttpPost post("", 0, false);
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


    url = "http://192.168.0.11";
    nm::HttpPost::ParseIpAndURI(url, ip, port, uri);
    assert((uri == "") && (port == 80) && (ip == "192.168.0.11"));


    url = "192.168.0.11";
    nm::HttpPost::ParseIpAndURI(url, ip, port, uri);
    assert((uri == "") && (port == 80) && (ip == "192.168.0.11"));
}

namespace
{
    class LoginListener : public nm::HttpRequest::Listener
    {
    public:
        LoginListener()
        {
        }

        //! \brief <b>Summary:</b>
        //! 	This function is called by HTTPWork(observable) to notify
        //! Listeners that this HTTP work is done, and the received data 
        //! from server is preserved in m_ptrRecvMDStream
        //! \note This function is called in another thread, you <b>MUST</b>
        //!     be care about the multi thread-safe problem
        //! \param  pw, the HTTPWork which is listened by this listener.
        //! you can call HTTPWork::getRecvDataStream() to get the server response string.
        virtual void OnFinishOKT( nm::HttpRequest* pw )
        {
            const std::string& recv_data = pw->GetRespData();
            (void)recv_data;
        }

        //! \brief <b>Summary:</b>
        //! 	This function is called by HTTPWork(observable) to notify
        //! Listeners that the work is no done because something error.
        //! \note This function is called in another thread, you <b>MUST</b>
        //!     be care about the multi thread-safe problem
        //! \param hec, error code
        //! \param pw, the HTTPWork which is listened by this listener
        virtual void OnFinishErrorT(nm::HttpRequest::HttpErrorCode hec, nm::HttpRequest* pw )
        {
            const std::string& recv_data = pw->GetRespData();
            (void)recv_data;
        }
    };
}

void CtesthttpDlg::Test_Login()
{
    std::string username = "ailun";
    std::string pwd = "123456";
    if (!logic_manager_->GetUserCenter()->Login(username, pwd, listener_))
    {
        fprintf(stderr, "login failed!\n");
    }
}




static size_t writeFunc( void* ptr, size_t size, size_t nmemb, void *usrptr )
{
    std::stringstream* ss = (std::stringstream*)usrptr;
    ss->write((const char*)ptr, size * nmemb);
    return (size*nmemb);
}

void Test_curl()
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
        temp.Format(_T("%s"),osl::StringUtil::utf8ToMbs(ss.str()).c_str());
        AfxMessageBox(temp);
    }
    else
    {
        int a;
        a = 1;
    }
}

void CtesthttpDlg::Test_All()
{
    Test_CharsetEncodingConvert();

    Test_ParseIpAndURI();
    
    //Test_Login();

    //Test_AsyncCURLWork();

    Test_curl();
}



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

void CtesthttpDlg::Test_AsyncCURLWork()
{
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


    //异步调用的时候，release 有些问题
    {
        net::HttpGetWorkPtr work = new net::HttpGetWork("http://www.baidu.com");
        work->addListener(listener_);
        logic_manager_->GetCURLService()->addWorkT(work);
    }
}

void CtesthttpDlg::Test_CharsetEncodingConvert()
{
    std::string mbs = "用户类型";
    std::string utf8str = osl::StringUtil::mbsToUtf8(mbs);
    //std::string unicodestr = osl::StringUtil::utf8ToUtf16()
}


