#pragma once
class CText
{
public:
	CText(void);
	~CText(void);
	BOOL Create(Rect rect,CStringW str,Gdiplus::Font * font,
		Gdiplus::Color color=Gdiplus::Color::Black ,
		StringAlignment format=StringAlignmentCenter);
	virtual void Show(Graphics* & g);
	virtual void Show(Graphics* & g,RectF rec);
	RectF GetRect();
	CStringW GetStr();
protected:
	RectF str_rect;
	Gdiplus::Font * mFont;
	WCHAR * mStr;
	CStringW mBuf;
	StringAlignment mFormat;
	Gdiplus::Color mColor;
};

