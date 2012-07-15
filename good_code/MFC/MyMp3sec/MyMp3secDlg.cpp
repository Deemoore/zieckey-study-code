// MyMp3secDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyMp3sec.h"
#include "MyMp3secDlg.h"
#include "PLAYBOX.h"
#include "DeleteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMp3secDlg dialog
PLAYBOX *pboxx;
CMyMp3secDlg::CMyMp3secDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyMp3secDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyMp3secDlg)
	m_yanshi = _T("TEST");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	PLAY.LoadBitmaps(IDB_PLAY);
	PLAYALL.LoadBitmaps(IDB_PLAYALL);
	HOME.LoadBitmaps(IDB_PEXIT);
	BACK.LoadBitmaps(IDB_PBACK);
	DELE.LoadBitmaps(IDB_DELE);

	FIRST.LoadBitmaps(IDB_FIRST);
	END.LoadBitmaps(IDB_END);
	PRE.LoadBitmaps(IDB_PRE);
	NEXT.LoadBitmaps(IDB_NEXT);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//PEXIT.LoadBitmaps(IDB_PEXIT);
	
}

void CMyMp3secDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyMp3secDlg)
	DDX_Control(pDX,IDC_MEDIAPLAYER1,m_thePlayer);
	DDX_Text(pDX, IDC_YANSHI, m_yanshi);
	DDX_Text(pDX,1,m_1);//������Щ���ʹnIDC(���������1��2��3��)��CString m[i]��EDit mcon[i]
						//��ϵ������ֻҪ�趨��m[i]�����壬�����һ�����ݣ���ҳ����ʾ�Ͳ���������
	DDX_Control(pDX,1,m_1con);

	DDX_Text(pDX,2,m[1]);
	DDX_Control(pDX,2,mcon[1]);
	DDX_Text(pDX,3,m[2]);
	DDX_Control(pDX,3,mcon[2]);
	DDX_Text(pDX,4,m[3]);
	DDX_Control(pDX,4,mcon[3]);
	DDX_Text(pDX,5,m[4]);
	DDX_Control(pDX,5,mcon[4]);
	DDX_Text(pDX,6,m[5]);
	DDX_Control(pDX,6,mcon[5]);
	DDX_Text(pDX,7,m[6]);
	DDX_Control(pDX,7,mcon[6]);
	DDX_Text(pDX,8,m[7]);
	DDX_Control(pDX,8,mcon[7]);
	DDX_Text(pDX,9,m[8]);
	DDX_Control(pDX,9,mcon[8]);
	DDX_Text(pDX,10,m[9]);
	DDX_Control(pDX,10,mcon[9]);
	DDX_Text(pDX,11,m[10]);
	DDX_Control(pDX,11,mcon[10]);
	DDX_Text(pDX,12,m[11]);
	DDX_Control(pDX,12,mcon[11]);
	DDX_Text(pDX,13,m[12]);
	DDX_Control(pDX,13,mcon[12]);
	DDX_Text(pDX,14,m[13]);
	DDX_Control(pDX,14,mcon[13]);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyMp3secDlg, CDialog)
	//{{AFX_MSG_MAP(CMyMp3secDlg)
	ON_BN_CLICKED(IDC_HOME, OnHome)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_CURRENT, OnCurrent)
	ON_BN_CLICKED(IDC_YANSHI, OnYanshi)
	ON_BN_CLICKED(IDC_PLAYALL, OnPlayall)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_FIRST, OnFirst)
	ON_BN_CLICKED(IDC_PRE, OnPre)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_END, OnEnd)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_DELE, OnDele)
	ON_BN_CLICKED(1, On1)
	ON_BN_CLICKED(2, On2)//ʹ�����ı���ִ����ͼƬIDC_v1��Ӧ�ĺ���On1()
	ON_BN_CLICKED(3, On3)
	ON_BN_CLICKED(4, On4)
	ON_BN_CLICKED(5, On5)
	ON_BN_CLICKED(6, On6)
	ON_BN_CLICKED(7, On7)
	ON_BN_CLICKED(8, On8)
	ON_BN_CLICKED(9, On9)
	ON_BN_CLICKED(10, On10)
	ON_BN_CLICKED(11, On11)
	ON_BN_CLICKED(12, On12)
	ON_BN_CLICKED(13, On13)
	ON_BN_CLICKED(14, On14)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyMp3secDlg message handlers

