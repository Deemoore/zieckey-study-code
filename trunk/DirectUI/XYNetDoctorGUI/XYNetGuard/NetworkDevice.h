#pragma once

#define		WIRED_NETWORK_DEVICE			0
#define		WIRELESS_NETWORK_DEVICE			1
#define		PPPoE_NETWORK_DEVICE			2
#define		VIRTUAL_NETWORK_DEVICE			3

typedef		struct		XY_NETWORK_DEVICE_INFO_DATA
{
	CString						pszConnectionName;			

	unsigned	int				nNetworkType;				

	CString						pszDeviceDesc;				
	CString						pszDeviceFriendlyDesc;		
	
	BOOL						bDeviceEnabled;				
	DWORD						dwDeviceStatus;				

	CString						pszIPAddress;				
	CString						pszNetMask;
	CString						pszGateway;

	BOOL						bAutoObtainDNS;
	CString						pszPrimaryDNS;
	CString						pszSecondaryDNS;

	BOOL						bUsingDHCP;
	CString						pszDHCPIPAddress;

	CString						pszMACAddress;

	XY_NETWORK_DEVICE_INFO_DATA()
	{
		
		pszConnectionName.Empty();
		pszDeviceDesc.Empty();
		pszDeviceFriendlyDesc.Empty();
		

		bDeviceEnabled		= TRUE;

		pszIPAddress.Empty();
		pszNetMask.Empty();
		pszGateway.Empty();
		pszPrimaryDNS.Empty();
		pszSecondaryDNS.Empty();

		bUsingDHCP = FALSE;
		pszDHCPIPAddress.Empty();

		pszMACAddress.Empty();
	}
	

}*LP_XY_NETWORK_DEVICE_INFO_DATA;
