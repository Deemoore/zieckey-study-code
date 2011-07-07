#include "OpenGLGame.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")



OpenGLGame::OpenGLGame( const char* szWindowTitle /*= NULL*/, GLsizei width /*= 640*/, GLsizei height /*= 480*/, GLsizei bitmode /*= 16 */ )
	: m_szTitle( szWindowTitle )
{
	m_nWidth = width;
	m_nHeight = height;
	m_nBitMode = bitmode;

	m_hRC = NULL;
	m_hDC = NULL;
	m_hWnd = NULL;
	m_hInstance = NULL;

	memset( m_vbPressKeys, 0, sizeof( m_vbPressKeys ) );
	m_bActive = true;
	m_bFullScreen = false;

    xRot = yRot = 0;
}

bool OpenGLGame::update()
{
	if ( !isActive() )						// 程序激活的么?
	{
		return true;
	}

	if ( isKeyPressed( VK_ESCAPE ) )				// ESC 按下了么?
	{
		return false;				// ESC 发出退出信号
	}

	// 不是退出的时候，刷新屏幕
	drawGLScene();				// 绘制场景
	::SwapBuffers( m_hDC );			// 交换缓存 (双缓存)

	if ( isKeyPressed( VK_F1 ) )					// F1键按下了么?
	{
		onKeyReleased( VK_F1 );			// 若是，使对应的Key数组中的值为 FALSE
		killGLWindow();					// 销毁当前的窗口
		m_bFullScreen = !m_bFullScreen; // 切换 全屏 / 窗口 模式

		// 重建 OpenGL 窗口
		if ( !createGLWindow() )
		{
			return false;				// 如果窗口未能创建，程序退出
		}
	}

	return true;
}



