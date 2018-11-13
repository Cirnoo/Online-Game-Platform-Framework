#pragma once
#include "PNGButton.h"
#include <list>
#include <memory>
#include "GameInterface.h"
class CTool;
class CGameDlg;
class CGameCtrl	:public CGameInterface	//负责转发游戏数据和管理控件
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
	void OnGameWin(const int serial_num);
	void ShowCtrl(Graphics * const g) const;
	void ShowText(Graphics * const g) const;
	void GameStart() ;
private:
	CGameCtrl(CGameDlg * parent);
	static CGameCtrl * self;
	CGameDlg * const main_dlg;
	const Point button_center;
	const Size  button_size;
	const GameRes res;
	bool ls_clear_flag;
	CTool & data;
	GameState & game_state;
	CPNGButton bt_min,bt_close;
	CtrlList ls_game_ctrl;
	std::list<CBaseControl *> ls_base_ctrl;
	void CreatCtrl_LandLord(bool is_first);
	void CreatCtlr_Wait();
	void CreatCtlr_DealCard();
	void CreatCtlr(const Rect rect,const vector<pImage> & vec_img, const MS_TYPE ms_tp);
	void CreatCtlr(const Rect rect,const vector<pImage> & vec_img, const std::function<void()> cmd );
private:
	void OnInit() override;
	void OnFrame() override;
	void OnPaint(Gdiplus::Graphics * const g) const override;
};

