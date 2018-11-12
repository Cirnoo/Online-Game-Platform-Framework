
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

class Global;
class CTool;
class CRegisterApp : public CWinApp
{
	struct GameActionCtrl
	{
		GameState game_state;
		int action_count;		//行动次数记录
		GameActionCtrl()
		{
			game_state=GameState::Wait;
			action_count=0;
		}
		void SetGameState(const GameState state)
		{
			if (game_state==state)
				action_count++;
			else
				action_count=0;
			game_state=state;
		}
		void Increase()
		{
			++action_count;
		}
		GameState GetGameState()
		{
			return game_state;
		}
	};
public:
	CRegisterApp();
	~CRegisterApp();
// 重写
public:
	virtual BOOL InitInstance();
	void CloseMainWnd();
	GameActionCtrl game_action;
// 实现
protected:
	int CreatGameRoom();
	int CreatGameDlg();
public:
	CTool & tools;
	Global & sys;
	DECLARE_MESSAGE_MAP()
};

extern CRegisterApp theApp;