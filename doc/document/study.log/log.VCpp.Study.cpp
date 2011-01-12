VC++学习日志



作者：zieckey(zieckey@yahoo.com.cn)
All Rights Reserved!


2006/11/22

MFC的消息映射有两个方式：
1）虚函数，这种方法会浪费虚表的内存空间
2）宏映射

OnDraw 是 CView 类的一个虚函数，每次窗口需要重绘时，应用程序框架都会调用它。
InvalidataRect 函数会使矩形区域无效，那么这之后就好调用 OnDraw 函数重绘窗口。

增加消息响应：
在“工作空间窗口”中选择“ClassView”，在某一个类上右键点击就可以看到“Add Windows Message Handle...”选项，打开就可以增加消息响应了。
通过这种方法增加的消息响应函数会在几个地方留下痕迹，
1）在头文件中 DECLARE_MESSAGE_MAP() 之前加入了原型声明
2）在源文件中，在  “BEGIN_MESSAGE_MAP(CDrawView, CView)”和“END_MESSAGE_MAP()”之间加入了宏定义
3）在源文件中加入了函数的具体代码实现
	

所以在删除时也应该通过这种右键点击的方式选择“delete”进行删除。

直线绘图：
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
	//方法一
	HDC hdc;
	hdc = ::GetDC(m_hWnd); //调用全局函数
	MoveToEx(hdc,m_ptOrigin.x,m_ptOrigin.y,0);
	LineTo(hdc,point.x,point.y);
	::ReleaseDC(m_hWnd,hdc);
	*/
	

	/*
	//方法二
	CDC *pDC = GetDC();
	pDC->MoveTo(m_ptOrigin);
	pDC->LineTo(point);
	ReleaseDC(pDC);
	*/


	/*
	//方法三
	CClientDC dc(this) ;   //CClientDC对象构造的时候就调用了GetDC，析构的时候调用ReleaseDC 
	CClientDC dc(GetParent());
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);
	*/


	/*
	//方法四
	//CWindowDC dc(this) ;  //CWindowDC可以访问客户区和非客户区
	//CWindowDC dc(GetParent()) ;
	CWindowDC dc(GetDesktopWindow()) ;
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);
	*/


	/*
	//改变画笔颜色和画线类型
	CPen pen( PS_DASHDOT   , 1 , RGB(255,128,128) );
	CClientDC dc(this) ;
	CPen *pOldPen = dc.SelectObject( &pen );   //选择新的画笔并保存原来的画笔
	dc.MoveTo(point);
	dc.LineTo(m_ptOrigin);
	dc.SelectObject( pOldPen );     //还原原来的画笔
	*/

	
	/*
	//用画刷填充两个点所决定的矩形区
	CBrush brush( RGB(255,128,128) );//画刷由颜色指定
	CClientDC dc(this) ;
	dc.FillRect(CRect(m_ptOrigin,point),&brush); //用指定的画刷填充一个矩形区
	*/

	
	/*
	//用画刷填充两个点所决定的矩形区
	CBitmap bitmap;   //创建一个位图
	bitmap.LoadBitmap(IDB_BITMAP_zhong);
	CBrush brush(&bitmap); //画刷由位图指定
	CClientDC dc(this) ;
	dc.FillRect(CRect(m_ptOrigin,point),&brush); //用指定的画刷填充一个矩形区
	*/

	/*
	//绘制一块空白的矩形
	CClientDC dc(this) ;
	dc.Rectangle(CRect(m_ptOrigin,point)); //用缺省的画刷填充一个矩形区
	*/


	/*
	//绘制一块透明的矩形
	CBrush *pBrush = CBrush::FromHandle( (HBRUSH)GetStockObject( HOLLOW_BRUSH ) );
	CClientDC dc(this) ;
	CBrush *pOldBrush = dc.SelectObject(pBrush); //替换缺省的画刷
	dc.Rectangle(CRect(m_ptOrigin,point)); //用指定的画刷填充一个矩形区
	dc.SelectObject(pOldBrush);
	*/

	CView::OnLButtonUp(nFlags, point);
}




连续线绘图：

void CDrawView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	/*
	//画连续的线条
	if ( m_bDraw )
	{
		CClientDC dc(this) ;
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin = point ;
	}
	*/
	
	
	/*
	//改变画笔的颜色
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
	//画扇型
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
	//画带边线的扇型
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


	//看看绘图的模式设置方法
	if ( m_bDraw )
	{
		CClientDC dc(this) ;
		dc.SetROP2(R2_BLACK);  //绘图的模式设置,始终绘制黑色图形
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
绘图

创建一幅位图：
1）菜单兰－>插入->资源
然后就可以在打开的对话框中操作了。




静态数据成员：
下面看一个例子：
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
这样编译是不会有任何错误的。
下面这样看
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
这样编译会处错，错误信息：illegal call of non-static member function，为什么？
因为在没有实例化一个类的具体对象时，类是没有被分配内存空间的。
好的再看看下面的例子:
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
这时编译就不会有错误，因为在类的定义时，它静态数据和成员函数就有了它的内存区，它不属于类的任何一个具体对象。
好的再看看下面的例子:
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
编译出错：
illegal reference to data member 'Point::x' in a static member function
illegal reference to data member 'Point::y' in a static member function
在一个静态成员函数里错误的引用了数据成员，
还是那个问题，静态成员（函数），不属于任何一个具体的对象，那么在类的具体对象声明之前就已经有了内存区，
而现在非静态数据成员还没有分配内存空间，那么这里调用就错误了，就好像没有声明一个变量却提前使用它一样。
也就是说在静态成员函数中不能引用非静态的成员变量。
好的再看看下面的例子:
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
好的，这样就不会有任何错误。这最终还是一个内存模型的问题，
任何变量在内存中有了自己的空间后，在其他地方才能被调用，否则就会出错。
好的再看看下面的例子:
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
编译：
Linking...
test.obj : error LNK2001: unresolved external symbol "private: static int Point::y" (?y@Point@@0HA)
test.obj : error LNK2001: unresolved external symbol "private: static int Point::x" (?x@Point@@0HA)
Debug/Test.exe : fatal error LNK1120: 2 unresolved externals
执行 link.exe 时出错.
可以看到编译没有错误，连接错误，这又是为什么呢？
这是因为静态的成员变量要进行初始化，可以这样：
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
在静态成员数据变量初始化之后就不会出现编译错误了。
再看看下面的代码：
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
编译没有错误，为什么？
即使他们没有初始化，因为我们没有访问x，y，所以编译不会出错。










字处理程序
创建一个插入符：CreateSolidCaret( 20, 100 )，然后调用ShowCaret

int CTextView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	/*
	CreateSolidCaret( 1, 20 ); //新建一个插入符
	ShowCaret( );
	*/


	/*
	//得到系统的字符宽度和高度
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CreateSolidCaret( tm.tmAveCharWidth/8 , tm.tmHeight ); //新建一个插入符
	ShowCaret( );
	*/

	
	//创建一个图形的插入符
	m_Bitmap.LoadBitmap(IDB_BITMAP_CARET);
	CreateCaret(&m_Bitmap);
	ShowCaret( );


	return 0;
}


CString str ;
str.LoadString(IDS_STRING_HELLO); //可以用字符资源号来赋值




2006/11/25
CDC::DrawText  
virtual int DrawText( LPCTSTR lpszString, int nCount, LPRECT lpRect, UINT nFormat );
int DrawText( const CString& str, LPRECT lpRect, UINT nFormat );
可以象卡KO那样平滑的输出文本


void CTextView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	

	CClientDC dc(this);

	TEXTMETRIC tm;
	dc.GetTextMetrics( &tm ); //得到文本的宽高信息

	CRect rect;
	rect.top = 200;
	rect.left = 0;
	rect.bottom = rect.top + tm.tmHeight;
	rect.right = m_nWidth;

	dc.SetTextColor(RGB(255,128,128));  //设置颜色
	CString str;
	str.LoadString(IDS_STRING_HELLO);   

	dc.DrawText(str,rect,DT_LEFT);		//平滑的输出文本
	m_nWidth += 5;

	rect.top = 100;
	rect.bottom = rect.top + tm.tmHeight;
	dc.DrawText(str,rect,DT_RIGHT);		//平滑的输出文本,右向


	CSize cs = dc.GetTextExtent(str);   //得到文本的宽度
	if ( m_nWidth > cs.cx )				
	{
		m_nWidth = 0;					//从头输出	
		dc.SetTextColor(RGB(0,128,128));//输出完后改变文字颜色   
		dc.TextOut( 0, 200, str);
	}




	CView::OnTimer(nIDEvent);
}









2006/11/26
添加菜单响应。Lesson7
让菜单的属性编辑框常驻顶层，可以单击左上角的小图钉样按钮就行了。
可以通过取消“Pop－Up”选项来对菜单的响应和编辑一个资源标识，
对菜单单击的响应优先级顺序：View->Doc->MainFrame->App


标准消息
      除WM_COMMAND之外，所有以WM_开头的消息。
      从CWnd派生的类，都可以接收到这类消息。
命令消息
      来自菜单、加速键或工具栏按钮的消息。这类消息都以WM_COMMAND呈现。在MFC中，通过菜单项的标识（ID）来区分不同的命令消息；在SDK中，通过消息的wParam参数识别。
	从CCmdTarget派生的类，都可以接收到这类消息。
通告消息
      由控件产生的消息，例如，按钮的单击，列表框的选择等均产生此类消息，为的是向其父窗口（通常是对话框）通知事件的发生。这类消息也是以WM_COMMAND形式呈现。
	从CCmdTarget派生的类，都可以接收到这类消息。


标记一个菜单
GetMenu()->GetSubMenu(0)->CheckMenuItem( 0 , MF_BYPOSITION | MF_CHECKED );
分隔栏也占索引号
图形化标记菜单
m_bitmap.LoadBitmap(IDB_BITMAP1);  //该位图应该为13*13像素大小
GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps( 0, MF_BYPOSITION , &m_bitmap, &m_bitmap );

得到系统菜单中位图的大小
CString str;
str.Format("x=%d,y=%d",GetSystemMetrics(SM_CXMENUCHECK),GetSystemMetrics(SM_CYMENUCHECK) );
MessageBox(str);

