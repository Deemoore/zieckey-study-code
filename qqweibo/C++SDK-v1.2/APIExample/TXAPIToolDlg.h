// TXAPIToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "listcontrolex.h"
#include "..\Include\WeiboApi.h"
#include <vector>
#include "ApiType.h"


// CTXAPIToolDlg �Ի���
class CTXAPIToolDlg : public CDialog,public VWeiboCallback
{
// ����
public:
	CTXAPIToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

	BOOL Login();
// �Ի�������
	enum { IDD = IDD_TXAPITOOL_DIALOG };

	//void InitApiTypeList();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	

	BOOL SetDefaultPara2ListCtrl(Txwb_api_option option);

// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	CComboBox m_comboApiType;
	virtual void OnRequestComplete(HTTP_RESULTCODE eHttpRetCode,const char* pReqUrl, CWeiboParam oParam, 
		const char*pData,int nLen);

	afx_msg void OnCbnSelchangeMethod();

protected:	
//	CListControlEx m_listParam;
	CListControlEx m_listHeader;
public:
	std::string m_strAppKey;
	// AppSecret
	std::string m_strAppSecret;
	// AccessKey
	std::string m_strAccessKey;
	// AccessSecret
	std::string m_strAccessSecret;

	//
//	std::vector<std::wstring> m_vecApiTypeList;

	//api type
	CApiType m_apiType;

protected:
	afx_msg void OnBnClickedSend();
public:
//	afx_msg void OnBnClickedAddheader();
//	afx_msg void OnBnClickedAddpic();
//	afx_msg void OnBnClickedDelpic();
//	afx_msg void OnBnClickedDelheader();
protected:
	// //������
	CString m_strOutput;
};
