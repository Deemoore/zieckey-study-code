//////////////////////////////////////////////////////////////////////////
//   File Name: bkwnddrawermenuctrl.h
// Description: Drawer Menu Control
//     Creator: Luckzj
//     Version: 2011.1.1 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once
#define _WTL_NO_CSTRING
#include "../include/bkwin/bkwndnotify.h"
#include <tinyxml/tinyxml.h>
#include <bkwin/bkobject.h>
#include <bkwin/bkimage.h>
#include <bkres/bkpngpool.h>
#include <bkwin/bkskin.h>
#include <bkwin/bkobject.h>
#include <bkwin/bkwnddlg.h>

class CBkDrawerMenuHead : public CBkWindow
{
	BKOBJ_DECLARE_CLASS_NAME(CBkDrawerMenuHead, "drawermenuhead")

public:
	CBkDrawerMenuHead()
		: m_nHeight(-1)
		, m_hParentCtrl(0)
	{
	}

	~CBkDrawerMenuHead()
	{
	}

protected:
	HBKWND m_hParentCtrl;
	CString m_strText;
	int     m_nHeight;

public:
	void SetParentCtrl(HBKWND hBkWnd)
	{
		m_hParentCtrl = hBkWnd;
	}
	
	int GetHeight()
	{
		int nHeight = m_nHeight;
		if (nHeight == -1)
		{
			if (m_style.m_strSkinName.IsEmpty() == FALSE)
			{
				CBkSkinBase* pSkin = BkSkin::GetSkin(m_style.m_strSkinName);
				if (pSkin)
				{
					nHeight = pSkin->GetSkinSize().cy;
				}
			}
		}

		if (nHeight == -1) 
		{
			nHeight = 0;
		}
		return nHeight;
	}
	void OnLButtonUp(UINT nFlags, CPoint point)
	{
		CBkWindow* pParent = BkWnds::GetWindow(m_hParentCtrl);
		if (pParent)
		{
			BKNMCOMMAND nms;
            nms.hdr.code = BKNM_COMMAND;
			nms.hdr.hwndFrom = this->GetContainer();
			nms.hdr.idFrom = m_hBkWnd;
			nms.uItemID = (UINT_PTR)1234;
            nms.szItemClass = this->GetObjectClass();

			LRESULT lRet = pParent->BkSendMessage(WM_NOTIFY, (LPARAM)nms.hdr.idFrom, (WPARAM)&nms);
		}
	}

	// Draw inner text default
    void OnPaint(CDCHandle dc)
    {
        BkDCPaint BkDC;

        BeforePaint(dc, BkDC);

        dc.DrawText(m_strText, m_strText.GetLength(), BkDC.rcClient, m_style.m_nTextAlign);

        AfterPaint(dc, BkDC);
    }

	BKWIN_DECLARE_ATTRIBUTES_BEGIN()
        BKWIN_INT_ATTRIBUTE("height", m_nHeight, FALSE)
		BKWIN_TSTRING_ATTRIBUTE("text", m_strText, FALSE)
    BKWIN_DECLARE_ATTRIBUTES_END()

	BKWIN_BEGIN_MSG_MAP()
		MSG_WM_LBUTTONUP(OnLButtonUp)
    BKWIN_END_MSG_MAP()
};

// menu item
class CBkMenu : public CBkDialog
{
	 BKOBJ_DECLARE_CLASS_NAME(CBkMenu, "drawermenu")

protected:
	CBkMenu*                m_pParentMenu;
	CAtlList<CBkMenu*>		m_listMenus;
	HBKWND                  m_hParentCtrl;
	int                     m_nHeight;
	CString                 m_strText;
	COLORREF                m_crbg;

	// 表示此控件是否被展开
	bool    m_bExtended;

public:
	CBkMenu()
		: m_nHeight(-1)
		, m_pParentMenu(NULL)
		, m_bExtended(false)
	{
	}

	~CBkMenu()
	{
	}

	int GetHeight()
	{
		int nHeight = m_nHeight;
		if (nHeight == -1)
		{
			if (!m_style.m_strSkinName.IsEmpty())
			{
				CBkSkinBase* pSkin = BkSkin::GetSkin(m_style.m_strSkinName);
				SIZE size = pSkin->GetSkinSize();
				m_nHeight = size.cy;
			}
		}

		return nHeight;
	}
	CBkMenu* GetParentMenu()
	{
		return m_pParentMenu;
	}
	bool IsExtended()
	{
		return m_bExtended;
	}
	CString GetText()
	{
		return m_strText;
	}

