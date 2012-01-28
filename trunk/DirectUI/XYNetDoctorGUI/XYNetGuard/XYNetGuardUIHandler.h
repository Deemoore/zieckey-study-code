
#pragma once

#include "msgdefine.h"

#define STATE_RUNOPT_NULL		0
#define STATE_RUNOPT_SCAN		1
#define STATE_RUNOPT_CANCEL		2

class CXYNetGuardMainDlg;
class CXYNetGuardUIHandler 
{
public:
	CXYNetGuardUIHandler(CXYNetGuardMainDlg* refDialog)
		: m_dlg(refDialog)
		, m_bFirstShowed(FALSE)
		, m_bIsDefaultSkin(TRUE)
	{
	}

	virtual ~CXYNetGuardUIHandler()
	{
		
	}

public:
	void Init();
	void FirstShow();
	
protected:
	CXYNetGuardMainDlg*		m_dlg;
	
	BOOL					m_bFirstShowed;
	BOOL					m_bIsDefaultSkin;

public:
	BOOL					OnMainSubTypeSelChange(int nTabItemIDOld, int nTabItemIDNew);

	//void					OnTimer(UINT_PTR nIDEvent);

public:
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		//BK_NOTIFY_TAB_SELCHANGE(IDC_TAB_MAIN_TOP,OnMainSubTypeSelChange)
	BK_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CXYNetGuardUIHandler)
		//MSG_WM_TIMER(OnTimer)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		//MESSAGE_HANDLER_EX(MSG_SYSOPT_REFRESH_ONEKEYOPT,	OnRefreshOnekeyOpt)
	END_MSG_MAP()
};