


#pragma once

#include "msgdefine.h"
#include "NetworkDevice.h"
#include "NetCardListView.h"


class CXYNetGuardMainDlg;
class CNetConfigUIHandler 
{
public:
	CNetConfigUIHandler(CXYNetGuardMainDlg* refDialog)
		: m_pMainDlg(refDialog)
		, m_bFirstShowed(FALSE)
	{
	}

	virtual ~CNetConfigUIHandler()
	{
		
	}

public:
	void					Init();
	void					FirstShow();
	
protected:
	CXYNetGuardMainDlg*		m_pMainDlg;
	CNetworkDeviceListView	m_NetworkDeviceListView;
	BOOL					m_bFirstShowed;

protected:
	void					ShowNetDeviceList();

public:
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)


	BK_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CNetConfigUIHandler)

		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)

	END_MSG_MAP()
};