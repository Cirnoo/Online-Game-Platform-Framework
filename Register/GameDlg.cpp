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
CGameDlg::CGameDlg(CString master)
	: CDialogEx(CGameDlg::IDD)
{
	m_master=master;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
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


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_width=720*1.4;
	m_height=540*1.4;
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
	m_text[Front].Create(rect,L"�ȴ���",sys.font);
	m_text[Left].Create(rect,L"",sys.font);
	m_text[Right].Create(rect,L"",sys.font);
}

void CGameDlg::RandomShuffle()
{
}

void CGameDlg::SortHand()
{
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
	//gBuf->DrawImage(sys.game_bg,0,0,m_width,m_height);
	ShowCtrl(gBuf);
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
	
	SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}
