VC++ѧϰ��־



���ߣ�zieckey(zieckey@yahoo.com.cn)
All Rights Reserved!


2006/11/22

MFC����Ϣӳ����������ʽ��
1���麯�������ַ������˷������ڴ�ռ�
2����ӳ��

OnDraw �� CView ���һ���麯����ÿ�δ�����Ҫ�ػ�ʱ��Ӧ�ó����ܶ����������
InvalidataRect ������ʹ����������Ч����ô��֮��ͺõ��� OnDraw �����ػ洰�ڡ�

������Ϣ��Ӧ��
�ڡ������ռ䴰�ڡ���ѡ��ClassView������ĳһ�������Ҽ�����Ϳ��Կ�����Add Windows Message Handle...��ѡ��򿪾Ϳ���������Ϣ��Ӧ�ˡ�
ͨ�����ַ������ӵ���Ϣ��Ӧ�������ڼ����ط����ºۼ���
1����ͷ�ļ��� DECLARE_MESSAGE_MAP() ֮ǰ������ԭ������
2����Դ�ļ��У���  ��BEGIN_MESSAGE_MAP(CDrawView, CView)���͡�END_MESSAGE_MAP()��֮������˺궨��
3����Դ�ļ��м����˺����ľ������ʵ��
	

������ɾ��ʱҲӦ��ͨ�������Ҽ�����ķ�ʽѡ��delete������ɾ����

ֱ�߻�ͼ��
void CDrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//MessageBox("Left Button Clicks DrawView");
	m_ptOrigin = point ;
	CView::OnLButtonDown(nFlags, point);
}

void CDrawView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	
	// TODO: Add your message handler code here and/or call default
	/*
	//����һ
	HDC hdc;
	hdc = ::GetDC(m_hWnd); //����ȫ�ֺ���
	MoveToEx(hdc,m_ptOrigin.x,m_ptOrigin.y,0);
	LineTo(hdc,point.x,point.y);
	::ReleaseDC(m_hWnd,hdc);
	*/
	

	/*
	//������
	CDC *pDC = GetDC();
	pDC->MoveTo(m_ptOrigin);
	pDC->LineTo(point);
	ReleaseDC(pDC);
	*/


	/*
	//������
	CClientDC dc(this) ;   //CClientDC�������ʱ��͵�����GetDC��������ʱ�����ReleaseDC 
	CClientDC dc(GetParent());
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);
	*/


	/*
	//������
	//CWindowDC dc(this) ;  //CWindowDC���Է��ʿͻ����ͷǿͻ���
	//CWindowDC dc(GetParent()) ;
	CWindowDC dc(GetDesktopWindow()) ;
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);
	*/


	/*
	//�ı仭����ɫ�ͻ�������
	CPen pen( PS_DASHDOT   , 1 , RGB(255,128,128) );
	CClientDC dc(this) ;
	CPen *pOldPen = dc.SelectObject( &pen );   //ѡ���µĻ��ʲ�����ԭ���Ļ���
	dc.MoveTo(point);
	dc.LineTo(m_ptOrigin);
	dc.SelectObject( pOldPen );     //��ԭԭ���Ļ���
	*/

	
	/*
	//�û�ˢ����������������ľ�����
	CBrush brush( RGB(255,128,128) );//��ˢ����ɫָ��
	CClientDC dc(this) ;
	dc.FillRect(CRect(m_ptOrigin,point),&brush); //��ָ���Ļ�ˢ���һ��������
	*/

	
	/*
	//�û�ˢ����������������ľ�����
	CBitmap bitmap;   //����һ��λͼ
	bitmap.LoadBitmap(IDB_BITMAP_zhong);
	CBrush brush(&bitmap); //��ˢ��λͼָ��
	CClientDC dc(this) ;
	dc.FillRect(CRect(m_ptOrigin,point),&brush); //��ָ���Ļ�ˢ���һ��������
	*/

	/*
	//����һ��հ׵ľ���
	CClientDC dc(this) ;
	dc.Rectangle(CRect(m_ptOrigin,point)); //��ȱʡ�Ļ�ˢ���һ��������
	*/


	/*
	//����һ��͸���ľ���
	CBrush *pBrush = CBrush::FromHandle( (HBRUSH)GetStockObject( HOLLOW_BRUSH ) );
	CClientDC dc(this) ;
	CBrush *pOldBrush = dc.SelectObject(pBrush); //�滻ȱʡ�Ļ�ˢ
	dc.Rectangle(CRect(m_ptOrigin,point)); //��ָ���Ļ�ˢ���һ��������
	dc.SelectObject(pOldBrush);
	*/

	CView::OnLButtonUp(nFlags, point);
}




�����߻�ͼ��

void CDrawView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	/*
	//������������
	if ( m_bDraw )
	{
		CClientDC dc(this) ;
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin = point ;
	}
	*/
	
	
	/*
	//�ı仭�ʵ���ɫ
	if ( m_bDraw )
	{
		CClientDC dc(this) ;
		CPen pen( PS_SOLID , 1 , RGB(255,128,128) );
		CPen *pOldPen = dc.SelectObject(&pen);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin = point ;
		dc.SelectObject(pOldPen);
	}*/


	/*
	//������
	if ( m_bDraw )
	{
		CClientDC dc(this) ;
		CPen pen( PS_SOLID , 1 , RGB(255,128,128) );
		CPen *pOldPen = dc.SelectObject(&pen);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOld = point ;
		dc.SelectObject(pOldPen);
	}*/
	
	/*
	//�������ߵ�����
	if ( m_bDraw )
	{
		CClientDC dc(this) ;
		CPen pen( PS_SOLID , 1 , RGB(255,128,128) );
		CPen *pOldPen = dc.SelectObject(&pen);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		dc.MoveTo(m_ptOld);
		dc.LineTo(point);
		m_ptOld = point ;
		dc.SelectObject(pOldPen);
	}*/


	//������ͼ��ģʽ���÷���
	if ( m_bDraw )
	{
		CClientDC dc(this) ;
		dc.SetROP2(R2_BLACK);  //��ͼ��ģʽ����,ʼ�ջ��ƺ�ɫͼ��
		CPen pen( PS_SOLID , 1 , RGB(255,128,128) );
		CPen *pOldPen = dc.SelectObject(&pen);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		dc.MoveTo(m_ptOld);
		dc.LineTo(point);
		m_ptOld = point ;
		dc.SelectObject(pOldPen);
	}

	CView::OnMouseMove(nFlags, point);
}






2006/11/23
��ͼ

����һ��λͼ��
1���˵�����>����->��Դ
Ȼ��Ϳ����ڴ򿪵ĶԻ����в����ˡ�




��̬���ݳ�Ա��
���濴һ�����ӣ�
#include <iostream.h>
class  Point
{
public:
	void output()
	{
	}
	static void init()
	{		
	}	
};
void main( void )
{
	Point pt;
	pt.init();
	pt.output();  
}
���������ǲ������κδ���ġ�
����������
#include <iostream.h>
class  Point
{
public:
	void output()
	{		
	}
	static void init()
	{		
	}	
};
void main( void )
{
	Point::output();
}
��������ᴦ��������Ϣ��illegal call of non-static member function��Ϊʲô��
��Ϊ��û��ʵ����һ����ľ������ʱ������û�б������ڴ�ռ�ġ�
�õ��ٿ������������:
#include <iostream.h>
class  Point
{
public:
	void output()
	{		
	}
	static void init()
	{		
	}	
};
void main( void )
{
	Point::init();
}
��ʱ����Ͳ����д�����Ϊ����Ķ���ʱ������̬���ݺͳ�Ա���������������ڴ�����������������κ�һ���������
�õ��ٿ������������:
#include <iostream.h>
class  Point
{
public:
	void output()
	{		
	}
	static void init()
	{	
		x = 0;
		y = 0;
	}
private:
	int x;
	int y;
};
void main( void )
{
	Point::init();
}
�������
illegal reference to data member 'Point::x' in a static member function
illegal reference to data member 'Point::y' in a static member function
��һ����̬��Ա�������������������ݳ�Ա��
�����Ǹ����⣬��̬��Ա�����������������κ�һ������Ķ�����ô����ľ����������֮ǰ���Ѿ������ڴ�����
�����ڷǾ�̬���ݳ�Ա��û�з����ڴ�ռ䣬��ô������þʹ����ˣ��ͺ���û������һ������ȴ��ǰʹ����һ����
Ҳ����˵�ھ�̬��Ա�����в������÷Ǿ�̬�ĳ�Ա������
�õ��ٿ������������:
#include <iostream.h>
class  Point
{
public:
	void output()
	{
		x = 0;
		y = 0;
		init();		
	}
	static void init()
	{	

	}
private:
	int x;
	int y;
};
void main( void )
{
	Point::init();
}
�õģ������Ͳ������κδ��������ջ���һ���ڴ�ģ�͵����⣬
�κα������ڴ��������Լ��Ŀռ���������ط����ܱ����ã�����ͻ����
�õ��ٿ������������:
#include <iostream.h>
class  Point
{
public:
	void output()
	{	
	}
	static void init()
	{	
		x = 0;
		y = 0;
	}
private:
	static int x;
	static int y;
};
void main( void )
{
	Point::init();
}
���룺
Linking...
test.obj : error LNK2001: unresolved external symbol "private: static int Point::y" (?y@Point@@0HA)
test.obj : error LNK2001: unresolved external symbol "private: static int Point::x" (?x@Point@@0HA)
Debug/Test.exe : fatal error LNK1120: 2 unresolved externals
ִ�� link.exe ʱ����.
���Կ�������û�д������Ӵ���������Ϊʲô�أ�
������Ϊ��̬�ĳ�Ա����Ҫ���г�ʼ��������������
#include <iostream.h>
class  Point
{
public:
	void output()
	{	
	}
	static void init()
	{	
		x = 0;
		y = 0;
	}
private:
	static int x;
	static int y;
};
int Point::x = 0;
int Point::y = 0;
void main( void )
{
	Point::init();
}
�ھ�̬��Ա���ݱ�����ʼ��֮��Ͳ�����ֱ�������ˡ�
�ٿ�������Ĵ��룺
#include <iostream.h>
class  Point
{
public:
	void output()
	{	
	}
	static void init()
	{	
		x = 0;
		y = 0;
	}
private:
	static int x;
	static int y;
};
void main( void )
{
}
����û�д���Ϊʲô��
��ʹ����û�г�ʼ������Ϊ����û�з���x��y�����Ա��벻�����










�ִ������
����һ���������CreateSolidCaret( 20, 100 )��Ȼ�����ShowCaret

int CTextView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	/*
	CreateSolidCaret( 1, 20 ); //�½�һ�������
	ShowCaret( );
	*/


	/*
	//�õ�ϵͳ���ַ���Ⱥ͸߶�
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CreateSolidCaret( tm.tmAveCharWidth/8 , tm.tmHeight ); //�½�һ�������
	ShowCaret( );
	*/

	
	//����һ��ͼ�εĲ����
	m_Bitmap.LoadBitmap(IDB_BITMAP_CARET);
	CreateCaret(&m_Bitmap);
	ShowCaret( );


	return 0;
}


CString str ;
str.LoadString(IDS_STRING_HELLO); //�������ַ���Դ������ֵ




2006/11/25
CDC::DrawText  
virtual int DrawText( LPCTSTR lpszString, int nCount, LPRECT lpRect, UINT nFormat );
int DrawText( const CString& str, LPRECT lpRect, UINT nFormat );
������KO����ƽ��������ı�


void CTextView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	

	CClientDC dc(this);

	TEXTMETRIC tm;
	dc.GetTextMetrics( &tm ); //�õ��ı��Ŀ����Ϣ

	CRect rect;
	rect.top = 200;
	rect.left = 0;
	rect.bottom = rect.top + tm.tmHeight;
	rect.right = m_nWidth;

	dc.SetTextColor(RGB(255,128,128));  //������ɫ
	CString str;
	str.LoadString(IDS_STRING_HELLO);   

	dc.DrawText(str,rect,DT_LEFT);		//ƽ��������ı�
	m_nWidth += 5;

	rect.top = 100;
	rect.bottom = rect.top + tm.tmHeight;
	dc.DrawText(str,rect,DT_RIGHT);		//ƽ��������ı�,����


	CSize cs = dc.GetTextExtent(str);   //�õ��ı��Ŀ��
	if ( m_nWidth > cs.cx )				
	{
		m_nWidth = 0;					//��ͷ���	
		dc.SetTextColor(RGB(0,128,128));//������ı�������ɫ   
		dc.TextOut( 0, 200, str);
	}




	CView::OnTimer(nIDEvent);
}









2006/11/26
��Ӳ˵���Ӧ��Lesson7
�ò˵������Ա༭��פ���㣬���Ե������Ͻǵ�Сͼ������ť�����ˡ�
����ͨ��ȡ����Pop��Up��ѡ�����Բ˵�����Ӧ�ͱ༭һ����Դ��ʶ��
�Բ˵���������Ӧ���ȼ�˳��View->Doc->MainFrame->App


��׼��Ϣ
      ��WM_COMMAND֮�⣬������WM_��ͷ����Ϣ��
      ��CWnd�������࣬�����Խ��յ�������Ϣ��
������Ϣ
      ���Բ˵������ټ��򹤾�����ť����Ϣ��������Ϣ����WM_COMMAND���֡���MFC�У�ͨ���˵���ı�ʶ��ID�������ֲ�ͬ��������Ϣ����SDK�У�ͨ����Ϣ��wParam����ʶ��
	��CCmdTarget�������࣬�����Խ��յ�������Ϣ��
ͨ����Ϣ
      �ɿؼ���������Ϣ�����磬��ť�ĵ������б���ѡ��Ⱦ�����������Ϣ��Ϊ�������丸���ڣ�ͨ���ǶԻ���֪ͨ�¼��ķ�����������ϢҲ����WM_COMMAND��ʽ���֡�
	��CCmdTarget�������࣬�����Խ��յ�������Ϣ��


���һ���˵�
GetMenu()->GetSubMenu(0)->CheckMenuItem( 0 , MF_BYPOSITION | MF_CHECKED );
�ָ���Ҳռ������
ͼ�λ���ǲ˵�
m_bitmap.LoadBitmap(IDB_BITMAP1);  //��λͼӦ��Ϊ13*13���ش�С
GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps( 0, MF_BYPOSITION , &m_bitmap, &m_bitmap );

�õ�ϵͳ�˵���λͼ�Ĵ�С
CString str;
str.Format("x=%d,y=%d",GetSystemMetrics(SM_CXMENUCHECK),GetSystemMetrics(SM_CYMENUCHECK) );
MessageBox(str);

