// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#pragma warning(disable: 4995)
#pragma warning(disable: 4996)
#pragma warning(disable: 4819)
#pragma warning(disable: 4018)
#pragma warning(disable: 4244)

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// TODO: 在此处引用程序需要的其他头文件
#include	<WinSock2.h>
#include	<ws2tcpip.h>
#include	<IPExport.h>
#pragma		comment(lib,"ws2_32.lib")

#include <atlbase.h>
#include <atlwin.h>
#include <atlstr.h>
#include <atltrace.h>
#include <atlfile.h>

// 不是用WTL的CString
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
