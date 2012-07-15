#if !defined(AFX_OPENFILEALLPATH_H__43C76376_2C40_4FF4_976D_6ADD362547F3__INCLUDED_)
#define AFX_OPENFILEALLPATH_H__43C76376_2C40_4FF4_976D_6ADD362547F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenFileAllPath.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenFileAllPath dialog

class COpenFileAllPath : public CDialog
{
// Construction
public:
	COpenFileAllPath(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpenFileAllPath)
	enum { IDD = IDD_NEW_OPENFILE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenFileAllPath)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenFileAllPath)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENFILEALLPATH_H__43C76376_2C40_4FF4_976D_6ADD362547F3__INCLUDED_)
