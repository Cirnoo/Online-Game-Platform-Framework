#pragma once
#include "Packdef.h"
#include "PokerLogic.h"



class CGamePlayer
{
public:	
	static CGamePlayer & GetInstance(wstring & self_name);
	~CGamePlayer(void);
	void Show(Gdiplus::Graphics * const g);
	void ShowLandlordLogo(Gdiplus::Graphics * g);
	void SetHead();	
	void SetPlayerName(const wstring & name_right,const wstring & name_lelf);
	void SetPlayerName(const wstring & name,const PlayerPosition pos);
	void DelPlayer(const PlayerPosition pos);
	void SetLandlord(const PlayerPosition pos);
private:
	wstring player_name[3];
	CGamePlayer(wstring & self_name);
	Rect head_rect[3];
	Point landlord_logo_pos[3];
	PlayerPosition landlord;
	pImage head_img,landlord_logo;
	static CGamePlayer * self_instance;
};

