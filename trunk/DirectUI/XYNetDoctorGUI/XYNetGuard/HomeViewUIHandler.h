
// ˫�����л�������Ҫ�ǵ���ʹ�� route change���޸�metricΪ1��metricΪ1�Ļ��ΪĬ�����أ�Default Gateway��

#pragma once


#include "msgdefine.h"
#include "ListViewCtrlEx.h"




#define		WM_SYSTEMTRAYICON				(WM_USER + 1000)
#define		WM_FINISHMEASURESPEED			(WM_USER + 1001) //������ɺ󣬷�����Ϣ
#define		WM_FINISHMEASUREPROCESS			(WM_USER + 1002) //�����ٶ���Ϣ

class CXYNetGuardMainDlg;


class CHomeViewUIHandler 
{
public:
	CHomeViewUIHandler(CXYNetGuardMainDlg* refDialog);
		

	virtual ~CHomeViewUIHandler();

public:
	void								Init();
	void								FirstShow();
	
protected:
	CXYNetGuardMainDlg*					m_pMainDlg;
	
	BOOL								m_bFirstShowed;

	BOOL								m_bIsExaming;
	BOOL								m_bHasDiagnosed;				// ����Ҫ����Ϻ�ŵ�����Ͻ��

private:
	CListViewCtrlEx						m_wndDiagnoseResult;
	int									m_nDiagnoseProcessPicNum;

	CComboBox							m_wndComboBox;

private:
	
	// ���ɨ����Ĺ���
private:
	void								InitLeftDiagnoseItemList();		// ��ʼ����ʾ����
	void								OnScanFinished();
	void								ShowDiagnoseResult();
	void								SetWebQoSStar(DWORD dwAvgSurferTime,int nSuccedCount);
	int									_GetProcessPos(IN int nAvgSpeed);
public:
	
	void								OnStartDiagnose();
	void								OnExportDiagnoseResult();

	void								OnAllDiagnoseFinished();

	void								OnTimer(UINT_PTR nIDEvent);
	void								OnSizeChanged(BOOL bMaxSize=TRUE);
private:
	LRESULT								OnSystemTrayIcon(UINT, WPARAM wParam, LPARAM lParam);
	LRESULT								OnScRestore(UINT, INT, HWND);
	LRESULT								OnScClose(UINT, INT, HWND);

	LRESULT								OnFeedBack(UINT, INT, HWND);
	LRESULT								OnCheckForNewVersion(UINT, INT, HWND);
	LRESULT								OnAbout(UINT, INT, HWND);
	LRESULT								OnContactUS(UINT, INT, HWND);


	// ��׼�ؼ��¼�����ComboBoxѡ�е����ݸı�ʱ֪ͨ
	LRESULT					OnComboBoxSelectChange(DWORD whParam, DWORD wlParam, HWND lParam,BOOL bHandled);

public:
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		BK_NOTIFY_ID_COMMAND(IDC_REDIAGNOSE_BUTTON,OnStartDiagnose)
		BK_NOTIFY_ID_COMMAND(IDC_EXPORT_DIAGNOSE_RESULT,OnExportDiagnoseResult)
	BK_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CHomeViewUIHandler)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		MESSAGE_HANDLER_EX(WM_SYSTEMTRAYICON, OnSystemTrayIcon)
		COMMAND_ID_HANDLER_EX(ID_TRAYMENU_OPENMAINWND, OnScRestore)
		COMMAND_ID_HANDLER_EX(ID_TRAYMENU_EXIT, OnScClose)

		COMMAND_ID_HANDLER_EX(ID_MAINMENU_FEEDBACK,OnFeedBack)
		COMMAND_ID_HANDLER_EX(ID_MAINMENU_UPDATE,OnCheckForNewVersion)
		COMMAND_ID_HANDLER_EX(ID_MAINMENU_ABOUT,OnAbout)
		COMMAND_ID_HANDLER_EX(ID_MAINMENU_CONTACT,OnContactUS)

		// ��׼�ؼ����¼�����: ComboBoxѡ�е����ݸı�ʱ֪ͨ
		COMMAND_HANDLER(IDC_DEMO_COMBOBOX_REALWND,CBN_SELCHANGE,OnComboBoxSelectChange)

		MSG_WM_TIMER(OnTimer)

	END_MSG_MAP()
};