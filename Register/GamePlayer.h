#pragma once
#include "Packdef.h"
#include "PokerLogic.h"
namespace Player
{
	enum PlayerPosition
	{
		Front,Left,Right
	};
}

using namespace Player;


class CGamePlayer
{
public:	
	CGamePlayer(PlayerPosition _pos);
	~CGamePlayer(void);
	void Show(Gdiplus::Graphics * g);
	void SetHead();
	CPokerLogic logic;
	wstring name;
private:
	
	Rect head_rect[3];
	PlayerPosition pos;
	Image * head_img;
};

