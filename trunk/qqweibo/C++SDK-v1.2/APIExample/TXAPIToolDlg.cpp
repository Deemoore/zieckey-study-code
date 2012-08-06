// TXAPIToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TXAPITool.h"
#include "TXAPIToolDlg.h"
#include "..\Include\WeiboApi.h"
#include "..\Include\WeiboParam.h"
#include "logindlg.h"
#include <assert.h>
#include "Util.h"
//#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*与HTTP_RESULTCODE一一对应*/
const TCHAR*  wszErrorString[] = {L"成功",L"请求超时",L"不能解析地址",L"不能连接",L"错误",L"返回的数据量太大",L"失败",L"类型错误，无法生成有效的url"};

// CTXAPIToolDlg 对话框

#define HIDE_PADDING 50

CTXAPIToolDlg::CTXAPIToolDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTXAPIToolDlg::IDD, pParent)
, m_strOutput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTXAPIToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_API_TYPE, m_comboApiType);
	DDX_Control(pDX, IDC_LISTHEADER, m_listHeader);
	DDX_Text(pDX, IDC_Result, m_strOutput);
}

BEGIN_MESSAGE_MAP(CTXAPIToolDlg, CDialog)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_API_TYPE, &CTXAPIToolDlg::OnCbnSelchangeMethod)
	ON_BN_CLICKED(IDC_SEND, &CTXAPIToolDlg::OnBnClickedSend)

END_MESSAGE_MAP()


// CTXAPIToolDlg 消息处理程序

BOOL CTXAPIToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

		
	int i;
	for(i = 1; i< TXWB_MAX; ++i)
	{
		m_comboApiType.InsertString(i-1,m_apiType.m_apiTypeNameList[i].c_str());
	}
	
	
	m_comboApiType.SetCurSel(0);

	m_listHeader.Init(type_Header);
	//默认选第一个，所以填充第一个api的默认参数
	SetDefaultPara2ListCtrl((Txwb_api_option)(TXWB_BASE+1));
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTXAPIToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTXAPIToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTXAPIToolDlg::OnCbnSelchangeMethod()
{
	int nIndex = m_comboApiType.GetCurSel();
	Txwb_api_option option =(Txwb_api_option)(nIndex+1);
	if(nIndex < 0)
	{
		return ;
	}
	
	if(option <=TXWB_BASE || option>=TXWB_MAX)
	{
		return ;
	}

	SetDefaultPara2ListCtrl(option);


}

void CTXAPIToolDlg::OnBnClickedSend()
{
	m_strOutput = L"";
	UpdateData(FALSE);


	CWeiboParam oParam;
    //以下四个参数在每次请求必须带上
	std::string c_strCustomKey		= TXWeibo::Param::strCustomKey;
	std::string c_strCustomSecrect	= TXWeibo::Param::strCustomSecrect;
	std::string c_strTokenKey		= TXWeibo::Param::strTokenKey;
	std::string c_strTokenSecrect	= TXWeibo::Param::strTokenSecrect;

	oParam.AddParam(c_strCustomKey.c_str(), m_strAppKey.c_str());
	oParam.AddParam(c_strCustomSecrect.c_str(), m_strAppSecret.c_str());
	oParam.AddParam(c_strTokenKey.c_str(),m_strAccessKey.c_str());
	oParam.AddParam(c_strTokenSecrect.c_str(),m_strAccessSecret.c_str());
	
		
	//获取类型
	Txwb_api_option option =(Txwb_api_option)(m_comboApiType.GetCurSel() + 1);



	if(option <= TXWB_BASE || option >=TXWB_MAX)
	{
		MessageBox(L"api 类型超出范围");
		return;
	}
	
	
	CStringArray strArryName;
	CStringArray strArryValue;
	//请求头参数listview 第0列放的是checkbox，第1列放的是name，第2列放的是value
	m_listHeader.GetColumnData(1,strArryName);
	m_listHeader.GetColumnData(2,strArryValue);

	int nSize;
	nSize = strArryName.GetCount();
	CString ctmp = L"pic";
	
	for (int i = 0; i < nSize;i++)
	{
		
		if(strArryName.GetAt(i).GetString() != ctmp)
			oParam.AddParam(Unicode2Mbcs(strArryName.GetAt(i).GetString()).c_str(),
				Unicode2Mbcs((strArryValue.GetAt(i).GetString())).c_str());
		else
		{
			//是图片，特殊处理
			//MessageBox(strArryValue.GetAt(i).GetString());
			oParam.AddPicNameParam("pic",
						Unicode2Mbcs((strArryValue.GetAt(i).GetString())).c_str());
		}
		
	}


	if(AsyncRequestByOption(option, oParam, this))
	{
		m_strOutput = L"请求中...";
	}
	else
	{
		m_strOutput = L"请求失败...";
	}
	UpdateData(FALSE);
}

/*异步请求回调函数，工作在主线程*/
void CTXAPIToolDlg::OnRequestComplete( HTTP_RESULTCODE eHttpRetCode,const char* pReqUrl, CWeiboParam oParam, 
									  const char*pData,int nLen )
{
	m_strOutput = L"";
    UpdateData(FALSE);

	if(eHttpRetCode != HTTPRESULT_OK && eHttpRetCode <= HTTPRESULT_FAIL)
	{
		m_strOutput = wszErrorString[eHttpRetCode];
		UpdateData(FALSE);
		return;
	}

	if (eHttpRetCode == HTTPRESULT_OK)
	{
		wchar_t* pUnicodeData = Util::String::Utf8ToUnicode(pData);
		m_strOutput = pUnicodeData;
		ReleaseData(pUnicodeData);
		UpdateData(FALSE);
	}
	else
	{
		assert(0);
	}
}

BOOL CTXAPIToolDlg::Login()
{
	CLoginDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_strAppKey = dlg.m_sstrAppKey;
		m_strAppSecret = dlg.m_sstrAppSecret;
		m_strAccessKey = dlg.m_sstrAccessKey;
		m_strAccessSecret = dlg.m_sstrAccessSecret;

		return TRUE;
	}
	return FALSE;
}

//填充默认参数
// option 为类型
BOOL CTXAPIToolDlg::SetDefaultPara2ListCtrl(Txwb_api_option option)
{
	
	if(option <=TXWB_BASE || option >=TXWB_MAX)
	{
		MessageBox(L"option 的值范围出错！");
		return FALSE;
	}

	m_listHeader.DeleteAllItems();
	
	int index = 0;
	for(int i = 0; i < m_apiType.m_apiDefaultKeyValuePairList[option].size(); ++i)
	{
		
		index = m_listHeader.InsertItem(m_listHeader.GetItemCount()+1,L"");
			
		m_listHeader.SetItemText(index,1,m_apiType.m_apiDefaultKeyValuePairList[option][i].first.c_str());
		
		m_listHeader.SetItemText(index,2,m_apiType.m_apiDefaultKeyValuePairList[option][i].second.c_str());
	
	}
		
	return TRUE;
}
