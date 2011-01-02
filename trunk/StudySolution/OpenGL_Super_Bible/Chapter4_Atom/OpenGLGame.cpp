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

	LightAmbient[0] = LightAmbient[1] = LightAmbient[2] = 0.5;
	LightAmbient[3] = 1.0;

	for ( int i = 0; i < 4; ++i )
	{
		LightDiffuse[i] = 1.0;
	}

	LightPosition[0] = LightPosition[1] = 0.5;
	LightPosition[2] = 2.0;
	LightPosition[3] = 1.0;

	xrot = yrot = xspeed = yspeed = 0;

	memset( texture, 0, sizeof( texture ) );

	m_nFilterIndex = 0;

	m_bLightOn = false;

    z = -5.0f;
}

bool OpenGLGame::update()
{
	if ( !isActive() )						// ���򼤻��ô?
	{
		return true;
	}

	if ( isKeyPressed( VK_ESCAPE ) )				// ESC ������ô?
	{
		return false;				// ESC �����˳��ź�
	}

	// �����˳���ʱ��ˢ����Ļ
	drawGLScene();				// ���Ƴ���
	::SwapBuffers( m_hDC );			// �������� (˫����)

	processKeyEvent();

	if ( isKeyPressed( VK_F1 ) )					// F1��������ô?
	{
		onKeyReleased( VK_F1 );			// ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE
		killGLWindow();					// ���ٵ�ǰ�Ĵ���
		m_bFullScreen = !m_bFullScreen; // �л� ȫ�� / ���� ģʽ

		// �ؽ� OpenGL ����
		if ( !createGLWindow() )
		{
			return false;				// �������δ�ܴ����������˳�
		}
	}

	return true;
}



int OpenGLGame::drawGLScene( GLvoid ) /* �����￪ʼ�������е� ��?*/
{

	// Clear The Screen And The Depth Buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity(); // Reset The View
	glTranslatef( 0.0f, 0.0f, -100 ); 
    static GLfloat fElect1 = 0.0f;

    //ԭ�Ӻ�
    glColor3ub( 255, 0, 0 );
    glutSolidSphere( 10, 15, 15 );

    //��һ������
    glPushMatrix();
    glColor3ub( 255, 255, 0 );
    glRotatef( fElect1, 0, 1, 0 );
    glTranslatef( 20, 0, 0 );
    glutSolidSphere( 3, 15, 15 );
    glPopMatrix();


    //��һ������
    glPushMatrix();
    glColor3ub( 255, 255, 0 );
    glRotatef( 45, 0, 0, 1 );
    glRotatef( fElect1, 0, 1, 0 );
    glTranslatef( -35, 0, 0 );
    glutSolidSphere( 3, 15, 15 );
    glPopMatrix();



    //��һ������
    glPushMatrix();
    glColor3ub( 255, 255, 0 );
    glRotatef( 45, 1, 0, 0 );
    glRotatef( fElect1, 0, 1, 0 );
    glTranslatef( -25, 0, 0 );
    glutSolidSphere( 3, 15, 15 );
    glPopMatrix();

    fElect1 += 0.1;
    if ( fElect1 >= 360 )
    {
        fElect1 = 0;
    }
    
    
    return TRUE;								//  һ�� OK
}

