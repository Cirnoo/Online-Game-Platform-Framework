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
private:
	virtual void OnInit() override;
	virtual void OnPaint(Gdiplus::Graphics * const g) const override;
	virtual void OnFrame() override;
public:
	void ShowLandlordLogo(Gdiplus::Graphics & g);
	void SetHead();	
	void SetPlayerName(const wstring & name,const PlayerPosition pos);
	void DelPlayer(const PlayerPosition pos);
	void SetLandlord(const PlayerPosition pos);
	std::array<bool,3> have_player;
	const int self_serial_num; //序列号
	PlayerPosition SerialNum2Pos(const int num) const;	 //序列号转位置
	LRESULT OnGetMateInfo(WPARAM wParam, LPARAM lParam);
private:
	std::array<wstring,3> player_name;
	CGamePlayer(const int serial_num);
	Rect head_rect[3];
	Point landlord_logo_pos[3];
	PlayerPosition landlord;
	pImage head_img,landlord_logo;
	static CGamePlayer * self_instance;
};

