// MP3Dlg.h : header file
//

#if !defined(AFX_MP3DLG_H__9B2F60C7_34BD_4E7E_8E04_4C0AB7E4C329__INCLUDED_)
#define AFX_MP3DLG_H__9B2F60C7_34BD_4E7E_8E04_4C0AB7E4C329__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CMP3Dlg dialog

class CMP3Dlg : public CDialog
{
// Construction
public:
	CMP3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMP3Dlg)
	enum { IDD = IDD_MP3_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMP3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMP3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MP3DLG_H__9B2F60C7_34BD_4E7E_8E04_4C0AB7E4C329__INCLUDED_)