int OpenGLGame::drawGLScene( GLvoid )
{

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Save matrix state and do the rotation
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);


    // Nose Cone /////////////////////////////
    // White
    glColor3ub(255, 255, 255);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 0.0f, 60.0f);
    glVertex3f(-15.0f, 0.0f, 30.0f);
    glVertex3f(15.0f,0.0f,30.0f);

    // Black
    glColor3ub(0,0,0);
    glVertex3f(15.0f,0.0f,30.0f);
    glVertex3f(0.0f, 15.0f, 30.0f);
    glVertex3f(0.0f, 0.0f, 60.0f);

    // Red
    glColor3ub(255,0,0);
    glVertex3f(0.0f, 0.0f, 60.0f);
    glVertex3f(0.0f, 15.0f, 30.0f);
    glVertex3f(-15.0f,0.0f,30.0f);


    // Body of the Plane ////////////////////////
    // Green
    glColor3ub(0,255,0);
    glVertex3f(-15.0f,0.0f,30.0f);
    glVertex3f(0.0f, 15.0f, 30.0f);
    glVertex3f(0.0f, 0.0f, -56.0f);

    glColor3ub(255,255,0);
    glVertex3f(0.0f, 0.0f, -56.0f);
    glVertex3f(0.0f, 15.0f, 30.0f);
    glVertex3f(15.0f,0.0f,30.0f);	

    glColor3ub(0, 255, 255);
    glVertex3f(15.0f,0.0f,30.0f);
    glVertex3f(-15.0f, 0.0f, 30.0f);
    glVertex3f(0.0f, 0.0f, -56.0f);

    ///////////////////////////////////////////////
    // Left wing
    // Large triangle for bottom of wing
    glColor3ub(128,128,128);
    glVertex3f(0.0f,2.0f,27.0f);
    glVertex3f(-60.0f, 2.0f, -8.0f);
    glVertex3f(60.0f, 2.0f, -8.0f);

    glColor3ub(64,64,64);
    glVertex3f(60.0f, 2.0f, -8.0f);
    glVertex3f(0.0f, 7.0f, -8.0f);
    glVertex3f(0.0f,2.0f,27.0f);

    glColor3ub(192,192,192);
    glVertex3f(60.0f, 2.0f, -8.0f);
    glVertex3f(-60.0f, 2.0f, -8.0f);
    glVertex3f(0.0f,7.0f,-8.0f);

    // Other wing top section
    glColor3ub(64,64,64);
    glVertex3f(0.0f,2.0f,27.0f);
    glVertex3f(0.0f, 7.0f, -8.0f);
    glVertex3f(-60.0f, 2.0f, -8.0f);

    // Tail section///////////////////////////////
    // Bottom of back fin
    glColor3ub(255,128,255);
    glVertex3f(-30.0f, -0.50f, -57.0f);
    glVertex3f(30.0f, -0.50f, -57.0f);
    glVertex3f(0.0f,-0.50f,-40.0f);

    // top of left side
    glColor3ub(255,128,0);
    glVertex3f(0.0f,-0.5f,-40.0f);
    glVertex3f(30.0f, -0.5f, -57.0f);
    glVertex3f(0.0f, 4.0f, -57.0f);

    // top of right side
    glColor3ub(255,128,0);
    glVertex3f(0.0f, 4.0f, -57.0f);
    glVertex3f(-30.0f, -0.5f, -57.0f);
    glVertex3f(0.0f,-0.5f,-40.0f);

    // back of bottom of tail
    glColor3ub(255,255,255);
    glVertex3f(30.0f,-0.5f,-57.0f);
    glVertex3f(-30.0f, -0.5f, -57.0f);
    glVertex3f(0.0f, 4.0f, -57.0f);

    // Top of Tail section left
    glColor3ub(255,0,0);
    glVertex3f(0.0f,0.5f,-40.0f);
    glVertex3f(3.0f, 0.5f, -57.0f);
    glVertex3f(0.0f, 25.0f, -65.0f);

    glColor3ub(255,0,0);
    glVertex3f(0.0f, 25.0f, -65.0f);
    glVertex3f(-3.0f, 0.5f, -57.0f);
    glVertex3f(0.0f,0.5f,-40.0f);

    // Back of horizontal section
    glColor3ub(128,128,128);
    glVertex3f(3.0f,0.5f,-57.0f);
    glVertex3f(-3.0f, 0.5f, -57.0f);
    glVertex3f(0.0f, 25.0f, -65.0f);

    glEnd(); // Of Jet

    glPopMatrix();
    
    return TRUE;								//  一切 OK
}