��һ���˵���ʧЧ��
������
m_bAutoMenuEnable = FALSE ;
GetMenu()->GetSubMenu(0)->EnableMenuItem( 1, MF_BYPOSITION | MF_DISABLED | MF_GRAYED ); 
���� m_bAutoMenuEnable = FALSE  ��������֮�������ĵط���û�в˵����¹����ˡ�

���ò˵�
SetMenu(NULL);
CMenu menu;
menu.LoadMenu(IDR_MAINFRAME);
SetMenu(&menu);
menu.Detach();




������£�
�˵���״̬��ά����������CN_UPDATE_COMMAND_UI��Ϣ��˭����CN_UPDATE_COMMAND_UI��Ϣ��
MFC�������д���һ��CCmdUI����
���ǿ���ͨ���ֹ�������ClassWizard����Ϣӳ�������ON_UPDATE_COMMAND_UI����
����CN_UPDATE_COMMAND_UI��Ϣ��
�ں�̨�����Ĺ����ǣ�����ϵͳ����WM_INITMENUPOPUP��Ϣ��Ȼ����MFC�Ļ�����CFrameWnd�ӹܡ�
������һ��CCmdUI���󣬲����һ���˵�������������ö����һ����Ա����DoUpdate()��
�����������CN_UPDATE_COMMAND_UI��Ϣ��������Ϣ����ָ��CCmdUI�����ָ�롣
ͬһ��CCmdUI���������Ϊ��ڶ����˵��������������˳����У�ֱ��������в˵��
��������UI��������Ӧ���ڵ���ʽ�˵����ϵ���Ŀ������Ӧ����������ʾ�Ķ����˵���Ŀ��





����һ������
void CMainFrame::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (ID_FILE_NEW==pCmdUI->m_nID)  //���ﲻ���ж�Ҳ�У���Ϊ������ڸ���Ϣ�������Ȼ�������ط���Ҫ�����ж���
	{
		pCmdUI->Enable(FALSE);
	}	
}


�Ҽ������˵�
ѡ��project->Add to project->conponent and controls..
������VC�ṩ�����ǵ�һЩ�齨�Ϳؼ�������ѡ�� Visual C++ Components �����Կ��� Pop-up Menu ��
ѡ����뵽 View ���С��������Ǿ�ͨ��VC�Զ�������������һ�������˵�
�����ڻع�ͷ���������ڳ����ж���Щʲô��
1. ��Դ��menu�ж�����������˵�
2. View����˸�������void OnContextMenu(CWnd*, CPoint point)
�ں����������� TrackPopupMenu ����ȥ������Ӧ����Ҽ������˵���
�˽������֮�����ǾͿ����Լ��ֶ������Ҽ������˵��ˡ�
�Լ����֣�

void CMenuLesson6View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CMenu menu;
	VERIFY(menu.LoadMenu(CG_IDR_POPUP_MENU_LESSON6_VIEW));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	ClientToScreen(&point);    //�ͻ�������ת������Ļ����
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			this);

	CView::OnRButtonDown(nFlags, point);
}



��̬�����һ�������˵�
	CMenu menu;
	ASSERT(menu.CreatePopupMenu( ));
	GetMenu()->AppendMenu(MF_POPUP,(UINT)menu.m_hMenu,"Zieckey");
	menu.AppendMenu(MF_STRING,111,"Hello");
	menu.AppendMenu(MF_STRING,110,"welcome");
	menu.Detach();
��ô��Ӷ���Щ��̬�˵���������Ӧ�أ�
���ǿ����ֶ�����ӡ����� Resource.h �ļ������һ����������ص�ID�������£�
#define       IDM_HELLO				    111
�����Ϣԭ�ͣ��� MainFrm.h ����Ӧλ����ӣ���������� DECLARE_MESSAGE_MAP() ֮ǰ��ӣ���
afx_msg void OnHello();
֮�������Ϣӳ�䣬�� MainFrm.cpp ����Ӧλ����ӣ���������� //}}AFX_MSG_MAP ֮ǰ��ӣ���
ON_COMMAND(IDM_HELLO,OnHello)
������ʵ�ֺ�����
void CMainFrame::OnHello() 
{
	MessageBox("Hello");
}
���������Լ��ֶ�������˲˵���������Ӧ��






2006/11/27
�Ի���

�˵���->����->����(C)...������һ���Ի���������ù����䣬����"�ؼ�"��

ģ̬�Ի���
	CTestDlg dlg;
	dlg.DoModal();

������ģ̬�Ի��򣬲������������������һ���ֲ�������
��Ҫ����һ����Ա�������ߴ���һ�����ڵ�ָ�����ͱ���������Ҫ����ShowWindow������ʾ���������磺
	CTestDlg *dlg = new CTestDlg();
	dlg->Create(IDD_DIALOG1,this);
	dlg->ShowWindow(SW_SHOW);
�������ַ����ڳ���ִ�й�ȥ֮�����Ǿ��޷��ͷŵ��ö�����ڴ棬�����һ��ǽ�֮����Ϊ��Ա����Ϊ�á�
���ڷ�ģ̬�Ի������Ǳ�������OnOK����ȥ����DestroyWindow���ͷŸöԻ�����ڴ棬������ɸ������EndDialog����������Ի���
����������û�����ٸöԻ�����û���ͷ��ڴ档

�κ�һ����CWnd���������඼������һ�� m_hWnd �ľ����
����������;���Ķ����������ʱ��m_hWnd ����ֵ�ˡ�
���������ַ�ʽ��̬��������
   	//����һ
	if ( !m_bIsCreate )
	{
		m_btn.Create( "Zieckey Study VC", BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD ,
				CRect(0,0,100,100), this, 100) ;
		m_bIsCreate = TRUE;
	}
	else	
	{
		m_btn.DestroyWindow();
		m_bIsCreate = FALSE;
	}
   	//������
	if ( !m_btn.m_hWnd )
	{
		m_btn.Create( "Zieckey Study VC", BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD ,
				CRect(0,0,100,100), this, 100) ;
	}
	else	
	{
		m_btn.DestroyWindow();
	}


���ھ�̬���ı���Ĭ���ǲ��ܽ������ȵĵ����Ϣ�����Ա����Ƚ����ġ�֪ͨ(Notify)��ѡ��򿪣�
������ı��������->��ʽ->֪ͨ

int atoi( const char *string ); �ַ���������
char *itoa( int value, char *string, int radix );���ֵ��ַ���

�õ�һ�������пؼ����ı����������ı�
	GetDlgItem(IDC_EDIT1)->GetWindowText(ch1,10);
	GetDlgItem(IDC_EDIT2)->GetWindowText(ch2,10);
	GetDlgItem(IDC_EDIT3)->SetWindowText(ch3);
����ֱ�ӵ��ã�
int GetDlgItemText( int nID, LPTSTR lpStr, int nMaxCount ) const;
int GetDlgItemText( int nID, CString& rString ) const;
void SetDlgItemText( int nID, LPCTSTR lpszString );
ֱ�ӽ��ı�ת��Ϊ���֣�
UINT GetDlgItemInt( int nID, BOOL* lpTrans = NULL, BOOL bSigned = TRUE ) const;
void SetDlgItemInt( int nID, UINT nValue, BOOL bSigned = TRUE );


���ؼ����Ա����������
Claas Wizard->Member Variables,���� Category ѡ��value�������ֵ�,
���ѡ��control����ָ��ؼ�����ı�����������ʹ�ؼ�����������ı������������ˡ�
�����ڻ�ȡ����֮ǰҪ���� UpdateData ������ʹ֮��Ч��UpdateData�������ú�У������.
	UpdateData( TRUE );	//��ȡ�༭�ؼ�������ֵ
	m_num3 = m_num1 + m_num2;
	UpdateData( FALSE );	//У��༭�ؼ������ı������������ı�
����У����У�������õ����ͺͱ�����ȡֵ��Χ(����������˵Ļ�)
	int num1,num2,num3;
	char ch1[10],ch2[10],ch3[10];
	m_edit1.GetWindowText(ch1,10);
	m_edit2.GetWindowText(ch2,10);
	num1=atoi(ch1);
	num2=atoi(ch2);
	num3=num1+num2;
	itoa(num3,ch3,10);
	m_edit3.SetWindowText(ch3);


���ǻ�����ͨ��������Ϣ����ɷ��ʿؼ���Ŀ��	
	//::SendMessage(GetDlgItem(IDC_EDIT1)->m_hWnd,WM_GETTEXT,10,(LPARAM)ch1);//�õ��ؼ�
	//::SendMessage(m_edit1.m_hWnd,WM_GETTEXT,10,(LPARAM)ch1); //�����Ŀؼ�����
	//GetDlgItem(IDC_EDIT1)->SendMessage(WM_GETTEXT,10,(LPARAM)ch1);//
	m_edit1.SendMessage(WM_GETTEXT,10,(LPARAM)ch1);
	m_edit2.SendMessage(WM_GETTEXT,10,(LPARAM)ch2);
	num1=atoi(ch1);
	num2=atoi(ch2);
	num3=num1+num2;
	itoa(num3,ch3,10);
	m_edit3.SendMessage(WM_SETTEXT,0,(LPARAM)ch3);
����,ֱ����SendDlgItemMessage���������
	int num1,num2,num3;
	char ch1[10],ch2[10],ch3[10];
	SendDlgItemMessage(IDC_EDIT1,WM_GETTEXT,10,(LPARAM)ch1);
	SendDlgItemMessage(IDC_EDIT2,WM_GETTEXT,10,(LPARAM)ch2);
	num1=atoi(ch1);
	num2=atoi(ch2);
	num3=num1+num2;
	itoa(num3,ch3,10);
	SendDlgItemMessage(IDC_EDIT3,WM_SETTEXT,0,(LPARAM)ch3);
�������ͨ�� EM_SETSEL �� EM_GETSEL�����ø�ѡ��ֵ
	SendDlgItemMessage(IDC_EDIT3,EM_SETSEL,1,3);
	m_edit3.SetFocus();   //���ý�������
SendDlgItemMessage(IDC_EDIT3,EM_SETSEL,0,-1); //0,-1 ѡ�����е�����



�Ի���ؼ��������ַ�ʽ�ܽ�:
GetDlgItem()->Get(Set)WindowText()
GetDlgItemText()/SetDlgItemText()
GetDlgItemInt()/SetDlgItemInt()
���ؼ������ͱ��������
���ؼ��Ϳؼ����������
SendMessage()
SendDlgItemMessage()




�Ի������������չ
��̬������ʼ��Ϊ0
���ô��ڵ�Z-Order�ʹ��ڴ�С:SetWindowPos
	CString str;
	if(GetDlgItemText(IDC_BUTTON_CHANGE,str),str=="����<<")
	{
		SetDlgItemText(IDC_BUTTON_CHANGE,"��չ>>");
	}
	else
	{
		SetDlgItemText(IDC_BUTTON_CHANGE,"����<<");
	}

	static CRect rectLarge;
	static CRect rectSmall;
	
	if(rectLarge.IsRectNull())
	{
		CRect rectSeparator;
		GetWindowRect(&rectLarge);
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectSeparator);

		rectSmall.left=rectLarge.left;
		rectSmall.top=rectLarge.top;
		rectSmall.right=rectLarge.right;
		rectSmall.bottom=rectSeparator.bottom;
	}
		
	
	if(str=="����<<")
	{
		SetWindowPos(NULL,0,0,rectSmall.Width(),rectSmall.Height(),
			SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(NULL,0,0,rectLarge.Width(),rectLarge.Height(),
			SWP_NOMOVE | SWP_NOZORDER);
	}

Z-order
        ���ڵ�Z����������ص����ڶ��д��ڵ�λ�ã�������ڶ��ǰ�һ��������ᶨλ�ģ��������Ǵ���Ļ������չ��Z�ᡣZ����������Ĵ��ڸ������������Ĵ��ڣ�Z������ײ�Ĵ��ڱ����������Ĵ��ڸ��ǡ�Ӧ�ó������ô�����Z�����е�λ����ͨ����������һ���������ڵĺ��棬���Ƿ��ڴ��ڶѵĶ�����ײ���
        Windowsϵͳ��������������Z���򡪡�һ�����ڶ��㴰�ڡ�һ�������ֵܴ��ڣ�����һ����������㴰�ڡ���㴰�ڸ���������������㴰�ڣ����������ǲ��ǻ���ڻ���ǰ̨���ڡ�Ӧ�ó���ͨ������WS_EX_TOPMOST��񴴽���㴰�ڡ�
        һ������£�Windowsϵͳ�Ѹոմ����Ĵ��ڷ���Z����Ķ������û���ͨ����������һ���������ı�Z����Windowsϵͳ���ǰѻ�Ĵ��ڷ���Z����Ķ�����Ӧ�ó�����ú���BringWindowToTop��һ�����ڷ��õ�Z����Ķ���������SetWindowPos��DeferWindowPos��������Z����
�ֵܴ���
     ����ͬһ�������ڵĶ���Ӵ��ڽ��ֵܴ��ڡ�
�����
              �������Ӧ�ó���Ķ��㴰�ڣ�Ҳ���ǵ�ǰʹ�õĴ��ڡ�ֻ��һ�����㴰�ڿ����ǻ���ڣ�����û�ʹ�õ���һ���Ӵ��ڣ�Windowsϵͳ�ͼ���������Ӵ�����Ӧ�Ķ��㴰�ڡ�
            �κ�ʱ��ϵͳ��ֻ����һ�����㴰���ǻ�ġ��û�ͨ���������ڣ������е�һ���Ӵ��ڣ���ʹ��ALT+TAB��ALT+ESC��ϼ�������һ�����㴰�ڣ�Ӧ�ó�������ú���SetActiveWindow������һ�����㴰�ڡ�
ǰ̨���ںͺ�̨����
            ��Windowsϵͳ�У�ÿһ�����̿����ж���̣߳�ÿ���̶߳��ܴ������ڡ���������ʹ�ô��ڵ��̳߳�֮Ϊǰ̨�̣߳�������ھͳ�֮Ϊǰ̨���ڡ������������̶߳��Ǻ�̨�̣߳��ɺ�̨�߳��������Ĵ��ڽк�̨���ڡ�
            �û�ͨ������һ�����ڡ�ʹ��ALT+TAB��ALT+ESC��ϼ�������ǰ̨���ڣ�Ӧ�ó������ú���SetForegroundWindow����ǰ̨���ڡ�����µ�ǰ̨������һ�����㴰�ڣ���ôWindowsϵͳ�ͼ����������仰˵��Windowsϵͳ������Ӧ�Ķ��㴰�ڡ�



����ȱʡ��ť.һ�������ȱʡ��ťʼOK��ť
���ǿ���ͨ������OnOK�������ı�ȱʡ��ť��Enter������Ľ���.�����ж�:
1)����һ����
2)�ı䴰�ڹ��̺���
BOOL CTestDlg::OnInitDialog() 

