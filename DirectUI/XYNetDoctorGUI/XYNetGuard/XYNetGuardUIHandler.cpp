#include "stdafx.h"
#include "XYNetGuard.h"
#include "XYNetGuardmaindlg.h"
#include "XYNetGuarduihandler.h"
#include "XYNetGuardmsgbox.h"


// ��ʼ��UIHandler
void CXYNetGuardUIHandler::Init()
{

}


// �������һ����ʾ
void CXYNetGuardUIHandler::FirstShow()
{
	
}


// ���������ŵ����˵�����
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