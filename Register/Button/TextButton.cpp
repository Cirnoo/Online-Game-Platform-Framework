// TextButton.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "TextButton.h"


// CTextButton

IMPLEMENT_DYNAMIC(CTextButton, CWnd)

CTextButton::CTextButton()
{
	use_button=false;
}

CTextButton::~CTextButton()
{
	delete[] mStr;
}


BOOL CTextButton::
	Create(Rect rect,CStringW str,Gdiplus::Font * font,
						 Gdiplus::Color color/*=Gdiplus::Color::Black */,
						 StringAlignment format/*=StringAlignmentCenter*/)
{
	mRect=rect;
	mRectF=RectFTransform(rect);
	mFont=font;
	mBuf=str;
	mStr=mBuf.GetBuffer();
	mFormat=format;
	mColor=color;
	str_rect=RectF(rect.GetLeft(),rect.GetTop()+font->GetSize()/4,rect.Width,rect.Height);
	return TRUE;
}

void CTextButton::Show(Graphics* & g)
{
	if (use_button)
	{
		mButton.Show(g);
	}
	SolidBrush brush(mColor);
	StringFormat format;
	format.SetAlignment(mFormat);
	g->DrawString(mStr,-1,mFont,str_rect,&format,&brush);
}

void CTextButton::SetButton(UINT nID,CWnd * pParentWnd,Gdiplus::Image* BG,Gdiplus::Image* _hoverBg,Gdiplus::Image* click_bg)
{
	use_button=true;
	mButton.Create(mRect,GetParent(),nID,BG,_hoverBg,click_bg);
}

void CTextButton::SetButton(UINT nID,CWnd * pParentWnd,std::vector<Image*>& bg)
{
	use_button=true;
	mButton.Create(mRect,pParentWnd,nID,bg);
}



BEGIN_MESSAGE_MAP(CTextButton, CWnd)
END_MESSAGE_MAP()



// CTextButton 消息处理程序


