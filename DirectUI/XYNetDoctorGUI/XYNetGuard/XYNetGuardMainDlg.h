#pragma once

#include <wtlhelper/whwindow.h>
#include "msgdefine.h"
#include "XYNetGuardmsgbox.h"
#include "XYNetGuardUIHandler.h"
#include "HomeViewUIHandler.h"
#include "NetConfigUIHandler.h"

#include <bkres/bkresutil.h>



class CXYNetGuardMainDlg
    : public CBkDialogImpl<CXYNetGuardMainDlg>
    , public CWHRoundRectFrameHelper<CXYNetGuardMainDlg>
{
public:
    CXYNetGuardMainDlg();
    ~CXYNetGuardMainDlg();

public:
	CXYNetGuardUIHandler*       m_pNetGuardUIHandler;
	CHomeViewUIHandler*			m_pHomeViewUIHandler;
	CNetConfigUIHandler*		m_pNetConfigUIHandler;
	
private:
	NOTIFYICONDATA				m_NotifyIconData;

	void						InitTray();
	void						DelTray();
	
public:
	LRESULT						OnSystemTrayIcon(UINT, WPARAM wParam, LPARAM lParam);
	LRESULT						OnScRestore(UINT, INT, HWND);
	LRESULT						OnScClose(UINT, INT, HWND);
public:
	void						EndDialog(UINT uRetCode);
    void						OnBkBtnClose();
    void						OnBkBtnMenu();
    void						OnBkBtnMin();
	void						OnBkBtnFeedBack();



	void						OnSysCommand(UINT nID, CPoint point);
	BOOL						OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/);
	LRESULT						OnDestroy();
	
public:
	
    BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
        BK_NOTIFY_ID_COMMAND(IDC_BTN_SYS_CLOSE, OnBkBtnClose)
        BK_NOTIFY_ID_COMMAND(IDC_BTN_SYS_MENU,	OnBkBtnMenu)
        BK_NOTIFY_ID_COMMAND(IDC_BTN_SYS_MIN,	OnBkBtnMin)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_SYS_FEEDBACK,OnBkBtnFeedBack)
		
	BK_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX_DECLARE(CXYNetGuardMainDlg)
};