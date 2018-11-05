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
	virtual void Show(Graphics* const g);
	void SetText(const CStringW str,Gdiplus::Font * const font,
		const Gdiplus::Color color=Gdiplus::Color::Black ,
		const StringAlignment format=StringAlignmentCenter);
protected:
	DECLARE_MESSAGE_MAP()
	CText mText;
};


