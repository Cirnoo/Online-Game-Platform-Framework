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
	BOOL Create(const Rect rect, CWnd * const pParentWnd,const UINT nID,
		Gdiplus::Image* BG,Gdiplus::Image* _hoverBg,Gdiplus::Image* _click_bg);
	virtual BOOL Create(const Rect rect,CWnd * const pParentWnd,const UINT nID,
		const std::vector<Image*> &);
	void SetClickDown(bool flag);
	virtual void Show(Graphics* const g);
	void Check(bool check);
protected:
	DECLARE_MESSAGE_MAP()  
	
};

