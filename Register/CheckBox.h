#pragma once

#include "PNGButton.h"
#include "Text.h"
// CCheckBox

class CCheckBox : public CPNGButton
{
	DECLARE_DYNAMIC(CCheckBox)

public:
	CCheckBox();
	virtual ~CCheckBox();
public:
	void Show(Graphics* & g);
	void SetText(CStringW str,Gdiplus::Font * font,
		Gdiplus::Color color=Gdiplus::Color::Black ,
		StringAlignment format=StringAlignmentCenter);
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	ButtonState button_state;
	CText mText;
};


