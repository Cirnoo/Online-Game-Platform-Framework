#pragma once

#include <vector>
#include "Text.h"
#include "Packdef.h"
#include "PokerLogic.h"
// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(wstring master);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
	enum { IDD = IDD_GAMEDLG };
	
protected:
	HICON m_hIcon;
	wstring m_master;
	int m_width,m_height;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	Point poker_center;
	std::vector<Poker> poker_in_hand;
	void ShowCtrl(Gdiplus::Graphics *  g);
	CText m_text[3];
	DECLARE_MESSAGE_MAP()
private:
	void InitVar();
	void DrawRectFrame(Gdiplus::Graphics * g);
	std::vector<pImage> vec_poker;
	CPoint lbutton_down;
	Rect select_region;
	bool is_lbutton_dowm;
	bool is_select_multi;
	CPokerLogic logic;
public:
	virtual BOOL OnInitDialog();
	void InitCtrl();
	void RandomShuffle();
	void SortHand();
	void GameStart();
	void AddPlayer();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
