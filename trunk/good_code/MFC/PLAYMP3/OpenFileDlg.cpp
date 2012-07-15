// OpenFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PLAYMP3.h"
#include "OpenFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString strPath = "\\sdmmc\\";

/////////////////////////////////////////////////////////////////////////////
// COpenFileDlg dialog


COpenFileDlg::COpenFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenFileDlg)
	_tempStrPath = "";
	//}}AFX_DATA_INIT
}


void COpenFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenFileDlg)
	DDX_Control(pDX, IDC_LISTCTRL, m_ListCtrl);
//	DDX_Text(pDX, IDC_EDIT1, m_temp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenFileDlg, CDialog)
	//{{AFX_MSG_MAP(COpenFileDlg)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL, OnDblclkListctrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL, OnClickListctrl)
	ON_BN_CLICKED(IDC_BUTTON1, OnOK)
	ON_BN_CLICKED(IDC_OK, OnOK)
	ON_BN_CLICKED(IDC_BUTTON2, OnCancel)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenFileDlg message handlers

BOOL COpenFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_Left=0;
	m_Top=0;
	m_Width=480;
	n_list_i = 0;
	m_Height=272;
	bei = 0;
	n_ListPage = 1 ;
	
	
	::SetWindowPos(this->GetSafeHwnd(),HWND_TOPMOST,m_Left, m_Top, 
	m_Width, m_Height,SWP_SHOWWINDOW);



//	m_ListCtrl.SetExtendedStyle(LVS_EX_CHECKBOXES);
	
	m_BackScreenBitmap.LoadBitmap(IDB_OPEN_BKG);

	m_imagelist.Create(32,32,TRUE,2,2);

	SetToolRectangle();
	
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_MP3));

	CenterWindow(GetDesktopWindow());
	
	m_prePick=-1;
	m_currentPick=0;
	m_bIsExecute=FALSE ;
	

	m_ListCtrl.MoveWindow(40,55,344,165);


	BYTE m_Byte[16]={0x30,0x26,0xB2,0x75,0x8E,0x66,0xCF,0x11,0xA6,0xD9, 0x00 ,0xAA ,0x00 ,0x62 ,0xCE ,0x6C};//wma文件头。
	char cBuffer[100];
	memcpy(cBuffer,m_Byte,sizeof(m_Byte));
	strWmaHead = cBuffer;//得到标准的WMA前字节字符串。

	
	count = 0;
	bool bFinished = false;
	hSearch = FindFirstFile(strPath + L"mp3\\*.wma",&FileData);

	if (hSearch != INVALID_HANDLE_VALUE)//找到
		while (!bFinished)
		{
			if(CheckWma(FileData.cFileName))//有效MP3文件，则向LIST中 添加文件
			{
				m_ListCtrl.InsertItem(n_list_i,FileData.cFileName);
			}
			if (!FindNextFile(hSearch ,&FileData))
			{
				bFinished = true;
			}
			
		}
//查找wma	
	bFinished = false;
	hSearch = FindFirstFile(strPath + L"mp3\\*.mp3",&FileData);
	if (hSearch != INVALID_HANDLE_VALUE)
		while (!bFinished)
		{
			if(CheckMp3(FileData.cFileName))//有效MP3文件，则向LIST中 添加文件
			{
				m_ListCtrl.InsertItem(n_list_i,FileData.cFileName);
			}
			if (!FindNextFile(hSearch ,&FileData))
			{
				bFinished = true;
			}
			
		}
		
	
	m_ListCtrl.SetImageList(&m_imagelist,LVSIL_NORMAL);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrl.SetBkColor(RGB(0,0,0));
	m_ListCtrl.SetTextColor(RGB(255,255,255));
	m_ListCtrl.SetTextBkColor(RGB(0,0,0));
