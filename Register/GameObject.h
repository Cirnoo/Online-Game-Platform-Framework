#pragma once
#include "GameInterface.h"
class CGameObject : public CGameInterface
{
public:
	CGameObject(void);
	~CGameObject(void);
	void DeleteObj()
	{
		del_flag=true;
	}
public:
	pImage img;
	int x,y;
	bool del_flag;
	virtual void OnPaint(Gdiplus::Graphics * const g) const override;
};

class ShadowObject : public CGameObject
{
private:

	virtual void OnFrame() override;
	virtual void OnPaint(Gdiplus::Graphics * const g) const override;
};

class GameTimer : public CGameObject
{
public:
	GameTimer();
	~GameTimer(){}

private:
	char ones,tens;

};

namespace ImgText
{
	enum TextType
	{
		NONE_IMG=-1,叫地主,不叫,抢地主,不抢,不出,准备,没大牌,非法出牌,
	};
}
namespace ImgGroupType
{
	enum  
	{
		出牌,不出,提示,不叫,不抢,叫地主,抢地主,准备
	};
}
class GameRes
{
public:
	vector<pImage> vec_min,vec_close;
	vector<pImage> vec_button_img[8];
	vector<pImage> vec_text_img;
	pImage img_win,img_lose;
	~GameRes();
	static const GameRes & GetInstance();
private:
	GameRes();
	static GameRes * self;
};