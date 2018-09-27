#pragma once
#include "PNGButton.h"
// CTextButton

class CTextButton : public CBaseControl
{
	DECLARE_DYNAMIC(CTextButton)

public:
	CTextButton();
	virtual ~CTextButton();
	BOOL Create(Rect rect,CStringW str,Gdiplus::Font * font,
		Gdiplus::Color color=Gdiplus::Color::Black ,
		StringAlignment format=StringAlignmentCenter);
	virtual void Show(Graphics* & g);
	void SetButton(UINT nID,CWnd * pParentWnd,Gdiplus::Image* BG,Gdiplus::Image* _hoverBg,Gdiplus::Image* click_bg);
	void SetButton(UINT nID,CWnd * pParentWnd,std::vector<Image*>& bg);

protected:
	DECLARE_MESSAGE_MAP()
	
	RectF mRectF;
	RectF str_rect;
	CPNGButton mButton;
	bool use_button;
	Gdiplus::Font * mFont;
	WCHAR * mStr;
	CStringW mBuf;
	StringAlignment mFormat;
	Gdiplus::Color mColor;
};


