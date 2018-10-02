#pragma once

#include <vector>
#include "Text.h"
#include "Packdef.h"

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
	Cards m_card[54];//13*4+2=54张牌
	Point poker_center;
	std::vector<char> poker_in_hand;
	void ShowCtrl(Gdiplus::Graphics *  g);
	CText m_text[3];
	DECLARE_MESSAGE_MAP()
private:
	void InitVar();
	void ShowHandPoker(Gdiplus::Graphics *  g);
	Rect GetFirstCardRect();
	Rect GetLastCardRect();
	Rect GetHandCardRect();
	std::vector<pImage> vec_poker;
	Size card_size;
	const int card_interval;
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
};
