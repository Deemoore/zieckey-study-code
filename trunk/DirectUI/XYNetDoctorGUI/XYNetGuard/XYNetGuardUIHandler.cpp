#include "stdafx.h"
#include "XYNetGuard.h"
#include "XYNetGuardmaindlg.h"
#include "XYNetGuarduihandler.h"
#include "XYNetGuardmsgbox.h"


// 初始化UIHandler
void CXYNetGuardUIHandler::Init()
{

}


// 主界面第一次显示
void CXYNetGuardUIHandler::FirstShow()
{
	
}


// 主界面上排导航菜单更改
BOOL CXYNetGuardUIHandler::OnMainSubTypeSelChange( int nTabItemIDOld, int nTabItemIDNew )
{
	switch(nTabItemIDNew)
	{	
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	default:
		break;
	}
	
	return TRUE;
}


//void CXYNetGuardUIHandler::OnTimer(UINT_PTR nIDEvent)
//{
//	m_dlg->m_pHomeViewUIHandler->OnTimer(nIDEvent);
//}