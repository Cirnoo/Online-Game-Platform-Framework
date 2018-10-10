// CheckBox.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "CheckBox.h"


// CCheckBox

IMPLEMENT_DYNAMIC(CCheckBox, CWnd)

CCheckBox::CCheckBox()
{

}

CCheckBox::~CCheckBox()
{
}


void CCheckBox::Show(Graphics* & g)
{
	if (is_tracked)
	{
		button_state=is_checked?HOVER_CHECK:HOVER;
	}
	else
	{
		button_state=is_checked?CHECK:NORMAL;
	}
	g->DrawImage(vec_bg[button_state],mRect);
	mText.Show(g);
}

void CCheckBox::SetText(CStringW str,Gdiplus::Font * font, Gdiplus::Color color/*=Gdiplus::Color::Black */, StringAlignment format/*=StringAlignmentCenter*/)
{
	Rect rec=Rect(mRect.GetLeft()+vec_bg[0]->GetWidth(),mRect.GetTop()+1,str.GetLength()*mRect.Width,mRect.Height);
	mText.Create(rec,str,font,color,format);
}

void CCheckBox::OnMouseLeave()
{
	is_tracked=false;
	ControlRepaint();
}

void CCheckBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!is_button_down)
	{
		return;
	}
	is_button_down=false;
	is_checked=!is_checked;
	ControlRepaint();
}

void CCheckBox::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!is_tracked) 
	{ 
		OnTrack();
		ControlRepaint();
		//OnMouseHover(nFlags,point);
	}
}

void CCheckBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	CBaseControl::OnLButtonDown(nFlags,point);
}

BEGIN_MESSAGE_MAP(CCheckBox, CWnd)
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CCheckBox 消息处理程序


