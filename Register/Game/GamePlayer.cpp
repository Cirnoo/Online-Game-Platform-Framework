#include "stdafx.h"
#include "GamePlayer.h"
#include "Register.h"


CGamePlayer * CGamePlayer::self_instance=nullptr;
CGamePlayer & CGamePlayer::GetInstance()
{
	if (!self_instance)
	{
		self_instance=new CGamePlayer;
	}
	return *self_instance;
}


CGamePlayer::CGamePlayer()
{
	head_img=theApp.sys.cirno;
	landlord_logo=::CutImage(theApp.sys.game_tool,105,105,64,88);
	landlord_logo=::ResizeImg(landlord_logo,0.8);
	head_rect[Self]=Rect(300,700,70,70);

	landlord_logo_pos[Self]=Point(GAME_DLG_WIDTH-250,GAME_DLG_HEIGHT-300);
	landlord_logo_pos[Right]=Point(GAME_DLG_WIDTH-150,100);
	landlord_logo_pos[Left]=Point(150,100);
}

CGamePlayer::~CGamePlayer(void)
{
	self_instance=nullptr;
}

void CGamePlayer::Show(Gdiplus::Graphics * g)
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

void CGamePlayer::SetPlayerName(const wstring & name_self,const wstring & name_right,const wstring & name_left)
{
	player_name[Self]=name_self;
	player_name[Right]=name_right;
	player_name[Left]=name_left;
}

void CGamePlayer::SetLandlord(const PlayerPosition pos)
{
	landlord=pos;
}

