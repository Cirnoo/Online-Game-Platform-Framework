#pragma once
#include "PNGButton.h"
#include <list>
#include <memory>
class CTool;
class CGameDlg;
enum class GameState;
class CGameCtrl		//负责转发游戏数据和管理控件
{

	typedef std::list<std::unique_ptr<CBaseControl>> CtrlList ;
	struct GameRes
	{
		vector<pImage> vec_min,vec_close;
		vector<pImage> vec_button_img[7];
		vector<pImage> vec_text_img;
		GameRes();
		~GameRes();
	};
public:
	static CGameCtrl & GetInstance(CGameDlg * parent);
	~CGameCtrl(void);
	void Show(Graphics * const g);
	void InitCtrl();
	void OnGameTimer();
	void OnGameWin(const int serial_num);
	void ShowCtrl(Graphics * const g) const;
	void ShowText(Graphics * const g) const;
	void ShowPlayer(Graphics * const g);
	void GameStart() ;
	CTool & data;
private:
	CGameCtrl(CGameDlg * parent);
	static CGameCtrl * self;
	CGameDlg * const main_dlg;
	const Point button_center;
	const Size  button_size;
	const GameRes res;
	GameState & game_state;
	void InvalidateRect(Rect & rect);
private:
	CPNGButton bt_min,bt_close;
	CtrlList ls_game_ctrl;
	std::list<CBaseControl *> ls_base_ctrl;
	void CreatCtrl_Ready(IN CtrlList &  ctrl_ls);
	void CreatCtlr_Wait( CtrlList &  ctrl_ls);
	int game_timer;
};

