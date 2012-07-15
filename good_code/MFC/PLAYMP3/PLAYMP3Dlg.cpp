 // PLAYMP3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "PLAYMP3.h"
#include "PLAYMP3Dlg.h"
//#include "OpenFileDlg.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lrc.h"
#include "fullpathfile.h"


//#define WM_SUSPEND WM_USER+9

extern CString strPath;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//COpenFileDlg openfile_dlg;
CFullPathFile openfile_dlg;
/////////////////////////////////////////////////////////////////////////////
// CPLAYMP3Dlg dialog

#define WM_SUSPEND WM_USER+9
#define SLIDER_TIMER   100

#define WM_SET_VOL WM_USER+229

static TCHAR gszBaseInstance[256] = _T("ControlPanel\\Volume");
HKEY g_hkVolume = NULL;//



CPLAYMP3Dlg::CPLAYMP3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPLAYMP3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPLAYMP3Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	mFilterGraph = NULL;
	mSourceFile  = "";
	mSliderTimer = 0;
	b_play_or_pause = true;
	str_lrc = L"";
	
	b_yesLrc = false;
	mp3Info = false;
	b_mp3info = false;
	b_btn_round = true;
	b_beginPlay = false;//最开始不播放
	temp_time = "00:00";
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CPLAYMP3Dlg::~CPLAYMP3Dlg()
{
	mp3DestroyGraph();
}

void CPLAYMP3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPLAYMP3Dlg)
	DDX_Control(pDX, IDC_STATE_DIAN, m_StateDian);
	DDX_Control(pDX, IDC_VOL_DIAN, m_VolDian);
	DDX_Control(pDX, IDC_NAMEING, m_Nameing);
	DDX_Control(pDX, IDC_PLAYING, m_Playing);
	DDX_Control(pDX, IDC_PLAYTIME, m_PlayTime);
	DDX_Control(pDX, IDC_LRCNEW, m_NewLrc);
	DDX_Control(pDX, IDC_LIST, m_ListMp3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPLAYMP3Dlg, CDialog)
	//{{AFX_MSG_MAP(CPLAYMP3Dlg)
	ON_WM_CTLCOLOR()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_SUSPEND,OnSuspend)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_WM_SETFOCUS()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, OnOK)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPLAYMP3Dlg message handlers

BOOL CPLAYMP3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_StateDian.MoveWindow(150,201,29,20);

	

	
	::SetWindowPos(this->GetSafeHwnd(), HWND_TOPMOST,0, 0, 
		480, 272,SWP_SHOWWINDOW);

	RegOpenKeyEx(HKEY_CURRENT_USER, gszBaseInstance, 0, 0, &g_hkVolume);



	xxx = 0;
	bei = 0;

	m_ListMp3.MoveWindow(41,56,67,162);//
	m_ListMp3.SetItemHeight(NULL ,18);//设LIST列表行间矩
	m_ListMp3.ShowWindow(SW_HIDE);

	kkk_minute= "";
	kkk_second= "";
	b_volume = true;

	CoInitialize(NULL); 
	
	GetVolume();//得到当前声音

	CenterWindow(GetDesktopWindow());	// center to the hpc screen
	// TODO: Add extra initialization here
	m_BackScreenBitmap.LoadBitmap(IDB_BKG);

	SetToolRectangle();
	
	m_listPick = 0;

	BYTE m_Byte[16]={0x33 ,0x26,0xB2 ,0x75, 0x8E ,0x66 ,0xCF, 0x11 ,0xA6 ,0xD9, 0x00, 0xAA ,0x00 ,0x62 ,0xCE, 0x6C};//wma文件头。
	char cBuffer[100];
	memcpy(cBuffer,m_Byte,sizeof(m_Byte));
	strWmaTAG = cBuffer;//得到标准的WMA前字节字符串。


	
	m_Playing.MoveWindow(180,53,220,27);
	m_Nameing.MoveWindow(180,80,220,27);

	
	m_PlayTime.MoveWindow(180,126-6,220,14);
	m_NewLrc.MoveWindow(180,150-4,225,35);

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}




