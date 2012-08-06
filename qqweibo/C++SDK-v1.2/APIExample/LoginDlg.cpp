// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TXAPITool.h"
#include "LoginDlg.h"
#include <string>
#include "..\Include\WeiboParam.h"
#include "inputdlg.h"
#include "Util.h"
using namespace std;

// CLoginDlg dialog


CStringA GetModulePath(void)
{
	char sExeFullPath[MAX_PATH];
	memset(sExeFullPath,0,MAX_PATH);

	int nLen = GetModuleFileNameA(NULL, sExeFullPath,MAX_PATH);
	CStringA strPath(sExeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	return strPath;
}

#define CONFIG_PATH (GetModulePath() + "\\APITool.ini")

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
: CDialog(CLoginDlg::IDD, pParent)
{
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_APPKEY, m_editAppKey);
	DDX_Control(pDX, IDC_APPSECRET, m_editAppSecret);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDC_LOGIN, &CLoginDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_CANCEL, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg message handlers

void CLoginDlg::OnBnClickedLogin()
{
	CString strInputAppKey;
	m_editAppKey.GetWindowText(strInputAppKey);

	CString strInputAppSecret;
	m_editAppSecret.GetWindowText(strInputAppSecret);

	if(strInputAppKey.IsEmpty())
	{
		MessageBox(L"AppKey不能为空");
		return ;
	}
	if(strInputAppSecret.IsEmpty())
	{
		MessageBox(L"AppSecret不能为空");
		return ;
	}


	if((Unicode2Mbcs(strInputAppKey.GetString()) != m_sstrAppKey)
		||(Unicode2Mbcs(strInputAppSecret.GetString()) != m_sstrAppSecret))   
	{
		m_sstrAccessKey.clear();
		m_sstrAccessSecret.clear(); 

        m_sstrAppKey = Unicode2Mbcs(strInputAppKey.GetString());
        m_sstrAppSecret = Unicode2Mbcs(strInputAppSecret.GetString());

		//获取tokenkey跳网页
		if(GetToken() == FALSE)
		{
			MessageBox(L"获取token key出错");
			return ;
		}

	}
	else if(m_sstrAccessKey.empty() || m_sstrAccessSecret.empty())
	{
		//获取tokenkey跳网页
		if(GetToken() == FALSE)
		{
			MessageBox(L"获取token key出错");
			return ;
		}
	}

	if(m_sstrAccessKey.empty() || m_sstrAccessSecret.empty())
	{
		CInputDlg dlg;//拿到oauth_verifier
		if(dlg.DoModal() != IDOK)
		{
			return;
		}
		m_ssOauth_Verify = Unicode2Mbcs(dlg.m_strInput.GetString());

		//根据oauth_verifier拿accessKey和accessSecret,这两个参数永久有效
		if(GetAccessKey() != TRUE)
		{
			MessageBox(L"获取access key出错");
			return ;
		}
	}
	//保存配置文件路径为当前exe的目录,信息均为明文
	::WritePrivateProfileStringA("Config","AppKey",m_sstrAppKey.c_str(),CONFIG_PATH);
	::WritePrivateProfileStringA("Config","AppSecret",m_sstrAppSecret.c_str(),CONFIG_PATH);
	::WritePrivateProfileStringA("Config","AccessKey",m_sstrAccessKey.c_str(),CONFIG_PATH);
	::WritePrivateProfileStringA("Config","AccessSecret",m_sstrAccessSecret.c_str(),CONFIG_PATH);

	OnOK();
}

void CLoginDlg::OnBnClickedCancel()
{
	OnCancel();
}

BOOL CLoginDlg::GetToken()
{
	string strCallbackUrl = "http://www.qq.com";

	CWeiboParam oParam;

	std::string c_strCustomKey		= TXWeibo::Param::strCustomKey;
	std::string c_strCustomSecrect	= TXWeibo::Param::strCustomSecrect;
	std::string c_oauthCallback		= TXWeibo::Param::strCallbackUrl;
	

	oParam.AddParam(c_strCustomKey.c_str(), m_sstrAppKey.c_str());
	oParam.AddParam(c_strCustomSecrect.c_str(), m_sstrAppSecret.c_str());
	oParam.AddParam(c_oauthCallback.c_str(), strCallbackUrl.c_str());

	string strUrl = "https://open.t.qq.com/cgi-bin/request_token";

	char* pRetData = NULL;
	int nLen = 0;
	HTTP_RESULTCODE  eErrorCode =  SyncRequest(strUrl.c_str(), EHttpMethod_Get, oParam, pRetData,nLen);
	if(eErrorCode != HTTPRESULT_OK || pRetData == NULL)
	{
		return FALSE;
	}
   
    string strResult = pRetData;
   
	ReleaseData(pRetData);

	string strMark1 = "oauth_token=";
	string strMark2 = "&oauth_token_secret=";
	string strMark3 = "&oauth_callback_confirmed=";

	string::size_type nTokenPos = strResult.find(strMark1);
	if (nTokenPos == 0)
	{
		string::size_type nSecrectPos = strResult.find(strMark2);
		if ((nSecrectPos != string::npos) && (nSecrectPos > nTokenPos))
		{
			m_sstrTokenKey = strResult.substr(strMark1.length(), nSecrectPos - strMark1.length());

			string::size_type nCallbackPos = strResult.find(strMark3);
			if (nTokenPos != string::npos)
			{
				m_sstrTokenSecrect = strResult.substr(nSecrectPos + strMark2.length(), nCallbackPos - (nSecrectPos + strMark2.length()));
			}
		}
	}

	if (!m_sstrTokenKey.empty())
	{
		string strVerify = "http://open.t.qq.com/cgi-bin/authorize";
		strVerify += "?oauth_token=";
		strVerify += m_sstrTokenKey;
		ShellExecuteA( NULL, "open", strVerify.c_str(), NULL, NULL, SW_SHOWNORMAL); 
		return TRUE;
	}

	return FALSE;
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//读取配置文件 
	char szConfig[1024];
	ZeroMemory(szConfig,1024*sizeof(char));
	::GetPrivateProfileStringA("Config","AppKey","",szConfig,1024,CONFIG_PATH);
	m_sstrAppKey = szConfig;
  
	ZeroMemory(szConfig,1024*sizeof(char));
	::GetPrivateProfileStringA("Config","AppSecret","",szConfig,1024,CONFIG_PATH);
	m_sstrAppSecret = szConfig;

	ZeroMemory(szConfig,1024*sizeof(char));
	::GetPrivateProfileStringA("Config","AccessKey","",szConfig,1024,CONFIG_PATH);
	m_sstrAccessKey = szConfig;

	ZeroMemory(szConfig,1024*sizeof(char));
	::GetPrivateProfileStringA("Config","AccessSecret","",szConfig,1024,CONFIG_PATH);
	m_sstrAccessSecret = szConfig;

	m_editAppKey.SetWindowText(Mbcs2Unicode(m_sstrAppKey.c_str()).c_str());
	m_editAppSecret.SetWindowText(Mbcs2Unicode(m_sstrAppSecret.c_str()).c_str());

	return TRUE;
}

BOOL CLoginDlg::GetAccessKey()
{
	CWeiboParam oParam;

	std::string c_strCustomKey		= TXWeibo::Param::strCustomKey;
	std::string c_strCustomSecrect	= TXWeibo::Param::strCustomSecrect;
	std::string c_strTokenKey		= TXWeibo::Param::strTokenKey;
	std::string c_strTokenSecrect	= TXWeibo::Param::strTokenSecrect;

	oParam.AddParam(c_strCustomKey.c_str(), m_sstrAppKey.c_str());
	oParam.AddParam(c_strCustomSecrect.c_str(), m_sstrAppSecret.c_str());

	oParam.AddParam(c_strTokenKey.c_str(), m_sstrTokenKey.c_str());
	oParam.AddParam(c_strTokenSecrect.c_str(), m_sstrTokenSecrect.c_str());

	size_t nSizeReturn = 0;

	oParam.AddParam("oauth_verifier", m_ssOauth_Verify.c_str());

	string strUrl = "https://open.t.qq.com/cgi-bin/access_token";
	
	char* pRetData = NULL;
	int nLen = 0;
	HTTP_RESULTCODE eHttpCode = SyncRequest(strUrl.c_str(), EHttpMethod_Get, oParam, pRetData,nLen);

	if(eHttpCode != HTTPRESULT_OK || pRetData == NULL)
	{
		return FALSE;
	}
  
	string strResult = pRetData;
 
	ReleaseData(pRetData);

	string strMark1 = "oauth_token=";
	string strMark2 = "&oauth_token_secret=";
	string strMark3 = "&name=";

	string::size_type nTokenPos = strResult.find(strMark1);
	if (nTokenPos == 0)
	{
		string::size_type nSecrectPos = strResult.find(strMark2);
		if ((nSecrectPos != string::npos) && (nSecrectPos > nTokenPos))
		{
			m_sstrAccessKey = strResult.substr(strMark1.length(), nSecrectPos - strMark1.length());

			string::size_type nCallbackPos = strResult.find(strMark3);
			if (nTokenPos != string::npos)
			{
				m_sstrAccessSecret = strResult.substr(nSecrectPos + strMark2.length(), nCallbackPos - (nSecrectPos + strMark2.length()));
			}
		}
		return TRUE;
	}
	return FALSE;
}