//	m_ListCtrl.SetIconSpacing(0,0);
	
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}
/*

void COpenFileDlg::OnOK() 
{

	CString str = "";

	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;
	else
	{
	 while (pos)
	 {
      int nItem = m_ListCtrl.GetNextSelectedItem(pos);
	 str = m_ListCtrl.GetItemText(nItem,0);
	  array_str.Add(str);
		}
	}




//list多选
/ *
	int count1;
	CString str;		
    int n = 0;
	count = m_list.GetSelCount();

	if (count < 1) //如何没有选中文件，则不退出
	{
		return;
	}
	int * m_Name = new int[count];
	m_list.GetSelItems(count,m_Name);
	

	for (int i=0;i < count;i++)
	{
		count1 = 0;
		n = m_list.GetTextLen( m_Name[i] );
		m_list.GetText( m_Name[i], str.GetBuffer(n) );

		array_str.Add(str);

		str.ReleaseBuffer(0);
	}
	delete[]m_Name;
* /

	CDialog::OnOK();
}

*/


BOOL COpenFileDlg::OnEraseBkgnd(CDC* pDC) 
{
	BITMAP bmpInfo;
	m_BackScreenBitmap.GetBitmap(&bmpInfo);
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dcMemory.SelectObject(&m_BackScreenBitmap);
	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 
		0, 0, SRCCOPY);
	dcMemory.SelectObject(pOldBitmap);
		
			
	return TRUE;
}
/*

void COpenFileDlg::OnCancel() 
{
//	m_list.ResetContent();
	CDialog::OnCancel();
}
*/

BOOL COpenFileDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	for(int kk=0;kk<m_imagelist.GetImageCount();kk++)
  m_imagelist.Remove(kk);

//	m_list.ResetContent();
	FindClose(hSearch);
	
	return CDialog::DestroyWindow();
}

bool COpenFileDlg::CheckMp3(CString _temp)
{
	
	CString strname1;
	strname1.Format(strPath + L"mp3\\%s",_temp);

	//如果是wma文则跳过，因为这段我没有做出来。
	
	///////////
	CFile file;
	
	if(!file.Open(strname1,CFile::modeRead))
	{
	//	AfxMessageBox(L"Can not open file.");
		return false; //文件无法打开
	}

	//把文件的最后128字节信息读给pbuf数组
	long seekPos = 128;
	file.Seek(-seekPos,CFile::end);
	BYTE pbuf1[3];
	memset(pbuf1,0,3);

	file.Read(pbuf1,3);

	//获得tag,如果不是tag，那么就返回
	if(!((pbuf1[0] == 'T'|| pbuf1[0] == 't')
		&&(pbuf1[1] == 'A'|| pbuf1[1] == 'a')
		&&(pbuf1[2] == 'G'|| pbuf1[0] == 'g')))
	{
		file.Close();
		return false;;
	}
	else
	{
		file.Close();
		return true;
	}
		


	return true;
}
/*

void COpenFileDlg::OnBtnAll() 
{

	UINT nCount = m_ListCtrl.GetItemCount();   
    for(UINT i = 0;i < nCount;i++)   
	{   
		m_ListCtrl.SetItemState(i,   LVIS_SELECTED,   LVIS_SELECTED);   
	}

}
*/

void COpenFileDlg::OnUp() 
{



}


void COpenFileDlg::OnDblclkListctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString str = "";
	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
    int nItem = m_ListCtrl.GetNextSelectedItem(pos);
	str = m_ListCtrl.GetItemText(nItem,0);
	if (str == "")
	{
		return;
	}
	array_str.Add(str);
	*pResult = 0;

	keybd_event(VK_CONTROL,MapVirtualKey(VK_CONTROL,0),KEYEVENTF_KEYUP,0); 

	CDialog::OnOK();

}

