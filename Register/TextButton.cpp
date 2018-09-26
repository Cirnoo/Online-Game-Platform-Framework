// TextButton.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "TextButton.h"


// CTextButton

IMPLEMENT_DYNAMIC(CTextButton, CWnd)

CTextButton::CTextButton()
{

}

CTextButton::~CTextButton()
{
}


BOOL CTextButton::
	Create(Rect rect,WCHAR * str,Gdiplus::Font * font,FontFamily * family,
						 Gdiplus::Color color/*=Gdiplus::Color::Black */,
						 StringAlignment format/*=StringAlignmentCenter*/)
{
	mRectF=RectFTransform(rect);
	mFont=font;
	mFamily=family;
	mStr=str;
	mFormat=format;
	mColor=color;
	return TRUE;
}

void CTextButton::Show(Graphics* & g)
{
	SolidBrush brush(mColor);
	StringFormat format;
	format.SetAlignment(mFormat);
	g->DrawString(mStr,-1,mFont,mRectF,&format,&brush);
}

BEGIN_MESSAGE_MAP(CTextButton, CWnd)
END_MESSAGE_MAP()



// CTextButton 消息处理程序


