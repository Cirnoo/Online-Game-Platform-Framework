
// Register.h : PROJECT_NAME 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "Sys.h"
#include "Tool.h"
#include "GameActionCtrl.h"
// CRegisterApp:
// 有关此类的实现，请参阅 Register.cpp
//


class CRegisterApp : public CWinApp
{
	
public:
	CRegisterApp();
	~CRegisterApp();
// 重写
public:
	virtual BOOL InitInstance();
	void CloseMainWnd();
protected:
	int CreatGameRoom();
	int CreatGameDlg();
public:
	CTool & tools;
	Global & sys;
	CGameActionCtrl & game_action;
	DECLARE_MESSAGE_MAP()
};

extern CRegisterApp theApp;