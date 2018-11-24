#pragma once
#include "GameInterface.h"
class CGameObject : public CGameInterface
{
public:
	CGameObject(void);
	~CGameObject(void);
protected:
	pImage img;
	int x,y;
	int timer;
	virtual void OnFrame() override;
	virtual void OnPaint(Gdiplus::Graphics * const g) const override;
};

class ShadowObject : public CGameObject
{
	virtual void OnPaint(Gdiplus::Graphics * const g) const override;
};