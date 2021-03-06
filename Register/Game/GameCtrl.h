#pragma once
#include "PNGButton.h"
#include <list>
#include <memory>
#include "GameInterface.h"
#include "GameObject.h"
#include "GameObjCtrl.h"
class CTool;
class CGameDlg;


class CGameCtrl	:public CGameInterface	//负责转发游戏数据和管理控件
{

	typedef std::list<std::unique_ptr<CBaseControl>> CtrlList ;
	
public:
	static CGameCtrl & GetInstance(CGameDlg * parent);
	~CGameCtrl(void);
	void OnGameWin(const int serial_num);
	void GameStart() ;
	void SetLastRoundText(MS_TYPE ms_type,Player::PlayerPosition pos);
	bool OurPlayCards();
	void TextClear();
private:
	CGameCtrl(CGameDlg * parent);
	static CGameCtrl * self;
	CGameDlg * const main_dlg;
	const Point button_center;
	const Size  button_size;
	const GameRes & res;
	bool ls_clear_flag;
	CTool & data;
	GameState_EX & cur_game_state;
	CPNGButton bt_min,bt_close;
	CtrlList ls_game_ctrl;
	CGameObjCtrl obj_ctrl;
	std::list<CBaseControl *> ls_base_ctrl;
	std::array<ImgText::TextType,3> last_round_text;
	void CreatCtrl_Pair(MS_TYPE ms_type);
	void CreatCtrl_CallLandLord();
	void CreatCtrl_RobLandLord();
	void CreatCtlr_Wait();
	void CreatCtlr_Play();
	void CreatCtlr(const Rect rect,const vector<pImage> & vec_img, const MS_TYPE ms_tp);
	void CreatCtlr(const Rect rect,const vector<pImage> & vec_img, const std::function<void()> cmd );
	void ShowLastRoundText(Gdiplus::Graphics * const g) const;
	ImgText::TextType GetImgTextType(const MS_TYPE ms_tp) const;
	void ShowCtrl(Graphics * const g) const;
	void ShowText(Graphics * const g) const;
	DATA_PACKAGE BuildProcessDate(MS_TYPE ms_tp);
private:
	GameState old_game_state;
	void OnInit() override;
	void OnFrame() override;
	void OnPaint(Gdiplus::Graphics * const g) const override;
	void OnGameStateChange(const GameState new_state) override;
};

