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
	virtual void Show(Graphics* const g)=0;
	void SetCmd(const std::function<void()> cmd );
	void SetRect(const Rect rect);
	void SetImg(const std::vector<Image*> & _bg);
protected:
	void VarInit();
	Rect mRect;
	std::vector<Image *> vec_bg;
	bool is_tracked;
	bool is_checked;
	bool is_button_down;
	std::function<void()> mCmd;
	virtual void OnClick();
	DECLARE_MESSAGE_MAP()
	virtual void OnTrack();
	void ControlRepaint() const;
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};
#endif

// CBaseControl



