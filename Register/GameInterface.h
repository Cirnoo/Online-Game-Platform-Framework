#pragma once
class CGameInterface
{
public:
	CGameInterface(void)
	{timer=0;}
	~CGameInterface(void){}
	virtual void OnTimer()
	{
		++timer;
	}
	virtual void OnPaint(Gdiplus::Graphics & g)=0;
	virtual void OnInit()=0;
protected:
	int timer;
};

