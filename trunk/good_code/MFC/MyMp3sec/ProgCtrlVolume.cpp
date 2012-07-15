// ProgCtrlVolume.cpp : implementation file
//

#include "stdafx.h"
#include "MyMp3sec.h"
#include "ProgCtrlVolume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProgCtrlVolume

ProgCtrlVolume::ProgCtrlVolume()
{
	pDCBackk=new CDC;
	pDCForee=new CDC;
}

ProgCtrlVolume::~ProgCtrlVolume()
{
}


BEGIN_MESSAGE_MAP(ProgCtrlVolume, CStatic)
	//{{AFX_MSG_MAP(ProgCtrlVolume)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgCtrlVolume message handlers

void ProgCtrlVolume::SetRangee(int nLower, int nUpper)
{

}

int ProgCtrlVolume::SetStepp(int nStep)
{
	return 1;
}

int ProgCtrlVolume::SetPoss(int nPos)
{
	return 1;
}

int ProgCtrlVolume::StepAdd()
{
	return 1;
}

int ProgCtrlVolume::StepSub()
{
	return 1;
}
