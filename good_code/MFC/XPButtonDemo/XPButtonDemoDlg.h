// XPButtonDemoDlg.h : header file
//

#if !defined(AFX_XPBUTTONDEMODLG_H__AD3ABC61_C66A_4C31_AC99_C94B3FB90684__INCLUDED_)
#define AFX_XPBUTTONDEMODLG_H__AD3ABC61_C66A_4C31_AC99_C94B3FB90684__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CXPButtonDemoDlg dialog

class CXPButtonDemoDlg : public CDialog
{
// Construction
public:
	CXPButtonDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXPButtonDemoDlg)
	enum { IDD = IDD_XPBUTTONDEMO_DIALOG };
	CXPButton	m_btnOK;
	CXPButton	m_btnCancel;
	CXPButton	m_btnDisable;
	CXPButton	m_btnFocus;
	CXPButton	m_btnOver;
	CXPButton	m_btnNormal;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPButtonDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXPButtonDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPBUTTONDEMODLG_H__AD3ABC61_C66A_4C31_AC99_C94B3FB90684__INCLUDED_)
