#if !defined(AFX_DELETEDLG_H__85997BC5_1139_4ACF_9DAB_6DBB579C8CC2__INCLUDED_)
#define AFX_DELETEDLG_H__85997BC5_1139_4ACF_9DAB_6DBB579C8CC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeleteDlg.h : header file
//
#include "MyMp3secDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CDeleteDlg dialog

class CDeleteDlg : public CDialog
{
// Construction
public:
	CDeleteDlg(CWnd* pParent = NULL);   // standard constructor
	int n1;
	CString sourcepath;
	CMyMp3secDlg* mymp3dlg;

// Dialog Data
	//{{AFX_DATA(CDeleteDlg)
	enum { IDD = IDD_DELETE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBitmapButton DELETEOK;
	CBitmapButton DELETECANCEL;
	// Generated message map functions
	//{{AFX_MSG(CDeleteDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETEDLG_H__85997BC5_1139_4ACF_9DAB_6DBB579C8CC2__INCLUDED_)
