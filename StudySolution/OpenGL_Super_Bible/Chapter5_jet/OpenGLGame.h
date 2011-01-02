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

	int initGL( GLvoid );								// 此处开始对OpenGL进行所有设置;

	int drawGLScene( GLvoid );							// 从这里开始进行所有的绘制;

	GLvoid killGLWindow( GLvoid );							// 正常销毁窗口;

	BOOL createGLWindow();


    ///////////////////////////////////////////////////////////
    // Draw a gridded ground
    void drawGround( void );


private:
	static LRESULT CALLBACK wndProc( HWND, UINT, WPARAM, LPARAM ); // Declaration For WndProc
private:
	HGLRC           m_hRC;		// 窗口着色描述表句柄
	HDC             m_hDC;		// OpenGL渲染描述表句柄
	HWND            m_hWnd;		// 保存我们的窗口句柄
	HINSTANCE       m_hInstance;// 保存程序的实例

	bool	m_vbPressKeys[256];	// 保存键盘按键的数组
	bool	m_bActive;			// 窗口的活动标志，缺省为TRUE
	bool	m_bFullScreen;		// 全屏标志缺省，缺省设定成全屏模式

	GLsizei       m_nWidth;
	GLsizei       m_nHeight;
	GLsizei       m_nBitMode;
	const char*   m_szTitle;

    GLfloat xRot;
    GLfloat yRot;

};//end of class OpenGLGame

OpenGLGame* getOpenGLGame();
#define s_pOpenGLGame (getOpenGLGame())

