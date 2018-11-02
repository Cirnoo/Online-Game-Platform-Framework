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
enum GameState
{
	Wait,Ready,Gaming,Over
};
IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)


CGameDlg::CGameDlg(wstring master,int num)
	: CDialogEx(CGameDlg::IDD),
	game_ctrl(CGameCtrl::GetInstance()),
	self_serial_num(num)
{
	ASSERT(num<0||num>=3);
	m_master=master;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	InitVar();
}

CGameDlg::~CGameDlg()
{
	delete &game_ctrl;
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
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitVar()
{
	m_width=GAME_DLG_WIDTH;
	m_height=GAME_DLG_HEIGHT;
	lbutton_down.SetPoint(-1,-1);
	is_lbutton_dowm=false;
	is_select_multi=false;
	for (int i=0;i<3;i++)
	{
		player_arr[i]=nullptr;
	}
	player_arr[Self].reset(new CGamePlayer(Self));
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
	for (int i=0;i<3;i++)
	{
		if (player_arr[i])
		{
			player_arr[i]->Show(g);
		}
	}
}

Player::PlayerPosition CGameDlg::SerialNum2Pos(const int num)
{
	ASSERT(num<0||num>=3);
	const char temp[]={0,1,2,0,1};
	int flag_self=self_serial_num;
	int flag_op=flag_self;
	while(temp[++flag_op]!=num);
	return PlayerPosition(flag_op-flag_self);
}

CPokerLogic & CGameDlg::GetSelfPokerLogic()
{
	return player_arr[Self]->logic;
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	::SetWindowPos(AfxGetMainWnd()->m_hWnd, HWND_TOP , 0, 0,m_width,m_height,SWP_NOMOVE);
	SetClassLong(this->m_hWnd, GCL_STYLE, GetClassLong(this->m_hWnd, GCL_STYLE) | CS_DROPSHADOW);
	CenterWindow();
	game_ctrl.InitCtrl(this);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
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
	Graphics* gBuf=Graphics::FromImage(&bmp);
	gBuf->DrawImage(theApp.sys.game_bg,0,0,m_width,m_height);
	game_ctrl.Show(gBuf);
	ShowPlayer(gBuf);
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
		auto & logic=GetSelfPokerLogic();
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
		auto & logic=GetSelfPokerLogic();
		if (is_select_multi)
		{
			for (auto & i:logic.GetSelfPoker())
			{
				if (i.select)
				{
					i.select=false;
					i.check=!i.check;
				}
			}
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
	auto & logic=GetSelfPokerLogic();
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
