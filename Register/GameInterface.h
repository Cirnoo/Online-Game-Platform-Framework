#pragma once
//#include "Packdef.h"
class CGameInterface
{
public:
	CGameInterface(void)
	{
		timer=0;
	}
	virtual ~CGameInterface(void){}
	void OnTimer()
	{
		OnFrame();
		++timer;
	}
	virtual void OnFrame(){}
	virtual void OnPaint(Gdiplus::Graphics * const g) const =0;
	virtual void OnInit(){}
	virtual void OnGameStateChange(const GameState game_state){}
protected:
	int timer;
};

