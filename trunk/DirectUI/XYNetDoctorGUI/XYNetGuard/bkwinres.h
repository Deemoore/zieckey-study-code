#pragma once

//////////////////////////////////////////////////////////////////////////
// CONTROL ID
#define IDC_BTN_SYS_FEEDBACK				60000
#define IDC_BTN_SYS_CLOSE                   60001
#define IDC_BTN_SYS_MENU                    60002
#define IDC_BTN_SYS_MIN                     60003

#define IDC_LBL_MSGBOX_TITLE                60004
#define IDC_ICON_MSGBOX_ICON                60005
#define IDC_LBL_MSGBOX_TEXT                 60006
#define IDC_CHK_MSGBOX_NONOTIFYLATER        60007
#define IDC_DIV_MSGBOX_BUTTONS              60008
#define IDC_DIV_MSGBOX_CONTENT              60009
#define IDC_CHK_MSGBOX_NEVERSHOW            60010

//////////////////////////////////////////////////////////////////////////
// 系统主界面 10000 - 10200


//////////////////////////////////////////////////////////////////////////
// 首页 10200 - 10400

#define	IDC_SCAN_ITEM_START								10201

#define IDC_REDIAGNOSE_BUTTON							10632

#define IDC_DIAGNOSE_RESULT_HEADER_RICHTEXT				10644

#define IDC_DIAGNOSE_PROCESSING_DLG						10660
#define IDC_DIAGNOSE_ALL_ANIMATE						10661

#define IDC_DIAGNOSE_RESULT_ERROR_DLG					10680
#define IDC_DIAGNOSE_RESULT_LIST_REALWND				10681

#define IDC_DIAGNOSE_RESULT_MAIN_REASON_RICHTEXT		10682
#define IDC_DIAGNOSE_RESULT_MAIN_SUGGUEST_RICHTEXT		10683

#define IDC_DIAGNOSE_RESULT_NOERROR_DLG					10700

#define	IDC_INTERNET_QOS_START_ID						10721

#define	IDC_NETSPEED_RESULT_RICHTEXT					10755
#define IDC_NETSPEED_RESULT_PROCESS						10756

#define	IDC_EXPORT_DIAGNOSE_RESULT						10780


//////////////////////////////////////////////////////////////////////////
// 网络环境 10400 - 10600
#define IDC_NETCONFIG_LEFT_MAIN_TAB						10801
#define IDC_NETCONFIG_NETWORK_DEVICE_LIST_DLG			10810

#define IDC_NETCONFIG_RESCAN_NEWORK_DEVICE_BUTTON		10872

#define IDC_NETCONFIG_NETWORK_DEVICE_LISTVIEW			10874

// 网卡切换设置的当前状态、修改网卡切换设置以及网卡切换按钮
#define IDC_NETCONFIG_NETWORK_DEVICE_AC_STATE			10821
#define IDC_NETCONFIG_NETWORK_DEVICE_AC_CHANGESETTING	10822
#define IDC_NETCONFIG_NETWORK_DEVICE_AC_ADAPTERCHANGE	10823

// 网络参数配置对话框
#define IDC_NETCONFIG_NETWORK_CONFIG_DLG				10850			// 网络配置对话框
#define IDC_NETCONFIG_NETWORK_DEVICE_LIST_COMBOBOX		10851			// 显示网卡列表的ComboBox以便用户选择
#define IDC_NETCONFIG_APPLY_NETWORK_IPADDRESS_MODIFY	10852			// 确认修改IP地址

#define IDC_NETCONFIG_AUTO_OBTAIN_IPADDRESS_RADIOBOX	10853			// 自动获取IP地址RadioBox
#define IDC_NETCONFIG_MANUAL_SET_IPADDRESS_RADIOBOX		10854			// 手动设置IP地址RadioBox
#define IDC_NETCONFIG_IPADDRESS_EDIT_WND				10855			// IP地址编辑框
#define IDC_NETCONFIG_NETMASK_EDIT_WND					10856			// 子网掩码编辑框
#define IDC_NETCONFIG_GATEWAY_EDIT_WND					10857			// 网关地址编辑框
#define IDC_NETCONFIG_AUTO_OBTAIN_DNS_RADIOBOX			10860			// 自动获取DNS服务器RadioBox
#define IDC_NETCONFIG_MANUL_SET_DNS_RADIOBOX			10861			// 手动设定DNS服务器RadioBox
#define IDC_NETCONFIG_PRIMARY_DNS_SERVER_EDIT_WND		10862			// 首选 DNS服务器地址编辑框
#define IDC_NETCONFIG_SECONDARY_DNS_SERVER_EDIT_WND		10863			// 备用 DNS服务器地址编辑框

#define IDC_NETCONFIG_AUTOCONFIG_BTN					10865			// 智能配置向导
#define IDC_NETCONFIG_ROUTETABLE_MGR_BTN				10866			// 管理路由表
#define IDC_NETCONFIG_ARPTABLE_MGR_BTN					10867			// 管理ARP列表
#define IDC_NETCONFIG_APPLY_IPCHANGE_BTN				10868			// 确认IP地址的修改
#define IDC_NETCONFIG_CLEAR_IPCHANGE_BTN				10869

//////////////////////////////////////////////////////////////////////////
// 故障诊断 10600 - 10800
#define IDC_DIAGNOSE_PROCESS_PIC						11001
#define IDC_DIAGNOSE_PROCESS_WND						11002

#define IDC_DEMO_COMBOBOX_REALWND						11004

#define	IDC_DIAGNOSE_RESULT_WND							11041

#define IDC_DIAGNOSE_SUPPORT_BUTTON						11043


//////////////////////////////////////////////////////////////////////////
// 网络检测 10800 - 11000


//////////////////////////////////////////////////////////////////////////
// 网络百宝箱 20000 - 20200


//////////////////////////////////////////////////////////////////////////
// 常见问题 20200 - 20400


//////////////////////////////////////////////////////////////////////////
// 意见反馈 20400 - 20600


// STRING ID

#define IDS_APP_FONT                            0
#define IDS_APP_NAME                            1
#define IDS_MSGBOX_BUTTON_XML                   17
#define IDS_MSGBOX_OK                           18
#define IDS_MSGBOX_CANCEL                       19
#define IDS_MSGBOX_ABORT                        20
#define IDS_MSGBOX_RETRY                        21
#define IDS_MSGBOX_IGNORE                       22
#define IDS_MSGBOX_YES                          23
#define IDS_MSGBOX_NO                           24
#define IDS_MSGBOX_CONTINUE                     25
#define IDS_MSGBOX_BUTTON_DIV                   26