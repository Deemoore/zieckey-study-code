
#pragma once

//////////////////////////////////////////////////////////////////////////
// Common Controls
// listview
#define MSG_USER_LDLISTVIEWCTRL_BEGIN		WM_APP+2000
#define MSG_USER_LDLISTVIEWCTRL_LBP_URL		MSG_USER_LDLISTVIEWCTRL_BEGIN+1//如果用户点击了URL，就会像用户发送这个消息，WPARAM 行号，LPARAM URL的索引
#define MSG_USER_LDLISTVIEWCTRL_LBP_EXTXT	MSG_USER_LDLISTVIEWCTRL_BEGIN+2//如果用户点击了EXTXT, 就会像用户发送这个消息，WPARAM 行号，LPARAM EXTXT的索引
#define MSG_USER_LDLISTVIEWCTRL_LBP_BTN		MSG_USER_LDLISTVIEWCTRL_BEGIN+3
#define MSG_USER_LDLISTVIEWCTRL_EXPAND		MSG_USER_LDLISTVIEWCTRL_BEGIN+4//展开操作
#define MSG_USER_LDLISTVIEWCTRL_NOTIFY		MSG_USER_LDLISTVIEWCTRL_BEGIN+5//LISTVIEW中需要回调给主窗口的消息
#define MSG_USER_LDLISTVIEWCTRL_END			MSG_USER_LDLISTVIEWCTRL_BEGIN+999

//////////////////////////////////////////////////////////////////////////
// Home

#define MSG_HOME_BEGIN						(WM_APP+3000)

#define	MSG_DIAGNOSE_ITEM_FINISHED			(MSG_HOME_BEGIN+1)		// 单个诊断项完成了
