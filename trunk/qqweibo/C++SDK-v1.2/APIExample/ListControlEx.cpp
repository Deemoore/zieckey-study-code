// ListControlEx.cpp : implementation file
//

#include "stdafx.h"
#include "TXAPITool.h"
#include "ListControlEx.h"

#define CONLUMN_LEFTWIDTH   20

// CListControlEx dialog

IMPLEMENT_DYNAMIC(CListControlEx, CListCtrl)

CListControlEx::CListControlEx()
{
}

CListControlEx::~CListControlEx()
{
}


BEGIN_MESSAGE_MAP(CListControlEx, CListCtrl)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(ORANGE_LVN_ENDEDIT, OnEndEdit)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

void CListControlEx::Init(TYPE_CONLUMN eType)
{
	DeleteAllItems();

	RECT rcWin;
	GetWindowRect(&rcWin);

	if(eType == type_Header)
	{
		int nLen = (rcWin.right - rcWin.left) / 2 - CONLUMN_LEFTWIDTH - 10;
		InsertColumn(0,L"",LVCFMT_LEFT,CONLUMN_LEFTWIDTH);
		InsertColumn(1,L"name",LVCFMT_LEFT,nLen);
		InsertColumn(2,L"value",LVCFMT_LEFT,nLen);
	}
	else if(eType == type_Image)
	{
		InsertColumn(0,L"",LVCFMT_LEFT,CONLUMN_LEFTWIDTH);
		InsertColumn(1,L"picture",LVCFMT_LEFT,rcWin.right - rcWin.left - CONLUMN_LEFTWIDTH - 10);
	}
}

void CListControlEx::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	// TODO:  ������Ĵ����Ի���ָ����
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	LVITEM lvi = {0};
	lvi.mask = LVIF_STATE;
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED ;
	lvi.iItem = lpDrawItemStruct->itemID;
	BOOL bGet = GetItem(&lvi);

	BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)||((lvi.state & LVIS_SELECTED) && ((GetFocus() == this)|| (GetStyle() & LVS_SHOWSELALWAYS))));

	CRect rcBack = lpDrawItemStruct->rcItem;

	if( bHighlight ) //������ʾ
	{
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
	}
	else
	{

		pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
		pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_WINDOW)));


	}
	//�����ı�
	CString strText=L"";
	CRect rcItem;
	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
	{
		for (int i = 0; i < GetHeaderCtrl()-> GetItemCount();i++)
		{            
			if ( !GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem ))
				continue;
			strText = GetItemText( lpDrawItemStruct->itemID, i );

			pDC->DrawText(strText,strText.GetLength(), &rcItem, DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_BOTTOM);
		}
	}
}

void CListControlEx::PreSubclassWindow()
{
	SetExtendedStyle(GetExtendedStyle()|LVS_EX_GRIDLINES| LVS_EX_CHECKBOXES |LVS_OWNERDRAWFIXED); 
	CListCtrl::PreSubclassWindow();
}

void CListControlEx::OnLButtonDown( UINT nFlags, CPoint point )
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CListCtrl::OnLButtonDown(nFlags, point);
	CRect rcCtrl;
	LVHITTESTINFO lvhti;
	lvhti.pt = point;
	m_nItem =SubItemHitTest(&lvhti);
	if (m_nItem == -1) return;
	m_nSubItem = lvhti.iSubItem;
	GetSubItemRect(m_nItem,m_nSubItem,LVIR_LABEL,rcCtrl);
	if (m_Edit_ctlItem.m_hWnd == NULL)
	{
		m_Edit_ctlItem.Create(ES_AUTOHSCROLL|WS_CHILD|ES_LEFT|ES_WANTRETURN|WS_BORDER,CRect(0,0,0,0),this,99);
		m_Edit_ctlItem.ShowWindow(SW_HIDE);

		m_FontItem.CreateStockObject(DEFAULT_GUI_FONT);
		m_Edit_ctlItem.SetFont(&m_FontItem);
		m_FontItem.DeleteObject();

	}
	CString strItem=GetItemText(m_nItem,m_nSubItem);
	m_Edit_ctlItem.MoveWindow(&rcCtrl);
	m_Edit_ctlItem.ShowWindow(SW_SHOW);
	m_Edit_ctlItem.SetWindowText(strItem);
	m_Edit_ctlItem.SetFocus();
	m_Edit_ctlItem.SetSel(-1); 
}

LRESULT CListControlEx::OnEndEdit( WPARAM wParam,LPARAM lParam )
{
	CString strText;
	m_Edit_ctlItem.GetWindowText(strText);
	SetItemText(m_nItem,m_nSubItem,strText);
	m_Edit_ctlItem.ShowWindow(SW_HIDE);

	return 0;
}

void CListControlEx::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	
	LVHITTESTINFO lvhti;
	lvhti.pt = point;
	int nItem = SubItemHitTest(&lvhti);
	if (nItem == -1)//����һ��
	{
		InsertItem(GetItemCount()+1,L"");
	}
	
}

void CListControlEx::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	Invalidate();
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CListControlEx::InsertOneItem()
{
	InsertItem(GetItemCount()+1,L"");
}

void CListControlEx::DelCheckedItem()
{
	for (int i = 0; i < GetItemCount();i++)
	{
		BOOL bCheck = GetCheck(i);
		if(bCheck == TRUE)
		{
			DeleteItem(i);
			i--;
		}
	}
}

void CListControlEx::GetColumnData( int nColumn,CStringArray & strArryData )
{
	int nCount = GetItemCount();

	for (int i = 0; i < nCount; i++)
	{
		strArryData.Add(GetItemText(i,nColumn));
	}
}