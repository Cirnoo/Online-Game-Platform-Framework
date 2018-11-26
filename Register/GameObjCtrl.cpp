#include "stdafx.h"
#include "GameObjCtrl.h"
#include <algorithm>
#include "GameObject.h"
CGameObjCtrl::CGameObjCtrl(void)
	:res(GameRes::GetInstance())
{
}


CGameObjCtrl::~CGameObjCtrl(void)
{
}

void CGameObjCtrl::NewObject()
{
	ShadowObject * obj=new ShadowObject;
	obj->img=res.vec_text_img[ImgText::没大牌];
	obj->x=200;obj->y=200;
	AddTask(obj);
}

void CGameObjCtrl::InvalidPlay()
{
	ShadowObject * obj=new ShadowObject;
	obj->img=res.vec_text_img[ImgText::非法出牌];
	obj->x=GAME_DLG_WIDTH/2-obj->img->GetWidth()/2;
	obj->y=GAME_DLG_HEIGHT/2+100;
	AddTask(obj);
}

void CGameObjCtrl::AddTask(CGameObject * obj)
{
	ls_obj.emplace_back(obj);
}

void CGameObjCtrl::OnFrame()
{
	ls_obj.erase(remove_if(ls_obj.begin(),ls_obj.end(),
		[](std::unique_ptr<CGameObject> & m){return m->del_flag;}),ls_obj.end());
	for (auto & i:ls_obj)
	{
		i->OnTimer();
	}
}

void CGameObjCtrl::OnPaint(Gdiplus::Graphics * const g) const
{
	for (auto & i:ls_obj)
	{
		i->OnPaint(g);
	}
}
