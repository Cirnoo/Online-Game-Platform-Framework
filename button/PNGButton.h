#pragma once
#include "afxwin.h"
#include <vector> 


class PNGButton : public CWnd
{
public:
	PNGButton(void);
	DECLARE_DYNCREATE(PNGButton)   
	~PNGButton(void);
	
	BOOL Create(Rect rect,CWnd * pParentWnd,UINT nID,
		Gdiplus::Image* BG,Gdiplus::Image* _hoverBg,int cmd);


	bool task_flag;
protected:
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);   
	DECLARE_MESSAGE_MAP()  
	Gdiplus::Image* bg;
	Gdiplus::Image* hoverBg;
	bool m_is_tracked;
	bool mouse_in_flag;
	bool m_is_checked;
	Rect mRect;
	int mCmd;
public:
	void SetRect(Rect rect);
	void Show(Bitmap & hMemDC,Graphics* & g);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClick(); 
	void Check(bool check);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

