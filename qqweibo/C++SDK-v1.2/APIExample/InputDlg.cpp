// InputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TXAPITool.h"
#include "InputDlg.h"


// CInputDlg dialog

IMPLEMENT_DYNAMIC(CInputDlg, CDialog)

CInputDlg::CInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputDlg::IDD, pParent)
	, m_strInput(_T(""))
{

}

CInputDlg::~CInputDlg()
{
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Input, m_strInput);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CInputDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputDlg message handlers

void CInputDlg::OnBnClickedOk()
{
    UpdateData(TRUE);
   
	if(m_strInput.IsEmpty())
	{
		MessageBox(L"输入不能为空");
	}

	OnOK();
}
