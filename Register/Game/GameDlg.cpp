// GameDlg.cpp : 实现文件
//
#include "stdafx.h"
#include <algorithm>
#include "Register.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "GameCtrl.h"

//#include ""

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(const wstring master,const int num)
	: CDialogEx(CGameDlg::IDD),
	game_ctrl(CGameCtrl::GetInstance(this)),
	logic(CPokerLogic::GetInstance()),
	players(CGamePlayer::GetInstance(theApp.sys.user.name.GetStr())),
	self_serial_num(num)
{
	ASSERT(num>0&&num<3);
	m_master=master;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	InitVar();
}

CGameDlg::~CGameDlg()
{
	delete back_img;
	delete &game_ctrl;
	delete &logic;
	delete &players;
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_MESSAGE(WM_GET_ROOM_MATE,CGameDlg::OnGetMateInfo)
	ON_MESSAGE(WM_GET_CARDS,CGameDlg::OnGetCards)
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
	game_timer=0;
	game_state=GameState::Wait;
	have_player[Self]=true;
	have_player[Left]=false;
	have_player[Right]=false;
}



void CGameDlg::DrawRectFrame(Gdiplus::Graphics * g)
{
	if (!is_lbutton_dowm||lbutton_down.x==-1)
	{
		return;
	}
	SolidBrush brush(Color(100, 60, 175, 228));
	Pen pen(Color(230,20,100,213));
	
	g->FillRectangle(&brush,select_region);
	g->DrawRectangle(&pen,select_region);
}



void CGameDlg::ShowPlayer(Gdiplus::Graphics * g)
{
	players.Show(g);
	switch (game_state)
	{
	case GameState::Wait:

		break;
	case GameState::GetCards:
		ASSERT(21-game_timer>=0);
		logic.ShowDealingCardsEffect(g,21-game_timer);		//发牌效果
		players.ShowLandlordLogo(g);
		break;
	case GameState::Ready:
		logic.ShowHandPoker(g);
		logic.ShowFinalThreeCards(g);
		
		break;
	case GameState::Gaming:
		logic.ShowHandPoker(g);
		logic.ShowLastRoundPoker(g);
		break;
	case GameState::Over:
		break;
	default:
		break;
	}
}

Player::PlayerPosition CGameDlg::SerialNum2Pos(const int num) const
{
	ASSERT(num>0&&num<3);
	const char temp[]={0,1,2,0,1};
	int flag_self=self_serial_num;
	int flag_op=flag_self;
	while(temp[++flag_op]!=num);
	return PlayerPosition(flag_op-flag_self);
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	::SetWindowPos(AfxGetMainWnd()->m_hWnd, HWND_TOP , 0, 0,m_width,m_height,SWP_NOMOVE);
	SetClassLong(this->m_hWnd, GCL_STYLE, GetClassLong(this->m_hWnd, GCL_STYLE) | CS_DROPSHADOW);
	CenterWindow();
	game_ctrl.InitCtrl();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SetTimer(IDC_GAME_TIMER,300,NULL);
	vector<char> temp(53);
	for (int i=0;i<53;i++)
	{
		temp[i]=i;
	}

	//ASSERT(game_state==GameState::GetCards);
	logic.SetPlayerPoker(temp,self_serial_num);
	return TRUE;
}




void CGameDlg::GameStart()
{
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::GAME_START;
	theApp.tools.DealData(pack);
}

void CGameDlg::AddPlayer()
{
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::ADD_PLAYER;
	theApp.tools.DealData(pack);
}


void CGameDlg::OnPaint()
{
	HDC hdc = ::GetDC(this->m_hWnd);
	Graphics graphics(hdc);
	Bitmap bmp(this->m_width,this->m_height);
	//PaintIrregularDlg(hdc,back_img);
	Graphics* gBuf=Graphics::FromImage(&bmp);
	gBuf->DrawImage(back_img,0,0,m_width,m_height);
	ShowPlayer(gBuf);
	game_ctrl.Show(gBuf);
	DrawRectFrame(gBuf);
	graphics.DrawImage(&bmp,0,0);
	::ReleaseDC(m_hWnd,hdc);
	delete gBuf;
	CDialogEx::OnPaint();
}

void CGameDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	//CRgn rgn;
	//CRect rc;
	//GetWindowRect(&rc); //获得窗口矩形
	//rc -= rc.TopLeft();
	//rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 10, 10); //根据窗口矩形创建一个圆角矩形最后两个是形成圆角的大小
	//SetWindowRgn(rgn, TRUE);
}


void CGameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.y<20)
	{
		PostMessage(WM_NCLBUTTONDOWN,
			HTCAPTION,
			MAKELPARAM(point.x, point.y));
	}
	else
	{
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
		select_region=Rect(min(x1,x2),min(y1,y2),width,height);
		InvalidateRect(Rect2CRect(select_region));
		is_select_multi=true;
		logic.SelectMutiPoker(select_region);
		InvalidateRect(Rect2CRect(logic.GetHandCardRect()));
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (is_lbutton_dowm)
	{
		lbutton_down.SetPoint(-1,-1);
		if (is_select_multi)
		{
			logic.FinishSelect();
		}
		else
		{
			logic.SelectPoker(point);
		}
		is_lbutton_dowm=false;
		is_select_multi=false;
		InvalidateRect(Rect2CRect(select_region));
		InvalidateRect(Rect2CRect(logic.GetHandCardRect()));
	}
	
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CGameDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (logic.IsLegalOutput())
	{
		//合法的出牌	
		CardArray cards=logic.GetCardsNeedSend();
		logic.DelCheckedCards();
		InvalidateRect(Rect2CRect(logic.GetHandCardRect()));
		//TRACE("出牌类型:%d\n",cards.type);
	}
	else
	{
		//输出信息
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(game_state)
	{
	case GameState::GetCards:
		if (--game_timer==1)
		{
			logic.SortHand();
		}
		else if (game_timer==0)
		{
			game_state=GameState::Ready;
			game_timer=20;
			OnSetLandlord(NULL,NULL);
		}
		Invalidate();
		break;
	case GameState::Ready:
		if (--game_timer==0)
		{

		}
		break;
	case GameState::Gaming:
		--game_timer;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CGameDlg::OnGetMateInfo(WPARAM wParam, LPARAM lParam)
{
	typedef PLAYER_INFO MATE_INFO[2];
	MATE_INFO * info=(MATE_INFO *) wParam;
	wstring name[2];
	PlayerPosition pos[2];
	for(int i=0;i<2;i++)
	{
		name[i]=info[i]->name.GetStr();
		if (name[i].empty())
		{
			continue;
		}
		pos[i]=SerialNum2Pos(info[i]->pos);
		have_player[pos[i]]=true;
		players.SetPlayerName(name[i],pos[i]);
	}
	
	return 0;
}

LRESULT CGameDlg::OnDelPlayer(WPARAM wParam, LPARAM lParam)
{
	PLAYER_INFO * info = (PLAYER_INFO *) wParam;
	auto pos=SerialNum2Pos(info->pos);
	have_player[pos]=false;
	return 0;
}

LRESULT CGameDlg::OnGetCards(WPARAM wParam, LPARAM lParam)
{
	vector<char> temp(53);
	for (int i=0;i<53;i++)
	{
		temp.push_back(i);
	}
	ASSERT(game_state==GameState::GetCards);
	logic.SetPlayerPoker(temp,self_serial_num);
	game_timer=17;
	return 0;
}

LRESULT CGameDlg::OnSetLandlord(WPARAM wParam, LPARAM lParam)
{
	ASSERT(game_state==GameState::Ready);
	logic.SetLandlord(Self);
	players.SetLandlord(Self);
	return 0;
}

LRESULT CGameDlg::OnGameWin(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


