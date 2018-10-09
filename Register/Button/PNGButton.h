#pragma once

#include "BaseControl.h"
#include <vector> 

class CPNGButton : public CBaseControl
{
	
public:
	CPNGButton(void);
	DECLARE_DYNCREATE(CPNGButton)   
	virtual ~CPNGButton(void);
public:	
	BOOL Create(Rect rect,CWnd * pParentWnd,UINT nID,
		Gdiplus::Image* BG,Gdiplus::Image* _hoverBg,Gdiplus::Image* _click_bg);
	virtual BOOL Create(Rect rect,CWnd * pParentWnd,UINT nID,
		std::vector<Image*> &);
	void ClickDown(bool flag);
	virtual void Show(Graphics* & g);
protected:
	DECLARE_MESSAGE_MAP()  
public:
	void Check(bool check);
};

