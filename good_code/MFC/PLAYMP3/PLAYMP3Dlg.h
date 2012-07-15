// PLAYMP3Dlg.h : header file
//

#if !defined(AFX_PLAYMP3DLG_H__FFD3B1F1_C6A4_4FC2_87A4_7D727806B7EB__INCLUDED_)
#define AFX_PLAYMP3DLG_H__FFD3B1F1_C6A4_4FC2_87A4_7D727806B7EB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CDXGraph.h"
#include "lrc.h"


typedef struct _MP3INFO //MP3��Ϣ�Ľṹ
{
	char Identify[3]; //TAG������ĸ
	//����������������ǲ����ļ���Ϣ����
	char Title[31];   //��������30���ֽ�
	char Artist[31];  //��������30���ֽ�
//CString Title;
//CString Artist;

	char Album[31];   //������Ƭ��30���ֽ�
	char Year[5];	  //�꣬4���ֽ�
	char Comment[29]; //ע�ͣ�28���ֽ�
	unsigned char reserved;  //����λ��1���ֽ�
	unsigned char reserved2; //����λ��1���ֽ�
	unsigned char reserved3; //����λ��1���ֽ�
} MP3INFO;




struct _WMAINFO
{
	CString Title;//������
	CString Artist;//��������
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
	UCHAR out;//����
	int m_listPick;
	CString kkk_minute;
	CString kkk_second;
	
	CString  mp3Title;   //��������30���ֽ�
	CString mp3Artist;  //��������30���ֽ�
	CString mp3Album;   //������Ƭ��30���ֽ�
	CString mp3Year;	  //�꣬4���ֽ�	
public:	
	CString GetMp3Name(CString strName);
	bool b_beginPlay;//��ʼ����
	CString strWmaTAG;
	int bei ;//��ҳ�ı���
	CString _name1,_name2;
	HBRUSH m_brMine;
	IGraphBuilder *pGraph;  
    IMediaControl *pMediaControl; 
	int xxx ;
	bool b_play_or_pause; 
	CDXGraph *   mFilterGraph;     // Filter Graph��װ
	CString      mSourceFile;      // Դ�ļ�
	UINT         mSliderTimer;     // ��ʱ��ID
	CLrc lrc;
	int temp_minute;
	int temp_second;
	CString temp_time;
	MP3INFO *mp3Info;//MP3��Ϣ
	bool b_btn_round;
	bool b_volume;//����
	bool b_mp3info;
	CString str_lrc;//���
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
