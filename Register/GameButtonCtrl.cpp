#include "stdafx.h"
//#include "GameButtonCtrl.h"
//#include "GameObject.h"
//#include "PNGButton.h"
//CGameButtonCtrl::CGameButtonCtrl(void)
//	:res(GameRes::GetInstance()),
//	button_center(GAME_DLG_WIDTH/2,GAME_DLG_HEIGHT/2+130),
//	button_size(93,37)
//{
//}
//
//
//CGameButtonCtrl::~CGameButtonCtrl(void)
//{
//}
//
//void CGameButtonCtrl::CreatCtrl_Pair(MS_TYPE ms_type)
//{
//	/************************************************************************/
//	/*			叫地主	不叫 	抢地主		不抢                            */
//	/************************************************************************/
//	Rect rect;
//	CPNGButton * button;
//	using namespace ImgGroupType;
//	int img_type1,img_type2;
//	MS_TYPE ms_tp_re1,ms_tp_re2;
//	switch (ms_type)
//	{
//	case MS_TYPE::IS_CALL_LANDLORD://叫地主
//		img_type1=叫地主;img_type2=不叫;
//		ms_tp_re1=MS_TYPE::CALL_LANDLORD_RQ;
//		ms_tp_re2=MS_TYPE::NOT_CALL;
//		break;
//	case MS_TYPE::IS_ROB_LANDLORD:
//		img_type1=抢地主;img_type2=不抢;
//		ms_tp_re1=MS_TYPE::ROB_LANDLORD_RQ;
//		ms_tp_re2=MS_TYPE::NOT_ROB;
//	default:
//		break;
//	}
//	rect = Rect(Point(button_center.X-button_size.Width-10,button_center.Y),button_size);
//	const auto & img1=res.vec_button_img[img_type1];
//	CreatCtlr(rect,img1,ms_tp_re1);
//
//	rect.X+=button_size.Width+20;
//	const auto & img2=res.vec_button_img[img_type2];
//	CreatCtlr(rect,img2,ms_tp_re2);
//}
//
//void CGameButtonCtrl::CreatCtrl_CallLandLord()
//{
//	CreatCtrl_Pair(MS_TYPE::IS_CALL_LANDLORD);
//}
//
//void CGameButtonCtrl::CreatCtrl_RobLandLord()
//{
//	CreatCtrl_Pair(MS_TYPE::IS_ROB_LANDLORD);
//}
//
//void CGameButtonCtrl::CreatCtlr_Wait()
//{
//	/************************************************************************/
//	/*						      开始                                      */
//	/************************************************************************/
//	using namespace ImgGroupType;
//	Rect rect(Point(button_center.X-button_size.Width*1.5-10,button_center.Y),button_size);
//	CreatCtlr(rect,res.vec_button_img[准备],MS_TYPE::GAME_START);
//}
//
//void CGameButtonCtrl::CreatCtlr_Play()
//{
//	/************************************************************************/
//	/*					      出牌  不出  提示                               */
//	/************************************************************************/
//	using namespace ImgGroupType;
//	Rect rect(Point(button_center.X-button_size.Width*1.5-10,button_center.Y),button_size);
//	CreatCtlr(rect,res.vec_button_img[出牌],[this]
//	{
//		OurPlayCards();
//	});
//
//	rect.X+=button_size.Width+10;
//	CreatCtlr(rect,res.vec_button_img[不出],MS_TYPE::PASS);
//
//	rect.X+=button_size.Width+10;
//	//CreatCtlr(rect,res.vec_button_img[提示])
//}
//
//void CGameButtonCtrl::CreatCtlr(const Rect rect,const vector<pImage> & vec_img, const MS_TYPE ms_tp)
//{
//	CreatCtlr(rect,vec_img,[this,ms_tp]()
//	{
//		data.DealData(BuildProcessDate(ms_tp));
//		ls_clear_flag=true;
//		last_round_text[Self]=GetImgTextType(ms_tp);
//		theApp.game_action.Increase();
//	});
//}
//
//void CGameButtonCtrl::CreatCtlr(const Rect rect,const vector<pImage> & vec_img, const std::function<void()> cmd)
//{
//	CPNGButton * button;
//	button=new CPNGButton();
//	button->Create(rect,main_dlg,ls_game_ctrl.size(),vec_img);
//	button->SetCmd(cmd);
//	ls_game_ctrl.emplace_back(button);
//}
//
//void CGameButtonCtrl::OnPaint(Gdiplus::Graphics * const g) const
//{
//
//}
//
//void CGameButtonCtrl::OnGameStateChange(const GameState game_state)
//{
//
//}
