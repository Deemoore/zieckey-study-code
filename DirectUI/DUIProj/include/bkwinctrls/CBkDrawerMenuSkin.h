#pragma once

#include <tinyxml/tinyxml.h>
#include <bkwin/bkobject.h>
#include <bkwin/bkimage.h>
#include <bkres/bkpngpool.h>
#include <bkwin/bkskin.h>

class CABDrawerMenuSkin : public CBkSkinBase
{
	BKOBJ_DECLARE_CLASS_NAME(CABDrawerMenuSkin, "abdrawermenu")
}

// BkWin Factory
class CABSkinFacotry : public IBkSkinFactory
{
public:
	virtual CBkSkinBase* CreateSkin(LPCSTR lpszName)
	{
		CBkSkinBase* pSkin = NULL;

		pSkin = CABDrawerMenuSkin::CheckAndNew(lpszName);
		if (pSkin) return pSkin;

		return NULL;
	}
};

