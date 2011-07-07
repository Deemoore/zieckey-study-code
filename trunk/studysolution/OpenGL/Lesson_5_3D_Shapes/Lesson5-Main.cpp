#include "OpenGLGame.h"

OpenGLGame* g_pOpenGLGame;

int WINAPI WinMain(	HINSTANCE	hInstance,				// 当前窗口实例
                    HINSTANCE	hPrevInstance,				// 前一个窗口实例
                    LPSTR		lpCmdLine,				// 命令行参数
                    int		nCmdShow )				// 窗口显示状态
{
    g_pOpenGLGame = new OpenGLGame( "Tutorial 5 : 3D Shapes" );

	MSG  msg;				// Windowsx消息结构
	BOOL done = FALSE;		// 用来退出循环的Bool 变量

	// 创建OpenGL窗口
	if ( !s_pOpenGLGame->createGLWindow() )
	{
		return 0;							// 失败退出
	}

	while( !done )								// 保持循环直到 done=TRUE
	{
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )			// 有消息在等待吗?
		{
			if ( msg.message == WM_QUIT )				// 收到退出消息?
			{
				done = TRUE;					// 是，则done=TRUE
			}
			else							// 不是，处理窗口消息
			{
				TranslateMessage( &msg );				// 翻译消息
				DispatchMessage( &msg );				// 发送消息
			}
		}
		else								// 如果没有消息
		{
			if ( !s_pOpenGLGame->update() )
			{
				done = TRUE;
			}
		}
	}


	// 关闭程序
	s_pOpenGLGame->killGLWindow();								// 销毁窗口

	delete g_pOpenGLGame;
	g_pOpenGLGame = NULL;
	return ( msg.wParam );							// 退出程序
}


OpenGLGame* getOpenGLGame()
{
	return g_pOpenGLGame;
}

/*
如果是字符集方面的错误，请在编译选项中设置字符集为“未设置”
*/