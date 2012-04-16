// testMMTimerDlg.h : header file
//

#pragma once

#include "TimeAgent.h"
// CtestMMTimerDlg dialog
class CtestMMTimerDlg : public CDialog,public CTimeAgent
{
// Construction
public:
	CtestMMTimerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTMMTIMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void OnMMTimer(int nTimerID);

    //CTimeAgent m_TimeAgent;
// Implementation
protected:
	HICON m_hIcon;
	int m_nText;
	int m_nText2;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
