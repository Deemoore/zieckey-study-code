//////////////////////////////////////////////////////////////////////////
//  Class Name: BKPngPool
// Description: PNG Pool
//     Creator: ZhangXiaoxuan
//     Version: 2010.2.24 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <GdiPlus.h>
#pragma comment(lib, "gdiplus.lib")

#include <atlcoll.h>

#include "bkresutil.h"

// BkPngPool中的PNG图片只从程序的自定义资源和资源目录中获取
// 已通过修改BkResManager::LoadResource来支持从资源DLL中获取自定义PNG图片资源

class BkPngPool
{
public:
    BkPngPool()
    {
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
    }
    virtual ~BkPngPool()
    {
        Gdiplus::Image *pImg = NULL;

        POSITION pos = m_mapPng.GetStartPosition();

        while (pos != NULL) 
        {
            pImg = m_mapPng.GetNextValue(pos);
            if (pImg)
                delete pImg;
        }

        m_mapPng.RemoveAll();

        Gdiplus::GdiplusShutdown(m_gdiplusToken);
    }

    typedef CAtlMap<UINT, Gdiplus::Image *> _TypePngPool;

    static Gdiplus::Image* Get(UINT uResID)
    {
        _TypePngPool::CPair* pPairRet = _Instance()->m_mapPng.Lookup(uResID);
        Gdiplus::Image* pImg = NULL;

        if (NULL == pPairRet)
        {
            _LoadPNGImageFromResourceID(uResID, pImg);
            if (pImg)
                _Instance()->m_mapPng[uResID] = pImg;
        }
        else
            pImg = pPairRet->m_value;

        return pImg;
    }

    static size_t GetCount()
    {
        return _Instance()->m_mapPng.GetCount();
    }

	static void Clear()
	{
		 POSITION			pos = _Instance()->m_mapPng.GetStartPosition();
		 Gdiplus::Image*	pImg;

        while (pos != NULL) 
        {
            pImg = _Instance()->m_mapPng.GetNextValue(pos);
            if (pImg)
                delete pImg;
        }

        _Instance()->m_mapPng.RemoveAll();
	}

protected:

    ULONG_PTR m_gdiplusToken;

    _TypePngPool m_mapPng;

    static BkPngPool* ms_pInstance;

    static BkPngPool* _Instance()
    {
        if (!ms_pInstance)
            ms_pInstance = new BkPngPool;
        return ms_pInstance;
    }

	// PNG图片只从程序的自定义资源和资源目录中获取
    static BOOL _LoadPNGImageFromResourceID(UINT nID, Gdiplus::Image* &pImg)
    {
        CStringA strResource;

        BOOL bRet = BkResManager::LoadResource(nID, strResource, BKRES_PNG_TYPE);
        int len = strResource.GetLength();

        HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, len);
        BYTE* pMem = (BYTE*)::GlobalLock(hMem);

        memcpy(pMem, (LPCSTR)strResource, len);

        IStream* pStm = NULL;
        ::CreateStreamOnHGlobal(hMem, FALSE, &pStm);

        pImg = Gdiplus::Image::FromStream(pStm);

        ::GlobalUnlock(hMem);
        pStm->Release();

        return TRUE;
    }
};

__declspec(selectany) BkPngPool* BkPngPool::ms_pInstance = NULL;