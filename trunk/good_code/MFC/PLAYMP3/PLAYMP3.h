// PLAYMP3.h : main header file for the PLAYMP3 application
//

#if !defined(AFX_PLAYMP3_H__C2949AE4_571B_4B00_A81A_094ADC5E5575__INCLUDED_)
#define AFX_PLAYMP3_H__C2949AE4_571B_4B00_A81A_094ADC5E5575__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPLAYMP3App:
#define SHOWLIST (WM_USER+140) 
#define HIDEMP3 (WM_USER + 141)
#define HIDEOPENMP3 (WM_USER + 142)
#define SHOWMP3WINDOW (WM_USER + 143)
#define VOLMUTE (WM_USER + 144)


  
// See PLAYMP3.cpp for the implementation of this class
//



class CPLAYMP3App : public CWinApp
{
public:
	CPLAYMP3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPLAYMP3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPLAYMP3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYMP3_H__C2949AE4_571B_4B00_A81A_094ADC5E5575__INCLUDED_)
