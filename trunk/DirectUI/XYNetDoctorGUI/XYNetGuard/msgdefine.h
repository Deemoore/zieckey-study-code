
#pragma once

//////////////////////////////////////////////////////////////////////////
// Common Controls
// listview
#define MSG_USER_LDLISTVIEWCTRL_BEGIN		WM_APP+2000
#define MSG_USER_LDLISTVIEWCTRL_LBP_URL		MSG_USER_LDLISTVIEWCTRL_BEGIN+1//����û������URL���ͻ����û����������Ϣ��WPARAM �кţ�LPARAM URL������
#define MSG_USER_LDLISTVIEWCTRL_LBP_EXTXT	MSG_USER_LDLISTVIEWCTRL_BEGIN+2//����û������EXTXT, �ͻ����û����������Ϣ��WPARAM �кţ�LPARAM EXTXT������
#define MSG_USER_LDLISTVIEWCTRL_LBP_BTN		MSG_USER_LDLISTVIEWCTRL_BEGIN+3
#define MSG_USER_LDLISTVIEWCTRL_EXPAND		MSG_USER_LDLISTVIEWCTRL_BEGIN+4//չ������
#define MSG_USER_LDLISTVIEWCTRL_NOTIFY		MSG_USER_LDLISTVIEWCTRL_BEGIN+5//LISTVIEW����Ҫ�ص��������ڵ���Ϣ
#define MSG_USER_LDLISTVIEWCTRL_END			MSG_USER_LDLISTVIEWCTRL_BEGIN+999

//////////////////////////////////////////////////////////////////////////
// Home

#define MSG_HOME_BEGIN						(WM_APP+3000)

#define	MSG_DIAGNOSE_ITEM_FINISHED			(MSG_HOME_BEGIN+1)		// ��������������
