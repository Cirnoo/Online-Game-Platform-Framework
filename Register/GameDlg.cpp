// GameDlg.cpp : 实现文件
//
#include "stdafx.h"
#include <algorithm>
#include "Register.h"
#include "GameDlg.h"
#include "afxdialogex.h"
//#include ""

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

namespace PlayerPosition
{
	enum PlayerPosition
	{
		Front,Left,Right
	};
}

using namespace PlayerPosition;
const int a=sizeof(Cards);
CGameDlg::CGameDlg(wstring master)
	: CDialogEx(CGameDlg::IDD),card_interval(25),card_up(20)
{
	m_master=master;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	InitVar();
}

CGameDlg::~CGameDlg()
{
	
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
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitVar()
{
	m_width=720*1.4;
	m_height=540*1.4;
	card_size=Size(57,80);  //牌的长宽
	poker_center=Point(m_width/2-57,m_height-250); //中间手牌位置
	lbutton_down.SetPoint(-1,-1);
	lbutton_move.SetPoint(-1,-1);
	is_lbutton_dowm=false;
	auto temp=GetImageGroup(IDB_POKER_CARDS,4,14);  //行列切割
	vec_poker.resize(55);
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<13;j++)
		{
			vec_poker[13*i+j]=temp[14*i+j];
		}
	}
	for (int i=0;i<2;i++)
	{
		vec_poker[52+i]=temp[13+14*i];
	}
	vec_poker.back()=temp[13+14*2];  //背面牌
	for (int i=0;i<13;i++)
	{
		poker_in_hand.push_back(i);
	}
	poker_in_hand.push_back(52);
	poker_in_hand.push_back(53);
	SortHand();
}

void CGameDlg::DrawHandPoker(Gdiplus::Graphics * g)
{
	auto rect=GetFirstCardRect();
	for(auto i:poker_in_hand)
	{
		auto temp=Rect(rect.GetLeft(),rect.GetTop()-card_up*i.check,card_size.Width,card_size.Height);
		g->DrawImage(vec_poker[i.toNum()],temp);
		if (i.select)
		{
			SolidBrush brush(Color(100,46,156,209));
			g->FillRectangle(&brush,temp);
		}
		rect.Offset(card_interval,0);
	}
	//g->DrawImage(vec_poker[0],rect);
}

void CGameDlg::DrawRectFrame(Gdiplus::Graphics * g)
{
	if (!is_lbutton_dowm||lbutton_move.x==-1)
	{
		return;
	}
	SolidBrush brush(Color(100, 60, 175, 228));
	Pen pen(Color(230,20,100,213));
	const auto & x1=lbutton_down.x,& x2=lbutton_move.x;
	const auto & y1=lbutton_down.y,& y2=lbutton_move.y;
	int width=abs(x2-x1);
	int height=abs(y2-y1);
	select_region=Rect(min(x1,x2),min(y1,y2),width,height);
	g->FillRectangle(&brush,select_region);
	g->DrawRectangle(&pen,select_region);
}

Rect CGameDlg::GetFirstCardRect()
{
	auto p=poker_center;
	p.X-=poker_in_hand.size()/2*card_interval;
	return Rect(p,card_size);
}

Rect CGameDlg::GetLastCardRect()
{
	auto p=poker_center;
	p.X+=(poker_in_hand.size()-poker_in_hand.size()/2-1)*card_interval;
	return Rect(p,card_size);
}

Rect CGameDlg::GetHandCardRect()
{
	auto left_rect=GetFirstCardRect();
	auto width=GetLastCardRect().GetRight()-left_rect.GetLeft();
	return Rect(left_rect.GetLeft(),left_rect.GetTop()-card_up,width,left_rect.Height+card_up);
}

