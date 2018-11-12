#pragma once
class CGameInterface
{
public:
	CGameInterface(void)
	{timer=0;}
	virtual ~CGameInterface(void){}
	void OnTimer()
	{
		OnFrame();
		++timer;
	}
	virtual void OnFrame()=0;
	virtual void OnPaint(Gdiplus::Graphics * const g) const =0;
	virtual void OnInit(){}
protected:
	int timer;
};

