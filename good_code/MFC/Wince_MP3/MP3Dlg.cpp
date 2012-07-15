// MP3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MP3.h"
#include "MP3Dlg.h"
#include <dshow.h>
#include <streams.h>

#pragma comment (lib,"Ole32.lib")
#pragma comment (lib,"Strmiids.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMP3Dlg dialog

CMP3Dlg::CMP3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMP3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMP3Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMP3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMP3Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMP3Dlg, CDialog)
	//{{AFX_MSG_MAP(CMP3Dlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMP3Dlg message handlers

BOOL CMP3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CMP3Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	IGraphBuilder *pGraph;  
/* 指向Filter Graph的指针 */
    IMediaControl *pMediaControl; 
/* 指向MediaControl对象的指针 */ 
/* 初始化，使用com第一步，程序启动时执行一次即可 */
CoInitialize(NULL); 
/**************************************************************************/
/* 以下程序每次播放MP3(或其他格式)文件时调用 */   
/* 创建一个Filter Graph manager */  
CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void **)&pGraph);
    pGraph->QueryInterface(IID_IMediaControl, (void **)&pMediaControl); 
/* 连接播放指定文件所需的filter */ 
pGraph->RenderFile(L"\\test.mp3", NULL); 
/* 开始播放指定的文件 */ 
pMediaControl->Run();  
/* 文件的播放在DirectShow中独立线程中进行，此处等待 */
//MessageBox(NULL, L"点击[OK]结束播放", L"Play MP3", MB_OK);  
pMediaControl->Stop();  //Pause();
/* 停止播放 */  
pMediaControl->Release(); 
/* 释放对象 */ 
pGraph->Release();  
    /**************************************************************************/ 
/* 程序结束时调用 */  
CoUninitialize();

}
