#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include "Packdef.h"
#include "PokerLogic.h"
#include "GamePlayer.h"
// CGameDlg 对话框


class CGameCtrl;
class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)
	friend class CGameCtrl;
public:
	CGameDlg(const int self_serial_num=0 /*当前玩家是第几人*/ );   
	virtual ~CGameDlg();
	
// 对话框数据
	enum { IDD = IDD_GAMEDLG };
	
protected:
	HICON m_hIcon;
	int m_width,m_height;
	DECLARE_MESSAGE_MAP()
private:
	void InitVar();
	void DrawRectFrame(Gdiplus::Graphics * g);
	int game_timer;
	CPoint lbutton_down;
	Rect select_region;
	bool is_lbutton_dowm;
	bool is_select_multi;
	ROOM_INFO & room_info;
	pImage back_img;
	CGameCtrl & game_ctrl;
	CPokerLogic & logic;
	CGamePlayer & players;
	Bitmap * bit_buf;
	Graphics * gra_buf;
	std::vector<CGameInterface *> vec_ctrl;
	GameState & r_game_state;
public:
	std::array<bool,3> & have_player;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnGetMateInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetCards(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetLandlord(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGameWin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGameRound(WPARAM wParam, LPARAM lParam);
};
