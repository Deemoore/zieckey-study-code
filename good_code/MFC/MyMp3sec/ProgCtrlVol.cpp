// ProgCtrlVol.cpp : implementation file
//

#include "stdafx.h"
#include "MyMp3sec.h"
#include "ProgCtrlVol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProgCtrlVol

ProgCtrlVol::ProgCtrlVol()
{
	//m_nPos=-1500;
	//m_nStep=300;
	//m_nLower=-3000;
	m_nPos=50;
	m_nStep=10;
	m_nLower=0;
	m_nUpper=100;
	pDCBack=new CDC;
	pDCFore=new CDC;
	bmpBack.LoadBitmap(IDB_VOLUMEBACK);
	bmpFore.LoadBitmap(IDB_VOLUMEFORE);
}

ProgCtrlVol::~ProgCtrlVol()
{
}


BEGIN_MESSAGE_MAP(ProgCtrlVol, CStatic)
	//{{AFX_MSG_MAP(ProgCtrlVol)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgCtrlVol message handlers

void ProgCtrlVol::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_length=(float)m_nPos/(m_nUpper-m_nLower);
	GetClientRect(&m_rect);
	pDCBack->CreateCompatibleDC(&dc);
	pDCFore->CreateCompatibleDC(&dc);
	bmpBack.GetBitmap(&bmback);
	bmpFore.GetBitmap(&bmfore);
	pDCBack->SelectObject(bmpBack);
	dc.StretchBlt(0,0,m_rect.Width(),m_rect.Height(),pDCBack,0,0,bmback.bmWidth,bmback.bmHeight,SRCCOPY);
	(CBitmap*)pDCFore->SelectObject(bmpFore);
	dc.StretchBlt(0,0,m_rect.Width()*m_length,m_rect.Height(),pDCFore,0,0,bmfore.bmWidth*m_length,bmfore.bmHeight,SRCCOPY);
	pDCBack->DeleteDC();
	pDCFore->DeleteDC();
	// Do not call CStatic::OnPaint() for painting messages
}

int ProgCtrlVol::StepIt()
{
	CRect tempRect=m_rect;
	m_nPos+=m_nStep;
	if(m_nPos>m_nUpper)
	{
		m_nPos=m_nUpper;
	}
	InvalidateRect(&tempRect);
	return 1;
}

int ProgCtrlVol::StepItt()
{
	CRect tempRect=m_rect;
	m_nPos-=m_nStep;
	if(m_nPos<m_nLower)
	{
		m_nPos=m_nLower;
	}
	InvalidateRect(&tempRect);
	return 1;
}