void COpenFileDlg::DrawInterface(CDC &dc)
{
	CDC  memDC ;
	memDC.CreateCompatibleDC ( &dc ) ;
	
	
	CBitmap*  pBitmap ;		//load all bitmap
	CBitmap*  pOldBitmap ;	//save old bitmap temp
	
	


	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	
	if (m_NavRefresh ||  m_currentPick == 0)
	{
	//黑
		pBitmap ->LoadBitmap ( IDB_OPEN_UP_W ) ;
		pOldBitmap = memDC.SelectObject ( pBitmap ) ;
		
		//将图片COPY到指定的像素位置
		dc.BitBlt ( m_rect[0].TopLeft().x, m_rect[0].TopLeft().y, 55, 55, &memDC, 0, 0, SRCCOPY ) ;
	}
	else
	{		//白
		pBitmap ->LoadBitmap ( IDB_OPEN_UP_B) ;
		pOldBitmap = memDC.SelectObject ( pBitmap ) ;
		
		//将图片COPY到指定的像素位置
		dc.BitBlt ( m_rect[0].TopLeft().x, m_rect[0].TopLeft().y, 55, 55, &memDC, 0, 0, SRCCOPY ) ;
	}
	
	
	memDC.SelectObject ( pOldBitmap ) ;
	
	//释放bitmap对象内存
	delete pBitmap ;
	//////////////////////////////////////////////
	//.............................................................
	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	
	if ( m_currentPick == 1 )
	{
	pBitmap ->LoadBitmap ( IDB_OPEN_DOWN_W ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	
	//将图片COPY到指定的像素位置
	dc.BitBlt ( m_rect[1].TopLeft().x, m_rect[1].TopLeft().y, 55, 55, &memDC, 0, 0, SRCCOPY ) ;
	}
	else
	{		
		pBitmap ->LoadBitmap ( IDB_OPEN_DOWN_B) ;
		pOldBitmap = memDC.SelectObject ( pBitmap ) ;
		
		//将图片COPY到指定的像素位置
		dc.BitBlt ( m_rect[1].TopLeft().x, m_rect[1].TopLeft().y, 55, 55, &memDC, 0, 0, SRCCOPY ) ;
	}

	
	memDC.SelectObject ( pOldBitmap ) ;
	
	//释放bitmap对象内存
	delete pBitmap ;
	
	//...............................................................
	//分配bitmap对象内存
	pBitmap = new CBitmap ;
	
	if ( m_currentPick == 2 )
	{
	pBitmap ->LoadBitmap ( IDB_OPEN_ALL_B ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	
	//将图片COPY到指定的像素位置
	dc.BitBlt ( m_rect[2].TopLeft().x, m_rect[2].TopLeft().y, 55, 55, &memDC, 0, 0, SRCCOPY ) ;
	}
	else
	{		
		pBitmap ->LoadBitmap ( IDB_OPEN_ALL_W ) ;
		pOldBitmap = memDC.SelectObject ( pBitmap ) ;
		
		//将图片COPY到指定的像素位置
		dc.BitBlt ( m_rect[2].TopLeft().x, m_rect[2].TopLeft().y, 55, 55, &memDC, 0, 0, SRCCOPY ) ;
	}
	
	memDC.SelectObject ( pOldBitmap ) ;
	
	//释放bitmap对象内存
	delete pBitmap ;
	

		//分配bitmap对象内存
	pBitmap = new CBitmap ;
	
	if ( m_currentPick == 3 )
	{
	pBitmap ->LoadBitmap ( IDB_OPEN_ADD_B ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	
	//将图片COPY到指定的像素位置
	dc.BitBlt ( m_rect[3].TopLeft().x, m_rect[3].TopLeft().y, 55, 55, &memDC, 0, 0, SRCCOPY ) ;
	}
	else
	{		
		pBitmap ->LoadBitmap ( IDB_OPEN_ADD_W) ;
		pOldBitmap = memDC.SelectObject ( pBitmap ) ;
		
		//将图片COPY到指定的像素位置
		dc.BitBlt ( m_rect[3].TopLeft().x, m_rect[3].TopLeft().y, 55, 55, &memDC, 0, 0, SRCCOPY ) ;
	}

	
	memDC.SelectObject ( pOldBitmap ) ;
	
	//释放bitmap对象内存
	delete pBitmap ;
		//分配bitmap对象内存
	pBitmap = new CBitmap ;
	
	if ( m_currentPick == 4 )
	{
	pBitmap ->LoadBitmap ( IDB_OPEN_CANCEL_B ) ;
	pOldBitmap = memDC.SelectObject ( pBitmap ) ;
	
	//将图片COPY到指定的像素位置
	dc.BitBlt ( m_rect[4].TopLeft().x, m_rect[4].TopLeft().y, 55, 55, &memDC, 0, 0, SRCCOPY ) ;
	}
	else
	{		
		pBitmap ->LoadBitmap ( IDB_OPEN_CANCEL_W) ;
		pOldBitmap = memDC.SelectObject ( pBitmap ) ;
		
		//将图片COPY到指定的像素位置
		dc.BitBlt ( m_rect[4].TopLeft().x, m_rect[4].TopLeft().y, 55, 55, &memDC, 0, 0, SRCCOPY ) ;
	}

	
	memDC.SelectObject ( pOldBitmap ) ;
	
	//释放bitmap对象内存
	delete pBitmap ;
	
	//分配bitmap对象内存
	////////////////
	memDC.DeleteDC ()  ;
}

void COpenFileDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	DrawInterface(dc);

}

void COpenFileDlg::SetToolRectangle()
{
	m_rect[0].SetRect(403,65,403+51,65+25);
	m_rect[1].SetRect(403,95,403+51,95+25);
	m_rect[2].SetRect(403,125,403+51,125+25);
	m_rect[3].SetRect(403,155,403+51,155+25);
	m_rect[4].SetRect(403,185,403+51,185+25);
	
	
}

void COpenFileDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		m_prePick = m_currentPick ;

	for ( int i = 0 ; i < 5 ; i ++ ) 
	{		
		if (  m_rect[i].PtInRect (point)   )
		{									
		
			{	
				
				CDC* pDC = GetDC () ;
				CDC  memDC ;
				memDC.CreateCompatibleDC ( pDC ) ;
				
				CBitmap bmp ;
				
				switch ( m_prePick )
				{
				case 0:
					{//白
						bmp.LoadBitmap ( IDB_OPEN_UP_B ) ;
						
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp ) ;
						
						pDC->BitBlt ( m_rect[m_prePick].TopLeft().x, m_rect[m_prePick].TopLeft().y, m_rect[m_prePick].Width(), 
							m_rect[m_prePick].Height(), &memDC, 0, 0, SRCCOPY ) ;
						
						memDC.SelectObject ( pOldBitmap ) ;						
						
						break ;
					}
				case 1:
					{
						bmp.LoadBitmap ( IDB_OPEN_DOWN_B ) ;
						
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp ) ;
						
						pDC->BitBlt ( m_rect[m_prePick].TopLeft().x, m_rect[m_prePick].TopLeft().y, m_rect[m_prePick].Width(), 
							m_rect[m_prePick].Height(), &memDC, 0, 0, SRCCOPY ) ;
						
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
				case 2:
					{
						bmp.LoadBitmap ( IDB_OPEN_ALL_W ) ;
						
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp ) ;
						
						pDC->BitBlt ( m_rect[m_prePick].TopLeft().x, m_rect[m_prePick].TopLeft().y, m_rect[m_prePick].Width(), 
							m_rect[m_prePick].Height(), &memDC, 0, 0, SRCCOPY ) ;
						
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
					case 3:
					{
						bmp.LoadBitmap ( IDB_OPEN_ADD_W ) ;
						
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp ) ;
						
						pDC->BitBlt ( m_rect[m_prePick].TopLeft().x, m_rect[m_prePick].TopLeft().y, m_rect[m_prePick].Width(), 
							m_rect[m_prePick].Height(), &memDC, 0, 0, SRCCOPY ) ;
						
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
			case 4:
					{
						bmp.LoadBitmap ( IDB_OPEN_CANCEL_W ) ;
						
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp ) ;
						
						pDC->BitBlt ( m_rect[m_prePick].TopLeft().x, m_rect[m_prePick].TopLeft().y, m_rect[m_prePick].Width(), 
							m_rect[m_prePick].Height(), &memDC, 0, 0, SRCCOPY ) ;
						
						memDC.SelectObject ( pOldBitmap ) ;
						break ;
					}
			
			
				}
				
				CBitmap   bmp1 ;
				switch ( i )
				{
				case 0:
					{			
						//load the bitmap	
						//黑
						bmp1.LoadBitmap ( IDB_OPEN_UP_W ) ;
						
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						
						memDC.SelectObject ( pOldBitmap ) ;
						
						break ;
					}
				case 1:			
					{				
						//load the bitmap
						
						bmp1.LoadBitmap ( IDB_OPEN_DOWN_W) ;
						
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						
						memDC.SelectObject ( pOldBitmap ) ;
						
						break ;
					}
				case 2:
					{							
						//load the bitmap
						
						bmp1.LoadBitmap ( IDB_OPEN_ALL_B) ;
						
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						
						memDC.SelectObject ( pOldBitmap ) ;
						
						break ;
					}
					case 3:
					{			
						//load the bitmap	
						//黑
						bmp1.LoadBitmap ( IDB_OPEN_ADD_B ) ;
						
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						
						memDC.SelectObject ( pOldBitmap ) ;
						
						break ;
					}
					case 4:
					{			
						//load the bitmap	
						//黑
						bmp1.LoadBitmap ( IDB_OPEN_CANCEL_B ) ;
						
						CBitmap* pOldBitmap = memDC.SelectObject ( &bmp1 ) ;
						
						pDC->BitBlt ( m_rect[i].TopLeft().x, m_rect[i].TopLeft().y, m_rect[i].Width(), 
							m_rect[i].Height(), &memDC, 0, 0, SRCCOPY ) ;
						
						memDC.SelectObject ( pOldBitmap ) ;
						
						break ;
					}
				}
				
				memDC.DeleteDC () ;
				ReleaseDC ( pDC ) ;
				
				m_currentPick = i ;				
			}	

		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}


void COpenFileDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CopyBMP(IDB_OPEN_UP_B,0);
	CopyBMP(IDB_OPEN_DOWN_B,1);
	CopyBMP(IDB_OPEN_ALL_W,2);
	CopyBMP(IDB_OPEN_ADD_W,3);
	CopyBMP(IDB_OPEN_CANCEL_W,4);

	int cou = m_ListCtrl.GetItemCount();
	
	int pp = 0;//设定上下移。
	
	m_bIsExecute = FALSE ;
	for ( int i = 0 ; i < 5 ; i ++ ) 
	{		
		if (  m_rect[i].PtInRect (point)   )
		{
			if ( m_currentPick == i)
			{
				m_bIsExecute =TRUE ;
				switch (i)
				{
					
				case 0:
					if (bei == 0)
					{
						break;
					}
					bei--;
					pp = bei * 8;
					
					m_ListCtrl.EnsureVisible(pp, FALSE);
					
						break ;
				case 1:
					if (bei > (cou / 8) )
					{
						break;
					}
					bei++;
					
					pp = bei * 8;
				
					if (pp > cou)
					{
						pp = cou - 1 ;
					}
					m_ListCtrl.EnsureVisible(pp, FALSE);
					break;
				case 2:
					BtnAll();
						break ;
				case 3:
					BtnOK();
						break ;
				case 4:
					BtnCancel();
						break ;
			
				default:
						break ;
				}
			}
		}
		
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void COpenFileDlg::CopyBMP(int m_map, int i)
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

void COpenFileDlg::BtnAll()
{
	UINT nCount = m_ListCtrl.GetItemCount();   
    for(UINT i = 0;i < nCount;i++)   
	{   
		m_ListCtrl.SetItemState(i,   LVIS_SELECTED,   LVIS_SELECTED);   
	}
}

void COpenFileDlg::BtnCancel()
{
	keybd_event(VK_CONTROL,MapVirtualKey(VK_CONTROL,0),KEYEVENTF_KEYUP,0); 
	CDialog::OnCancel();
}

void COpenFileDlg::BtnOK()
{
	//松开ctrl
	keybd_event(VK_CONTROL,MapVirtualKey(VK_CONTROL,0),KEYEVENTF_KEYUP,0); 

	
	CString str = "";


	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;
	else
	{
	 while (pos)
	 {
      int nItem = m_ListCtrl.GetNextSelectedItem(pos);
	  str = m_ListCtrl.GetItemText(nItem,0);
	  array_str.Add(str);
	 }
	}




//list多选
/*
	int count1;
	CString str;		
    int n = 0;
	count = m_list.GetSelCount();

	if (count < 1) //如何没有选中文件，则不退出
	{
		return;
	}
	int * m_Name = new int[count];
	m_list.GetSelItems(count,m_Name);
	

	for (int i=0;i < count;i++)
	{
		count1 = 0;
		n = m_list.GetTextLen( m_Name[i] );
		m_list.GetText( m_Name[i], str.GetBuffer(n) );

		array_str.Add(str);

		str.ReleaseBuffer(0);
	}
	delete[]m_Name;
*/

	CDialog::OnOK();
}

void COpenFileDlg::OnClickListctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
// 	CString str = "";

	keybd_event(VK_CONTROL,MapVirtualKey(VK_CONTROL,0),0,0); 

//	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
//	if (pos == NULL)
//		return;
//	else
//	{
//	 while (pos)
//		{
//		 int nItem = m_ListCtrl.GetNextSelectedItem(pos);
//		}
//	}

	*pResult = 0;
}

void COpenFileDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	HWND hwnd;
	hwnd = ::FindWindow(TEXT("PLAY"),NULL);

	if(hwnd!=NULL)
	{
		::SendMessage(hwnd,WM_CLOSE,0,0);
	}

	CDialog::OnClose();
}

