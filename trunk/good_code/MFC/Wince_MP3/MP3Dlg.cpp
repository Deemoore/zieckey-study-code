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
/* ָ��Filter Graph��ָ�� */
    IMediaControl *pMediaControl; 
/* ָ��MediaControl�����ָ�� */ 
/* ��ʼ����ʹ��com��һ������������ʱִ��һ�μ��� */
CoInitialize(NULL); 
/**************************************************************************/
/* ���³���ÿ�β���MP3(��������ʽ)�ļ�ʱ���� */   
/* ����һ��Filter Graph manager */  
CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void **)&pGraph);
    pGraph->QueryInterface(IID_IMediaControl, (void **)&pMediaControl); 
/* ���Ӳ���ָ���ļ������filter */ 
pGraph->RenderFile(L"\\test.mp3", NULL); 
/* ��ʼ����ָ�����ļ� */ 
pMediaControl->Run();  
/* �ļ��Ĳ�����DirectShow�ж����߳��н��У��˴��ȴ� */
//MessageBox(NULL, L"���[OK]��������", L"Play MP3", MB_OK);  
pMediaControl->Stop();  //Pause();
/* ֹͣ���� */  
pMediaControl->Release(); 
/* �ͷŶ��� */ 
pGraph->Release();  
    /**************************************************************************/ 
/* �������ʱ���� */  
CoUninitialize();

}