LRESULT CALLBACK OpenGLGame::wndProc(	HWND	hWnd,					// ���ڵľ��
                                        UINT	uMsg,					// ���ڵ���Ϣ
                                        WPARAM	wParam,					// ���ӵ���Ϣ����
                                        LPARAM	lParam )					// ���ӵ���Ϣ����
{
	OpenGLGame* pOpenGLGame = getOpenGLGame();

	switch ( uMsg )								// ���Windows��Ϣ
	{
		case WM_ACTIVATE:						// ���Ӵ��ڼ�����Ϣ
			{
				if ( !HIWORD( wParam ) )					// �����С��״̬
				{
					s_pOpenGLGame->setActive( TRUE );					// �����ڼ���״̬
				}
				else
				{
					s_pOpenGLGame->setActive( FALSE );					// �����ټ���
				}

				return 0;						// ������Ϣѭ��
			}
		case WM_SYSCOMMAND:						// ϵͳ�ж�����
			{
				switch ( wParam )						// ���ϵͳ����
				{
					case SC_SCREENSAVE:				// ����Ҫ����?
					case SC_MONITORPOWER:				// ��ʾ��Ҫ����ڵ�ģʽ?
						return 0;					// ��ֹ����
				}

				break;							// �˳�
			}
		case WM_CLOSE:							// �յ�Close��Ϣ?
			{
				PostQuitMessage( 0 );					// �����˳���Ϣ
				return 0;						// ����
			}
		case WM_KEYDOWN:						// �м�����ô?
			{
				s_pOpenGLGame->onKeyPressed( wParam ) ;					// ����ǣ���ΪTRUE
				return 0;						// ����
			}
		case WM_KEYUP:							// �м��ſ�ô?
			{
				s_pOpenGLGame->onKeyReleased( wParam ) ;						// ����ǣ���ΪFALSE
				return 0;						// ����
			}
		case WM_SIZE:							// ����OpenGL���ڴ�С
			{
				s_pOpenGLGame->resizeGLScene( LOWORD( lParam ), HIWORD( lParam ) );		// LoWord=Width,HiWord=Height
				return 0;						// ����
			}
	}

	// �� DefWindowProc��������δ�������Ϣ��
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

BOOL OpenGLGame::createGLWindow()
{
	GLuint		PixelFormat;						// �������ƥ��Ľ��
	WNDCLASS	wc;							// ������ṹ
	DWORD		dwExStyle;						// ��չ���ڷ��
	DWORD		dwStyle;						// ���ڷ��

	RECT WindowRect;							// ȡ�þ��ε����ϽǺ����½ǵ�����ֵ
	WindowRect.left = ( long )0;						// ��Left   ��Ϊ 0
	WindowRect.right = ( long )m_nWidth;						// ��Right  ��ΪҪ��Ŀ��
	WindowRect.top = ( long )0;							// ��Top    ��Ϊ 0
	WindowRect.bottom = ( long )m_nHeight;						// ��Bottom ��ΪҪ��ĸ߶�

	m_hInstance		= GetModuleHandle( NULL );			// ȡ�����Ǵ��ڵ�ʵ��
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// �ƶ�ʱ�ػ�����Ϊ����ȡ��DC
	wc.lpfnWndProc		= ( WNDPROC ) &OpenGLGame::wndProc;				// WndProc������Ϣ
	wc.cbClsExtra		= 0;						// �޶��ⴰ������
	wc.cbWndExtra		= 0;						// �޶��ⴰ������
	wc.hInstance		= m_hInstance;					// ����ʵ��
	wc.hIcon		= LoadIcon( NULL, IDI_WINLOGO );			// װ��ȱʡͼ��
	wc.hCursor		= LoadCursor( NULL, IDC_ARROW );			// װ�����ָ��
	wc.hbrBackground	= NULL;						// GL����Ҫ����
	wc.lpszMenuName		= NULL;						// ����Ҫ�˵�
	wc.lpszClassName	= "OpenG";					// �趨������


	if ( !RegisterClass( &wc ) )						// ����ע�ᴰ����
	{
		MessageBox( NULL, "ע�ᴰ��ʧ��", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// �˳�������FALSE
	}

	if ( m_bFullScreen )								// Ҫ����ȫ��ģʽ��?
	{
		DEVMODE dmScreenSettings;						// �豸ģʽ
		memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );			// ȷ���ڴ����Ϊ��
		dmScreenSettings.dmSize = sizeof( dmScreenSettings );			// Devmode �ṹ�Ĵ�С
		dmScreenSettings.dmPelsWidth	= m_nWidth;				// ��ѡ��Ļ���
		dmScreenSettings.dmPelsHeight	= m_nHeight;				// ��ѡ��Ļ�߶�
		dmScreenSettings.dmBitsPerPel	= m_nBitMode;					// ÿ������ѡ��ɫ�����
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;



		// ����������ʾģʽ�����ؽ����ע: CDS_FULLSCREEN ��ȥ��״̬����
		if ( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
		{
			// ��ģʽʧ�ܣ��ṩ����ѡ��˳����ڴ��������С�
			if ( MessageBox( NULL, "ȫ��ģʽ�ڵ�ǰ�Կ�������ʧ�ܣ�\nʹ�ô���ģʽ��", "G", MB_YESNO | MB_ICONEXCLAMATION ) == IDYES )
			{
				m_bFullScreen = FALSE;				// ѡ�񴰿�ģʽ(Fullscreen=FALSE)
			}
			else
			{
				// ����һ���Ի��򣬸����û��������
				MessageBox( NULL, "���򽫱��ر�", "����", MB_OK | MB_ICONSTOP );
				return FALSE;					//  �˳������� FALSE
			}
		}
	}


	if ( m_bFullScreen )								// �Դ���ȫ��ģʽ��?
	{
		dwExStyle = WS_EX_APPWINDOW;					// ��չ������
		dwStyle = WS_POPUP;						// ������
		ShowCursor( FALSE );						// �������ָ��
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// ��չ������
		dwStyle = WS_OVERLAPPEDWINDOW;					//  ������
	}

	AdjustWindowRectEx( &WindowRect, dwStyle, FALSE, dwExStyle );		// �������ڴﵽ����Ҫ��Ĵ�С

	if ( !( m_hWnd = CreateWindowEx(	dwExStyle,				// ��չ������
	                                    "OpenG",				// ������
	                                    m_szTitle,					// ���ڱ���
	                                    WS_CLIPSIBLINGS |			// ����Ĵ���������
	                                    WS_CLIPCHILDREN |			// ����Ĵ���������
	                                    dwStyle,				// ѡ��Ĵ�������
	                                    0, 0,					// ����λ��
	                                    WindowRect.right - WindowRect.left,	// ��������õĴ��ڿ��
	                                    WindowRect.bottom - WindowRect.top,	// ��������õĴ��ڸ߶�
	                                    NULL,					// �޸�����
	                                    NULL,					// �޲˵�
	                                    m_hInstance,				// ʵ��
	                                    NULL ) ) )					// ����WM_CREATE�����κζ���
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "���ܴ���һ�������豸������", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =					// /pfd ���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ
	{
		sizeof( PIXELFORMATDESCRIPTOR ),					// ������ʽ�������Ĵ�С
		1,								// �汾��
		PFD_DRAW_TO_WINDOW |						// ��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL |						// ��ʽ����֧��OpenGL
		PFD_DOUBLEBUFFER,						// ����֧��˫����
		PFD_TYPE_RGBA,							// ���� RGBA ��ʽ
		m_nBitMode,								// ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,						// ���Ե�ɫ��λ
		0,								// ��Alpha����
		0,								// ����Shift Bit
		0,								// ���ۼӻ���
		0, 0, 0, 0,							// ���Ծۼ�λ
		16,								// 16λ Z-���� (��Ȼ���)
		0,								// ���ɰ建��
		0,								// �޸�������
		PFD_MAIN_PLANE,							// ����ͼ��
		0,								// Reserved
		0, 0, 0								// ���Բ�����
	};


	if ( !( m_hDC = GetDC( m_hWnd ) ) )							// ȡ���豸��������ô?
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "���ܴ���һ����ƥ������ظ�ʽ", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}

	if ( !( PixelFormat = ChoosePixelFormat( m_hDC, &pfd ) ) )				// Windows �ҵ���Ӧ�����ظ�ʽ����?
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "�����������ظ�ʽ", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}

	if( !SetPixelFormat( m_hDC, PixelFormat, &pfd ) )				// �ܹ��������ظ�ʽô?
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "�����������ظ�ʽ", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}


	if ( !( m_hRC = wglCreateContext( m_hDC ) ) )					// �ܷ�ȡ����ɫ������?
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "���ܴ���OpenGL��Ⱦ������", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}

	if( !wglMakeCurrent( m_hDC, m_hRC ) )						// ���Լ�����ɫ������
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "���ܼ��ǰ��OpenGL��Ȼ������", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}

	ShowWindow( m_hWnd, SW_SHOW );						// ��ʾ����
	SetForegroundWindow( m_hWnd );						// ����������ȼ�
	SetFocus( m_hWnd );								// ���ü��̵Ľ������˴���
	resizeGLScene( m_nWidth, m_nHeight );						// ����͸�� GL ��Ļ


	if ( !initGL() )								// ��ʼ���½���GL����
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}


	return TRUE;								// �ɹ�
}