ͨ��Ĭ��ȱʡ��ťʼOK��ť�Ľ����ź�,����Ҫȡ�� CDialog::OnOK();
����:
void CTestDlg::OnOK() 
{
	// TODO: Add extra validation here
	//GetDlgItem(IDC_EDIT1)->GetNextWindow()->SetFocus();
	//GetFocus()->GetNextWindow()->SetFocus();
	//GetFocus()->GetWindow(GW_HWNDNEXT)->SetFocus();
	GetNextDlgTabItem(GetFocus())->SetFocus();
	//CDialog::OnOK();
}
ok��ť��ȱʡID����: IDOK ,������IDC_OK,�������������OK��ťʱҪ����ID�Ÿ�ΪIDOK 


�ñ༭����ܻس���Ҫ�޸���������,ʹ"���� MultiLine"��ѡ��.











2006/11/28
lesson19,��̬���ӿ�
dumpbin
VC��binĿ¼�µ� VCVARS32.BAT �����������ǽ���VC�Ŀ��Ż�����.
��������ʾ���µ�ճ���Ϳ���
ճ���������Ҽ�ճ���Ϳ�����
���Ƶ������Ҽ�ѡ����,Ȼ�������������һ��,����������,��ô�ͽ���Ӧ���ݸ��Ƶ�����������.


�½�һ���յ�dll����,Ȼ�󴴽�һ��dll1.cpp�ļ�����
int  add(int a,int b)
{
	return a+b;
}

int  subtract(int a,int b)
{
	return a-b;
}
����֮��,���ǿ�����������
E:\zieckey\CPP-study\Lesson19\Dll1\Debug>dumpbin -exports dll1.dll
Microsoft (R) COFF Binary File Dumper Version 6.00.8168
Copyright (C) Microsoft Corp 1992-1998. All rights reserved.


Dump of file dll1.dll

File Type DLL

  Summary

        7000 .data
        1000 .idata
        2000 .rdata
        2000 .reloc
       2A000 .text
����û���κε�������,��ô���ǿ�������,����Դ�ļ�
_declspec(dllexport) int  add(int a,int b)
{
	return a+b;
}

_declspec(dllexport) int  subtract(int a,int b)
{
	return a-b;
}

����֮����ȥ����

E:\zieckey\CPP-study\Lesson19\Dll1\Debug>dumpbin -exports dll1.dll
Microsoft (R) COFF Binary File Dumper Version 6.00.8168
Copyright (C) Microsoft Corp 1992-1998. All rights reserved.


Dump of file dll1.dll

File Type DLL

  Section contains the following exports for Dll1.dll

           0 characteristics
    456BD6E2 time date stamp Tue Nov 28 142746 2006
        0.00 version
           1 ordinal base
           2 number of functions
           2 number of names

    ordinal hint RVA      name

          1    0 0000100A add@@YAHHH@Z
          2    1 00001005 subtract@@YAHHH@Z

  Summary

        7000 .data
        1000 .idata
        3000 .rdata
        2000 .reloc
       2A000 .text

����,������ǿ��������������Լ��µĺ�������,ֻ�������ƺ������Ĺ���,����VCΪ�˺������صķ���,�����Լ��Ĺ����޸������ǵ�Դ����ĺ�������.
���������������¸ոս�����dll1.dll��̬���ӿ�.
�����½�һ��win32����̨�Ŀչ���,�½�һ��dlltest.cpp ,����������Դ��
#include iostream.h
extern int add(int,int);   ��������������ⲿ����
extern int subtract(int,int);
void main(void)
{
	cout3+5 = add(3,5)endl;
	cout5-3 = subtract(5,3)endl;
}
����һ��
Compiling...
dlltest.cpp
Linking...
dlltest.obj  error LNK2001 unresolved external symbol int __cdecl substract(int,int) (substract@@YAHHH@Z)
dlltest.obj  error LNK2001 unresolved external symbol int __cdecl add(int,int) (add@@YAHHH@Z)
DebugDllTest.exe  fatal error LNK1120 2 unresolved externals
ִ�� link.exe ʱ����.
DllTest.exe - 1 error(s), 0 warning(s)

���Է����������ӵ�ʱ�������,��˵��������û�д�,�������ҵ�������������,��Ϊ�����������Ѿ�������.
���������ӵ�ʱ��û���ҵ�.���ǿ���������;
���ո����ɶ�̬���ӿ��ļ���ͬһĿ¼��,�ҵ�dll1.lib������ļ�,���������ǵĹ���Ŀ¼��,
��� Project��Settings  ��Linkѡ��ҵ�Objectlibrary modules  ��������� dll1.lib ��
���ԭ���������ӣ���ʹ�ÿո�ָ���

�õ������ٱ�����
--------------------Configuration DllTest - Win32 Debug--------------------
DllTest.exe - 0 error(s), 0 warning(s)
û�д���,ִ��ʱ�ֳ��ִ���,Ŷ,���ǵĳ�����ִ��ʱû���ҵ�dll1.dll����ļ�,��˵,����Ҳ��������ǰ���̵�Ŀ¼��.
��ִ��,ye,��ξͺ���,�����Ϣ����
3+5 = 8
5-3 = 2
Press any key to continue

���ǿ��Բ鿴�Բ鿴һ�������ִ�г����������Ϣ
E:\zieckey\CPP-study\Lesson19\DllTest\Debug>dumpbin -imports DllTest.exe
Microsoft (R) COFF Binary File Dumper Version 6.00.8168
Copyright (C) Microsoft Corp 1992-1998. All rights reserved.


Dump of file DllTest.exe

File Type EXECUTABLE IMAGE

  Section contains the following imports

    Dll1.dll
                43019C Import Address Table
                43003C Import Name Table
                     0 time date stamp
                     0 Index of first forwarder reference

                   0  add@@YAHHH@Z
                   1  subtract@@YAHHH@Z

    KERNEL32.dll
                4301D0 Import Address Table
                430070 Import Name Table
                     0 time date stamp
                     0 Index of first forwarder reference

                  CA  GetCommandLineA
                 174  GetVersion
                  7D  ExitProcess
                 22F  RtlUnwind
                 11A  GetLastError
                  1B  CloseHandle
                 2DF  WriteFile
                 218  ReadFile
                 26A  SetFilePointer
                 26D  SetHandleCount
                 152  GetStdHandle
                 115  GetFileType
                 150  GetStartupInfoA
                  51  DebugBreak
                 1AD  InterlockedDecrement
                 1F5  OutputDebugStringA
                 13E  GetProcAddress
                 1C2  LoadLibraryA
                 1B0  InterlockedIncrement
                 124  GetModuleFileNameA
                 29E  TerminateProcess
                  F7  GetCurrentProcess
                 2AD  UnhandledExceptionFilter
                  B2  FreeEnvironmentStringsA
                  B3  FreeEnvironmentStringsW
                 2D2  WideCharToMultiByte
                 106  GetEnvironmentStrings
                 108  GetEnvironmentStringsW
                 126  GetModuleHandleA
                 109  GetEnvironmentVariableA
                 175  GetVersionExA
                 19D  HeapDestroy
                 19B  HeapCreate
                 19F  HeapFree
                 2BF  VirtualFree
                  AA  FlushFileBuffers
                 1B8  IsBadWritePtr
                 1B5  IsBadReadPtr
                 1A7  HeapValidate
                 27C  SetStdHandle
                 241  SetConsoleCtrlHandler
                  BF  GetCPInfo
                  B9  GetACP
                 131  GetOEMCP
                 199  HeapAlloc
                 2BB  VirtualAlloc
                 1A2  HeapReAlloc
                 28B  SetUnhandledExceptionFilter
                 1B2  IsBadCodePtr
                 1E4  MultiByteToWideChar
                 1BF  LCMapStringA
                 1C0  LCMapStringW
                 153  GetStringTypeA
                 156  GetStringTypeW

  Summary

        6000 .data
        1000 .idata
        2000 .rdata
        2000 .reloc
       27000 .text



�������ǿ���ͨ��VC�ṩ��ͼ�λ����߲鿴���ǵĿ�ִ�г��������Ķ�̬���ӿ��ļ�,
��VC�İ�װĿ¼�µ� DSoftwaresMicrosoft Visual StudioVC98Microsoft Visual C++ 6.0 Tools Ŀ¼����������� Depends .
�����Բ鿴��ִ�г��������Ķ�̬���ӿ��ļ�

���ǻ���������������̬���ӿ���ĺ����ӿ�,Դ���޸�Ϊ
#include iostream.h
extern int add(int,int);
extern int subtract(int,int);
_declspec(dllimport) int add(int,int);
_declspec(dllimport) int subtract(int,int);
void main(void)
{
	cout3+5 = add(3,5)endl;
	cout5-3 = subtract(5,3)endl;
}
��������.
_declspec(dllimport) �͸��߱�������������ǴӶ�̬���ӿ��.lib�ļ��������,������������������Ч�ʸ��ߵĴ���.

���ǿ��԰������Լ����Ķ�̬���ӿ��ļ��ĺ����������ŵ�һ��ͷ�ļ���,�Ա�����û������̬���ӿ��ļ����װ�ĺ���ԭ��.
�õ�������ǰ�涯̬���ӿ�Ĺ��������һ��ͷ�ļ� dll1.h ,�������������
_declspec(dllimport) int add(int,int);
_declspec(dllimport) int subtract(int,int);

��ô�������ǾͿ��Խ�Դ���޸�Ϊ
#include iostream.h
extern int add(int,int);
extern int subtract(int,int);
#include ..Dll1dll1.h
void main(void)
{
	cout3+5 = add(3,5)endl;
	cout5-3 = subtract(5,3)endl;
}
��������.

���ǵ�������Է���,ǰ��Ķ�̬���ӿ�Դ���ļ�dll1.cpp
_declspec(dllexport) int  add(int a,int b)
{
	return a+b;
}
_declspec(dllexport) int  subtract(int a,int b)
{
	return a-b;
}
�����ǵ�����ʽ(dllexport),��ô�����̬���ӿ�Ͳ��ܱ����Լ���Դ��������,��ʱ���ǿ��Ըĸľ�����
dll1.cpp
#define DLL1_API _declspec(dllexport)
#include dll1.h
int  add(int a,int b)
{
	return a+b;
}
int  subtract(int a,int b)
{
	return a-b;
}


dll1.h
#ifdef DLL1_API
#else
#define DLL1_API _declspec(dllimport)
#endif
DLL1_API int add(int,int);
DLL1_API int subtract(int,int);


�������dll��Ϳ��Ա��Լ�����Ҳ���Ա��������������.
�����ٿ�����ô���ർ��,�������ͺ���
#ifdef DLL1_API
#else
#define DLL1_API _declspec(dllimport)
#endif
DLL1_API int add(int,int);
DLL1_API int subtract(int,int);
class DLL1_API Point
{
public
	void output( int x,int y);
};

������ǲ��뽫�����඼����,����ֻ�轫��Ĳ��ֹ��г�Ա��������,
���ǿ���������
#ifdef DLL1_API
#else
#define DLL1_API _declspec(dllimport)
#endif
DLL1_API int add(int,int);
DLL1_API int subtract(int,int);
class DLL1_API Point
{
public
	DLL1_API void output( int x,int y);
	void test();
};
�����void test();����һ���Ա��õ�.
������dumpbin -exports dll1.dll�����������
E:\zieckey\CPP-study\Lesson19\Dll1\Debug>dumpbin -exports dll1.dll
Microsoft (R) COFF Binary File Dumper Version 6.00.8168
Copyright (C) Microsoft Corp 1992-1998. All rights reserved.


Dump of file dll1.dll

File Type DLL

  Section contains the following exports for Dll1.dll

           0 characteristics
    456BE737 time date stamp Tue Nov 28 153727 2006
        0.00 version
           1 ordinal base
           3 number of functions
           3 number of names

    ordinal hint RVA      name

          1    0 00001019 add@@YAHHH@Z
          2    1 0000101E output@Point@@QAEXHH@Z
          3    2 00001014 subtract@@YAHHH@Z

  Summary

        7000 .data
        1000 .idata
        3000 .rdata
        2000 .reloc
       31000 .text

����Ϳ��Է���ֻ��
          2    1 0000101E output@Point@@QAEXHH@Z
��û��test()


�����ᵽ��VC++���������������ֽ����˸�д,�����������������˵Ҳ��Ͳ���ʲô����,��Ϊ�����������ܿ����Ҳ��������ĺ���,
��Ϊ�����Ѿ����Ķ���.��ô���Ǿ�ϣ��������ֲ�Ҫ����.������Լ��� extern C ��ʶ
dll1.cpp
#define DLL1_API extern C _declspec(dllexport)
#include dll1.h
int  add(int a,int b)
{
	return a+b;
}
int  subtract(int a,int b)
{
	return a-b;
}

dll1.h
#ifdef DLL1_API
#else
#define DLL1_API extern C _declspec(dllimport)
#endif
DLL1_API int add(int,int);
DLL1_API int subtract(int,int);
������,�����������,
E:\zieckey\CPP-study\Lesson19\Dll1\Debug>dumpbin -exports dll1.dll
Microsoft (R) COFF Binary File Dumper Version 6.00.8168
Copyright (C) Microsoft Corp 1992-1998. All rights reserved.


Dump of file dll1.dll

File Type DLL

  Section contains the following exports for Dll1.dll

           0 characteristics
    456BE969 time date stamp Tue Nov 28 154649 2006
        0.00 version
           1 ordinal base
           2 number of functions
           2 number of names

    ordinal hint RVA      name

          1    0 0000100A add
          2    1 00001005 subtract

  Summary

        7000 .data
        1000 .idata
        3000 .rdata
        2000 .reloc
       2A000 .text

����Ϳ��Կ�������û�иı�,
������ extern C ��ʶҲ��ȱ��,������ֻ�ܱ�ʾȫ�ֺ���,
��������˵,�����ܵ�����ĳ�Ա����.
�������Լ�����ı��˵Ļ�,��ʹ���� extern C ��ʶ,���������ǻᱻ�ı�
�������Ǿ�������
dll1.cpp
#define DLL1_API extern C _declspec(dllexport)
#include dll1.h
int _stdcall  add(int a,int b)
{
	return a+b;
}
int _stdcall  subtract(int a,int b)
{
	return a-b;
}

