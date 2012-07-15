// MyMp3sec.h : main header file for the MYMP3SEC application
//

#if !defined(AFX_MYMP3SEC_H__1FBDE860_C151_4EB5_B148_8F905606D674__INCLUDED_)
#define AFX_MYMP3SEC_H__1FBDE860_C151_4EB5_B148_8F905606D674__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyMp3secApp:
// See MyMp3sec.cpp for the implementation of this class
//

class CMyMp3secApp : public CWinApp
{
public:
	CMyMp3secApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMp3secApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyMp3secApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMP3SEC_H__1FBDE860_C151_4EB5_B148_8F905606D674__INCLUDED_)
