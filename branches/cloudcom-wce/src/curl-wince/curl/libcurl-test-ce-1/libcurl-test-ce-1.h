// libcurl-test-ce-1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 

// Clibcurltestce1App:
// �йش����ʵ�֣������ libcurl-test-ce-1.cpp
//

class Clibcurltestce1App : public CWinApp
{
public:
	Clibcurltestce1App();
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Clibcurltestce1App theApp;