	void AddSubMenu(CBkMenu* pSubMenu)
	{
		pSubMenu->m_pParentMenu = this;
		m_listMenus.AddTail(pSubMenu);
	}
	void SetMenuVisible(BOOL bVisible)
	{
		SetVisible(bVisible);
		POSITION pos = m_listMenus.GetHeadPosition();
		while (pos != NULL)
		{
			CBkMenu *pBkWndChild = m_listMenus.GetNext(pos);
			pBkWndChild->SetVisible(bVisible);
			pBkWndChild->m_bExtended = false;

		}

		// if visible, reposition this control
		if (bVisible)
		{
			m_bExtended = true;

			// set parent visible
			CBkMenu* pParentMenu = GetParentMenu();
			while(pParentMenu)
			{
				pParentMenu->SetVisible(TRUE);
				pParentMenu = pParentMenu->GetParentMenu();
			}

			RepositionSubMenus();
		}
	}

	bool HasSubButton()
	{
		return (m_listMenus.GetCount() != 0);
	}
	virtual BOOL Load(TiXmlElement* pTiXmlElem)
	{
		if (!CBkWindow::Load(pTiXmlElem))
			return FALSE;

		BOOL bRet = LoadChilds(pTiXmlElem->FirstChildElement());

		if (bRet)
		{
			POSITION pos = m_lstWndChild.GetHeadPosition();
			while (pos != NULL)
			{
				CBkWindow *pBkWndChild = m_lstWndChild.GetNext(pos);

				if (!strncmp(pBkWndChild->GetObjectClass(), this->GetObjectClass(), 1024))
				{
					CBkMenu* pSubMenu = static_cast<CBkMenu*>(pBkWndChild);
					if (pSubMenu)
					{
						AddSubMenu(pSubMenu);
					}
				}
			}

		}
	}

	void SetContainer(HWND hWndContainer)
	{
		__super::SetContainer(hWndContainer);
		POSITION pos = m_listMenus.GetHeadPosition();
		while (pos != NULL)
        {
            CBkMenu *pBkWndChild = m_listMenus.GetNext(pos);

            if (pBkWndChild)
            {
                pBkWndChild->SetContainer(hWndContainer);
            }
        }
	}

	void SetParentCtrl(HBKWND hParentCtrl)
	{
		m_hParentCtrl = hParentCtrl;
		POSITION pos = m_listMenus.GetHeadPosition();
		while (pos != NULL)
        {
            CBkMenu *pBkWndChild = m_listMenus.GetNext(pos);

            if (pBkWndChild)
            {
                pBkWndChild->SetParentCtrl(hParentCtrl);
            }
        }
	}

	void OnDestroy()
	{
		POSITION pos = m_listMenus.GetHeadPosition();
		while (pos != NULL)
        {
            CBkMenu *pBkWndChild = m_listMenus.GetNext(pos);

            if (pBkWndChild)
            {
				pBkWndChild->BkSendMessage(WM_DESTROY);
				delete pBkWndChild;
            }
        }

		m_listMenus.RemoveAll();
	}
	void RepositionSubMenus()
	{
		int nHeight = 0;
		POSITION pos = m_listMenus.GetHeadPosition();
		while (pos != NULL)
		{
			CBkMenu *pBkWndChild = m_listMenus.GetNext(pos);

			if (pBkWndChild)
			{
				int top = nHeight;
				int bottom = top + pBkWndChild->GetHeight();

				// set attribute
				char posBuf[1024];
				sprintf(posBuf, "0,%d,-0,%d", top, bottom);
				pBkWndChild->SetAttribute("pos", posBuf, FALSE);

				nHeight = bottom;
			}
		}
	}

	void OnLButtonUp(UINT nFlags, CPoint point)
	{
		CBkWindow* pParent = BkWnds::GetWindow(m_hParentCtrl);
		if (pParent)
		{
			BKNMCOMMAND nms;
            nms.hdr.code = BKNM_COMMAND;
			nms.hdr.hwndFrom = this->GetContainer();
			nms.hdr.idFrom = this->m_hBkWnd;
			nms.uItemID = this->m_hBkWnd;
            nms.szItemClass = this->GetObjectClass();

			LRESULT lRet = pParent->BkSendMessage(WM_NOTIFY, (LPARAM)nms.hdr.idFrom, (WPARAM)&nms);
		}
	}

