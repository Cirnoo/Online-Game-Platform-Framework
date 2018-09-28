#ifndef CBASE
#define CBASE
class CBaseControl : public CWnd
{
	DECLARE_DYNAMIC(CBaseControl)

public:
	CBaseControl();
	virtual ~CBaseControl();
public:
	virtual void Show(Graphics* & g)=0;
	virtual void SwichControl(bool flag);
	Rect mRect;
protected:
	virtual void PaintParent();
	DECLARE_MESSAGE_MAP()
};
#endif

// CBaseControl



