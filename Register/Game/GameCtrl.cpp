#include "stdafx.h"
#include "GameCtrl.h"
#include "Tool.h"
#include "GameDlg.h"
#include <thread>
CGameCtrl * CGameCtrl::self=nullptr;
CGameCtrl & CGameCtrl::GetInstance(CGameDlg * parent)  //饿汉式
{
	if (self==nullptr)
	{
		self = new CGameCtrl(parent);
	}
	return *self;
}
namespace ImgGroupType
{
	enum  
	{
		出牌,不出,提示,不叫,不抢,叫地主,抢地主,准备
	};
}
namespace ImgTextType
{
	enum 
	{
		不出,抢地主,叫地主,准备,没大牌
	};
}

CGameCtrl::CGameCtrl(CGameDlg * parent):
	data(CTool::GetInstance()),
	game_state(theApp.game_action.game_state),
	main_dlg(parent),
	button_center(GAME_DLG_WIDTH/2,GAME_DLG_HEIGHT/2+100),
	button_size(100,39)
{
	ls_clear_flag=false;
}


CGameCtrl::~CGameCtrl(void)
{
	self=nullptr;
	/*DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::LEAVE_ROOM;
	pack.buf=USER_BUF(main_dlg->m_master);
	data.DealData(pack);*/
}





void CGameCtrl::OnGameWin(const int serial_num)
{
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::GAME_WIN;
	pack.buf=serial_num;
	data.DealData(pack);
}

void CGameCtrl::CreatCtrl_LandLord(bool is_first)
{
	/************************************************************************/
	/*			叫地主	不叫 	抢地主		不抢                            */
	/************************************************************************/
	Rect rect;
	CPNGButton * button;
	using namespace ImgGroupType;
	//叫地主
	rect = Rect(Point(button_center.X-button_size.Width-10,button_center.Y),button_size);
	const auto & img1=res.vec_button_img[is_first?叫地主:抢地主];
	CreatCtlr(rect,MS_TYPE::WANT_LANDLORD,img1);

	//不叫
	button=new CPNGButton();
	rect.X+=button_size.Width+20;
	const auto & img2=res.vec_button_img[is_first?不叫:不抢];
	CreatCtlr(rect,MS_TYPE::NOT_WANT_LANDLORD,img2);
}

void CGameCtrl::ShowCtrl(Gdiplus::Graphics * const g) const
{
	for (const auto & i:ls_game_ctrl)
	{
		i->Show(g);
	}
}

void CGameCtrl::CreatCtlr_Wait()
{
	/************************************************************************/
	/*						      开始                                      */
	/************************************************************************/
	using namespace ImgGroupType;
	CPNGButton * button;
	button=new CPNGButton();
	Rect rect(Point(button_center.X-button_size.Width*1.5-10,button_center.Y),button_size);
	CreatCtlr(rect,MS_TYPE::GAME_START,res.vec_button_img[准备]);
}

void CGameCtrl::CreatCtlr_DealCard()
{
	/************************************************************************/
	/*			           出牌      不出						            */
	/************************************************************************/
	Rect rect;
	CPNGButton * button;
	using namespace ImgGroupType;
	//叫地主
	rect = Rect(Point(button_center.X-button_size.Width-10,button_center.Y),button_size);
	const auto & img1=res.vec_button_img[出牌];
	CreatCtlr(rect,MS_TYPE::WANT_LANDLORD,img1);

	//不叫
	button=new CPNGButton();
	rect.X+=button_size.Width+20;
	const auto & img2=res.vec_button_img[不出];
	CreatCtlr(rect,MS_TYPE::NOT_WANT_LANDLORD,img2);
}

void CGameCtrl::CreatCtlr(const Rect rect,const MS_TYPE ms_tp,const vector<pImage> & vec_img)
{
	CPNGButton * button;
	button=new CPNGButton();
	button->Create(rect,main_dlg,ls_game_ctrl.size(),vec_img);
	button->SetCmd([=]()
	{
		DATA_PACKAGE pack;
		pack.ms_type=ms_tp;
		data.DealData(pack);
		ls_clear_flag=true;
	});
	ls_game_ctrl.emplace_back(button);
}

