#pragma once
#include "Packdef.h"
#include "PokerLogic.h"
#include <array>
#include "GameInterface.h"

class CGamePlayer:public CGameInterface
{
public:	
	static CGamePlayer & GetInstance(const int num);
	~CGamePlayer(void);
	virtual void OnInit();
	virtual void OnPaint(Gdiplus::Graphics & g);
	virtual void OnTimer();
	void Show(Gdiplus::Graphics * const g);
	void ShowLandlordLogo(Gdiplus::Graphics * g);
	void SetHead();	
	void SetPlayerName(const wstring & name,const PlayerPosition pos);
	void DelPlayer(const PlayerPosition pos);
	void SetLandlord(const PlayerPosition pos);
	std::array<bool,3> have_player;
	const int self_serial_num; //序列号
	PlayerPosition SerialNum2Pos(const int num) const;	 //序列号转位置
private:
	std::array<wstring,3> player_name;
	CGamePlayer(const int serial_num);
	Rect head_rect[3];
	Point landlord_logo_pos[3];
	PlayerPosition landlord;
	pImage head_img,landlord_logo;
	static CGamePlayer * self_instance;
};