BOOL CMyMp3secDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen
	//VERIFY(PEXIT.SubclassDlgItem(IDC_PEXIT,this));
	//PEXIT.SizeToContent();
	VERIFY(PLAY.SubclassDlgItem(IDC_PLAY,this));
	PLAY.SizeToContent();
	VERIFY(PLAYALL.SubclassDlgItem(IDC_PLAYALL,this));
	PLAYALL.SizeToContent();
	VERIFY(HOME.SubclassDlgItem(IDC_HOME,this));
	HOME.SizeToContent();
	VERIFY(BACK.SubclassDlgItem(IDC_BACK,this));
	BACK.SizeToContent();
	VERIFY(DELE.SubclassDlgItem(IDC_DELE,this));
	DELE.SizeToContent();

	VERIFY(FIRST.SubclassDlgItem(IDC_FIRST,this));
	FIRST.SizeToContent();
	VERIFY(END.SubclassDlgItem(IDC_END,this));
	END.SizeToContent();
	VERIFY(PRE.SubclassDlgItem(IDC_PRE,this));
	PRE.SizeToContent();
	VERIFY(NEXT.SubclassDlgItem(IDC_NEXT,this));
	NEXT.SizeToContent();

	GetDlgItem(IDC_v1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v10)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v11)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v12)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v13)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_v14)->ShowWindow(SW_HIDE);

	time=new CFont;
	time->CreateFont(18,0,0,0,900,FALSE,FALSE,0,
					ANSI_CHARSET,OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH|FF_SWISS,
					_T("����"));
	
	preV=IDC_v1;
	// TODO: Add extra initialization here
	directory="\\Storage Card\\";
	//directory="\\Temp\\";
	directorystar="\Storage Card\\*.mp3";
	SearchFile();
	On0();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyMp3secDlg::SearchFile()
{
	n=0;
	file=FindFirstFile(_T("\\Storage Card\\*.mp3"),&lpFileData);
	//file=FindFirstFile(_T("\\Temp\\*.mp3"),&lpFileData);
	if(file!=INVALID_HANDLE_VALUE)
	{
		CString wavlist;
		wavlist=lpFileData.cFileName;
		int dot=wavlist.Find('.');
		m_1=wavlist.Left(dot);
		//m_1=wavlist;
		m_1con.SetFont(time);
		m_1con.SetWindowText(m_1);
	//MessageBox(wavlist,TEXT("wavlist"),MB_OK);
		//GetDlgItem(1)->SetWindowText(wavlist);
		n++;
	}
	int i=2;
	BOOL FileEnd=FindNextFile(file,&lpFileData);
	while(FileEnd!=0)
	{
		if(i<15)
		{
			CString wavlist;
			wavlist=lpFileData.cFileName;
			int dot=wavlist.Find('.');
			wavlist=wavlist.Left(dot);
			m[n]=wavlist;
			mcon[n].SetFont(time);
			//mcon[n].SetWindowText(m[n]);//��һ��Ҳ���ԣ�����һ��Ҳ����
			GetDlgItem(i)->SetWindowText(wavlist);
			if(i<14)
			{
				FileEnd=FindNextFile(file,&lpFileData);
			}
			i++;
			n++;
		}
		else
		{
			FileEnd=0;
		}
	}
}

void CMyMp3secDlg::OnHome() 
{
	CMyMp3secDlg::OnOK();
	CMyMp3secDlg::DestroyWindow();
}

void CMyMp3secDlg::OnPlay() 
{

	delete pboxx;
	this->m_thePlayer.SetFileName(Wavpath);
	this->m_thePlayer.Play();
	pboxx=new PLAYBOX;
	CMyMp3secDlg *dlggg=this;
	pboxx->pmed=dlggg;//////////////////////////////////////////////////////important
	pboxx->m_sSongnamep=wavlist;
	pboxx->m_sSongpath=Wavpath;
	pboxx->Create(IDD_PLAYBOX,NULL);
	pboxx->ShowWindow(SW_SHOW);
	//dlggg->ShowWindow (SW_HIDE);
}