让一个菜单项失效：
两步：
m_bAutoMenuEnable = FALSE ;
GetMenu()->GetSubMenu(0)->EnableMenuItem( 1, MF_BYPOSITION | MF_DISABLED | MF_GRAYED ); 
但是 m_bAutoMenuEnable = FALSE  这样设置之后，其他的地方都没有菜单更新功能了。

设置菜单
SetMenu(NULL);
CMenu menu;
menu.LoadMenu(IDR_MAINFRAME);
SetMenu(&menu);
menu.Detach();




命令更新：
菜单项状态的维护是依赖于CN_UPDATE_COMMAND_UI消息，谁捕获CN_UPDATE_COMMAND_UI消息，
MFC就在其中创建一个CCmdUI对象。
我们可以通过手工或利用ClassWizard在消息映射中添加ON_UPDATE_COMMAND_UI宏来
捕获CN_UPDATE_COMMAND_UI消息。
在后台所做的工作是：操作系统发出WM_INITMENUPOPUP消息，然后由MFC的基类如CFrameWnd接管。
它创建一个CCmdUI对象，并与第一个菜单项相关联，调用对象的一个成员函数DoUpdate()。
这个函数发出CN_UPDATE_COMMAND_UI消息，这条消息带有指向CCmdUI对象的指针。
同一个CCmdUI对象就设置为与第二个菜单项相关联，这样顺序进行，直到完成所有菜单项。
更新命令UI处理程序仅应用于弹出式菜单项上的项目，不能应用于永久显示的顶级菜单项目。





更新一个命令
void CMainFrame::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (ID_FILE_NEW==pCmdUI->m_nID)  //这里不加判断也行，因为这个就在该消息处理里。当然在其他地方就要加上判断了
	{
		pCmdUI->Enable(FALSE);
	}	
}


右键弹出菜单
选择：project->Add to project->conponent and controls..
这里是VC提供给我们的一些组建和控件，我们选择 Visual C++ Components ，可以看到 Pop-up Menu ，
选择插入到 View 类中。这样我们就通过VC自动帮我们生成了一个弹出菜单
我们在回过头来看看现在程序中多了些什么：
1. 资源的menu中多了这个弹出菜单
2. View类多了个函数：void OnContextMenu(CWnd*, CPoint point)
在函数里，最后会调用 TrackPopupMenu 函数去最终响应鼠标右键弹出菜单。
了解了这个之后我们就可以自己手动生产右键弹出菜单了。
自己动手：

void CMenuLesson6View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CMenu menu;
	VERIFY(menu.LoadMenu(CG_IDR_POPUP_MENU_LESSON6_VIEW));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	ClientToScreen(&point);    //客户区坐标转换到屏幕坐标
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			this);

	CView::OnRButtonDown(nFlags, point);
}



动态的添加一个弹出菜单
	CMenu menu;
	ASSERT(menu.CreatePopupMenu( ));
	GetMenu()->AppendMenu(MF_POPUP,(UINT)menu.m_hMenu,"Zieckey");
	menu.AppendMenu(MF_STRING,111,"Hello");
	menu.AppendMenu(MF_STRING,110,"welcome");
	menu.Detach();
那么添加对这些动态菜单的命令响应呢？
我们可以手动的添加。先在 Resource.h 文件中添加一个与命令相关的ID，例如下：
#define       IDM_HELLO				    111
添加消息原型，在 MainFrm.h 中相应位置添加（具体就是在 DECLARE_MESSAGE_MAP() 之前添加）：
afx_msg void OnHello();
之后添加消息映射，在 MainFrm.cpp 中相应位置添加（具体就是在 //}}AFX_MSG_MAP 之前添加）：
ON_COMMAND(IDM_HELLO,OnHello)
最后就是实现函数：
void CMainFrame::OnHello() 
{
	MessageBox("Hello");
}
好了我们自己手动的添加了菜单的命令响应。






2006/11/27
对话框

菜单栏->工具->定制(C)...这样打开一个对话框可以设置工具箱，包括"控件"等

模态对话框：
	CTestDlg dlg;
	dlg.DoModal();

创建非模态对话框，不能象上面的那样创建一个局部变量，
而要创建一个成员变量或者创建一个堆内的指针类型变量，并且要调用ShowWindow方法显示出来，例如：
	CTestDlg *dlg = new CTestDlg();
	dlg->Create(IDD_DIALOG1,this);
	dlg->ShowWindow(SW_SHOW);
但是这种方法在程序执行过去之后，我们就无法释放掉该对象的内存，所以我还是将之定义为成员变量为好。
对于非模态对话框，我们必须重载OnOK方法去调用DestroyWindow来释放该对话框的内存，否则就由父类调用EndDialog来隐藏这个对话，
但是这样并没有销毁该对话，即没有释放内存。

任何一个由CWnd类派生的类都保存了一个 m_hWnd 的句柄，
当该派生类和具体的对象相关联的时候，m_hWnd 就有值了。
下面是两种方式动态创建对象：
   	//方法一
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
   	//方法二
	if ( !m_btn.m_hWnd )
	{
		m_btn.Create( "Zieckey Study VC", BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD ,
				CRect(0,0,100,100), this, 100) ;
	}
	else	
	{
		m_btn.DestroyWindow();
	}


对于静态的文本框默认是不能介绍鼠标等的点击信息，所以必须先将它的“通知(Notify)”选项打开，
点击该文本框的属性->样式->通知

int atoi( const char *string ); 字符串到数字
char *itoa( int value, char *string, int radix );数字到字符串

得到一个窗口中控件的文本和设置其文本
	GetDlgItem(IDC_EDIT1)->GetWindowText(ch1,10);
	GetDlgItem(IDC_EDIT2)->GetWindowText(ch2,10);
	GetDlgItem(IDC_EDIT3)->SetWindowText(ch3);
或者直接调用：
int GetDlgItemText( int nID, LPTSTR lpStr, int nMaxCount ) const;
int GetDlgItemText( int nID, CString& rString ) const;
void SetDlgItemText( int nID, LPCTSTR lpszString );
直接将文本转换为数字：
UINT GetDlgItemInt( int nID, BOOL* lpTrans = NULL, BOOL bSigned = TRUE ) const;
void SetDlgItemInt( int nID, UINT nValue, BOOL bSigned = TRUE );


将控件与成员变量关联：
Claas Wizard->Member Variables,这里 Category 选择value就是数字等,
如果选择control则是指向控件本身的变量，这样就使控件方便的与具体的变量关联起来了。
不过在获取数字之前要调用 UpdateData 函数，使之生效。UpdateData可以设置和校验数据.
	UpdateData( TRUE );	//获取编辑控件的数字值
	m_num3 = m_num1 + m_num2;
	UpdateData( FALSE );	//校验编辑控件关联的变量，即输入文本
这里校验是校验你设置的类型和变量的取值范围(如果你设置了的话)
	int num1,num2,num3;
	char ch1[10],ch2[10],ch3[10];
	m_edit1.GetWindowText(ch1,10);
	m_edit2.GetWindowText(ch2,10);
	num1=atoi(ch1);
	num2=atoi(ch2);
	num3=num1+num2;
	itoa(num3,ch3,10);
	m_edit3.SetWindowText(ch3);


我们还可以通过发送消息来完成访问控件的目的	
	//::SendMessage(GetDlgItem(IDC_EDIT1)->m_hWnd,WM_GETTEXT,10,(LPARAM)ch1);//得到控件
	//::SendMessage(m_edit1.m_hWnd,WM_GETTEXT,10,(LPARAM)ch1); //关联的控件变量
	//GetDlgItem(IDC_EDIT1)->SendMessage(WM_GETTEXT,10,(LPARAM)ch1);//
	m_edit1.SendMessage(WM_GETTEXT,10,(LPARAM)ch1);
	m_edit2.SendMessage(WM_GETTEXT,10,(LPARAM)ch2);
	num1=atoi(ch1);
	num2=atoi(ch2);
	num3=num1+num2;
	itoa(num3,ch3,10);
	m_edit3.SendMessage(WM_SETTEXT,0,(LPARAM)ch3);
或者,直接用SendDlgItemMessage函数来完成
	int num1,num2,num3;
	char ch1[10],ch2[10],ch3[10];
	SendDlgItemMessage(IDC_EDIT1,WM_GETTEXT,10,(LPARAM)ch1);
	SendDlgItemMessage(IDC_EDIT2,WM_GETTEXT,10,(LPARAM)ch2);
	num1=atoi(ch1);
	num2=atoi(ch2);
	num3=num1+num2;
	itoa(num3,ch3,10);
	SendDlgItemMessage(IDC_EDIT3,WM_SETTEXT,0,(LPARAM)ch3);
另外可以通过 EM_SETSEL 和 EM_GETSEL来设置复选的值
	SendDlgItemMessage(IDC_EDIT3,EM_SETSEL,1,3);
	m_edit3.SetFocus();   //设置焦点所在
SendDlgItemMessage(IDC_EDIT3,EM_SETSEL,0,-1); //0,-1 选择所有的内容



对话框控件访问七种方式总结:
GetDlgItem()->Get(Set)WindowText()
GetDlgItemText()/SetDlgItemText()
GetDlgItemInt()/SetDlgItemInt()
将控件和整型变量相关联
将控件和控件变量相关联
SendMessage()
SendDlgItemMessage()




