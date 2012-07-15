// FullPathFile.cpp : implementation file
//

#include "stdafx.h"
#include "PLAYMP3.h"
#include "FullPathFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFullPathFile dialog


CFullPathFile::CFullPathFile(CWnd* pParent /*=NULL*/)
	: CDialog(CFullPathFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFullPathFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFullPathFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFullPathFile)
	DDX_Control(pDX, IDC_UP, m_UP);
	DDX_Control(pDX, IDC_PATH, m_PathList);
	DDX_Control(pDX, IDC_FILE, m_FileList);
	DDX_Control(pDX, IDC_EXIT, m_OK);
	DDX_Control(pDX, IDC_ALL, m_All);
	DDX_Control(pDX, IDC_ADD, m_Add);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFullPathFile, CDialog)
	//{{AFX_MSG_MAP(CFullPathFile)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_ALL, OnAll)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_NOTIFY(NM_CLICK, IDC_PATH, OnClickPath)
	ON_NOTIFY(NM_DBLCLK, IDC_PATH, OnDblclkPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFullPathFile message handlers

BOOL CFullPathFile::OnEraseBkgnd(CDC* pDC) 
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

HBRUSH CFullPathFile::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CFullPathFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	::SetWindowPos(this->GetSafeHwnd(),HWND_TOPMOST,0, 0,480, 272,SWP_SHOWWINDOW);
	m_BackScreenBitmap.LoadBitmap(IDB_OPEN_BKG);

	m_PathList.MoveWindow(33,33+5,140,210);//
	m_FileList.MoveWindow(183,33+5,190,210);

	m_UP      .MoveWindow(415,108+8,54,29);	
	m_OK      .MoveWindow(415,213+8,54,29);
	m_All     .MoveWindow(415,143+8,54,29);
	m_Add     .MoveWindow(415,178+8,54,29);

	m_OK      .LoadBitmaps(IDB_OPEN_CANCEL_W,IDB_OPEN_CANCEL_B);
	m_UP      .LoadBitmaps(IDB_OPENFILE_UP1,IDB_OPENFILE_UP2);
	m_All     .LoadBitmaps(IDB_OPEN_ALL_W,IDB_OPEN_ALL_B);
	m_Add     .LoadBitmaps(IDB_OPEN_ADD_W,IDB_OPEN_ADD_B);


	m_OK.SizeToContent();
	m_UP.SizeToContent();
	m_All.SizeToContent();
	m_Add.SizeToContent();





/////////////////////////
	m_imagelist_path.Create(24,24,TRUE,2,2);
	m_imagelist_path.Add(AfxGetApp()->LoadIcon(IDI_PATH));

	m_PathList.SetImageList(&m_imagelist_path,LVSIL_NORMAL);
	m_PathList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_PathList.SetBkColor(RGB(0,0,0));
	m_PathList.SetTextColor(RGB(255,255,255));
	m_PathList.SetTextBkColor(RGB(0,0,0));

/////////////////////////////////////////////////	
	m_imagelist_file.Create(24,24,TRUE,2,2);
	m_imagelist_file.Add(AfxGetApp()->LoadIcon(IDI_MP3));

	m_FileList.SetImageList(&m_imagelist_file,LVSIL_NORMAL);
	m_FileList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_FileList.SetBkColor(RGB(0,0,0));
	m_FileList.SetTextColor(RGB(255,255,255));
	m_FileList.SetTextBkColor(RGB(0,0,0));






	strRoot = "\\sdmmc\\";
	// TODO: Add extra initialization here

	INTFindFile(strRoot);



	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFullPathFile::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CFullPathFile::OnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CFullPathFile::INTFindFile(CString strPath)
{
	WIN32_FIND_DATA FileData;
	HANDLE hSearch;
	bool bFinished = false;
	int i_path =0 , i_file = 0;
	hSearch = FindFirstFile( strPath + L"*.*",&FileData);

	if (hSearch == INVALID_HANDLE_VALUE)
	{
		return ;
	}

	while (!bFinished)
	{
		if (FileData.cFileName[0] == '.') 
		continue; // 过滤这两个目录 
		if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{ 	
				CString str  =  FileData.cFileName;
				m_PathList.InsertItem(i_path,str);
				i_path++;
			
		}
		else
		{
				CString str  =  FileData.cFileName;
				if (str.Right(4) == ".mp3")
				{
					m_FileList.InsertItem(i_file,str);
					i_file++;
				}
				if (str.Right(4) == ".MP3")
				{
					m_FileList.InsertItem(i_file,str);
					i_file++;
				}
		
		}

	
		if (!FindNextFile(hSearch ,&FileData))
		{
			bFinished = true;
		}

		
	}
	
	FindClose(hSearch);
}

void CFullPathFile::OnUp() 
{
	if (strRoot == "\\sdmmc\\")
		{
			return;
		}

	CString str_;
	int i =0;
	int len = strRoot.GetLength() ;

	for (i = len - 2; ;i--)
	{
		str_ = strRoot.GetAt(i);
		if (str_ == "\\")
		{
			break;
		}
	}

	strRoot = strRoot.Left(i+1);

	m_FileList.DeleteAllItems();
	m_PathList.DeleteAllItems();
	
	INTFindFile(strRoot);	
}

void CFullPathFile::OnAll() 
{
int nCount = m_FileList.GetItemCount();   
    for(int j = 0;j < nCount;j++)   
	{   
		m_FileList.SetItemState(j,LVIS_SELECTED,LVIS_SELECTED);   
	}	
}

void CFullPathFile::OnAdd() 
{
CString str = "";

	POSITION pos = m_FileList.GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		CDialog::OnOK();
		return;
	}
	else
	{
	    while (pos)
		{
            int nItem = m_FileList.GetNextSelectedItem(pos);
	        str = m_FileList.GetItemText(nItem,0);
			array_str.Add(strRoot + str);	
			CDialog::OnOK();
//			AfxMessageBox(strRoot + str);
		}
	}	
}