bool COpenFileDlg::CheckWma(CString _temp1)
{
/*
	//以下四行，为WMA文件头前16个字节
	BYTE m_Byte[16]={0x30,0x26,0xB2,0x75,0x8E,0x66,0xCF,0x11,0xA6,0xD9, 0x00 ,0xAA ,0x00 ,0x62 ,0xCE ,0x6C};//wma文件头。
	char cBuffer[100];
	memcpy(cBuffer,m_Byte,sizeof(m_Byte));
	CString strWmaHead = cBuffer;//得到标准的WMA前字节字符串。
*/

	//////////////////////////////////////////////////////////////////

	CString strname1;
	strname1.Format(strPath +  L"mp3\\%s",_temp1);

	////////////////////以下十行为读WMA文件头。
	CFile file11;
	if(!file11.Open(strname1,CFile::modeRead))
	{
		return false; //文件无法打开
	}
	long seekPos11 = 0;
	file11.Seek(seekPos11,CFile::begin);
	BYTE pbuf11[16];
	memset(pbuf11,0,16);
	file11.Read(pbuf11,16);
	///////////////////////////////////////////
	CString _strWMa = "";
	_strWMa = pbuf11;
	if (_strWMa == strWmaHead )
	{
		file11.Close();
		return true;
	}
	else 
	{
		file11.Close();
		return false;
	}

	return true;
}
void COpenFileDlg::OnOK() 
{
	
}

LRESULT COpenFileDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == HIDEOPENMP3) 
	{
		CDialog::OnCancel();
	}
	return CDialog::WindowProc(message, wParam, lParam);
}