对话框的收缩与扩展
静态变量初始化为0
设置窗口的Z-Order和窗口大小:SetWindowPos
	CString str;
	if(GetDlgItemText(IDC_BUTTON_CHANGE,str),str=="收缩<<")
	{
		SetDlgItemText(IDC_BUTTON_CHANGE,"扩展>>");
	}
	else
	{
		SetDlgItemText(IDC_BUTTON_CHANGE,"收缩<<");
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
		
	
	if(str=="收缩<<")
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
        窗口的Z次序表明了重叠窗口堆中窗口的位置，这个窗口堆是按一个假想的轴定位的，这个轴就是从屏幕向外伸展的Z轴。Z次序最上面的窗口覆盖所有其它的窗口，Z次序最底层的窗口被所有其它的窗口覆盖。应用程序设置窗口在Z次序中的位置是通过把它放在一个给定窗口的后面，或是放在窗口堆的顶部或底部。
        Windows系统管理三个独立的Z次序——一个用于顶层窗口、一个用于兄弟窗口，还有一个是用于最顶层窗口。最顶层窗口覆盖所有其它非最顶层窗口，而不管它是不是活动窗口或是前台窗口。应用程序通过设置WS_EX_TOPMOST风格创建最顶层窗口。
        一般情况下，Windows系统把刚刚创建的窗口放在Z次序的顶部，用户可通过激活另外一个窗口来改变Z次序；Windows系统总是把活动的窗口放在Z次序的顶部，应用程序可用函数BringWindowToTop把一个窗口放置到Z次序的顶部。函数SetWindowPos和DeferWindowPos用来重排Z次序。
兄弟窗口
     共享同一个父窗口的多个子窗口叫兄弟窗口。
活动窗口
              活动窗口是应用程序的顶层窗口，也就是当前使用的窗口。只有一个顶层窗口可以是活动窗口，如果用户使用的是一个子窗口，Windows系统就激活与这个子窗口相应的顶层窗口。
            任何时候系统中只能有一个顶层窗口是活动的。用户通过单击窗口（或其中的一个子窗口）、使用ALT+TAB或ALT+ESC组合键来激活一个顶层窗口，应用程序则调用函数SetActiveWindow来激活一个顶层窗口。
前台窗口和后台窗口
            在Windows系统中，每一个进程可运行多个线程，每个线程都能创建窗口。创建正在使用窗口的线程称之为前台线程，这个窗口就称之为前台窗口。所有其它的线程都是后台线程，由后台线程所创建的窗口叫后台窗口。
            用户通过单击一个窗口、使用ALT+TAB或ALT+ESC组合键来设置前台窗口，应用程序则用函数SetForegroundWindow设置前台窗口。如果新的前台窗口是一个顶层窗口，那么Windows系统就激活它，换句话说，Windows系统激活相应的顶层窗口。



设置缺省按钮.一般情况下缺省按钮始OK按钮
我们可以通过重载OnOK函数来改变缺省按钮和Enter键击后的焦点.方法有二:
1)生成一个类
2)改变窗口过程函数
BOOL CTestDlg::OnInitDialog() 

通过默认缺省按钮始OK按钮的接收信号,不过要取消 CDialog::OnOK();
例如:
void CTestDlg::OnOK() 
{
	// TODO: Add extra validation here
	//GetDlgItem(IDC_EDIT1)->GetNextWindow()->SetFocus();
	//GetFocus()->GetNextWindow()->SetFocus();
	//GetFocus()->GetWindow(GW_HWNDNEXT)->SetFocus();
	GetNextDlgTabItem(GetFocus())->SetFocus();
	//CDialog::OnOK();
}
ok按钮的缺省ID号是: IDOK ,而不是IDC_OK,所以我们在添加OK按钮时要将其ID号改为IDOK 


让编辑框接受回车键要修改它的属性,使"多行 MultiLine"复选上.











2006/11/28
lesson19,动态链接库
dumpbin
VC的bin目录下的 VCVARS32.BAT 批处理程序就是建立VC的开放环境的.
在命令提示符下的粘贴和拷贝
粘贴点击鼠标右键粘贴就可以了
复制点击鼠标右键选择标记,然后用鼠标左键标记一段,单击鼠标左键,那么就将相应内容复制到剪贴板下了.


新建一个空的dll工程,然后创建一个dll1.cpp文件如下
int  add(int a,int b)
{
	return a+b;
}

int  subtract(int a,int b)
{
	return a-b;
}
编译之后,我们看看导出函数
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
这里没有任何导出函数,那么我们可以这样,更改源文件
_declspec(dllexport) int  add(int a,int b)
{
	return a+b;
}

_declspec(dllexport) int  subtract(int a,int b)
{
	return a-b;
}

编译之后再去看看

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

好了,这次我们看到了两个我们自己下的函数名字,只是名字似乎被更改过了,这是VC为了函数重载的方便,它以自己的规则修改了我们的源程序的函数名字.
下面我们来测试下刚刚建立的dll1.dll动态链接库.
我们新建一个win32控制台的空工程,新建一个dlltest.cpp ,下面是它的源码
#include iostream.h
extern int add(int,int);   声明这个函数在外部定义
extern int subtract(int,int);
void main(void)
{
	cout3+5 = add(3,5)endl;
	cout5-3 = subtract(5,3)endl;
}
编译一下
Compiling...
dlltest.cpp
Linking...
dlltest.obj  error LNK2001 unresolved external symbol int __cdecl substract(int,int) (substract@@YAHHH@Z)
dlltest.obj  error LNK2001 unresolved external symbol int __cdecl add(int,int) (add@@YAHHH@Z)
DebugDllTest.exe  fatal error LNK1120 2 unresolved externals
执行 link.exe 时出错.
DllTest.exe - 1 error(s), 0 warning(s)

可以发现是在连接的时候出错了,则说明编译是没有错,编译器找到了这两个函数,因为这两个函数已经声明了.
但是在连接的时候没有找到.我们可以这样做;
将刚刚生成动态链接库文件的同一目录下,找到dll1.lib输入库文件,拷贝到我们的工程目录下,
最后 Project－Settings  在Link选项卡找到Objectlibrary modules  在最后填入 dll1.lib 。
如果原来就有链接，请使用空格分隔。

好的我们再编译下
--------------------Configuration DllTest - Win32 Debug--------------------
DllTest.exe - 0 error(s), 0 warning(s)
没有错误,执行时又出现错误,哦,我们的程序在执行时没有找到dll1.dll这个文件,好说,将它也拷贝到当前工程的目录下.
再执行,ye,这次就好了,输出信息如下
3+5 = 8
5-3 = 2
Press any key to continue

我们可以查看以查看一下这个可执行程序的输入信息
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



另外我们可以通过VC提供的图形化工具查看我们的可执行程序依赖的动态链接库文件,
在VC的安装目录下的 DSoftwaresMicrosoft Visual StudioVC98Microsoft Visual C++ 6.0 Tools 目录下有这个工具 Depends .
它可以查看可执行程序依赖的动态链接库文件

我们还可以这样声明动态链接库里的函数接口,源码修改为
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
编译运行.
_declspec(dllimport) 就告诉编译器这个函数是从动态链接库的.lib文件中输入的,编译器就能生成运行效率更高的代码.

我们可以把我们自己做的动态链接库文件的函数声明都放到一个头文件中,以便告诉用户这个动态链接库文件里封装的函数原型.
好的我们在前面动态链接库的工程中添加一个头文件 dll1.h ,其里面的内容是
_declspec(dllimport) int add(int,int);
_declspec(dllimport) int subtract(int,int);

那么现在我们就可以将源码修改为
#include iostream.h
extern int add(int,int);
extern int subtract(int,int);
#include ..Dll1dll1.h
void main(void)
{
	cout3+5 = add(3,5)endl;
	cout5-3 = subtract(5,3)endl;
}
编译运行.

我们到这里可以发现,前面的动态链接库源码文件dll1.cpp
_declspec(dllexport) int  add(int a,int b)
{
	return a+b;
}
_declspec(dllexport) int  subtract(int a,int b)
{
	return a-b;
}
这里是导出形式(dllexport),那么这个动态链接库就不能被它自己的源码程序调用,这时我们可以改改就行了
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


现在这个dll库就可以被自己调用也可以被其他程序调用了.
我们再看看怎么将类导出,象这样就好了
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

如果我们不想将整个类都导出,我们只需将类的部分公有成员函数导出,
我们可以这样做
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
这里的void test();是做一个对比用的.
我们用dumpbin -exports dll1.dll看看导出情况
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

这里就可以发现只有
          2    1 0000101E output@Point@@QAEXHH@Z
而没有test()


上面提到了VC++编译器将函数名字进行了改写,这对于其他编译器来说也许就不是什么好事,因为其他编译器很可能找不到导出的函数,
因为名字已经被改动了.那么我们就希望这个名字不要更改.这里可以加上 extern C 标识
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
编译下,看看导出情况,
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

这里就可以看到名字没有改变,
但是用 extern C 标识也有缺陷,就是它只能表示全局函数,
而对于类说,它不能导出类的成员函数.
如果调用约定被改变了的话,即使加了 extern C 标识,函数名还是会被改变
这里我们举例看看
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
编译下,看看导出情况
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
这里就可以看到名字还是发生了改变,
_add@8这里的8表示add函数的参数所占字节数.
我们看看下面的解决方法.

再重新新建一个dll的空工程,命名为Dll2       
再新建一个C++源文件,命名为dll2.cpp,
dll2.cpp
int add(int a,int b)
{
	return a+b;
}
int subtract(int a,int b)
{
	return a-b;
}

然后我们创建一个模块定义文件,命名为dll2.def,然后添加我们的工程中.其内容如下

LIBRARY Dll2

EXPORTS
add
subtract



其中 LIBRARY Dll2 这个名字一定要与我们的工程名字匹配,另外这句话也不是必须的.
EXPORTS表明动态链接库中要导出的函数名字,我们可以在 MSDN 中查看一下它的用法.

编译一下,看看导出情况
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
       
这里就可以看到名字没有改变,和原来的一样.


上面我们都是用隐式链接的方式调用动态链接库的,
下面我们看看另一种方法,显示调用
将我们的 DllTest 工程中的 Project－Settings  
在Link选项卡中的 Objectlibrary modules 删除 dll1.lib 

这里就要用到一个函数
HINSTANCE LoadLibrary
(
  LPCTSTR lpLibFileName    address of filename of executable module
);
它是映射指定的模块到应用进程的地址空间

获得函数的地址空间用如下函数,
FARPROC GetProcAddress(
  HMODULE hModule,     handle to DLL module
  LPCSTR lpProcName    name of function
);

好的,现在我们看看我们的测试程序怎么写,将测试工程中的 dlltest.cpp 文件改为如下

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
		cout获取函数地址失败！endl;
		return;
	}
	cout3+5 = ADD(3,5)endl;
	cout5-3 = SUB(5,3)endl;
	FreeLibrary(hInst);	 释放动态链接库	
}

编译运行,哦,别忘了将我们新编译处理的dll文件 dll2.dll 复制到我们的测试程序工程目录下.
运行结果如下
3+5 = 8
5-3 = 2
Press any key to continue

这里我们可以发现我们只拷贝了一个 dll2.dll 文件,
而没有拷贝我们的 dll2.lib ,这里是因为我们是动态加载的.
动态加载的好处是在我们需要的地方加载,这样可以节约内存空间.
如果是用隐式链接的方式,那么在我们启动程序时,多个dll库都要加载到内存中,
这时很浪费内存的,而且程序启动时间也很慢.