void CFullPathFile::OnClickPath(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_PathList.GetFirstSelectedItemPosition();
    long nItem = m_PathList.GetNextSelectedItem(pos);//   》0  表示已点中。

	if (nItem < 0 ) return;
	

	str_New = m_PathList.GetItemText(nItem,0);
	
 


	m_FileList.DeleteAllItems();
//	m_PathList.DeleteAllItems();
	
	FindOnlyFile(strRoot + str_New + "\\");
	strRoot = strRoot + str_New + "\\";
	*pResult = 0;
}

void CFullPathFile::OnDblclkPath(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_PathList.GetFirstSelectedItemPosition();
    long nItem = m_PathList.GetNextSelectedItem(pos);//   》0  表示已点中。

	if (nItem < 0 ) return;
	

	str_New = m_PathList.GetItemText(nItem,0);
	
	strRoot = strRoot + str_New + "\\";


//	m_FileList.DeleteAllItems();
	m_PathList.DeleteAllItems();
	
	FindPath(strRoot);
	
	*pResult = 0;
}

void CFullPathFile::FindPath(CString strPath)
{
	WIN32_FIND_DATA FileData;
	HANDLE hSearch;
	bool bFinished = false;
	int i_path =0 , i_file = 0;
	hSearch = FindFirstFile( strPath + L"*.*",&FileData);

	if (hSearch == INVALID_HANDLE_VALUE)
	{
		return ;
	}

	while (!bFinished)
	{
		if (FileData.cFileName[0] == '.') 
		continue; // 过滤这两个目录 
		if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{ 	
				CString str  =  FileData.cFileName;
				m_PathList.InsertItem(i_path,str);
				i_path++;
			
		}
		if (!FindNextFile(hSearch ,&FileData))
		{
			bFinished = true;
		}

		
	}
	

	FindClose(hSearch);

	if (i_path == 0)
	{
		OnUp();
	}


}

void CFullPathFile::FindOnlyFile(CString strOnlyFile)
{
	WIN32_FIND_DATA FileData;
	HANDLE hSearch;
	bool bFinished = false;
	int i_path =0 , i_file = 0;
	hSearch = FindFirstFile( strOnlyFile + L"*.*",&FileData);

	if (hSearch == INVALID_HANDLE_VALUE)
	{
		return ;
	}

	while (!bFinished)
	{
		if (FileData.cFileName[0] == '.') 
		continue; // 过滤这两个目录 
		if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{ 	
		}
		else
		{
			CString str  =  FileData.cFileName;
			if (str.Right(4) == ".MP3")
			{
				m_FileList.InsertItem(i_file,str);
				i_file++;
			}
			if (str.Right(4) == ".mp3")
			{
				m_FileList.InsertItem(i_file,str);
				i_file++;
			}
		
		}

	
		if (!FindNextFile(hSearch ,&FileData))
		{
			bFinished = true;
		}

		
	}
	
	FindClose(hSearch);
}
