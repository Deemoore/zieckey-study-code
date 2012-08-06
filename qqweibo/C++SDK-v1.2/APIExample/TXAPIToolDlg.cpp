// TXAPIToolDlg.cpp : ʵ���ļ�
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

/*��HTTP_RESULTCODEһһ��Ӧ*/
const TCHAR*  wszErrorString[] = {L"�ɹ�",L"����ʱ",L"���ܽ�����ַ",L"��������",L"����",L"���ص�������̫��",L"ʧ��",L"���ʹ����޷�������Ч��url"};

// CTXAPIToolDlg �Ի���

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


// CTXAPIToolDlg ��Ϣ�������

BOOL CTXAPIToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

		
	int i;
	for(i = 1; i< TXWB_MAX; ++i)
	{
		m_comboApiType.InsertString(i-1,m_apiType.m_apiTypeNameList[i].c_str());
	}
	
	
	m_comboApiType.SetCurSel(0);

	m_listHeader.Init(type_Header);
	//Ĭ��ѡ��һ������������һ��api��Ĭ�ϲ���
	SetDefaultPara2ListCtrl((Txwb_api_option)(TXWB_BASE+1));
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTXAPIToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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
    //�����ĸ�������ÿ������������
	std::string c_strCustomKey		= TXWeibo::Param::strCustomKey;
	std::string c_strCustomSecrect	= TXWeibo::Param::strCustomSecrect;
	std::string c_strTokenKey		= TXWeibo::Param::strTokenKey;
	std::string c_strTokenSecrect	= TXWeibo::Param::strTokenSecrect;

	oParam.AddParam(c_strCustomKey.c_str(), m_strAppKey.c_str());
	oParam.AddParam(c_strCustomSecrect.c_str(), m_strAppSecret.c_str());
	oParam.AddParam(c_strTokenKey.c_str(),m_strAccessKey.c_str());
	oParam.AddParam(c_strTokenSecrect.c_str(),m_strAccessSecret.c_str());
	
		
	//��ȡ����
	Txwb_api_option option =(Txwb_api_option)(m_comboApiType.GetCurSel() + 1);



	if(option <= TXWB_BASE || option >=TXWB_MAX)
	{
		MessageBox(L"api ���ͳ�����Χ");
		return;
	}
	
	
	CStringArray strArryName;
	CStringArray strArryValue;
	//����ͷ����listview ��0�зŵ���checkbox����1�зŵ���name����2�зŵ���value
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
			//��ͼƬ�����⴦��
			//MessageBox(strArryValue.GetAt(i).GetString());
			oParam.AddPicNameParam("pic",
						Unicode2Mbcs((strArryValue.GetAt(i).GetString())).c_str());
		}
		
	}


	if(AsyncRequestByOption(option, oParam, this))
	{
		m_strOutput = L"������...";
	}
	else
	{
		m_strOutput = L"����ʧ��...";
	}
	UpdateData(FALSE);
}

/*�첽����ص����������������߳�*/
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

//���Ĭ�ϲ���
// option Ϊ����
BOOL CTXAPIToolDlg::SetDefaultPara2ListCtrl(Txwb_api_option option)
{
	
	if(option <=TXWB_BASE || option >=TXWB_MAX)
	{
		MessageBox(L"option ��ֵ��Χ����");
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
