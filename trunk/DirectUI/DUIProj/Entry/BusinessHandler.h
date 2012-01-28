#pragma once
#include <wtlhelper/whwindow.h>

class CMainDlg;

class CBusinessHandler
{
public:
	CBusinessHandler(CMainDlg* pMainDlg);
	~CBusinessHandler(void);

	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		 BK_NOTIFY_ID_COMMAND(IDC_LEFT_BTN_04, OnLeftBtn04Click)
	BK_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CContentUIManager)
		 MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)	
	END_MSG_MAP()

private:
	CMainDlg* m_pMainDlg;

public:
	void Init();

private:
	void OnLeftBtn04Click();
};
