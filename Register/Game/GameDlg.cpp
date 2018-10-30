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
	: CDialogEx(CGameDlg::IDD)
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
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CGameDlg ��Ϣ�������


void CGameDlg::InitVar()
{
	m_width=720*1.4;
	m_height=540*1.4;
	lbutton_down.SetPoint(-1,-1);
	is_lbutton_dowm=false;
	is_select_multi=false;
	
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
		[](Poker a, Poker b)->bool 
	{
		return a.point>b.point;     
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
	gBuf->DrawImage(theApp.sys.game_bg,0,0,m_width,m_height);
	//ShowCtrl(gBuf);
	logic.ShowHandPoker(gBuf);
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
	is_lbutton_dowm=true;
	lbutton_down=point;
	SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CGameDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return FALSE;
}


void CGameDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (is_lbutton_dowm)
	{
		const auto & x1=lbutton_down.x,& x2=point.x;
		const auto & y1=lbutton_down.y,& y2=point.y;
		int width=abs(x2-x1);
		int height=abs(y2-y1);
		select_region=Rect(min(x1,x2),min(y1,y2),width,height);
		InvalidateRect(Rect2CRect(select_region));
		if(logic.SelectMutiPoker(select_region))
		{
			InvalidateRect(Rect2CRect(logic.GetHandCardRect()));
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (is_lbutton_dowm)
	{

		lbutton_down.SetPoint(-1,-1);
		for (auto & i:logic.poker_in_hand)
		{
			if (i.select)
			{
				i.select=false;
				i.check=!i.check;
			}
		}
		if (!is_select_multi)
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (logic.IsLegalOutput())
	{
		//�Ϸ��ĳ���	
		auto need_send=logic.GetCheckedCards();
		ArrayType arrtype=logic.GetCardsArrType();
		TRACE("��������:%d\n",arrtype);
	}
	else
	{
		//�����Ϣ
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}