我们再来看看改变调用的方式,将dll2.cpp文件改变如下
dll2.cpp
int add(int a,int b)
{
	return a+b;
}
int subtract(int a,int b)
{
	return a-b;
}

编译一下,看看导出情况
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
这里就可以看到即使改变了调用方式,函数名字没有改变,和原来的一样.
好的,那么我们来看看测试程序,
当然,别忘了将我们新编译处理的dll文件 dll2.dll 复制到我们的测试程序工程目录下.
编译,没有错误,在运行时出现了错误,这是因为我们改变了调用的约定,
当然,在调用的时候也要遵循这样的约定,将测试工程中的 dlltest.cpp 文件改为如下

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
		cout获取函数地址失败！endl;
		return;
	}
	cout3+5 = ADD(3,5)endl;
	cout5-3 = SUB(5,3)endl;
	FreeLibrary(hInst);	 释放动态链接库	
}
好了这样就行了.
我们再来看看现在编译出来的可执行程序 dlltest.exe 的导入信息.
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
       
这里就看不到我们的 dll2.dll 的信息了.因为我们时动态加载

我们看到dll2.dll库的信息有如下
          1    0 0000100A add
          2    1 00001005 subtract
我们可以通过序号调用这两个函数,这里我们用到了 MAKEINTRESOURCE      
将测试工程中的 dlltest.cpp 文件改为如下

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
		cout获取函数地址失败！endl;
		return;
	}
	cout3+5 = ADD(3,5)endl;
	cout5-3 = SUB(5,3)endl;
	FreeLibrary(hInst);	 释放动态链接库	
}
好了这样就行了.  
但是我们应该通过函数名来调用dll库中的函数.
因为这个让程序可读性更好,出错几率也小些

对于动态链接库的可选程序入库点时 DllMain
BOOL WINAPI DllMain(
  HINSTANCE hinstDLL,   handle to DLL module
  DWORD fdwReason,      reason for calling function
  LPVOID lpvReserved    reserved
);

这里我们看到通过模块话生成动态链接库是比较好的选择.






Lesson8
逃跑按钮，属性表单，向导
用ClassWizard生成新的类时,有时候它并不识别这个类,那么我们需要先将工程关闭,
然后删除工程目录下的*.clw文件,然后再打开工程,按照提示创建一个同名的文件.

属性表单(类似于QT中的TabWidget)的创建方法:
Objects of class CPropertyPage represent individual pages of a property sheet, 
otherwise known as a tab dialog box. As with standard dialog boxes, 
you derive a class from CPropertyPage for each page in your property sheet. 
To use CPropertyPage-derived objects, first create a CPropertySheet object, 
and then create an object for each page that goes in the property sheet. 
Call CPropertySheet::AddPage for each page in the sheet, 
and then display the property sheet by calling CPropertySheet::DoModal for a modal property sheet, 
or CPropertySheet::Create for a modeless property sheet.

生成属性表单的方法
->首先单独生成几个 CPropertyPage 对话框,例如CProp1,CProp2,CProp3,...
->构造一个新类 CMyPropertySheet,继承自 CPropertySheet
->在 CMyPropertySheet 中分别声明 CProp1,CProp2,CProp3,...的实例对象
->在 CMyPropertySheet 的构造函数中调用 AddPage(...)分别将前面的属性页添加进来
->最后就实例化一个 CMyPropertySheet 对象,然后调用 DoModal 就可以了.


生成配置向导的方法:
->首先单独生成几个 CPropertyPage 对话框,例如CProp1,CProp2,CProp3,...
->构造一个新类 CMyPropertySheet,继承自 CPropertySheet
->在 CMyPropertySheet 中分别声明 CProp1,CProp2,CProp3,...的实例对象
->在 CMyPropertySheet 的构造函数中调用 AddPage(...)分别将前面的属性页添加进来
->最后就实例化一个 CMyPropertySheet 对象,然后依次调用 SetWizardMode  DoModal 就可以了.
但是这样生成的向导,在第一步还有"上一步",在最后一步还要"下一步",我们必须修改下
这个方法 SetWizardButtons 是设置按钮的.

Call this member function to enable or disable the Back, Next, or Finish button 
in a wizard property sheet. Call SetWizardButtons only after the dialog is open;
 you can’t call SetWizardButtons before you call DoModal.
  Typically, you should call SetWizardButtons from CPropertyPage::OnSetActive.
这里说应该在 CPropertyPage::OnSetActive 中调用  SetWizardButtons
BOOL CProperty3::OnSetActive() 
{
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_FINISH | PSWIZB_BACK );
	return CPropertyPage::OnSetActive();
}

创建多个单选按钮时,要将第一个的属性中的"组(Group)"选中,这样才能排斥其他，
那么在遇到第二个"组(Group)"选中之前的所有单选按钮都是一组的。
对单选按钮的选择的判断可以增加一个关联对象。

CListBox 
CComboBox 默认有排序功能，要是不想其排序而按照我们输入的顺序排列，可以将其属性的“sort”不选中

void *memset( void *dest, int c, size_t count );可以初始化一段内存
例如:
BOOL bLike[10];
memset(bLike,0,sizeof(bLike));



2006/11/29
lesson 9
应用程序外观
1. 在创建窗口完成之前修改
修改应用程序的外观可以在框架类的PreCreateWindow函数中去修改
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

改变标题:
	cs.style &= ~FWS_ADDTOTITLE ;   //这一步是必须的，让窗口不具有 FWS_ADDTOTITLE 类型
	cs.lpszName = "http://blog.csdn.net/zieckey"

该函数可以在窗口创建之后改变外观。
LONG SetWindowLong(
  HWND hWnd,       // handle of window
  int nIndex,      // offset of value to set
  LONG dwNewLong   // new value
);
下面我们看看：
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
....
	SetWindowLong( m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW );  //去掉文档的标题
0....
}

获取现有窗口类型：
LONG GetWindowLong(
  HWND hWnd,  // handle of window
  int nIndex  // offset of value to retrieve
);

取消窗口的最大化按钮。
SetWindowLong(m_hWnd,GWL_STYLE,GetWindowLong(m_hWnd,GWL_STYLE) & ~WS_MAXIMIZEBOX);

修改窗口的光标和背景要在View类中去修改，因为我们看到的单文档程序的上面覆盖有View类
而修改窗口的图标等就应该在Frame类中修改。

修改窗口的图标：
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
这一过程可以通过这个函数实现：	
cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,0,0,LoadIcon(NULL,IDI_WARNING));
如果我们使用缺省的值：
cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);
会得到一个透明的窗口
	
2. 在创建窗口完成之后修改	
在OnCreate函数中调用SetClassLong
SetClassLong(m_hWnd,GCL_HICON,(LONG)LoadIcon(NULL,IDI_ERROR));	

AfxGetInstanceHandle   得到当前的应用程序实例句柄Obtains a handle to the current application instance.
MAKEINTRESOURCE 将资源ID转换为字符数组 The MAKEINTRESOURCE macro converts an integer value to a resource type compatible with Win32 resource-management functions
在CMainFrame类的构造函数中加载图标的方法:
函数原型:
HICON LoadIcon(
  HINSTANCE hInstance, // handle to application instance
  LPCTSTR lpIconName   // icon-name string or icon resource identifier
);
{
	m_hIcons[0]=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1));
	m_hIcons[1]=LoadIcon(theApp.m_hInstance,MAKEINTRESOURCE(IDI_ICON2));  //用这个之前声明一下:  extern CStyleApp theApp;
	m_hIcons[2]=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON3));
}

创建自己的工具栏:
1. Create a toolbar resource.
2. Construct the CToolBar object.
3. Call the Create (or CreateEx) function to create the Windows toolbar and attach it to the CToolBar object.
4. Call LoadToolBar to load the toolbar resource. 
具体实现:(这里可以参考MFC源程序为我们生成工具栏的方法)
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
	
下面在"菜单->查看"下增加一个项,可以让我们新建的工具栏显示或隐藏
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
				RecalcLayout();   //检测工具条,如果没有工具栏,那么就隐藏工具条
				DockControlBar(&m_newToolBar);  //停靠工具栏
		}
		或者另外的方式:
		{
				ShowControlBar(&m_newToolBar,!m_newToolBar.IsWindowVisible(),FALSE);
		}			
}

为我们的"菜单->查看"加上它的复选标记:
{
		void CMainFrame::OnUpdateViewNewtool(CCmdUI* pCmdUI) 
		{
			// TODO: Add your command update UI handler code here
			pCmdUI->SetCheck(m_newToolBar.IsWindowVisible());
		}
}


