// TextButton.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "TextButton.h"


// CTextButton

IMPLEMENT_DYNAMIC(CTextButton, CWnd)

CTextButton::CTextButton()
{
	ClickDown(true);
}

CTextButton::~CTextButton()
{
}

void CTextButton::Show(Graphics* & g)
{

	CPNGButton::Show(g);
	auto t_rect=mText.GetRect();
	if (is_button_down)
	{
		t_rect.Offset(1,1);
	}
	mText.Show(g,t_rect);
}

void CTextButton::SetText(CStringW str,Gdiplus::Font * font, Gdiplus::Color color/*=Gdiplus::Color::Black */, StringAlignment format/*=StringAlignmentCenter*/)
{
	Rect rec=Rect(mRect.GetLeft(),mRect.GetTop()+font->GetSize()/4+1,mRect.Width,mRect.Height);
	mText.Create(rec,str,font,color,format);
}


BEGIN_MESSAGE_MAP(CTextButton, CWnd)
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CTextButton 消息处理程序


