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


CGameCtrl::CGameCtrl(CGameDlg * parent):
	data(CTool::GetInstance()),
	cur_game_state(theApp.game_action.game_state),
	main_dlg(parent),
	button_center(GAME_DLG_WIDTH/2,GAME_DLG_HEIGHT/2+100),
	button_size(100,39)
{
	ls_clear_flag=false;
	old_game_state=GameState::Wait;
	last_round_text.fill(ImgText::NONE_IMG);
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
	pack.ms_type=MS_TYPE::GAME_WIN_RQ;
	pack.buf=serial_num;
	data.DealData(pack);
}

void CGameCtrl::CreatCtrl_Pair(MS_TYPE ms_type)
{
	/************************************************************************/
	/*			叫地主	不叫 	抢地主		不抢                            */
	/************************************************************************/
	Rect rect;
	CPNGButton * button;
	using namespace ImgGroupType;
	int img_type1,img_type2;
	MS_TYPE ms_tp_re1,ms_tp_re2;
	switch (ms_type)
	{
	case MS_TYPE::IS_CALL_LANDLORD://叫地主
		img_type1=叫地主;img_type2=不叫;
		ms_tp_re1=MS_TYPE::CALL_LANDLORD_RQ;
		ms_tp_re2=MS_TYPE::NOT_CALL;
		break;
	case MS_TYPE::IS_ROB_LANDLORD:
		img_type1=抢地主;img_type2=不抢;
		ms_tp_re1=MS_TYPE::ROB_LANDLORD_RQ;
		ms_tp_re2=MS_TYPE::NOT_ROB;
	default:
		break;
	}
	rect = Rect(Point(button_center.X-button_size.Width-10,button_center.Y),button_size);
	const auto & img1=res.vec_button_img[img_type1];
	CreatCtlr(rect,img1,ms_tp_re1);

	rect.X+=button_size.Width+20;
	const auto & img2=res.vec_button_img[img_type2];
	CreatCtlr(rect,img2,ms_tp_re2);
}

void CGameCtrl::CreatCtrl_CallLandLord()
{
	CreatCtrl_Pair(MS_TYPE::IS_CALL_LANDLORD);
}

void CGameCtrl::CreatCtrl_RobLandLord()
{
	CreatCtrl_Pair(MS_TYPE::IS_ROB_LANDLORD);
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
	Rect rect(Point(button_center.X-button_size.Width*1.5-10,button_center.Y),button_size);
	CreatCtlr(rect,res.vec_button_img[准备],MS_TYPE::GAME_START);
}


void CGameCtrl::CreatCtlr(const Rect rect,const vector<pImage> & vec_img, const MS_TYPE ms_tp)
{
	CreatCtlr(rect,vec_img,[this,ms_tp]()
	{
		DATA_PACKAGE pack;
		pack.ms_type=ms_tp;
		data.DealData(pack);
		ls_clear_flag=true;
		last_round_text[Self]=GetImgTextType(ms_tp);
		if (ms_tp==MS_TYPE::PLAY_CARD||ms_tp==MS_TYPE::PASS)
		{
			cur_game_state=GameState::OtherPlay;
		}
		else
		{
			cur_game_state=GameState::OtherCall;
		}
		theApp.game_action.Increase();
	});
}

void CGameCtrl::CreatCtlr(const Rect rect,const vector<pImage> & vec_img, const std::function<void()> cmd)
{
	CPNGButton * button;
	button=new CPNGButton();
	button->Create(rect,main_dlg,ls_game_ctrl.size(),vec_img);
	button->SetCmd(cmd);
	ls_game_ctrl.emplace_back(button);
}

void CGameCtrl::ShowLastRoundText(Gdiplus::Graphics * const g) const
{
	Point point[3];
	point[Self]=Point(GAME_DLG_WIDTH/2-50,GAME_DLG_HEIGHT/2+100);
	point[Right]=Point(GAME_DLG_WIDTH/2+200,GAME_DLG_HEIGHT/2-150);
	point[Left]=Point(GAME_DLG_WIDTH/2-280,GAME_DLG_HEIGHT/2-150);
	int cnt=0;
	for (int i:last_round_text)
	{
		if (i!=ImgText::NONE_IMG)
		{
			g->DrawImage(res.vec_text_img[i],point[cnt]);
		}
		++cnt;
	}
}

ImgText::TextType CGameCtrl::GetImgTextType(const MS_TYPE ms_tp) const
{
	using namespace ImgText;
	switch (ms_tp)
	{
	case MS_TYPE::CALL_LANDLORD_RQ:
		return 叫地主;
	case MS_TYPE::NOT_CALL:
		return 不叫;
	case MS_TYPE::ROB_LANDLORD_RQ:
		return 抢地主;
	case MS_TYPE::NOT_ROB:
		return 不抢;
	default:
		return ImgText::NONE_IMG;
	}
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
	if (action_cnt>0)
	{
		int x=0;
	}
	if (main_dlg->players.SerialNum2Pos(action_cnt)!=Self)
	{
		timer=-1;
		return ;
	}
	
	old_game_state=cur_game_state;
}

void CGameCtrl::OnPaint(Gdiplus::Graphics * const g) const 
{
	for (const auto & i:ls_base_ctrl)
	{
		i->Show(g);
	}
	ShowCtrl(g);
	ShowLastRoundText(g);
	switch (cur_game_state)
	{
	case GameState::Wait:
		ShowText(g);
	default:
		break;
	}
}

void CGameCtrl::OnGameStateChange(const GameState new_state)
{
	const auto action_cnt=theApp.game_action.action_count;
	if (main_dlg->players.SerialNum2Pos(action_cnt)!=Self)
	{
		timer=-1;
		return ;
	}
	last_round_text[Self]=ImgText::NONE_IMG;
	switch (cur_game_state)
	{
	case GameState::CallLandLord:
		CreatCtrl_CallLandLord();
		break;
	case GameState::RobLandlord:
		CreatCtrl_RobLandLord();
		break;
	default:
		timer=-1;
		break;
	}
}

void CGameCtrl::ShowText(Graphics * const g) const
{
	using namespace ImgText;
	switch (cur_game_state)
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
	ASSERT(cur_game_state==GameState::Wait);
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::GAME_START;
	data.DealData(pack);
}



void CGameCtrl::SetLastRoundText(MS_TYPE ms_type,PlayerPosition pos)
{
	last_round_text[pos]=GetImgTextType(ms_type);
}

void CGameCtrl::TextClear()
{
	last_round_text.fill(ImgText::NONE_IMG);
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
	using namespace ImgText;
	vec_text_img.resize(8);
	vec_text_img[准备]=::CutImage(theApp.sys.game_tool,0,80,89,42);
	vec_text_img[抢地主]=::CutImage(theApp.sys.game_tool,0,0,89,38);
	vec_text_img[叫地主]=::CutImage(theApp.sys.game_tool,0,37,89,42);
	vec_text_img[不叫]=::CutImage(theApp.sys.game_tool,0,121,89,45);
	vec_text_img[不抢]=::CutImage(theApp.sys.game_tool,0,165,89,38);
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
