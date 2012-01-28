#pragma once

#include <wtlhelper/whwindow.h>

class CBusinessHandler;

class CMainDlg
	: public CBkDialogImpl<CMainDlg>
	, public CWHRoundRectFrameHelper<CMainDlg>
{
public:
	CMainDlg(void);
	~CMainDlg(void);

BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
    BK_NOTIFY_ID_COMMAND(IDC_HOME_BTN_CLOSE, OnBkBtnClose)
    BK_NOTIFY_ID_COMMAND(IDC_HOME_BTN_MIN,	OnBkBtnMin)
/* 
	BK_NOTIFY_ID_COMMAND(IDC_HEAD_BTN_00, OnBkBtn1Clicked)
	BK_NOTIFY_ID_COMMAND(IDC_HEAD_BTN_01, OnBkBtn2Clicked)
	BK_NOTIFY_ID_COMMAND(IDC_HEAD_BTN_02, OnBkBtn3Clicked)
	BK_NOTIFY_ID_COMMAND(IDC_HEAD_BTN_03, OnBkBtn4Clicked)
	BK_NOTIFY_ID_COMMAND_EX(IDC_BODY_LEFT_BTN_BASE, (IDC_BODY_LEFT_BTN_BASE+100), OnBkLeftBtnClick)*/
BK_NOTIFY_MAP_END()

public:
	BOOL OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/);
	BEGIN_MSG_MAP_EX_DECLARE(CMainDlg)

protected:
	CBusinessHandler* m_pBusinessHandler;

private:
	void OnBkBtnClose();
    void OnBkBtnMin();
};
