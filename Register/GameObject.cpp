#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject(void)
{
	x=0;y=0;
	timer=0;
	del_flag=false;
}


CGameObject::~CGameObject(void)
{
}


void CGameObject::OnPaint(Gdiplus::Graphics * const g) const 
{
	g->DrawImage(img,x,y);
}

void ShadowObject::OnFrame()
{
	if (timer>=30)
	{
		DeleteObj();
	}
	AfxGetMainWnd()->InvalidateRect(CRect(x,y,img->GetWidth(),img->GetHeight()),FALSE);
}

void ShadowObject::OnPaint(Gdiplus::Graphics * const g) const 
{
	const unsigned char cur_alpha=(1-(15-timer)*(15-timer)/255.0)*255;
	//const unsigned char cur_alpha=255*abs(sin(timer/(2*3.14)));
	DrawImgWithAlpha(g,img,x,y,cur_alpha);
}


GameTimer::GameTimer()
{
	ones=0;tens=0;
	img=::CutImage(theApp.sys.game_tool,97,0,56,59);

}


GameRes * GameRes::self = nullptr;
const GameRes & GameRes::GetInstance()
{
	if (self==nullptr)
	{
		self = new GameRes;
	}
	return *self;
}

GameRes::~GameRes()
{
	for (auto i:vec_min)
	{
		delete i;
	}
	for (auto i:vec_close)
	{
		delete i;
	}

	for (auto i:vec_button_img)
	{
		for (auto j:i)
		{
			delete j;
		}
	}
	for (auto i:vec_text_img)
	{
		delete i;
	}
	self=nullptr;
}

GameRes::GameRes()
{
	auto vec_temp=::GetImageGroup(IDB_GAME_CTRL,2,3);
	for (auto & i:vec_temp)
	{
		i=ResizeImg(i,0.4);
	}
	for (int i=0;i<3;i++)
	{
		vec_min.push_back(vec_temp[i]);
	}
	for (int i=3;i<6;i++)
	{
		vec_close.push_back(vec_temp[i]);
	}

	vec_temp=::GetImageGroup(IDB_GAME_BUTTON,7,3);
	for (int i=0;i<7;i++)
	{
		vec_button_img[i].resize(3);
		for (int j=0;j<3;j++)
		{
			vec_button_img[i][j]=vec_temp[3*i+j];
		}
	}
	using namespace ImgText;
	vec_text_img.resize(8);
	vec_text_img[准备]=::CutImage(theApp.sys.game_tool,0,80,89,42);
	vec_text_img[抢地主]=::CutImage(theApp.sys.game_tool,0,0,89,38);
	vec_text_img[叫地主]=::CutImage(theApp.sys.game_tool,0,37,89,42);
	vec_text_img[不叫]=::CutImage(theApp.sys.game_tool,0,121,89,45);
	vec_text_img[不抢]=::CutImage(theApp.sys.game_tool,0,165,89,38);
	vec_text_img[没大牌]=::CutImage(theApp.sys.game_tool,0,233,153,30);
	vec_text_img[非法出牌]=::CutImage(theApp.sys.game_tool,0,233,102,25);
}

