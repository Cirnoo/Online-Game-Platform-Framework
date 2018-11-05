#include "stdafx.h"
#include "Text.h"
#include "Sys.h"

CText::CText(void)
{
}


CText::~CText(void)
{
}

BOOL CText::Create(const Rect rect,const CStringW str,Gdiplus::Font * const font,
				   const Gdiplus::Color color/*=Gdiplus::Color::Black */ ,
				   const StringAlignment format/*=StringAlignmentCenter*/)
{
	str_rect=Rect2RectF(rect);
	mFont=font;
	SetText(str);
	mFormat=format;
	mColor=color;
	return TRUE;
}

void CText::Show(Graphics* const g)
{
	SolidBrush brush(mColor);
	StringFormat format;
	format.SetAlignment(mFormat);
	g->DrawString(mStr,-1,mFont,str_rect,&format,&brush);
}

void CText::Show(Graphics* const g,RectF rec)
{
	auto temp=str_rect;
	str_rect=rec;
	Show(g);
	str_rect=temp;
}

RectF CText::GetRect()
{
	return str_rect;
}

CStringW CText::GetStr()
{
	return mBuf;
}

void CText::SetFont(Gdiplus::Font * const font)
{
	mFont=font;
}

void CText::SetText(const CStringW str)
{
	mBuf=str;
	mStr=mBuf.GetBuffer();
}

void CText::SetColor(const Gdiplus::Color color)
{
	mColor=color;
}
