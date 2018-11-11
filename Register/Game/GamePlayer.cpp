#include "stdafx.h"
#include "GamePlayer.h"
#include "Register.h"


CGamePlayer * CGamePlayer::self_instance=nullptr;
CGamePlayer & CGamePlayer::GetInstance(const int num)
{
	if (!self_instance)
	{
		self_instance=new CGamePlayer(num);
	}
	return *self_instance;
}

CGamePlayer::CGamePlayer(const int serial_num):self_serial_num(serial_num)
{
	const pImage head_temp=theApp.sys.cirno;
	CRgn rgn;
	CRect rc(0,0,head_temp->GetWidth(),head_temp->GetHeight());
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 25, 25);
	head_img=CutImage(head_temp,rgn);	//²Ã¼ô³ÉÔ²½ÇµÄÍ·Ïñ

	landlord_logo=::CutImage(theApp.sys.game_tool,97,110,56,93);
	landlord_logo=::ResizeImg(landlord_logo,0.9);

	head_rect[Self]=Rect(300,GAME_DLG_HEIGHT-150,80,80);
	head_rect[Right]=Rect(GAME_DLG_WIDTH-190,300,80,80);
	head_rect[Left]=Rect(150,300,80,80);
	landlord_logo_pos[Self]=Point(GAME_DLG_WIDTH-250,GAME_DLG_HEIGHT-300);
	landlord_logo_pos[Right]=Point(GAME_DLG_WIDTH-150,100);
	landlord_logo_pos[Left]=Point(150,100);
}

CGamePlayer::~CGamePlayer(void)
{
	self_instance=nullptr;
}

void CGamePlayer::OnPaint(Gdiplus::Graphics & g)
{
	for (int i=Self;i<=Left;i++)
	{
		if (!player_name[i].empty())
		{
			g.DrawImage(head_img,head_rect[i]);
		}
	}
}

void CGamePlayer::OnInit()
{
	const auto & mate_name_arr=theApp.sys.client_info.room.mate_arr;
	for (int i=0;i<3;i++)
	{
		if (!mate_name_arr[i].empty())
		{
			SetPlayerName(mate_name_arr[i],SerialNum2Pos(i));
		}
		else
		{
			have_player[SerialNum2Pos(i)]=false;
		}
	}
}

void CGamePlayer::OnTimer()
{

}

void CGamePlayer::Show(Gdiplus::Graphics *const g)
{

}

void CGamePlayer::ShowLandlordLogo(Gdiplus::Graphics * g)
{
	g->DrawImage(landlord_logo,landlord_logo_pos[Right]);
}

void CGamePlayer::SetPlayerName(const wstring & name,const PlayerPosition pos)
{
	player_name[pos]=name;
	have_player[pos]=true;
	AfxGetMainWnd()->InvalidateRect(Rect2CRect(head_rect[pos]));
}



void CGamePlayer::DelPlayer(const PlayerPosition pos)
{
	player_name[pos].clear();
	have_player[pos]=false;
	AfxGetMainWnd()->InvalidateRect(Rect2CRect(head_rect[pos]));
}

void CGamePlayer::SetLandlord(const PlayerPosition pos)
{
	landlord=pos;
}



Player::PlayerPosition CGamePlayer::SerialNum2Pos(const int num) const
{
	ASSERT(num>=0&&num<3);
	if (num==self_serial_num)
	{
		return Self;
	}
	const char temp[]={0,1,2,0,1};
	int flag_self=self_serial_num;
	int flag_op=flag_self;
	while(temp[++flag_op]!=num);
	return PlayerPosition(flag_op-flag_self);
}