状态栏的编程:
{
	//提示符数组
	static UINT indicators[] =
	{
		ID_SEPARATOR,           // status line indicator
		ID_INDICATOR_CAPS,      //大小写开关键
		ID_INDICATOR_NUM,				//数字开关键
		ID_INDICATOR_SCRL,			//Scroll开关键
	};
	//状态栏对象
	CStatusBar  m_wndStatusBar;
	
	//实现:
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
		当我们想在状态栏上添加项目时,只需先在资源的"String Table"中添加相应项,例如: IDS_INDICATOR_TIMER
		然后将 IDS_INDICATOR_TIMER 添加到indicators数组的定义中,例如:
		static UINT indicators[] =
		{
			ID_SEPARATOR,           // status line indicator
			IDS_INDICATOR_TIMER,
			ID_INDICATOR_CAPS,      //大小写开关键
			ID_INDICATOR_NUM,				//数字开关键
			ID_INDICATOR_SCRL,			//Scroll开关键
		};
		这样就可以在状态栏下添加相应的项目了.
	}
	
	在状态栏显示我们的信息,例如我们显示 CString str="zieckey";
	{
				简单的实现
				{
					//这里的 index 是状态栏中的索引号,也就是和indicators数组中对应的项	
					//m_wndStatusBar.SetPaneText(index,str);
				}
			
				  //更详细的实现
				  {
							CTime t=CTime::GetCurrentTime();  //得到系统时间
							CString str=t.Format("%H:%M:%S"); //格式化到字符数组
							CClientDC dc(this);
							CSize sz=dc.GetTextExtent(str);		//得到字符数组的显示长度
							int index=0;
							index=m_wndStatusBar.CommandToIndex(IDS_TIMER);  //得到索引号
							 
							//更改状态栏信息,以恰当的宽度显示字符串
							m_wndStatusBar.SetPaneInfo(index,IDS_TIMER,SBPS_NORMAL,sz.cx); 
							m_wndStatusBar.SetPaneText(index,str); //显示字符串
				  }
		  
				  {
						  		//为了便于实时更新我们的系统时间,上面的代码可以在 OnTimer 函数中实现:
						  		//当然你得先做这一步:  SetTimer(1,1000,NULL);
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

得到系统时间
{
	CTime t=CTime::GetCurrentTime();
	CString str=t.Format("%H:%M:%S");
}


进度栏的创建:
{
		//在任意位置创建
		{
				m_progress.Create(WS_CHILD | WS_VISIBLE | PBS_VERTICAL,CRect(100,100,120,200),this,123);
				m_progress.SetPos(50);//设置进度数值,这里是正中间
		}
		//在状态栏中创建
		{
					//可以在OnPaint函数中去创建
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
		
		//让进度条动起来:
		在OnTimer函数中调用m_progress.StepIt();就可以了
}

在状态栏中显示鼠标坐标的值:
{
			void CStyleView::OnMouseMove(UINT nFlags, CPoint point) 
			{
				
				CString str;
				str.Format("x=%d,y=%d",point.x,point.y);
				//方法一:
				//((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(str);
				//方法二:
				//((CMainFrame*)GetParent())->SetMessageText(str);
				//方法三:
				//((CMainFrame*)GetParent())->GetMessageBar()->SetWindowText(str);
				//方法四,AFX_IDW_STATUS_BAR是系统预先定义的值
				GetParent()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowText(str);
				
				CView::OnMouseMove(nFlags, point);
			}
}


自定义消息:
{
		消息定义:
		{
				//在
				//这里的WM_USER是系统定义的宏,小于WM_USER的整数都被系统消息占用
				//那么我们自定义的消息值就可以这样定义
				#define UM_PROGRESS		WM_USER+1
		}
		消息处理函数原型声明:
		{
				.....
				//}}AFX_MSG
				afx_msg void OnProgress();
				DECLARE_MESSAGE_MAP()
		}
		消息映射:
		{
				//}}AFX_MSG_MAP
				ON_MESSAGE(UM_PROGRESS,OnProgress)
				END_MESSAGE_MAP()
		}
		最后就是消息处理函数的实现
		
}

程序带上启动画面:
{
		选择：project->Add to project->conponent and controls..
		这里是VC提供给我们的一些组建和控件，我们选择 Visual C++ Components ,
		再选择 Splash screen 插入到我们的工程中.
		在 int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 中有一个 SetTimer(1, 750, NULL);
		就是这个画面的显示时间 
}





2006/11/30

Lesson 12 文件操作

指向常量的指针
{
		#include <iostream.h>
		
		void main()
		{
			char ch[5] = "lisi";
			const char * pCStr1 = ch;
		
			//*pCStr1= 'w';		//error   pCStr1 指向的对象是常量,所以不那被修改
			pCStr1 = "zieckey" ;	//OK	pCStr1 指向的对象是常量,但是它的地址是可以修改的
		
			char * const pCStr2 = ch;
		
			*pCStr2 = 'w';			//OK 	*pCStr2 不是常量,也就是说pCStr2指向的内容是可以修改的 
			//pCStr2 = "zieckey";   //error pCStr2是常量,也就是pCStr2的地址是常量
		
			const char * const pCCStr = ch;
			//*pCCStr = 'w';			//error		
			//pCCStr = "zieckey";   //error 这个时候 pCCStr 也是常量 
		}
}


C语言中对文件的操作:
{
			FILE *fopen( const char *filename, const char *mode );用法:

			size_t fwrite( const void *buffer, size_t size, size_t count, FILE *stream ); 用法:
			(
					加入我们想写入6个字节,
					如果 size = 1,那么 count = 6
					如果 size = 2,那么 count = 3
			)
			
			C语言对文件的操作使用是的缓冲型的,也就是说他会为每个打开的文件开辟一个内存缓冲区.
			{
					写入文件内容到磁盘后并保存退出
					{
							FILE *pFile=fopen("1.txt","w");
							fwrite("http://blog.csdn.net/zieckey",1,strlen("http://blog.csdn.net/zieckey"),pFile);
							fclose(pFile);			
					}
					写入文件内容到磁盘后但不退出:
					{
							FILE *pFile=fopen("1.txt","w");
							fwrite("http://blog.csdn.net/zieckey",1,strlen("http://blog.csdn.net/zieckey"),pFile);
							fflush(pFile);  //刷新缓冲区,即是将内存中数据写入到磁盘			
					}			
					
					int fseek( FILE *stream, long offset, int origin );//移动文件指针到指定位置处

					//读取文件数据1
					void CFileView::OnFileRead() 
					{
						FILE *pFile=fopen("1.txt","r");
						char ch[100];
						memset(ch,0,100);   //将字符数组所有的数据都初始化为0
						fread(ch,1,100,pFile);
						MessageBox(ch);
						fclose(pFile);
					}				

					//读取文件数据2
					void CFileView::OnFileRead() 
					{
						//以实际文件大小分配内存空间
						FILE *pFile=fopen("1.txt","r");
						char *pBuf;
						fseek(pFile,0,SEEK_END);  //移动文件指针到文件末尾
						int len=ftell(pFile);     //得到文件大小字节数			
						pBuf=new char[len+1];     //这里多分配了一个字节,主要是存放'\0'
						rewind(pFile);            //移动文件指针到文件开始处
						fread(pBuf,1,len,pFile);
						pBuf[len]=0;
						MessageBox(pBuf);
						fclose(pFile);
					}					
			}
}

文件
{
		二进制文件和文本文件定义:
		{
				文件是在计算机内存中以二进制表示的数据在外部存储介质上的另一种存放形式。
				文件通常分为二进制文件和文本文件。
				二进制文件是包含在 ASCII 及扩展 ASCII 字符中编写的数据或程序指令的文件。
				一般是可执行程序、图形、图象、声音等等文件。
				文本文件(也称为ASCII文件)：它的每一个字节存放的是可表示为一个字符的ASCII代码的文件。
				它是以 “行”为基本结构的一种信息组织和存储方式的文件，
				可用任何文字处理程序阅读的简单文本文件。  
		}
		文本方式和二进制方式:
		{
				当我们按照文本方式往文件中写入数据时，一旦遇到换行字符(ASCII为10)，
				则会转换为回车－换行(ASCII为13、10)。
				在读取文件时，一旦遇到回车－换行的组合(即连续的ASCII 13、10)，
				则会转换为换行字符(ASCII为10)。
				
				当我们按照二进制方式往文件中写入数据，则将数据在内存中的存储形式原样输出到文件中。		
			
				所以我们在读写文件的时候应该一致.
				另外,不管是二进制文件还是文本文件我们都可以通过二进制方式读写文件,这样是最安全的.
		}
}




C++语言中对文件的操作:
{
		通过ofstream类来操作文件,当然我们必须包含 #include <fstream.h>
		{
				ofstream ofs("4.txt");
				ofs.write("http://www.sunxin.org",strlen("http://www.sunxin.org"));
				ofs.close();			
		}
		打开文件:
		{
				ifstream ifs("4.txt");
				char ch[100];
				memset(ch,0,100);
				ifs.read(ch,100);
				ifs.close();
				MessageBox(ch);		
		}		
}

我们再看看WIN API中的文件操作:  CreateFile
{
		写文件:
		{
				HANDLE hFile;
				hFile=CreateFile(	"5.txt",		//文件名
									GENERIC_WRITE,
									0,	
									NULL,			//使用缺省的安全性
									CREATE_NEW,
									FILE_ATTRIBUTE_NORMAL,
									NULL);
				DWORD dwWrites;//接受实际写入的字节数
				WriteFile(hFile,"http://blog.csdn.net/zieckey",strlen("http://blog.csdn.net/zieckey"),
					&dwWrites,NULL);  
				CloseHandle(hFile);		
		}
		读文件:
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

我们再看看MFC中的文件操作:  CFile
{
		写入:
		{
				CFile file("6.txt",CFile::modeCreate | CFile::modeWrite);
				file.Write("http://blog.csdn.net/zieckey",strlen("http://blog.csdn.net/zieckey"));
				file.Close();		
		}
		读取:
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


MFC下打开或保存的文件对话框: CFileDialog
{
		//创建一个保存对话框1
		{
				CFileDialog fileDlg(TRUE);
				fileDlg.DoModal()；		
		}
		
		//创建一个保存对话框2
		{
				CFileDialog fileDlg(TRUE);
				fileDlg.m_ofn.lpstrTitle="我的文件打开对话框";   //对话框的标题栏
				fileDlg.m_ofn.lpstrFilter="Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";  //过滤器
				fileDlg.m_ofn.lpstrDefExt="txt";  //缺省的扩展名
				if(IDOK==fileDlg.DoModal())
				{	//在保存的时候写入一些数据到文本
					CFile file(fileDlg.GetFileName(),CFile::modeCreate | CFile::modeWrite);
					file.Write("http://blog.csdn.net/zieckey",strlen("http://blog.csdn.net/zieckey"));
					file.Close();
				}					
		}


		//打开文件对话框
		
}

向 win.ini 文件写入一些信息：
{
		可以在BOOL CFileApp::InitInstance()函数中添加类似下面的语句
		::WriteProfileString("http://blog.csdn.net/zieckey","admin","zieckey");
}
当然可以同过  GetProfileString
{
		CString str;
		::GetProfileString("http://www.sunxin.org","admin","lisi",
			str.GetBuffer(100),100);
		AfxMessageBox(str);
}

但是 CWinApp::WriteProfileString 写入的信息就有所区别：
{
		The entries are stored as follows: 
		In Windows NT, the value is stored to a registry key.
		In Windows 3.x, the value is stored in the WIN.INI file. 
		In Windows 95, the value is stored in a cached version of WIN.INI. 
		
		如果直接在 BOOL CFileApp::InitInstance()函数中添加这样的语句的话，他会写入注册表：
				WriteProfileString("http://blog.csdn.net/zieckey","admin","zieckey");
		在注册表的：HKEY_CURRENT_USER\Software\Local AppWizard-Generated Applications\File 
		下面写入一个信息。
		这是因为在 BOOL CFileApp::InitInstance()函数中有下面的语句来设置注册表项：
				SetRegistryKey(_T("Local AppWizard-Generated Applications"));
		当然你可以更改"Local AppWizard-Generated Applications"使之更符合你的需求。
}

我们当然可以读取注册表中的值：CWinApp::GetProfileString 

对注册表编程：
{
		//写注册表：RegCreateKey
		void CMainFrame::OnRegWrite() 
		{
			HKEY hKey;   //声明一个句柄
			DWORD dwAge=30;
		
			//在注册表的HKEY_LOCAL_MACHINE\SOFTWARE\ 地方写入 http://blog.csdn.net/zieckey 并在他目录下写入 admin 
			RegCreateKey(HKEY_LOCAL_MACHINE,"Software\\http://blog.csdn.net/zieckey\\admin",&hKey);
			
			// 在 admin 下创建两个项
			{
				//RegSetValue用于设置缺省的值，并且值只能是字符串型的
				RegSetValue(hKey,NULL,REG_SZ,"zieckey",strlen("zieckey"));  
				//创建REG_SZ以外的其他类型的值
				RegSetValueEx(hKey,"age",0,REG_DWORD,(CONST BYTE*)&dwAge,4);
			}
			
			RegCloseKey(hKey);	
		}
		
		读注册表的缺省值：RegQueryValue
		void CMainFrame::OnRegRead() 
		{
			LONG lValue;
			RegQueryValue(HKEY_LOCAL_MACHINE,"Software\\http://blog.csdn.net/zieckey\\admin",
				NULL,&lValue);  //先得到数据的长度(包含的末尾'\0'这个结束符)
			char *pBuf=new char[lValue];//动态准确的分配内存
			RegQueryValue(HKEY_LOCAL_MACHINE,"Software\\http://blog.csdn.net/zieckey\\admin",
				pBuf,&lValue);  //得到数据值 
			MessageBox(pBuf);	//显示数据值 
		}		
		
		读取注册表的其他数据值:
		{
				void CMainFrame::OnRegRead()
				{
					HKEY hKey;
					RegOpenKey(HKEY_LOCAL_MACHINE,"Software\\http://blog.csdn.net/zieckey\\admin",&hKey);
					DWORD dwType;
					DWORD dwValue;
					DWORD dwAge;
				
					//hKey必须先被打开,所以前面必须有 "RegOpenKey"类似的函数得到 hKey
					RegQueryValueEx(hKey,"age",0,&dwType,(LPBYTE)&dwAge,&dwValue);  
					CString str;
					str.Format("age=%d",dwAge);
					MessageBox(str);
				}		
		}
}



2006/12/2

在对话框上添加菜单栏（CMenu）
{
	在资源管理器中生成一个菜单资源其ID命名为：IDM_MAIN_MENU
	然后再对话框的 BOOL CDialogWithMenuDlg::OnInitDialog() 函数中添加以下语句：
	{	//m_menu是对话框的成员变量
		VERIFY(m_menu.LoadMenu(IDM_MAIN_MENU));
		SetMenu(&m_menu);
		m_menu.Detach();
	}
}






2006/12/4
文档和视图的分离
文档对象容纳数据，而视图对象显示这些数据并允许编辑。

CView::GetDocument 函数
与文档对象关联

CDocument::UpdateAllViews 函数
通知所有的视图更新数据



2006/12/05
Lesson13
文档和串行化

CArchive的使用
{
	//写入数据到文件
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
			ar<<i<<ch<<f<<str;		//写入数据
		}	
	}
	
	//读取文件中数据
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
			ar>>i>>ch>>f>>str;  //这里注意要与上面保存的时候顺序一致
			strResult.Format("%d,%c,%f,%s",i,ch,f,str);
			MessageBox(strResult);
		}		
	}
}

设置文档的标题
{
	//通过OnNewDocument函数设置
	BOOL CGraphicDoc::OnNewDocument()
	{
		if (!CDocument::OnNewDocument())
			return FALSE;
	
		// TODO: add reinitialization code here
		// (SDI documents will reuse this document)
		SetTitle("http://blog.csdn.net/zieckey");
		
		return TRUE;
	}
	
	另外还可以在资源视图中的"String Table->字符串表"中的 IDR_MAINFRAME 修改
	可以看到 IDR_MAINFRAME 的缺省值类似:
		Graphic\n\nGraphi\n\n\nGraphic.Document\nGraphi Document
	这里每个 \n	表示一个段的分隔,我们该为如下的,跟上面的 SetTitle 效果一样
		Graphic\nhttp://blog.csdn.net/zieckey\nGraphi\n\n\nGraphic.Document\nGraphi Document
	这是通过 BOOL CGraphicApp::InitInstance() 中的
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGraphicDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CGraphicView));
	AddDocTemplate(pDocTemplate);
	添加进来的	
}

