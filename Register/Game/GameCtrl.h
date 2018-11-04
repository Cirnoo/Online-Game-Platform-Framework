#pragma once
#include "PNGButton.h"
#include <list>
#include <memory>
class CTool;
class CGameDlg;
class CGameCtrl		//负责转发游戏数据和管理控件
{
	enum  GameState
	{
		Wait,GetCards,Ready,Gaming,Over
	};
	typedef std::list<std::unique_ptr<CBaseControl>> CtrlList ;
	struct GameRes
	{
		vector<pImage> vec_min,vec_close;
		vector<pImage> vec_button_img[7];
		GameRes();
	};
public:
	static CGameCtrl & GetInstance(CGameDlg * parent);
	~CGameCtrl(void);
	void Show(Gdiplus::Graphics * g);
	void InitCtrl();
	void OnGameTimer();
	void OnGameWin(const int serial_num);
	void ShowCtrl(Gdiplus::Graphics * g);
private:
	CGameCtrl(CGameDlg * parent);
	static CGameCtrl * self;
	CGameDlg * const main_dlg;
	CTool & data;
	const Point button_center;
	const Size  button_size;
	const GameRes res;
private:
	CPNGButton bt_min,bt_close;
	CtrlList ls_game_ctrl;
	std::list<CBaseControl *> ls_base_ctrl;
	void CreatCtrl_Ready(IN CtrlList &  ctrl_ls);
	void CreatCtlr_Wait( CtrlList &  ctrl_ls);
	int game_timer;
};

