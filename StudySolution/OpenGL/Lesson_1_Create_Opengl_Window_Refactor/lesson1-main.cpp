#include "OpenGLGame.h"

OpenGLGame* g_pOpenGLGame;

int WINAPI WinMain(	HINSTANCE	hInstance,				// ��ǰ����ʵ��
                   HINSTANCE	hPrevInstance,				// ǰһ������ʵ��
                   LPSTR		lpCmdLine,				// �����в���
                   int		nCmdShow)				// ������ʾ״̬
{
    MSG  msg;				// Windowsx��Ϣ�ṹ
    BOOL done=FALSE;		// �����˳�ѭ����Bool ����

    g_pOpenGLGame = new OpenGLGame();

    // ��ʾ�û�ѡ������ģʽ
    if (MessageBox(NULL,"������ȫ��ģʽ������ô��", "����ȫ��ģʽ",MB_YESNO|MB_ICONQUESTION)==IDNO)
    {
        s_pOpenGLGame->setFullScreen( false );						// FALSEΪ����ģʽ
    }

    // ����OpenGL����
    if ( !s_pOpenGLGame->createGLWindow("NeHe's OpenGL������",640,480,16 ) )
    {
        return 0;							// ʧ���˳�
    }

    while( !done )								// ����ѭ��ֱ�� done=TRUE
    {
        if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) )			// ����Ϣ�ڵȴ���?
        {
            if (msg.message==WM_QUIT)				// �յ��˳���Ϣ?
            {
                done=TRUE;					// �ǣ���done=TRUE
            }
            else							// ���ǣ���������Ϣ
            {
                TranslateMessage(&msg);				// ������Ϣ
                DispatchMessage(&msg);				// ������Ϣ
            }
        }
        else								// ���û����Ϣ
        {
            if ( !s_pOpenGLGame->update() )
            {
                done = TRUE;
            }
        }
    }


    // �رճ���
    s_pOpenGLGame->killGLWindow();								// ���ٴ���

    delete g_pOpenGLGame;
    g_pOpenGLGame = NULL;
    return (msg.wParam);							// �˳�����
}


OpenGLGame* getOpenGLGame()
{
    return g_pOpenGLGame;
}

/*
������ַ�������Ĵ������ڱ���ѡ���������ַ���Ϊ��δ���á�
*/