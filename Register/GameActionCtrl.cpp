#include "stdafx.h"
#include "GameActionCtrl.h"


CGameActionCtrl & CGameActionCtrl::GetInstance()
{
	return *self;
}

CGameActionCtrl::CGameActionCtrl()
{
	game_state=GameState::Wait;
	action_count=0;
}

CGameActionCtrl * CGameActionCtrl::self=new CGameActionCtrl;


