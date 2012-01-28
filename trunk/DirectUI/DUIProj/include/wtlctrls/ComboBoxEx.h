#include <atlcrack.h>
#include <atlstr.h>

#pragma once

class CComboBoxBasic : public CWindowImpl<CComboBoxBasic, CComboBox>, public CMessageFilter
{
	BEGIN_MSG_MAP(CComboBoxBasic)
		REFLECTED_COMMAND_CODE_HANDLER_EX(CBN_SELCHANGE, OnSelectChange)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	CComboBoxBasic(HWND hWnd)
	{
		m_hWnd = hWnd;
	}

	BOOL SubclassWindow( HWND hWnd )
	{
		return( CWindowImpl< CComboBoxBasic, CComboBox >::SubclassWindow( hWnd ) );
	}

	LRESULT OnSelectChange(UINT , int, HWND)
	{
		LRESULT lRet = ::SendMessage(m_hWnd, WM_NOTIFY, NULL, NULL);
	}

private:
	HWND		m_hWnd;
};