void CPLAYMP3Dlg::DrawInterface(CDC &dc)
{
	CDC  memDC ;
	memDC.CreateCompatibleDC ( &dc ) ;
	
	
	CBitmap*  pBitmap ;		//load all bitmap
	CBitmap*  pOldBitmap ;	//save old bitmap temp
	
	
	/////////////////////////////////////////////////
	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	pBitmap ->LoadBitmap ( IDB_UP_W) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	dc.BitBlt ( m_rect[0].TopLeft().x, m_rect[0].TopLeft().y, 158, 158, &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	delete pBitmap ;
	//////////////////////////////////////////////
	
	//.............................................................
	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	pBitmap ->LoadBitmap ( IDB_DOWN_W ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	dc.BitBlt ( m_rect[1].TopLeft().x, m_rect[1].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	delete pBitmap ;
	
	//...............................................................
	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	pBitmap ->LoadBitmap ( IDB_ADD_W ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	dc.BitBlt ( m_rect[2].TopLeft().x, m_rect[2].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	delete pBitmap ;
	//................................................................
	
	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	pBitmap ->LoadBitmap ( IDB_SUB_W ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	dc.BitBlt ( m_rect[3].TopLeft().x, m_rect[3].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	delete pBitmap ;
	//................................................................

	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	
	if (!b_play_or_pause) 
	{
		pBitmap ->LoadBitmap ( IDB_SPAUSE_B ) ;
		pOldBitmap = memDC.SelectObject ( pBitmap ) ;
		
		//将图片COPY到指定的像素位置
		dc.BitBlt ( m_rect[4].TopLeft().x, m_rect[4].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;

	}
	else
		{		
			pBitmap ->LoadBitmap ( IDB_PLAYMP3_W ) ;
			pOldBitmap = memDC.SelectObject ( pBitmap ) ;
			
			//将图片COPY到指定的像素位置
			dc.BitBlt ( m_rect[4].TopLeft().x, m_rect[4].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;
		}
		
	memDC.SelectObject ( pOldBitmap ) ;
	delete pBitmap ;
	
	//................................................................
	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	pBitmap ->LoadBitmap ( IDB_STOP_W ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	dc.BitBlt ( m_rect[5].TopLeft().x, m_rect[5].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	//释放bitmap对象内存
	delete pBitmap ;

	///////////////////////////////////////
	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	pBitmap ->LoadBitmap ( IDB_LEFT_W ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	dc.BitBlt ( m_rect[6].TopLeft().x, m_rect[6].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	delete pBitmap ;
	////////////////////////

	
	//////////////////////
	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	pBitmap ->LoadBitmap ( IDB_RIGHT_W ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	dc.BitBlt ( m_rect[7].TopLeft().x, m_rect[7].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	delete pBitmap ;
	/////////////////////////////////////////////////


	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	pBitmap ->LoadBitmap ( IDB_ROUND_W ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	dc.BitBlt ( m_rect[8].TopLeft().x, m_rect[8].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	delete pBitmap ;
	/////////////////////


	//////////////////////
	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	pBitmap ->LoadBitmap ( IDB_CLOSE_W ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	dc.BitBlt ( m_rect[9].TopLeft().x, m_rect[9].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	delete pBitmap ;


	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	pBitmap ->LoadBitmap ( IDB_CANCEL_W ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	dc.BitBlt ( m_rect[10].TopLeft().x, m_rect[10].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	//释放bitmap对象内存
	delete pBitmap ;
	
	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	pBitmap ->LoadBitmap ( IDB_volume ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	dc.BitBlt ( m_rect[11].TopLeft().x, m_rect[11].TopLeft().y, 111, 111, &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	//释放bitmap对象内存
	delete pBitmap ;

	memDC.DeleteDC ()  ;
}

HBRUSH CPLAYMP3Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{

	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_LISTBOX)
	{
	//	pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(0,0,0));
		m_brMine = ::CreateSolidBrush(RGB(0,0,0));
		return m_brMine;
	}
	if(nCtlColor == CTLCOLOR_EDIT)
	{
	//	pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(250,200,150));
		pDC->SetBkColor(RGB(99,99,99));
		m_brMine = ::CreateSolidBrush(RGB(99,99,99));
		return m_brMine;
	}

	if(nCtlColor == CTLCOLOR_STATIC )
	{
	//	pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(99,99,99));
		m_brMine = ::CreateSolidBrush(RGB(99,99,99));
		return m_brMine;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;

}

void CPLAYMP3Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPLAYMP3Dlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default


	for ( int i = 0 ; i < 12 ; i ++ ) 
	{		
		if (  m_rect[i].PtInRect (point)   )
		{									
		
	
				CDC* pDC = GetDC () ;
				CDC  memDC ;
				memDC.CreateCompatibleDC ( pDC ) ;
				
				CBitmap   bmp1 ;
				switch ( i )
				{
				case 0:
					{			
						bmp1.LoadBitmap ( IDB_UP_B ) ;
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
				case 1:			
					{				
						bmp1.LoadBitmap ( IDB_DOWN_B) ;
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
				case 2:
					{							
						bmp1.LoadBitmap ( IDB_ADD_B ) ;
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
				case 3:
					{
						bmp1.LoadBitmap ( IDB_SUB_B) ;
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
				case 4:
						break ;
				case 5:
					{
						bmp1.LoadBitmap ( IDB_STOP_B ) ;
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
				case 6:
					{
						bmp1.LoadBitmap ( IDB_LEFT_B ) ;
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
				case 7:
					{
						bmp1.LoadBitmap ( IDB_RIGHT_B ) ;
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
		
				case 8:
					{
						bmp1.LoadBitmap ( IDB_ROUND_B ) ;
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
				case 9:
					{
						bmp1.LoadBitmap ( IDB_CLOSE_B ) ;
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
				case 10:
					{
						bmp1.LoadBitmap ( IDB_CANCEL_B ) ;
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
				
				}
				
				memDC.DeleteDC () ;
				ReleaseDC ( pDC ) ;
				
		}
	}

}

void CPLAYMP3Dlg::OnLButtonUp(UINT nFlags, CPoint point) 
{

	if(b_beginPlay)//开始播放后才可能按进度条。
		if (point.x > 151 && point.x < 270 && point.y > 200 &&point.y < 220)
		{
			double duration = 1.;
			mFilterGraph->GetDuration(&duration);
			if (point.x < 151+15)
			{
				double pos = duration * (point.x - 151) / 101;  //-15,是为了，到按纽中间
				mFilterGraph->SetCurrentPosition(pos);
			}
			else
			{
				double pos = duration * (point.x - 151 - 15) / 101;  //-15,是为了，到按纽中间
				mFilterGraph->SetCurrentPosition(pos);

			}
			
		}
		
	CopyBMP(IDB_UP_W,0);
	CopyBMP(IDB_DOWN_W,1);
	CopyBMP(IDB_ADD_W,2);
	CopyBMP(IDB_SUB_W,3);
//	CopyBMP(IDB_PLAYMP3_B,4);
	CopyBMP(IDB_STOP_W,5);
	CopyBMP(IDB_LEFT_W,6);
	CopyBMP(IDB_RIGHT_W,7);
	CopyBMP(IDB_ROUND_W,8);
	CopyBMP(IDB_CLOSE_W,9);
	CopyBMP(IDB_CANCEL_W,10);

	for ( int i = 0 ; i < 12 ; i ++ ) 
	{		
		if ( m_rect[i].PtInRect (point)   )
		{
				switch (i)
				{
					
				case 0:
					Btn_Up();
					break ;
				case 1:
					Btn_Down();
					break;
				case 2:
					Btn_Add();
					break ;
				case 3:	
					Btn_Sub();
					break ;
				case 4:		 
					Btn_Play();
					break ;
				case 5:		
					Btn_Stop();
					break ;
				case 6:			
					Btn_Left();
					break ;
				case 7:		
					Btn_Right();
						break ;
				case 8:		 
					Btn_Round();
					break ;
				case 9:		 
					Btn_Close();
					break ;
				case 10:
					Btn_Cancel();
					break ;
				case 11:
					Btn_NoVolume();
					break;
				}
		}
		
	}


}

void CPLAYMP3Dlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	DrawInterface(dc);

	if (b_mp3info &&(m_ListMp3.GetCount() > 0))
	{

		//设字体大小
		CFont font;
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = 18;
		lf.lfWeight = FW_BOLD;//粗体
	//	lf.lfItalic = TRUE;//斜体

		dc.SetTextColor(RGB(255,255,255));
		lstrcpy(lf.lfFaceName, _T("Arial"));
	    VERIFY(font.CreateFontIndirect(&lf));
	    CFont* def_font = dc.SelectObject(&font);
		CString _str_temp_stater = "";
		dc.SetBkMode(TRANSPARENT);//透明
		
		

		_name1 = _name2 = "";

		_name1.Format(L"正在播放: %s",mp3Title);
		_name2.Format(L"演唱: %s",mp3Artist);

		//显示歌曲信息时，如果长度大于，20时。左对齐。反。之中间对齐
		if (GetCStringLen(_name1) > 23) 
		{
//			m_Playing.SetMargins()
			m_Playing.SetWindowText(_name1);
		   //dc.DrawText(_name1,CRect(103,53,291,70),ETO_CLIPPED| DT_LEFT);
		}
		else
			m_Playing.SetWindowText(_name1);
			//dc.DrawText(_name1,CRect(103,53,291,70),ETO_CLIPPED| DT_CENTER);
	
		if (GetCStringLen(_name2) > 23) 
		{
			m_Nameing.SetWindowText(_name2);
			//dc.DrawText(_name2,CRect(102,77,294,96),ETO_CLIPPED| DT_LEFT);
		}
		else
			m_Nameing.SetWindowText(_name2);
			//dc.DrawText(_name2,CRect(102,77,294,96),ETO_CLIPPED| DT_CENTER);
		//显示。状态情况
		dc.SetTextColor(RGB(255,255,255));


	}


}

BOOL CPLAYMP3Dlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	BITMAP bmpInfo;
	m_BackScreenBitmap.GetBitmap(&bmpInfo);
	
	// Create an in-memory DC compatible with the
	// display DC we're using to paint
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	
	
	// Select the bitmap into the in-memory DC
	CBitmap* pOldBitmap = dcMemory.SelectObject(&m_BackScreenBitmap);
	
	// Find a centerpoint for the bitmap in the client area
	CRect rect;
	GetClientRect(&rect);
	
	// Copy the bits from the in-memory DC into the on-
	// screen DC to actually do the painting. Use the centerpoint
	// we computed for the target offset.
	pDC->BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 
		0, 0, SRCCOPY);
	
	dcMemory.SelectObject(pOldBitmap);
	return TRUE;
}

void CPLAYMP3Dlg::CopyBMP(int m_map, int i)
{
	CDC* pDC = GetDC () ;
	CDC  memDC ;
	memDC.CreateCompatibleDC ( pDC ) ;
	CBitmap bmp,bmp1 ;
	CBitmap* pOldBitmap ;
	bmp1.LoadBitmap ( m_map) ;
	pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
	pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
	m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
	memDC.SelectObject ( pOldBitmap ) ;
	
	memDC.DeleteDC () ;
	ReleaseDC ( pDC ) ;	
}

void CPLAYMP3Dlg::SetToolRectangle()
{


	m_rect[0].SetRect(41,26,41+68,26+26);//up
	m_rect[1].SetRect(41,218,41+68,218+27);//down
	m_rect[2].SetRect(277,225,277+32,225+32);//+
	m_rect[3].SetRect(312,225,312+32,225+32);//-
	m_rect[4].SetRect(139,225,139+27,225+27);//spause play
	m_rect[5].SetRect(173,225,173+27,225+27);//stop
	m_rect[6].SetRect(207,225,207+27,225+27);//left
	m_rect[7].SetRect(244,225,244+27,225+27);//right
	m_rect[8].SetRect(382,224,382+27,224+27); //round
	m_rect[9].SetRect(388,25,388+21,25+20);//close
	m_rect[10].SetRect(436,221,436+33,221+33);//cancel
	m_rect[11].SetRect(290,201,290+21,201+20);//vol




}


void CPLAYMP3Dlg::Btn_Up()
{
	if (bei ==0 ) return;
	bei --;
	
	int 	n_height = bei * 5;

	m_ListMp3.SetTopIndex(n_height);

}

void CPLAYMP3Dlg::Btn_Down()
{
	int yu;

	int lllll = m_ListMp3.GetCount() ;

	yu = (m_ListMp3.GetCount()/5) * 5    + 1;

	if (bei == (m_ListMp3.GetCount()/5)) 
	{
		return;
	}

	int n_height = 0;
	n_height = (++bei) * 5 ;

	

	if (n_height > m_ListMp3.GetCount() )
	{
		m_ListMp3.SetTopIndex(yu);
	}	
	else
		m_ListMp3.SetTopIndex(n_height);


}

void CPLAYMP3Dlg::Btn_Add()
{
	
	//int  nResponse = openfile_dlg.DoModal();
	int nResponse = openfile_dlg.DoModal();
	
	if (nResponse == IDOK) 
	{
		
		//没有名称，不显示。
		if (openfile_dlg.array_str.GetSize() > 0)
		{
			newPos = 0;

			//4.10后添的。
			AddToListBox();
			//可以去掉虚线框
			if (m_ListMp3.GetCount() > 0 )
			{
				m_ListMp3.ShowWindow(SW_SHOW);
			}
			else
				m_ListMp3.ShowWindow(SW_HIDE);
		}
		
	} 
	if(nResponse == IDCANCEL)
	{
		b_mp3info = FALSE;
		newPos = 0;
		Invalidate();

	}
 
}


void CPLAYMP3Dlg::Btn_Sub()
{
//	b_sub = true;

//	InvalidateRect(CRect(103,53,294,96));

	newPos = 0;
	mp3Stop();
	mp3DestroyGraph();

	int xxxx,yyyy;
	if (m_ListMp3.GetCurSel() < 0)//
	{	
		xxxx = m_ListMp3.GetCount();
		yyyy = openfile_dlg.array_str.GetSize();

		CString pppp;

		
	//	m_ListMp3.GetText(0,pppp);

		pppp = openfile_dlg.array_str.GetAt(0);


		m_ListMp3.DeleteString(0);

		if (yyyy == 0) 
		{
			return;
		}
		
		for(int i = 0;i<openfile_dlg.array_str.GetSize();i++)
		{
			if (pppp == openfile_dlg.array_str.GetAt(i))
			{
				openfile_dlg.array_str.RemoveAt(i);
			}
		}
//		openfile_dlg.array_str.RemoveAt(0);
	

	}
	else
	{
		xxxx = m_ListMp3.GetCount();
		yyyy = openfile_dlg.array_str.GetSize();

		int xx = m_ListMp3.GetCurSel();


		CString str111111;
		
	//	m_ListMp3.GetText(xx,str111111);

	str111111 =openfile_dlg.array_str.GetAt(xx);

		
		m_ListMp3.DeleteString(m_ListMp3.GetCurSel());


		
		yyyy = openfile_dlg.array_str.GetSize();



		for(int i = 0;i<openfile_dlg.array_str.GetSize();i++)
		{

//			m_ListMp3.GetText( xx,str111111);
			str111111 =  openfile_dlg.array_str.GetAt(xx);


			if (str111111 == openfile_dlg.array_str.GetAt(i))
			{
				openfile_dlg.array_str.RemoveAt(i);
			}
		}
		
	//	openfile_dlg.array_str.RemoveAt(m_ListMp3.GetCurSel());


	}

}

void CPLAYMP3Dlg::Btn_Play()
{
//	int m = m_ListMp3.GetCount();
	m_Playing.ShowWindow(true);
	m_Nameing.ShowWindow(true);

	
	m_PlayTime.ShowWindow(true);
	m_NewLrc.ShowWindow(true);


	if (m_ListMp3.GetCount() == 0)
	{
		return;
	}
	//最开始没有点中列表时，默认播放第一首。
	if (m_ListMp3.GetCurSel() < 0 && m_ListMp3.GetCount() > 0)
	{
		CopyBMP(IDB_PLAYMP3_W,4);
	

		CString name_ ;
		m_ListMp3.SetCurSel(0);//设定蓝条。
	//	m_ListMp3.GetText(0,name_);
		name_ = openfile_dlg.array_str.GetAt(0);


		mSourceFile = name_;

	//	mSourceFile.Format(strPath + L"mp3\\%s",name_);

		GetMp3INFO(mSourceFile);
		b_mp3info = true;
		
		str_lrc = L"";
		CString strMP3NAME,strLRCNAME;
		strMP3NAME = mSourceFile.Left(mSourceFile.GetLength() - 4);	
		strLRCNAME = strMP3NAME + ".lrc";

		lrc.Free();
		
		if ((lrc.Open(strLRCNAME)))
		{
			b_yesLrc = true;
		}
		else
		{
			str_lrc = L"";
			//m_lrc.SetWindowText(str_lrc);
			m_NewLrc.SetWindowText(str_lrc);
//			m_lrc.ShowWindow(SW_HIDE);
		}
		

		InvalidateRect(CRect(103,53,293,110),false);
		mp3CreateGraph();
		b_play_or_pause = true;

	}

	if (b_play_or_pause)//开始和暂停切换
	{
		b_beginPlay = true;//开始播放,此时可以按快进，快退，和停止
		CopyBMP(IDB_SPAUSE_B,4);
		
		mp3PLAY();
	}
	if (!b_play_or_pause)
	{
		CopyBMP(IDB_PLAYMP3_W,4);
		mp3Pause();
		
	}

	b_play_or_pause = !b_play_or_pause;

}

void CPLAYMP3Dlg::Btn_Stop()
{
	CopyBMP(IDB_PLAYMP3_W,4);
	newPos = 0;//要按两下才可以再播放。以后再改。
	mp3Stop();
}


void CPLAYMP3Dlg::Btn_Left()
{
	if (m_ListMp3.GetCount() == 1)
	{
		return;
	}
	if (m_ListMp3.GetCount() <= 0 )//没有歌曲时。
	{
		return;
	}
	//左移
	int x = m_ListMp3.GetCurSel() - 1;

	
	CopyBMP(IDB_SPAUSE_B,4);
		if (!b_btn_round)//随 机
		{
			int l_max = m_ListMp3.GetCount();
			srand( WCE_FCTN(time) (NULL) );
			x =	rand()%(l_max );
			

		}
		else//循环
			if (x == -1)
				x = m_ListMp3.GetCount() - 1;


	CString name_ ;

	m_ListMp3.SetCurSel(x);
	
//	m_ListMp3.GetText(x,name_);

	name_ = openfile_dlg.array_str.GetAt(x);

	//	mSourceFile.Format(strPath + L"mp3\\%s",name_);
	mSourceFile = name_;

	GetMp3INFO(mSourceFile);
	b_mp3info = true;
	
	str_lrc = L"";
	CString strMP3NAME,strLRCNAME;
	strMP3NAME = mSourceFile.Left(mSourceFile.GetLength() - 4);	
	strLRCNAME = strMP3NAME + ".lrc";

	lrc.Free();
	
	if ((lrc.Open(strLRCNAME)))
	{
		b_yesLrc = true;
	}
	else
	{
		str_lrc = L"";
//		m_lrc.ShowWindow(SW_HIDE);
	}
	

	InvalidateRect(CRect(103,53,293,110),false);
	mp3CreateGraph();
	mp3PLAY();
	b_play_or_pause = true;


}

void CPLAYMP3Dlg::Btn_Right()
{

	if (m_ListMp3.GetCount() == 1)//一个歌时不可以左右。
	{
		return;
	}
	if (m_ListMp3.GetCount() <= 0 )//没有歌曲时。
	{
		return;
	}

	int x = m_ListMp3.GetCurSel() + 1;

	CopyBMP(IDB_SPAUSE_B,4);
	
		if (!b_btn_round)//随 机
		{
			int l_max = m_ListMp3.GetCount();
			
			srand( WCE_FCTN(time) (NULL) );
			x =	rand()%(l_max );

		}
		else//循环
		{
			if (x == m_ListMp3.GetCount() )
			{
				x = 0;
			}
			
		}
		
//	m_ListMp3.SetCurSel(x);

	CString name_ ;

	m_ListMp3.SetCurSel(x);
//	m_ListMp3.GetText(x,name_);
	name_ = openfile_dlg.array_str.GetAt(x);


//	mSourceFile.Format(strPath +  L"mp3\\%s",name_);
	mSourceFile = name_;

	GetMp3INFO(mSourceFile);
	b_mp3info = true;
	
	str_lrc = L"";
	CString strMP3NAME,strLRCNAME;
	strMP3NAME = mSourceFile.Left(mSourceFile.GetLength() - 4);	
	strLRCNAME = strMP3NAME + ".lrc";

	lrc.Free();
	
	if ((lrc.Open(strLRCNAME)))
	{
		b_yesLrc = true;
	}
	else
	{
		str_lrc = L"";
//		m_lrc.ShowWindow(SW_HIDE);
	}
	

	InvalidateRect(CRect(103,53,293,110),false);
	mp3CreateGraph();
		mp3PLAY();
	b_play_or_pause = true;

	
}

void CPLAYMP3Dlg::Btn_Round()
{

//	CString ss;
//	ss.Format(L"%d",m_ListMp3.GetCount());
//	AfxMessageBox(ss);
//	
	if (m_ListMp3.GetCount() == 1)
	{
		return;
	}
	if (m_ListMp3.GetCount() <= 0 )//没有歌曲时。
	{
		return;
	}
	

	
	b_btn_round = !b_btn_round;

	if (!b_btn_round)
	{
		CopyBMP (IDB_RANDOM_W,8);
	}
	else
	{
		CopyBMP(IDB_ROUND_W,8);
	}

}


void CPLAYMP3Dlg::Btn_Close()
{
	


	RegCloseKey(g_hkVolume);
	if (mFilterGraph)
	{

		delete mFilterGraph;
		mFilterGraph = NULL;
		// Stop the timer
		if (mSliderTimer)
		{
			KillTimer(mSliderTimer);
			mSliderTimer = 0;
			CDialog::OnOK();
		}

		CDialog::OnOK();
	}


	CDialog::OnOK();	
}

void CPLAYMP3Dlg::Btn_Cancel()
{

	
	m_Playing.ShowWindow(false);
	m_Nameing.ShowWindow(false);

	m_PlayTime.ShowWindow(false);
	m_NewLrc.ShowWindow(false);

	RegCloseKey(g_hkVolume);
	this->ShowWindow(SW_HIDE);
}

	

void CPLAYMP3Dlg::Btn_NoVolume()
{
	DWORD sVolume,dwVolume,dw = 0;
	DWORD sv = 0;

	

	if (!b_volume)
	{
		CopyBMP(IDB_volume,11);

		switch ( out )
			{
			case 0:
				sVolume = 0;
				break;
			case 1:
				sVolume=((DWORD)0xffff/9*1-1);
				break;
			case 2:
				sVolume=((DWORD)0xffff/9*2-1);
				break;
			case 3:
				sVolume=((DWORD)0xffff/9*3-1);
				break;
			case 4:
				sVolume=((DWORD)0xffff/9*4-1);
				break;
			case 5:
				sVolume=((DWORD)0xffff/9*5-1);
				break;
			case 6:
				sVolume=((DWORD)0xffff/9*6-1);
				break;
			case 7:
				sVolume=((DWORD)0xffff/9*7-1);
				break;
			case 8:
				sVolume=((DWORD)0xffff/9*8-1);
				break;
			case 9:
				sVolume=0xffff;
				break;
							
			}
		dwVolume=(sVolume<<16)|(sVolume);
		waveOutSetVolume(0,dwVolume);
		int x ;
		switch(out)
		{
	    case 0:
			x = 315;
			break;
		case 1:
			x = 322;
			break;
		case 2:
			x = 329;
			break;
		case 3:
			x = 336;
			break;
		case 4:
			x = 343;
			break;
		case 5:
			x = 350;
			break;
		case 6:
			x = 357;
			break;
		case 7:
			x = 364;
			break;
		case 8:
			x = 371;
			break;
		case 9:
			x = 378;
			break;
	
	}


	}
	else 
	{
		CopyBMP (IDB_MUTE,11);
		//按静音按纽时，先保存当前声音
		DWORD dwVolume;
	DWORD sVolume;
	
	DWORD dwType ;
	dwType = REG_DWORD ;
	waveOutGetVolume(0, &dwVolume);

	sVolume=dwVolume>>16;
	
	if(sVolume==0) 
		out=0;
	else if(sVolume<((DWORD)0xffff/9*1))
		out=1;
	else if(sVolume<((DWORD)0xffff/9*2))
		out=2;
	else if(sVolume<((DWORD)0xffff/9*3))
		out=3;
	else if(sVolume<((DWORD)0xffff/9*4))
		out=4;
	else if(sVolume<((DWORD)0xffff/9*5))
		out=5;
	else if(sVolume<((DWORD)0xffff/9*6))
		out=6;
	else if(sVolume<((DWORD)0xffff/9*7))
		out=7;
	else if(sVolume<((DWORD)0xffff/9*8))
		out=8;
	else
		out=9;

	//为点静音按纽，保丰收当前音量。


		waveOutSetVolume(0,0);
	}
		

	b_volume = !b_volume;
	
}

LPCTSTR CPLAYMP3Dlg::CStringDownMP3(CString m_string)
{
	
	return LPCTSTR(m_string);
}



void CPLAYMP3Dlg::mp3CreateGraph()
{
	mp3DestroyGraph();


	mFilterGraph = new CDXGraph();
	if (mFilterGraph->Create())
	{
		mFilterGraph->RenderFile(mSourceFile);

		mFilterGraph->Pause();
		
	}
}

void CPLAYMP3Dlg::mp3DestroyGraph()
{
	if (mFilterGraph)
	{
		// Stop the filter graph first
		mFilterGraph->Stop();
		mFilterGraph->SetNotifyWindow(NULL);

		delete mFilterGraph;
		mFilterGraph = NULL;
	}

}

void CPLAYMP3Dlg::mp3PLAY()
{

	if (mFilterGraph)
	{
		mFilterGraph->Run();
	
		// Start a timer
		if (mSliderTimer == 0)
		{
			mSliderTimer = SetTimer(SLIDER_TIMER, 1000, NULL);
		}
	}


}

void CPLAYMP3Dlg::mp3Pause()
{
	if (mFilterGraph)
	{
		mFilterGraph->Pause();
		// Start a timer
		if (mSliderTimer == 0)
		{
			mSliderTimer = SetTimer(SLIDER_TIMER, 1000, NULL);
		}
	}
}

void CPLAYMP3Dlg::mp3Stop()
{

	if (mFilterGraph)
	{
		mFilterGraph->SetCurrentPosition(0);
//		ShowRate(0);
		mFilterGraph->Stop();
		// Stop the timer
		if (mSliderTimer)
		{
			KillTimer(mSliderTimer);
			mSliderTimer = 0;
		}
	}
}


void CPLAYMP3Dlg::OnTimer(UINT nIDEvent) 
{

	if (nIDEvent == mSliderTimer && mFilterGraph)
	{
		double pos = 0, duration = 1.;
		mFilterGraph->GetCurrentPosition(&pos);
		mFilterGraph->GetDuration(&duration);
		
		if (b_yesLrc&&b_beginPlay) //如果有歌词。
		{
			for(int i=0; i<lrc.m_recordArray.GetSize(); i++)
			{
				int ll = (int)pos;
				double nnn=lrc.m_recordArray[i]->m_time;
				int lll = (int)(nnn/100);
				if (lll == ll) 
				{
					str_lrc = lrc.m_recordArray[i]->m_str;
			
					m_NewLrc.SetWindowText(L"歌词：" + str_lrc);
				
				}	
			}
		}
	    int fen,miao;
		if (duration < 60)
		{
			fen = 0;
			miao = duration;
		}
		else
		{
			miao = (int)duration%60;
			fen = (int)duration /60;
		}

		CString s1;
		s1.Format(L"%02d:%02d",fen,miao);


		if (pos<60)
		{
			temp_second = (int)pos;
			temp_minute = 0;
		}
		else
			if (pos>=60)
			{
				temp_second = (int)pos % 60;
				temp_minute = (int)pos / 60;
			}

			
		kkk_minute.Format(L"%02d",temp_minute);
		kkk_second.Format(L"%02d",temp_second);

		temp_time = L"播放时间:  "+kkk_minute + ":" + kkk_second + " | " +s1; 

		if (b_beginPlay)
		{
			m_PlayTime.SetWindowText(temp_time);
		}

		//播放下一首
		if (pos == duration)
			{
							
				if (!b_btn_round)//随 机
				{
					int l_max = m_ListMp3.GetCount();
					xxx =	rand()%(l_max );
					

				}
				else//循环
				{
					if (m_ListMp3.GetCount() == 1) 
					{
						xxx = 0;
					}
					else	
						if (xxx == m_ListMp3.GetCount() - 1)
							xxx = 0;
						else 
							xxx++;
				}
				

				CString name_ ;

				m_ListMp3.SetCurSel(xxx);

		//		m_ListMp3.GetText(xxx,name_);

					name_ = openfile_dlg.array_str.GetAt(xxx);

			//	mSourceFile.Format( strPath +  L"mp3\\%s",name_);
					mSourceFile = name_;

				///////////////
				lrc.Free();
				CString strMP3NAME,strLRCNAME;
				strMP3NAME = mSourceFile.Left(mSourceFile.GetLength() - 4);	
				strLRCNAME = strMP3NAME + ".lrc";
	
				str_lrc = L"";
				if ((lrc.Open(strLRCNAME)))
					{
						b_yesLrc = true;
					}	
				else
					{
//						m_lrc.ShowWindow(SW_HIDE);
					}
			
	
					

				
				GetMp3INFO(mSourceFile);
				b_mp3info = true;
				

				mp3CreateGraph();

				InvalidateRect(CRect(19,182,155 + 19,182+11),false);

				mp3PLAY();
				b_play_or_pause = true;
				return;


				
			}

		newPos = int(pos * 101 / duration);



	m_StateDian.MoveWindow(newPos + 151 ,201,29,20);
		
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CPLAYMP3Dlg::GetVolume()
{

	
	DWORD dwVolume;
	DWORD sVolume;
	
	DWORD dwType ;
	dwType = REG_DWORD ;
	waveOutGetVolume(0, &dwVolume);

	sVolume=dwVolume>>16;
	
	if(sVolume==0) 
		out=0;
	else if(sVolume<((DWORD)0xffff/9*1))
		out=1;
	else if(sVolume<((DWORD)0xffff/9*2))
		out=2;
	else if(sVolume<((DWORD)0xffff/9*3))
		out=3;
	else if(sVolume<((DWORD)0xffff/9*4))
		out=4;
	else if(sVolume<((DWORD)0xffff/9*5))
		out=5;
	else if(sVolume<((DWORD)0xffff/9*6))
		out=6;
	else if(sVolume<((DWORD)0xffff/9*7))
		out=7;
	else if(sVolume<((DWORD)0xffff/9*8))
		out=8;
	else
		out=9;

		
	int x =0;

	switch(out)
	{
	     case 0:
			x = 315;
			break;
		case 1:
			x = 322;
			break;
		case 2:
			x = 329;
			break;
		case 3:
			x = 336;
			break;
		case 4:
			x = 343;
			break;
		case 5:
			x = 350;
			break;
		case 6:
			x = 357;
			break;
		case 7:
			x = 364;
			break;
		case 8:
			x = 371;
			break;
		case 9:
			x = 378;
			break;
	
	
	}
	//为点静音按纽，保丰收当前音量。

	m_VolDian.MoveWindow(x,201,14,20);


	
}
//
//void CPLAYMP3Dlg::ShowVolume(UCHAR volume)
//{
//
//}
//	

BOOL CPLAYMP3Dlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (mSliderTimer)
	{
		KillTimer(mSliderTimer);
		mSliderTimer = 0;
	}
	
	return CDialog::DestroyWindow();
}

HRESULT CPLAYMP3Dlg::FindFilterByInterface(REFIID riid, IBaseFilter **ppFilter)
{
	 *ppFilter = NULL;
	if (!mFilterGraph)
	{
		return E_FAIL;
	}

    IEnumFilters* pEnum;
    HRESULT hr = mFilterGraph->GetGraph()->EnumFilters(&pEnum);
    if (FAILED(hr)) 
	{
		return hr;
    }

    IBaseFilter* pFilter = NULL;
    while (pEnum->Next(1, &pFilter, NULL) == S_OK) 
	{
		// Check for required interface
		IUnknown* pUnk;
		HRESULT hrQuery = pFilter->QueryInterface(riid, (void**)&pUnk);
		if (SUCCEEDED(hrQuery)) 
		{
			pUnk->Release();
			pEnum->Release();
			*ppFilter = pFilter;
			return S_OK;
		}
		pFilter->Release();
    }
    pEnum->Release();

    return E_FAIL;
}
/*

void CPLAYMP3Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (pScrollBar->GetSafeHwnd() == m_SliderGraph.GetSafeHwnd())
	{
		
	}
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}
*/

void CPLAYMP3Dlg::GetMp3INFO(CString _tempPath)
{

	_WMAINFO wmainfo;

//	mp3Artist = "";
//	mp3Title  = "";
	CString _p = _tempPath.Right(4);
//	CString _p2 = _p.MakeUpper();
	CString _p3 = ".wma";

	
	int i = _p.CompareNoCase(_p3);//0 为等
	

	if (i == 0)//如果是WMA格式则有眺过。因为我没有做出来。CompareNoCase 
	{
		mp3Title	 =  GetWmaINFO(_tempPath) .Artist;
		mp3Artist	 =  GetWmaINFO(_tempPath) .Title;

		return;
	}

	CFile file;

	if(!file.Open(_tempPath,CFile::modeRead))
	{
	//	AfxMessageBox(L"Can not open file.");
		return ; //文件^无法打开
	}

	//把文件的最后128字节信息读给pbuf数组
	long seekPos = 128;
	file.Seek(-seekPos,CFile::end);
	BYTE pbuf[128];
	memset(pbuf,0,sizeof(pbuf));
	file.Read(pbuf,128);

	mp3Info=(MP3INFO *) new BYTE[sizeof(MP3INFO)];
	ZeroMemory(mp3Info,sizeof(MP3INFO));

//	memcpy(mp3Info->Identify,pbuf,3); //获得tag


	memcpy(mp3Info->Title,pbuf+3,30); //获得歌名
	memcpy(mp3Info->Artist,pbuf+33,30); //获得作者

/*
	memcpy(mp3Info->Album,pbuf+63,30); //获得唱片名
	memcpy(mp3Info->Year,pbuf+93,4); //获得年
	memcpy(mp3Info->Comment,pbuf+97,28); //获得注释
	memcpy(&mp3Info->reserved,pbuf+125,1); //获得保留
	memcpy(&mp3Info->reserved2,pbuf+126,1);
	memcpy(&mp3Info->reserved3,pbuf+127,1);

*/

	mp3Title = mp3Info->Title;
	mp3Artist = mp3Info->Artist;
/*
	mp3Album = mp3Info->Album;
	mp3Year = mp3Info->Year;
*/

	file.Close();
	delete mp3Info;
}

int CPLAYMP3Dlg::GetCStringLen(CString str)
{
	int len = 0;
	bool c = true;
	int n = 0;

	int l = str.GetLength();

	while (c)
	{
		if (str.GetAt(n) > 0xa1)
		{
			len = len + 2;
		}
		else
			len++;
		n++;
		
		if ( n == l)
		{
			c = false;
		}
		
	}
	

	return len;
}

void CPLAYMP3Dlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox(L"sadfasdfasdf");
	if (mFilterGraph)
	{

		delete mFilterGraph;
		mFilterGraph = NULL;
		// Stop the timer
		if (mSliderTimer)
		{
			KillTimer(mSliderTimer);
			mSliderTimer = 0;
		}
	}
	CDialog::OnOK();

}

void CPLAYMP3Dlg::OnOK() 
{
	
//	this->ShowWindow(SW_HIDE);
//
//	HWND h1;
//
//	h1 = ::FindWindow(TEXT("OPENPLAY"),NULL);
//	if (h1 !=NULL) 
//	{
//		::SendMessage(h1,WM_CLOSE,0,0 );
//	}
//
//

	
//
//	HWND h;
//	h = ::FindWindow(TEXT("PLAY"),NULL);
//
//	if(h !=NULL)
//
//		::SendMessage(h,WM_CLOSE,0,0 );

	
}
HRESULT CPLAYMP3Dlg::OnSuspend()
{

	HWND h1;

	h1 = ::FindWindow(TEXT("OPENPLAY"),NULL);
	if (h1 !=NULL) 
	{
		::SendMessage(h1,WM_CLOSE,0,0 );
	}

	HWND h;
	h = ::FindWindow(TEXT("PLAY"),NULL);

	if(h !=NULL)

		::SendMessage(h,WM_CLOSE,0,0 );
	

	return true;
}

LRESULT CPLAYMP3Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (message == VOLMUTE)
	{
		DWORD dwVolume;
		DWORD sVolume;
		waveOutGetVolume(0, &dwVolume);
		sVolume=dwVolume>>16;
		if(sVolume==0) 
			Btn_NoVolume();
	}

	if (message == HIDEMP3) 
	{
		RegCloseKey(g_hkVolume);
		this->ShowWindow(SW_HIDE);
	}

	if (message == WM_SET_VOL) 
	{
		b_volume = true;

		int x ;
		switch(wParam)
		{
	      case 0:
			x = 315;
			break;
		case 1:
			x = 322;
			break;
		case 2:
			x = 329;
			break;
		case 3:
			x = 336;
			break;
		case 4:
			x = 343;
			break;
		case 5:
			x = 350;
			break;
		case 6:
			x = 357;
			break;
		case 7:
			x = 364;
			break;
		case 8:
			x = 371;
			break;
		case 9:
			x = 378;
			break;
	
		}
		//设为非静音量，用currentVolume

        m_VolDian.MoveWindow(x,201,14,20);

		if (wParam > 0) 
		{
			CopyBMP(IDB_volume,11);
		}
	
	}

	if (message == SHOWMP3WINDOW)//显示歌曲信息控件。
	{
		m_Playing.ShowWindow(true);
		m_Nameing.ShowWindow(true);

	
		m_PlayTime.ShowWindow(true);
		m_NewLrc.ShowWindow(true);

	}
	return CDialog::WindowProc(message, wParam, lParam);
}

_WMAINFO CPLAYMP3Dlg::GetWmaINFO(CString _strWmaPath)
{
	_WMAINFO _str_Wma_info;//定义WMA信息，包括两个变量。
	//return _str_Wma_info;
/*
	BYTE m_Byte[16]={0x33 ,0x26,0xB2 ,0x75, 0x8E ,0x66 ,0xCF, 0x11 ,0xA6 ,0xD9, 0x00, 0xAA ,0x00 ,0x62 ,0xCE, 0x6C};//wma文件头。
	char cBuffer[100];
	memcpy(cBuffer,m_Byte,sizeof(m_Byte));
	CString strWmaTAG= cBuffer;//得到标准的WMA前字节字符串。
*/

	//////////////////////////////////////////////////////////////////
	////////////////////以下十行为读WMA文件头。
	CFile file11;
	if(!file11.Open(_strWmaPath,CFile::modeRead))
	{
		file11.Close();
		_str_Wma_info.Artist = " ";
		_str_Wma_info.Title  = " ";
		return _str_Wma_info; //文件无法打开
	}
	long seekPos11 = 30;

	bool x = true;

	BYTE pbuf11[16];

	while (x)
	{
		file11.Seek(seekPos11,CFile::begin);
		memset(pbuf11,seekPos11,16);
		file11.Read(pbuf11,16);
		if (pbuf11 == strWmaTAG)
		{
			x = false;
		}

		seekPos11 = seekPos11 + 1;	
	}

	TCHAR  pbuf22[100];
	CString strppp ;	
	seekPos11 = seekPos11 + 33;
	file11.Seek(seekPos11,CFile::begin);
	memset(pbuf22,seekPos11,100);
	file11.Read(pbuf22,100);
	
	TCHAR name1[50]={0};
	TCHAR name2[50]={0};

	int l =0;//读唱者
	for(int i = 0;i < 100;i++)
	{
		if (pbuf22[i] == '\0')
		{
			for(int j = 0;j < i;j++)
			{
				name1[j] = pbuf22[j];
			}
			l = i+1;
			break;
		}

		
		
	}
	

	//读歌名。
	for(int ii = l;ii < 100;ii++)
	{
		if (pbuf22[ii] == '\0')
		{
			for(int j = 0;j < ii;j++)
			{
				name2[j] = pbuf22[l++];
			}
			break;
		}

	}

	
	CString na1,na2;
	na1 = name1;
	na2 = name2;

	_str_Wma_info.Artist = name1;
	_str_Wma_info.Title  = name2;
	
//	AfxMessageBox(name1);
//	AfxMessageBox(name2);


	file11.Close();
	return _str_Wma_info;
}

void CPLAYMP3Dlg::AddToListBox()
{
	int zzz = m_ListMp3.GetCount();

	for(int o11 = 0;o11<zzz;o11++)
	{
		m_ListMp3.DeleteString(0);
	}

	for (int i = 0;i < openfile_dlg.array_str.GetSize(); i++)
	{
	//	m_ListMp3.AddString(openfile_dlg.array_str.GetAt(i));
		//7.19改
		CString ppp = GetMp3Name(openfile_dlg.array_str.GetAt(i));
		m_ListMp3.AddString(ppp);

	}
	
}


void CPLAYMP3Dlg::OnSelchangeList() 
{
	// TODO: Add your control notification handler code here

	m_Playing.ShowWindow(true);
	m_Nameing.ShowWindow(true);

	
	m_PlayTime.ShowWindow(true);
	m_NewLrc.ShowWindow(true);

	
	CopyBMP(IDB_PLAYMP3_W,4);
	
	int index =  m_ListMp3.GetCurSel();

	CString name_ ;

//	m_ListMp3.GetText(index,name_);

	name_ = openfile_dlg.array_str.GetAt(index);



//	mSourceFile.Format(strPath +  L"mp3\\%s",name_);
	mSourceFile = name_;

	GetMp3INFO(mSourceFile);
	b_mp3info = true;
	
	str_lrc = "";
	CString strMP3NAME,strLRCNAME;
	strMP3NAME = mSourceFile.Left(mSourceFile.GetLength() - 4);	
	strLRCNAME = strMP3NAME + ".lrc";

	lrc.Free();
	
	if ((lrc.Open(strLRCNAME)))
	{
		b_yesLrc = true;
	}
	else
	{
		str_lrc = L"";
		//m_lrc.SetWindowText(str_lrc);
		m_NewLrc.SetWindowText(str_lrc);
//		m_lrc.ShowWindow(SW_HIDE);
	}
	




	InvalidateRect(CRect(103,53,293,110),false);
	mp3CreateGraph();
	b_play_or_pause = true;
}

void CPLAYMP3Dlg::OnSetFocus(CWnd* pOldWnd) 
{
	CDialog::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here

}

void CPLAYMP3Dlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(b_beginPlay)//开始播放后才可能按进度条。
		if (point.x > 151 && point.x < 270 && point.y > 200 &&point.y < 220)
		{
    		m_StateDian.MoveWindow(point.x-15 ,201,29,20);
			
			//MOUSE抬起里，设定当前播放段//这里设不可以托了。
		}

if (b_volume)

	if (point.x >= 315 && point.x < 390 && point.y > 201 && point.y < 220)
	{
		


		if (point.x > 378)
		{
			point.x = 378;
		}
		m_VolDian.MoveWindow(point.x,201,14,20);
		

		//将音量分为，85份。
		DWORD dwVolume;
		DWORD sVolume=((DWORD)0xffff/65*(point.x - 315));
		dwVolume=(sVolume<<16)|(sVolume);

		//最小声
		if (point.x <= 315)
		{
			dwVolume = 0;
		}
		//最大声
		if (point.x >= 375)
		{
			dwVolume == 0xffff;
		}

		waveOutSetVolume(0,dwVolume);

	}
	CDialog::OnMouseMove(nFlags, point);
}



//
//
//
//		int all_second,all_minute;
//		CString all_T;
//		if (duration<60)
//		{
//			all_second = (int)duration;
//			all_minute = 0;
//		}
//		else
//			if (duration>=60)
//			{
//				all_second = (int)duration % 60;
//				all_minute = (int)duration / 60;
//			}
//		
//			all_T.Format(L"%02d:%02d");

CString CPLAYMP3Dlg::GetMp3Name(CString strName)
{

	CString tempstr;

	for (int i = strName.GetLength() -1 ; ; i--)
	{
		tempstr = strName.GetAt(i);

		if (tempstr == "\\")
		{
			break;
		}
	}

	CString ppp = strName.Right(strName.GetLength() -1 - i);
	return ppp;

}
