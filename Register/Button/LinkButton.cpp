// LinkButton.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "LinkButton.h"

// CLinkButton

IMPLEMENT_DYNAMIC(CLinkButton, CWnd)

CLinkButton::CLinkButton()
{

}

CLinkButton::~CLinkButton()
{
}





void CLinkButton::SetText(CStringW str,Gdiplus::Font * font, Gdiplus::Color color_normal/*=Color(39, 134, 230)*/,Gdiplus::Color color_hover/*=Color(21, 112, 235)*/)
{
	m_color_normal=color_normal;
	m_color_hover=color_hover;
	mText.Create(mRect,str,font,m_color_normal);
}

BOOL CLinkButton::Create(Rect rect,CWnd * pParentWnd,UINT nID)
{
	SetRect(rect);
	BOOL OK=CWnd::Create(NULL,NULL,WS_CHILDWINDOW|WS_VISIBLE|WS_CLIPCHILDREN,RectTransform(rect),pParentWnd, nID, NULL);
	ModifyStyleEx(0, WS_EX_TRANSPARENT);

	return OK;
}

void CLinkButton::Show(Graphics* & g)
{
	mText.Show(g);
}

BEGIN_MESSAGE_MAP(CLinkButton, CWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CLinkButton 消息处理程序




void CLinkButton::OnTrack()
{
	mText.SetColor(m_color_hover);
	
	CBaseControl::OnTrack();
}

void CLinkButton::OnMouseMove(UINT nFlags, CPoint point)
{
	CBaseControl::OnMouseMove(nFlags,point);
	HCURSOR hCur  =  LoadCursor( NULL  , IDC_HAND ) ;
	::SetCursor(hCur);
}



void CLinkButton::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	mText.SetColor(m_color_normal);
	HCURSOR hCur  =  LoadCursor( NULL  , IDC_ARROW ) ;
	::SetCursor(hCur);
	CBaseControl::OnMouseLeave();
}


BOOL CLinkButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}
