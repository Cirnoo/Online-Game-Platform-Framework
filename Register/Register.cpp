
// Register.cpp : ����Ӧ�ó��������Ϊ��
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


// CRegisterApp ����

CRegisterApp::CRegisterApp():sys(Global::GetInstance()),tools(CTool::GetInstance())
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


CRegisterApp::~CRegisterApp()
{
	delete &this->tools;
	delete &this->sys;
}

/************************************************************************/
/*                            ��ʼ������                                */

	Global * Global::sys= new Global();
	CTool * CTool::tool= new CTool(); 
	// Ψһ��һ�� CRegisterApp ����
	CRegisterApp theApp;
/************************************************************************/

// CRegisterApp ��ʼ��

BOOL CRegisterApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	
	AfxEnableControlContainer();

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//CLoginDlg dlg;
	CGameDlg dlg(L"123",1);
	m_pMainWnd = &dlg;
	
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}
	if (nResponse != WM_LOGIN)
	{
		return FALSE;
	}
	//��¼�ɹ�
	nResponse=CreatGameRoom(m_pMainWnd);

	if (nResponse!=WM_ENTER_ROOM)
	{
		return FALSE;
	}
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	
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

