// GameDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include <algorithm>
#include "Register.h"
#include "GameDlg.h"
#include "afxdialogex.h"
//#include ""

// CGameDlg �Ի���

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
	: CDialogEx(CGameDlg::IDD),card_interval(25)
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
END_MESSAGE_MAP()


// CGameDlg ��Ϣ�������


void CGameDlg::InitVar()
{
	m_width=720*1.4;
	m_height=540*1.4;
	card_size=Size(57,80);
	poker_center=Point(m_width/2-57,m_height-250);
	auto temp=GetImageGroup(IDB_POKER_CARDS,4,14);
	vec_poker.resize(55);
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<13;j++)
		{
			vec_poker[13*i+j]=temp[14*i+j];
		}
	}
	for (int i=0;i<3;i++)
	{
		vec_poker[52+i]=temp[13+14*i];
	}

	for (int i=0;i<13;i++)
	{
		poker_in_hand.push_back(i);
	}
	poker_in_hand.push_back(52);
	poker_in_hand.push_back(53);
	SortHand();
}

void CGameDlg::ShowHandPoker(Gdiplus::Graphics * g)
{
	auto rect=GetFirstCardRect();
	for(auto i:poker_in_hand)
	{
		rect.Offset(card_interval,0);
		g->DrawImage(vec_poker[i],rect);
	}
	//g->DrawImage(vec_poker[0],rect);
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
	p.X+=(poker_in_hand.size()-poker_in_hand.size()/2)*card_interval;
	return Rect(p,card_size);
}

Rect CGameDlg::GetHandCardRect()
{
	auto left_rect=GetFirstCardRect();
	auto width=GetLastCardRect().GetRight()-left_rect.GetLeft();
	return Rect(left_rect.GetLeft(),left_rect.GetTop(),width,left_rect.Height);
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	::SetWindowPos(AfxGetMainWnd()->m_hWnd, HWND_TOP , 0, 0,m_width,m_height,SWP_NOMOVE);
	CenterWindow();
	InitCtrl();
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	return TRUE;
}


void CGameDlg::InitCtrl()
{
	Rect rect=Rect(400,400,50,50);
	m_text[Front].Create(rect,L"�ȴ���",theApp.sys.font);
	m_text[Left].Create(rect,L"",theApp.sys.font);
	m_text[Right].Create(rect,L"",theApp.sys.font);
}

void CGameDlg::RandomShuffle()
{
}

void CGameDlg::SortHand()
{
	std::sort(poker_in_hand.begin(),poker_in_hand.end(),
		[](char a, char b)->bool 
	{
		return a<13*4 && b<13*4?a%13>b%13:a>b;     
		//ÿ�ֻ�ɫ13�ţ�52��53�ֱ�ΪС������
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
	//gBuf->DrawImage(theApp.sys.game_bg,0,0,m_width,m_height);
	//ShowCtrl(gBuf);
	ShowHandPoker(gBuf);
	graphics.DrawImage(&bmp,0,0);
	::ReleaseDC(m_hWnd,hdc);
	CDialogEx::OnPaint();
}

void CGameDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRgn rgn;
	CRect rc;
	GetWindowRect(&rc); //��ô��ھ���
	rc -= rc.TopLeft();
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 10, 10); //���ݴ��ھ��δ���һ��Բ�Ǿ�������������γ�Բ�ǵĴ�С
	SetWindowRgn(rgn, TRUE);
}


void CGameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (point.y<20)
	{
		PostMessage(WM_NCLBUTTONDOWN,
			HTCAPTION,
			MAKELPARAM(point.x, point.y));
	}
	auto rect=Rect2CRect(GetHandCardRect()); 
	const auto px=point.x;
	const auto py=point.y;
	if(rect.PtInRect(point)) //�Ƿ�ѡ����
	{
		auto right_rect=Rect2CRect(GetLastCardRect());
		int cnt=0;
		for (auto i=poker_in_hand.rbegin();i!=poker_in_hand.rend();cnt++,i++)
		{
			if (right_rect.PtInRect(point))
			{
				TRACE("ѡ���˵�%d����",poker_in_hand.size()-cnt);
				break;
			}
			right_rect.OffsetRect(-card_interval,0);
		}
	}
	SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}
