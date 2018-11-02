#pragma once
#include "Packdef.h"
#include "PokerLogic.h"



class CGamePlayer
{
public:	
	static CGamePlayer & GetInstance();
	~CGamePlayer(void);
	void Show(Gdiplus::Graphics * g);
	void SetHead();
	CPokerLogic & logic;
	void SetPlayerName(const wstring & name_self,const wstring & name_right,const wstring & name_lelf);
	void SetPlayerName(const wstring & name,const PlayerPosition pos);
private:
	wstring player_name[3];
	CGamePlayer();
	Rect head_rect[3];
	PlayerPosition pos;
	Image * head_img;
	static CGamePlayer * self_instance;
};

