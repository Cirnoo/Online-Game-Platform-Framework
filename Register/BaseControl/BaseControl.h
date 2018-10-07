#ifndef CBASE
#define CBASE
#include <vector> 
#include <functional>
enum ButtonState
{
	NORMAL,HOVER,CHECK,DISABLE,HOVER_CHECK,DISABLE_CHECK
};
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
	void SetImg(std::vector<Image*> & _bg);
protected:
	void VarInit();
	Rect mRect;
	std::vector<Image *> vec_bg;
	bool is_tracked;
	bool is_checked;
	bool is_button_down;
	bool is_click_move;
	std::function<void()> mCmd;
	virtual void ClickCmd();
	DECLARE_MESSAGE_MAP()
	virtual void OnTrack();
	void PaintParent();
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
#endif

// CBaseControl



