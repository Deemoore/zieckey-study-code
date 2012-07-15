#if !defined(AFX_DELOG_H__06CC9A1A_2075_462F_85A0_F757531C223E__INCLUDED_)
#define AFX_DELOG_H__06CC9A1A_2075_462F_85A0_F757531C223E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Delog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Delog dialog

class Delog : public CDialog
{
// Construction
public:
	Delog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Delog)
	enum { IDD = IDD_DELOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Delog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Delog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELOG_H__06CC9A1A_2075_462F_85A0_F757531C223E__INCLUDED_)
