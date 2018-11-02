#pragma once
#include "Packdef.h"
#include "PokerLogic.h"



class CGamePlayer
{
public:	
	CGamePlayer(PlayerPosition _pos);
	~CGamePlayer(void);
	void Show(Gdiplus::Graphics * g);
	void SetHead();
	CPokerLogic logic;
	void SetPlayerName(wstring name_self,wstring name_lelf,wstring name_right);
	wstring name[3];
private:
	Rect head_rect[3];
	PlayerPosition pos;
	Image * head_img;
};

