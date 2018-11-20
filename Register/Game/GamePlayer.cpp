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

	head_rect[Self]=Rect(340,GAME_DLG_HEIGHT-120,80,80);
	head_rect[Right]=Rect(GAME_DLG_WIDTH-150,250,80,80);
	head_rect[Left]=Rect(70,250,80,80);
	landlord_logo_pos[Self]=Point(GAME_DLG_WIDTH-300,GAME_DLG_HEIGHT-220);
	landlord_logo_pos[Right]=Point(GAME_DLG_WIDTH-150,100);
	landlord_logo_pos[Left]=Point(150,100);
}

CGamePlayer::~CGamePlayer(void)
{
	self_instance=nullptr;
}

void CGamePlayer::OnPaint(Gdiplus::Graphics * const g) const
{
	for (int i=Self;i<=Left;i++)
	{
		if (!player_name[i].empty())
		{
			g->DrawImage(head_img,head_rect[i]);
		}
	}
	const auto game_state=theApp.game_action.GetGameState();
	if (game_state==GameState::OurPlay||game_state==GameState::OtherPlay)
	{
		ShowLandlordLogo(g);
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

void CGamePlayer::OnFrame()
{

}


void CGamePlayer::ShowLandlordLogo(Gdiplus::Graphics * const g) const
{
	g->DrawImage(landlord_logo,landlord_logo_pos[landlord_pos]);
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
	landlord_pos=pos;
}



Player::PlayerPosition CGamePlayer::SerialNum2Pos(int num) const
{
	num%=3;
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


void CGamePlayer::OnGetMateInfo(WPARAM wParam)
{
	typedef USER_BUF MATE_INFO[3];
	const auto & info=::GetPackBufData<MATE_INFO>(wParam);
	for (int i=0;i<3;i++)
	{
		PlayerPosition pos=SerialNum2Pos(i);
		if (pos==Self)
		{
			continue;
		}
		wstring name=info[i].GetStr();
		if (name.empty())
		{
			DelPlayer(pos);
		}
		else
		{
			SetPlayerName(name,pos);
		}
	}
}