dll1.h
#ifdef DLL1_API
#else
#define DLL1_API extern C _declspec(dllimport)
#endif
DLL1_API int _stdcall add(int,int);
DLL1_API int _stdcall subtract(int,int);
������,�����������
E:\zieckey\CPP-study\Lesson19\Dll1\Debug>dumpbin -exports dll1.dll
Microsoft (R) COFF Binary File Dumper Version 6.00.8168
Copyright (C) Microsoft Corp 1992-1998. All rights reserved.


Dump of file dll1.dll

File Type DLL

  Section contains the following exports for Dll1.dll

           0 characteristics
    456BEBDB time date stamp Tue Nov 28 155715 2006
        0.00 version
           1 ordinal base
           2 number of functions
           2 number of names

    ordinal hint RVA      name

          1    0 00001005 _add@8
          2    1 0000100A _subtract@8

  Summary

        7000 .data
        1000 .idata
        3000 .rdata
        2000 .reloc
       2A000 .text
����Ϳ��Կ������ֻ��Ƿ����˸ı�,
_add@8�����8��ʾadd�����Ĳ�����ռ�ֽ���.
���ǿ�������Ľ������.

�������½�һ��dll�Ŀչ���,����ΪDll2       
���½�һ��C++Դ�ļ�,����Ϊdll2.cpp,
dll2.cpp
int add(int a,int b)
{
	return a+b;
}
int subtract(int a,int b)
{
	return a-b;
}

Ȼ�����Ǵ���һ��ģ�鶨���ļ�,����Ϊdll2.def,Ȼ��������ǵĹ�����.����������

LIBRARY Dll2

EXPORTS
add
subtract



���� LIBRARY Dll2 �������һ��Ҫ�����ǵĹ�������ƥ��,������仰Ҳ���Ǳ����.
EXPORTS������̬���ӿ���Ҫ�����ĺ�������,���ǿ����� MSDN �в鿴һ�������÷�.

����һ��,�����������
E:\zieckey\CPP-study\Lesson19\Dll2\Debug>dumpbin -exports dll2.dll
Microsoft (R) COFF Binary File Dumper Version 6.00.8168
Copyright (C) Microsoft Corp 1992-1998. All rights reserved.


Dump of file dll2.dll

File Type DLL

  Section contains the following exports for Dll2.dll

           0 characteristics
    456BEECE time date stamp Tue Nov 28 160950 2006
        0.00 version
           1 ordinal base
           2 number of functions
           2 number of names

    ordinal hint RVA      name

          1    0 0000100A add
          2    1 00001005 subtract

  Summary

        7000 .data
        1000 .idata
        3000 .rdata
        2000 .reloc
       2A000 .text
       
����Ϳ��Կ�������û�иı�,��ԭ����һ��.


�������Ƕ�������ʽ���ӵķ�ʽ���ö�̬���ӿ��,
�������ǿ�����һ�ַ���,��ʾ����
�����ǵ� DllTest �����е� Project��Settings  
��Linkѡ��е� Objectlibrary modules ɾ�� dll1.lib 

�����Ҫ�õ�һ������
HINSTANCE LoadLibrary
(
  LPCTSTR lpLibFileName    address of filename of executable module
);
����ӳ��ָ����ģ�鵽Ӧ�ý��̵ĵ�ַ�ռ�

��ú����ĵ�ַ�ռ������º���,
FARPROC GetProcAddress(
  HMODULE hModule,     handle to DLL module
  LPCSTR lpProcName    name of function
);

�õ�,�������ǿ������ǵĲ��Գ�����ôд,�����Թ����е� dlltest.cpp �ļ���Ϊ����

dlltest.cpp
#include iostream.h
#include windows.h
void main(void)
{
	HINSTANCE hInst;
	hInst=LoadLibrary(Dll2.dll);
	typedef int (FUNCPROC)(int a,int b);
	FUNCPROC ADD=(FUNCPROC)GetProcAddress(hInst,add);
	FUNCPROC SUB=(FUNCPROC)GetProcAddress(hInst,subtract);
	if(!ADD)
	{
		cout��ȡ������ַʧ�ܣ�endl;
		return;
	}
	cout3+5 = ADD(3,5)endl;
	cout5-3 = SUB(5,3)endl;
	FreeLibrary(hInst);	 �ͷŶ�̬���ӿ�	
}

��������,Ŷ,�����˽������±��봦���dll�ļ� dll2.dll ���Ƶ����ǵĲ��Գ��򹤳�Ŀ¼��.
���н������
3+5 = 8
5-3 = 2
Press any key to continue

�������ǿ��Է�������ֻ������һ�� dll2.dll �ļ�,
��û�п������ǵ� dll2.lib ,��������Ϊ�����Ƕ�̬���ص�.
��̬���صĺô�����������Ҫ�ĵط�����,�������Խ�Լ�ڴ�ռ�.
���������ʽ���ӵķ�ʽ,��ô��������������ʱ,���dll�ⶼҪ���ص��ڴ���,
��ʱ���˷��ڴ��,���ҳ�������ʱ��Ҳ����.



�������������ı���õķ�ʽ,��dll2.cpp�ļ��ı�����
dll2.cpp
int add(int a,int b)
{
	return a+b;
}
int subtract(int a,int b)
{
	return a-b;
}

����һ��,�����������
E:\zieckey\CPP-study\Lesson19\Dll2\Debug>dumpbin -exports dll2.dll
Microsoft (R) COFF Binary File Dumper Version 6.00.8168
Copyright (C) Microsoft Corp 1992-1998. All rights reserved.


Dump of file dll2.dll

File Type DLL

  Section contains the following exports for Dll2.dll

           0 characteristics
    456BF57D time date stamp Tue Nov 28 163821 2006
        0.00 version
           1 ordinal base
           2 number of functions
           2 number of names

    ordinal hint RVA      name

          1    0 0000100A add
          2    1 00001005 subtract

  Summary

        7000 .data
        1000 .idata
        3000 .rdata
        2000 .reloc
       2A000 .text
����Ϳ��Կ�����ʹ�ı��˵��÷�ʽ,��������û�иı�,��ԭ����һ��.
�õ�,��ô�������������Գ���,
��Ȼ,�����˽������±��봦���dll�ļ� dll2.dll ���Ƶ����ǵĲ��Գ��򹤳�Ŀ¼��.
����,û�д���,������ʱ�����˴���,������Ϊ���Ǹı��˵��õ�Լ��,
��Ȼ,�ڵ��õ�ʱ��ҲҪ��ѭ������Լ��,�����Թ����е� dlltest.cpp �ļ���Ϊ����

dlltest.cpp
#include iostream.h
#include windows.h
void main(void)
{
	HINSTANCE hInst;
	hInst=LoadLibrary(Dll2.dll);
	typedef int (_stdcall FUNCPROC)(int a,int b);
	FUNCPROC ADD=(FUNCPROC)GetProcAddress(hInst,add);
	FUNCPROC SUB=(FUNCPROC)GetProcAddress(hInst,subtract);
	if(!ADD)
	{
		cout��ȡ������ַʧ�ܣ�endl;
		return;
	}
	cout3+5 = ADD(3,5)endl;
	cout5-3 = SUB(5,3)endl;
	FreeLibrary(hInst);	 �ͷŶ�̬���ӿ�	
}
��������������.
���������������ڱ�������Ŀ�ִ�г��� dlltest.exe �ĵ�����Ϣ.
E:\zieckey\CPP-study\Lesson19\DllTest\Debug>dumpbin -imports DllTest.exe
Microsoft (R) COFF Binary File Dumper Version 6.00.8168
Copyright (C) Microsoft Corp 1992-1998. All rights reserved.


Dump of file DllTest.exe

File Type EXECUTABLE IMAGE

  Section contains the following imports

    KERNEL32.dll
                43015C Import Address Table
                430028 Import Name Table
                     0 time date stamp
                     0 Index of first forwarder reference

                  B4  FreeLibrary
                 13E  GetProcAddress
                 1C2  LoadLibraryA
                  CA  GetCommandLineA
                 174  GetVersion
                  7D  ExitProcess
                 22F  RtlUnwind
                 11A  GetLastError
                  1B  CloseHandle
                 2DF  WriteFile
                 218  ReadFile
                 26A  SetFilePointer
                 26D  SetHandleCount
                 152  GetStdHandle
                 115  GetFileType
                 150  GetStartupInfoA
                  51  DebugBreak
                 1AD  InterlockedDecrement
                 1F5  OutputDebugStringA
                 1B0  InterlockedIncrement
                 124  GetModuleFileNameA
                 29E  TerminateProcess
                  F7  GetCurrentProcess
                 2AD  UnhandledExceptionFilter
                  B2  FreeEnvironmentStringsA
                  B3  FreeEnvironmentStringsW
                 2D2  WideCharToMultiByte
                 106  GetEnvironmentStrings
                 108  GetEnvironmentStringsW
                 126  GetModuleHandleA
                 109  GetEnvironmentVariableA
                 175  GetVersionExA
                 19D  HeapDestroy
                 19B  HeapCreate
                 19F  HeapFree
                 2BF  VirtualFree
                  AA  FlushFileBuffers
                 1B8  IsBadWritePtr
                 1B5  IsBadReadPtr
                 1A7  HeapValidate
                 27C  SetStdHandle
                 241  SetConsoleCtrlHandler
                  BF  GetCPInfo
                  B9  GetACP
                 131  GetOEMCP
                 199  HeapAlloc
                 2BB  VirtualAlloc
                 1A2  HeapReAlloc
                 28B  SetUnhandledExceptionFilter
                 1B2  IsBadCodePtr
                 1E4  MultiByteToWideChar
                 1BF  LCMapStringA
                 1C0  LCMapStringW
                 153  GetStringTypeA
                 156  GetStringTypeW

  Summary

        6000 .data
        1000 .idata
        2000 .rdata
        2000 .reloc
       27000 .text
       
����Ϳ��������ǵ� dll2.dll ����Ϣ��.��Ϊ����ʱ��̬����

���ǿ���dll2.dll�����Ϣ������
          1    0 0000100A add
          2    1 00001005 subtract
���ǿ���ͨ����ŵ�������������,���������õ��� MAKEINTRESOURCE      
�����Թ����е� dlltest.cpp �ļ���Ϊ����

dlltest.cpp
#include iostream.h
#include windows.h
void main(void)
{
	HINSTANCE hInst;
	hInst=LoadLibrary(Dll2.dll);
	typedef int (_stdcall FUNCPROC)(int a,int b);
	FUNCPROC ADD=(FUNCPROC)GetProcAddress(hInst,MAKEINTRESOURCE(1));
	FUNCPROC SUB=(FUNCPROC)GetProcAddress(hInst,MAKEINTRESOURCE(2));
	if(!ADD)
	{
		cout��ȡ������ַʧ�ܣ�endl;
		return;
	}
	cout3+5 = ADD(3,5)endl;
	cout5-3 = SUB(5,3)endl;
	FreeLibrary(hInst);	 �ͷŶ�̬���ӿ�	
}
��������������.  
��������Ӧ��ͨ��������������dll���еĺ���.
��Ϊ����ó���ɶ��Ը���,������ҲСЩ

���ڶ�̬���ӿ�Ŀ�ѡ��������ʱ DllMain
BOOL WINAPI DllMain(
  HINSTANCE hinstDLL,   handle to DLL module
  DWORD fdwReason,      reason for calling function
  LPVOID lpvReserved    reserved
);

�������ǿ���ͨ��ģ�黰���ɶ�̬���ӿ��ǱȽϺõ�ѡ��.






Lesson8
���ܰ�ť�����Ա�����
��ClassWizard�����µ���ʱ,��ʱ��������ʶ�������,��ô������Ҫ�Ƚ����̹ر�,
Ȼ��ɾ������Ŀ¼�µ�*.clw�ļ�,Ȼ���ٴ򿪹���,������ʾ����һ��ͬ�����ļ�.

���Ա�(������QT�е�TabWidget)�Ĵ�������:
Objects of class CPropertyPage represent individual pages of a property sheet, 
otherwise known as a tab dialog box. As with standard dialog boxes, 
you derive a class from CPropertyPage for each page in your property sheet. 
To use CPropertyPage-derived objects, first create a CPropertySheet object, 
and then create an object for each page that goes in the property sheet. 
Call CPropertySheet::AddPage for each page in the sheet, 
and then display the property sheet by calling CPropertySheet::DoModal for a modal property sheet, 
or CPropertySheet::Create for a modeless property sheet.

�������Ա��ķ���
->���ȵ������ɼ��� CPropertyPage �Ի���,����CProp1,CProp2,CProp3,...
->����һ������ CMyPropertySheet,�̳��� CPropertySheet
->�� CMyPropertySheet �зֱ����� CProp1,CProp2,CProp3,...��ʵ������
->�� CMyPropertySheet �Ĺ��캯���е��� AddPage(...)�ֱ�ǰ�������ҳ��ӽ���
->����ʵ����һ�� CMyPropertySheet ����,Ȼ����� DoModal �Ϳ�����.


���������򵼵ķ���:
->���ȵ������ɼ��� CPropertyPage �Ի���,����CProp1,CProp2,CProp3,...
->����һ������ CMyPropertySheet,�̳��� CPropertySheet
->�� CMyPropertySheet �зֱ����� CProp1,CProp2,CProp3,...��ʵ������
->�� CMyPropertySheet �Ĺ��캯���е��� AddPage(...)�ֱ�ǰ�������ҳ��ӽ���
->����ʵ����һ�� CMyPropertySheet ����,Ȼ�����ε��� SetWizardMode  DoModal �Ϳ�����.
�����������ɵ���,�ڵ�һ������"��һ��",�����һ����Ҫ"��һ��",���Ǳ����޸���
������� SetWizardButtons �����ð�ť��.

Call this member function to enable or disable the Back, Next, or Finish button 
in a wizard property sheet. Call SetWizardButtons only after the dialog is open;
 you can��t call SetWizardButtons before you call DoModal.
  Typically, you should call SetWizardButtons from CPropertyPage::OnSetActive.
����˵Ӧ���� CPropertyPage::OnSetActive �е���  SetWizardButtons
BOOL CProperty3::OnSetActive() 
{
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_FINISH | PSWIZB_BACK );
	return CPropertyPage::OnSetActive();
}

���������ѡ��ťʱ,Ҫ����һ���������е�"��(Group)"ѡ��,���������ų�������
��ô�������ڶ���"��(Group)"ѡ��֮ǰ�����е�ѡ��ť����һ��ġ�
�Ե�ѡ��ť��ѡ����жϿ�������һ����������

CListBox 
CComboBox Ĭ���������ܣ�Ҫ�ǲ�����������������������˳�����У����Խ������Եġ�sort����ѡ��

