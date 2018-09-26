#pragma once
#include "PNGButton.h"
// CTextButton

class CTextButton : public CBaseControl
{
	DECLARE_DYNAMIC(CTextButton)

public:
	CTextButton();
	virtual ~CTextButton();
	BOOL Create(Rect rect,WCHAR * str,Gdiplus::Font * font,FontFamily * family,
		Gdiplus::Color color=Gdiplus::Color::Black ,
		StringAlignment format=StringAlignmentCenter);
	virtual void Show(Graphics* & g);
protected:
	DECLARE_MESSAGE_MAP()
	RectF mRectF;
	CPNGButton mButton;
	Gdiplus::Font * mFont;
	FontFamily* mFamily;
	WCHAR * mStr;
	StringAlignment mFormat;
	Gdiplus::Color mColor;
};


