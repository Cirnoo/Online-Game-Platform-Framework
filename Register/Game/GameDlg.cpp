// GameDlg.cpp : 实现文件
//
#include "stdafx.h"
#include <algorithm>
#include "Register.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "GameCtrl.h"
#include "GameActionCtrl.h"
#include "Packdef.h"
#include <mutex>
//#include ""

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)


CGameDlg::CGameDlg(const int self_serial_num)
	: CDialogEx(CGameDlg::IDD),
	game_ctrl(CGameCtrl::GetInstance(this)),
	logic(CPokerLogic::GetInstance()),
	players(CGamePlayer::GetInstance(self_serial_num)),
	have_player(players.have_player),
	r_game_state(theApp.game_action.GetStateReference()),
	room_info(theApp.sys.client_info.room)
{
	ASSERT(self_serial_num>=0 && self_serial_num<3);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	have_player=players.have_player;
	InitVar();
	vec_ctrl.push_back(&players);
	vec_ctrl.push_back(&game_ctrl);
	vec_ctrl.push_back(&logic);
	theApp.game_action.SetSelfSerialNum(self_serial_num);
	/*for (auto & i:theApp.sys.client_info.room.mate_arr)
	{
	i=L"test";
	}
	vector<char> temp;
	for (int i=0;i<53;i++)
	{
	temp.push_back(i);
	}
	logic.SetPlayerPoker(temp,Self);*/
	r_game_state=GameState::Wait;
}

CGameDlg::~CGameDlg()
{
	/*SetEvent(thread_exit_flag);
	if(WAIT_TIMEOUT == WaitForSingleObject(h_Thread,200))
	{
	TerminateThread(h_Thread,-1);
	}
	CloseHandle(h_Thread);*/
	delete back_img;
	delete bit_buf;
	delete gra_buf;
	for (auto i:vec_ctrl)
	{
		delete i;
	}
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_MESSAGE(WM_GET_ROOM_MATE,CGameDlg::OnGetMateInfo)
	ON_MESSAGE(WM_GET_CARDS,CGameDlg::OnGetCards)
	ON_MESSAGE(WM_GAME_STATE_CHANGE,CGameDlg::OnGameStateChange)
	ON_MESSAGE(WM_GAME_PROCESS,CGameDlg::OnGameProcess)
	ON_MESSAGE(WM_SET_LANDLORD,CGameDlg::OnSetLandlord)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitVar()
{
	m_width=GAME_DLG_WIDTH;
	m_height=GAME_DLG_HEIGHT;
	lbutton_down.SetPoint(-1,-1);
	is_lbutton_dowm=false;
	is_select_multi=false;
	back_img=::LoadPNGFormResource(IDB_GAME_BG);
	bit_buf=new Bitmap(this->m_width,this->m_height);
	gra_buf=Graphics::FromImage(bit_buf);
}



void CGameDlg::DrawRectFrame(Gdiplus::Graphics * g)
{
	if (!is_lbutton_dowm||!is_select_multi||lbutton_down.x==-1)
	{
		return;
	}
	SolidBrush brush(Color(100, 60, 175, 228));
	Pen pen(Color(230,20,100,213));
	
	g->FillRectangle(&brush,select_region);
	g->DrawRectangle(&pen,select_region);
}

UINT OnTimer(LPVOID  lpParam)
{
	CGameDlg * self = (CGameDlg *)lpParam;
	while (WaitForSingleObject(self->thread_exit_flag,0)==WAIT_TIMEOUT)
	{
		self->OnTimer(0);
		Sleep(100);
	}
	return 0;
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	::SetWindowPos(this->m_hWnd, HWND_TOP , 0, 0,m_width,m_height,SWP_NOMOVE);
	SetClassLong(this->m_hWnd, GCL_STYLE, GetClassLong(this->m_hWnd, GCL_STYLE) | CS_DROPSHADOW);
	CenterWindow();
	for (auto i:vec_ctrl)
	{
		i->OnInit();
	}
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	thread_exit_flag=CreateEvent(NULL,TRUE,FALSE,L"test");
	SetTimer(IDC_GAME_TIMER,100,NULL);		//100ms调用一次Ontimer,10次为1s
	//h_Thread = AfxBeginThread(::OnTimer,this,THREAD_PRIORITY_NORMAL,0,0);	
	return TRUE;
}


void CGameDlg::OnPaint()
{
	HDC hdc = ::GetDC(this->m_hWnd);
	Graphics graphics(hdc);
	gra_buf->DrawImage(back_img,0,0,m_width,m_height);
	for (auto i:vec_ctrl)
	{
		i->OnPaint(gra_buf);
	}
	DrawRectFrame(gra_buf);
	graphics.DrawImage(bit_buf,0,0);
	::ReleaseDC(m_hWnd,hdc);
	CDialogEx::OnPaint();
}



void CGameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.y<20)
	{
		SendMessage(WM_NCLBUTTONDOWN,
			HTCAPTION,
			MAKELPARAM(point.x, point.y));
	}
	else
	{
		CRect rect;
		GetWindowRect(rect);
		ClipCursor(rect);
		is_lbutton_dowm=true;
		lbutton_down=point;
	}
	SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CGameDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return FALSE;
}


void CGameDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (is_lbutton_dowm && point!=lbutton_down)
	{
		const auto & x1=lbutton_down.x,& x2=point.x;
		const auto & y1=lbutton_down.y,& y2=point.y;
		int width=abs(x2-x1);
		int height=abs(y2-y1);
		//重绘选择框
		CRgn old_regin,new_region;
		old_regin.CreateRectRgnIndirect(Rect2CRect(select_region));

		select_region=Rect(min(x1,x2),min(y1,y2),width,height);
		new_region.CreateRectRgnIndirect(Rect2CRect(select_region));
		new_region.CombineRgn(&new_region,&old_regin,RGN_XOR);
		InvalidateRgn(&new_region);
		is_select_multi=true;
		logic.SelectMutiPoker(select_region);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (is_lbutton_dowm)
	{
		lbutton_down.SetPoint(-1,-1);
		is_lbutton_dowm=false;
		ClipCursor(NULL);
		InvalidateRect(Rect2CRect(select_region));
		if (r_game_state==GameState::OurPlay||r_game_state==GameState::OtherPlay)
		{
			if (is_select_multi)
			{
				logic.FinishMutiSelect();
			}
			else
			{
				logic.SelectPoker(point);
			}
			InvalidateRect(Rect2CRect(logic.GetHandCardRect()));
		}
		is_select_multi=false;
	}
	
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CGameDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (r_game_state==GameState::OurPlay)
	{
		game_ctrl.OurPlayCards();
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	for (auto i:vec_ctrl)
	{
		i->OnTimer();
	}
	if(++m_timer%15==0)
	{
		Invalidate(FALSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CGameDlg::OnGetMateInfo(WPARAM wParam, LPARAM lParam)
{
	players.OnGetMateInfo(wParam);
	if(theApp.game_action.GetSelfSeriaNum()==0 && r_game_state==GameState::Wait && std::count(have_player.begin(),have_player.end(),true)==3)
	{
		//可以开始游戏了
		game_ctrl.GameStart();
	}
	return 0;
}


LRESULT CGameDlg::OnGetCards(WPARAM wParam, LPARAM lParam)
{
	ASSERT(r_game_state==GameState::Wait);
	const auto & poker_group=::GetPackBufData<AllocCardMs>(wParam);
	logic.SetPlayerPoker(poker_group.poker,theApp.game_action.GetSelfSeriaNum());
	theApp.game_action.action_count=poker_group.first_pos;		//确定先手
	r_game_state=GameState::GetCards;
	return 0;
}

LRESULT CGameDlg::OnSetLandlord(WPARAM wParam, LPARAM lParam)
{
	//设置地主位置 游戏正式开始
	ASSERT(r_game_state==GameState::OtherCall);
	const auto & process=::GetPackBufData<GAME_PROCESS>(wParam);
	auto & action = theApp.game_action;
	const char land_num=process.landlord_pos;		//地主序列号
	action.action_count=land_num;
	const auto land_pos=action.GetCurActPlayerPos();		//转换为相对位置
	PlayerPosition last_player=action.SerialNum2Pos(process.last_player_pos);
	game_ctrl.SetLastRoundText(process.last_palyer_ms,last_player);
	std::thread do_later([land_pos,this]
	{
		Sleep(500);
		if (land_pos==Self)
		{
			r_game_state=GameState::OurPlay;
		}
		else
		{
			r_game_state=GameState::OtherPlay;
		}
		logic.SetLandlord(land_pos);
		players.SetLandlord(land_pos);
		game_ctrl.TextClear();
		Invalidate(FALSE);
		return ;
	});
	do_later.detach();
	return 0;
}

LRESULT CGameDlg::OnGameWin(WPARAM wParam, LPARAM lParam)
{
	return 0;
}



LRESULT CGameDlg::OnGameStateChange(WPARAM wParam, LPARAM lParam)
{
	for (auto & i:vec_ctrl)
	{
		i->OnGameStateChange(r_game_state);
	}
	Invalidate(FALSE);
	return 0;
}

LRESULT CGameDlg::OnGameProcess(WPARAM wParam, LPARAM lParam)
{
	//抢地主和出牌的状态处理
	DATA_PACKAGE * pack=(DATA_PACKAGE *)wParam;
	const auto & process=::GetPackBufData<GAME_PROCESS>(wParam);
	auto & action=theApp.game_action;
	action.action_count=process.last_player_pos+1;
	PlayerPosition last_player=players.SerialNum2Pos(process.last_player_pos);
	bool is_self_turn=players.SerialNum2Pos(process.last_player_pos+1)==Self;
	switch (pack->ms_type)
	{
	case MS_TYPE::IS_CALL_LANDLORD:
		r_game_state=is_self_turn
			?GameState::CallLandLord
			:GameState::OtherCall;
		break;
	case MS_TYPE::IS_ROB_LANDLORD:
		r_game_state=is_self_turn
			?GameState::RobLandlord
			:GameState::OtherCall;
		break;
	case MS_TYPE::IS_PALY_CARD:
		r_game_state=is_self_turn
			?GameState::OurPlay
			:GameState::OtherPlay;
		logic.MatePlayCards(process.card_arr,last_player);
		break;
	}
	game_ctrl.SetLastRoundText(process.last_palyer_ms,last_player);
	return 0;
}

