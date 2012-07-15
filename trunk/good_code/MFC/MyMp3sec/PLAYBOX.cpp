// PLAYBOX.cpp : implementation file
//

#include "stdafx.h"
#include "MyMp3sec.h"
#include "PLAYBOX.h"
#include "Delog.h"
#include "ProgCtrlVol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PLAYBOX dialog
PLAYBOX::PLAYBOX(CWnd* pParent /*=NULL*/)
	: CDialog(PLAYBOX::IDD, pParent)
{
	//{{AFX_DATA_INIT(PLAYBOX)
	m_sSongnamep=_T("");
	m_exe = _T("");
	//}}AFX_DATA_INIT
	PEXIT.LoadBitmaps(IDB_PEXIT);
	PPAUSE.LoadBitmaps(IDB_PPAUSE);
	PREPLAY.LoadBitmaps(IDB_PREPLAY);
	PBACK.LoadBitmaps(IDB_PBACK);
	PVOLNEC.LoadBitmaps(IDB_PVOLNEC,IDB_PVOLNECC);
	PVOLADD.LoadBitmaps(IDB_PVOLADD,IDB_PVOLADDD);
	PPICTURE.LoadBitmaps(IDB_BITMAP13);///////////////////////
	PPICTURE1.LoadBitmaps(IDB_BITMAP22);
}


void PLAYBOX::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PLAYBOX)
	
	DDX_Control(pDX, IDC_BMPSHOWVOLUME, m_bmpvol);
	DDX_Control(pDX,IDC_BMPSHOW,m_bmpprog);

	DDX_Text(pDX, IDC_EXE, m_exe);
	DDX_Control(pDX, IDC_EXE, m_controlexe);
	//DDX_Control(pDX,IDC_EXE,m_execon);

	DDX_Text(pDX,IDC_SONAME,m_sSongnamep);
	DDX_Control(pDX,IDC_SONAME,m_sSongnamepcon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PLAYBOX, CDialog)
	//{{AFX_MSG_MAP(PLAYBOX)
	ON_BN_CLICKED(IDC_PEXIT, OnPexit)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PREPLAY, OnPreplay)
	ON_BN_CLICKED(IDC_PPAUSE, OnPpause)
	ON_BN_CLICKED(IDC_PVOLNEC, OnPvolnec)
	ON_BN_CLICKED(IDC_PVOLADD, OnPvoladd)
	ON_BN_CLICKED(IDC_PBACK, OnPback)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PLAYBOX message handlers

void PLAYBOX::OnPexit() 
{
	// TODO: Add your control notification handler code here
	//OnOK();
	//pmed->KillTimer(1);
	//pmed->KillTimer(2);
	//pmed->m_thePlayer.Stop();
	KillTimer(2);
	KillTimer(3);
	KillTimer(4);
	PLAYBOX::OnOK();
	DestroyWindow();
	pmed->m_thePlayer.Stop ();
	//pmed->KillTimer(1);
	//pmed->ShowWindow(SW_SHOW);
	//pmed->delete pboxx;
}

void PLAYBOX::OnPback() 
{
	KillTimer(2);////////////////////////////////////////////////////
	KillTimer(3);
	KillTimer(4);
	pmed->m_thePlayer.Stop ();
	//PLAYBOX::OnOK();///////////////////////////////////////////////////
	PLAYBOX::DestroyWindow();
	//DestroyWindow();
	//pmed->KillTimer(1);
}

