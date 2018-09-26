#include "stdAfx.h"
#include "PNGButton.h"
#include "Resource.h"
#include "Sys.h"
const UINT TIMER_CONTROL =1; 
CRect RectTransform(Rect);



CPNGButton::CPNGButton(void) { 
	this->m_is_checked=false;
	mouse_in_flag=false;
	m_is_tracked	=	false; 
	mCmd=0;
	task_flag=true;
	button_down_flag=false;
	bg=nullptr;
	hover_bg=nullptr;
	click_bg=nullptr;
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


BOOL CPNGButton::Create(Rect rect,CWnd * pParentWnd,UINT nID, Gdiplus::Image* BG,Gdiplus::Image* _hoverBg,Gdiplus::Image* _click_bg,int cmd)
{
	LPCTSTR lpszClassName=AfxRegisterWndClass( CS_HREDRAW|CS_VREDRAW ,  AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(TRANSPARENT), NULL) ;   
	bg=BG;
	SetRect(rect);
	hover_bg=_hoverBg;
	click_bg=_click_bg;
	BOOL OK=CWnd::Create(NULL,NULL,WS_CHILDWINDOW|WS_VISIBLE,RectTransform(rect),pParentWnd, nID, NULL);
	ModifyStyleEx(0, WS_EX_TRANSPARENT); 
	mCmd=cmd;
	return OK;
}

void CPNGButton::SwichControl(bool flag)
{
	task_flag=flag;
}

void CPNGButton::SetRect(Rect rect)
{
	mRect=rect;
}

void CPNGButton::Show(Graphics* & g)
{
	if (button_down_flag)
	{
		g->DrawImage(click_bg,mRect);
	}
	else if(m_is_tracked)
	{
		g->DrawImage(hover_bg,mRect); 
	}
	else
	{
		g->DrawImage(this->bg,mRect); 
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
	m_is_tracked	=   false;  
	mouse_in_flag=false;
	PaintParent();
	GetParent()->UpdateWindow(); 
	//TRACE(L"OnMouseLeave\r\n");
	CWnd::OnMouseLeave();
}





void CPNGButton::Check(bool check)
{
	if(this->m_is_checked!=check)
	{
		this->m_is_checked=check;
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
	switch (mCmd)
	{
	case CMD_CLOSE:
		GetParent()->SendMessage(WM_CLOSE ,0, 0); 
	case CMD_MINSIZE:
		GetParent()->SendMessage(WM_SYSCOMMAND ,SC_MINIMIZE, 0);
	default:
		break;
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
	if(!m_is_tracked) 
	{ 
		TRACKMOUSEEVENT   tme; 
		tme.cbSize		=   sizeof(TRACKMOUSEEVENT); 
		tme.dwFlags		=   TME_LEAVE|TME_HOVER; //
		tme.hwndTrack   =   GetSafeHwnd(); 
		tme.dwHoverTime	=   80; 
		_TrackMouseEvent(&tme);  
		m_is_tracked   =   true;
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


//void CPNGButton::OnMouseHover(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CBaseControl::OnMouseHover(nFlags, point);
//}
