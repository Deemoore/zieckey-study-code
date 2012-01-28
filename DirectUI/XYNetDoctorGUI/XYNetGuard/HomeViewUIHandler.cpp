#include "stdafx.h"
#include "XYNetGuard.h"
#include "XYNetGuardmaindlg.h"
#include "HomeViewUIHandler.h"
#include "XYNetGuardmsgbox.h"


#define		DIAGNOSE_TIMER_NUMBER		1000
#define		SPEEDMEASURE_TIMER_NUMBER	1001

#define		COL_SCAN_ITEM_DISABLE		RGB(150,150,150)
#define		COL_SCAN_ITEM_NORMAL		RGB(0,0,0)
#define		COL_SCAN_ITEM_RISK			RGB(231,199,66)
#define		COL_SCAN_ITEM_ERROR			RGB(255,0,0)


CHomeViewUIHandler::CHomeViewUIHandler(CXYNetGuardMainDlg* refDialog)
: m_pMainDlg(refDialog)
, m_bFirstShowed(FALSE)
, m_bIsExaming(FALSE)
, m_bHasDiagnosed(FALSE)
, m_nDiagnoseProcessPicNum(0)
{
	
}

 CHomeViewUIHandler::~CHomeViewUIHandler()
{

}


// ��ʼ��UIHandler
void CHomeViewUIHandler::Init()
{
	if(!m_wndDiagnoseResult.Create( 
		m_pMainDlg->GetViewHWND(), NULL, NULL, 
		WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL | LVS_OWNERDRAWFIXED, 
		0, IDC_DIAGNOSE_RESULT_LIST_REALWND, NULL) != NULL)
	{
		// ������
		return;
	}
	
	m_wndDiagnoseResult.InsertColumn(0, _T("�������"), LVCFMT_CENTER, 120);
	m_wndDiagnoseResult.InsertColumn(1, _T("��Ͻ��"), LVCFMT_CENTER, 220);
	m_wndDiagnoseResult.InsertColumn(2, _T("����ԭ��"), LVCFMT_CENTER, 240);

	m_wndDiagnoseResult.SetItemHeight(30);


	if(!m_wndComboBox.Create( 
		m_pMainDlg->GetViewHWND(), CRect(10,10,200,30), NULL, 
		WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST , 
		0, IDC_DEMO_COMBOBOX_REALWND, NULL) != NULL)
	{
		// ������
		return;
	}

	int		nIndex = 0;
	m_wndComboBox.InsertString(nIndex++,_T("������0"));
	m_wndComboBox.InsertString(nIndex++,_T("������1"));
	m_wndComboBox.InsertString(nIndex++,_T("������2"));
	m_wndComboBox.InsertString(nIndex++,_T("������3"));
	m_wndComboBox.InsertString(nIndex++,_T("������4"));
	m_wndComboBox.InsertString(nIndex++,_T("������5"));

	m_wndComboBox.SetCurSel(0);
}



// �������һ����ʾ
void CHomeViewUIHandler::FirstShow()
{
	OnStartDiagnose();
}


void CHomeViewUIHandler::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == DIAGNOSE_TIMER_NUMBER)
	{
		for(int i=0;i<2 ;i++)
		{
			m_pMainDlg->SetItemDWordAttribute(IDC_SCAN_ITEM_START+i*4,"sub",m_nDiagnoseProcessPicNum%12);
			
		}
				
		// �м�Ķ���
		m_pMainDlg->SetItemDWordAttribute(IDC_DIAGNOSE_ALL_ANIMATE,"sub",m_nDiagnoseProcessPicNum%12);

		m_nDiagnoseProcessPicNum++;

		if(m_nDiagnoseProcessPicNum >= 100)
		{
			OnAllDiagnoseFinished();
		}
	}

}


