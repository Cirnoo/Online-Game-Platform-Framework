#pragma once
class CText
{
public:
	CText(void);
	~CText(void);
	BOOL Create(const Rect rect,const CStringW str,Gdiplus::Font * const font,
		const Gdiplus::Color color=Gdiplus::Color::Black ,
		const StringAlignment format=StringAlignmentCenter);
	virtual void Show(Graphics* const g);
	virtual void Show(Graphics* const g,RectF rec);
	RectF GetRect();
	CStringW GetStr();
	void SetFont(Gdiplus::Font * const font);
	void SetText(const CStringW str);
	void SetColor(const Gdiplus::Color color);
protected:
	RectF str_rect;
	Gdiplus::Font * mFont;
	WCHAR * mStr;
	CStringW mBuf;
	StringAlignment mFormat;
	Gdiplus::Color mColor;
};