void CMyMp3secDlg::OnPlayall() 
{

	file=FindFirstFile(_T("\\Storage Card\\*.mp3"),&lpFileData);
	//file=FindFirstFile(_T("\\Temp\\*.mp3"),&lpFileData);
	if(file!=INVALID_HANDLE_VALUE)
	{
		//CString wavlist;
		wavlist=lpFileData.cFileName;
	//MessageBox(wavlist,TEXT("first wavlist"),MB_OK);
		//GetDlgItem(1)->SetWindowText(wavlist);
		//n++;
		Wavpath=directory+wavlist;

	}
	this->m_thePlayer.SetFileName(Wavpath);
	this->m_thePlayer.Play();
	
	/*
	PLAYBOX *pbox=new PLAYBOX;
	pbox=new PLAYBOX;
	CMyMp3secDlg *dlggg=this;
	pbox->pmed=dlggg;//////////////////////////////////////////////////////important
	pbox->m_sSongnamep=wavlist;
	pbox->m_sSongpath=Wavpath;
	pbox->Create(IDD_PLAYBOX,NULL);
	pbox->ShowWindow(SW_SHOW);
	*/
	pboxx=new PLAYBOX;
	CMyMp3secDlg *dlggg=this;
	//SetTimer(1,1000,NULL);
	pboxx->pmed=dlggg;//////////////////////////////////////////////////////important
//MessageBox(wavlist,TEXT("second wavlist"),MB_OK);
	pboxx->m_sSongnamep=wavlist;
	pboxx->m_sSongpath=Wavpath;
	pboxx->Create(IDD_PLAYBOX,NULL);
	pboxx->ShowWindow(SW_SHOW);
	pboxx->PLAYALL();
	//dlggg->ShowWindow (SW_HIDE);
	
}

void CMyMp3secDlg::OnBack() 
{
	// TODO: Add your control notification handler code here
	CMyMp3secDlg::OnOK();
	CMyMp3secDlg::DestroyWindow();
}

void CMyMp3secDlg::OnDele() 
{
	// TODO: Add your control notification handler code here
	CString str,a;
	CDeleteDlg deletedlg;
	deletedlg.sourcepath=Wavpath;
	deletedlg.n1=n;
	deletedlg.mymp3dlg=this;
	deletedlg.DoModal();
}

void CMyMp3secDlg::OnTimer(UINT nIDEvent) 
{

		long m_lState=m_thePlayer.GetPlayState();
		if(m_lState==0)
		{
		//MessageBox(TEXT("FIRST SONG OVER"),TEXT("CONMENT"),MB_OK);
			//delete pboxx;//�������Σ�����IDD_PLAYBOX����ʧ
			KillTimer(1);
		MessageBox(TEXT("FIRST SONG OVER"),TEXT("CONMENT"),MB_OK);
			BOOL FileEnd=FindNextFile(file,&lpFileData);
			while(FileEnd!=0)
			{
			MessageBox(TEXT("enter FileEnd"),TEXT("CONMENT"),MB_OK);
				CString wavlist;
				wavlist=lpFileData.cFileName;
				Wavpath=directory+wavlist;
			MessageBox(Wavpath,TEXT("Wavpath"),MB_OK);
				this->m_thePlayer.SetFileName(Wavpath);
				this->m_thePlayer.Play();
				/*
				PLAYBOX *pbox=new PLAYBOX;
				CMyMp3secDlg *dlggg=this;
				pbox->pmed=dlggg;
				pbox->m_sSongnamep=wavlist;
				pbox->m_sSongpath=Wavpath;
				*/
				pboxx=new PLAYBOX;
				CMyMp3secDlg *dlggg=this;
				pboxx->pmed=dlggg;//////////////////////////////////////////////////////important
				pboxx->m_sSongnamep=wavlist;
				pboxx->m_sSongpath=Wavpath;
				//pboxx->ShowWindow(SW_SHOW);
				//dlggg->ShowWindow (SW_HIDE);
				SetTimer(1,1000,NULL);
				break;
				//FileEnd=FindNextFile(file,&lpFileData);
			}
		}
		//FileEnd=FindNextFile(file,&lpFileData);

	CDialog::OnTimer(nIDEvent);
}

