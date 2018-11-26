//#pragma once
//#include "gameinterface.h"
//#include <functional>
//#include <list>
//class CGameCtrl;
//class GameRes;
//class CGameButtonCtrl :
//	public CGameInterface
//{
//public:
//	CGameButtonCtrl(void);
//	~CGameButtonCtrl(void);
//	
//private:
//	typedef std::list<std::unique_ptr<CBaseControl>> CtrlList ;
//	CtrlList ls_game_ctrl;
//	bool ls_clear_flag;
//	const Point button_center;
//	const Size  button_size;
//	const GameRes & res;
//	void CreatCtrl_Pair(MS_TYPE ms_type);
//	void CreatCtrl_CallLandLord();
//	void CreatCtrl_RobLandLord();
//	void CreatCtlr_Wait();
//	void CreatCtlr_Play();
//	void CreatCtlr(const Rect rect,const vector<pImage> & vec_img, const MS_TYPE ms_tp);
//	void CreatCtlr(const Rect rect,const vector<pImage> & vec_img, const std::function<void()> cmd );
//	virtual void OnFrame();
//	virtual void OnPaint(Gdiplus::Graphics * const g) const ;
//	virtual void OnInit();
//	virtual void OnGameStateChange(const GameState game_state);
//};
//
