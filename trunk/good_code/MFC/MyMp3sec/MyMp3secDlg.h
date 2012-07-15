// MyMp3secDlg.h : header file
//
#include "mediaplayer2.h"
#include "PLAYBOX.h"
#if !defined(AFX_MYMP3SECDLG_H__99AA5776_2D79_4C0B_8228_FBF0AD255A9C__INCLUDED_)
#define AFX_MYMP3SECDLG_H__99AA5776_2D79_4C0B_8228_FBF0AD255A9C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CMyMp3secDlg dialog

class CMyMp3secDlg : public CDialog
{
// Construction
public:
	//PLAYBOX * pboxx;
	//PLAYBOX* pboxx;
	void vnec();
	void vadd();
	
	void On14();
	void On13();
	void On12();
	void On11();
	void On10();
	void On9();
	void On8();
	void On7();
	void On6();
	void On5();
	void On4();
	void On3();
	void On2();
	void On0();
	CString directory;
	CString directorystar;
	CString Wavpath;
	CString wavlist;
	CString m_sSongname;
	void Onx();
	void On1();
	void SearchFile();
	CMyMp3secDlg(CWnd* pParent = NULL);	// standard constructor
	HANDLE file;
	int n;
	WIN32_FIND_DATA lpFileData;
	int preV;
	CString m_1;
	CEdit m_1con;
	CString m[14];
	CEdit mcon[14];
// Dialog Data
	//{{AFX_DATA(CMyMp3secDlg)
	enum { IDD = IDD_MYMP3SEC_DIALOG };
	CMediaPlayer2 m_thePlayer;
	CString	m_yanshi;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMp3secDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont* time;
	HICON m_hIcon;
	CBitmapButton PLAY;
	CBitmapButton PLAYALL;
	CBitmapButton HOME;
	CBitmapButton BACK;
	CBitmapButton DELE;

	CBitmapButton FIRST;
	CBitmapButton END;
	CBitmapButton PRE;
	CBitmapButton NEXT;
	// Generated message map functions
	//{{AFX_MSG(CMyMp3secDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHome();
	afx_msg void OnPlay();
	afx_msg void OnCurrent();
	afx_msg void OnYanshi();
	afx_msg void OnPlayall();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFirst();
	afx_msg void OnPre();
	afx_msg void OnNext();
	afx_msg void OnEnd();
	afx_msg void OnBack();
	afx_msg void OnDele();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMP3SECDLG_H__99AA5776_2D79_4C0B_8228_FBF0AD255A9C__INCLUDED_)
