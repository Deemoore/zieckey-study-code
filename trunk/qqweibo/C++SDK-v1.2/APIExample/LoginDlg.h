#pragma once
#include "afxwin.h"
#include <xstring>


// CLoginDlg dialog

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDlg();

// Dialog Data
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    BOOL GetToken();
	BOOL GetAccessKey();
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	// //appkey
	std::string m_sstrAppKey;
	// AppSecret
	std::string m_sstrAppSecret;
	// AccessKey
	std::string m_sstrAccessKey;
	// AccessSecret
	std::string m_sstrAccessSecret;

	std::string m_ssOauth_Verify;

protected:
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedCancel();
	CEdit m_editAppKey;
	CEdit m_editAppSecret;

	std::string m_sstrTokenKey;
	std::string m_sstrTokenSecrect;
};
