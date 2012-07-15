// PLAYMP3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PLAYMP3.h"
#include "PLAYMP3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPLAYMP3App

BEGIN_MESSAGE_MAP(CPLAYMP3App, CWinApp)
	//{{AFX_MSG_MAP(CPLAYMP3App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPLAYMP3App construction

CPLAYMP3App::CPLAYMP3App()
	: CWinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPLAYMP3App object

CPLAYMP3App theApp;

/////////////////////////////////////////////////////////////////////////////
// CPLAYMP3App initialization

BOOL CPLAYMP3App::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	
	HWND hWnd;
	hWnd = ::FindWindow(TEXT("PLAY"),NULL);
	if(hWnd != NULL)
	{
		//��ʾ���ڡ�
		::SendMessage (hWnd,ShowWindow(hWnd,SW_SHOW),0,0);//��ʾ����
		::SendMessage(hWnd,SHOWMP3WINDOW,0,0);//��MP3���ڷ���Ϣ���ø�����������ʱ�ؼ���ʾ��
		::SetWindowPos(hWnd, HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);//����
		::SendMessage(hWnd,VOLMUTE,0,0);//���;������ƣ��õ���ǰ����

		return true;
	}

	HWND hWnd1;
	hWnd1 = ::FindWindow(TEXT("OPENPLAY"),NULL);
	if(hWnd1 != NULL)
	{
		//��ʾ���ڡ�
		::SendMessage (hWnd1,ShowWindow(hWnd1,SW_SHOW),0,0);//��ʾ����
		::SetWindowPos(hWnd1, HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);//����

		return true;
	}


	CPLAYMP3Dlg dlg;
	m_pMainWnd = &dlg;

	WNDCLASS  wc  =  {0};  //ע������ΪPLAY
	::GetClassInfo(AfxGetInstanceHandle(),L"Dialog",&wc);  
    wc.lpszClassName=L"PLAY";  
    AfxRegisterClass(&wc);  

	WNDCLASS  wc1  =  {0};  //OPENPLAY
	::GetClassInfo(AfxGetInstanceHandle(),L"Dialog",&wc1);  
    wc1.lpszClassName=L"OPENPLAY";  
    AfxRegisterClass(&wc1);  

	int nResponse = dlg.DoModal();



	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
