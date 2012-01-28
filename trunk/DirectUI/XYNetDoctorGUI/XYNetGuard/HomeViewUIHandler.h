
// 双网卡切换，最主要是的是使用 route change来修改metric为1，metric为1的会成为默认网关（Default Gateway）

#pragma once


#include "msgdefine.h"
#include "ListViewCtrlEx.h"




#define		WM_SYSTEMTRAYICON				(WM_USER + 1000)
#define		WM_FINISHMEASURESPEED			(WM_USER + 1001) //测速完成后，发送消息
#define		WM_FINISHMEASUREPROCESS			(WM_USER + 1002) //发送速度消息

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
	BOOL								m_bHasDiagnosed;				// 必须要是诊断后才导出诊断结果

private:
	CListViewCtrlEx						m_wndDiagnoseResult;
	int									m_nDiagnoseProcessPicNum;

	CComboBox							m_wndComboBox;

private:
	
	// 左侧扫描项的管理
private:
	void								InitLeftDiagnoseItemList();		// 初始化显示界面
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


	// 标准控件事件处理：ComboBox选中的内容改变时通知
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

		// 标准控件的事件处理: ComboBox选中的内容改变时通知
		COMMAND_HANDLER(IDC_DEMO_COMBOBOX_REALWND,CBN_SELCHANGE,OnComboBoxSelectChange)

		MSG_WM_TIMER(OnTimer)

	END_MSG_MAP()
};