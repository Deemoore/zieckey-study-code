// osl-ce-testDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "osl-ce-test.h"
#include "osl-ce-testDlg.h"

#pragma comment(lib, "osl.lib")
#include "osl/include/data_stream.h"
#include "osl/include/thread.h"
#include "osl/include/process_ext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CoslcetestDlg �Ի���

CoslcetestDlg::CoslcetestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoslcetestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CoslcetestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CoslcetestDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON1, &CoslcetestDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CoslcetestDlg ��Ϣ�������

static int g_count = 0;
DWORD __stdcall ThreadProc( void* pvArg )
{
    while(true)
    {
        g_count++;
        osl::Process::msleep(1000);
    }
}


class MyThread : public osl::Thread
{
public:
    MyThread() : count_(0)
    {
        buf_ = new osl::MemoryDataStream(1024);
    }

    ~MyThread()
    {
    }

    virtual void stop()
    {
        running_ = false;
        osl::Thread::stop();
    }

    virtual void run()
    {
        running_ = true;
        while(running_)
        {
            count_++;
            buf_->write("aaa,", 4);
            if (buf_->size() > 100000)
            {
                buf_->reset();
            }
            osl::Process::msleep(1000);
        }
    }

 osl::MemoryDataStreamPtr buf_;
 bool running_;
 int count_;
};

MyThread* g_thread;

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

BOOL CoslcetestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

    test_MemoryDataStream();

    g_thread = new MyThread();
    g_thread->ref();
    g_thread->start();
    DWORD m_dwReadThreadID = 0;
    HANDLE mythread = CreateThread(NULL,0,ThreadProc,this,0,&m_dwReadThreadID);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CoslcetestDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_OSLCETEST_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_OSLCETEST_DIALOG));
	}
}
#endif


void CoslcetestDlg::OnBnClickedButton1()
{

    // TODO: �ڴ���ӿؼ�֪ͨ����������

    size_t ss = g_thread->count_;
    (void)ss;
    size_t bb = ss;

    g_thread->stop();
    g_thread->unref();
}