String Table中IDR_MAINFRAME字符串资源中各子串的含义
{
	virtual BOOL GetDocString( CString& rString, enum DocStringIndex index ) const;
	
	(1)CDocTemplate::windowTitle，主窗口标题栏上的字符串，MDI程序不需要指定，
		将以IDR_MAINFRAME字符串为默认值。
	(2)CDocTemplate::docName，缺省文档的名称。如果没有指定，缺省文档的名称是无标题。
	(3)CDocTemplate::fileNewName，文档类型的名称。如果应用程序支持多种类型的文档，
		此字符串将显示在"File/New"对话框中。如果没有指定，
		就不能够在"File/New"对话框处理这种文件。
	(4)CDocTemplate::filterName，文档类型的描述和一个适用于此类型的通配符过滤器。
		这个字符串将出现在“File/Open”对话框中的文件类型列表框中。
		要和CDocTemplate::filterExt一起使用。
	(5)CDocTemplate::filterExt，文档的扩展名。
		如果没有指定，就不能够在“File/Open”对话框中处理这种文档。
		要和CDocTemplate::filterName一起使用。
	(6)CDocTemplate::regFileTypeId，如果你以::RegisterShellFileTypes向系统的注册表注册文件类型，
		此值会出现在HEY_CLASSES_ROOT之下成为其子项，并仅供Windows内部使用。
		如果没有指定，这种文件类型就无法注册。
	(7)CDocTemplate::regFileTypeName，这也是存储在注册表中的文件类型名称。
		它会显示于程序中用以访问注册表的对话框内。
			
}

文件->保存(或打开)项的实现:
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
	
	不过这里要注意,在保存后第二次打开文件对话框并不会进入 Serialize 这个函数里来,
	因为MFC认为这是一段相同的数据.
}
 

创建一个串行化的类:
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

打开一个已有的资源:
	直接打开*.rc的文件就好了.这样就可以复制原来已有的资源了.
	
在文档类中得到视类的指针:
	
	
Document/View结构
{
	在MFC中，文档类负责管理数据，提供保存和加载数据的功能。
	视类负责数据的显示，以及给用户提供对数据的编辑和修改功能。
	
	MFC给我们提供Document/View结构，将一个应用程序所需要的“数据处理与显示”的函数空壳都设计好了，
	这些函数都是虚函数，我们可以在派生类中重写这些函数。
	有关文件读写的操作在CDocument的Serialize函数中进行，
	有关数据和图形显示的操作在CView的OnDraw函数中进行。
	我们在其派生类中，只需要去关注Serialize和OnDraw函数就可以了，
	其它的细节我们不需要去理会，程序就可以良好地运行。
	
	当我们按下“File/Open”，Application Framework会激活文件打开对话框，
	让你指定文件名，然后自动调用CGraphicDoc::Serialize读取文件。
	Application Framework还会调用CGraphicView::OnDraw，传递一个显示DC，让你重新绘制窗口内容。
	
	MFC给我们提供Document/View结构，是希望我们将精力放在数据结构的设计和数据显示的操作上，
	而不要把时间和精力花费在对象与对象之间、模块与模块之间的通信上。
	
	一个文档对象可以和多个视类对象相关联，而一个视类对象只能和一个文档对象相关联。

}	



2006/12/06
数据库

数据库访问技术
{
	ODBC(Open Database Connectivity)，开放数据库互连。
	ODBC是上个世纪八十年代末九十年代初出现的技术，
	它为编写关系数据库的客户软件提供了一种统一的接口。
	ODBC提供一个单一的API，可用于处理不同数据库的客户应用程序。
	使用ODBC API的应用程序可以与任何具有ODBC驱动程序的关系数据库进行通信。
	
	DAO(Data Access Object)，数据访问对象。
	DAO就是一组Microsoft Access/Jet数据库引擎的COM自动化接口。 
	DAO不像ODBC那样是面向C/C++程序员的，
	它是微软提供给Visual Basic开发人员的一种简单的数据访问方法，用于操纵Access数据库。 
	
	RDO(Remote Data Object)，远程数据对象。
	由于RDO直接调用ODBC API(而不是像DAO那样通过Jet引擎)，
	所以，可以为使用关系数据库的应用程序提供更好的性能。
	
	OLE DB，对象链接与嵌入数据库。 
	OLE DB在两个方面对ODBC进行了扩展。
	首先， OLE DB提供了一个数据库编程的COM接口；
	第二， OLE DB提供了一个可用于关系型和非关系型数据源的接口。 
	OLE DB的两个基本结构是OLE DB提供程序(Provider)和OLE DB用户程序(Consumer)。
	
	ADO(ActiveX Data Object)，ActiveX数据对象，它建立在OLE DB之上。
	ADO是一个OLE DB用户程序。使用ADO的应用程序都要间接地使用OLE DB。
	ADO简化了OLE DB，提供了对自动化的支持，使得像VBScript这样的脚本语言也能够使用ADO访问数据库。
	
	ADO的三个核心对象
	{
		Connection对象
			Connection对象表示了到数据库的连接，
			它管理应用程序和数据库之间的通信。 
			Recordset和Command对象都有一个ActiveConnection属性，
			该属性用来引用Connection对象。
		Command对象
			Command对象被用来处理重复执行的查询，
			或处理需要检查在存储过程调用中的输出或返回参数的值的查询。
		Recordset对象
			Recordset对象被用来获取数据。 
			Recordset对象存放查询的结果，这些结果由数据的行(称为记录)和列(称为字段)组成。
			每一列都存放在Recordset的Fields集合中的一个Field对象中。
	}
}

使用ADO
{
	ado的动态连接库：C:\Program Files\Common Files\System\ado
	找到 "C:\Program Files\Common Files\System\ado\msado15.dll"
	然后在我们的工程中的stdafx.h文件中添加：
	#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","rsEOF")
	这里加上 rename("EOF","rsEOF") ，因为我们的文件结尾也是 EOF 为了避免冲突，更改以下。	

	编译后在debug目录下生成有下面两个文件：msado15.tlh，msado15.tli
	为了方便查看，可以将其添加到工程中。
}



