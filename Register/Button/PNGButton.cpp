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
} 
CPNGButton::~CPNGButton(void) { }
IMPLEMENT_DYNCREATE(CPNGButton, CWnd)  
	BEGIN_MESSAGE_MAP(CPNGButton, CWnd)  
		
		ON_WM_MOUSEHOVER()
		ON_WM_MOUSELEAVE()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
	END_MESSAGE_MAP()  


BOOL CPNGButton::Create(Rect rect,CWnd * pParentWnd,UINT nID, Gdiplus::Image* BG,Gdiplus::Image* _hoverBg, int cmd)
{
	LPCTSTR lpszClassName=AfxRegisterWndClass( CS_HREDRAW|CS_VREDRAW ,  AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(TRANSPARENT), NULL) ;   
	bg=BG;
	SetRect(rect);
	hoverBg=_hoverBg;
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
	
	if(mouse_in_flag||m_is_tracked)
	{

		g->DrawImage(hoverBg,mRect); 
	} 
	else
	{
		g->DrawImage(this->bg,mRect); 
	}
}



void CPNGButton::OnMouseHover(UINT nFlags, CPoint point)
{    
	if (!task_flag)
	{
		return;
	}
	mouse_in_flag=true;
	PaintParent();
	GetParent()->UpdateWindow();
	//TRACE(L"OnMouseHover\r\n");
	//CWnd::OnMouseHover(nFlags, point);
}


void CPNGButton::OnMouseLeave()
{    
	if (!task_flag)
	{
		return;
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
	GetParent()->SendMessage(WM_COMMAND,GetDlgCtrlID()|0,(LONG)GetSafeHwnd());
	CWnd::OnLButtonUp(nFlags, point);
}



void CPNGButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!m_is_tracked) 
	{ 
		TRACKMOUSEEVENT   tme; 
		tme.cbSize		=   sizeof(TRACKMOUSEEVENT); 
		tme.dwFlags		=   TME_LEAVE|TME_HOVER; //
		tme.hwndTrack   =   GetSafeHwnd(); 
		tme.dwHoverTime	=   80; 
		_TrackMouseEvent(&tme);  
		m_is_tracked   =   true;    
		//OnMouseHover(nFlags,point);
	}  
	CWnd::OnMouseMove(nFlags, point);
}

void CPNGButton::PaintParent()
{  
	CRect   rect;
	GetWindowRect(&rect); 
	GetParent()-> ScreenToClient(&rect); 
	GetParent()-> InvalidateRect(&rect);
}
