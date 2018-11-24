#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject(void)
{
	x=0;y=0;
	timer=0;
}


CGameObject::~CGameObject(void)
{
}

void CGameObject::OnFrame()
{
	timer++;
}

void CGameObject::OnPaint(Gdiplus::Graphics * const g) const 
{
	g->DrawImage(img,x,y);
}

void ShadowObject::OnPaint(Gdiplus::Graphics * const g) const 
{
	DrawImgWithAlpha(g,img,x,y,timer);
}