	virtual BOOL RedrawRegion(CDCHandle& dc, CRgn& rgn)
	{
		// 背景也不让绘制了
		if (m_bExtended == false)
			return __super::RedrawRegion(dc, rgn);

		return TRUE;
	}

	void OnPaint(CDCHandle dc)
	{
		// draw bkgnd
		if (m_bExtended == false)
		{
			if (!m_style.m_strSkinName.IsEmpty())
			{
				CBkSkinBase* pSkin = BkSkin::GetSkin(m_style.m_strSkinName);
				if (pSkin)
				{
					pSkin->Draw(dc, m_rcWindow, m_dwState);
				}
			}

			// draw text
			BkDCPaint BkDC;
			BeforePaint(dc, BkDC);
			dc.DrawText(m_strText, m_strText.GetLength(), m_rcWindow, m_style.m_nTextAlign);
			AfterPaint(dc, BkDC);
		}
	}
	
	void DrawAsExtendedMenu(CDCHandle dc)
	{
		dc.FillSolidRect(m_rcWindow, m_crbg);
		// draw items
		POSITION pos = m_listMenus.GetHeadPosition();
		while (pos != NULL)
		{
			CBkMenu *pBkWndChild = m_listMenus.GetNext(pos);

			if (pBkWndChild)
			{
				pBkWndChild->OnPaint(dc);
			}
		}
	}

	BKWIN_DECLARE_ATTRIBUTES_BEGIN()
        BKWIN_INT_ATTRIBUTE("height", m_nHeight, FALSE)
		BKWIN_COLOR_ATTRIBUTE("crbkgnd", m_crbg, FALSE)
		BKWIN_TSTRING_ATTRIBUTE("text", m_strText, FALSE)
    BKWIN_DECLARE_ATTRIBUTES_END()

	BKWIN_BEGIN_MSG_MAP()
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_PAINT(OnPaint)
    BKWIN_END_MSG_MAP()
};

class CBkDrawerMenuCtrl : public CBkDialog
{
	BKOBJ_DECLARE_CLASS_NAME(CBkDrawerMenuCtrl, "drawermenuctrl")

protected:
	CBkMenu* m_pMenu;
	CBkMenu* m_pCurrentMenu;
	CBkDrawerMenuHead* m_pHead;
	int      m_nWidth;
	CBkSkinBase*			m_pSkinFrame;

	// use this to draw animation
	CBitmap m_bmpAnimate;
	bool m_bAnimating;
	bool m_bMoveLeft;
	int  m_nAnimatePos;
	bool m_bAnimateInitialized;
	int  m_nTimerID;

public:
	CBkDrawerMenuCtrl()
		: m_pMenu(0)
		, m_pCurrentMenu(0)
		, m_nWidth(-1)
		, m_pSkinFrame(0)
		, m_pHead(0)
		, m_bAnimating(false)
		, m_bMoveLeft(true)
		, m_nAnimatePos(0)
		, m_bAnimateInitialized(false)
		, m_nTimerID(0)
	{
	}

	~CBkDrawerMenuCtrl()
	{
	}