void CHomeViewUIHandler::OnStartDiagnose()
{
	if(m_bIsExaming)
		return;

	InitLeftDiagnoseItemList();

	m_wndDiagnoseResult.DeleteAllItems();

	m_bIsExaming	= TRUE;

	m_nDiagnoseProcessPicNum	= 0;
	
	// ������Ҫ
	m_pMainDlg->SetTimer(DIAGNOSE_TIMER_NUMBER,80,NULL);
	m_pMainDlg->SetTimer(SPEEDMEASURE_TIMER_NUMBER, 46,NULL);

	m_pMainDlg->SetItemVisible(IDC_DIAGNOSE_PROCESSING_DLG,TRUE);
	m_pMainDlg->SetItemVisible(IDC_DIAGNOSE_RESULT_ERROR_DLG,FALSE);
	m_pMainDlg->SetItemVisible(IDC_DIAGNOSE_RESULT_NOERROR_DLG,FALSE);
	
	m_pMainDlg->SetRichText(IDC_DIAGNOSE_RESULT_HEADER_RICHTEXT,_T("���ڽ���������ϣ����Ժ󡣡���"));


}

void	CHomeViewUIHandler::OnAllDiagnoseFinished()
{
	m_bIsExaming			= FALSE;
	m_bHasDiagnosed			= TRUE;

	m_pMainDlg->KillTimer(DIAGNOSE_TIMER_NUMBER);

	// ���ݼ������������
	ShowDiagnoseResult();
}

// ���������Ҳ���ʾ��Ͻ��
void	CHomeViewUIHandler::ShowDiagnoseResult()
{
	BOOL									bNoError		= TRUE;
	
	int										nItemNum;

	for(int i=0;i<2;i++)
	{
		m_pMainDlg->SetItemVisible(IDC_SCAN_ITEM_START+i*4,FALSE);
		m_pMainDlg->SetItemVisible(IDC_SCAN_ITEM_START+i*4+1,TRUE);
		m_pMainDlg->SetItemDWordAttribute(IDC_SCAN_ITEM_START+i*4+1,"sub",0);
		m_pMainDlg->SetItemColorAttribute(IDC_SCAN_ITEM_START+i*4+2,"crtext",COL_SCAN_ITEM_NORMAL);
		m_pMainDlg->SetItemColorAttribute(IDC_SCAN_ITEM_START+i*4+3,"crtext",COL_SCAN_ITEM_NORMAL);
		m_pMainDlg->SetItemText(IDC_SCAN_ITEM_START+i*4+3,_T("����"));

	}
	
	m_pMainDlg->SetItemVisible(IDC_DIAGNOSE_PROCESSING_DLG,FALSE);
	m_pMainDlg->SetItemVisible(IDC_DIAGNOSE_RESULT_ERROR_DLG,FALSE);
	m_pMainDlg->SetItemVisible(IDC_DIAGNOSE_RESULT_NOERROR_DLG,TRUE);

	m_pMainDlg->SetRichText(IDC_DIAGNOSE_RESULT_HEADER_RICHTEXT,_T("�����ϣ�δ�����κ����⡣"));
			
	SetWebQoSStar(1024,2048);

	int m_nMaxSpeed	= 512;
	

	CString		strSpeedMsg;
	strSpeedMsg.Format(_T("����ƽ�����٣�<b><c  color=FB9D00>420KB</c></b>/�룬�������<b><c  color=FB9D00>512KB</c></b>/��"));

	m_pMainDlg->SetRichText(IDC_NETSPEED_RESULT_RICHTEXT,strSpeedMsg );
	int nSpeed = _GetProcessPos(m_nMaxSpeed);
	m_pMainDlg->SetItemIntAttribute(IDC_NETSPEED_RESULT_PROCESS, "value", nSpeed);

}

// ���ݷ�����վ��ƽ����Ӧʱ���������Ǽ�
// ʹ�ÿ�3�η��ķ�ʽ����������Ӧʱ�����40000����ĵ�������Ӧ�ģ�ͳһ����Ϊ���ǣ�����������3�η�ȡ��������
void	CHomeViewUIHandler::SetWebQoSStar(DWORD dwAvgSurferTime,int nSuccedCount)
{
	DWORD	dwStarLevel	= 9;
	for(int i=0;i<5;i++)
	{
		if(i<dwStarLevel/2)
		{
			m_pMainDlg->SetItemDWordAttribute(IDC_INTERNET_QOS_START_ID+1+i,"sub",0);
		}
		else
		{
			m_pMainDlg->SetItemDWordAttribute(IDC_INTERNET_QOS_START_ID+1+i,"sub",2);
		}
	}

	if(dwStarLevel%2 == 1)
	{
		m_pMainDlg->SetItemDWordAttribute(IDC_INTERNET_QOS_START_ID+(dwStarLevel+1)/2,"sub",1);
	}

}


