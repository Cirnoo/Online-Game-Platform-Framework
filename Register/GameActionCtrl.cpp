#include "stdafx.h"
#include "GameActionCtrl.h"

CGameActionCtrl & CGameActionCtrl::GetInstance()
{
	return *self;
}

void CGameActionCtrl::Increase()
{
	if(++action_count==3)
	{
		action_count=0;
	}
}

GameState CGameActionCtrl::GetGameState()
{
	return game_state;
}

GameState_EX & CGameActionCtrl::GetStateReference()
{
	return game_state;
}

void CGameActionCtrl::SetGameState(const GameState & new_state)
{
	game_state=new_state;
}

void CGameActionCtrl::SetSelfSerialNum(const int num)
{
	self_serial_num=num;
}

Player::PlayerPosition CGameActionCtrl::SerialNum2Pos(int num) const
{
	num%=3;
	if (num==self_serial_num)
	{
		return Player::Self;
	}
	const char temp[]={0,1,2,0,1};
	int flag_self=self_serial_num;
	int flag_op=flag_self;
	while(temp[++flag_op]!=num);
	return Player::PlayerPosition(flag_op-flag_self);
}

Player::PlayerPosition CGameActionCtrl::GetCurActPlayerPos()
{
	return SerialNum2Pos(action_count);
}

const int CGameActionCtrl::GetSelfSeriaNum()
{
	return self_serial_num;
}

CGameActionCtrl::CGameActionCtrl()
{
	game_state=GameState::Wait;
	action_count=0;
	self_serial_num=0;
}

CGameActionCtrl * CGameActionCtrl::self=new CGameActionCtrl;