void CGameCtrl::OnInit()
{
	const int IDG_MIN   = 10000;
	const int IDG_CLOSE = 10001;
	const int bt_width  = res.vec_min[0]->GetWidth();
	const int bt_height = res.vec_min[0]->GetHeight();

	const CRect rectDlg(0,0,GAME_DLG_WIDTH,GAME_DLG_HEIGHT);

	Rect rect=Rect(rectDlg.Width()-bt_width*1.6,5,bt_width,bt_height);

	bt_close.Create(rect,main_dlg,IDG_CLOSE,res.vec_close);
	bt_close.SetCmd([this]()
	{
		main_dlg->PostMessageW(WM_CLOSE);
	});
	ls_base_ctrl.push_back(&bt_close);
	rect.X-=bt_width*1.5;
	bt_min.Create(rect,main_dlg,IDG_MIN,res.vec_min);
	bt_min.SetCmd([this]()
	{
		main_dlg->PostMessageW(WM_SYSCOMMAND ,SC_MINIMIZE, 0);
	});
	ls_base_ctrl.push_back(&bt_min);
}

void CGameCtrl::OnFrame()
{
	if (ls_clear_flag)
	{
		ls_game_ctrl.clear();
		ls_clear_flag=false;
	}

	const auto action_cnt=theApp.game_action.action_count;
	switch (game_state)
	{
	case GameState::SelectLandLord:
		if (timer==0)
		{
			CreatCtrl_LandLord(ls_game_ctrl,action_cnt==0);
		}
		break;
	default:
		timer=-1;
		break;
	}
	
}

void CGameCtrl::OnPaint(Gdiplus::Graphics * const g) const 
{
	for (const auto & i:ls_base_ctrl)
	{
		i->Show(g);
	}
	for (auto & i:ls_game_ctrl)
	{
		i->Show(g);
	}
	switch (game_state)
	{
	case GameState::Wait:
		ShowText(g);
	default:
		break;
	}
}

void CGameCtrl::ShowText(Graphics * const g) const
{
	using namespace ImgTextType;
	switch (game_state)
	{
	case GameState::Wait:
		{
			Point point[3];
			point[Self]=Point(GAME_DLG_WIDTH/2-50,GAME_DLG_HEIGHT/2+100);
			point[Right]=Point(GAME_DLG_WIDTH/2+200,GAME_DLG_HEIGHT/2-100);
			point[Left]=Point(GAME_DLG_WIDTH/2-300,GAME_DLG_HEIGHT/2-100);
			const auto & img=res.vec_text_img[准备];
			for (int i=Self;i<=Left;i++)
			{
				if (main_dlg->have_player[i])
				{
					g->DrawImage(img,point[i]);
				}
			}
			
		}
		break;
	default:
		break;
	}
}


void CGameCtrl::GameStart() 
{
	ASSERT(game_state==GameState::Wait);
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::GAME_START;
	data.DealData(pack);
}



CGameCtrl::GameRes::GameRes()
{
	auto vec_temp=::GetImageGroup(IDB_GAME_CTRL,2,3);
	for (auto & i:vec_temp)
	{
		i=ResizeImg(i,0.4);
	}
	for (int i=0;i<3;i++)
	{
		vec_min.push_back(vec_temp[i]);
	}
	for (int i=3;i<6;i++)
	{
		vec_close.push_back(vec_temp[i]);
	}

	vec_temp=::GetImageGroup(IDB_GAME_BUTTON,7,3);
	for (int i=0;i<7;i++)
	{
		vec_button_img[i].resize(3);
		for (int j=0;j<3;j++)
		{
			vec_button_img[i][j]=vec_temp[3*i+j];
		}
	}
	using namespace ImgTextType;
	vec_text_img.resize(5);
	vec_text_img[准备]=::CutImage(theApp.sys.game_tool,0,80,89,42);
}

CGameCtrl::GameRes::~GameRes()
{
	for (auto i:vec_min)
	{
		delete i;
	}
	for (auto i:vec_close)
	{
		delete i;
	}

	for (auto i:vec_button_img)
	{
		for (auto j:i)
		{
			delete j;
		}
	}
	for (auto i:vec_text_img)
	{
		delete i;
	}
}
