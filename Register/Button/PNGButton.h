#pragma once

#include "BaseControl.h"
#include <vector> 
#include <functional>

typedef void (*CmdFun)();

enum ButtonBg
{
	normal_bg,hover_bg,click_bg
};
class CPNGButton : public CBaseControl
{
	
public:
	CPNGButton(void);
	DECLARE_DYNCREATE(CPNGButton)   
	~CPNGButton(void);
	
	BOOL Create(Rect rect,CWnd * pParentWnd,UINT nID,
		Gdiplus::Image* BG,Gdiplus::Image* _hoverBg,Gdiplus::Image* _click_bg);
	BOOL Create(Rect rect,CWnd * pParentWnd,UINT nID,
		std::vector<Image*> &);
	void ClickDown(bool flag);
protected:
	DECLARE_MESSAGE_MAP()  
public:
	void Show(Graphics* & g);
	void Check(bool check);
};