void CMyMp3secDlg::On0()
{
	GetDlgItemText(1,wavlist);
	CMyMp3secDlg::Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v1;
	GetDlgItem(IDC_v1)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On1()
{
	
	GetDlgItemText(1,wavlist);
	wavlist=wavlist+".mp3";
//MessageBox(wavlist,_T("CONTENT"),MB_OK);
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v1;
	GetDlgItem(IDC_v1)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::Onx()
{
	CString SourcePath=directory;
	Wavpath=SourcePath+wavlist;
}



void CMyMp3secDlg::On2()
{
	GetDlgItemText(2,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v2;
	GetDlgItem(IDC_v2)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On3()
{
	GetDlgItemText(3,wavlist);
	wavlist=wavlist+".mp3";
//MessageBox(wavlist,TEXT("wavlist"),MB_OK);
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v3;
	GetDlgItem(IDC_v3)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On4()
{
	GetDlgItemText(4,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v4;
	GetDlgItem(IDC_v4)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On5()
{
	GetDlgItemText(5,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v5;
	GetDlgItem(IDC_v5)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On6()
{
	GetDlgItemText(6,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v6;
	GetDlgItem(IDC_v6)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On7()
{
	GetDlgItemText(7,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v7;
	GetDlgItem(IDC_v7)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On8()
{
	GetDlgItemText(8,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v8;
	GetDlgItem(IDC_v8)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On9()
{
	GetDlgItemText(9,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v9;
	GetDlgItem(IDC_v9)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On10()
{
	GetDlgItemText(10,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v10;
	GetDlgItem(IDC_v10)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On11()
{
	GetDlgItemText(11,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v11;
	GetDlgItem(IDC_v11)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On12()
{
	GetDlgItemText(12,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v12;
	GetDlgItem(IDC_v12)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On13()
{
	GetDlgItemText(13,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v13;
	GetDlgItem(IDC_v13)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::On14()
{
	GetDlgItemText(14,wavlist);
	wavlist=wavlist+".mp3";
	Onx();
	GetDlgItem(preV)->ShowWindow(SW_HIDE);
	preV=IDC_v14;
	GetDlgItem(IDC_v14)->ShowWindow(SW_SHOW);
}

void CMyMp3secDlg::OnCurrent() 
{
	// TODO: Add your control notification handler code here
	int kkk=this->m_thePlayer.GetDuration(); //ȡ�ø���ʱ��
CString j;
j.Format (_T("%s%d"),j,kkk);
MessageBox(j,TEXT("OnCurrent()�е�m_thePlayer.GetDuration()"),MB_OK);
}

void CMyMp3secDlg::OnYanshi() 
{
	// TODO: Add your control notification handler code here
	MessageBox(TEXT("ABC"),TEXT("OnCurrent()�е�m_thePlayer.GetDuration()"),MB_OK);
	//m_yanshi.Empty();
	//m_yanshi.LoadString('a');
	GetDlgItem(IDC_YANSHI)->SetWindowText(_T("china"));
MessageBox(TEXT("DET"),TEXT("OnCurrent()�е�m_thePlayer.GetDuration()"),MB_OK);

	GetDlgItem(IDC_YANSHI)->ShowWindow(SW_HIDE);
MessageBox(TEXT("DET"),TEXT("OnCurrent()�е�m_thePlayer.GetDuration()"),MB_OK);
}

void CMyMp3secDlg::vadd()
{
	long m_lState=m_thePlayer.GetPlayState();
	if(m_lState==2)
	{
		long m_volume=m_thePlayer.GetVolume();
	CString k;
	k.Format(_T("%s%d"),k,m_volume);
	//MessageBox(k,TEXT("m_volume"),MB_OK);
		if(m_volume>-300)
		{
			m_volume=-300;
		}
		m_thePlayer.SetVolume(m_volume+300);
	}
	else return;
}

void CMyMp3secDlg::vnec()
{
	long m_lState=m_thePlayer.GetPlayState();
	if(m_lState==2)
	{
		long m_volume=m_thePlayer.GetVolume();
		if(m_volume<-3000)
		{
			m_volume=-3000;
		}
		m_thePlayer.SetVolume(m_volume-300);
	}
	else return ;
}

void CMyMp3secDlg::OnFirst() 
{
	// TODO: Add your control notification handler code here
	On0();
	n=1;
	file = FindFirstFile(directorystar,&lpFileData);
	if(file!=INVALID_HANDLE_VALUE)
	{
		CString wavlist;
		wavlist=lpFileData.cFileName;
		int dot=wavlist.Find('.');
		wavlist=wavlist.Left(dot);
		GetDlgItem(1)->SetWindowText(wavlist);
		n++;
	}
	int i=2;
	BOOL FileEnd=FindNextFile(file,&lpFileData);
	while(FileEnd != 0)
	{      
		if(i<15)
		{
			CString wavlist;
			wavlist=lpFileData.cFileName;
			int dot=wavlist.Find('.');
			wavlist=wavlist.Left(dot);
			GetDlgItem(i)->SetWindowText(wavlist);	
			if(i<14)
			{
				FileEnd=FindNextFile(file,&lpFileData);
			}
			i++;
			n++;
		}
		else
		{
			FileEnd=0;	
		}			
	}
}

void CMyMp3secDlg::OnPre() 
{
	On0();
	for (int aa=1;aa <15; aa++)//���Ƚ�1��14����̬�ı����
	{
		
		 GetDlgItem(aa)->SetWindowText(_T(""));
	}
	int k,d;
	k=n/14;
	d=n%14;
	if(n<29)
	{
		file = FindFirstFile(directorystar,&lpFileData);
		if(file!=INVALID_HANDLE_VALUE)
		{
			CString wavlist;
			wavlist=lpFileData.cFileName;
			int dot=wavlist.Find('.');
			wavlist=wavlist.Left(dot);
			GetDlgItem(1)->SetWindowText(wavlist);
			n=1;
		}

		int i;
		i=2;
		BOOL FileEnd=FindNextFile(file,&lpFileData);
		while(FileEnd != 0)
		{      
			if(i<15)
			{
				CString wavlist;
				wavlist=lpFileData.cFileName;
				int dot=wavlist.Find('.');
				wavlist=wavlist.Left(dot);
				GetDlgItem(i)->SetWindowText(wavlist);
				if(i<14)
				{
					FileEnd=FindNextFile(file,&lpFileData);
				}
				i++;
				n++;
			}
			else
			{
				FileEnd=0;	
			}
		}
	}

	else //n>=29(���ǵ�n=32),�������ڵ���ҳ��Ҳ�����һҳ��,��ʱn=32��k=2,d=4
	{
		//����n=42,�� k=3,d=0,���ڵ���ҳn=42
		if(d==0)
		{    
			file = FindFirstFile(directorystar,&lpFileData);
			n=1;
			for(int aa=1;aa<14*(k-2);aa++)//aa=1;aa<14;aa++
			{
				FindNextFile(file,&lpFileData);
				n++;				
			}

			int i=1;
			BOOL FileEnd=FindNextFile(file,&lpFileData);
			while(FileEnd != 0)
			{      
				if(i<15)
				{
					CString wavlist;
					wavlist=lpFileData.cFileName;
					int dot=wavlist.Find('.');
					wavlist=wavlist.Left(dot);
					GetDlgItem(i)->SetWindowText(wavlist);
					if(i<14)
					{
						FileEnd=FindNextFile(file,&lpFileData);
					}
					n++;
					i++;
				}
				else
				{
					FileEnd=0;	
				}			
			}
		}


		else//n>=29(���ǵ�n=32),�������ڵ���ҳ��Ҳ�����һҳ��,��ʱn=32��k=2,d=4
		{
		//MessageBox(_T("�������ǵ�ѭ��"));
			file = FindFirstFile(directorystar,&lpFileData);
			n=1;
			for(int aa=1;aa<14*(k-1);aa++)//aa=1;aa<14;aa++
			{
				FindNextFile(file,&lpFileData);
				n++;				
			}
			int i=1;
			BOOL FileEnd=FindNextFile(file,&lpFileData);
			while(FileEnd != 0)
			{      
				if(i<15)
				{
					CString wavlist;
					wavlist=lpFileData.cFileName;
					int dot=wavlist.Find('.');
					wavlist=wavlist.Left(dot);
					GetDlgItem(i)->SetWindowText(wavlist);
					if(i<14)
					{
						FileEnd=FindNextFile(file,&lpFileData);
					}
					n++;
					i++;
				}
				else
				{
					FileEnd=0;	
				}
					
			}
		}
	}
	
}

void CMyMp3secDlg::OnNext() 
{
	On0();
	int i=1;
	BOOL FileEnd=FindNextFile(file,&lpFileData);
	if(FileEnd!= 0)
	{	
		for (int aa=1;aa < 15; aa++)//��8��Ϊ15
		{
		
			GetDlgItem(aa)->SetWindowText(_T(""));
		}
	}
	while(FileEnd != 0)
	{      
		if(i<15)
		{
			CString wavlist;
			wavlist=lpFileData.cFileName;
			int dot=wavlist.Find('.');
			wavlist=wavlist.Left(dot);
			GetDlgItem(i)->SetWindowText(wavlist);
		//��i=13�ҵ���14���ļ�������i=14,����14���ļ���ʾ��
		//������i=14,����if(i<14),i=15,n=28����if(i<15),FileEnd=0,����whileѭ��
			if(i<14)
			{
				FileEnd=FindNextFile(file,&lpFileData);
			}
			n++;
			i++;
		}
		else
		{
			FileEnd=0;	
		}			
	}
	
}

void CMyMp3secDlg::OnEnd() 
{
	On0();
	for (int aa=1;aa <15; aa++)
	{
		
		 GetDlgItem(aa)->SetWindowText(_T(""));
	}
	int k,z=0,d;
	file = FindFirstFile(directorystar,&lpFileData);
	if(file!=INVALID_HANDLE_VALUE)
	{
		z++;//����е�һ���ļ���z��Ϊ1
	}

	BOOL FileEnd=FindNextFile(file,&lpFileData);
	while(FileEnd != 0)
	{      
		z++;    //z������ļ�����Ŀ
		FileEnd=FindNextFile(file,&lpFileData);
	}

	k=z/14;//����z=32,��k=2(ҳ��),d=4(ʣ�����һҶ��)
	d=z%14;

	if(z<=14)//��������ļ��ڵ�һҳ�Ϳ�����ʾ
	{
		file = FindFirstFile(directorystar,&lpFileData);
		if(file!=INVALID_HANDLE_VALUE)
		{
			CString wavlist;
			wavlist=lpFileData.cFileName;

			int dot=wavlist.Find('.');
			wavlist=wavlist.Left(dot);
			GetDlgItem(1)->SetWindowText(wavlist);
			n=0;
			n++; 
		}
		int i=2;
		BOOL FileEnd=FindNextFile(file,&lpFileData);
		while(FileEnd != 0)
		{      
			if(i<15)
			{
				CString wavlist;
				wavlist=lpFileData.cFileName;
				int dot=wavlist.Find('.');
				wavlist=wavlist.Left(dot);
				GetDlgItem(i)->SetWindowText(wavlist);
				n++;
				FileEnd=FindNextFile(file,&lpFileData);
				i++;
			}
			else
			{
				FileEnd=0;	
			}
		}
	}

	else  //z>14
	{
		file = FindFirstFile(directorystar,&lpFileData);
		n=1;
		if(d!=0)////����z=32,��k=2(ҳ��),d=4 (ʣ�����һҳ��)
		{
			for(int aa=0;aa<14*k-1;aa++)//aa����ҳ���ļ���Ŀ������aa=14*2-1=27,aa��0��27
			{
				FindNextFile(file,&lpFileData);
				n++;	//n++ѭ��27�Σ�n������28	��n��ǰ����ҳ�ĸ�����		
			}
		}
		else//d=0����������ҳ��û�����,�������ҳk=2,��n=14;
			//							�������ҳk=3,��n=28;
			//							�������ҳk=4,��n=42;						
		{
			for(int aa=0;aa<14*(k-1)-1;aa++)
			{
				FindNextFile(file,&lpFileData);
				n++;	//n�ǳ����һҳ��ǰ����ҳ�ĸ���
			}

		}
	//CString k;
	//k.Format (TEXT("%s%d"),k,n);
	//MessageBox(k,TEXT("nӦ����28"),MB_OK);
	//����ʾ���һҳʱ��ǰ��ͳ��n��û�����ã�ʵ�����ǿ�FindNextFile()�ƶ�Ѱ��ָ�룬
	//������32���ļ���ǰ������n=1�ҵ���һ���ļ�������ѭ��27�Σ���ʱn=28,�ļ�ָ��ָ���28���ļ���
		int i=1;
		BOOL FileEnd=FindNextFile(file,&lpFileData);//�ļ�ָ��ָ���29���ļ�
		while(FileEnd != 0)
		{      
			if(i<15)
			{
				CString wavlist;
				wavlist=lpFileData.cFileName;
				int dot=wavlist.Find('.');
				wavlist=wavlist.Left(dot);
				GetDlgItem(i)->SetWindowText(wavlist);
				n++;	//n���ָ���32���ļ�
				FileEnd=FindNextFile(file,&lpFileData);
				i++;
			}
			else
			{
				FileEnd=0;	
			}
			
		}
			
	}
	
}



HBRUSH CMyMp3secDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	for(int color=1;color<15;color++)
	{
		if(pWnd->GetDlgCtrlID()==color)
		{
			pDC->SetBkColor(RGB(180,180,180));
			pDC->SetTextColor(RGB(0,0,255));
		}
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
