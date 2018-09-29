#ifndef CBASE
#define CBASE
#include <vector> 
#include <functional>
class CBaseControl : public CWnd
{
	DECLARE_DYNAMIC(CBaseControl)

public:
	CBaseControl();
	virtual ~CBaseControl();
public:
	virtual void Show(Graphics* & g)=0;
	void SetCmd(std::function<void()> cmd );
	void SetRect(Rect rect);
protected:
	void VarInit();
	Rect mRect;
	std::vector<Image *> vec_bg;
	bool is_tracked;
	bool is_checked;
	bool button_down_flag;
	bool click_move;
	std::function<void()> mCmd;
	virtual void PaintParent();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
#endif

// CBaseControl



