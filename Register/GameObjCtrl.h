#pragma once
#include "GameObject.h"
#include <list>
class GameRes;
class CGameObjCtrl : public CGameInterface
{
	typedef std::list<std::unique_ptr<CGameObject>>  ObjList ;
public:
	CGameObjCtrl(void);
	~CGameObjCtrl(void);
	ObjList ls_obj;
	void NewObject();
	void InvalidPlay();
	void AddTask(CGameObject * obj);
	virtual void OnFrame() override;
	virtual void OnPaint(Gdiplus::Graphics * const g) const;
	virtual void OnGameStateChange(const GameState game_state){};
private:
	const GameRes & res;
};