void *memset( void *dest, int c, size_t count );���Գ�ʼ��һ���ڴ�
����:
BOOL bLike[10];
memset(bLike,0,sizeof(bLike));



2006/11/29
lesson 9
Ӧ�ó������
1. �ڴ����������֮ǰ�޸�
�޸�Ӧ�ó������ۿ����ڿ�����PreCreateWindow������ȥ�޸�
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

�ı����:
	cs.style &= ~FWS_ADDTOTITLE ;   //��һ���Ǳ���ģ��ô��ڲ����� FWS_ADDTOTITLE ����
	cs.lpszName = "http://blog.csdn.net/zieckey"

�ú��������ڴ��ڴ���֮��ı���ۡ�
LONG SetWindowLong(
  HWND hWnd,       // handle of window
  int nIndex,      // offset of value to set
  LONG dwNewLong   // new value
);
�������ǿ�����
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
....
	SetWindowLong( m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW );  //ȥ���ĵ��ı���
0....
}

��ȡ���д������ͣ�
LONG GetWindowLong(
  HWND hWnd,  // handle of window
  int nIndex  // offset of value to retrieve
);

ȡ�����ڵ���󻯰�ť��
SetWindowLong(m_hWnd,GWL_STYLE,GetWindowLong(m_hWnd,GWL_STYLE) & ~WS_MAXIMIZEBOX);

�޸Ĵ��ڵĹ��ͱ���Ҫ��View����ȥ�޸ģ���Ϊ���ǿ����ĵ��ĵ���������渲����View��
���޸Ĵ��ڵ�ͼ��Ⱦ�Ӧ����Frame�����޸ġ�

�޸Ĵ��ڵ�ͼ�꣺
{
	WNDCLASS wndcls;
	wndcls.cbClsExtra=0;
	wndcls.cbWndExtra=0;
	wndcls.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor=LoadCursor(NULL,IDC_HELP);
	wndcls.hIcon=LoadIcon(NULL,IDI_ERROR);
	wndcls.hInstance=AfxGetInstanceHandle();
	wndcls.lpfnWndProc=::DefWindowProc;
	wndcls.lpszClassName="sunxin.org";
	wndcls.lpszMenuName=NULL;
	wndcls.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);
	cs.lpszClass="sunxin.org";
}	
��һ���̿���ͨ���������ʵ�֣�	
cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,0,0,LoadIcon(NULL,IDI_WARNING));
�������ʹ��ȱʡ��ֵ��
cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);
��õ�һ��͸���Ĵ���
	
2. �ڴ����������֮���޸�	
��OnCreate�����е���SetClassLong
SetClassLong(m_hWnd,GCL_HICON,(LONG)LoadIcon(NULL,IDI_ERROR));	

AfxGetInstanceHandle   �õ���ǰ��Ӧ�ó���ʵ�����Obtains a handle to the current application instance.
MAKEINTRESOURCE ����ԴIDת��Ϊ�ַ����� The MAKEINTRESOURCE macro converts an integer value to a resource type compatible with Win32 resource-management functions
��CMainFrame��Ĺ��캯���м���ͼ��ķ���:
����ԭ��:
HICON LoadIcon(
  HINSTANCE hInstance, // handle to application instance
  LPCTSTR lpIconName   // icon-name string or icon resource identifier
);
{
	m_hIcons[0]=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1));
	m_hIcons[1]=LoadIcon(theApp.m_hInstance,MAKEINTRESOURCE(IDI_ICON2));  //�����֮ǰ����һ��:  extern CStyleApp theApp;
	m_hIcons[2]=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON3));
}

�����Լ��Ĺ�����:
1. Create a toolbar resource.
2. Construct the CToolBar object.
3. Call the Create (or CreateEx) function to create the Windows toolbar and attach it to the CToolBar object.
4. Call LoadToolBar to load the toolbar resource. 
����ʵ��:(������Բο�MFCԴ����Ϊ�������ɹ������ķ���)
{
	if (!m_newToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_newToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_newToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_newToolBar);
}
	
������"�˵�->�鿴"������һ����,�����������½��Ĺ�������ʾ������
{
		{
				if(m_newToolBar.IsWindowVisible())
				{
					m_newToolBar.ShowWindow(SW_HIDE);
				}
				else
				{
					m_newToolBar.ShowWindow(SW_SHOW);
				}
				RecalcLayout();   //��⹤����,���û�й�����,��ô�����ع�����
				DockControlBar(&m_newToolBar);  //ͣ��������
		}
		��������ķ�ʽ:
		{
				ShowControlBar(&m_newToolBar,!m_newToolBar.IsWindowVisible(),FALSE);
		}			
}

Ϊ���ǵ�"�˵�->�鿴"�������ĸ�ѡ���:
{
		void CMainFrame::OnUpdateViewNewtool(CCmdUI* pCmdUI) 
		{
			// TODO: Add your command update UI handler code here
			pCmdUI->SetCheck(m_newToolBar.IsWindowVisible());
		}
}


״̬���ı��:
{
	//��ʾ������
	static UINT indicators[] =
	{
		ID_SEPARATOR,           // status line indicator
		ID_INDICATOR_CAPS,      //��Сд���ؼ�
		ID_INDICATOR_NUM,				//���ֿ��ؼ�
		ID_INDICATOR_SCRL,			//Scroll���ؼ�
	};
	//״̬������
	CStatusBar  m_wndStatusBar;
	
	//ʵ��:
	{
			if (!m_wndStatusBar.Create(this) ||
			!m_wndStatusBar.SetIndicators(indicators,
			  sizeof(indicators)/sizeof(UINT)))
			{
				TRACE0("Failed to create status bar\n");
				return -1;      // fail to create
			}
	}
	
	
	{
		����������״̬���������Ŀʱ,ֻ��������Դ��"String Table"�������Ӧ��,����: IDS_INDICATOR_TIMER
		Ȼ�� IDS_INDICATOR_TIMER ��ӵ�indicators����Ķ�����,����:
		static UINT indicators[] =
		{
			ID_SEPARATOR,           // status line indicator
			IDS_INDICATOR_TIMER,
			ID_INDICATOR_CAPS,      //��Сд���ؼ�
			ID_INDICATOR_NUM,				//���ֿ��ؼ�
			ID_INDICATOR_SCRL,			//Scroll���ؼ�
		};
		�����Ϳ�����״̬���������Ӧ����Ŀ��.
	}
	
	��״̬����ʾ���ǵ���Ϣ,����������ʾ CString str="zieckey";
	{
				�򵥵�ʵ��
				{
					//����� index ��״̬���е�������,Ҳ���Ǻ�indicators�����ж�Ӧ����	
					//m_wndStatusBar.SetPaneText(index,str);
				}
			
				  //����ϸ��ʵ��
				  {
							CTime t=CTime::GetCurrentTime();  //�õ�ϵͳʱ��
							CString str=t.Format("%H:%M:%S"); //��ʽ�����ַ�����
							CClientDC dc(this);
							CSize sz=dc.GetTextExtent(str);		//�õ��ַ��������ʾ����
							int index=0;
							index=m_wndStatusBar.CommandToIndex(IDS_TIMER);  //�õ�������
							 
							//����״̬����Ϣ,��ǡ���Ŀ����ʾ�ַ���
							m_wndStatusBar.SetPaneInfo(index,IDS_TIMER,SBPS_NORMAL,sz.cx); 
							m_wndStatusBar.SetPaneText(index,str); //��ʾ�ַ���
				  }
		  
				  {
						  		//Ϊ�˱���ʵʱ�������ǵ�ϵͳʱ��,����Ĵ�������� OnTimer ������ʵ��:
						  		//��Ȼ���������һ��:  SetTimer(1,1000,NULL);
									void CMainFrame::OnTimer(UINT nIDEvent) 
									{				
										CTime t=CTime::GetCurrentTime();
										CString str=t.Format("%H:%M:%S");
										CClientDC dc(this);
										CSize sz=dc.GetTextExtent(str);
										m_wndStatusBar.SetPaneInfo(1,IDS_TIMER,SBPS_NORMAL,sz.cx);
										m_wndStatusBar.SetPaneText(1,str);
											
										CFrameWnd::OnTimer(nIDEvent);
									}		  									  
					}       
	}
	
	
	
	
	
}

�õ�ϵͳʱ��
{
	CTime t=CTime::GetCurrentTime();
	CString str=t.Format("%H:%M:%S");
}


�������Ĵ���:
{
		//������λ�ô���
		{
				m_progress.Create(WS_CHILD | WS_VISIBLE | PBS_VERTICAL,CRect(100,100,120,200),this,123);
				m_progress.SetPos(50);//���ý�����ֵ,���������м�
		}
		//��״̬���д���
		{
					//������OnPaint������ȥ����
					void CMainFrame::OnPaint() 
					{
						CPaintDC dc(this); // device context for painting
						CRect rect;
						m_wndStatusBar.GetItemRect(2,&rect);
						if(!m_progress.m_hWnd)
								m_progress.Create(WS_CHILD | WS_VISIBLE ,//| PBS_SMOOTH,rect,&m_wndStatusBar,123);
						else
								m_progress.MoveWindow(rect);
						m_progress.SetPos(50);
					}
		}
		
		//�ý�����������:
		��OnTimer�����е���m_progress.StepIt();�Ϳ�����
}

��״̬������ʾ��������ֵ:
{
			void CStyleView::OnMouseMove(UINT nFlags, CPoint point) 
			{
				
				CString str;
				str.Format("x=%d,y=%d",point.x,point.y);
				//����һ:
				//((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(str);
				//������:
				//((CMainFrame*)GetParent())->SetMessageText(str);
				//������:
				//((CMainFrame*)GetParent())->GetMessageBar()->SetWindowText(str);
				//������,AFX_IDW_STATUS_BAR��ϵͳԤ�ȶ����ֵ
				GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowText(str);
				
				CView::OnMouseMove(nFlags, point);
			}
}


�Զ�����Ϣ:
{
		��Ϣ����:
		{
				//��
				//�����WM_USER��ϵͳ����ĺ�,С��WM_USER����������ϵͳ��Ϣռ��
				//��ô�����Զ������Ϣֵ�Ϳ�����������
				#define UM_PROGRESS		WM_USER+1
		}
		��Ϣ������ԭ������:
		{
				.....
				//}}AFX_MSG
				afx_msg void OnProgress();
				DECLARE_MESSAGE_MAP()
		}
		��Ϣӳ��:
		{
				//}}AFX_MSG_MAP
				ON_MESSAGE(UM_PROGRESS,OnProgress)
				END_MESSAGE_MAP()
		}
		��������Ϣ��������ʵ��
		
}

���������������:
{
		ѡ��project->Add to project->conponent and controls..
		������VC�ṩ�����ǵ�һЩ�齨�Ϳؼ�������ѡ�� Visual C++ Components ,
		��ѡ�� Splash screen ���뵽���ǵĹ�����.
		�� int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) ����һ�� SetTimer(1, 750, NULL);
		��������������ʾʱ�� 
}





2006/11/30

Lesson 12 �ļ�����

ָ������ָ��
{
		#include <iostream.h>
		
		void main()
		{
			char ch[5] = "lisi";
			const char * pCStr1 = ch;
		
			//*pCStr1= 'w';		//error   pCStr1 ָ��Ķ����ǳ���,���Բ��Ǳ��޸�
			pCStr1 = "zieckey" ;	//OK	pCStr1 ָ��Ķ����ǳ���,�������ĵ�ַ�ǿ����޸ĵ�
		
			char * const pCStr2 = ch;
		
			*pCStr2 = 'w';			//OK 	*pCStr2 ���ǳ���,Ҳ����˵pCStr2ָ��������ǿ����޸ĵ� 
			//pCStr2 = "zieckey";   //error pCStr2�ǳ���,Ҳ����pCStr2�ĵ�ַ�ǳ���
		
			const char * const pCCStr = ch;
			//*pCCStr = 'w';			//error		
			//pCCStr = "zieckey";   //error ���ʱ�� pCCStr Ҳ�ǳ��� 
		}
}


C�����ж��ļ��Ĳ���:
{
			FILE *fopen( const char *filename, const char *mode );�÷�:

			size_t fwrite( const void *buffer, size_t size, size_t count, FILE *stream ); �÷�:
			(
					����������д��6���ֽ�,
					��� size = 1,��ô count = 6
					��� size = 2,��ô count = 3
			)
			
			C���Զ��ļ��Ĳ���ʹ���ǵĻ����͵�,Ҳ����˵����Ϊÿ���򿪵��ļ�����һ���ڴ滺����.
			{
					д���ļ����ݵ����̺󲢱����˳�
					{
							FILE *pFile=fopen("1.txt","w");
							fwrite("http://blog.csdn.net/zieckey",1,strlen("http://blog.csdn.net/zieckey"),pFile);
							fclose(pFile);			
					}
					д���ļ����ݵ����̺󵫲��˳�:
					{
							FILE *pFile=fopen("1.txt","w");
							fwrite("http://blog.csdn.net/zieckey",1,strlen("http://blog.csdn.net/zieckey"),pFile);
							fflush(pFile);  //ˢ�»�����,���ǽ��ڴ�������д�뵽����			
					}			
					
					int fseek( FILE *stream, long offset, int origin );//�ƶ��ļ�ָ�뵽ָ��λ�ô�

					//��ȡ�ļ�����1
					void CFileView::OnFileRead() 
					{
						FILE *pFile=fopen("1.txt","r");
						char ch[100];
						memset(ch,0,100);   //���ַ��������е����ݶ���ʼ��Ϊ0
						fread(ch,1,100,pFile);
						MessageBox(ch);
						fclose(pFile);
					}				

					//��ȡ�ļ�����2
					void CFileView::OnFileRead() 
					{
						//��ʵ���ļ���С�����ڴ�ռ�
						FILE *pFile=fopen("1.txt","r");
						char *pBuf;
						fseek(pFile,0,SEEK_END);  //�ƶ��ļ�ָ�뵽�ļ�ĩβ
						int len=ftell(pFile);     //�õ��ļ���С�ֽ���			
						pBuf=new char[len+1];     //����������һ���ֽ�,��Ҫ�Ǵ��'\0'
						rewind(pFile);            //�ƶ��ļ�ָ�뵽�ļ���ʼ��
						fread(pBuf,1,len,pFile);
						pBuf[len]=0;
						MessageBox(pBuf);
						fclose(pFile);
					}					
			}
}

