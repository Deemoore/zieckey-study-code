#include "stdafx.h"
#include "XYNetGuard.h"
#include "XYNetGuardmaindlg.h"
#include "NetConfigUIHandler.h"
#include "XYNetGuardmsgbox.h"


// 初始化UIHandler
void CNetConfigUIHandler::Init()
{
	m_NetworkDeviceListView.Create( 
		m_pMainDlg->GetViewHWND(), NULL, NULL, 
		WS_CLIPCHILDREN | WS_CHILD |WS_VSCROLL | LBS_OWNERDRAWVARIABLE| LBS_HASSTRINGS , 
		0, IDC_NETCONFIG_NETWORK_DEVICE_LISTVIEW, NULL);
	m_NetworkDeviceListView.CreateX();

}

// 主界面第一次显示时，扫描网络设备等信息
void CNetConfigUIHandler::FirstShow()
{
	if(m_bFirstShowed)
		return;
	else
		m_bFirstShowed = TRUE;

	
	ShowNetDeviceList();

}

void	CNetConfigUIHandler::ShowNetDeviceList()
{
	LP_XY_NETWORK_DEVICE_INFO_DATA	pNetworkDeviceInfoData;
	CString							pszRichTextValue;

	pNetworkDeviceInfoData	= new XY_NETWORK_DEVICE_INFO_DATA;
	
	pNetworkDeviceInfoData->bDeviceEnabled			= TRUE;
	pNetworkDeviceInfoData->nNetworkType			= PPPoE_NETWORK_DEVICE;
	pNetworkDeviceInfoData->pszConnectionName		= _T("宽带连接");
	pNetworkDeviceInfoData->pszIPAddress			= _T("10.10.10.10");
	pNetworkDeviceInfoData->pszGateway				= _T("10.10.10.20");
	pNetworkDeviceInfoData->pszDeviceDesc			= _T("PPPoE");

	m_NetworkDeviceListView.InsertItemX(pNetworkDeviceInfoData);
}
