// libcurl-test-ce-1.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "libcurl-test-ce-1.h"
#include "libcurl-test-ce-1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clibcurltestce1App

BEGIN_MESSAGE_MAP(Clibcurltestce1App, CWinApp)
END_MESSAGE_MAP()


// Clibcurltestce1App 构造
Clibcurltestce1App::Clibcurltestce1App()
	: CWinApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 Clibcurltestce1App 对象
Clibcurltestce1App theApp;

// Clibcurltestce1App 初始化

BOOL Clibcurltestce1App::InitInstance()
{
    // 在应用程序初始化期间，应调用一次 SHInitExtraControls 以初始化
    // 所有 Windows Mobile 特定控件，如 CAPEDIT 和 SIPPREF。
    SHInitExtraControls();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	Clibcurltestce1Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
