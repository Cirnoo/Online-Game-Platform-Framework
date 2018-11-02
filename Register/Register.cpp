
// Register.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "LoginDlg.h"
#include "RegisterDlg.h"
#include "SettingDlg.h"
#include "GameDlg.h"
#include "GameRoom.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegisterApp

BEGIN_MESSAGE_MAP(CRegisterApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRegisterApp 构造

CRegisterApp::CRegisterApp():sys(Global::GetInstance()),tools(CTool::GetInstance())
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


CRegisterApp::~CRegisterApp()
{
	delete &this->tools;
	delete &this->sys;
}

/************************************************************************/
/*                            初始化单例                                */

	Global * Global::sys= new Global();
	CTool * CTool::tool= new CTool(); 
	// 唯一的一个 CRegisterApp 对象
	CRegisterApp theApp;
/************************************************************************/

// CRegisterApp 初始化

BOOL CRegisterApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	
	AfxEnableControlContainer();

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//CLoginDlg dlg;
	CGameDlg dlg(L"123",1);
	m_pMainWnd = &dlg;
	
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}
	if (nResponse != WM_LOGIN)
	{
		return FALSE;
	}
	//登录成功
	nResponse=CreatGameRoom(m_pMainWnd);

	if (nResponse!=WM_ENTER_ROOM)
	{
		return FALSE;
	}
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	
	return FALSE;
}

int CRegisterApp::CreatGameRoom(CWnd* m_pMainWnd)
{
	CGameRoom dlg;
	m_pMainWnd = &dlg;
	return dlg.DoModal();
}

int CRegisterApp::CreatGameDlg(CWnd* m_pMainWnd)
{
	CGameDlg dlg(sys.room.name,sys.room.num);
	m_pMainWnd = &dlg;
	return dlg.DoModal();
}

