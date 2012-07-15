// ProgCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyMp3sec.h"
#include "ProgCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProgCtrl

ProgCtrl::ProgCtrl()
{
	pDCBack=new CDC;
	//pDCFore=new CDC;
	pDCGogogo=new CDC;
	bmpBack.LoadBitmap(IDB_PROGRESSBACK);
	//bmpFore.LoadBitmap(IDB_PROGRESSFORE);
	bmpGogogo.LoadBitmap(IDB_MAN);
}

ProgCtrl::~ProgCtrl()
{
}


BEGIN_MESSAGE_MAP(ProgCtrl, CStatic)
	//{{AFX_MSG_MAP(ProgCtrl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgCtrl message handlers

void ProgCtrl::SetRange(int nLower, int nUpper)
{
	m_nLower=nLower;
	m_nUpper=nUpper;
}

int ProgCtrl::SetStep(int nStep)
{
	m_nStep=nStep;
	return 1;
}

int ProgCtrl::StepIt()
{
	CRect tempRect=m_rect;
	tempRect.left=(long)m_length*m_rect.Width();
	m_nPos+=m_nStep;
	
	if(m_nPos>=m_nUpper)
	{
		m_nPos=0;
		InvalidateRect(&tempRect);
		return 1;
	}
	else
	{
		InvalidateRect(&tempRect);
		return 1;
	}
	
	InvalidateRect(&tempRect);
	return 1;
}

int ProgCtrl::SetPos(int nPos)
{
	m_nPos=nPos;
	return 1;
}

void ProgCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_length = (float)m_nPos/(m_nUpper-m_nLower);
	GetClientRect(&m_rect);
	pDCBack->CreateCompatibleDC(&dc);
	//pDCFore->CreateCompatibleDC(&dc);
	bmpBack.GetBitmap(&bmback);
	//bmpFore.GetBitmap(&bmfore);
	pDCBack->SelectObject(bmpBack);
	dc.StretchBlt(0,0,m_rect.Width(),m_rect.Height(),pDCBack,0,0,bmback.bmWidth,bmback.bmHeight,SRCCOPY);
	//(CBitmap*)pDCFore->SelectObject(bmpFore);
	//dc.StretchBlt(0,0,m_rect.Width()*m_length,m_rect.Height(),pDCFore,0,0,bmfore.bmWidth*m_length,bmfore.bmHeight,SRCCOPY);
	
	pDCGogogo->CreateCompatibleDC(&dc);
	bmpGogogo.GetBitmap(&bmgogogo);
	pDCGogogo->SelectObject(bmpGogogo);
	dc.StretchBlt(m_rect.Width()*m_length,0,m_rect.Height(),m_rect.Height(),pDCGogogo,0,0,bmgogogo.bmWidth,bmgogogo.bmHeight,SRCCOPY);

	pDCBack->DeleteDC();
	//pDCFore->DeleteDC();
	pDCGogogo->DeleteDC();
	// Do not call CStatic::OnPaint() for painting messages
}

int ProgCtrl::GetPos()
{
	return m_nPos;
}
