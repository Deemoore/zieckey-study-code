// PLAYMP3Dlg.h : header file
//

#if !defined(AFX_PLAYMP3DLG_H__FFD3B1F1_C6A4_4FC2_87A4_7D727806B7EB__INCLUDED_)
#define AFX_PLAYMP3DLG_H__FFD3B1F1_C6A4_4FC2_87A4_7D727806B7EB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CDXGraph.h"
#include "lrc.h"


typedef struct _MP3INFO //MP3信息的结构
{
	char Identify[3]; //TAG三个字母
	//这里可以用来鉴别是不是文件信息内容
	char Title[31];   //歌曲名，30个字节
	char Artist[31];  //歌手名，30个字节
//CString Title;
//CString Artist;

	char Album[31];   //所属唱片，30个字节
	char Year[5];	  //年，4个字节
	char Comment[29]; //注释，28个字节
	unsigned char reserved;  //保留位，1个字节
	unsigned char reserved2; //保留位，1个字节
	unsigned char reserved3; //保留位，1个字节
} MP3INFO;




struct _WMAINFO
{
	CString Title;//歌曲名
	CString Artist;//歌手名。
};

/////////////////////////////////////////////////////////////////////////////
// CPLAYMP3Dlg dialog

class CPLAYMP3Dlg : public CDialog
{
// Construction
public:
	void AddToListBox();
	_WMAINFO GetWmaINFO(CString _strWmaPath);
	int GetCStringLen(CString str);
	void GetMp3INFO(CString _tempPath);
	HRESULT FindFilterByInterface(REFIID riid, IBaseFilter** ppFilter);
	void GetVolume();
	void mp3Stop();
	void mp3Pause();
	void mp3PLAY();
	void mp3DestroyGraph();
	void mp3CreateGraph();
	LPCTSTR CStringDownMP3(CString);

	void Btn_Add();
	void Btn_Down();
	void Btn_Up();
	void Btn_Sub();
	void Btn_Play();
	void Btn_Stop();
	void Btn_Left();
	void Btn_Right();
	void Btn_Round();

	void Btn_Close();
	void Btn_Cancel();
	void Btn_NoVolume();
	void SetToolRectangle();
	void CopyBMP(int m_map, int i);
	void DrawInterface(CDC &dc);
	
	CPLAYMP3Dlg(CWnd* pParent = NULL);	// standard constructor
	~CPLAYMP3Dlg();

private:
	int m_Left,m_Top,m_Width,m_Height;
	CBitmap m_BackScreenBitmap;
	CRect m_rect[12];
	UCHAR out;//声音
	int m_listPick;
	CString kkk_minute;
	CString kkk_second;
	
	CString  mp3Title;   //歌曲名，30个字节
	CString mp3Artist;  //歌手名，30个字节
	CString mp3Album;   //所属唱片，30个字节
	CString mp3Year;	  //年，4个字节	
public:	
	CString GetMp3Name(CString strName);
	bool b_beginPlay;//开始播放
	CString strWmaTAG;
	int bei ;//翻页的倍数
	CString _name1,_name2;
	HBRUSH m_brMine;
	IGraphBuilder *pGraph;  
    IMediaControl *pMediaControl; 
	int xxx ;
	bool b_play_or_pause; 
	CDXGraph *   mFilterGraph;     // Filter Graph封装
	CString      mSourceFile;      // 源文件
	UINT         mSliderTimer;     // 定时器ID
	CLrc lrc;
	int temp_minute;
	int temp_second;
	CString temp_time;
	MP3INFO *mp3Info;//MP3信息
	bool b_btn_round;
	bool b_volume;//静音
	bool b_mp3info;
	CString str_lrc;//歌词
	bool b_yesLrc;
	int newPos;


	// Dialog Data
	//{{AFX_DATA(CPLAYMP3Dlg)
	enum { IDD = IDD_PLAYMP3_DIALOG };
	CStatic	m_StateDian;
	CStatic	m_VolDian;
	CStatic	m_Nameing;
	CStatic	m_Playing;
	CStatic	m_PlayTime;
	CStatic	m_NewLrc;
	CListBox	m_ListMp3;
	CString	m_s;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPLAYMP3Dlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPLAYMP3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnOK();
	afx_msg HRESULT OnSuspend();
	afx_msg void OnSelchangeList();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYMP3DLG_H__FFD3B1F1_C6A4_4FC2_87A4_7D727806B7EB__INCLUDED_)
