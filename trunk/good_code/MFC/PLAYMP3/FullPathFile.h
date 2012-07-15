#if !defined(AFX_FULLPATHFILE_H__C3C25256_8BCA_4808_9637_C51517D70533__INCLUDED_)
#define AFX_FULLPATHFILE_H__C3C25256_8BCA_4808_9637_C51517D70533__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FullPathFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFullPathFile dialog

class CFullPathFile : public CDialog
{
// Construction
public:
	CFullPathFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFullPathFile)
	enum { IDD = IDD_NEW_OPENFILE };
	CBitmapButton	m_UP;
	CListCtrl	m_PathList;
	CListCtrl	m_FileList;
	CBitmapButton	m_OK;
	CBitmapButton	m_All;
	CBitmapButton	m_Add;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFullPathFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void FindOnlyFile(CString strOnlyFile);
	void FindPath(CString strPath);
	void INTFindFile(CString strPath);
	CBitmap m_BackScreenBitmap;
	CStringArray array_str;
	CString strRoot;  //初始目录
	CString str_New;  //新打开的目录。
	CImageList m_imagelist_path;
	CImageList m_imagelist_file;


protected:

	// Generated message map functions
	//{{AFX_MSG(CFullPathFile)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnExit();
	afx_msg void OnUp();
	afx_msg void OnAll();
	afx_msg void OnAdd();
	afx_msg void OnClickPath(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkPath(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLPATHFILE_H__C3C25256_8BCA_4808_9637_C51517D70533__INCLUDED_)
