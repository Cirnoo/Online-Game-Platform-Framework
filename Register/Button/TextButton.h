#pragma once
#include "PNGButton.h"
#include "Text.h"
// CTextButton

class CTextButton : public CPNGButton
{
	DECLARE_DYNAMIC(CTextButton)

public:
	CTextButton();
	virtual ~CTextButton();
public:	
	virtual void Show(Graphics* & g);
	void SetText(CStringW str,Gdiplus::Font * font,
		Gdiplus::Color color=Gdiplus::Color::Black ,
		StringAlignment format=StringAlignmentCenter);
protected:
	DECLARE_MESSAGE_MAP()
	CText mText;
};


