
// ButtonBackGroundColor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CButtonBackGroundColorApp:
// �йش����ʵ�֣������ ButtonBackGroundColor.cpp
//

class CButtonBackGroundColorApp : public CWinAppEx
{
public:
	CButtonBackGroundColorApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CButtonBackGroundColorApp theApp;