LRESULT CALLBACK OpenGLGame::wndProc(	HWND	hWnd,					// 窗口的句柄
                                        UINT	uMsg,					// 窗口的消息
                                        WPARAM	wParam,					// 附加的消息内容
                                        LPARAM	lParam )					// 附加的消息内容
{
	OpenGLGame* pOpenGLGame = getOpenGLGame();

	switch ( uMsg )								// 检查Windows消息
	{
		case WM_ACTIVATE:						// 监视窗口激活消息
			{
				if ( !HIWORD( wParam ) )					// 检查最小化状态
				{
					s_pOpenGLGame->setActive( TRUE );					// 程序处于激活状态
				}
				else
				{
					s_pOpenGLGame->setActive( FALSE );					// 程序不再激活
				}

				return 0;						// 返回消息循环
			}
		case WM_SYSCOMMAND:						// 系统中断命令
			{
				switch ( wParam )						// 检查系统调用
				{
					case SC_SCREENSAVE:				// 屏保要运行?
					case SC_MONITORPOWER:				// 显示器要进入节电模式?
						return 0;					// 阻止发生
				}

				break;							// 退出
			}
		case WM_CLOSE:							// 收到Close消息?
			{
				PostQuitMessage( 0 );					// 发出退出消息
				return 0;						// 返回
			}
		case WM_KEYDOWN:						// 有键按下么?
			{
				s_pOpenGLGame->onKeyPressed( wParam ) ;					// 如果是，设为TRUE
				return 0;						// 返回
			}
		case WM_KEYUP:							// 有键放开么?
			{
				s_pOpenGLGame->onKeyReleased( wParam ) ;						// 如果是，设为FALSE
				return 0;						// 返回
			}
		case WM_SIZE:							// 调整OpenGL窗口大小
			{
				s_pOpenGLGame->resizeGLScene( LOWORD( lParam ), HIWORD( lParam ) );		// LoWord=Width,HiWord=Height
				return 0;						// 返回
			}
	}

	// 向 DefWindowProc传递所有未处理的消息。
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

BOOL OpenGLGame::createGLWindow()
{
	GLuint		PixelFormat;						// 保存查找匹配的结果
	WNDCLASS	wc;							// 窗口类结构
	DWORD		dwExStyle;						// 扩展窗口风格
	DWORD		dwStyle;						// 窗口风格

	RECT WindowRect;							// 取得矩形的左上角和右下角的坐标值
	WindowRect.left = ( long )0;						// 将Left   设为 0
	WindowRect.right = ( long )m_nWidth;						// 将Right  设为要求的宽度
	WindowRect.top = ( long )0;							// 将Top    设为 0
	WindowRect.bottom = ( long )m_nHeight;						// 将Bottom 设为要求的高度

	m_hInstance		= GetModuleHandle( NULL );			// 取得我们窗口的实例
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// 移动时重画，并为窗口取得DC
	wc.lpfnWndProc		= ( WNDPROC ) &OpenGLGame::wndProc;				// WndProc处理消息
	wc.cbClsExtra		= 0;						// 无额外窗口数据
	wc.cbWndExtra		= 0;						// 无额外窗口数据
	wc.hInstance		= m_hInstance;					// 设置实例
	wc.hIcon		= LoadIcon( NULL, IDI_WINLOGO );			// 装入缺省图标
	wc.hCursor		= LoadCursor( NULL, IDC_ARROW );			// 装入鼠标指针
	wc.hbrBackground	= NULL;						// GL不需要背景
	wc.lpszMenuName		= NULL;						// 不需要菜单
	wc.lpszClassName	= "OpenG";					// 设定类名字


	if ( !RegisterClass( &wc ) )						// 尝试注册窗口类
	{
		MessageBox( NULL, "注册窗口失败", "错误", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// 退出并返回FALSE
	}

	if ( m_bFullScreen )								// 要尝试全屏模式吗?
	{
		DEVMODE dmScreenSettings;						// 设备模式
		memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );			// 确保内存清空为零
		dmScreenSettings.dmSize = sizeof( dmScreenSettings );			// Devmode 结构的大小
		dmScreenSettings.dmPelsWidth	= m_nWidth;				// 所选屏幕宽度
		dmScreenSettings.dmPelsHeight	= m_nHeight;				// 所选屏幕高度
		dmScreenSettings.dmBitsPerPel	= m_nBitMode;					// 每象素所选的色彩深度
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;



		// 尝试设置显示模式并返回结果。注: CDS_FULLSCREEN 移去了状态条。
		if ( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
		{
			// 若模式失败，提供两个选项：退出或在窗口内运行。
			if ( MessageBox( NULL, "全屏模式在当前显卡上设置失败！\n使用窗口模式？", "G", MB_YESNO | MB_ICONEXCLAMATION ) == IDYES )
			{
				m_bFullScreen = FALSE;				// 选择窗口模式(Fullscreen=FALSE)
			}
			else
			{
				// 弹出一个对话框，告诉用户程序结束
				MessageBox( NULL, "程序将被关闭", "错误", MB_OK | MB_ICONSTOP );
				return FALSE;					//  退出并返回 FALSE
			}
		}
	}


	if ( m_bFullScreen )								// 仍处于全屏模式吗?
	{
		dwExStyle = WS_EX_APPWINDOW;					// 扩展窗体风格
		dwStyle = WS_POPUP;						// 窗体风格
		ShowCursor( FALSE );						// 隐藏鼠标指针
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// 扩展窗体风格
		dwStyle = WS_OVERLAPPEDWINDOW;					//  窗体风格
	}

	AdjustWindowRectEx( &WindowRect, dwStyle, FALSE, dwExStyle );		// 调整窗口达到真正要求的大小

	if ( !( m_hWnd = CreateWindowEx(	dwExStyle,				// 扩展窗体风格
	                                    "OpenG",				// 类名字
	                                    m_szTitle,					// 窗口标题
	                                    WS_CLIPSIBLINGS |			// 必须的窗体风格属性
	                                    WS_CLIPCHILDREN |			// 必须的窗体风格属性
	                                    dwStyle,				// 选择的窗体属性
	                                    0, 0,					// 窗口位置
	                                    WindowRect.right - WindowRect.left,	// 计算调整好的窗口宽度
	                                    WindowRect.bottom - WindowRect.top,	// 计算调整好的窗口高度
	                                    NULL,					// 无父窗口
	                                    NULL,					// 无菜单
	                                    m_hInstance,				// 实例
	                                    NULL ) ) )					// 不向WM_CREATE传递任何东东
	{
		killGLWindow();							// 重置显示区
		MessageBox( NULL, "不能创建一个窗口设备描述表", "错误", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// 返回 FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =					// /pfd 告诉窗口我们所希望的东东，即窗口使用的像素格式
	{
		sizeof( PIXELFORMATDESCRIPTOR ),					// 上述格式描述符的大小
		1,								// 版本号
		PFD_DRAW_TO_WINDOW |						// 格式支持窗口
		PFD_SUPPORT_OPENGL |						// 格式必须支持OpenGL
		PFD_DOUBLEBUFFER,						// 必须支持双缓冲
		PFD_TYPE_RGBA,							// 申请 RGBA 格式
		m_nBitMode,								// 选定色彩深度
		0, 0, 0, 0, 0, 0,						// 忽略的色彩位
		0,								// 无Alpha缓存
		0,								// 忽略Shift Bit
		0,								// 无累加缓存
		0, 0, 0, 0,							// 忽略聚集位
		16,								// 16位 Z-缓存 (深度缓存)
		0,								// 无蒙板缓存
		0,								// 无辅助缓存
		PFD_MAIN_PLANE,							// 主绘图层
		0,								// Reserved
		0, 0, 0								// 忽略层遮罩
	};


	if ( !( m_hDC = GetDC( m_hWnd ) ) )							// 取得设备描述表了么?
	{
		killGLWindow();							// 重置显示区
		MessageBox( NULL, "不能创建一种相匹配的像素格式", "错误", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// 返回 FALSE
	}

	if ( !( PixelFormat = ChoosePixelFormat( m_hDC, &pfd ) ) )				// Windows 找到相应的象素格式了吗?
	{
		killGLWindow();							// 重置显示区
		MessageBox( NULL, "不能设置像素格式", "错误", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// 返回 FALSE
	}

	if( !SetPixelFormat( m_hDC, PixelFormat, &pfd ) )				// 能够设置象素格式么?
	{
		killGLWindow();							// 重置显示区
		MessageBox( NULL, "不能设置像素格式", "错误", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// 返回 FALSE
	}


	if ( !( m_hRC = wglCreateContext( m_hDC ) ) )					// 能否取得着色描述表?
	{
		killGLWindow();							// 重置显示区
		MessageBox( NULL, "不能创建OpenGL渲染描述表", "错误", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// 返回 FALSE
	}

	if( !wglMakeCurrent( m_hDC, m_hRC ) )						// 尝试激活着色描述表
	{
		killGLWindow();							// 重置显示区
		MessageBox( NULL, "不能激活当前的OpenGL渲然描述表", "错误", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// 返回 FALSE
	}

	ShowWindow( m_hWnd, SW_SHOW );						// 显示窗口
	SetForegroundWindow( m_hWnd );						// 略略提高优先级
	SetFocus( m_hWnd );								// 设置键盘的焦点至此窗口
	resizeGLScene( m_nWidth, m_nHeight );						// 设置透视 GL 屏幕


	if ( !initGL() )								// 初始化新建的GL窗口
	{
		killGLWindow();							// 重置显示区
		MessageBox( NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// 返回 FALSE
	}


	return TRUE;								// 成功
}

GLvoid OpenGLGame::killGLWindow( GLvoid ) /* 正常销 俅翱?*/
{
	if ( m_bFullScreen )								// 我们处于全屏模式吗?
	{
		ChangeDisplaySettings( NULL, 0 );					// 是的话，切换回桌面
		ShowCursor( TRUE );						// 显示鼠标指针
	}

	if ( m_hRC )								// 我们拥有OpenGL渲染描述表吗?
	{
		if ( !wglMakeCurrent( NULL, NULL ) )					// 我们能否释放DC和RC描述表?
		{
			MessageBox( NULL, "释放DC或RC失败。", "关闭错误", MB_OK | MB_ICONINFORMATION );
		}

		if ( !wglDeleteContext( m_hRC ) )					// 我们能否删除RC?
		{
			MessageBox( NULL, "释放RC失败。", "关闭错误", MB_OK | MB_ICONINFORMATION );
		}

		m_hRC = NULL;							// 将RC设为 NULL
	}

	if ( m_hDC && !ReleaseDC( m_hWnd, m_hDC ) )					// 我们能否释放 DC?
	{
		MessageBox( NULL, "释放DC失败。", "关闭错误", MB_OK | MB_ICONINFORMATION );
		m_hDC = NULL;							// 将 DC 设为 NULL
	}

	if ( m_hWnd && !DestroyWindow( m_hWnd ) )					// 能否销毁窗口?
	{
		MessageBox( NULL, "释放窗口句柄失败。", "关闭错误", MB_OK | MB_ICONINFORMATION );
		m_hWnd = NULL;							// 将 hWnd 设为 NULL
	}

	if ( !UnregisterClass( "OpenG", m_hInstance ) )				// 能否注销类?
	{
		MessageBox( NULL, "不能注销窗口类。", "关闭错误", MB_OK | MB_ICONINFORMATION );
		m_hInstance = NULL;							// 将 hInstance 设为 NULL
	}
}

int OpenGLGame::initGL( GLvoid ) /* 此处开始对OpenGL进行所有设置 */
{
    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out

    // Nice light blue
    glClearColor(0.0f, 0.0f, 05.f,1.0f);

	return TRUE; // Initialization Went OK
}

GLvoid OpenGLGame::resizeGLScene( GLsizei w, GLsizei h )
{
	GLfloat nRange = 80.0f;
    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
        glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void OpenGLGame::onKeyPressed( char key )
{
    if(key == VK_UP)
        xRot-= 5.0f;

    if(key == VK_DOWN)
        xRot += 5.0f;

    if(key == VK_LEFT)
        yRot -= 5.0f;

    if(key == VK_RIGHT)
        yRot += 5.0f;

    if(key > 356.0f)
        xRot = 0.0f;

    if(key < -1.0f)
        xRot = 355.0f;

    if(key > 356.0f)
        yRot = 0.0f;

    if(key < -1.0f)
        yRot = 355.0f;
}

void OpenGLGame::onKeyReleased( char key )
{
    m_vbPressKeys[key] = false;
}

bool OpenGLGame::isKeyPressed( char key )
{
    return m_vbPressKeys[key];
}

void OpenGLGame::setFullScreen( bool bFullSceen )
{
	m_bFullScreen = bFullSceen;
}

bool OpenGLGame::isFullScreen() const
{
	return m_bFullScreen;
}

bool OpenGLGame::isActive() const
{
	return m_bActive;
}

void OpenGLGame::setActive( bool bActive )
{
    m_bActive = bActive;
}

void OpenGLGame::drawGround( void )
{
    
}


