#pragma once

#include <bkwin/bkwndpanel.h>
#include "bkwnddrawermenuctrl.h"

class CExtendCtrlFactory : public IBkCtrlFactory
{
public:
	virtual CBkWindow* CreateControl(LPCSTR pszName)
	{
		CBkWindow* pNewWindow = NULL;
		
		pNewWindow = CBkDrawerMenuCtrl::CheckAndNew(pszName);
		if (pNewWindow) return pNewWindow;

		pNewWindow = CBkMenu::CheckAndNew(pszName);
		if (pNewWindow) return pNewWindow;

		pNewWindow = CBkDrawerMenuHead::CheckAndNew(pszName);
		if (pNewWindow) return pNewWindow;

		return NULL;
	}
};