int CGameDlg::SelectPoker(const CPoint & point)
{
	const auto rect=Rect2CRect(GetHandCardRect());  //是否有选中牌
	if (!rect.PtInRect(point))
	{
		return -1;
	}
	const auto right_rect=Rect2CRect(GetLastCardRect());
	int cnt=0;
	for (auto i=poker_in_hand.rbegin();i!=poker_in_hand.rend();cnt++,i++)
	{
		auto temp_rect=right_rect;
		temp_rect.OffsetRect(-card_interval*cnt,0);
		temp_rect.OffsetRect(0,-card_up*i->check);
		if (temp_rect.PtInRect(point))
		{
			i->check=!i->check;
			InvalidateRect(rect);
			TRACE("选中了第%d张牌",poker_in_hand.size()-cnt);
			break;
		}
	}
	return poker_in_hand.size()-cnt;
}

void CGameDlg::SelectMutiPoker()
{
	const auto hand_rect=GetHandCardRect();
	if (!select_region.IntersectsWith(hand_rect))
	{
		return ;
	}
	auto rect=GetFirstCardRect();
	//poker_in_hand[0].select=true;
	for(auto & i:poker_in_hand)
	{
		auto temp=Rect(rect.GetLeft()+card_interval/3,rect.GetTop()-card_up*i.check-card_interval/3,
			card_size.Width*2/3,card_size.Height*2/3);//牌能够被选到的范围比实际小点
		if (temp.IntersectsWith(select_region))
		{
			i.select=true;
		}
		else
		{
			i.select=false;
		}
		rect.Offset(card_interval,0);
	}
	InvalidateRect(Rect2CRect(GetHandCardRect()));
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	::SetWindowPos(AfxGetMainWnd()->m_hWnd, HWND_TOP , 0, 0,m_width,m_height,SWP_NOMOVE);
	CenterWindow();
	InitCtrl();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return TRUE;
}


void CGameDlg::InitCtrl()
{
	Rect rect=Rect(400,400,50,50);
	m_text[Front].Create(rect,L"等待中",theApp.sys.font);
	m_text[Left].Create(rect,L"",theApp.sys.font);
	m_text[Right].Create(rect,L"",theApp.sys.font);
}

void CGameDlg::RandomShuffle()
{
}

void CGameDlg::SortHand()
{
	std::sort(poker_in_hand.begin(),poker_in_hand.end(),
		[](Poker a, Poker b)->bool 
	{
		return a.point>b.point;     
		//每种花色13张，52和53分别为小王大王
	});

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

void CGameDlg::ShowCtrl(Gdiplus::Graphics *  g)
{
	for (int i=0;i<3;i++)
	{
		m_text->Show(g);
	}
}

void CGameDlg::OnPaint()
{
	HDC hdc = ::GetDC(this->m_hWnd);
	Graphics graphics(hdc);
	Bitmap bmp(this->m_width,this->m_height);
	Graphics* gBuf=Graphics::FromImage(&bmp);
	gBuf->DrawImage(theApp.sys.game_bg,0,0,m_width,m_height);
	//ShowCtrl(gBuf);
	DrawHandPoker(gBuf);
	DrawRectFrame(gBuf);
	graphics.DrawImage(&bmp,0,0);
	::ReleaseDC(m_hWnd,hdc);
	CDialogEx::OnPaint();
}

void CGameDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRgn rgn;
	CRect rc;
	GetWindowRect(&rc); //获得窗口矩形
	rc -= rc.TopLeft();
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 10, 10); //根据窗口矩形创建一个圆角矩形最后两个是形成圆角的大小
	SetWindowRgn(rgn, TRUE);
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
	SelectPoker(point);
	is_lbutton_dowm=true;
	lbutton_down=point;
	//SelectPoker(point);
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
	if (is_lbutton_dowm)
	{
		lbutton_move=point;
		CRect rect(lbutton_down,lbutton_move);
		InvalidateRect(rect);
		SelectMutiPoker();
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (is_lbutton_dowm)
	{
		CRect rect(lbutton_down,lbutton_move);
		InvalidateRect(rect);
		lbutton_down.SetPoint(-1,-1);
		lbutton_move.SetPoint(-1,-1);
		is_lbutton_dowm=false;
		InvalidateRect(Rect2CRect(GetHandCardRect()));
		for (auto & i:poker_in_hand)
		{
			if (i.select)
			{
				i.select=false;
				i.check=!i.check;
			}
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}
