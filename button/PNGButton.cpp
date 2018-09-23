#include "stdAfx.h"
#include "PNGButton.h"
#include "Resource.h"
#include "Sys.h"
const UINT TIMER_CONTROL =1; 
CRect RectTransform(Rect);



PNGButton::PNGButton(void) { 
	this->m_is_checked=false;
	mouse_in_flag=false;
	m_is_tracked	=	false; 
	mCmd=0;
	task_flag=true;
} 
PNGButton::~PNGButton(void) { }
IMPLEMENT_DYNCREATE(PNGButton, CWnd)  
	BEGIN_MESSAGE_MAP(PNGButton, CWnd)  
		//{{AFX_MSG_MAP(MySelfWnd)  
		//	ON_WM_LBUTTONDOWN()

		//}}AFX_MSG_MAP
		ON_WM_MOUSEHOVER()
		ON_WM_MOUSELEAVE()
//		ON_WM_MOUSEMOVE()

		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
	END_MESSAGE_MAP()  


BOOL PNGButton::Create(Rect rect,CWnd * pParentWnd,UINT nID, Gdiplus::Image* BG,Gdiplus::Image* _hoverBg, int cmd)
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


void PNGButton::SetRect(Rect rect)
{
	mRect=rect;

}

void PNGButton::Show(Bitmap& buf,Graphics* & g)
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



void PNGButton::OnMouseHover(UINT nFlags, CPoint point)
{    
	if (!task_flag)
	{
		return;
	}
	mouse_in_flag=true;
	GetParent()->UpdateWindow();
	TRACE(L"OnMouseHover\r\n");
	//CWnd::OnMouseHover(nFlags, point);
}


void PNGButton::OnMouseLeave()
{    
	if (!task_flag)
	{
		return;
	}
	m_is_tracked	=   false;  
	mouse_in_flag=false;
	UpdateWindow(); 
	//TRACE(L"OnMouseLeave\r\n");
	CWnd::OnMouseLeave();
}


void PNGButton::Check(bool check)
{
	if(this->m_is_checked!=check)
	{
		this->m_is_checked=check;
		UpdateWindow();
		//TRACE(L"DrawSelected\r\n");
	} /*else{  TRACE(L"Check(%d,%d)\r\n",GetDlgCtrlID(),check); }*/
}

 



void PNGButton::OnLButtonUp(UINT nFlags, CPoint point)
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


CRect RectTransform(Rect rect)
{
	return CRect(rect.GetLeft(),rect.GetTop(),rect.GetLeft()+rect.Width,rect.GetTop()+rect.Height);
}


void PNGButton::OnMouseMove(UINT nFlags, CPoint point)
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
