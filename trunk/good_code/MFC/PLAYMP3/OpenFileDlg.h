#if !defined(AFX_OPENFILEDLG_H__F5BB19F1_087F_4C43_AC0A_C002BE4E90B4__INCLUDED_)
#define AFX_OPENFILEDLG_H__F5BB19F1_087F_4C43_AC0A_C002BE4E90B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenFileDlg dialog

class COpenFileDlg : public CDialog
{
// Construction
public:
	COpenFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpenFileDlg)
	enum { IDD = IDD_OPENFILE };
	CListCtrl	m_ListCtrl;
//	CString	m_temp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenFileDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool CheckWma(CString _temp1);
	void BtnOK();
	void BtnCancel();
	void BtnAll();
	void CopyBMP(int m_map, int i);
	void SetToolRectangle();
	void DrawInterface(CDC &dc);
	bool CheckMp3(CString _temp);
	int	m_Left,	m_Top,	m_Width,m_Height;
	int count;
	CString m_strName;
	int bei ;//设上下翻
	CStringArray array_str;
	int sum;
	CString _tempStrPath;
	int n_ListPage;//list 滚动页
//	int count;
	CString m_tempStr;
	CImageList m_imagelist;
	int   n_list_i; 
	WIN32_FIND_DATA FileData;
	HANDLE hSearch;
	CBitmap m_BackScreenBitmap;
	int	m_prePick ;			//the last time picked button
	int m_currentPick ;	
	BOOL m_bIsExecute ;
	BOOL m_NavRefresh ;
	CRect m_rect[5];
	CString strWmaHead;
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUp();
	afx_msg void OnDblclkListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENFILEDLG_H__F5BB19F1_087F_4C43_AC0A_C002BE4E90B4__INCLUDED_)
