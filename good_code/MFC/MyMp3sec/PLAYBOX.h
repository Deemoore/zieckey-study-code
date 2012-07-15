#if !defined(AFX_PLAYBOX_H__A1F2E90F_63D0_451F_AF74_BE1BB01D7FB7__INCLUDED_)
#define AFX_PLAYBOX_H__A1F2E90F_63D0_451F_AF74_BE1BB01D7FB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PLAYBOX.h : header file
//
#include "MyMp3secDlg.h"
#include "ProgCtrl.h"
#include "ProgCtrlVol.h"
/////////////////////////////////////////////////////////////////////////////
// PLAYBOX dialog

class PLAYBOX : public CDialog
{
// Construction
public:
	void testt();
	void PLAYALL();
	void test();
	PLAYBOX(CWnd* pParent = NULL);   // standard constructor
	CString sourcepath;
	CMyMp3secDlg *wavdlg;
	CMyMp3secDlg *pmed;

	CString m_sSongnamep;
	CEdit m_sSongnamepcon;

	CString m_sSongpath;
	CString j;
	int songduration;
	int i;
	HANDLE playboxfile;
	CString playboxdirectory;
	CString playboxWavpath;
	WIN32_FIND_DATA lpFileData;
	long m_lState;
// Dialog Data
	//{{AFX_DATA(PLAYBOX)
	enum { IDD = IDD_PLAYBOX };
	CString	m_exe;
	CStatic	m_controlexe;

	ProgCtrlVol	m_bmpvol;
	ProgCtrl m_bmpprog;
	
	//CEdit m_execon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PLAYBOX)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//CString m_sSongnamep;
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBitmapButton PEXIT;
	CBitmapButton PPAUSE;
	CBitmapButton PREPLAY;
	CBitmapButton PBACK;
	CBitmapButton PVOLNEC;
	CBitmapButton PVOLADD;
	CBitmapButton PPICTURE;
	CBitmapButton PPICTURE1;
	int State;
	CString progresstime;
	CFont* time;
	// Generated message map functions
	//{{AFX_MSG(PLAYBOX)
	afx_msg void OnPexit();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPreplay();
	afx_msg void OnPpause();
	afx_msg void OnPvolnec();
	afx_msg void OnPvoladd();
	afx_msg void OnPback();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYBOX_H__A1F2E90F_63D0_451F_AF74_BE1BB01D7FB7__INCLUDED_)
