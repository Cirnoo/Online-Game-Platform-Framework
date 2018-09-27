#include "stdAfx.h"
#include "PNGButton.h"
#include "Resource.h"
#include "Sys.h"
const UINT TIMER_CONTROL =1; 

enum ButtonBg
{
	normal_bg,hover_bg,click_bg
};

CPNGButton::CPNGButton(void) { 
	this->is_checked=false;
	mouse_in_flag=false;
	is_tracked	=	false; 
	task_flag=true;
	button_down_flag=false;
	vec_bg.resize(3);
	mCmd=nullptr;
} 
CPNGButton::~CPNGButton(void) { }
IMPLEMENT_DYNCREATE(CPNGButton, CWnd)  
	BEGIN_MESSAGE_MAP(CPNGButton, CWnd)  
		//ON_WM_MOUSEHOVER()
		ON_WM_MOUSELEAVE()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_WM_LBUTTONDOWN()
//		ON_WM_MOUSEHOVER()
	END_MESSAGE_MAP()  



BOOL CPNGButton::Create(Rect rect,CWnd * pParentWnd,UINT nID, Gdiplus::Image* BG,Gdiplus::Image* _hoverBg,Gdiplus::Image* _click_bg)
{
	LPCTSTR lpszClassName=AfxRegisterWndClass( CS_HREDRAW|CS_VREDRAW ,  AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(TRANSPARENT), NULL) ;   
	SetRect(rect);
	vec_bg[normal_bg]=BG;
	vec_bg[hover_bg]=_hoverBg;
	vec_bg[click_bg]=_click_bg;
	BOOL OK=CWnd::Create(NULL,NULL,WS_CHILDWINDOW|WS_VISIBLE,RectTransform(rect),pParentWnd, nID, NULL);
	ModifyStyleEx(0, WS_EX_TRANSPARENT); 
	return OK;
}

BOOL CPNGButton::Create(Rect rect,CWnd * pParentWnd,UINT nID, std::vector<Image*>& _bg)
{
	LPCTSTR lpszClassName=AfxRegisterWndClass( CS_HREDRAW|CS_VREDRAW ,  AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(TRANSPARENT), NULL) ;   
	SetRect(rect);
	vec_bg=_bg;
	BOOL OK=CWnd::Create(NULL,NULL,WS_CHILDWINDOW|WS_VISIBLE,RectTransform(rect),pParentWnd, nID, NULL);
	ModifyStyleEx(0, WS_EX_TRANSPARENT); 
	return OK;
}

void CPNGButton::SwichControl(bool flag)
{
	task_flag=flag;
}


void CPNGButton::SetCmd(std::function<void()> cmd)
{
	mCmd=std::move(cmd);
}

void CPNGButton::SetRect(Rect rect)
{
	mRect=rect;
}

void CPNGButton::Show(Graphics* & g)
{
	if (button_down_flag)
	{
		g->DrawImage(vec_bg[click_bg],mRect);
	}
	else if(is_tracked)
	{
		g->DrawImage(vec_bg[hover_bg],mRect); 
	}
	else
	{
		g->DrawImage(vec_bg[normal_bg],mRect); 
	}
}





void CPNGButton::OnMouseLeave()
{    
	if (!task_flag)
	{
		return;
	}
	if (button_down_flag)
	{
		button_down_flag=false;
	}
	is_tracked	=   false;  
	mouse_in_flag=false;
	PaintParent();
	GetParent()->UpdateWindow(); 
	//TRACE(L"OnMouseLeave\r\n");
	CWnd::OnMouseLeave();
}





void CPNGButton::Check(bool check)
{
	if(this->is_checked!=check)
	{
		this->is_checked=check;
		Invalidate();
		UpdateWindow();
		//TRACE(L"DrawSelected\r\n");
	} /*else{  TRACE(L"Check(%d,%d)\r\n",GetDlgCtrlID(),check); }*/
}

 



void CPNGButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!button_down_flag)
	{
		return;
	}
	button_down_flag=false;
	TRACE(L"Click!\n");
	if (mCmd!=nullptr)
	{
		mCmd();
	}
	CWnd::OnLButtonUp(nFlags, point);
}



void CPNGButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!task_flag)
	{
		return;
	}
	if(!is_tracked) 
	{ 
		TRACKMOUSEEVENT   tme; 
		tme.cbSize		=   sizeof(TRACKMOUSEEVENT); 
		tme.dwFlags		=   TME_LEAVE|TME_HOVER; //
		tme.hwndTrack   =   GetSafeHwnd(); 
		tme.dwHoverTime	=   80; 
		_TrackMouseEvent(&tme);  
		is_tracked   =   true;
		mouse_in_flag=true;
		//OnMouseHover(nFlags,point);
	}
	CWnd::OnMouseMove(nFlags, point);
}



void CPNGButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	button_down_flag=true;
	PaintParent();
	GetParent()->UpdateWindow(); 
	CBaseControl::OnLButtonDown(nFlags, point);
}

