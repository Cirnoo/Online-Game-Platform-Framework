#pragma once
#include "afxwin.h"
#include "BaseControl.h"
#include <vector> 
#include <functional>
typedef void (*CmdFun)();

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
	virtual void SwichControl(bool);

	
protected:
	DECLARE_MESSAGE_MAP()  
	std::vector<Image *> vec_bg;
	bool is_tracked;
	bool mouse_in_flag;
	bool is_checked;
	bool task_flag;
	bool button_down_flag;
	std::function<void()> mCmd;
	
public:
    void SetCmd(std::function<void()> cmd );
	void SetRect(Rect rect);
	void Show(Graphics* & g);
	afx_msg void OnMouseLeave();
	void Check(bool check);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

