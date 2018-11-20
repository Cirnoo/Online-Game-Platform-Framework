#pragma once
#include "Packdef.h"
class GameState_EX
{
public:
	operator GameState() const
	{
		return m_state;
	}
	void operator = (const GameState game_state)
	{
		if (m_state!=game_state)
		{
			if (AfxGetMainWnd())
			{
				AfxGetMainWnd()->PostMessage(WM_GAME_STATE_CHANGE);
			}
			m_state=game_state;
			
		}
	}
private:
	GameState m_state;
};

class CGameActionCtrl
{
	
public:
	static CGameActionCtrl & GetInstance();
	GameState_EX game_state;
	int action_count;		//行动次数记录
	void Increase()
	{
		if(++action_count==3)
		{
			action_count=0;
		}
	}
	GameState_EX GetGameState()
	{
		return game_state;
	}
	GameState_EX & GetStateReference()
	{
		return game_state;
	}
	void SetGameState(const GameState & new_state)
	{
		game_state=new_state;
	}
private:
	
	CGameActionCtrl();
	static CGameActionCtrl * self;
};