	CBkMenu* GetCurrentMenu()
	{
		return m_pCurrentMenu;
	}
	virtual HBKWND BkGetHWNDFromPoint(POINT ptHitTest, BOOL bOnlyText)
	{
		HBKWND hBkWnd = __super::BkGetHWNDFromPoint(ptHitTest, bOnlyText);

		CBkWindow* pWindow = BkWnds::GetWindow(hBkWnd);
		if (pWindow && !strncmp(pWindow->GetObjectClass(), "drawermenu", 1024))
		{
			// 如果是子菜单，则测试是否被展开，如果展开了，则暴力干掉
			CBkMenu* pMenu = static_cast<CBkMenu*>(pWindow);
			if (pMenu && pMenu->IsExtended())
			{
				hBkWnd = m_hBkWnd;
			}
		}

		return hBkWnd;
	}
	BOOL LoadChilds(TiXmlElement* pTiXmlChildElem)
    {
        BOOL bFirstPage = TRUE;
        int nHeight = 0;

        BkSendMessage(WM_DESTROY);

        for (TiXmlElement* pXmlChild = pTiXmlChildElem; NULL != pXmlChild; pXmlChild = pXmlChild->NextSiblingElement())
        {
			CBkDrawerMenuHead* pHead = CBkDrawerMenuHead::CheckAndNew(pXmlChild->Value());
			if (pHead)
			{
				m_pHead = pHead;
				m_pHead->SetParent(m_hBkWnd);
				m_pHead->SetContainer(m_hWndContainer);
				m_pHead->Load(pXmlChild);
				m_pHead->SetParentCtrl(m_hBkWnd);
				this->m_lstWndChild.AddTail(m_pHead);
				continue;
			}

            CBkMenu *pNewChildWindow = CBkMenu::CheckAndNew(pXmlChild->Value());
			if (!pNewChildWindow)
                continue;

            pNewChildWindow->SetParent(m_hBkWnd);
            pNewChildWindow->SetContainer(m_hWndContainer);
            pNewChildWindow->Load(pXmlChild);
			this->m_lstWndChild.AddTail(pNewChildWindow);
            // pNewChildWindow->SetAttribute("pos", "0,0,-0,-0", TRUE);

			if (m_pMenu == NULL)
			{
				m_pMenu = pNewChildWindow;
			}
        }

		SetContainer(GetContainer());
		m_pMenu->SetParentCtrl(m_hBkWnd);
		SelectMenu(m_pMenu);

        return TRUE;
    }

    void SetContainer(HWND hWndContainer)
    {
        __super::SetContainer(hWndContainer);

		if (m_pMenu)
		{
			m_pMenu->SetContainer(hWndContainer);
		}
	}

	virtual BOOL Load(TiXmlElement* pTiXmlElem)
	{
		if (!CBkWindow::Load(pTiXmlElem))
			return FALSE;

		BOOL bRet = LoadChilds(pTiXmlElem->FirstChildElement());
		if (!bRet)
			return FALSE;

		return TRUE;
	}

	void OnDestroy()
    {
		if (m_pMenu)
			m_pMenu->BkSendMessage(WM_DESTROY);
    }

	void OnPaint(CDCHandle dc)
	{
		if (m_bAnimating == false)
		{
			m_pHead->OnPaint(dc);
			m_pCurrentMenu->DrawAsExtendedMenu(dc);
		}
		else if (m_bAnimateInitialized == false)
		{
			m_pHead->OnPaint(dc);
			m_pCurrentMenu->DrawAsExtendedMenu(dc);
			
			CDC memDC;
			memDC.CreateCompatibleDC(dc.m_hDC);
			HBITMAP hOldBmp = memDC.SelectBitmap(m_bmpAnimate.m_hBitmap);
			memDC.BitBlt((!m_bMoveLeft) ? 0 : m_rcWindow.Width(),0,m_rcWindow.Width(), m_rcWindow.Height(), dc.m_hDC, m_rcWindow.left, m_rcWindow.top, SRCCOPY);
			memDC.SelectBitmap(hOldBmp);
			m_bAnimateInitialized = true;

			OnPaint(dc);
		}
		else
		{
			CDC memDC;
			memDC.CreateCompatibleDC(dc.m_hDC);
			HBITMAP hOldBmp = memDC.SelectBitmap(m_bmpAnimate.m_hBitmap);
			int x = (m_bMoveLeft) ? m_nAnimatePos : m_rcWindow.Width() - m_nAnimatePos;
			dc.BitBlt(m_rcWindow.left, m_rcWindow.top, m_rcWindow.Width(), m_rcWindow.Height(), memDC.m_hDC, x, 0, SRCCOPY);
			memDC.SelectBitmap(hOldBmp);
			
		}
	}

	static void CALLBACK TimerProc(          
		HWND hwnd,
		UINT uMsg,
		UINT_PTR idEvent,
		DWORD dwTime
		)
	{
		if (idEvent == pThis->m_nTimerID)
		{
			if (pThis->IncrementAnimatePos() == FALSE)
			{
				::KillTimer(NULL, idEvent);
			}
		}
	}

	static CBkDrawerMenuCtrl* pThis;

