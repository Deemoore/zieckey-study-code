#pragma once

#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "OpenGLSB.h"

class OpenGLGame
{
public:
	OpenGLGame( const char* szWindowTitle = NULL, GLsizei width = 640, GLsizei height = 480, GLsizei bitmode = 16 );

	bool update();

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


    ///////////////////////////////////////////////////////////
    // Draw a gridded ground
    void drawGround( void );


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

    GLfloat xRot;
    GLfloat yRot;

};//end of class OpenGLGame

OpenGLGame* getOpenGLGame();
#define s_pOpenGLGame (getOpenGLGame())

