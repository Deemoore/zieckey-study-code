#pragma once

#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

class OpenGLGame
{
public:
	OpenGLGame( const char* szWindowTitle = NULL, GLsizei width = 640, GLsizei height = 480, GLsizei bitmode = 16 );

	bool update();

	bool processKeyEvent();
	void onKeyPressed( char key );
	void onKeyReleased( char key );
	bool isKeyPressed( char key );

	void setFullScreen( bool bFullSceen );
	bool isFullScreen() const;

	bool isActive() const;
	void setActive( bool bActive );

	// Resize And Initialize The GL Window
	GLvoid resizeGLScene( GLsizei width, GLsizei height );

	int initGL( GLvoid );								// �˴���ʼ��OpenGL������������;

	int drawGLScene( GLvoid );							// �����￪ʼ�������еĻ���;

	GLvoid killGLWindow( GLvoid );							// �������ٴ���;

	BOOL createGLWindow();

private:
	static LRESULT CALLBACK wndProc( HWND, UINT, WPARAM, LPARAM ); // Declaration For WndProc
private:
	HGLRC           m_hRC;		// ������ɫ��������
	HDC             m_hDC;		// OpenGL��Ⱦ��������
	HWND            m_hWnd;		// �������ǵĴ��ھ��
	HINSTANCE       m_hInstance;// ��������ʵ��

	bool	m_vbPressKeys[256];	// ������̰���������
	bool	m_bActive;			// ���ڵĻ��־��ȱʡΪTRUE
	bool	m_bFullScreen;		// ȫ����־ȱʡ��ȱʡ�趨��ȫ��ģʽ

	GLsizei       m_nWidth;
	GLsizei       m_nHeight;
	GLsizei       m_nBitMode;
	const char*   m_szTitle;

	GLfloat xrot; // X Rotation ( NEW )
	GLfloat yrot; // Y Rotation ( NEW )
	GLfloat xspeed; // X Rotation speed
	GLfloat yspeed; // Y Rotation speed
	GLfloat z; // Z

	GLint m_nFilterIndex;
	enum { E_TEXTURE_NUM = 3 };
	GLuint texture[E_TEXTURE_NUM]; // Storage For One Texture ( NEW )

	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightPosition[4];

	bool m_bLightOn;

};//end of class OpenGLGame

OpenGLGame* getOpenGLGame();
#define s_pOpenGLGame (getOpenGLGame())