	BOOL IncrementAnimatePos()
	{
		bool bRet = TRUE;
		m_nAnimatePos += 10;
		if (m_nAnimatePos >= m_rcWindow.Width())
		{
			// stop animate
			m_bAnimating = false;
			m_bAnimateInitialized = false;
			m_nAnimatePos = 0;
			bRet = FALSE;
		}

		NotifyInvalidate();
		return bRet;
	}
	void StartAnimate(bool bMoveLeft)
	{
		m_bMoveLeft = bMoveLeft;
		m_bAnimating = true;
		m_nAnimatePos = 0;

		// draw origin dc
		HDC hDC = ::GetDC(GetContainer());
		CDC memDC;
		memDC.CreateCompatibleDC(hDC);
		HBITMAP hOldBmp = memDC.SelectBitmap(m_bmpAnimate.m_hBitmap);
		memDC.BitBlt(m_bMoveLeft ? 0 : m_rcWindow.Width(),0,m_rcWindow.Width(), m_rcWindow.Height(), hDC, m_rcWindow.left, m_rcWindow.top, SRCCOPY);
		memDC.SelectBitmap(hOldBmp);
		ReleaseDC(GetContainer(), hDC);

		// wait for new image to be drawed
		m_bAnimateInitialized = false;

		if (pThis == NULL)
		{
			pThis = this;
		}
		this->m_nTimerID = ::SetTimer(NULL, 0, 10, TimerProc);
	}
	void SelectMenu(CBkMenu* pMenu)
	{
		// check parameter
		if (m_pMenu == NULL || pMenu == NULL || pMenu == m_pCurrentMenu) return;

		// hide all items
		if (m_pCurrentMenu)	m_pCurrentMenu->SetMenuVisible(FALSE);

		// start animate
		// m_pCurrentMenu == NULL means system is loading
		if (m_pCurrentMenu)
		{
			StartAnimate(pMenu->GetParentMenu() == m_pCurrentMenu);
		}

		// adjust menu position
		if (pMenu != m_pMenu)
		{
			pMenu->SetAttribute("pos", "0,0,-0,-0", FALSE);
		}

		pMenu->SetMenuVisible(TRUE);
		m_pCurrentMenu = pMenu;

		this->NotifyInvalidate();
	}

	LRESULT OnMenuClicked(LPNMHDR lpNMHDR)
	{
		HBKWND hFrom = (HBKWND)lpNMHDR->idFrom;
		CBkWindow* pWin = BkWnds::GetWindow(hFrom);

		if (!strncmp(pWin->GetObjectClass(), "drawermenuhead", 1024))
		{
			if (m_pCurrentMenu != m_pMenu && m_pCurrentMenu->GetParentMenu())
			{
				SelectMenu(m_pCurrentMenu->GetParentMenu());
			}
		}

		if (!strncmp(pWin->GetObjectClass(), "drawermenu", 1024))
		{
			CBkMenu* pMenu = static_cast<CBkMenu*>(pWin);

			if (pMenu && pMenu->HasSubButton())
			{
				SelectMenu(pMenu);
			}
		}
		return 0;
	}

	// create a dc here, is not very good a solution.
	// However, it works~
	void OnWindowPosChanged(LPWINDOWPOS lpWinPos)
	{
		__super::OnWindowPosChanged(lpWinPos);

		if (m_bmpAnimate.m_hBitmap)
		{
			m_bmpAnimate.DeleteObject();
		}

		HDC hDC = ::GetDC(GetContainer());
		m_bmpAnimate.CreateCompatibleBitmap(hDC, 2*m_rcWindow.Width(), m_rcWindow.Height());
		::ReleaseDC(GetContainer(), hDC);
	}
protected:
    BKWIN_BEGIN_MSG_MAP()
        MSG_WM_PAINT(OnPaint)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_SHOWWINDOW(OnShowWindow)
		MSG_WM_WINDOWPOSCHANGED(OnWindowPosChanged)
		NOTIFY_CODE_HANDLER_EX(BKNM_COMMAND,OnMenuClicked)
    BKWIN_END_MSG_MAP()

	BKWIN_DECLARE_ATTRIBUTES_BEGIN()
        BKWIN_INT_ATTRIBUTE("width", m_nWidth, FALSE)
    BKWIN_DECLARE_ATTRIBUTES_END()
};

_declspec(selectany) CBkDrawerMenuCtrl* CBkDrawerMenuCtrl::pThis = NULL;