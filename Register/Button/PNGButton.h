#pragma once
#include "afxwin.h"
#include "BaseControl.h"
#include <vector> 


class CPNGButton : public CBaseControl
{
public:
	CPNGButton(void);
	DECLARE_DYNCREATE(CPNGButton)   
	~CPNGButton(void);
	
	BOOL Create(Rect rect,CWnd * pParentWnd,UINT nID,
		Gdiplus::Image* BG,Gdiplus::Image* _hoverBg,int cmd);
	virtual void SwichControl(bool);

	
protected:
	DECLARE_MESSAGE_MAP()  
	Gdiplus::Image* bg;
	Gdiplus::Image* hoverBg;
	bool m_is_tracked;
	bool mouse_in_flag;
	bool m_is_checked;
	Rect mRect;
	int mCmd;
	bool task_flag;
	void PaintParent();
public:
	void SetRect(Rect rect);
	void Show(Graphics* & g);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnClick(); 
	void Check(bool check);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

