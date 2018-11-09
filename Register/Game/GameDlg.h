#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include "Packdef.h"
#include "PokerLogic.h"
#include "GamePlayer.h"
// CGameDlg 对话框

enum class GameState
{
	Wait,GetCards,Ready,Gaming,Over
};

class CGameCtrl;
class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(const wstring master,const int num=0 /*当前玩家是第几人*/ );   
	virtual ~CGameDlg();
	GameState game_state;
	
	wstring m_master;
// 对话框数据
	enum { IDD = IDD_GAMEDLG };
	
protected:
	HICON m_hIcon;
	
	int m_width,m_height;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
private:
	void InitPlayerInfo();
	void GameStart();
	void AddPlayer();
	void InitVar();
	void DrawRectFrame(Gdiplus::Graphics * g);
	void ShowPlayer(Gdiplus::Graphics * g);
	PlayerPosition SerialNum2Pos(const int num) const;	 //序列号转位置
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
	const int self_serial_num; //序列号
	Bitmap * bit_buf;
	Graphics * gra_buf;
public:
	std::array<bool,3> & have_player;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnGetMateInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDelPlayer(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetCards(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetLandlord(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGameWin(WPARAM wParam, LPARAM lParam);
};
