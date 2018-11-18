#pragma once

#include <vector>
#include <array>
#include <thread>
//#include "Packdef.h"
#include "PokerLogic.h"
#include "GamePlayer.h"
// CGameDlg 对话框


class CGameCtrl;
class GameState_EX;
class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)
	friend class CGameCtrl;
public:
	CGameDlg(const int self_serial_num=theApp.sys.client_info.player_pos /*当前玩家是第几人*/ );   
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
	GameState_EX & r_game_state;
	HANDLE 	h_Thread;
	int m_timer;
public:
	HANDLE thread_exit_flag;
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
	afx_msg LRESULT OnGameStateChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGameProcess(WPARAM wParam, LPARAM lParam);
};
