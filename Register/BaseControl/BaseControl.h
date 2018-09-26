#pragma once


// CBaseControl

class CBaseControl : public CWnd
{
	DECLARE_DYNAMIC(CBaseControl)

public:
	CBaseControl();
	virtual ~CBaseControl();
	virtual void Show(Graphics* & g)=0;
	virtual void SwichControl(bool flag);
protected:
	Rect mRect;
	virtual void PaintParent();
	DECLARE_MESSAGE_MAP()
};


