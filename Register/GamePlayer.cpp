#include "stdafx.h"
#include "GamePlayer.h"
#include "Register.h"



CGamePlayer::CGamePlayer(PlayerPosition _pos)
{
	ASSERT(pos<3);
	pos=_pos;
	head_img=theApp.sys.cirno;
	head_rect[Front]=Rect(300,700,70,70);
}

CGamePlayer::~CGamePlayer(void)
{

}

void CGamePlayer::Show(Gdiplus::Graphics * g)
{
	Rect temp=head_rect[pos];
	g->DrawImage(head_img,temp);
	logic.ShowHandPoker(g);
}

