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
	head_rect[Self]=Rect(300,700,70,70);
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