�ļ�
{
		�������ļ����ı��ļ�����:
		{
				�ļ����ڼ�����ڴ����Զ����Ʊ�ʾ���������ⲿ�洢�����ϵ���һ�ִ����ʽ��
				�ļ�ͨ����Ϊ�������ļ����ı��ļ���
				�������ļ��ǰ����� ASCII ����չ ASCII �ַ��б�д�����ݻ����ָ����ļ���
				һ���ǿ�ִ�г���ͼ�Ρ�ͼ�������ȵ��ļ���
				�ı��ļ�(Ҳ��ΪASCII�ļ�)������ÿһ���ֽڴ�ŵ��ǿɱ�ʾΪһ���ַ���ASCII������ļ���
				������ ���С�Ϊ�����ṹ��һ����Ϣ��֯�ʹ洢��ʽ���ļ���
				�����κ����ִ�������Ķ��ļ��ı��ļ���  
		}
		�ı���ʽ�Ͷ����Ʒ�ʽ:
		{
				�����ǰ����ı���ʽ���ļ���д������ʱ��һ�����������ַ�(ASCIIΪ10)��
				���ת��Ϊ�س�������(ASCIIΪ13��10)��
				�ڶ�ȡ�ļ�ʱ��һ�������س������е����(��������ASCII 13��10)��
				���ת��Ϊ�����ַ�(ASCIIΪ10)��
				
				�����ǰ��ն����Ʒ�ʽ���ļ���д�����ݣ����������ڴ��еĴ洢��ʽԭ��������ļ��С�		
			
				���������ڶ�д�ļ���ʱ��Ӧ��һ��.
				����,�����Ƕ������ļ������ı��ļ����Ƕ�����ͨ�������Ʒ�ʽ��д�ļ�,�������ȫ��.
		}
}




C++�����ж��ļ��Ĳ���:
{
		ͨ��ofstream���������ļ�,��Ȼ���Ǳ������ #include <fstream.h>
		{
				ofstream ofs("4.txt");
				ofs.write("http://www.sunxin.org",strlen("http://www.sunxin.org"));
				ofs.close();			
		}
		���ļ�:
		{
				ifstream ifs("4.txt");
				char ch[100];
				memset(ch,0,100);
				ifs.read(ch,100);
				ifs.close();
				MessageBox(ch);		
		}		
}

�����ٿ���WIN API�е��ļ�����:  CreateFile
{
		д�ļ�:
		{
				HANDLE hFile;
				hFile=CreateFile(	"5.txt",		//�ļ���
									GENERIC_WRITE,
									0,	
									NULL,			//ʹ��ȱʡ�İ�ȫ��
									CREATE_NEW,
									FILE_ATTRIBUTE_NORMAL,
									NULL);
				DWORD dwWrites;//����ʵ��д����ֽ���
				WriteFile(hFile,"http://blog.csdn.net/zieckey",strlen("http://blog.csdn.net/zieckey"),
					&dwWrites,NULL);  
				CloseHandle(hFile);		
		}
		���ļ�:
		{
				HANDLE hFile;
				hFile=CreateFile("5.txt",GENERIC_READ,0,NULL,OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,NULL);
				char ch[100];
				DWORD dwReads;
				ReadFile(hFile,ch,100,&dwReads,NULL);
				ch[dwReads]=0;
				CloseHandle(hFile);
				MessageBox(ch);			
		}
}

�����ٿ���MFC�е��ļ�����:  CFile
{
		д��:
		{
				CFile file("6.txt",CFile::modeCreate | CFile::modeWrite);
				file.Write("http://blog.csdn.net/zieckey",strlen("http://blog.csdn.net/zieckey"));
				file.Close();		
		}
		��ȡ:
		{
				CFile file("6.txt",CFile::modeRead);
				char *pBuf;
				DWORD dwFileLen;
				dwFileLen=file.GetLength();
				pBuf=new char[dwFileLen+1];
				pBuf[dwFileLen]=0;
				file.Read(pBuf,dwFileLen);
				file.Close();
				MessageBox(pBuf);		
		}	
}


MFC�´򿪻򱣴���ļ��Ի���: CFileDialog
{
		//����һ������Ի���1
		{
				CFileDialog fileDlg(TRUE);
				fileDlg.DoModal()��		
		}
		
		//����һ������Ի���2
		{
				CFileDialog fileDlg(TRUE);
				fileDlg.m_ofn.lpstrTitle="�ҵ��ļ��򿪶Ի���";   //�Ի���ı�����
				fileDlg.m_ofn.lpstrFilter="Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";  //������
				fileDlg.m_ofn.lpstrDefExt="txt";  //ȱʡ����չ��
				if(IDOK==fileDlg.DoModal())
				{	//�ڱ����ʱ��д��һЩ���ݵ��ı�
					CFile file(fileDlg.GetFileName(),CFile::modeCreate | CFile::modeWrite);
					file.Write("http://blog.csdn.net/zieckey",strlen("http://blog.csdn.net/zieckey"));
					file.Close();
				}					
		}


		//���ļ��Ի���
		
}

�� win.ini �ļ�д��һЩ��Ϣ��
{
		������BOOL CFileApp::InitInstance()���������������������
		::WriteProfileString("http://blog.csdn.net/zieckey","admin","zieckey");
}
��Ȼ����ͬ��  GetProfileString
{
		CString str;
		::GetProfileString("http://www.sunxin.org","admin","lisi",
			str.GetBuffer(100),100);
		AfxMessageBox(str);
}

���� CWinApp::WriteProfileString д�����Ϣ����������
{
		The entries are stored as follows: 
		In Windows NT, the value is stored to a registry key.
		In Windows 3.x, the value is stored in the WIN.INI file. 
		In Windows 95, the value is stored in a cached version of WIN.INI. 
		
		���ֱ���� BOOL CFileApp::InitInstance()������������������Ļ�������д��ע���
				WriteProfileString("http://blog.csdn.net/zieckey","admin","zieckey");
		��ע���ģ�HKEY_CURRENT_USER\Software\Local AppWizard-Generated Applications\File 
		����д��һ����Ϣ��
		������Ϊ�� BOOL CFileApp::InitInstance()����������������������ע����
				SetRegistryKey(_T("Local AppWizard-Generated Applications"));
		��Ȼ����Ը���"Local AppWizard-Generated Applications"ʹ֮�������������
}

���ǵ�Ȼ���Զ�ȡע����е�ֵ��CWinApp::GetProfileString 

��ע����̣�
{
		//дע���RegCreateKey
		void CMainFrame::OnRegWrite() 
		{
			HKEY hKey;   //����һ�����
			DWORD dwAge=30;
		
			//��ע����HKEY_LOCAL_MACHINE\SOFTWARE\ �ط�д�� http://blog.csdn.net/zieckey ������Ŀ¼��д�� admin 
			RegCreateKey(HKEY_LOCAL_MACHINE,"Software\\http://blog.csdn.net/zieckey\\admin",&hKey);
			
			// �� admin �´���������
			{
				//RegSetValue��������ȱʡ��ֵ������ֵֻ�����ַ����͵�
				RegSetValue(hKey,NULL,REG_SZ,"zieckey",strlen("zieckey"));  
				//����REG_SZ������������͵�ֵ
				RegSetValueEx(hKey,"age",0,REG_DWORD,(CONST BYTE*)&dwAge,4);
			}
			
			RegCloseKey(hKey);	
		}
		
		��ע����ȱʡֵ��RegQueryValue
		void CMainFrame::OnRegRead() 
		{
			LONG lValue;
			RegQueryValue(HKEY_LOCAL_MACHINE,"Software\\http://blog.csdn.net/zieckey\\admin",
				NULL,&lValue);  //�ȵõ����ݵĳ���(������ĩβ'\0'���������)
			char *pBuf=new char[lValue];//��̬׼ȷ�ķ����ڴ�
			RegQueryValue(HKEY_LOCAL_MACHINE,"Software\\http://blog.csdn.net/zieckey\\admin",
				pBuf,&lValue);  //�õ�����ֵ 
			MessageBox(pBuf);	//��ʾ����ֵ 
		}		
		
		��ȡע������������ֵ:
		{
				void CMainFrame::OnRegRead()
				{
					HKEY hKey;
					RegOpenKey(HKEY_LOCAL_MACHINE,"Software\\http://blog.csdn.net/zieckey\\admin",&hKey);
					DWORD dwType;
					DWORD dwValue;
					DWORD dwAge;
				
					//hKey�����ȱ���,����ǰ������� "RegOpenKey"���Ƶĺ����õ� hKey
					RegQueryValueEx(hKey,"age",0,&dwType,(LPBYTE)&dwAge,&dwValue);  
					CString str;
					str.Format("age=%d",dwAge);
					MessageBox(str);
				}		
		}
}



2006/12/2

�ڶԻ�������Ӳ˵�����CMenu��
{
	����Դ������������һ���˵���Դ��ID����Ϊ��IDM_MAIN_MENU
	Ȼ���ٶԻ���� BOOL CDialogWithMenuDlg::OnInitDialog() ���������������䣺
	{	//m_menu�ǶԻ���ĳ�Ա����
		VERIFY(m_menu.LoadMenu(IDM_MAIN_MENU));
		SetMenu(&m_menu);
		m_menu.Detach();
	}
}






2006/12/4
�ĵ�����ͼ�ķ���
�ĵ������������ݣ�����ͼ������ʾ��Щ���ݲ�����༭��

CView::GetDocument ����
���ĵ��������

CDocument::UpdateAllViews ����
֪ͨ���е���ͼ��������



2006/12/05
Lesson13
�ĵ��ʹ��л�

CArchive��ʹ��
{
	//д�����ݵ��ļ�
	{
		void CGraphicView::OnFileWrite() 
		{
			// TODO: Add your command handler code here
			CFile file("1.txt",CFile::modeCreate | CFile::modeWrite);
			CArchive ar(&file,CArchive::store);
			int i=4;
			char ch='a';
			float f=1.3f;
			CString str("http://www.sunxin.org");
			ar<<i<<ch<<f<<str;		//д������
		}	
	}
	
	//��ȡ�ļ�������
	{
		void CGraphicView::OnFileRead() 
		{
			// TODO: Add your command handler code here
			CFile file("1.txt",CFile::modeRead);
			CArchive ar(&file,CArchive::load);
			int i;
			char ch;
			float f;
			CString str;
			CString strResult;
			ar>>i>>ch>>f>>str;  //����ע��Ҫ�����汣���ʱ��˳��һ��
			strResult.Format("%d,%c,%f,%s",i,ch,f,str);
			MessageBox(strResult);
		}		
	}
}

�����ĵ��ı���
{
	//ͨ��OnNewDocument��������
	BOOL CGraphicDoc::OnNewDocument()
	{
		if (!CDocument::OnNewDocument())
			return FALSE;
	
		// TODO: add reinitialization code here
		// (SDI documents will reuse this document)
		SetTitle("http://blog.csdn.net/zieckey");
		
		return TRUE;
	}
	
	���⻹��������Դ��ͼ�е�"String Table->�ַ�����"�е� IDR_MAINFRAME �޸�
	���Կ��� IDR_MAINFRAME ��ȱʡֵ����:
		Graphic\n\nGraphi\n\n\nGraphic.Document\nGraphi Document
	����ÿ�� \n	��ʾһ���εķָ�,���Ǹ�Ϊ���µ�,������� SetTitle Ч��һ��
		Graphic\nhttp://blog.csdn.net/zieckey\nGraphi\n\n\nGraphic.Document\nGraphi Document
	����ͨ�� BOOL CGraphicApp::InitInstance() �е�
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGraphicDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CGraphicView));
	AddDocTemplate(pDocTemplate);
	��ӽ�����	
}

String Table��IDR_MAINFRAME�ַ�����Դ�и��Ӵ��ĺ���
{
	virtual BOOL GetDocString( CString& rString, enum DocStringIndex index ) const;
	
	(1)CDocTemplate::windowTitle�������ڱ������ϵ��ַ�����MDI������Ҫָ����
		����IDR_MAINFRAME�ַ���ΪĬ��ֵ��
	(2)CDocTemplate::docName��ȱʡ�ĵ������ơ����û��ָ����ȱʡ�ĵ����������ޱ��⡣
	(3)CDocTemplate::fileNewName���ĵ����͵����ơ����Ӧ�ó���֧�ֶ������͵��ĵ���
		���ַ�������ʾ��"File/New"�Ի����С����û��ָ����
		�Ͳ��ܹ���"File/New"�Ի����������ļ���
	(4)CDocTemplate::filterName���ĵ����͵�������һ�������ڴ����͵�ͨ�����������
		����ַ����������ڡ�File/Open���Ի����е��ļ������б���С�
		Ҫ��CDocTemplate::filterExtһ��ʹ�á�
	(5)CDocTemplate::filterExt���ĵ�����չ����
		���û��ָ�����Ͳ��ܹ��ڡ�File/Open���Ի����д��������ĵ���
		Ҫ��CDocTemplate::filterNameһ��ʹ�á�
	(6)CDocTemplate::regFileTypeId���������::RegisterShellFileTypes��ϵͳ��ע���ע���ļ����ͣ�
		��ֵ�������HEY_CLASSES_ROOT֮�³�Ϊ�����������Windows�ڲ�ʹ�á�
		���û��ָ���������ļ����;��޷�ע�ᡣ
	(7)CDocTemplate::regFileTypeName����Ҳ�Ǵ洢��ע����е��ļ��������ơ�
		������ʾ�ڳ��������Է���ע���ĶԻ����ڡ�
			
}

�ļ�->����(���)���ʵ��:
{
	void CGraphicDoc::Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			// TODO: add storing code here
			int i=5;
			char ch='b';
			float f=1.2f;
			CString str("http://www.sunxin.org");
			ar<<i<<ch<<f<<str;
		}
		else
		{
			// TODO: add loading code here
			int i;
			char ch;
			float f;
			CString str;
			CString strResult;
			ar>>i>>ch>>f>>str;
			strResult.Format("%d,%c,%f,%s",i,ch,f,str);
			AfxMessageBox(strResult);
		}
	}
	
	��������Ҫע��,�ڱ����ڶ��δ��ļ��Ի��򲢲������ Serialize �����������,
	��ΪMFC��Ϊ����һ����ͬ������.
}
 

����һ�����л�����:
{
	Serialization: Making a Serializable Class
	
	Five main steps are required to make a class serializable. 
	They are listed below and explained in the following sections: 
	
	Deriving your class from CObject (or from some class derived from CObject).
	
	Overriding the Serialize member function.
	
	Using the DECLARE_SERIAL macro in the class declaration.  
	
	Defining a constructor that takes no arguments.
	
	Using the IMPLEMENT_SERIAL macro in the implementation file for your class. 
}

