// TXAPIToolDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "listcontrolex.h"
#include "..\Include\WeiboApi.h"
#include <vector>
#include "ApiType.h"


// CTXAPIToolDlg 对话框
class CTXAPIToolDlg : public CDialog,public VWeiboCallback
{
// 构造
public:
	CTXAPIToolDlg(CWnd* pParent = NULL);	// 标准构造函数

	BOOL Login();
// 对话框数据
	enum { IDD = IDD_TXAPITOOL_DIALOG };

	//void InitApiTypeList();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	

	BOOL SetDefaultPara2ListCtrl(Txwb_api_option option);

// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
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
	// //结果输出
	CString m_strOutput;
};
