// BaseControl.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "BaseControl.h"


// CBaseControl

IMPLEMENT_DYNAMIC(CBaseControl, CWnd)

CBaseControl::CBaseControl()
{
	VarInit();
	mCmd=[=]()
	{
		this->OnClick();
	};
}

CBaseControl::~CBaseControl()
{
	
}



void CBaseControl::VarInit()
{
	is_checked=false;
	is_tracked	=	false; 
	is_button_down=false;
	is_click_move=false;
}

void CBaseControl::ControlRepaint()
{
	CRect   rect;
	GetWindowRect(&rect); 
	GetParent()-> ScreenToClient(&rect); 
	GetParent()-> InvalidateRect(&rect);
	//GetParent()->UpdateWindow(); 
}

BEGIN_MESSAGE_MAP(CBaseControl, CWnd)
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CBaseControl::SetCmd(std::function<void()> cmd)
{
	mCmd=std::move(cmd);
}

void CBaseControl::SetRect(Rect rect)
{
	mRect=rect;
}

void CBaseControl::SetImg(std::vector<Image*> & _bg)
{
	vec_bg=_bg;
}


void CBaseControl::OnClick()
{
	//左键点击默认执行此函数
	return;
}

void CBaseControl::OnTrack()
{
	//鼠标进入控件执行此函数
	TRACKMOUSEEVENT   tme; 
	tme.cbSize		=   sizeof(TRACKMOUSEEVENT); 
	tme.dwFlags		=   TME_LEAVE; //
	tme.hwndTrack   =   GetSafeHwnd(); 
	_TrackMouseEvent(&tme);
	is_tracked   =   true;
	return;
}


// CBaseControl 消息处理程序


void CBaseControl::OnMouseLeave()
{    

	VarInit();
	is_tracked	=   false;  
	ControlRepaint();
	//TRACE(L"OnMouseLeave\r\n");
	CWnd::OnMouseLeave();
}


void CBaseControl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!is_button_down)
	{
		return;
	}
	is_button_down=false;
	ControlRepaint();
	TRACE(L"Click!\n");
	if (mCmd!=nullptr)
	{
		mCmd();
	}
	CWnd::OnLButtonUp(nFlags, point);
}



void CBaseControl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!is_tracked) 
	{ 
		VarInit();
		OnTrack();
		ControlRepaint();
		//OnMouseHover(nFlags,point);
	}
	CWnd::OnMouseMove(nFlags, point);
}



void CBaseControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	is_button_down=true;
	ControlRepaint();
	CWnd::OnLButtonDown(nFlags, point);
}



void CBaseControl::OnPaint()
{
	CWnd::OnPaint();
}
