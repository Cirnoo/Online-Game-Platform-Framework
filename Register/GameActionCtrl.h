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
	void Increase();
	GameState GetGameState();
	GameState_EX & GetStateReference();
	void SetGameState(const GameState & new_state);
	void SetSelfSerialNum(const int num);
	Player::PlayerPosition SerialNum2Pos(int num) const;
	Player::PlayerPosition GetCurActPlayerPos();
	const int GetSelfSeriaNum();
private:
	int self_serial_num;
	CGameActionCtrl();
	static CGameActionCtrl * self;
};