LRESULT CHomeViewUIHandler::OnSystemTrayIcon(UINT nCommandID, WPARAM wParam, LPARAM lParam)
{
	return m_pMainDlg->OnSystemTrayIcon(nCommandID,wParam,lParam);
}

LRESULT CHomeViewUIHandler::OnScRestore(UINT nCmdID, INT nID, HWND hWnd)
{
	return m_pMainDlg->OnScRestore(nCmdID,nID,hWnd);
}

LRESULT CHomeViewUIHandler::OnScClose(UINT nCmdID, INT nID, HWND hWnd)
{
	return m_pMainDlg->OnScClose(nCmdID,nID,hWnd);
}



void	CHomeViewUIHandler::InitLeftDiagnoseItemList()
{
	for(int i=0;i<2;i++)
	{
		m_pMainDlg->SetItemVisible(IDC_SCAN_ITEM_START+i*4,TRUE);
		m_pMainDlg->SetItemVisible(IDC_SCAN_ITEM_START+i*4+1,FALSE);
		m_pMainDlg->SetItemColorAttribute(IDC_SCAN_ITEM_START+i*4+2,"crtext",COL_SCAN_ITEM_DISABLE);
		m_pMainDlg->SetItemColorAttribute(IDC_SCAN_ITEM_START+i*4+3,"crtext",COL_SCAN_ITEM_DISABLE);
		m_pMainDlg->SetItemText(IDC_SCAN_ITEM_START+i*4+3,_T("�������"));

		
	}
}

LRESULT	CHomeViewUIHandler::OnFeedBack(UINT, INT, HWND)
{
	::ShellExecute(NULL, _T("open"), _T("http://bbs.code.ijinshan.com/forumdisplay.php?fid=11"), NULL, NULL, SW_SHOWNORMAL);	

	return TRUE;
}

LRESULT	CHomeViewUIHandler::OnCheckForNewVersion(UINT, INT, HWND)
{
	::ShellExecute(NULL, _T("open"), _T("http://bbs.code.ijinshan.com/forumdisplay.php?fid=11"), NULL, NULL, SW_SHOWNORMAL);

	return TRUE;
}

LRESULT	CHomeViewUIHandler::OnAbout(UINT, INT, HWND)
{


	return TRUE;
}

LRESULT	CHomeViewUIHandler::OnContactUS(UINT, INT, HWND)
{


	return TRUE;
}

void	CHomeViewUIHandler::OnExportDiagnoseResult()
{

}


int CHomeViewUIHandler::_GetProcessPos(IN int nAvgSpeed)
{
	float fRet = 0;
	float nTrueSpeed = nAvgSpeed * 8;

	if (nTrueSpeed <= 256)
		fRet = 0 + nTrueSpeed * 10 / 256 ;
	else if (nTrueSpeed <= 256 * 2)
		fRet = 10 + (nTrueSpeed - 256) * 10.0 / 256 ;
	else if (nTrueSpeed <= 256 * 4)
		fRet = 20 + (nTrueSpeed - 256 * 2) * 10.0 / (256 * 2) ;
	else if (nTrueSpeed <= 256 * 8)
		fRet = 30 + (nTrueSpeed - 256 * 4)* 10.0 / (256 * 4) ;
	else if (nTrueSpeed <= 256 * 16)
		fRet = 40 + (nTrueSpeed - 256 * 8)* 10.0 / (256 * 8) ;
	else if (nTrueSpeed <= 256 * 32)
		fRet = 50 + (nTrueSpeed - 256 * 16)* 10.0 / (256 * 16) ;
	else if (nTrueSpeed <= 256 * 64)
		fRet = 60 + (nTrueSpeed - 256 * 32)* 10.0 / (256 * 32) ;
	else if (nTrueSpeed > 256 * 64)
		fRet = 70;

	return (int)(fRet + 0.5);
}

// ��׼WTL�ؼ��¼�������ʾ
LRESULT	CHomeViewUIHandler::OnComboBoxSelectChange(DWORD whParam, DWORD wlParam, HWND lParam,BOOL bHandled)
{
	::MessageBox(NULL,_T("WTL��׼�ؼ�ComoboBox�����ݱ��ı䣨ѡ����仯��"),_T("��׼WTL�ؼ��¼�����"),MB_OK);

	return TRUE;
}