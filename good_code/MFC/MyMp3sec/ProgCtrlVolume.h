#if !defined(AFX_PROGCTRLVOLUME_H__11E13FA1_B05C_4B7C_9DFD_6311FAEBB524__INCLUDED_)
#define AFX_PROGCTRLVOLUME_H__11E13FA1_B05C_4B7C_9DFD_6311FAEBB524__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgCtrlVolume.h : header file
//
/*
/////////////////////////////////////////////////////////////////////////////
// ProgCtrlVolume window

class ProgCtrlVolume : public CStatic
{
// Construction
public:
	
	ProgCtrlVolume();
	int GetPoss();
	int SetPos(int nPoss);
	int StepItt();
	int SetStepp(int nStep);
	void SetRangee(int nLower,int nUpper);
	
// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProgCtrlVolume)
	//}}AFX_VIRTUAL

// Implementation
public:
	int StepSub();
	int StepAdd();
	int SetPoss(int nPos);
	int SetStepp(int nStep);
	void SetRangee(int nLower,int nUpper);
	virtual ~ProgCtrlVolume();

	// Generated message map functions
protected:
	//{{AFX_MSG(ProgCtrlVolume)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	float m_lengthh;
	CRect m_rectt;
	int m_nStepp;
	int m_nUpperr;
	int m_nLowerr;
	int m_nPoss;
	CBitmap bmpBackk;
	CBitmap bmpForee;
	//CBitmap bmpGogogo;
	CDC * pDCBackk;
	CDC * pDCForee;
	//CDC * pDCGogogo;
	BITMAP bmbackk;
	BITMAP bmforee;
	//BITMAP bmgogogo;
};
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGCTRLVOLUME_H__11E13FA1_B05C_4B7C_9DFD_6311FAEBB524__INCLUDED_)
