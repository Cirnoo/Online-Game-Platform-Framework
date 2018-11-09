#pragma once
#include "Packdef.h"
#include "PokerLogic.h"
#include <array>


class CGamePlayer
{
public:	
	static CGamePlayer & GetInstance();
	~CGamePlayer(void);
	void Show(Gdiplus::Graphics * const g);
	void ShowLandlordLogo(Gdiplus::Graphics * g);
	void SetHead();	
	void SetPlayerName(const wstring & name,const PlayerPosition pos);
	void DelPlayer(const PlayerPosition pos);
	void SetLandlord(const PlayerPosition pos);
	std::array<bool,3> have_player;
private:
	
	wstring player_name[3];
	CGamePlayer();
	Rect head_rect[3];
	Point landlord_logo_pos[3];
	PlayerPosition landlord;
	pImage head_img,landlord_logo;
	static CGamePlayer * self_instance;
};