2006/12/08
ODBC数据库管理
{
	ODBC元素：环境(environment),连接(connection)和语句(statement),
	这三个都是通过句柄来访问的。
	
	首先我们必须有一个环境，他建立了程序和ODBC系统之间的关系，应用系统通常只有一
	个环境句柄。
	然后，我们需要有一个或多个连接。连接建立了驱动程序和数据源之间的特定组合关系
	一旦获得了连接我们需要一个SQL语句来执行。
	
	MFC ODBC类————CRecordset和CDatabase
	{
		类CDatabase的对象代表了数据源的ODBC连接，而CRecordset的对象代表了可滚动
		行集。用户很少从CDatabase类派生出类，却总是从CRecordset中派生出类，
		以便和数据库中的表的列相匹配。
		
	}
}



2006/12/09
ODBC数据库应用
{
	自己先用Access定义一个数据库GSM.mdb，然后建立一个表，例如：Athlete。
	然后注册数据源(控制面板->管理工具->数据源(ODBC))	

	
	在VC中通过类向导生成一个CRecordset的派生类，例如：CAthleteRecordSet
	之后选择数据源的时候选择GSM.mdb，再选择表Athlete，这样就好了。
	（注意：有多个表的时候应建立多个CRecordset的派生类与每个表单独对应）
	
	在写程序时，在C*Doc类中添加 CAthleteRecordSet的数据成员 m_AthleteRecordSet
	在C*View类中添加 CAthleteRecordSet的数据成员 *m_pAthleteRecordSet;
	在C*Doc类的头文件中添加#include "AthleteRecordSet.h"
	在C*View类的构造函数中添加初始化代码:
	m_pAthleteRecordSet = &GetDocument()->m_AthleteRecordSet;
	
	那么现在就可以通过m_pAthleteRecordSet来实现对数据库的操作了.

	
	对ODBC数据库应用程序实现对数据的任意查询，只需先关闭记录集，
	然后调用CRecordSet::Open()函数时指定SQL查询语句，例如：
	{
		if ( m_pSet->IsOpen() ) 
		{
			m_pSet->Close();
		}
		m_pSet->Open( CRecordset::dynaset, _T("select * from table1"));
	}
	
	或者先设置 m_strFilter 
	然后调用Requery方法就可以了。



}





//改变窗口大小
void CGameManageSystemView::OnSize(UINT nType, int cx, int cy) 
{
	CRecordView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rectClient;
	this->GetClientRect( &rectClient ); // 获得视类窗口区域
	
	//这里要进行判断,因为WM_SIZE消息在窗口初绘时就发出,而
	//窗口里的一些控件可能还没有初始化
	if ( m_TabCtrl ) 
	{
		m_TabCtrl.SetWindowPos( m_TabCtrl.GetWindow( GW_HWNDPREV ) , 
				rectClient.left, rectClient.top, 
				rectClient.Width(), rectClient.Height(), 
				SWP_SHOWWINDOW );
	}
		
}



2006/12/12
在CTabCtrl中的按钮消息，可以发送到MainFrm中，
然后通过GetActiveView( )在MainFrm中处理信号

CListCtrl::InsertItem这个是在第一列插入一个Item

使用这个时，必须将CListCtrl的属性的 “Styles->View”设置为“Report”
m_ListCtrlAthlete.InsertColumn( 0, "编号" , LVCFMT_LEFT, 30, 0);



	//得到新的主键
	long AthleteID = 154;
	m_pSet->Close();
	m_pSet->m_strSort = "AthleteID";  //排序
	m_pSet->Open();
	m_pSet->MoveLast();  //得到最后一个记录，也就是最大的编号
	AthleteID = m_pSet->m_AthleteID+1;
	
	
	
	HANDLE GetClipboardData(
  UINT uFormat   // clipboard format
);


开始一段记录集的操作
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
对数据库的操作要注意的地方:
{
	在进行	this->MoveLast(); 操作之前一定要判断是否到了最后,或记录集是否为空.
	
	在任何时候对m_strFilter、m_strSort操作之后，都要将其清空，
		this->m_strFilter.Empty();
		this->m_strSort.Empty();
	在任何时候执行打开Open或Requery前都要先将m_strFilter、m_strSort操作,然后再赋值	 
}




列表框的使用
{
	//先插入表头
	m_list.InsertColumn( 0,  "Test", LVCFMT_CENTER, 80 );
	m_list.InsertColumn( 1, "编号" , LVCFMT_LEFT, 80 );
	m_list.InsertColumn( 2, "姓名" , LVCFMT_LEFT, 80 );
	m_list.InsertColumn( 3, "性别" , LVCFMT_LEFT, 80 );
	m_list.InsertColumn( 4, "出生年份" , LVCFMT_LEFT, 80 );
	m_list.InsertColumn( 5, "学号" , LVCFMT_LEFT, 80 );

	//再插入表的内容。
	//插入表的内容之前要先用InsertItem插入一行，
	//然后调用SetItemText函数插入该行中各列的内容
	
	//插入第一行
	m_list.InsertItem(  0,"Test");
	m_list.SetItemText( 0, 0, "ga" ); //插入编号
	m_list.SetItemText( 0, 1, "ga" );
	m_list.SetItemText( 0, 2, "ga" );
	m_list.SetItemText( 0, 3, "ga" );
	m_list.SetItemText( 0, 4, "ga" );
	m_list.SetItemText( 0, 5, "ga" ); //插入班级

	//插入第二行
	m_list.InsertItem(  1,"Test");
	m_list.SetItemText( 1, 0, "sfsf" ); //插入编号
	m_list.SetItemText( 1, 1, "sfsf" );
	m_list.SetItemText( 1, 2, "sfsf" );
	m_list.SetItemText( 1, 3, "sfsf" );
	m_list.SetItemText( 1, 4, "sfsf" );
	m_list.SetItemText( 1, 5, "sfsf" ); //插入班级
	
}	



