
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

class Global;
class CTool;
class CRegisterApp : public CWinApp
{
	struct GameActionCtrl
	{
		GameState game_state;
		int action_count;		//�ж�������¼
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
// ��д
public:
	virtual BOOL InitInstance();
	void CloseMainWnd();
	GameActionCtrl game_action;
// ʵ��
protected:
	int CreatGameRoom();
	int CreatGameDlg();
public:
	CTool & tools;
	Global & sys;
	DECLARE_MESSAGE_MAP()
};

extern CRegisterApp theApp;