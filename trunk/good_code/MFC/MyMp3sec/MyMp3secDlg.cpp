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
	DDX_Text(pDX,1,m_1);//下面这些语句使nIDC(比如这里的1、2、3等)与CString m[i]和EDit mcon[i]
						//联系起来，只要设定了m[i]的字体，则可以一老永逸，翻页的显示就不用再设了
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
	ON_BN_CLICKED(2, On2)//使单击文本就执行与图片IDC_v1对应的函数On1()
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
					_T("宋体"));
	
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
			//mcon[n].SetWindowText(m[n]);//这一句也可以，下面一句也可以
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
			//delete pboxx;//必须屏蔽，否则IDD_PLAYBOX将消失
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
	int kkk=this->m_thePlayer.GetDuration(); //取得歌曲时间
CString j;
j.Format (_T("%s%d"),j,kkk);
MessageBox(j,TEXT("OnCurrent()中的m_thePlayer.GetDuration()"),MB_OK);
}

void CMyMp3secDlg::OnYanshi() 
{
	// TODO: Add your control notification handler code here
	MessageBox(TEXT("ABC"),TEXT("OnCurrent()中的m_thePlayer.GetDuration()"),MB_OK);
	//m_yanshi.Empty();
	//m_yanshi.LoadString('a');
	GetDlgItem(IDC_YANSHI)->SetWindowText(_T("china"));
MessageBox(TEXT("DET"),TEXT("OnCurrent()中的m_thePlayer.GetDuration()"),MB_OK);

	GetDlgItem(IDC_YANSHI)->ShowWindow(SW_HIDE);
MessageBox(TEXT("DET"),TEXT("OnCurrent()中的m_thePlayer.GetDuration()"),MB_OK);
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
	for (int aa=1;aa <15; aa++)//首先将1到14个静态文本清空
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

	else //n>=29(我们的n=32),例如现在第三页（也是最后一页）,此时n=32则k=2,d=4
	{
		//假如n=42,则 k=3,d=0,现在第三页n=42
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


		else//n>=29(我们的n=32),例如现在第三页（也是最后一页）,此时n=32则k=2,d=4
		{
		//MessageBox(_T("进入我们的循环"));
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
		for (int aa=1;aa < 15; aa++)//将8改为15
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
		//当i=13找到第14个文件，接着i=14,将第14个文件显示。
		//接着因i=14,跳过if(i<14),i=15,n=28跳过if(i<15),FileEnd=0,跳出while循环
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
		z++;//如果有第一个文件，z变为1
	}

	BOOL FileEnd=FindNextFile(file,&lpFileData);
	while(FileEnd != 0)
	{      
		z++;    //z最后是文件的数目
		FileEnd=FindNextFile(file,&lpFileData);
	}

	k=z/14;//例如z=32,则k=2(页数),d=4(剩在最后一叶的)
	d=z%14;

	if(z<=14)//如果所有文件在第一页就可以显示
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
		if(d!=0)////例如z=32,则k=2(页数),d=4 (剩在最后一页的)
		{
			for(int aa=0;aa<14*k-1;aa++)//aa是整页的文件数目，例如aa=14*2-1=27,aa从0到27
			{
				FindNextFile(file,&lpFileData);
				n++;	//n++循环27次，n最后等于28	（n是前面整页的个数）		
			}
		}
		else//d=0，表明是整页，没有余的,如果整两页k=2,则n=14;
			//							如果整三页k=3,则n=28;
			//							如果整四页k=4,则n=42;						
		{
			for(int aa=0;aa<14*(k-1)-1;aa++)
			{
				FindNextFile(file,&lpFileData);
				n++;	//n是除最后一页外前面整页的个数
			}

		}
	//CString k;
	//k.Format (TEXT("%s%d"),k,n);
	//MessageBox(k,TEXT("n应该是28"),MB_OK);
	//在显示最后一页时，前面统计n并没有作用，实际上是靠FindNextFile()移动寻找指针，
	//例如有32个文件，前面首先n=1找到第一个文件，接着循环27次（这时n=28,文件指针指向第28个文件）
		int i=1;
		BOOL FileEnd=FindNextFile(file,&lpFileData);//文件指针指向第29个文件
		while(FileEnd != 0)
		{      
			if(i<15)
			{
				CString wavlist;
				wavlist=lpFileData.cFileName;
				int dot=wavlist.Find('.');
				wavlist=wavlist.Left(dot);
				GetDlgItem(i)->SetWindowText(wavlist);
				n++;	//n最后指向第32个文件
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
