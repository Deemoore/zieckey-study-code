// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#pragma warning(disable: 4995)
#pragma warning(disable: 4996)
#pragma warning(disable: 4819)
#pragma warning(disable: 4018)
#pragma warning(disable: 4244)

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include	<WinSock2.h>
#include	<ws2tcpip.h>
#include	<IPExport.h>
#pragma		comment(lib,"ws2_32.lib")

#include <atlbase.h>
#include <atlwin.h>
#include <atlstr.h>
#include <atltrace.h>
#include <atlfile.h>

// ������WTL��CString
#define _WTL_NO_CSTRING

#include <exdisp.h>
#include <exdispid.h>
#include <mshtml.h>
#include <mshtmdid.h>
#include <math.h>

#include <wtl/atlapp.h>
#include <wtl/atlframe.h>
#include <wtl/atlctrls.h>
#include <wtl/atlctrlx.h>
#include <wtl/atldlgs.h>
#include <wtl/atlcrack.h>
#include <wtl/atlmisc.h>

#include <tinyxml/tinyxml.h>
#include <bkres/bkresutil.h>
#include <miniutil/bkcmdline.h>
#include <bkwin/bkatldefine.h>
#include <bkwin/bklistview.h>
#include <bkres/bkres.h>

#include <atlwin.h>
