#include "stdafx.h"
#include "GamePlayer.h"
#include "Register.h"


CGamePlayer * CGamePlayer::self_instance=nullptr;
CGamePlayer & CGamePlayer::GetInstance(wstring & self_name)
{
	if (!self_instance)
	{
		self_instance=new CGamePlayer(self_name);
	}
	return *self_instance;
}


CGamePlayer::CGamePlayer(wstring & self_name)
{
	head_img=theApp.sys.cirno;

	player_name[Self]=self_name;

	landlord_logo=::CutImage(theApp.sys.game_tool,97,110,56,93);
	landlord_logo=::ResizeImg(landlord_logo,0.9);
	head_rect[Self]=Rect(300,700,70,70);

	landlord_logo_pos[Self]=Point(GAME_DLG_WIDTH-250,GAME_DLG_HEIGHT-300);
	landlord_logo_pos[Right]=Point(GAME_DLG_WIDTH-150,100);
	landlord_logo_pos[Left]=Point(150,100);
}

CGamePlayer::~CGamePlayer(void)
{
	self_instance=nullptr;
}

void CGamePlayer::Show(Gdiplus::Graphics *const g)
{
	for (int i=Self;i<=Left;i++)
	{
		if (!player_name[i].empty())
		{
			Rect temp=head_rect[i];
			g->DrawImage(head_img,temp);
		}
	}
}

void CGamePlayer::ShowLandlordLogo(Gdiplus::Graphics * g)
{
	g->DrawImage(landlord_logo,landlord_logo_pos[Right]);
}

void CGamePlayer::SetPlayerName(const wstring & name,const PlayerPosition pos)
{
	player_name[pos]=name;
}

void CGamePlayer::SetPlayerName(const wstring & name_right,const wstring & name_left)
{
	player_name[Right]=name_right;
	player_name[Left]=name_left;
}

void CGamePlayer::DelPlayer(const PlayerPosition pos)
{
	player_name[pos].clear();
}

void CGamePlayer::SetLandlord(const PlayerPosition pos)
{
	landlord=pos;
}

