
// Register.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Sys.h"
#include "Tool.h"
// CRegisterApp:
// �йش����ʵ�֣������ Register.cpp
//
using std::wstring;
using std::string;
using std::vector;
class Global;
class CTool;
class CRegisterApp : public CWinApp
{
public:
	CRegisterApp();
	~CRegisterApp();
// ��д
public:
	virtual BOOL InitInstance();
// ʵ��
protected:
	int CreatGameRoom(CWnd* m_pMainWnd);
	int CreatGameDlg(CWnd* m_pMainWnd);
public:
	CTool & tools;
	Global & sys;
	DECLARE_MESSAGE_MAP()
};

extern CRegisterApp theApp;