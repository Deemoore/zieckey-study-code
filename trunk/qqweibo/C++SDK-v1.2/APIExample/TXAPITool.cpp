// TXAPITool.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "TXAPITool.h"
#include "TXAPIToolDlg.h"
#include "logindlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTXAPIToolApp

BEGIN_MESSAGE_MAP(CTXAPIToolApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTXAPIToolApp ����

CTXAPIToolApp::CTXAPIToolApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CTXAPIToolApp ����

CTXAPIToolApp theApp;


// CTXAPIToolApp ��ʼ��

BOOL CTXAPIToolApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CLoginDlg loginDlg;
    CTXAPIToolDlg dlg;
	
	if(loginDlg.DoModal() == IDOK)
	{
		m_pMainWnd = &dlg;
		dlg.m_strAppKey = loginDlg.m_sstrAppKey;
		dlg.m_strAppSecret = loginDlg.m_sstrAppSecret;
		dlg.m_strAccessKey = loginDlg.m_sstrAccessKey;
		dlg.m_strAccessSecret = loginDlg.m_sstrAccessSecret;

		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
			//  �Ի���Ĵ���
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
			//  �Ի���Ĵ���
		}

		// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
		//  ����������Ӧ�ó������Ϣ�á�
	}
	return FALSE;
}
