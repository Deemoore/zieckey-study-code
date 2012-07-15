#if !defined(AFX_PROGCTRLVOL_H__DB0FC60D_281F_4324_9317_9CCB544DB5E0__INCLUDED_)
#define AFX_PROGCTRLVOL_H__DB0FC60D_281F_4324_9317_9CCB544DB5E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgCtrlVol.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ProgCtrlVol window

class ProgCtrlVol : public CStatic
{
// Construction
public:
	ProgCtrlVol();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProgCtrlVol)
	//}}AFX_VIRTUAL

// Implementation
public:
	int StepItt();
	int StepIt();
	virtual ~ProgCtrlVol();

	// Generated message map functions
protected:
	//{{AFX_MSG(ProgCtrlVol)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	float m_length;
	BITMAP bmfore;
	BITMAP bmback;
	CDC * pDCFore;
	CDC * pDCBack;
	CBitmap bmpFore;
	CBitmap bmpBack;
	CRect m_rect;
	int m_nPos;
	int m_nStep;
	int m_nUpper;
	int m_nLower;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGCTRLVOL_H__DB0FC60D_281F_4324_9317_9CCB544DB5E0__INCLUDED_)
