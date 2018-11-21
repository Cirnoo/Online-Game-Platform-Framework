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
public:
	void SetHead();	
	void SetPlayerName(const wstring & name,const PlayerPosition pos);
	void DelPlayer(const PlayerPosition pos);
	void SetLandlord(const PlayerPosition pos);
	std::array<bool,3> have_player;
	PlayerPosition SerialNum2Pos(int num) const;	 //ÐòÁÐºÅ×ªÎ»ÖÃ
	void OnGetMateInfo(WPARAM wParam);
private:
	void ShowLandlordLogo(Gdiplus::Graphics * const g) const;
	std::array<wstring,3> player_name;
	CGamePlayer(const int serial_num);
	Rect head_rect[3];
	Point landlord_logo_pos[3];
	PlayerPosition landlord_pos;
	pImage head_img,landlord_logo;
	static CGamePlayer * self_instance;
private:
	virtual void OnInit() override;
	virtual void OnPaint(Gdiplus::Graphics * const g) const override;
	virtual void OnFrame() override;
};