��һ�����е���Դ:
	ֱ�Ӵ�*.rc���ļ��ͺ���.�����Ϳ��Ը���ԭ�����е���Դ��.
	
���ĵ����еõ������ָ��:
	
	
Document/View�ṹ
{
	��MFC�У��ĵ��ฺ��������ݣ��ṩ����ͼ������ݵĹ��ܡ�
	���ฺ�����ݵ���ʾ���Լ����û��ṩ�����ݵı༭���޸Ĺ��ܡ�
	
	MFC�������ṩDocument/View�ṹ����һ��Ӧ�ó�������Ҫ�ġ����ݴ�������ʾ���ĺ����տǶ���ƺ��ˣ�
	��Щ���������麯�������ǿ���������������д��Щ������
	�й��ļ���д�Ĳ�����CDocument��Serialize�����н��У�
	�й����ݺ�ͼ����ʾ�Ĳ�����CView��OnDraw�����н��С�
	���������������У�ֻ��Ҫȥ��עSerialize��OnDraw�����Ϳ����ˣ�
	������ϸ�����ǲ���Ҫȥ��ᣬ����Ϳ������õ����С�
	
	�����ǰ��¡�File/Open����Application Framework�ἤ���ļ��򿪶Ի���
	����ָ���ļ�����Ȼ���Զ�����CGraphicDoc::Serialize��ȡ�ļ���
	Application Framework�������CGraphicView::OnDraw������һ����ʾDC���������»��ƴ������ݡ�
	
	MFC�������ṩDocument/View�ṹ����ϣ�����ǽ������������ݽṹ����ƺ�������ʾ�Ĳ����ϣ�
	����Ҫ��ʱ��;��������ڶ��������֮�䡢ģ����ģ��֮���ͨ���ϡ�
	
	һ���ĵ�������ԺͶ������������������һ���������ֻ�ܺ�һ���ĵ������������

}	



2006/12/06
���ݿ�

���ݿ���ʼ���
{
	ODBC(Open Database Connectivity)���������ݿ⻥����
	ODBC���ϸ����Ͱ�ʮ���ĩ��ʮ��������ֵļ�����
	��Ϊ��д��ϵ���ݿ�Ŀͻ�����ṩ��һ��ͳһ�Ľӿڡ�
	ODBC�ṩһ����һ��API�������ڴ���ͬ���ݿ�Ŀͻ�Ӧ�ó���
	ʹ��ODBC API��Ӧ�ó���������κξ���ODBC��������Ĺ�ϵ���ݿ����ͨ�š�
	
	DAO(Data Access Object)�����ݷ��ʶ���
	DAO����һ��Microsoft Access/Jet���ݿ������COM�Զ����ӿڡ� 
	DAO����ODBC����������C/C++����Ա�ģ�
	����΢���ṩ��Visual Basic������Ա��һ�ּ򵥵����ݷ��ʷ��������ڲ���Access���ݿ⡣ 
	
	RDO(Remote Data Object)��Զ�����ݶ���
	����RDOֱ�ӵ���ODBC API(��������DAO����ͨ��Jet����)��
	���ԣ�����Ϊʹ�ù�ϵ���ݿ��Ӧ�ó����ṩ���õ����ܡ�
	
	OLE DB������������Ƕ�����ݿ⡣ 
	OLE DB�����������ODBC��������չ��
	���ȣ� OLE DB�ṩ��һ�����ݿ��̵�COM�ӿڣ�
	�ڶ��� OLE DB�ṩ��һ�������ڹ�ϵ�ͺͷǹ�ϵ������Դ�Ľӿڡ� 
	OLE DB�����������ṹ��OLE DB�ṩ����(Provider)��OLE DB�û�����(Consumer)��
	
	ADO(ActiveX Data Object)��ActiveX���ݶ�����������OLE DB֮�ϡ�
	ADO��һ��OLE DB�û�����ʹ��ADO��Ӧ�ó���Ҫ��ӵ�ʹ��OLE DB��
	ADO����OLE DB���ṩ�˶��Զ�����֧�֣�ʹ����VBScript�����Ľű�����Ҳ�ܹ�ʹ��ADO�������ݿ⡣
	
	ADO���������Ķ���
	{
		Connection����
			Connection�����ʾ�˵����ݿ�����ӣ�
			������Ӧ�ó�������ݿ�֮���ͨ�š� 
			Recordset��Command������һ��ActiveConnection���ԣ�
			��������������Connection����
		Command����
			Command�������������ظ�ִ�еĲ�ѯ��
			������Ҫ����ڴ洢���̵����е�����򷵻ز�����ֵ�Ĳ�ѯ��
		Recordset����
			Recordset����������ȡ���ݡ� 
			Recordset�����Ų�ѯ�Ľ������Щ��������ݵ���(��Ϊ��¼)����(��Ϊ�ֶ�)��ɡ�
			ÿһ�ж������Recordset��Fields�����е�һ��Field�����С�
	}
}

ʹ��ADO
{
	ado�Ķ�̬���ӿ⣺C:\Program Files\Common Files\System\ado
	�ҵ� "C:\Program Files\Common Files\System\ado\msado15.dll"
	Ȼ�������ǵĹ����е�stdafx.h�ļ�����ӣ�
	#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","rsEOF")
	������� rename("EOF","rsEOF") ����Ϊ���ǵ��ļ���βҲ�� EOF Ϊ�˱����ͻ���������¡�	

	�������debugĿ¼�����������������ļ���msado15.tlh��msado15.tli
	Ϊ�˷���鿴�����Խ�����ӵ������С�
}



2006/12/08
ODBC���ݿ����
{
	ODBCԪ�أ�����(environment),����(connection)�����(statement),
	����������ͨ����������ʵġ�
	
	�������Ǳ�����һ���������������˳����ODBCϵͳ֮��Ĺ�ϵ��Ӧ��ϵͳͨ��ֻ��һ
	�����������
	Ȼ��������Ҫ��һ���������ӡ����ӽ������������������Դ֮����ض���Ϲ�ϵ
	һ�����������������Ҫһ��SQL�����ִ�С�
	
	MFC ODBC�ࡪ������CRecordset��CDatabase
	{
		��CDatabase�Ķ������������Դ��ODBC���ӣ���CRecordset�Ķ�������˿ɹ���
		�м����û����ٴ�CDatabase���������࣬ȴ���Ǵ�CRecordset���������࣬
		�Ա�����ݿ��еı������ƥ�䡣
		
	}
}



2006/12/09
ODBC���ݿ�Ӧ��
{
	�Լ�����Access����һ�����ݿ�GSM.mdb��Ȼ����һ�������磺Athlete��
	Ȼ��ע������Դ(�������->������->����Դ(ODBC))	

	
	��VC��ͨ����������һ��CRecordset�������࣬���磺CAthleteRecordSet
	֮��ѡ������Դ��ʱ��ѡ��GSM.mdb����ѡ���Athlete�������ͺ��ˡ�
	��ע�⣺�ж�����ʱ��Ӧ�������CRecordset����������ÿ��������Ӧ��
	
	��д����ʱ����C*Doc������� CAthleteRecordSet�����ݳ�Ա m_AthleteRecordSet
	��C*View������� CAthleteRecordSet�����ݳ�Ա *m_pAthleteRecordSet;
	��C*Doc���ͷ�ļ������#include "AthleteRecordSet.h"
	��C*View��Ĺ��캯������ӳ�ʼ������:
	m_pAthleteRecordSet = &GetDocument()->m_AthleteRecordSet;
	
	��ô���ھͿ���ͨ��m_pAthleteRecordSet��ʵ�ֶ����ݿ�Ĳ�����.

	
	��ODBC���ݿ�Ӧ�ó���ʵ�ֶ����ݵ������ѯ��ֻ���ȹرռ�¼����
	Ȼ�����CRecordSet::Open()����ʱָ��SQL��ѯ��䣬���磺
	{
		if ( m_pSet->IsOpen() ) 
		{
			m_pSet->Close();
		}
		m_pSet->Open( CRecordset::dynaset, _T("select * from table1"));
	}
	
	���������� m_strFilter 
	Ȼ�����Requery�����Ϳ����ˡ�



}





//�ı䴰�ڴ�С
void CGameManageSystemView::OnSize(UINT nType, int cx, int cy) 
{
	CRecordView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rectClient;
	this->GetClientRect( &rectClient ); // ������ര������
	
	//����Ҫ�����ж�,��ΪWM_SIZE��Ϣ�ڴ��ڳ���ʱ�ͷ���,��
	//�������һЩ�ؼ����ܻ�û�г�ʼ��
	if ( m_TabCtrl ) 
	{
		m_TabCtrl.SetWindowPos( m_TabCtrl.GetWindow( GW_HWNDPREV ) , 
				rectClient.left, rectClient.top, 
				rectClient.Width(), rectClient.Height(), 
				SWP_SHOWWINDOW );
	}
		
}



2006/12/12
��CTabCtrl�еİ�ť��Ϣ�����Է��͵�MainFrm�У�
Ȼ��ͨ��GetActiveView( )��MainFrm�д����ź�

CListCtrl::InsertItem������ڵ�һ�в���һ��Item

ʹ�����ʱ�����뽫CListCtrl�����Ե� ��Styles->View������Ϊ��Report��
m_ListCtrlAthlete.InsertColumn( 0, "���" , LVCFMT_LEFT, 30, 0);



	//�õ��µ�����
	long AthleteID = 154;
	m_pSet->Close();
	m_pSet->m_strSort = "AthleteID";  //����
	m_pSet->Open();
	m_pSet->MoveLast();  //�õ����һ����¼��Ҳ�������ı��
	AthleteID = m_pSet->m_AthleteID+1;
	
	
	
	HANDLE GetClipboardData(
  UINT uFormat   // clipboard format
);


��ʼһ�μ�¼���Ĳ���
{
	m_pSetResult = new CSetClass;
	if ( m_pSetResult>IsOpen() ) 
	{
		m_pSetResult->Close();
	}
	m_pSetResult->m_strFilter.Empty();
	m_pSetResult->m_strSort.Empty();	
	m_pSetResult->Open();

	while ( !m_pSetResult->IsEOF())
	{
	
	}
	
}
�����ݿ�Ĳ���Ҫע��ĵط�:
{
	�ڽ���	this->MoveLast(); ����֮ǰһ��Ҫ�ж��Ƿ������,���¼���Ƿ�Ϊ��.
	
	���κ�ʱ���m_strFilter��m_strSort����֮�󣬶�Ҫ������գ�
		this->m_strFilter.Empty();
		this->m_strSort.Empty();
	���κ�ʱ��ִ�д�Open��Requeryǰ��Ҫ�Ƚ�m_strFilter��m_strSort����,Ȼ���ٸ�ֵ	 
}




�б���ʹ��
{
	//�Ȳ����ͷ
	m_list.InsertColumn( 0,  "Test", LVCFMT_CENTER, 80 );
	m_list.InsertColumn( 1, "���" , LVCFMT_LEFT, 80 );
	m_list.InsertColumn( 2, "����" , LVCFMT_LEFT, 80 );
	m_list.InsertColumn( 3, "�Ա�" , LVCFMT_LEFT, 80 );
	m_list.InsertColumn( 4, "�������" , LVCFMT_LEFT, 80 );
	m_list.InsertColumn( 5, "ѧ��" , LVCFMT_LEFT, 80 );

	//�ٲ��������ݡ�
	//����������֮ǰҪ����InsertItem����һ�У�
	//Ȼ�����SetItemText������������и��е�����
	
	//�����һ��
	m_list.InsertItem(  0,"Test");
	m_list.SetItemText( 0, 0, "ga" ); //������
	m_list.SetItemText( 0, 1, "ga" );
	m_list.SetItemText( 0, 2, "ga" );
	m_list.SetItemText( 0, 3, "ga" );
	m_list.SetItemText( 0, 4, "ga" );
	m_list.SetItemText( 0, 5, "ga" ); //����༶

	//����ڶ���
	m_list.InsertItem(  1,"Test");
	m_list.SetItemText( 1, 0, "sfsf" ); //������
	m_list.SetItemText( 1, 1, "sfsf" );
	m_list.SetItemText( 1, 2, "sfsf" );
	m_list.SetItemText( 1, 3, "sfsf" );
	m_list.SetItemText( 1, 4, "sfsf" );
	m_list.SetItemText( 1, 5, "sfsf" ); //����༶
	
}	



�Զ�����Ϣ:���Ĳ��ߣ�
{
		1.��Ϣ����:
		{
				//��C*APP���ͷ�ļ��ж�����Ϣֵ
				//�����WM_USER��ϵͳ����ĺ�,С��WM_USER����������ϵͳ��Ϣռ��
				//��ô�����Զ������Ϣֵ�Ϳ�����������
				#define UM_GAME_ITEM_CHANGED		WM_USER+1
		}
		2.��Ϣ������ԭ������:
		{	
				//�ڴ������Ϣ�����ͷ�ļ��������������Ϣ�ĺ���

				//{{AFX_MSG(CPageResult)
				afx_msg void OnButtonAdd();
				afx_msg void OnButtonAddComplete();
				afx_msg void OnButtonDelete();
				afx_msg void OnButtonEdit();
				afx_msg void OnButtonQuery();
				afx_msg void OnEditchangeComboGameItemName();
				afx_msg void OnSelchangeComboGameItemName();
				//}}AFX_MSG
				afx_msg void OnGameItemChanged();  //�Զ�����Ϣ������
				DECLARE_MESSAGE_MAP()
		}
		3.��Ϣӳ��:
		{		
//�ڴ������Ϣ�����ʵ���ļ���������Ϣӳ��
BEGIN_MESSAGE_MAP(CPageResult, CDialog)
	//{{AFX_MSG_MAP(CPageResult)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_ADD_COMPLETE, OnButtonAddComplete)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_CBN_EDITCHANGE(IDC_COMBO_GAME_ITEM_NAME, OnEditchangeComboGameItemName)
	ON_CBN_SELCHANGE(IDC_COMBO_GAME_ITEM_NAME, OnSelchangeComboGameItemName)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_GAME_ITEM_CHANGED,OnGameItemChanged)
END_MESSAGE_MAP()
		}
		4.��������Ϣ��������ʵ��
		void CPageResult::OnGameItemChanged()
		{
			//������������������������
		}
		
		���ھͿ����������Ϣ�ˣ������Ҫϵͳ��ʱ�������Ϣ�����Ե���
		SentMessage( UM_GAME_ITEM_CHANGED );������
		�����ϵͳ�ڴ�����������Ϣ��������Ӧ����Ϣ���͵��ã�
		PostMessage( UM_GAME_ITEM_CHANGED );
		
}




