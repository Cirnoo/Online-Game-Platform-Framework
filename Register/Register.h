
// Register.h : PROJECT_NAME 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "Sys.h"
#include "Tool.h"
// CRegisterApp:
// 有关此类的实现，请参阅 Register.cpp
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
// 重写
public:
	virtual BOOL InitInstance();
// 实现
protected:
	int CreatGameRoom(CWnd* m_pMainWnd);
	int CreatGameDlg(CWnd* m_pMainWnd);
public:
	CTool & tools;
	Global & sys;
	DECLARE_MESSAGE_MAP()
};

extern CRegisterApp theApp;