BOOL PLAYBOX::OnInitDialog() 
{
//MessageBox(TEXT("enter PLAYBOX"),TEXT("提示"),MB_OK);
	CDialog::OnInitDialog();
	VERIFY(PEXIT.SubclassDlgItem(IDC_PEXIT,this));
	PEXIT.SizeToContent();
	VERIFY(PPAUSE.SubclassDlgItem(IDC_PPAUSE,this));
	PPAUSE.SizeToContent();
	VERIFY(PREPLAY.SubclassDlgItem(IDC_PREPLAY,this));
	PREPLAY.SizeToContent();
	VERIFY(PBACK.SubclassDlgItem(IDC_PBACK,this));
	PBACK.SizeToContent();
	VERIFY(PVOLNEC.SubclassDlgItem(IDC_PVOLNEC,this));
	PVOLNEC.SizeToContent();
	VERIFY(PVOLADD.SubclassDlgItem(IDC_PVOLADD,this));
	PVOLADD.SizeToContent();

	VERIFY(PPICTURE.SubclassDlgItem(IDC_PPICTURE, this));///////////////////////////
	PPICTURE.SizeToContent();
	VERIFY(PPICTURE1.SubclassDlgItem(IDC_PPICTURE1, this));
	PPICTURE1.SizeToContent();

	time=new CFont;
	time->CreateFont(18,0,0,0,900,FALSE,FALSE,0,
					ANSI_CHARSET,OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH|FF_SWISS,
					_T("宋体"));
	m_sSongnamepcon.SetFont(time);
	m_sSongnamep="曲目名称："+m_sSongnamep;
	m_sSongnamepcon.SetWindowText(m_sSongnamep);

	m_bmpprog.SetRange(0,songduration);//songduration
	m_bmpprog.SetStep(1);//1
	m_bmpprog.SetPos(0);
	m_bmpprog.StepIt();

	SetTimer(1,800,NULL);//200
	//SetTimer(3,1000,NULL);//1000
	//SetTimer(4,500,NULL);
	//i=0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PLAYBOX::test()
{
	songduration=pmed->m_thePlayer.GetDuration();
	KillTimer(1);
	int minute=songduration/60;
	int second=songduration%60;
CString k;
k.Format(_T("%s%d"),k,minute);
CString kk;
kk.Format(_T("%s%d"),kk,second);
//MessageBox(k,TEXT("K"),MB_OK);//213
	//j.Format (_T("%s%d"),j,songduration);
//MessageBox(j,TEXT("j"),MB_OK);//179213
	//CString jj=j.Right(3);
//MessageBox(jj,TEXT("jj"),MB_OK);//213
	//GetDlgItem(IDC_EXE)->SetWindowText(_T(""));
	//GetDlgItem(IDC_EXE)->SetWindowText(j);
	//UpdateData(FALSE);
	if(second<10)
	{
		kk="0"+kk;
	}
	CString kkk="曲目长度："+k+":"+kk;
	//m_execon.SetFont(time);
	//m_execon.SetWindowText(kkk);
//MessageBox(kkk,TEXT("kkk"),MB_OK);
	m_controlexe.SetFont(time);
	m_controlexe.SetWindowText(kkk);
	m_bmpprog.SetRange(0,songduration);//songduration
	m_bmpprog.SetStep(1);//1
	m_bmpprog.SetPos(0);
	m_bmpprog.StepIt();

	i=0;
	SetTimer(3,1000,NULL);//1000
	SetTimer(4,500,NULL);
}

void PLAYBOX::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1:
		test();
		//KillTimer(1);
		break;
	case 2:
		
		m_lState=pmed->m_thePlayer.GetPlayState();
		if(m_lState==0)
		{
			KillTimer(2);
		//MessageBox(TEXT("FIRST SONG OVER"),TEXT("CONMENT"),MB_OK);
			BOOL FileEnd=FindNextFile(playboxfile,&lpFileData);
			while(FileEnd!=0)
			{
			//MessageBox(TEXT("enter FileEnd"),TEXT("CONMENT"),MB_OK);
				CString wavlist;
				wavlist=lpFileData.cFileName;
				playboxWavpath=playboxdirectory+wavlist;
			//MessageBox(playboxWavpath,TEXT("playboxWavpath"),MB_OK);
				pmed->m_thePlayer.SetFileName(playboxWavpath);
				pmed->m_thePlayer.Play();
				this->m_sSongnamep=wavlist;
				this->m_sSongpath=playboxWavpath;
				//m_sSongnamep=_T("");
				//m_exe = _T("");
				//m_controlexe.ShowWindow(true);
				//m_controlexe.SetWindowText(_T(""));
				GetDlgItem(IDC_SONAME)->SetWindowText(_T(""));
				GetDlgItem(IDC_SONAME)->SetWindowText(m_sSongnamep);
			//MessageBox(m_sSongnamep,TEXT("m_sSongnamep"),MB_OK);
				SetTimer(1,500,NULL);//1000
				i=0;
				SetTimer(2,1000,NULL);
				//test();
				break;
			}
		}
		break;
		
	case 3:
		/*
		CString State=pmed->m_thePlayer.GetPlayState();
		if(State==2)
		{
			if(PPICTURE.ShowWindow(1))
			{
			PPICTURE1.ShowWindow(1);
			PPICTURE.ShowWindow(0);
			}
			else
			{
			PPICTURE.ShowWindow(1);
			PPICTURE1.ShowWindow(0);}
		}
		else
		{PPICTURE.ShowWindow(1);}
		*/
		i+=1;
		//CString progresstime;
		progresstime.Format(_T("%d"),i);
		//progresstime.Format(_T("%s%d"),progresstime,i);
		GetDlgItem(IDC_PROGRESSTIME)->SetWindowText(progresstime);
		//GetDlgItem(IDC_PROGRESSTIME)->SetWindowText(CString(i));
		m_bmpprog.StepIt();
		if(i>=songduration)
		{
			KillTimer(3);
			i=0;
		}
		break;
	case 4:
		State=pmed->m_thePlayer.GetPlayState();
		if(State==2)
		{
			if(PPICTURE.ShowWindow(1))
			{
			PPICTURE1.ShowWindow(1);
			PPICTURE.ShowWindow(0);
			}
			else
			{
			PPICTURE.ShowWindow(1);
			PPICTURE1.ShowWindow(0);}
		}
		else
		{PPICTURE.ShowWindow(1);}
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void PLAYBOX::OnPreplay() 
{
	// TODO: Add your control notification handler code here
	//KillTimer(2);
	KillTimer(3);
	pmed->m_thePlayer.Stop();
	m_bmpprog.SetPos(0);
	m_bmpprog.StepIt();
	SetTimer(3,1000,NULL);
	i=0;
	pmed->m_thePlayer.SetFileName(m_sSongpath);
	pmed->m_thePlayer.Play();
}

void PLAYBOX::OnPpause() 
{
	// TODO: Add your control notification handler code here
	int playstate=pmed->m_thePlayer.GetPlayState();
CString j;
j.Format(_T("%d"),playstate);
//MessageBox(j,TEXT("playstate"),MB_OK);
	if(playstate==2)
	{
		KillTimer(3);
		pmed->m_thePlayer.Pause();
	}
	else if(playstate==1)
	{
		SetTimer(3,1000,NULL);
		pmed->m_thePlayer.Play();
	}
}

void PLAYBOX::OnPvolnec() 
{
	// TODO: Add your control notification handler code here
	m_bmpvol.StepItt();
	pmed->vnec();

}

void PLAYBOX::OnPvoladd() 
{
	// TODO: Add your control notification handler code here
	m_bmpvol.StepIt();
	pmed->vadd();
}

void PLAYBOX::PLAYALL()
{
	//playboxdirectory="\\Temp\\";
	playboxdirectory="\\Storage Card\\";
	CString wavlist;
	//playboxfile=FindFirstFile(_T("\\Temp\\*.mp3"),&lpFileData);
	playboxfile=FindFirstFile(_T("\\Storage Card\\*.mp3"),&lpFileData);
	if(playboxfile!=INVALID_HANDLE_VALUE)
	{
	
		wavlist=lpFileData.cFileName;
		//MessageBox(wavlist,TEXT("wavlist"),MB_OK);
		//GetDlgItem(1)->SetWindowText(wavlist);
		//n++;
		playboxWavpath=playboxdirectory+wavlist;
	}
	//pmed->m_thePlayer.SetFileName(playboxWavpath);
	//pmed->m_thePlayer.Play();
	//this->m_sSongnamep=wavlist;
	//this->m_sSongpath=playboxWavpath;
	SetTimer(2,1000,NULL);
	//i=0;
}





HBRUSH PLAYBOX::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_SONAME)
	{
		pDC->SetBkColor(RGB(200,200,200));
		pDC->SetTextColor(RGB(0,0,255));
	}

	if(pWnd->GetDlgCtrlID()==IDC_EXE)
	{
		pDC->SetBkColor(RGB(200,200,200));
		pDC->SetTextColor(RGB(255,0,0));
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