自定义消息:分四步走：
{
		1.消息定义:
		{
				//在C*APP类的头文件中定义消息值
				//这里的WM_USER是系统定义的宏,小于WM_USER的整数都被系统消息占用
				//那么我们自定义的消息值就可以这样定义
				#define UM_GAME_ITEM_CHANGED		WM_USER+1
		}
		2.消息处理函数原型声明:
		{	
				//在处理该消息的类的头文件中声明处理该消息的函数

				//{{AFX_MSG(CPageResult)
				afx_msg void OnButtonAdd();
				afx_msg void OnButtonAddComplete();
				afx_msg void OnButtonDelete();
				afx_msg void OnButtonEdit();
				afx_msg void OnButtonQuery();
				afx_msg void OnEditchangeComboGameItemName();
				afx_msg void OnSelchangeComboGameItemName();
				//}}AFX_MSG
				afx_msg void OnGameItemChanged();  //自定义消息处理函数
				DECLARE_MESSAGE_MAP()
		}
		3.消息映射:
		{		
//在处理该消息的类的实现文件中声明消息映射
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
		4.最后就是消息处理函数的实现
		void CPageResult::OnGameItemChanged()
		{
			//。。。。。。。。。。。。
		}
		
		现在就可以用这个消息了，如果需要系统及时处理该消息，可以调用
		SentMessage( UM_GAME_ITEM_CHANGED );函数，
		如果想系统在处理完其它消息后再来响应该消息，就调用：
		PostMessage( UM_GAME_ITEM_CHANGED );
		
}




Visual C++中的ODBC编程实例2006年12月02日 星期六 21:15Visual C++中的ODBC编程实例
{
	Microsoft Developer Studio为大多数标准的数据库格式提供了32位ODBC驱动器。这些标准数据格式包
	
	括有:SQL Server、Access、Paradox、dBase、FoxPro、Excel、Oracle以及Microsoft Text。如果用户
	
	希望使用其他数据格式,则需要安装相应的ODBC驱动器及DBMS。 
	
	　　 用户使用自己的DBMS数据库管理功能生成新的数据库模式后,就可以使用ODBC来登录数据源。对用
	
	户的应用程序来说,只要安装有驱动程序,就能注册很多不同的数据库。登录数据库的具体操作参见有关
	
	ODBC的联机帮助。 
	
	　　 一、MFC提供的ODBC数据库类 
	
	　　 Visual C++的MFC基类库定义了几个数据库类。在利用ODBC编程时,经常要使用到 CDatabase(数据
	
	库类)、CRecordSet(记录集类)和CRecordView(可视记录集类)。 
	
	　　 CDatabase类对象提供了对数据源的连接,通过它可以对数据源进行操作。 
	
	　　 CRecordSet类对象提供了从数据源中提取出的记录集。CRecordSet对象通常用于两种形式:动态行
	
	集(dynasets)和快照集(snapshots)。动态行集能与其他用户所做的更改保持同步,快照集则是数据的一
	
	个静态视图。每种形式在记录集被打开时都提供一组记录,所不同的是,当在一个动态行集里滚动到一条
	
	记录时,由其他用户或应用程序中的其他记录集对该记录所做的更改会相应地显示出来。 
	
	　　 CRecordView类对象能以控件的形式显示数据库记录,这个视图是直接连到一个CRecordSet对象的表
	
	视图。 
	
	　　 二、应用ODBC编程 
	
	　　 应用Visual C＋＋的AppWizard可以自动生成一个ODBC应用程序框架,步骤是:打开File菜单的New选
	
	项,选取Projects,填入工程名,选择MFC AppWizard (exe),然后按AppWizard的提示进行操作。 
	
	　　 当AppWizard询问是否包含数据库支持时,如果想读写数据库,那么选定Database view with file 
	
	support;如果想访问数据库的信息而不想写回所做的改变,那么选定Database view without file 
	
	support。 
	
	　　 选好数据库支持之后,Database Source 按钮会被激活,选中它去调用Data Options对话框。在
	
	Database Options对话框中会显示出已向ODBC注册的数据库资源,选定所要操作的数据库,如:Super_ES,
	
	单击OK后出现Select Database Tables对话框,其中列举了选中的数据库包含的全部表;选择要操作的表
	
	后,单击OK。在选定了数据库和数据表之后,就可以按照惯例继续进行AppWizard操作。 
	
	　　 特别需要指出的是:在生成的应用程序框架View类(如:CSuper_ESView)中,包含一个指向
	
	CSuper_ESSet对象的指针m_pSet,该指针由AppWizard建立,目的是在视表单和记录集之间建立联系,使得
	
	记录集中的查询结果能够很容易地在视表单上显示出来。 
	
	　　 要使程序与数据源建立联系,需用CDateBase::OpenEx()或CDatabase::Open()函数来进行初始化。
	
	数据库对象必须在使用它构造记录集对象之前初始化。 
	
	三、实例 
	
	　　 1.查询记录 
	
	　　 查询记录使用CRecordSet::Open()和CRecordSet::Requery()成员函数。在使用CRecordSet类对象
	
	之前,必须使用CRecordSet::Open()函数来获得有效的记录集。一旦已经使用过CRecordSet::Open()函数
	
	,再次查询时就可以应用CRecordSet::Requery()函数。 
	
	　　 在调用CRecordSet::Open()函数时,如果将一个已经打开的CDatabase对象指针传给CRecordSet类对
	
	象的m_pDatabase成员变量,则使用该数据库对象建立ODBC连接;否则如果m_pDatabase为空指针,就新建一
	
	个CDatabase类对象,并使其与缺省的数据源相连,然后进行CRecordSet类对象的初始化。缺省数据源由
	
	GetDefaultConnect()函数获得。也可以提供所需要的SQL语句,并以它来调用CRecordSet::Open()函数,
	
	例如:Super_ESSet.Open(AFX_DATABASE_USE_DEFAULT,strSQL); 
	
	　　 如果没有指定参数,程序则使用缺省的SQL语句,即对在GetDefaultSQL()函数中指定的SQL语句进行
	
	操作: 
	
	　　 CString CSuper_ESSet::GetDefaultSQL() 
	　　 {return _T(″[BsicData],[MinSize]″);} 
	
	　　 对于GetDefaultSQL()函数返回的表名,对应的缺省操作是SELECT语句,即: 
	
	　　 SELECT *FROM BasicData,MainSize 
	
	　　 在查询过程中,也可以利用CRecordSet的成员变量m_strFilter和m_strSort来执行条件查询和结果
	
	排序。m_strFilter为过滤字符串,存放着SQL语句中WHERE后的条件串;m_strSort为排序字符串,存放着
	
	SQL语句中ORDER BY后的字符串。如: 
	
	　　 Super_ESSet.m_strFilter=″TYPE=‘电动机'″; 
	　　 Super_ESSet.m_strSort=″VOLTAGE″; 
	　　 Super_ESSet.Requery(); 
	
	　　 对应的SQL语句为: 
	
	　　 SELECT *FROM BasicData,MainSize 
	　　 WHERE TYPE=‘电动机' 
	　　 ORDER BY VOLTAGE 
	
	　　 除了直接赋值给m_strFilter以外,还可以使用参数化。利用参数化可以更直观、更方便地完成条件
	
	查询任务。使用参数化的步骤如下: 
	
	　　 S声明参变量: 
	
	 
	
	　　 CString p1; 
	　　 float p2; 
	
	　　 S在构造函数中初始化参变量: 
	
	　　 p1=_T(″″); 
	　　 p2=0.0f; 
	　　 m_nParams=2; 
	
	　　 S将参变量与对应列绑定: 
	
	　　 pFX－>SetFieldType(CFieldExchange::param) 
	
	　　 RFX_Text(pFX,_T(″P1″),p1); 
	　　 RFX_Single(pFX,_T(″P2″),p2); 
	
	　　 完成以上步骤后就可以利用参变量进行条件查询: 
	
	　　 m_pSet－>m_strFilter=″TYPE=? AND VOLTAGE=?″;m_pSet－>p1=″电动机″; 
	　　 m_pSet－>p2=60.0; 
	　　 m_pSet－>Requery(); 
	
	　　 参变量的值按绑定的顺序替换查询字串中的“?”通配符。 
	
	　　 如果查询的结果是多条记录,可以用CRecordSet类的函数Move()、MoveNext()、MovePrev()、
	
	MoveFirst()和MoveLast()来移动光标。 
	
	　　 2.增加记录 
	
	　　 增加记录使用AddNew()函数,要求数据库必须是以允许增加的方式打开: 
	
	　　 m_pSet－>AddNew(); //在表的末尾增加新记录 
	　　 m_pSet－>SetFieldNull(＆(m_pSet－>m_type), FALSE); 
	　　 m_pSet－>m_type=″电动机″; 
	　　 …… 
	　　 //输入新的字段值 
	　　 m_pSet－>Update(); 
	　　 //将新记录存入数据库 
	　　 m_pSet－>Requery(); 
	　　 //重建记录集 
	
	　　 3.删除记录 
	
	　　 可以直接使用Delete()函数来删除记录,并且在调用Delete()函数之后不需调用Update()函数: 
	
	　　 m_pSet－>Delete(); 
	　　 if (!m_pSet－>IsEOF()) 
	　　 m_pSet－>MoveNext(); 
	　　 else 
	　　 m_pSet－>MoveLast(); 
	
	　　 4.修改记录 
	
	　　 修改记录使用Edit()函数: 
	
	　　 m_pSet－>Edit(); 
	　　 //修改当前记录 
	　　 m_pSet－>m_type=″发电机″; 
	　　 //修改当前记录字段值 
	　　 …… 
	　　 m_pSet－>Update(); //将修改结果存入数据库 
	　　 m_pSet－>Requery(); 
	
	　　 5.撤消操作 
	
	　　 如果用户选择了增加或者修改记录后希望放弃当前操作,可以在调用Update()函数之前调用: 
	
	　　 CRecordSet::Move(AFX_MOVE_REFRESH)来撤消增加或修改模式,并恢复在增加或修改模式之前的当
	
	前记录。其中,参数AFX_MOVE_REFRESH的值为零。 
	
	　　 6.数据库连接的复用 
	
	　　 在CRecordSet类中定义了一个成员变量m_pDatabase: 
	
	　　 CDatabase* m_pDatabase; 
	
	　　 它是指向对象数据库类的指针。如果在CRecordSet类对象调用Open()函数之前,将一个已经打开的
	
	CDatabase类对象指针传给m_pDatabase,就能共享相同的CDatabase类对象。如: 
	
	　　 CDatabase m_db; 
	　　 CRecordSet m_set1,m_set2; 
	　　 m_db.Open(_T(″Super_ES″)); //建立ODBC连接 
	　　 m_set1.m_pDatabase=＆m_db; 
	　　 //m_set1复用m_db对象 
	　　 m_set2.m_pDatabse=＆m_db; 
	　　 // m_set2复用m_db对象 
	
	　　 7.SQL语句的直接执行 
	
	　　 虽然我们可以通过CRecordSet类完成大多数的查询操作,而且在CRecordSet::Open()函数中也可以
	
	提供SQL语句,但是有时候我们还是希望进行一些其他操作,例如建立新表、删除表、建立新的字段等,这
	
	时就需要使用CDatabase类直接执行SQL语句的机制。通过调用CDatabase::ExecuteSQL()函数来完成SQL
	
	语句的直接执行: 
	
	　　 BOOL CDB::ExecuteSQLAndReportFailure(const CString＆ strSQL) 
	　　 {TRY 
	　　 {m_pdb－>ExecuteSQL(strSQL); 
	　　 //直接执行SQL语句} 
	　　 CATCH (CDBException,e) 
	　　 {CString strMsg; 
	　　 strMsg.LoadString(IDS_EXECUTE_SQL_FAILED); 
	　　 strMsg＋=strSQL; 
	　　 return FALSE;} 
	　　 END_CATCH 
	　　 return TRUE;} 
	
	　　 应当指出的是,由于不同的DBMS提供的数据操作语句不尽相同,直接执行SQL语句可能会破坏软件的
	
	DBMS无关性,因此在应用中应当慎用此类操作。 
	
	　　 8.动态连接表 
	
	　　 表的动态连接可以利用在调用CRecordSet::Open()函数时指定SQL语句来实现。同一个记录集对象
	
	只能访问具有相同结构的表,否则查询结果将无法与变量相对应。 
	
	　　 void CDB::ChangeTable() 
	　　 { 
	　　 if (m_pSet－>IsOpen()) m_pSet－>Close(); 
	　　 switch (m_id) 
	　　 { 
	　　 case 0: 
	　　 m_pSet－>Open(AFX_DB_USE_DEFAULT_TYPE, 
	　　 ″SELECT ＊ FROM SLOT0″); 
	　　 //连接表SLOT0 
	　　 m_id=1; 
	　　 break; 
	　　 case 1: 
	　　 m_pSet－>Open(AFX_DB_USE_DEFAULT_TYPE, 
	　　 ″SELECT * FROM SLOT1″); //连接表SLOT1 
	　　 m_id=0; 
	　　 break; }} 
	
	　　 9.动态连接数据库 
	
	　　 可以通过赋与CRecordSet类对象参数m_pDatabase来连接不同数据库的CDatabase对象指针,从而实
	
	现动态连接数据库。 
	
	　　 void CDB::ChangeConnect() 
	　　 {CDatabase* pdb=m_pSet－>m_pDatabase; 
	　　 pdb－>Close(); 
	　　 switch (m_id) 
	　　 { 
	　　 case 0: 
	　　 if (!pdb－>Open(_T(″Super_ES″))) 
	　　 //连接数据源Super_ES 
	　　 { 
	　　 AfxMessageBox(″数据源Super_ES打开失败″,″请检查相应的ODBC连接″, 
	
	MB_OK|MB_ICONWARNING); 
	　　 exit(0); 
	　　 } 
	　　 m_id=1; 
	　　 break; 
	　　 case 1: 
	　　 if (!pdb－>Open(_T(″Motor″))) 
	　　 //连接数据源Motor 
	　　 { 
	　　 AfxMessageBox(″数据源Motor打开失败″,″请检查相应的ODBC连接″, MB_OK|MB_ICONWARNING); 
	　　 exit(0); 
	　　 } 
	　　 m_id=0; 
	　　 break; }} 
	
	　　 总结：Visual C＋＋中的ODBC类库可以帮助程序员完成绝大多数的数据库操作。利用ODBC技术使得
	
	程序员从具体的DBMS中解脱出来,从而可以减少软件开发的工作量,缩短开发周期,并提高效率和软件的可
	
	靠性。
} 
