#if !defined(AFX_PROGCTRL_H__0118A25D_9C05_48C2_BA6E_F3B09615EE4E__INCLUDED_)
#define AFX_PROGCTRL_H__0118A25D_9C05_48C2_BA6E_F3B09615EE4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ProgCtrl window

class ProgCtrl : public CStatic
{
// Construction
public:
	ProgCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProgCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetPos();
	int SetPos(int nPos);
	int StepIt();
	int SetStep(int nStep);
	void SetRange(int nLower,int nUpper);
	virtual ~ProgCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(ProgCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	float m_length;
	CRect m_rect;
	int m_nStep;
	int m_nUpper;
	int m_nLower;
	int m_nPos;
	CBitmap bmpBack;
	CBitmap bmpFore;
	CBitmap bmpGogogo;
	CDC * pDCBack;
	CDC * pDCFore;
	CDC * pDCGogogo;
	BITMAP bmback;
	BITMAP bmfore;
	BITMAP bmgogogo;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGCTRL_H__0118A25D_9C05_48C2_BA6E_F3B09615EE4E__INCLUDED_)
