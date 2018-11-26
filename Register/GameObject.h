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
		NONE_IMG=-1,�е���,����,������,����,����,׼��,û����,�Ƿ�����,
	};
}
namespace ImgGroupType
{
	enum  
	{
		����,����,��ʾ,����,����,�е���,������,׼��
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