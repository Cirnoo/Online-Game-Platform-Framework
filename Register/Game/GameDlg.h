#pragma once

#include <vector>
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
	CGameDlg(wstring master, int num /*当前玩家是第几人*/ );   
	virtual ~CGameDlg();

// 对话框数据
	enum { IDD = IDD_GAMEDLG };
	
protected:
	HICON m_hIcon;
	wstring m_master;
	int m_width,m_height;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
private:
	void GameStart();
	void AddPlayer();
	void InitVar();
	void DrawRectFrame(Gdiplus::Graphics * g);
	void ShowPlayer(Gdiplus::Graphics * g);
	GameState game_state;
	int game_timer;
	CPoint lbutton_down;
	Rect select_region;
	bool is_lbutton_dowm;
	bool is_select_multi;
	PlayerPosition SerialNum2Pos(const int num) const;	 //序列号转位置
	CGameCtrl & game_ctrl;
	CPokerLogic & logic;
	CGamePlayer & players;
	const int self_serial_num; //序列号
public:
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
	afx_msg LRESULT OnGetCards(WPARAM wParam, LPARAM lParam);
};