GLvoid OpenGLGame::killGLWindow( GLvoid ) /* ������ ٴ��?*/
{
	if ( m_bFullScreen )								// ���Ǵ���ȫ��ģʽ��?
	{
		ChangeDisplaySettings( NULL, 0 );					// �ǵĻ����л�������
		ShowCursor( TRUE );						// ��ʾ���ָ��
	}

	if ( m_hRC )								// ����ӵ��OpenGL��Ⱦ��������?
	{
		if ( !wglMakeCurrent( NULL, NULL ) )					// �����ܷ��ͷ�DC��RC������?
		{
			MessageBox( NULL, "�ͷ�DC��RCʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION );
		}

		if ( !wglDeleteContext( m_hRC ) )					// �����ܷ�ɾ��RC?
		{
			MessageBox( NULL, "�ͷ�RCʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION );
		}

		m_hRC = NULL;							// ��RC��Ϊ NULL
	}

	if ( m_hDC && !ReleaseDC( m_hWnd, m_hDC ) )					// �����ܷ��ͷ� DC?
	{
		MessageBox( NULL, "�ͷ�DCʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION );
		m_hDC = NULL;							// �� DC ��Ϊ NULL
	}

	if ( m_hWnd && !DestroyWindow( m_hWnd ) )					// �ܷ����ٴ���?
	{
		MessageBox( NULL, "�ͷŴ��ھ��ʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION );
		m_hWnd = NULL;							// �� hWnd ��Ϊ NULL
	}

	if ( !UnregisterClass( "OpenG", m_hInstance ) )				// �ܷ�ע����?
	{
		MessageBox( NULL, "����ע�������ࡣ", "�رմ���", MB_OK | MB_ICONINFORMATION );
		m_hInstance = NULL;							// �� hInstance ��Ϊ NULL
	}
}

int OpenGLGame::initGL( GLvoid ) /* �˴���ʼ��OpenGL������������ */
{
	glEnable( GL_TEXTURE_2D ); // Enable Texture Mapping ( NEW )
	glShadeModel( GL_SMOOTH ); // Enable Smooth Shading
	glClearColor( 0.0f, 0.0f, 0.0f, 0.5f ); // Black Background
	glClearDepth( 1.0f ); // Depth Buffer Setup
	glEnable( GL_DEPTH_TEST ); // Enables Depth Testing
	glDepthFunc( GL_LEQUAL ); // The Type Of Depth Testing To Do
	// Really Nice Perspective Calculations
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );


	glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient ); // ���û�����
	glLightfv( GL_LIGHT1, GL_DIFFUSE, LightDiffuse ); // ���������
	glLightfv( GL_LIGHT1, GL_POSITION, LightPosition ); // ���ù�Դλ��
	glEnable( GL_LIGHT1 ); // ����һ�Ź�Դ
 //   glEnable( GL_LIGHTING ); // ���ù�Դ


	return TRUE; // Initialization Went OK
}

GLvoid OpenGLGame::resizeGLScene( GLsizei width, GLsizei height )
{
	if ( height == 0 ) // Prevent A Divide By Zero By
	{
		height = 1; // Making Height Equal One
	}

	glViewport( 0, 0, width, height ); // Reset The Current Viewport

	//ͶӰ������Ϊ���ǵĳ�������͸�ӹ��ܣ���ζ��ԽԶ�Ķ���������ԽС��
	glMatrixMode( GL_PROJECTION );				// ѡ��ͶӰ����
	glLoadIdentity();							// ����ͶӰ����

	// �����ӿڵĴ�С
	gluPerspective( 45.0f, ( GLfloat )width / ( GLfloat )height, 0.1f, 1000.0f );

	//ģ�͹۲�������������ǵ�������Ϣ
	glMatrixMode( GL_MODELVIEW );						// ѡ��ģ�͹۲����
	glLoadIdentity();							// ����ģ�͹۲����
}


void OpenGLGame::onKeyPressed( char key )
{
	m_vbPressKeys[key] = true;
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

bool OpenGLGame::isKeyPressed( char key )
{
	return m_vbPressKeys[key];
}

void OpenGLGame::onKeyReleased( char key )
{
	m_vbPressKeys[key] = false;
}


bool OpenGLGame::processKeyEvent()
{
	//light
	if ( isKeyPressed( 'L' ) || isKeyPressed( 'l' ) )
	{
		onKeyReleased( 'L' );
		onKeyReleased( 'l' );

		m_bLightOn = !m_bLightOn;

		if ( m_bLightOn )
		{
			glEnable( GL_LIGHTING ); // ���ù�Դ
		}
		else
		{
			glDisable( GL_LIGHTING ); // ���ù�Դ
		}
	}

	//filter
	if ( isKeyPressed( 'F' ) || isKeyPressed( 'f' ) )
	{
		onKeyReleased( 'F' );
		onKeyReleased( 'f' );

		++m_nFilterIndex;

		if ( m_nFilterIndex > 2 )
		{
			m_nFilterIndex = 0;
		}
	}


	if ( isKeyPressed( VK_PRIOR ) ) // PageUp������?
	{
		onKeyReleased( VK_PRIOR );
		z -= 0.2f; // �����£���ľ��������Ļ�ڲ�
	}

	if ( isKeyPressed( VK_NEXT ) ) // PageDown������ô
	{
		onKeyReleased( VK_NEXT );
		z += 0.2f; // �����µĻ�����ľ������۲���
	}

	if ( isKeyPressed( VK_UP ) ) // Up�����������ô?
	{
		onKeyReleased( VK_UP );
		xspeed -= 0.01f; // ����,����xspeed
	}

	if ( isKeyPressed( VK_DOWN ) ) // Down�����������ô?
	{
		onKeyReleased( VK_DOWN );
		xspeed += 0.01f; // ����,����xspeed
	}

	if ( isKeyPressed( VK_RIGHT ) ) // Right�����������ô?
	{
		onKeyReleased( VK_RIGHT );
		yspeed -= 0.01f; // ����,����yspeed
	}

	if ( isKeyPressed( VK_LEFT ) ) // Left�����������ô?
	{
		onKeyReleased( VK_LEFT );
		yspeed += 0.01f; // ����, ����yspeed
	}

	return true;
}