#pragma once
#include "Packdef.h"
#include "PokerLogic.h"
#include <array>


class CGamePlayer
{
public:	
	static CGamePlayer & GetInstance(const int num);
	~CGamePlayer(void);
	void Show(Gdiplus::Graphics * const g);
	void ShowLandlordLogo(Gdiplus::Graphics * g);
	void SetHead();	
	void SetPlayerName(const wstring & name,const PlayerPosition pos);
	void DelPlayer(const PlayerPosition pos);
	void SetLandlord(const PlayerPosition pos);
	void InitPlayerInfo();
	std::array<bool,3> have_player;
	const int self_serial_num; //序列号
	PlayerPosition SerialNum2Pos(const int num) const;	 //序列号转位置
private:
	
	
	wstring player_name[3];
	CGamePlayer(const int serial_num);
	Rect head_rect[3];
	Point landlord_logo_pos[3];
	PlayerPosition landlord;
	pImage head_img,landlord_logo;
	static CGamePlayer * self_instance;
};

