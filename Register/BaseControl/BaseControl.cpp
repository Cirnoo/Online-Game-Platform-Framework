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
	mCmd=nullptr;
	
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

//void CBaseControl::PaintParent()
//{
//	CRect   rect;
//	GetWindowRect(&rect); 
//	GetParent()-> ScreenToClient(&rect); 
//	GetParent()-> InvalidateRect(&rect);
//}

BEGIN_MESSAGE_MAP(CBaseControl, CWnd)
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
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


void CBaseControl::OnTrack()
{
	return;
}

// CBaseControl 消息处理程序


void CBaseControl::OnMouseLeave()
{    

	if (is_button_down)
	{
		is_button_down=false;
	}
	is_tracked	=   false;  
	//PaintParent();
	//GetParent()->UpdateWindow(); 
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
		TRACKMOUSEEVENT   tme; 
		tme.cbSize		=   sizeof(TRACKMOUSEEVENT); 
		tme.dwFlags		=   TME_LEAVE|TME_HOVER; //
		tme.hwndTrack   =   GetSafeHwnd(); 
		tme.dwHoverTime	=   80; 
		_TrackMouseEvent(&tme);  
		VarInit();
		is_tracked   =   true;
		OnTrack();
		//OnMouseHover(nFlags,point);
	}
	CWnd::OnMouseMove(nFlags, point);
}



void CBaseControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	is_button_down=true;
	//PaintParent();
	CWnd::OnLButtonDown(nFlags, point);
}