Visual C++�е�ODBC���ʵ��2006��12��02�� ������ 21:15Visual C++�е�ODBC���ʵ��
{
	Microsoft Developer StudioΪ�������׼�����ݿ��ʽ�ṩ��32λODBC����������Щ��׼���ݸ�ʽ��
	
	����:SQL Server��Access��Paradox��dBase��FoxPro��Excel��Oracle�Լ�Microsoft Text������û�
	
	ϣ��ʹ���������ݸ�ʽ,����Ҫ��װ��Ӧ��ODBC��������DBMS�� 
	
	���� �û�ʹ���Լ���DBMS���ݿ�����������µ����ݿ�ģʽ��,�Ϳ���ʹ��ODBC����¼����Դ������
	
	����Ӧ�ó�����˵,ֻҪ��װ����������,����ע��ܶ಻ͬ�����ݿ⡣��¼���ݿ�ľ�������μ��й�
	
	ODBC������������ 
	
	���� һ��MFC�ṩ��ODBC���ݿ��� 
	
	���� Visual C++��MFC����ⶨ���˼������ݿ��ࡣ������ODBC���ʱ,����Ҫʹ�õ� CDatabase(����
	
	����)��CRecordSet(��¼����)��CRecordView(���Ӽ�¼����)�� 
	
	���� CDatabase������ṩ�˶�����Դ������,ͨ�������Զ�����Դ���в����� 
	
	���� CRecordSet������ṩ�˴�����Դ����ȡ���ļ�¼����CRecordSet����ͨ������������ʽ:��̬��
	
	��(dynasets)�Ϳ��ռ�(snapshots)����̬�м����������û������ĸ��ı���ͬ��,���ռ��������ݵ�һ
	
	����̬��ͼ��ÿ����ʽ�ڼ�¼������ʱ���ṩһ���¼,����ͬ����,����һ����̬�м��������һ��
	
	��¼ʱ,�������û���Ӧ�ó����е�������¼���Ըü�¼�����ĸ��Ļ���Ӧ����ʾ������ 
	
	���� CRecordView��������Կؼ�����ʽ��ʾ���ݿ��¼,�����ͼ��ֱ������һ��CRecordSet����ı�
	
	��ͼ�� 
	
	���� ����Ӧ��ODBC��� 
	
	���� Ӧ��Visual C������AppWizard�����Զ�����һ��ODBCӦ�ó�����,������:��File�˵���Newѡ
	
	��,ѡȡProjects,���빤����,ѡ��MFC AppWizard (exe),Ȼ��AppWizard����ʾ���в����� 
	
	���� ��AppWizardѯ���Ƿ�������ݿ�֧��ʱ,������д���ݿ�,��ôѡ��Database view with file 
	
	support;�����������ݿ����Ϣ������д�������ĸı�,��ôѡ��Database view without file 
	
	support�� 
	
	���� ѡ�����ݿ�֧��֮��,Database Source ��ť�ᱻ����,ѡ����ȥ����Data Options�Ի�����
	
	Database Options�Ի����л���ʾ������ODBCע������ݿ���Դ,ѡ����Ҫ���������ݿ�,��:Super_ES,
	
	����OK�����Select Database Tables�Ի���,�����о���ѡ�е����ݿ������ȫ����;ѡ��Ҫ�����ı�
	
	��,����OK����ѡ�������ݿ�����ݱ�֮��,�Ϳ��԰��չ�����������AppWizard������ 
	
	���� �ر���Ҫָ������:�����ɵ�Ӧ�ó�����View��(��:CSuper_ESView)��,����һ��ָ��
	
	CSuper_ESSet�����ָ��m_pSet,��ָ����AppWizard����,Ŀ�������ӱ��ͼ�¼��֮�佨����ϵ,ʹ��
	
	��¼���еĲ�ѯ����ܹ������׵����ӱ�����ʾ������ 
	
	���� Ҫʹ����������Դ������ϵ,����CDateBase::OpenEx()��CDatabase::Open()���������г�ʼ����
	
	���ݿ���������ʹ���������¼������֮ǰ��ʼ���� 
	
	����ʵ�� 
	
	���� 1.��ѯ��¼ 
	
	���� ��ѯ��¼ʹ��CRecordSet::Open()��CRecordSet::Requery()��Ա��������ʹ��CRecordSet�����
	
	֮ǰ,����ʹ��CRecordSet::Open()�����������Ч�ļ�¼����һ���Ѿ�ʹ�ù�CRecordSet::Open()����
	
	,�ٴβ�ѯʱ�Ϳ���Ӧ��CRecordSet::Requery()������ 
	
	���� �ڵ���CRecordSet::Open()����ʱ,�����һ���Ѿ��򿪵�CDatabase����ָ�봫��CRecordSet���
	
	���m_pDatabase��Ա����,��ʹ�ø����ݿ������ODBC����;�������m_pDatabaseΪ��ָ��,���½�һ
	
	��CDatabase�����,��ʹ����ȱʡ������Դ����,Ȼ�����CRecordSet�����ĳ�ʼ����ȱʡ����Դ��
	
	GetDefaultConnect()������á�Ҳ�����ṩ����Ҫ��SQL���,������������CRecordSet::Open()����,
	
	����:Super_ESSet.Open(AFX_DATABASE_USE_DEFAULT,strSQL); 
	
	���� ���û��ָ������,������ʹ��ȱʡ��SQL���,������GetDefaultSQL()������ָ����SQL������
	
	����: 
	
	���� CString CSuper_ESSet::GetDefaultSQL() 
	���� {return _T(��[BsicData],[MinSize]��);} 
	
	���� ����GetDefaultSQL()�������صı���,��Ӧ��ȱʡ������SELECT���,��: 
	
	���� SELECT *FROM BasicData,MainSize 
	
	���� �ڲ�ѯ������,Ҳ��������CRecordSet�ĳ�Ա����m_strFilter��m_strSort��ִ��������ѯ�ͽ��
	
	����m_strFilterΪ�����ַ���,�����SQL�����WHERE���������;m_strSortΪ�����ַ���,�����
	
	SQL�����ORDER BY����ַ�������: 
	
	���� Super_ESSet.m_strFilter=��TYPE=���綯��'��; 
	���� Super_ESSet.m_strSort=��VOLTAGE��; 
	���� Super_ESSet.Requery(); 
	
	���� ��Ӧ��SQL���Ϊ: 
	
	���� SELECT *FROM BasicData,MainSize 
	���� WHERE TYPE=���綯��' 
	���� ORDER BY VOLTAGE 
	
	���� ����ֱ�Ӹ�ֵ��m_strFilter����,������ʹ�ò����������ò��������Ը�ֱ�ۡ���������������
	
	��ѯ����ʹ�ò������Ĳ�������: 
	
	���� S�����α���: 
	
	 
	
	���� CString p1; 
	���� float p2; 
	
	���� S�ڹ��캯���г�ʼ���α���: 
	
	���� p1=_T(���); 
	���� p2=0.0f; 
	���� m_nParams=2; 
	
	���� S���α������Ӧ�а�: 
	
	���� pFX��>SetFieldType(CFieldExchange::param) 
	
	���� RFX_Text(pFX,_T(��P1��),p1); 
	���� RFX_Single(pFX,_T(��P2��),p2); 
	
	���� ������ϲ����Ϳ������òα�������������ѯ: 
	
	���� m_pSet��>m_strFilter=��TYPE=? AND VOLTAGE=?��;m_pSet��>p1=��綯����; 
	���� m_pSet��>p2=60.0; 
	���� m_pSet��>Requery(); 
	
	���� �α�����ֵ���󶨵�˳���滻��ѯ�ִ��еġ�?��ͨ����� 
	
	���� �����ѯ�Ľ���Ƕ�����¼,������CRecordSet��ĺ���Move()��MoveNext()��MovePrev()��
	
	MoveFirst()��MoveLast()���ƶ���ꡣ 
	
	���� 2.���Ӽ�¼ 
	
	���� ���Ӽ�¼ʹ��AddNew()����,Ҫ�����ݿ���������������ӵķ�ʽ��: 
	
	���� m_pSet��>AddNew(); //�ڱ��ĩβ�����¼�¼ 
	���� m_pSet��>SetFieldNull(��(m_pSet��>m_type), FALSE); 
	���� m_pSet��>m_type=��綯����; 
	���� ���� 
	���� //�����µ��ֶ�ֵ 
	���� m_pSet��>Update(); 
	���� //���¼�¼�������ݿ� 
	���� m_pSet��>Requery(); 
	���� //�ؽ���¼�� 
	
	���� 3.ɾ����¼ 
	
	���� ����ֱ��ʹ��Delete()������ɾ����¼,�����ڵ���Delete()����֮�������Update()����: 
	
	���� m_pSet��>Delete(); 
	���� if (!m_pSet��>IsEOF()) 
	���� m_pSet��>MoveNext(); 
	���� else 
	���� m_pSet��>MoveLast(); 
	
	���� 4.�޸ļ�¼ 
	
	���� �޸ļ�¼ʹ��Edit()����: 
	
	���� m_pSet��>Edit(); 
	���� //�޸ĵ�ǰ��¼ 
	���� m_pSet��>m_type=�巢�����; 
	���� //�޸ĵ�ǰ��¼�ֶ�ֵ 
	���� ���� 
	���� m_pSet��>Update(); //���޸Ľ���������ݿ� 
	���� m_pSet��>Requery(); 
	
	���� 5.�������� 
	
	���� ����û�ѡ�������ӻ����޸ļ�¼��ϣ��������ǰ����,�����ڵ���Update()����֮ǰ����: 
	
	���� CRecordSet::Move(AFX_MOVE_REFRESH)���������ӻ��޸�ģʽ,���ָ������ӻ��޸�ģʽ֮ǰ�ĵ�
	
	ǰ��¼������,����AFX_MOVE_REFRESH��ֵΪ�㡣 
	
	���� 6.���ݿ����ӵĸ��� 
	
	���� ��CRecordSet���ж�����һ����Ա����m_pDatabase: 
	
	���� CDatabase* m_pDatabase; 
	
	���� ����ָ��������ݿ����ָ�롣�����CRecordSet��������Open()����֮ǰ,��һ���Ѿ��򿪵�
	
	CDatabase�����ָ�봫��m_pDatabase,���ܹ�����ͬ��CDatabase�������: 
	
	���� CDatabase m_db; 
	���� CRecordSet m_set1,m_set2; 
	���� m_db.Open(_T(��Super_ES��)); //����ODBC���� 
	���� m_set1.m_pDatabase=��m_db; 
	���� //m_set1����m_db���� 
	���� m_set2.m_pDatabse=��m_db; 
	���� // m_set2����m_db���� 
	
	���� 7.SQL����ֱ��ִ�� 
	
	���� ��Ȼ���ǿ���ͨ��CRecordSet����ɴ�����Ĳ�ѯ����,������CRecordSet::Open()������Ҳ����
	
	�ṩSQL���,������ʱ�����ǻ���ϣ������һЩ��������,���罨���±�ɾ���������µ��ֶε�,��
	
	ʱ����Ҫʹ��CDatabase��ֱ��ִ��SQL���Ļ��ơ�ͨ������CDatabase::ExecuteSQL()���������SQL
	
	����ֱ��ִ��: 
	
	���� BOOL CDB::ExecuteSQLAndReportFailure(const CString�� strSQL) 
	���� {TRY 
	���� {m_pdb��>ExecuteSQL(strSQL); 
	���� //ֱ��ִ��SQL���} 
	���� CATCH (CDBException,e) 
	���� {CString strMsg; 
	���� strMsg.LoadString(IDS_EXECUTE_SQL_FAILED); 
	���� strMsg��=strSQL; 
	���� return FALSE;} 
	���� END_CATCH 
	���� return TRUE;} 
	
	���� Ӧ��ָ������,���ڲ�ͬ��DBMS�ṩ�����ݲ�����䲻����ͬ,ֱ��ִ��SQL�����ܻ��ƻ������
	
	DBMS�޹���,�����Ӧ����Ӧ�����ô�������� 
	
	���� 8.��̬���ӱ� 
	
	���� ��Ķ�̬���ӿ��������ڵ���CRecordSet::Open()����ʱָ��SQL�����ʵ�֡�ͬһ����¼������
	
	ֻ�ܷ��ʾ�����ͬ�ṹ�ı�,�����ѯ������޷���������Ӧ�� 
	
	���� void CDB::ChangeTable() 
	���� { 
	���� if (m_pSet��>IsOpen()) m_pSet��>Close(); 
	���� switch (m_id) 
	���� { 
	���� case 0: 
	���� m_pSet��>Open(AFX_DB_USE_DEFAULT_TYPE, 
	���� ��SELECT �� FROM SLOT0��); 
	���� //���ӱ�SLOT0 
	���� m_id=1; 
	���� break; 
	���� case 1: 
	���� m_pSet��>Open(AFX_DB_USE_DEFAULT_TYPE, 
	���� ��SELECT * FROM SLOT1��); //���ӱ�SLOT1 
	���� m_id=0; 
	���� break; }} 
	
	���� 9.��̬�������ݿ� 
	
	���� ����ͨ������CRecordSet��������m_pDatabase�����Ӳ�ͬ���ݿ��CDatabase����ָ��,�Ӷ�ʵ
	
	�ֶ�̬�������ݿ⡣ 
	
	���� void CDB::ChangeConnect() 
	���� {CDatabase* pdb=m_pSet��>m_pDatabase; 
	���� pdb��>Close(); 
	���� switch (m_id) 
	���� { 
	���� case 0: 
	���� if (!pdb��>Open(_T(��Super_ES��))) 
	���� //��������ԴSuper_ES 
	���� { 
	���� AfxMessageBox(������ԴSuper_ES��ʧ�ܡ�,��������Ӧ��ODBC���ӡ�, 
	
	MB_OK|MB_ICONWARNING); 
	���� exit(0); 
	���� } 
	���� m_id=1; 
	���� break; 
	���� case 1: 
	���� if (!pdb��>Open(_T(��Motor��))) 
	���� //��������ԴMotor 
	���� { 
	���� AfxMessageBox(������ԴMotor��ʧ�ܡ�,��������Ӧ��ODBC���ӡ�, MB_OK|MB_ICONWARNING); 
	���� exit(0); 
	���� } 
	���� m_id=0; 
	���� break; }} 
	
	���� �ܽ᣺Visual C�����е�ODBC�����԰�������Ա��ɾ�����������ݿ����������ODBC����ʹ��
	
	����Ա�Ӿ����DBMS�н��ѳ���,�Ӷ����Լ�����������Ĺ�����,���̿�������,�����Ч�ʺ�����Ŀ�
	
	���ԡ�
} 
