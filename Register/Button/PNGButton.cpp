#include "stdAfx.h"
#include "afxwin.h"
#include "PNGButton.h"
#include "Resource.h"
#include "Sys.h"
const UINT TIMER_CONTROL =1; 



CPNGButton::CPNGButton(void) { 
	
} 
CPNGButton::~CPNGButton(void) { }

IMPLEMENT_DYNCREATE(CPNGButton, CWnd)  

BEGIN_MESSAGE_MAP(CPNGButton, CWnd)  
		ON_WM_MOUSELEAVE()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_WM_LBUTTONDOWN()
	END_MESSAGE_MAP()  



BOOL CPNGButton::Create(const Rect rect,CWnd * const pParentWnd,const UINT nID,
						Gdiplus::Image* BG,Gdiplus::Image* _hoverBg,Gdiplus::Image* _click_bg)
{
	LPCTSTR lpszClassName=AfxRegisterWndClass( CS_HREDRAW|CS_VREDRAW ,  AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(TRANSPARENT), NULL) ;   
	SetRect(rect);
	vec_bg.resize(3);
	vec_bg[NORMAL]=BG;
	vec_bg[HOVER]=_hoverBg;
	vec_bg[CHECK]=_click_bg;
	BOOL OK=CWnd::Create(NULL,NULL,WS_CHILDWINDOW|WS_VISIBLE|WS_CLIPCHILDREN,Rect2CRect(rect),pParentWnd, nID, NULL);
	ModifyStyleEx(0, WS_EX_TRANSPARENT);
	
	return OK;
}

BOOL CPNGButton::Create(const Rect rect, CWnd * const pParentWnd,
						const UINT nID,const std::vector<Image*>& _bg)
{
	LPCTSTR lpszClassName=AfxRegisterWndClass( CS_HREDRAW|CS_VREDRAW ,  AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(TRANSPARENT), NULL) ;   
	SetRect(rect);
	vec_bg=_bg;
	BOOL OK=CWnd::Create(NULL,NULL,WS_CHILDWINDOW|WS_VISIBLE|WS_CLIPCHILDREN,Rect2CRect(rect),pParentWnd, nID, NULL);
	ModifyStyleEx(0, WS_EX_TRANSPARENT); 

	return OK;
}





void CPNGButton::SetClickDown(bool flag)
{
	is_click_move=flag;
}

void CPNGButton::Show(Graphics* const g)
{
	if (is_button_down)
	{
		auto t_rec=mRect;
		if (is_click_move)
		{
			t_rec.Offset(1,1);
		}
		g->DrawImage(vec_bg[CHECK],t_rec);
	}
	else if(is_tracked)
	{
		g->DrawImage(vec_bg[HOVER],mRect); 
	}
	else
	{
		g->DrawImage(vec_bg[NORMAL],mRect); 
	}
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

 


